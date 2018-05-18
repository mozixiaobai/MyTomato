
// XRayViewerv1.0Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "XRayViewerv1.0Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString  g_strProXmlPath;        //͸���Ĭ��ģ��
CString  g_strDocXmlPath;        //�����Ĭ��ģ��
std::vector<CString> g_vcRes;
std::vector<int>     g_vcSlid;
int g_nGrayValue[18][2]={{169,42}, {100,32}, {106,33}, {112,34}, {119,35}, {125,36}, {131,37}, {137,38}, {144,39}, {150,40},{156,41}, {162,42}, {169,43}, {175,44}, {181,45}, {187,46}, {194,47}, {200,48}};
CString  g_strEditInfo;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXRayViewerv10Dlg �Ի���




CXRayViewerv10Dlg::CXRayViewerv10Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXRayViewerv10Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_BShowTab    = TRUE;
	m_BShowList   = TRUE;
	m_BFullScreen = FALSE;
	m_BShowPicCtrl= FALSE;

	
}

void CXRayViewerv10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UDS_VIDEOCTRL1, m_conVideoCtrl);
	DDX_Control(pDX, IDC_TAB_CTRL, m_conTab);
	DDX_Control(pDX, IDC_LIST_IMAGE, m_conListCtrl);
	DDX_Control(pDX, IDC_STA_PIC, m_conPicCtrl);
	DDX_Control(pDX, IDC_BTN_FULLSCREEN, m_btnFullScreen);
	DDX_Control(pDX, IDC_BTN_LAST, m_btnZoomIn);
	DDX_Control(pDX, IDC_BTN_NEXT, m_btnZoomOut);
	DDX_Control(pDX, IDC_BTN_DRAG, m_btnDrag);
}

BEGIN_MESSAGE_MAP(CXRayViewerv10Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTRL, &CXRayViewerv10Dlg::OnSelchangeTabCtrl)
	ON_WM_SIZING()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_SCANSET, &CXRayViewerv10Dlg::OnScanset)
	ON_MESSAGE(WM_TEMPLATE, &CXRayViewerv10Dlg::OnTemplate)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGE, &CXRayViewerv10Dlg::OnDblclkListImage)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_IMAGE, &CXRayViewerv10Dlg::OnRclickListImage)
	ON_COMMAND(ID_32771, &CXRayViewerv10Dlg::On32771Delete)
	ON_COMMAND(ID_32772, &CXRayViewerv10Dlg::On32772Property)
	ON_BN_CLICKED(IDC_BTN_FULLSCREEN, &CXRayViewerv10Dlg::OnBnClickedBtnFullscreen)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CXRayViewerv10Dlg::OnBnClickedBtnNext)
	ON_WM_GETMINMAXINFO()
//	ON_WM_LBUTTONDBLCLK()
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_IMAGE, &CXRayViewerv10Dlg::OnItemchangedListImage)
ON_MESSAGE(WM_IMGPROCESS, &CXRayViewerv10Dlg::OnImgprocess)
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_MOVE()
ON_WM_LBUTTONUP()
ON_WM_MOUSEWHEEL()
ON_NOTIFY(NM_HOVER, IDC_LIST_IMAGE, &CXRayViewerv10Dlg::OnHoverListImage)
//ON_WM_NCHITTEST()
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BTN_LAST, &CXRayViewerv10Dlg::OnBnClickedBtnLast)
ON_MESSAGE(WM_REFRESHIMG, &CXRayViewerv10Dlg::OnRefreshimg)
ON_BN_CLICKED(IDC_BTN_DRAG, &CXRayViewerv10Dlg::OnBnClickedBtnDrag)
ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_CTRL, &CXRayViewerv10Dlg::OnSelchangingTabCtrl)
END_MESSAGE_MAP()


// CXRayViewerv10Dlg ��Ϣ��������

BOOL CXRayViewerv10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu; 
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

//	ShowWindow(SW_MAXIMIZE);     //����󻯰�ť��������󻯻��ڵ��������� ��˲��������������
	CRect rcWorkArea; 
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0); 
	MoveWindow(&rcWorkArea); 


	// TODO: �ڴ����Ӷ���ĳ�ʼ������
	/***********************************
	* 0������GDI+
	* 1��������ʼ��
	* 2�������ļ�·��
	* 3������Camera
	* 4����ȡ�����ļ�
	* 5�����÷ֱ���
	*    ���ò��п�
	* 6��ȷ��Camera֧����Щ���ԣ���������xml
	* 7������ģ�壬������Camera
	* 8��Tab Ctrl��ʼ��
	* 9����ȡ�ļ���ʽ
	* 10���˵���ʼ��
	* 11���ж�Ĭ��Ŀ¼�Ƿ����
	* 12����������
	*
	***********************************/
	/*0������GDI+*/
	GdiplusStartupInput m_StartupInput;
	ULONG_PTR m_pGdiToKen;
	GdiplusStartup(&m_pGdiToKen, &m_StartupInput, NULL);


	/*1��������ʼ��*/
	m_nMinWidth      = 1030;
	m_nMinHeight     = 600;
	m_nLastTemplate  = 0;
	m_nLastRes       = 0;
	m_nLastImgType   = 0;
	m_nLastPreRotate = 0;
	m_nLastMergeMode = 0;
	m_nImageCount    = 0;
	m_nThumbWidth    = 160;
	m_nThumbHeight   = 130;

	m_nLastRelay     = 30;

	m_nLastBrit   = 0;
	m_nLastCtst   = 0;
	m_nLastCGama  = 0;

	m_nViewMode   = 0;
	m_lLeftSite   = 0;
	m_lTopSite    = 0;
	m_lRightSite  = 0;
	m_lBottomSite = 0;

	m_nHDRBackLgt = 0;

	m_nVidoeMode  = 0;

	m_fPI         = 3.1415926;

	m_lReturnCode = -1;
	m_nAngleCount = 0;
	m_nPrcsIndex  = -1;

	m_nLineMode   = 1;
	m_nLineWidth  = 5;
	m_nArrowLen   = 35;
	m_nArrowAngle = 30;
	m_refLineColor= 255;

	m_nFontSize   =120;
	m_strFont     = _T("����");
	m_strIniPath  = _T("");
	m_BBold       = FALSE;
	m_BItalic     = FALSE;
	m_nNoteCount  = 0;

	m_ptNoteSite.x = 0;
	m_ptNoteSite.y = 0;

	m_nHDRCapDelay = 20;

	m_nLowLight    = 1;
	m_nHigLight    = 70;
	m_nLowDelay    = 20;
	m_nHigDelay    = 20;
	m_nLowGray     = 9;
	m_nHigGray     = 13;
	m_nLowBackLgt  = 0;
	m_nHigBackLgt  = 1;
	

	m_BShowTab    = TRUE;
	m_BShowList   = TRUE;
	m_BFullScreen = FALSE;
	m_BNoSaved    = FALSE;
	m_BSlcRect    = FALSE;
	m_BSlcRected  = FALSE;
	m_BPaintLine  = FALSE;
	m_BLButtonDown= FALSE;
	m_BSpaceDown  = TRUE;
	m_BEscDown    = TRUE;
	m_BClickTab   = FALSE;
	m_BSelectTab  = FALSE;
	m_BOriSize    = FALSE;
	m_BLabel      = FALSE;

	m_BHDRCap     = FALSE;
	m_BCtrl       = TRUE;

	m_strDevPID   = _T("");
	m_strDevVID   = _T("");
	m_strDevCode  = _T("");
	m_strMyCode1  = _T("thefirstdevice");
	m_strConfigDoc= _T("");
	m_strXmlDoc   = _T("");
	m_strThumbDoc = _T("");
	m_strCVDoc    = _T("");
	m_strSaveDoc  = _T("");
	m_strTabImg   = _T("");

	m_clrCtrlColor = RGB(72, 77, 91);
	m_clrBackColor = RGB(72, 77, 91);
	m_clrTextColor = RGB(255, 255, 255);

	pWnd           = GetDlgItem(IDC_STA_PIC);
	

	/*2����ȡ���á�ģ��Ŀ¼*/
	CFileFind     tem_fileFind;
	m_strConfigDoc  = Self_GetMyDocument();
	m_strConfigDoc += _T("\\");
	m_strConfigDoc += _T("UDSXRayData");
	if (!tem_fileFind.FindFile(m_strConfigDoc))
	{
		CreateDirectory(m_strConfigDoc, NULL);
	}

	m_strXmlDoc  = m_strConfigDoc;
	m_strXmlDoc += _T("\\");
	m_strXmlDoc += _T("xml");
	if (!tem_fileFind.FindFile(m_strXmlDoc))
	{
		CreateDirectory(m_strXmlDoc, NULL);
	}
	g_strProXmlPath = m_strXmlDoc;
	g_strProXmlPath += _T("\\");
//	g_strProXmlPath += _T("Ĭ��.xml");
//	g_strProXmlPath += _T("Default.xml");
	g_strProXmlPath += _T("͸���Ĭ��.xml");

	g_strDocXmlPath  = m_strXmlDoc;
	g_strDocXmlPath += _T("\\");
	g_strDocXmlPath += _T("�����Ĭ��.xml");

	m_strThumbDoc  = m_strConfigDoc;
	m_strThumbDoc += _T("\\");
	m_strThumbDoc += _T("ThumbBuffer");
	if (!tem_fileFind.FindFile(m_strThumbDoc))
	{
		CreateDirectory(m_strThumbDoc, NULL);
	}

	m_strCVDoc  = m_strConfigDoc;
	m_strCVDoc += _T("\\");
	m_strCVDoc += _T("CVBuffer");
	if (!tem_fileFind.FindFile(m_strCVDoc))
	{
		CreateDirectory(m_strCVDoc, NULL);
	}

	m_strIniPath  = m_strConfigDoc;
	m_strIniPath += _T("\\");
	m_strIniPath += _T("BaseConfig.ini");	
	CopyFile(_T("BaseConfig.ini"), m_strIniPath, TRUE);

	m_strXmlPath  = m_strConfigDoc;
	m_strXmlPath += _T("\\");
	m_strXmlPath += _T("config.xml");
	CopyFile(_T("config.xml"), m_strXmlPath, TRUE);

	m_strLangXmlPath  = m_strConfigDoc;
	m_strLangXmlPath += _T("\\");
	m_strLangXmlPath += _T("language.xml");
	CopyFile(_T("language.xml"), m_strLangXmlPath, TRUE);

	Self_ReadLanguageXml(m_strLangXmlPath, m_vcMainLang, _T("Main"));    //��ȡMain�ڵ��µ�����
	Self_ReadLanguageXml(m_strLangXmlPath, m_vcTipsLge, _T("Tips"));
	


//	Self_FindTems(m_strXmlDoc);

	/*3������Camera*/
	m_lReturnCode = m_conVideoCtrl.Initial();

	//if (m_lReturnCode != 0)
	//{
	//	MessageBox(m_vcTipsLge[1], m_vcTipsLge[0], MB_OK);
	//	CDialog::OnOK();
	//	return FALSE;
	//}
	//
	int  tem_nDevNum   = m_conVideoCtrl.GetDeviceCount();
	int  tem_nDevIndex = -1;
	Self_FindCamera(m_strXmlPath);
	for (int i=0; i<tem_nDevNum; i++)
	{
		CString  tem_strDevID = m_conVideoCtrl.GetDevDisplayName(i);
		
		int      tem_nPID     = tem_strDevID.Find(m_strDevPID);
		int      tem_nVID     = tem_strDevID.Find(m_strDevVID);
		if (tem_nPID!=-1 && tem_nVID!=-1 && m_strDevCode==m_strMyCode1)
		{
			tem_nDevIndex = i;
			break;
		}
	}
	if (tem_nDevIndex == -1)
	{
		MessageBox(m_vcTipsLge[2], m_vcTipsLge[0], MB_OK);
		CDialog::OnOK();
		return FALSE;
	}

	m_lReturnCode = m_conVideoCtrl.StartRun(tem_nDevIndex);

	/*4����ȡ�����ļ�*/
	Self_ReadIni(m_strIniPath);
	Self_ReadWaterIni(m_strIniPath);

	/*5�����÷ֱ��ʡ���ת��������ģʽ*/
	//�жϱ���ķֱ����Ƿ��ǲ�ֵ�ֱ���

	

	int  tem_nResNum = m_conVideoCtrl.GetResCount();
	m_nInterpolateReso = tem_nResNum;
	for (int i=0; i<tem_nResNum; i++)
	{
		CString tem_strResolution = m_conVideoCtrl.GetResolution(i);
		//�жϷֱ����Ƿ�<500W,С��500W��ֱ�ӹ���
		if (Self_FilterRes(tem_strResolution))
		{
			g_vcRes.push_back(tem_strResolution);
		}	
	}
	g_vcRes.push_back(_T("4480��3360"));


	/*6��ȷ��Camera����*/
	if (!PathFileExists(g_strProXmlPath))
	{
		Self_EnsureItems();
	}
	if (!PathFileExists(g_strDocXmlPath))
	{
		Self_EnsureItems2();     //���������Ĭ��ģ��
	}

	/*7������ģ�壬����Camera*/
	/*0515
	BOOL    tem_bTem = TRUE;
	for (int i=0; i<m_vcTemName.size(); i++)
	{
		if (m_strLastTem == m_vcTemName[i])
		{
			tem_bTem = FALSE;
			CString   tem_strTemPath = m_vcTemPath[i];
			Self_ReadXml(tem_strTemPath);
			m_nLastTemplate = i;
		}
	}
	if (tem_bTem)
	{
		Self_ReadXml(g_strProXmlPath);
		m_nLastTemplate = m_vcTemPath.size();
	}
	*/
	if (m_strLastTem == _T("͸���"))
	{
		Self_ReadXml(g_strProXmlPath);
	} 
	else
	{
		Self_ReadXml(g_strDocXmlPath);
	}

	
// 	if (m_nLastRes == m_nInterpolateReso)
// 	{
// 		//��ȡ���ֱ���������������Ϊ���ֱ���
// 		int  tem_nMaxIndex = Self_GetSpyRes(1);
// 		m_conVideoCtrl.SetResolution(tem_nMaxIndex);
// 	}
// 	else
// 	{
// 		//����Ϊ�ϴ�ʹ�õķֱ���
// 		m_conVideoCtrl.SetResolution(m_nLastRes);
// 	}
	
	switch (m_nLastPreRotate)
	{
	case 0:
		break;
	case 1:
		m_conVideoCtrl.RotatedVideo(1);
		break;
	case 2:
		m_conVideoCtrl.RotatedVideo(2);
		break;
	case 3:
		m_conVideoCtrl.RotatedVideo(3);
		break;
	default:
		break;
	}

	//Ĭ�ϻҶ�����
	m_conVideoCtrl.SetColorMode(2);
	
	//	m_conVideoCtrl.AdjuestImageCrop(TRUE);    //�����Զ�����
	//	m_conVideoCtrl.ManualImageCrop(TRUE);     //�����ֶ�����


	//˵�������̶����п�����÷�������ͷ��ʼ����ɵ��¼���

	

	/*8��Tab Ctrl*/
	m_conTab.InsertItem(0, m_vcMainLang[0]);
//	m_conTab.InsertItem(1, m_vcMainLang[1]);
	m_conTab.InsertItem(1, m_vcMainLang[2]);

	m_dlgOne.Create(IDD_DLG_ONG, GetDlgItem(IDC_TAB_CTRL));
//	m_dlgTwo.Create(IDD_DLG_TWO, GetDlgItem(IDC_TAB_CTRL));
	m_dlgThree.Create(IDD_DLG_THREE, GetDlgItem(IDC_TAB_CTRL));

	CRect  tem_rcTab;
	m_conTab.GetClientRect(&tem_rcTab);
	tem_rcTab.top     += 22;
	tem_rcTab.left += 2;


	m_dlgOne.MoveWindow(&tem_rcTab);
//	m_dlgTwo.MoveWindow(&tem_rcTab);
	m_dlgThree.MoveWindow(&tem_rcTab);

	m_dlgOne.ShowWindow(TRUE);
//	m_dlgTwo.ShowWindow(FALSE);
	m_dlgThree.ShowWindow(FALSE);

	m_conTab.SetCurSel(0);

	GetDlgItem(IDC_BTN_LAST)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_NEXT)->EnableWindow(TRUE);
//	GetDlgItem(IDC_BTN_LAST)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_BTN_NEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_HIDE);
	/*9����ȡ�ļ���ʽ*/
	switch(m_nLastImgType)
	{
	case 0:
		m_strFileFormat = _T(".bmp");
		break;
	case 1:
		m_strFileFormat = _T(".jpg");
		break;
	case 2:
		m_strFileFormat = _T(".png");
		break;
	case 3:
		m_strFileFormat = _T(".tif");
		break;
	case 4:
		m_strFileFormat = _T(".pdf");
		break;
	case 5:
		m_strFileFormat = _T(".dcm");
		break;
	default:
		m_strFileFormat = _T(".jpg");
		break;
	}

	/*10���˵���ʼ��*/
	m_ListMenu.LoadMenuW(IDR_MENU_LIST);

	/*11*/
	if (!PathFileExists(m_strSaveDoc))
	{
		//�����ڣ���ȡ����·�������޸�Ĭ��·������
		TCHAR MyDir[_MAX_PATH];  
		SHGetSpecialFolderPath(this->GetSafeHwnd(),MyDir,CSIDL_DESKTOP,0);
		m_strSaveDoc  = MyDir;
		m_strSaveDoc += _T("\\");
	}
	GetDlgItem(IDC_STA_CURDOCPATH)->SetWindowText(m_strSaveDoc);
	::WritePrivateProfileString(_T("BaseSet"), _T("SaveDoc"), m_strSaveDoc, m_strIniPath);

	GetDlgItem(IDC_STA_CURDOC)->SetWindowText(m_vcMainLang[3]);

	/*12����������*/
	//a��ListCtrl��������
	m_conListCtrl.SetBkColor(m_clrCtrlColor);

	//b���Ի��򱳾�����
	CDialogEx::SetBackgroundColor(m_clrBackColor);
	LoadPicture(m_imgBK, IDB_PNG_BKBLACK, _T("PNG"));

	//c����ťͼ��
	m_btnFullScreen.Init(IDB_PNG_FULLSCREEN, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnZoomIn.Init(IDB_PNG_ZOOMIN, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnZoomOut.Init(IDB_PNG_ZOOMOUT, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnDrag.Init(IDB_PNG_DRAG, BTN_IMG_3, BTN_TYPE_NORMAL);

	m_tipInfo.Create(this);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_FULLSCREEN), m_vcMainLang[4]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_LAST), m_vcMainLang[5]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_NEXT), m_vcMainLang[6]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_DRAG), m_vcMainLang[7]);

	m_tipInfo.SetDelayTime(TTDT_INITIAL, 100);
	m_tipInfo.SetDelayTime(TTDT_AUTOPOP, 5000);
	m_tipInfo.SetDelayTime(TTDT_RESHOW, 100);
	m_tipInfo.SetTipTextColor(RGB(255, 255, 255));
	m_tipInfo.SetTipBkColor(RGB(0, 0, 0));
	m_tipInfo.Activate(TRUE);

	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CXRayViewerv10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CXRayViewerv10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		CPaintDC  dc(this);
		CDC*      pDC = &dc;
		CDC       dcMem;
		dcMem.CreateCompatibleDC(pDC);

		CRect      tem_rcClient;
		GetClientRect(tem_rcClient);
		CBitmap memBitmap;
		memBitmap.CreateCompatibleBitmap(pDC, tem_rcClient.Width(), tem_rcClient.Height());
		dcMem.SelectObject(memBitmap);
		dcMem.FillSolidRect(tem_rcClient, RGB(72, 77, 91));	//���û�����ɫ
		if (!m_imgBK.IsNull())
		{
			CRect rcImg = CRect(0, 0, m_imgBK.GetWidth(), m_imgBK.GetHeight());
			m_imgBK.Draw(dcMem.m_hDC, rcImg, rcImg);
		}
		pDC->BitBlt(0, 0, tem_rcClient.Width(), tem_rcClient.Height(), &dcMem, 0, 0, SRCCOPY);
		memBitmap.DeleteObject();
 		if (m_BClickTab)
 		{
 			Self_ShowPicCtrl();
			m_BClickTab = FALSE;
 		}
//		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CXRayViewerv10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH CXRayViewerv10Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID()==IDC_STA_CURDOC || pWnd->GetDlgCtrlID()==IDC_STA_CURDOCPATH)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_clrTextColor);
	}


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CXRayViewerv10Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ�����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_tipInfo.RelayEvent(pMsg);
	}

	if (pMsg->message == WM_LBUTTONDBLCLK && !m_BShowPicCtrl)
	{
		CPoint   tem_ptCursor;
		GetCursorPos(&tem_ptCursor);
		CRect    tem_rcOCX;
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowRect(&tem_rcOCX);
		if (tem_rcOCX.PtInRect(tem_ptCursor))
		{
			if (m_BFullScreen)
			{
				Self_NormalScreen();
				/*
				GetDlgItem(IDC_STA_CURDOC)->EnableWindow(TRUE);
				GetDlgItem(IDC_STA_CURDOCPATH)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_FULLSCREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_LAST)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_DRAG)->EnableWindow(TRUE);
				*/
				GetDlgItem(IDC_STA_CURDOC)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(IDC_STA_CURDOCPATH)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(IDC_BTN_FULLSCREEN)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(IDC_BTN_LAST)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(IDC_BTN_NEXT)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(IDC_BTN_DRAG)->ShowWindow(SW_SHOWNORMAL);

// 				if (m_nViewMode == 1)
// 				{
// 					::SendMessage(this->m_hWnd, WM_SCANSET, 22, 0);
// 				}
				
			} 
			else
			{
				Self_FullScreen();
				/*
				GetDlgItem(IDC_STA_CURDOC)->EnableWindow(FALSE);
				GetDlgItem(IDC_STA_CURDOCPATH)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_FULLSCREEN)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_LAST)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_DRAG)->EnableWindow(FALSE);
				*/
				GetDlgItem(IDC_STA_CURDOC)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STA_CURDOCPATH)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTN_FULLSCREEN)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTN_LAST)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTN_NEXT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTN_DRAG)->ShowWindow(SW_HIDE);
				
// 				if (m_nViewMode == 1)
// 				{
// 					::SendMessage(this->m_hWnd, WM_SCANSET, 23, 0);
// 					m_nViewMode = 1;
// 				}
				
			}
		}
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_SPACE:
			//�ո��
			if (m_BSpaceDown)
			{
				::SendMessage(this->m_hWnd, WM_SCANSET, 11, 0);
				m_BSpaceDown = FALSE;
			}
			return TRUE;
			break;
		case VK_ESCAPE:
			//�˳���
			if (m_BEscDown)
			{
				//�жϴ�ʱ��ȫ��������ͨ״̬
				if (m_BFullScreen)
				{
					Self_NormalScreen();
					GetDlgItem(IDC_STA_CURDOC)->EnableWindow(TRUE);
					GetDlgItem(IDC_STA_CURDOCPATH)->EnableWindow(TRUE);
				} 
				else
				{
					::SendMessage(this->m_hWnd, WM_CLOSE, 0, 0);
				}
				m_BEscDown = FALSE;
			}
			return TRUE;
			break;
		case VK_RETURN:
			//�س���
			return TRUE;
			break;
		case VK_DELETE:
			//ɾ��
			break;
		case 0x5A:
			if (m_BCtrl)
			{
				//�ֶ�����
				m_BCtrl = FALSE;
				m_conVideoCtrl.ManualImageCrop(TRUE);
				m_conVideoCtrl.SetMessage(1);
			}
			break;
		}
	}
	else if (pMsg->message == WM_KEYUP)
	{
		switch(pMsg->wParam)
		{
		case VK_SPACE:
			m_BSpaceDown = TRUE;
			return TRUE;
			break;
		case VK_ESCAPE:
			m_BEscDown = TRUE;
			break;
		case VK_RETURN:
			return TRUE;
			break;
		case 0x5A:
			m_BCtrl = TRUE;
			::SendMessage(this->m_hWnd, WM_SCANSET, 16, 0);
			break;
		}
	}
	
	if (pMsg->message == WM_NCLBUTTONDBLCLK || pMsg->message == WM_NCLBUTTONDOWN)
	{
		if(pMsg->wParam == HTCAPTION)
		{
			return TRUE;
		}
	}

	//������ģ��������˭���ܷ��㡪��������������������������������������������������
	//����SliderCtrl����Release��Ϣ������Ҫ����������������Ϣ
	if (pMsg->message == WM_MOUSEHWHEEL || pMsg->message == WM_MOUSEWHEEL)
	{
		POINT   tem_CurPos;
		GetCursorPos(&tem_CurPos);
		pMsg->hwnd = ::WindowFromPoint(tem_CurPos);
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


void CXRayViewerv10Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴�������Ϣ�����������
	/*����OnInitDialogִ��*/
	if (::IsWindow(GetDlgItem(IDC_TAB_CTRL)->GetSafeHwnd()))
	{	
		if (IsIconic())
		{
			return;
		}

		CClientDC  dc(this);
		int   tem_nOcxWidth;     //���ڶ���OCX�ؼ�����ؼ���λ��
		int   tem_nScreenWidth; 
		int   tem_nScreenHeight;
		int   tem_nCellWidth = dc.GetDeviceCaps(LOGPIXELSX);
		int   tem_nCellHeight= dc.GetDeviceCaps(LOGPIXELSY);
		float tem_fOffsetY   = 0;
		BOOL  tem_BMax = IsZoomed();
		if (tem_BMax)
		{
			tem_nScreenWidth  = GetSystemMetrics(SM_CXSCREEN) ;
			tem_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
			tem_fOffsetY      = 0.8;
		} 
		else
		{
			CRect  tem_rcClient;
			GetClientRect(&tem_rcClient);
			tem_nScreenWidth  = tem_rcClient.Width();
			tem_nScreenHeight = tem_rcClient.Height();
			tem_fOffsetY      = 0.1;
		}
		//-----------------------------------------------------------------------------

		int   tem_nCx, tem_nCy, tem_nWidth, tem_nHeight;
		if (m_BShowTab && m_BShowList)
		{
			//ɨ��������̬��������
			//1��TabCtrl---------------------------------------------------------
			tem_nCx     = 5;
			tem_nCy     = 5;
			tem_nWidth  = (int)((tem_nCellWidth*1.0)*3.2-32);                                    //TabCtrl�� 3-inch
			tem_nHeight = (int)(tem_nScreenHeight - (tem_nCellHeight*1.0)*tem_fOffsetY);       //�ײ�Ԥ��0.7-inch, �����������ڵ�
			GetDlgItem(IDC_TAB_CTRL)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			CRect  tem_rcTab;
			m_conTab.GetClientRect(&tem_rcTab);
			tem_rcTab.top     += 22;
			tem_rcTab.left += 2;

			m_dlgOne.MoveWindow(&tem_rcTab);
//			m_dlgTwo.MoveWindow(&tem_rcTab);
			m_dlgThree.MoveWindow(&tem_rcTab);

			//2��ListCtrl--------------------------------------------------------
			tem_nWidth  = (int)((tem_nCellWidth*1.0)*2.5-32);                                  //TabCtrl�� 2.5-inch
			tem_nHeight = (int)(tem_nScreenHeight - (tem_nCellHeight*1.0)*tem_fOffsetY);       //�ײ�Ԥ��0.7-inch, �����������ڵ�
			tem_nCx     = tem_nScreenWidth - tem_nWidth-5;
			tem_nCy     = 5;
			GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			//2��OCX-------------------------------------------------------------
			m_conTab.GetClientRect(&tem_rcTab);
			CRect  tem_rcList;
			m_conListCtrl.GetClientRect(&tem_rcList);

			tem_nCx     = tem_rcTab.right + 10;
			tem_nCy     = 5;
			tem_nWidth  = tem_nScreenWidth - (tem_nCx + 15 +tem_rcList.Width());
			tem_nHeight = (int)(tem_nScreenHeight - (tem_nCellHeight*1.0)*tem_fOffsetY - (tem_nCellHeight*1.0)*0.3);     //Ԥ��1.5 inch����ΪOCX���滹�а�ť
			tem_nOcxWidth = tem_nWidth;

			if (m_BShowPicCtrl)
			{
				GetDlgItem(IDC_STA_PIC)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight-3, TRUE);
			} 
			else
			{
				GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
				m_conVideoCtrl.RefreshRect();
			}

			//3����ť-------------------------------------------------------------
			tem_nCy     = 7 + tem_nHeight;
			tem_nWidth  = 32;
			tem_nHeight = 32;
			GetDlgItem(IDC_BTN_FULLSCREEN)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			tem_nCx    += 42;
			GetDlgItem(IDC_BTN_LAST)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			tem_nCx    += 42;
			GetDlgItem(IDC_BTN_NEXT)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			tem_nCx    += 42;
			GetDlgItem(IDC_BTN_DRAG)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			tem_nCx    += 42;
			tem_nCy    += 7;
//			tem_nWidth  = 70;
			tem_nWidth  = 90;
			tem_nHeight = 30;
			GetDlgItem(IDC_STA_CURDOC)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			tem_nCx    += 90;
			tem_nWidth  = tem_nOcxWidth - 150;
			tem_nHeight =30;
			GetDlgItem(IDC_STA_CURDOCPATH)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);
			
			

		} 
		else if ((!m_BShowTab) && (!m_BShowList))
		{
			//ɨ��ȫ����̬

		}
		else if (m_BShowTab && (!m_BShowList))
		{
			//�༭״̬������
		}

		if (m_BShowPicCtrl && m_vcHistoryImg.size()>0)
		{
			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(GetDlgItem(IDC_STA_PIC), m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		}

	}
}


void CXRayViewerv10Dlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴�������Ϣ�����������
	
	if ((pRect->right-pRect->left)<1030)
	{
		if(fwSide == MOVE_LEFT || fwSide == MOVE_LTOP || fwSide == MOVE_LBOTTOM)
		{
			pRect->left = pRect->right - m_nMinWidth;
		}
		else if (fwSide == MOVE_RIGHT || fwSide == MOVE_RTOP || fwSide == MOVE_RBOTTOM)
		{
			pRect->right = pRect->left + m_nMinWidth;
		}
	}
	if ((pRect->bottom-pRect->top)<600)
	{
		if (fwSide == MOVE_TOP || fwSide == MOVE_LTOP || fwSide == MOVE_RTOP)
		{
			pRect->top = pRect->bottom - m_nMinHeight;
		}
		else if (fwSide == MOVE_BOTTOM || fwSide == MOVE_LBOTTOM || fwSide == MOVE_RBOTTOM)
		{
			pRect->bottom = pRect->top + m_nMinHeight;
		}
	}
	
}


void CXRayViewerv10Dlg::OnSelchangingTabCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if (m_BSelectTab)
	{
		*pResult=1;
	}
	else 
	{
		*pResult = 0;
	}

}


void CXRayViewerv10Dlg::OnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CRect rtlbl; 
	int  tem_nCursel = m_conTab.GetCurSel();
	switch(tem_nCursel)
	{
	case 0:
		m_dlgOne.ShowWindow(TRUE);
//		m_dlgTwo.ShowWindow(FALSE);
		m_dlgThree.ShowWindow(FALSE);
		Self_EnsureSave();
		Self_ShowOcxCtrl();
		m_BClickTab = FALSE;
		break;
		/*0515
	case 1:
		m_dlgOne.ShowWindow(FALSE);
//		m_dlgTwo.ShowWindow(TRUE);
		m_dlgThree.ShowWindow(FALSE);
		Self_EnsureSave();
		Self_ShowOcxCtrl();
		m_BClickTab = FALSE;
		break;
		*/
	case 1:
		m_dlgOne.ShowWindow(FALSE);
//		m_dlgTwo.ShowWindow(FALSE);
		m_dlgThree.ShowWindow(TRUE);
		//��ʾPicCtrl�ؼ���������ͼ��
		m_BClickTab = TRUE;
		Self_ShowPicCtrl();
		break;
	default:
		break;
	}


	*pResult = 0;
}


CString CXRayViewerv10Dlg::Self_GetMyDocument(void)
{
	CString        tem_strMyDocument = _T("");
	TCHAR          tem_cMyDocument[MAX_PATH] = {0};
	LPITEMIDLIST   tem_Pid = NULL;
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &tem_Pid);
	if (tem_Pid && SHGetPathFromIDList(tem_Pid, tem_cMyDocument))
	{
		tem_strMyDocument = tem_cMyDocument;
		return tem_strMyDocument;
	}
	return tem_strMyDocument;
}


void CXRayViewerv10Dlg::OnClose()
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	m_conVideoCtrl.StopRun();
	m_conVideoCtrl.Uninitial();

	//	Self_SetRelayZero();

	//����һ��ֱ����Ϊ1�����ⲿ���ڰ�ťʱ��������
//	Self_SetRelayValue(1);

	//������������0���ٵ�һ�������������Ҫ��һ��
		Self_SetRelay1();

	if (m_vcThumbPath.size()==0)
	{
		CDialogEx::OnClose();
	}

	std::vector<CString>::iterator  item;
	for (item=m_vcThumbPath.begin(); item!=m_vcThumbPath.end(); item++)
	{
		DeleteFile(*item);
	}

	//ȷ��ͼ�����Ƿ񱣴�
	if (m_vcFilePath.size()==0)
	{
		return;
	}
	if (m_vcHistoryImg.size()>2)
	{
		if (m_BNoSaved)
		{
//			int tem_nClose = MessageBox(_T("�޸���δ���棡�Ƿ񱣴棿"), _T("����"), MB_YESNO);
			int tem_nClose = MessageBox(m_vcMainLang[10], _T("UDS"), MB_YESNO);
			if (tem_nClose == 6)
			{
				//ȷ������
				CString tem_strNewImgPath = m_vcHistoryImg.back();
				CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
			}
		}
	}

	//ɾ�������ļ�
//	DeleteFile(m_strBufferImgPath);
	if (m_vcHistoryImg.size()>1)
	{
		//����ɾ��2���������ͼ��
		std::vector<CString>::iterator iter;
		for (iter=m_vcHistoryImg.begin()+1; iter!=m_vcHistoryImg.end(); iter++)
		{
			DeleteFile(*iter);
		}
	}


	CDialogEx::OnClose();
}


BOOL CXRayViewerv10Dlg::Self_FindCamera(CString xmlpath)
{
	const char*       tem_cInfo;
	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	//����xml�ļ�
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//���ڵ�
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();

	TiXmlElement*    tem_xmlChildElt= tem_xmlRootElt->FirstChildElement();
	tem_cInfo = tem_xmlChildElt->Value();

	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_cInfo = tem_xmlChildAtb->Value();
	m_strDevPID = tem_cInfo;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_cInfo       = tem_xmlChildAtb->Value();
	m_strDevVID = tem_cInfo;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_cInfo   = tem_xmlChildAtb->Value();
	m_strDevCode= tem_cInfo;

	return TRUE;
}


void CXRayViewerv10Dlg::Self_ReadIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("û���ҵ�Template��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strLastTem = tem_strRead;
	tem_strRead.ReleaseBuffer();

	/*�ֱ��ʺ�ͼ��������������ģ��
	::GetPrivateProfileString(_T("BaseSet"), _T("ResIndex"), _T("û���ҵ�ResIndex��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastRes = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ImgType"), _T("û���ҵ�ImgType��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastImgType = tem_nRead;
	tem_strRead.ReleaseBuffer();
	*/


	::GetPrivateProfileString(_T("BaseSet"), _T("PreRotate"), _T("û���ҵ�PreRotate��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastPreRotate = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("MergeMode"), _T("û���ҵ�MergeMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastMergeMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMark"), _T("û���ҵ�WaterMark��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastWaterMark = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("û���ҵ�NameMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("û���ҵ�NameDate��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameDate   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("û���ҵ�NameTime��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameTime   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("û���ҵ�NameDivide��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNameDivide = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("û���ҵ�NamePre1��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre1 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("û���ҵ�NamePre2��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre2 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("û���ҵ�NamePre3��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre3 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("û���ҵ�NameBegin��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameBegin   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("û���ҵ�NameBegin2��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameBegin2   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveDoc"), _T("û���ҵ���ͷSaveDoc��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strSaveDoc = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewMode"), _T("û���ҵ�ViewMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_nViewMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewLeft"), _T("û���ҵ�ViewLeft��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_lLeftSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewTop"), _T("û���ҵ�ViewTop��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead  = _ttoi(tem_strRead);
	m_lTopSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewRight"), _T("û���ҵ�ViewRight��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	m_lRightSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewBottom"), _T("û���ҵ�ViewBottom��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_lBottomSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("û���ҵ�SaveTips��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	if (tem_nRead == 0)
	{
		m_BShowTips = FALSE;
	}
	else
	{
		m_BShowTips = TRUE;
	}
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("û���ҵ�SaveFormat��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	if (tem_nRead == 0)
	{
		m_BSaveFmt = FALSE;
	}
	else
	{
		m_BSaveFmt = TRUE;
	}
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("lowvalue"), _T("û���ҵ�lowvalue��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nLowLight   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("higvalue"), _T("û���ҵ�SaveFormat��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nHigLight   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("VidoeMode"), _T("û���ҵ�VidoeMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nVidoeMode= tem_nRead;
	tem_strRead.ReleaseBuffer();	
}


void CXRayViewerv10Dlg::Self_ReadWaterIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMark"), _T("û���ҵ�WaterMark��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterMark = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterSite"), _T("û���ҵ���ͷWaterSite��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterSite = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterSize"), _T("û���ҵ���ͷWaterSize��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterSize = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterFont"), _T("û���ҵ���ͷWaterFont��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterFont = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterColor"), _T("û���ҵ���ͷWaterColor��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strWaterColor = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterInfo"), _T("û���ҵ���ͷWaterInfo��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strWaterInfo = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMode"), _T("û���ҵ���ͷWaterMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterMode = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
}


afx_msg LRESULT CXRayViewerv10Dlg::OnScanset(WPARAM wParam, LPARAM lParam)
{
	int tem_nOperation = (int)wParam;    //������
	int tem_nInfo      = (int)lParam;    //������Ϣ
	int tem_nMiddle    = 0;              
	CString   tem_strSlcTem;
	CString   tem_strImgName;
	CString   tem_strValue = _T("");
	CString   tem_strSlcDoc= _T("");
	
	int       tem_nItem = 0;
	switch(tem_nOperation)
	{
	case 0:
		if (tem_nInfo != m_nLastTemplate)
		{
			//Ӧ��ģ��
// 			if (tem_nInfo==m_vcTemPath.size())
// 			{
// 				tem_strSlcTem = g_strProXmlPath;
// 			}
// 			else
			{
				tem_strSlcTem = m_vcTemPath[tem_nInfo];
			}
			Self_ReadXml(tem_strSlcTem);
			m_dlgOne.Self_ResetUI(tem_strSlcTem);
//			m_dlgTwo.Self_ReadXml(tem_strSlcTem);
			m_nLastTemplate = tem_nInfo;

		}
		break;
	case 1:
		//����------------------------
//		m_dlgTwo.m_nLastRes = tem_nInfo;
//		m_dlgTwo.Self_UpdateSlider(4);
		//����ʵ��--------------------
		switch(tem_nInfo)
		{
		case 0:
			tem_nInfo = 6;
			break;
		case 1:
			tem_nInfo = 7;
			break;
		case 2:
			tem_nInfo = 8;
			break;
		case 3:
			tem_nInfo = 9;
			break;
		default:
			tem_nInfo = 8;
			break;
		}
		if (tem_nInfo!=m_nLastRes)
		{
			if (tem_nInfo==m_nInterpolateReso)
			{
				int  tem_nMaxIndex = Self_GetSpyRes(1);
//				m_conVideoCtrl.SetResolution(tem_nMaxIndex);
				m_conVideoCtrl.SetResolutionPro(tem_nMaxIndex, m_nVidoeMode);
				m_nLastRes = tem_nInfo;
			}
			else
			{
//				m_conVideoCtrl.SetResolution(tem_nInfo);
				m_conVideoCtrl.SetResolutionPro(tem_nInfo, m_nVidoeMode);
				m_nLastRes = tem_nInfo;
			}	
			//�������ûҽ�
			m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
			m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);
			m_conVideoCtrl.SetBacklightCom(m_nLastBackLight, 0);

		}
		break;
	case 2:
		if (tem_nInfo!=m_nLastImgType)
		{
// 			m_dlgTwo.m_nLastImgType = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(5);
			m_nLastImgType = tem_nInfo;
			switch(m_nLastImgType)
			{
			case 0:
				m_strFileFormat = _T(".bmp");
				break;
			case 1:
				m_strFileFormat = _T(".jpg");
				break;
			case 2:
				m_strFileFormat = _T(".png");
				break;
			case 3:
				m_strFileFormat = _T(".tif");
				break;
			case 4:
				m_strFileFormat = _T(".pdf");
				break;
			case 5:
				m_strFileFormat = _T(".dcm");
				break;
			default:
				m_strFileFormat = _T(".jpg");
				break;
			}

		}
		break;
	case 3:
		if (tem_nInfo!=m_nLastPreRotate)
		{
			switch (tem_nInfo)
			{
			case 0:
				m_conVideoCtrl.RotatedVideo(0);
				break;
			case 1:
				m_conVideoCtrl.RotatedVideo(1);
				m_conVideoCtrl.ManualImageCrop(TRUE);
				m_conVideoCtrl.SetMessage(1);
				m_conVideoCtrl.SetRectValue(239+191, 6, 466+191, 119);
				m_conVideoCtrl.SetMessage(0);	
				break;
			case 2:
				m_conVideoCtrl.RotatedVideo(2);
				break;
			case 3:
				m_conVideoCtrl.RotatedVideo(3);
				break;
			default:
				m_conVideoCtrl.RotatedVideo(0);
				break;
			}
			m_nLastPreRotate = tem_nInfo;
		}
		break;
	case 4:
		if (tem_nInfo!=m_nLastMergeMode)
		{
			m_nLastMergeMode = tem_nInfo;
		}
		break;
	case 5:
		//�Զ�����
		if (tem_nInfo == 5121314)
		{
			m_conVideoCtrl.SetBrightness(0, 1);		
		}
		else
		{
			m_conVideoCtrl.SetBrightness(tem_nInfo, 0);					
		}
		break;
	case 6:
		//�ֶ�����
		if (tem_nInfo!=m_nLastBright)
		{
			m_conVideoCtrl.SetBrightness(tem_nInfo, 0);
			m_nLastBright = tem_nInfo;
// 			m_dlgTwo.m_nLastBright = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(0);
		}
		break;
	case 7:
		//�Զ��Աȶ�
		if (tem_nInfo == 5121314)
		{
			m_conVideoCtrl.SetContrast(0, 1);

		}
		else
		{
			m_conVideoCtrl.SetContrast(tem_nInfo, 0);
		}
		break;
	case 8:
		//�ֶ��Աȶ�
		if (tem_nInfo!=m_nLastContrst)
		{
			m_conVideoCtrl.SetContrast(tem_nInfo, 0);
			m_nLastContrst = tem_nInfo;
// 			m_dlgTwo.m_nLastContrast = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(1);
		}
		break;
	case 9:
		tem_strSlcDoc = Self_SlcSaveDoc(); 
		if (tem_strSlcDoc!=_T(""))
		{
			m_strSaveDoc = tem_strSlcDoc;
		}
		break;
	case 10:
		if (IDOK==m_dlgWaterSet.DoModal())
		{
			Self_ReadWaterIni(m_strIniPath);
		}
		break;
	case 11:
		tem_strImgName  = Self_NamingFile(m_nImageCount);
//		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		Self_CapatureImg(tem_strImgName);
		m_nPrcsIndex = -1;
//		m_conVideoCtrl.RefreshRect();
		
		break;
	case 12:
		Self_ReadNameRule();
		break;
	case 13:
		if (tem_nInfo==1)
		{
			m_nWaterMark = 1;
		} 
		else
		{
			m_nWaterMark = 0;
		}
		break;
	case 14:
		m_conVideoCtrl.ShowPorpertiesWindow(TRUE);
		//�������ָ�����ǰģ�壬�����¼��ص�ǰģ��


		break;
	case 15:
		//���ò��п�
		
//		m_conVideoCtrl.ManualImageCrop(TRUE); 
//		m_conVideoCtrl.SetMessage(1);
		
		m_conVideoCtrl.GetRectValue(&m_lLeftSite, &m_lTopSite, &m_lRightSite, &m_lBottomSite);
		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conVideoCtrl.SetMessage(0);

		tem_strValue.Format(_T("%l"), m_lLeftSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewLeft"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%l"), m_lTopSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewTop"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%l"), m_lRightSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewRight"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%l"), m_lBottomSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewBottom"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		break;
	case 16:
		//ȷ�ϲ��п�
		m_nViewMode = 1;
		m_conVideoCtrl.GetRectValue(&m_lLeftSite, &m_lTopSite, &m_lRightSite, &m_lBottomSite);
		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conVideoCtrl.SetMessage(0);

		tem_strValue.Format(_T("%d"), m_lLeftSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewLeft"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%d"), m_lTopSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewTop"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%d"), m_lRightSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewRight"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();

		tem_strValue.Format(_T("%d"), m_lBottomSite);
		::WritePrivateProfileString(_T("BaseSet"), _T("ViewBottom"), tem_strValue, m_strIniPath);
		tem_strValue.ReleaseBuffer();
		break;
	case 17:
		Self_GetRelayStatus();
		break;
	case 18:
		if (tem_nInfo!=m_nLastRelay)
		{
			Self_SetRelayValue(tem_nInfo);
// 			m_dlgTwo.m_nLastLightBox = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(2);
		}
		break;
	//case 19,case 20��������У׼���ƣ�����������Ϊ0��100���Զ�У׼��ȱ�㣬����ͣ����0��100������һֱУ׼�������������
	case 19:
		/*ȡ��0У׼����
		Self_SetRelayZero();
		m_dlgTwo.m_nLastLightBox = 0;
		m_dlgTwo.Self_UpdateSlider(2);
		*/
		if (tem_nInfo!=m_nLastRelay)
		{
			Self_SetRelayValue(tem_nInfo);
// 			m_dlgTwo.m_nLastLightBox = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(2);
		}
		break;
	case 20:
		/*ȡ��100У׼����
		Self_SetRelay100();
		m_dlgTwo.m_nLastLightBox = 100;
		m_dlgTwo.Self_UpdateSlider(2);
		*/
		if (tem_nInfo!=m_nLastRelay)
		{
			Self_SetRelayValue(tem_nInfo);
// 			m_dlgTwo.m_nLastLightBox = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(2);
		}
		break;
	case 21:
		m_nViewMode = 0;
		m_conVideoCtrl.ManualImageCrop(TRUE); 
		m_conVideoCtrl.SetMessage(1);

//		m_dlgTwo.Self_UpdateSlider(7);
		break;
	case 22:
		m_nViewMode = 1;
		m_conVideoCtrl.ManualImageCrop(TRUE); 
		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conVideoCtrl.SetMessage(0);

//		m_dlgTwo.Self_UpdateSlider(7);
		break;
	case 23:
		m_nViewMode = 2;
		m_conVideoCtrl.ManualImageCrop(FALSE);
		m_conVideoCtrl.AdjuestImageCrop(FALSE);

		m_dlgOne.Self_UpdateSlider(7);
//		m_dlgTwo.Self_UpdateSlider(7);
		break;
	case 24:
		//�ҽ�
		if (tem_nInfo!=m_nLastGray)
		{		
			m_conVideoCtrl.SetGamma(g_nGrayValue[tem_nInfo][0], 0);     
			m_conVideoCtrl.SetGain(g_nGrayValue[tem_nInfo][1], 0);

			m_nLastGray = tem_nInfo;

//			m_dlgTwo.m_nLastGray = tem_nInfo;
//			m_dlgTwo.Self_UpdateSlider(3);
		}
		break;
	case 25:
		if (m_BHDR)
		{
			tem_strImgName  = Self_NamingFile(m_nImageCount);
			Self_CaptureHdrImg(tem_strImgName);
			m_nPrcsIndex = -1;
		}

		break;
	case 26:
		m_nViewMode = 3;
		m_conVideoCtrl.ManualImageCrop(FALSE); 
		m_conVideoCtrl.AdjuestImageCrop(TRUE);

//		m_dlgTwo.Self_UpdateSlider(6);
		break;
	case 27:
		/*0515
			tem_strSlcTem = m_vcTemPath[tem_nInfo];
			Self_ReadXml(tem_strSlcTem);
			m_dlgOne.Self_ResetUI(tem_strSlcTem);
// 			m_dlgTwo.Self_ReadXml(tem_strSlcTem);
			m_nLastTemplate = tem_nInfo;
			*/
		if (tem_nInfo==0)
		{
			//���¼���͸���ģ��
			Self_ReadXml(g_strProXmlPath);
			m_dlgOne.Self_ResetUI(g_strProXmlPath);
		}
		else
		{
			//���¼��ط����ģ��
			Self_ReadXml(g_strDocXmlPath);
			m_dlgOne.Self_ResetUI(g_strDocXmlPath);
		}	
		m_nLastTemplate = tem_nInfo;
		break;
	case 28:
		if (tem_nInfo==0)
		{
			//����͸���ģ��
			for (unsigned int i=0; i<m_vcTemPath.size(); i++, tem_nItem++)
			{
				tem_strSlcTem = m_vcTemPath[i];
				if (tem_strSlcTem.Find(_T("͸���Ĭ��")) >= 0)
				{
					
					Self_ReadXml(tem_strSlcTem);
					m_dlgOne.Self_ResetUI(tem_strSlcTem);
// 					m_dlgTwo.Self_ReadXml(tem_strSlcTem);
					m_dlgOne.Self_SetSlider(tem_strSlcTem);
					m_nLastTemplate = tem_nItem;
					break;
				}
			}
		}
		else
		{
			//���ط����ģ��
			for (unsigned int i=0; i<m_vcTemPath.size(); i++, tem_nItem++)
			{
				tem_strSlcTem = m_vcTemPath[i];
				if (tem_strSlcTem.Find(_T("�����Ĭ��")) >= 0)
				{
					m_BHDR = FALSE;
					Self_ReadXml(tem_strSlcTem);
					m_dlgOne.Self_ResetUI(tem_strSlcTem);
// 					m_dlgTwo.Self_ReadXml(tem_strSlcTem);
					m_dlgOne.Self_SetSlider(tem_strSlcTem);
					m_nLastTemplate = tem_nItem;
					break;
				}
			}
		}
		break;
	case 29:
		if (tem_nInfo==1)
		{
			m_BHDRCap = TRUE;
		}
		else
		{
			m_BHDRCap = FALSE;
		}
		break;
	case 30:
		tem_strImgName  = Self_NamingFile(m_nImageCount);
		Self_CaptureImgHDR(tem_strImgName);
		m_nPrcsIndex = -1;
		break;
	case 31:
		if (tem_nInfo==0)
		{
			Self_ReadXml(g_strProXmlPath);
			m_dlgOne.Self_ResetUI(g_strProXmlPath);
			m_dlgOne.Self_SetSlider(g_strProXmlPath);
			m_nLastTemplate = tem_nItem;
		}
		else
		{
			Self_ReadXml(g_strDocXmlPath);
			m_dlgOne.Self_ResetUI(g_strDocXmlPath);
			m_dlgOne.Self_SetSlider(g_strDocXmlPath);
			m_nLastTemplate = tem_nItem;
		}
		break;
	case 32:

		break;
	default:
		break;
	}
	return 0;
}


afx_msg LRESULT CXRayViewerv10Dlg::OnTemplate(WPARAM wParam, LPARAM lParam)
{
	int tem_nOperation = (int)wParam;    //������
	int tem_nInfo      = (int)lParam;    //������Ϣ
	CString*   tem_strInfo;
	tem_strInfo = new CString;
	long       tem_lCur;                 //û��ʵ������
	long       tem_lAuto;                //û��ʵ������

	switch(tem_nOperation)
	{
	case 0:
		break;
	//CheckBox-��Ӧ����Ϣ
	case 1:
		if (tem_nInfo != m_nLastIris)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetIris(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetIris(tem_nInfo, 0);
			}
			m_nLastIris = tem_nInfo;
		}
		break;
	case 2:
		if (tem_nInfo!=m_nLastBright)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetBrightness(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetBrightness(tem_nInfo, 0);

			}
			m_nLastBright = tem_nInfo;
			m_dlgOne.m_nLastBright = tem_nInfo;
			m_dlgOne.Self_UpdateSlider(0);
		}
		
		break;
	case 3:
		if (tem_nInfo!=m_nLastExpos)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetAutoExposure(TRUE);
			} 
			else
			{
				m_conVideoCtrl.SetExposure(tem_nInfo, 0);
				m_nLastExpos = tem_nInfo;
			}
			
		}
		
		break;
	case 4:
		if (tem_nInfo!=m_nLastFocus)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetFocus(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetFocus(tem_nInfo, 0);
			}
			m_nLastFocus = tem_nInfo;
		}
		
		break;
	case 5:
		if (tem_nInfo!=m_nLastGama)
		{
			if (tem_nInfo == 5211314)
			{
//				m_conVideoCtrl.SetGamma(0, 1);
			} 
			else
			{
//				m_conVideoCtrl.SetGamma(tem_nInfo, 0);
			}
			m_nLastGama = tem_nInfo;
		}
		
		break;
	case 6:
		if (tem_nInfo!=m_nLastGain)
		{
			if (tem_nInfo == 5211314)
			{
//				m_conVideoCtrl.SetGain(0, 1);
			} 
			else
			{
//				m_conVideoCtrl.SetGain(tem_nInfo, 0);
			}
			m_nLastGain = tem_nInfo;
		}
		
		break;
	case 7:
		if (tem_nInfo!=m_nLastHue)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetHue(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetHue(tem_nInfo, 0);
			}
			m_nLastHue = tem_nInfo;
		}
		
		break;
	case 8:
		if (tem_nInfo!=m_nLastPan)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetPan(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetPan(tem_nInfo, 0);
			}
			m_nLastPan = tem_nInfo;
		}
		
		break;
	case 9:
		if (tem_nInfo!=m_nLastRoll)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetRoll(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetRoll(tem_nInfo, 0);
			}
			m_nLastRoll = tem_nInfo;
		}
		
		break;
	case 10:
		if (tem_nInfo!=m_nLastTilt)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetTilt(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetTilt(tem_nInfo, 0);
			}
			m_nLastTilt = tem_nInfo;
		}
		
		break;
	case 11:
		if (tem_nInfo!=m_nLastZoom)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetZoom(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetZoom(tem_nInfo, 0);
			}
			m_nLastZoom = tem_nInfo;
		}
		
		break;
	case 12:
		if (tem_nInfo != m_nLastContrst)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetContrast(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetContrast(tem_nInfo, 0);
			}
			m_nLastContrst = tem_nInfo;
			m_dlgOne.m_nLastContrast = tem_nInfo;
			m_dlgOne.Self_UpdateSlider(1);
		}
		
		break;
	case 13:
		if (tem_nInfo!=m_nLastSharp)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetSharpness(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetSharpness(tem_nInfo, 0);
			}
			m_nLastSharp = tem_nInfo;
		}
		
		break;
	case 14:
		if (tem_nInfo!=m_nLastSatura)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetSaturation(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetSaturation(tem_nInfo, 0);
			}
			m_nLastSatura = tem_nInfo;
		}
	
		break;
	case 15:
		if (tem_nInfo!=m_nLastWhiteB)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetWhiteBalance(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetWhiteBalance(tem_nInfo, 0);
				m_nLastWhiteB = tem_nInfo;
			}
			
		}
		
		break;
	case 16:
		if (tem_nInfo!=m_nLastBackLight)
		{
			if (tem_nInfo == 5211314)
			{
				m_conVideoCtrl.SetBacklightCom(0, 1);
			} 
			else
			{
				m_conVideoCtrl.SetBacklightCom(tem_nInfo, 0);
			}
			m_nLastBackLight = tem_nInfo;
		}
		
		break;
	case 17:
		if (tem_nInfo!=m_nLastRelay)
		{
			Self_SetRelayValue(tem_nInfo);
			m_dlgOne.m_nLastLightBox = tem_nInfo;
			m_dlgOne.Self_UpdateSlider(2);
		}
		break;
	case 18:
		/*ȡ��0У׼����
		Self_SetRelayZero();
		m_dlgOne.m_nLastLightBox = 0;
		m_dlgOne.Self_UpdateSlider(2);
		*/
		if (tem_nInfo!=m_nLastRelay)
		{
			Self_SetRelayValue(tem_nInfo);
			m_dlgOne.m_nLastLightBox = tem_nInfo;
			m_dlgOne.Self_UpdateSlider(2);
		}
		break;
	case 19:
		/*ȡ��100У׼����
		Self_SetRelay100();
		m_dlgOne.m_nLastLightBox = 100;
		m_dlgOne.Self_UpdateSlider(2);
		*/
		if (tem_nInfo!=m_nLastRelay)
		{
			Self_SetRelayValue(tem_nInfo);
			m_dlgOne.m_nLastLightBox = tem_nInfo;
			m_dlgOne.Self_UpdateSlider(2);
		}
		break;
	case 20:
		//����ģ��
		m_dlgOne.Self_SlcNewTem();
		break;
	case 21:
		//����TWO��ʵ��ģ�屣��
		tem_strInfo = (CString*)lParam;
// 		m_dlgTwo.Self_CreateXml(*tem_strInfo);
//		MessageBox(*tem_strInfo);

		break;
	case 22:
		//�����Ӵ���һ��ģ���б�����ѡ����ģ��
		tem_strInfo = (CString*)lParam;
//		if (*tem_strInfo!=_T(""))
		{
			m_dlgOne.Self_RefrushTem(*tem_strInfo);

			
		}
		Self_FindTems(m_strXmlDoc);
		break;
	case 23:
		if (tem_nInfo!=m_nLastGray)
		{
			m_conVideoCtrl.SetGamma(g_nGrayValue[tem_nInfo][0], 0);
			m_conVideoCtrl.SetGain(g_nGrayValue[tem_nInfo][1], 0);
			m_nLastGray = tem_nInfo;
			m_dlgOne.m_nLastGrayScal = tem_nInfo;
			m_dlgOne.Self_UpdateSlider(3);
		}
		break;
	case 24:
		//�ֱ����л�
		//����-----------
		m_dlgOne.m_nLastRes = tem_nInfo;
		m_dlgOne.Self_UpdateSlider(4);
		//����ʵ��-------
		switch(tem_nInfo)
		{
		case 0:
			tem_nInfo = 6;
			break;
		case 1:
			tem_nInfo = 7;
			break;
		case 2:
			tem_nInfo = 8;
			break;
		case 3:
			tem_nInfo = 9;
			break;
		default:
			tem_nInfo = 8;
			break;
		}
		if (tem_nInfo!=m_nLastRes)
		{
			if (tem_nInfo==m_nInterpolateReso)
			{
				int  tem_nMaxIndex = Self_GetSpyRes(1);
//				m_conVideoCtrl.SetResolution(tem_nMaxIndex);
				m_conVideoCtrl.SetResolutionPro(tem_nMaxIndex, m_nVidoeMode);
				m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
				m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);
				m_conVideoCtrl.SetBacklightCom(m_nLastBackLight, 0);
				m_nLastRes = tem_nInfo;
			}
			else
			{
//				m_conVideoCtrl.SetResolution(tem_nInfo);
				m_conVideoCtrl.SetResolutionPro(tem_nInfo, m_nVidoeMode);
				m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
				m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);
				m_conVideoCtrl.SetBacklightCom(m_nLastBackLight, 0);
				m_nLastRes = tem_nInfo;
			}	
		}
		break;
	case 25:
		//ͼ���ʽ�л�
		//����--------------
		m_dlgOne.m_nLastImgType = tem_nInfo;
		m_dlgOne.Self_UpdateSlider(5);
		//����ʵ��-----------
		if (tem_nInfo!=m_nLastImgType)
		{
			m_nLastImgType = tem_nInfo;
			switch(m_nLastImgType)
			{
			case 0:
				m_strFileFormat = _T(".bmp");
				break;
			case 1:
				m_strFileFormat = _T(".jpg");
				break;
			case 2:
				m_strFileFormat = _T(".png");
				break;
			case 3:
				m_strFileFormat = _T(".tif");
				break;
			case 4:
				m_strFileFormat = _T(".pdf");
				break;
			case 5:
				m_strFileFormat = _T(".dcm");
				break;
			default:
				m_strFileFormat = _T(".jpg");
				break;
			}
		}
		break;
	case 26:
		if (tem_nInfo==1)
		{
			m_BHDR = TRUE;
		} 
		else
		{
			m_BHDR = FALSE;		
			m_dlgOne.Self_UpdateSlider(8);
		}
		break;
	case 27:
		if (tem_nInfo==1)
		{
			m_nHDRMerge = 1;
		} 
		else
		{
			m_nHDRMerge = 2;
		}
		break;
	case 28:
		if (tem_nInfo!=m_nHDRLight)
		{
			m_nHDRLight = tem_nInfo;
		}
		break;
	case 29:
		if (tem_nInfo!=m_nHDRDelay)
		{
			m_nHDRDelay = tem_nInfo;
		}
		break;
	case 30:
		if (tem_nInfo==1)
		{
			//��ѡ�����
			m_dlgOne.Self_UpdateSlider(6);
		}			
		else
		{
			//ȡ��
			//�жϵ�ǰ��m_nViewMode,�����Զ��򲻹ܣ�Ϊ�Զ�����Ϊ������ʽ

			m_dlgOne.Self_UpdateSlider(7);
			
			if (m_nViewMode == 3)
			{
				m_nViewMode = 2;
				m_conVideoCtrl.ManualImageCrop(FALSE);
				m_conVideoCtrl.AdjuestImageCrop(FALSE);
			}	
		}
		break;
	case 31:
		m_dlgOne.OnBnClickedBtnDefault();
		break;
	case 32:
		//HDR�ҽ�
		if (tem_nInfo!=m_nHDRGray)
		{
			m_nHDRGray = tem_nInfo;
		}
		break;
	case 33:
		//HDR���Ա�
		if (tem_nInfo==0)
		{
			m_nHDRBackLgt = 0;
		} 
		else
		{
			m_nHDRBackLgt = 1;
		}
		break;
	case 34:
		//Low��Դ
		m_nLowLight = tem_nInfo;
		break;
	case  35:
		//Low��ʱ
		m_nLowDelay = tem_nInfo;
		break;
	case 36:
		//Low�ҽ�
		m_nLowGray = tem_nInfo;
		break;
	case 37:
		//Low���Ա�
		m_nLowBackLgt = tem_nInfo;
		break;
	case 38:
		//High��Դ
		m_nHigLight = tem_nInfo;
		break;
	case 39:
		//High��ʱ
		m_nHigDelay = tem_nInfo;
		break;
	case 40:
		//High�ҽ�
		m_nHigGray = tem_nInfo;
		break;
	case 41:
		//Hight���Ա�
		m_nHigBackLgt = tem_nInfo;
		break;
	default:
		break;
	}
	return 0;
}


afx_msg LRESULT CXRayViewerv10Dlg::OnImgprocess(WPARAM wParam, LPARAM lParam)
{
	int      tem_nOperation = (int)wParam;    //������
	int      tem_nInfo      = (int)lParam;    //������Ϣ
	CString  tem_strProcess = _T("");         //����ɫ��ƽ������¼���ͼ��
	std::string strTempData;  

	/*case 0:תDCM*/
	int      tem_nRead      = 0;
	CString  tem_strRead    = _T("");
	CString  tem_strDcmPath = _T("");
//	std::vector<CString>::iterator item;
	int      tem_nIndex     = 0;
	switch(tem_nOperation)
	{
	case 0:
		//����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			//0)���������ʽ�Ի��ѡ�񱣴��ʽ
			if (m_BShowTips)
			{
				if (IDOK ==m_dlgSlcFormat.DoModal())
				{
					//�ض������ļ�
					::GetPrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("û���ҵ�SaveTips��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
					tem_nRead     = _ttoi(tem_strRead);
					if (tem_nRead == 0)
					{
						m_BShowTips = FALSE;
					}
					else
					{
						m_BShowTips = TRUE;
					}
					tem_strRead.ReleaseBuffer();

					::GetPrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("û���ҵ�SaveFormat��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
					tem_nRead     = _ttoi(tem_strRead);
					if (tem_nRead == 0)
					{
						m_BSaveFmt = FALSE;
					}
					else
					{
						m_BSaveFmt = TRUE;
					}
					tem_strRead.ReleaseBuffer();

				} 
				
			} 

			//1)����bufferͼ����Ϣ
			m_strBufferImgPath = m_vcHistoryImg.back();
			//2)�滻ԭ�ļ�
			CopyFile(m_strBufferImgPath, m_strFilesPath, FALSE);
			std::vector<CString>::iterator item;
			for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end()-1; item++)
			{
				DeleteFile(*item);
			}



			if (m_BSaveFmt)
			{
				//����ΪDcm��ʽ����������ͼ�Լ�������Ϣ
				
				//4)��ͼ��תΪdcm,�µ�ͼ��·��Ϊm_strBufferImgPath
				Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
				tem_strDcmPath = Self_Img2DCM(m_strFilesPath);

				//5)���Ҹ�������������m_vcFilePath���и���
				for (item=m_vcFilePath.begin(); item!=m_vcFilePath.end();item++, tem_nIndex++)
				{
					if (*item == m_strFilesPath)
					{
						m_vcFilePath[tem_nIndex] = tem_strDcmPath;
						break;
					}
				}

				//6)����ͼ����ʾ����ʾdcm���ܱ�����
				Self_ClearPicCtrl();
				Self_CVShowTipImage(_T("res\\tips.jpg"));
				m_cvSrcImage.release();
				m_cvDstImage.release();
				m_cvLastImg.release();
				m_cvNextImg.release();

				//7)����vector
				m_vcHistoryImg.clear();



			} 
			else
			{
				//����Ϊԭ��ʽ����������ͼ�Լ�������Ϣ

				//4)����ͼ����ʾ
				std::string strTempData = (CStringA)m_strBufferImgPath; 
				m_cvSrcImage.release();
				m_cvDstImage.release();
				m_cvLastImg.release();
				m_cvNextImg.release();
				m_cvSrcImage = imread(strTempData);
				Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
				//5)����vector
				m_vcHistoryImg.clear();
				m_vcHistoryImg.push_back(m_strFilesPath);
				m_vcHistoryImg.push_back(m_strBufferImgPath);
				//6)���±���
				m_BNoSaved  = FALSE;
				//7)��������ͼ
				Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
			}
		
			
		}
		break;
	case 1:
		//����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			CString  tem_strNewImg = m_vcHistoryImg.back();
			//ɾ�����һ��ͼ��
			DeleteFile(tem_strNewImg);
			//ɾ��vector���һ��Ԫ��
			m_vcHistoryImg.erase(m_vcHistoryImg.end()-1);
			//���µ�ַ
			tem_strNewImg = m_vcHistoryImg.back();		
			std::string tem_sNewImg = (CStringA)tem_strNewImg; 
			m_cvSrcImage  = imread(tem_sNewImg);	//���¼���ͼ������Ҫ���¼�������������к�ͼ��ߴ緢���仯
			tem_strNewImg.ReleaseBuffer();

			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);			
		}
		else if (m_vcHistoryImg.size()==2)
		{
			m_BNoSaved = FALSE;
		}
		break;
	case 2:
		//����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			//1)���¼���ͼ��
			std::string strTempData = (CStringA)m_strBufferImgPath; 
			m_cvSrcImage.release();
			m_cvDstImage.release();
			m_cvLastImg.release();
			m_cvNextImg.release();
			m_cvSrcImage = imread(strTempData);
			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			//2)ɾ����������ͼ��
			std::vector<CString>::iterator item;
			for (item=m_vcHistoryImg.begin()+2; item!=m_vcHistoryImg.end(); item++)
			{
				DeleteFile(*item);
			}
			//3)����vector
			m_vcHistoryImg.clear();
			m_vcHistoryImg.push_back(m_strFilesPath);
			m_vcHistoryImg.push_back(m_strBufferImgPath);
			//4)���±���
			m_BNoSaved  = FALSE;
		}
		break;
	case 3:
		//����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageRotate(m_cvSrcImage, 90);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ClearPicCtrl();
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 4:
		//����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageRotate(m_cvSrcImage, -90);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ClearPicCtrl();
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 5:
		//180����ת
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageRotate(m_cvSrcImage, 180);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 6:
		//ˮƽ����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageMirror(m_cvSrcImage, TRUE);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ResetImageRect();
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 7:
		//��ֱ����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_BNoSaved = TRUE;
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageMirror(m_cvSrcImage, FALSE);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ResetImageRect();
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		break;
	case 8:
		//�ֶ���ת
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_dlgThree.Self_DisableCtrl(2); 
		m_BNoSaved   = TRUE;
		m_BPaintLine = TRUE;
		Self_CreateLine();
		m_BSelectTab = TRUE;

//		m_cvSrcImage.copyTo(m_cvLastImg);
		
		break;
	case 9:
		//��ɫ
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_cvSrcImage.copyTo(m_cvLastImg);
		ImageInvert(m_cvSrcImage);
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		m_BNoSaved = TRUE;
		m_cvLastImg.release();
		m_cvNextImg.release();
		m_cvDstImage.release();
		break;
	case 10:
		//��
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = ImageSharp(m_cvSrcImage);
		m_cvSrcImage = m_cvDstImage.clone();
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		m_BNoSaved = TRUE;
		m_cvLastImg.release();
		m_cvNextImg.release();
		m_cvDstImage.release();
		break;
	case 11:
		//����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_BNoSaved = TRUE;
		m_BSlcRect = TRUE;
		Self_ResetImageRect();
		//���¼���ͼ��
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);

		break;
	case 12:
		//��Ӧ��Ļ
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		Self_ClearPicCtrl();
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 13:
		//���ȵ���
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			//�����ȵ������û�ԭλ

			m_dlgThree.Self_ResetSlider(0);
			break;
		}
		if (tem_nInfo!=m_nLastBrit)
		{
			m_dlgThree.Self_DisableCtrl(0);
			m_BNoSaved   = TRUE;
			m_nLastBrit  = tem_nInfo;
			m_cvSrcImage.copyTo(m_cvLastImg);
			m_cvDstImage = BrightAndContrast(m_cvSrcImage, m_nLastBrit, m_nLastCtst);
//			m_cvDstImage.copyTo(m_cvSrcImage);
			Self_ShowMatImage2(m_cvDstImage, m_rcImageShow);
			m_BSelectTab = TRUE;
		}

		break;
	case 14:
		//�Աȶȵ���
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			m_dlgThree.Self_ResetSlider(1);
			break;
		}
		if (tem_nInfo!=m_nLastCtst)
		{
			m_dlgThree.Self_DisableCtrl(0);
			m_BNoSaved   = TRUE;
			m_nLastCtst  = tem_nInfo;
			m_cvSrcImage.copyTo(m_cvLastImg);
			m_cvDstImage = BrightAndContrast(m_cvSrcImage, m_nLastBrit, m_nLastCtst);
//			m_cvDstImage.copyTo(m_cvSrcImage);
			Self_ShowMatImage2(m_cvDstImage, m_rcImageShow);
			m_BSelectTab = TRUE;
		}
		break;
	case 15:
		//���Ͷȵ���
		break;
	case 16:
		//Gama����
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			m_dlgThree.Self_ResetSlider(2);
			break;
		}
		if (tem_nInfo!=m_nLastCGama)
		{
			if (tem_nInfo!=0)
			{
				m_dlgThree.Self_DisableCtrl(0);
				m_BNoSaved   = TRUE;
				m_nLastCGama  = tem_nInfo;
				m_cvSrcImage.copyTo(m_cvLastImg);

				m_cvDstImage = ImageGamma(m_cvSrcImage, m_nLastCGama);
				//			m_cvDstImage.copyTo(m_cvSrcImage);
				Self_ShowMatImage2(m_cvDstImage, m_rcImageShow);
				m_BSelectTab = TRUE;
			}
			/*
			else
			{
				m_BNoSaved   = TRUE;
				m_nLastCGama  = tem_nInfo;
				m_cvSrcImage.copyTo(m_cvLastImg);
				m_cvSrcImage.copyTo(m_cvDstImage);
				Self_ShowMatImage2(m_cvDstImage, m_rcImageShow);
				m_BSelectTab = TRUE;

			}
			*/
			
		}
		break;
	case 17:
		//����ɫ�ʵ���
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		switch(tem_nInfo)
		{
		case 13:
		case 14:
		case 16:
			m_cvDstImage.copyTo(m_cvNextImg);
			Self_SaveLastImg();

			//���¼������Σ�������ܳ��ֺ���
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_BSelectTab = FALSE;
			break;
		case 8:
			if (m_nAngleCount!=0)
			{
				m_cvSrcImage = m_cvDstImage.clone();
			}
			Self_SaveLastImg();
			m_BPaintLine = FALSE;
			Self_CreateLine();
			m_nAngleCount = 0;
			m_BSelectTab = FALSE;
			break;
		case 20:
		case 21:
			m_cvDstImage.copyTo(m_cvNextImg);

			//���¼������Σ�������ܳ��ֺ���
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_BLabel     = FALSE;
			m_nNoteCount = 0;
			m_ptNoteSite.x = 0;
			m_ptNoteSite.y = 0;
			break;
		case 31:
			m_cvDstImage.copyTo(m_cvNextImg);

			//���¼������Σ�������ܳ��ֺ���
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_BLabel     = FALSE;
			m_nNoteCount = 0;
			break;
		}
		::SetFocus(m_hWnd);        //���ⴰ���޷���ӦOnMouseWheel��Ϣ
		break;
	case 18:
		//����ɫ�ʵ���
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		if (tem_nInfo == 8)
		{
			//������ת
			m_BPaintLine = FALSE;
			if (m_nAngleCount!=0)
			{
				m_cvSrcImage = m_cvLastImg.clone();
			}
			
			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_nAngleCount = 0;

			m_cvLastImg.release();
			m_cvNextImg.release();
		} 
		else if (tem_nInfo == 13 || tem_nInfo == 14 || tem_nInfo == 16)
		{
			//����ɫ��ƽ��
			m_cvSrcImage = m_cvLastImg.clone();

//			Self_ClearPicCtrl();
//			Self_ResetImageRect();
//			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);

			m_cvLastImg.release();
			m_cvNextImg.release();
		}
		else if (tem_nInfo == 20 || tem_nInfo ==21 || tem_nInfo == 31)
		{
			//��������
			for (int i=0; i<m_nNoteCount&&m_vcHistoryImg.size()>2; i++)
			{
				CString  tem_strNewImg = m_vcHistoryImg.back();
				//ɾ�����һ��ͼ��
				DeleteFile(tem_strNewImg);
				//ɾ��vector���һ��Ԫ��
				m_vcHistoryImg.erase(m_vcHistoryImg.end()-1);	 
			}
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);

			m_cvLastImg.release();
			m_cvNextImg.release();
			m_BLabel     = FALSE;
			m_nNoteCount = 0;
		}
		::SetFocus(m_hWnd);        //���ⴰ���޷���ӦOnMouseWheel��Ϣ
		m_BSelectTab = FALSE;
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 19:
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("����ͼ��ʧ�ܣ�"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		//ԭ���������÷Ŵ���С������ʵ��1:1ԭͼ��ʾ
// 		m_fCurRatio = 0.95;
// 		Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
// 		m_fCurRatio = 1.0;

		m_BOriSize = TRUE;
		BOOL tem_BRC; 
		if (m_fCurRatio<=0.95)
		{
			tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
			while (tem_BRC)
			{
				m_fCurRatio+=0.05;
				if (m_fCurRatio>=0.95)
				{
					m_BOriSize = FALSE;
					tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
					m_fCurRatio+=0.05;
					break;
				}
				tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
			}
		}
		else if (m_fCurRatio>=1.05)
		{
			tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
			while (tem_BRC)
			{
				m_fCurRatio-=0.05;
				if (m_fCurRatio<=1.05)
				{
					m_BOriSize = FALSE;
					tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
					m_fCurRatio-=0.05;
					break;
				}
				tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
			}
		}
		break;
	case 20:
		//����-------------------------------------------
		if (!m_cvSrcImage.data)
		{
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_dlgThree.Self_SetCtrl(1);
		m_dlgThree.Self_DisableCtrl(3); 

		m_nLineMode = 0;
		m_BNoSaved = TRUE;
		m_BLabel   = TRUE;
		Self_ResetImageRect();
		//���¼���ͼ��
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 21:
		//����ͷ
		if (!m_cvSrcImage.data)
		{
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_dlgThree.Self_SetCtrl(1);
		m_dlgThree.Self_DisableCtrl(3); 
		m_nLineMode = 1;
		m_BNoSaved = TRUE;
		m_BLabel   = TRUE;
		Self_ResetImageRect();
		//���¼���ͼ��
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 22:
		m_nLineWidth = tem_nInfo;
		break;
	case 23:
		m_refLineColor = tem_nInfo;
		break;
	case 24:
		//���⻭
		if (!m_cvSrcImage.data)
		{
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		
		m_nLineMode = 2;
		m_BNoSaved = TRUE;
		m_BLabel   = TRUE;
		Self_ResetImageRect();
		//���¼���ͼ��
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 25:
		//�������ֱ�ע
		if (!m_cvSrcImage.data)
		{
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_dlgThree.Self_SetCtrl(2);
		m_dlgThree.Self_DisableCtrl(3);
		m_nLineMode = 3;
		m_BNoSaved = TRUE;
		m_BLabel   = TRUE;
		Self_ResetImageRect();
		//���¼���ͼ��
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 26:
		//����
		switch(tem_nInfo)
		{
		case 0:
			m_strFont = _T("Arial");
			break;
		case 1:
			m_strFont = _T("Calibri");
			break;
		case 2:
			m_strFont = _T("Times New Roman");
			break;
		case 3:
			m_strFont = _T("����");
			break;
		case 4:
			m_strFont = _T("����");
			break;
		case 5:
			m_strFont = _T("����");
			break;
		case 6:
			m_strFont = _T("����");
			break;
		case 7:
			m_strFont = _T("����");
			break;
		case 8:
			m_strFont = _T("΢���ź�");
			break;
		case 9:
			m_strFont = _T("������");
			break;
		}
		break;
	case 27:
		//�����С
		m_nFontSize = tem_nInfo;
		break;
	case 28:
		//�Ӵ�
		if (tem_nInfo == 0)
		{
			m_BBold = FALSE;
		}
		else
		{
			m_BBold = TRUE;
		}
		break;
	case 29:
		//б��
		if (tem_nInfo == 0)
		{
			m_BItalic = FALSE;
		} 
		else
		{
			m_BItalic = TRUE;
		}
		break;
	case 30:
		//����
		break;
	case 31:
		m_cvSrcImage.copyTo(m_cvLastImg);
		m_cvDstImage = Self_AddText(m_cvSrcImage, m_rcImageShow, m_rcImageCrop, g_strEditInfo, m_refLineColor, m_strFont, m_nFontSize, m_BBold, m_BItalic);
		m_nNoteCount++;
		m_cvDstImage.copyTo(m_cvSrcImage);
		m_cvSrcImage.copyTo(m_cvNextImg);
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		Self_SaveLastImg();
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	default:
		break;
	}

	return 0;
}


//����͸���Ĭ��ģ��
void CXRayViewerv10Dlg::Self_EnsureItems(void)
{
	long       tem_lRC       = -1;    //����ֵ
	long       tem_lMark     = -1;    //�Ƿ�֧��
	long       tem_lAuto     = -1;    //�Զ�����
	long       tem_lCurVlaue = -1;    //��ǰֵ
	long       tem_lMaxValue = -1;    //���ֵ
	long       tem_lMinValue = -1;    //��Сֵ

	CString    tem_strName   = _T("");  //������

	PROPERTY   tem_stcCamera;

	std::vector<PROPERTY>  tem_vcCamera;	

	//1����ȡ����ͷ����-----------------------------------------------------
	//ָ��ģ�����
	//��Ȧ
	tem_strName = _T("Iris");
// 	tem_lRC = m_conVideoCtrl.GetIrisRange(&tem_lMinValue, &tem_lMaxValue);
// 	if (tem_lRC==0)
// 	{
// 		tem_lMark = 1;
// 		tem_stcCamera.m_strName = tem_strName;
// 		tem_stcCamera.m_lSuport = tem_lMark;
// 
// 		m_conVideoCtrl.GetIris(&tem_lCurVlaue, &tem_lAuto);
// 		if (tem_lAuto == 1)
// 		{
// 			tem_stcCamera.m_lAuto = 1;
// 		}
// 		else
// 		{
// 			tem_stcCamera.m_lAuto = 0;
// 		}
// 		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
// 		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
// 		tem_stcCamera.m_lMinValue = tem_lMinValue;
// 
// 		tem_vcCamera.push_back(tem_stcCamera);
// 	}
// 	else
	{

		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����-
	tem_strName = _T("Bright");
	tem_lRC = m_conVideoCtrl.GetBrightnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetBrightness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = -1;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ع�-
	tem_strName = _T("Expos");
	tem_lRC = m_conVideoCtrl.GetExposureRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetExposure(&tem_lCurVlaue, &tem_lAuto);
		tem_lAuto = 0;
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = -10;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Focus");
// 	tem_lRC = m_conVideoCtrl.GetFocusRange(&tem_lMinValue, &tem_lMaxValue);
// 	if (tem_lRC==0)
// 	{
// 		tem_lMark = 1;
// 		tem_stcCamera.m_strName = tem_strName;
// 		tem_stcCamera.m_lSuport = tem_lMark;
// 
// 		m_conVideoCtrl.GetFocus(&tem_lCurVlaue, &tem_lAuto);
// 		if (tem_lAuto == 1)
// 		{
// 			tem_stcCamera.m_lAuto = 1;
// 		}
// 		else
// 		{
// 			tem_stcCamera.m_lAuto = 0;
// 		}
// 		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
// 		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
// 		tem_stcCamera.m_lMinValue = tem_lMinValue;
// 
// 		tem_vcCamera.push_back(tem_stcCamera);
// 	}
// 	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//GAMA-
	tem_strName = _T("Gama");
	tem_lRC = m_conVideoCtrl.GetGammaRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetGamma(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 162;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����-
	tem_strName = _T("Gain");
	tem_lRC = m_conVideoCtrl.GetGainRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetGain(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 42;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//ɫ��
	tem_strName = _T("Hue");
	tem_lRC = m_conVideoCtrl.GetHueRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetHue(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//ȫ��-
	tem_strName = _T("Pan");
// 	tem_lRC = m_conVideoCtrl.GetPanRange(&tem_lMinValue, &tem_lMaxValue);
// 	if (tem_lRC==0)
// 	{
// 		tem_lMark = 1;
// 		tem_stcCamera.m_strName = tem_strName;
// 		tem_stcCamera.m_lSuport = tem_lMark;
// 
// 		m_conVideoCtrl.GetPan(&tem_lCurVlaue, &tem_lAuto);
// 		if (tem_lAuto == 1)
// 		{
// 			tem_stcCamera.m_lAuto = 1;
// 		}
// 		else
// 		{
// 			tem_stcCamera.m_lAuto = 0;
// 		}
// 		tem_stcCamera.m_lCurValue = 0;
// 		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
// 		tem_stcCamera.m_lMinValue = tem_lMinValue;
// 
// 		tem_vcCamera.push_back(tem_stcCamera);
// 	}
//	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Roll");
// 	tem_lRC = m_conVideoCtrl.GetRollRange(&tem_lMinValue, &tem_lMaxValue);
// 	if (tem_lRC==0)
// 	{
// 		tem_lMark = 1;
// 		tem_stcCamera.m_strName = tem_strName;
// 		tem_stcCamera.m_lSuport = tem_lMark;
// 
// 		m_conVideoCtrl.GetRoll(&tem_lCurVlaue, &tem_lAuto);
// 		if (tem_lAuto == 1)
// 		{
// 			tem_stcCamera.m_lAuto = 1;
// 		}
// 		else
// 		{
// 			tem_stcCamera.m_lAuto = 0;
// 		}
// 		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
// 		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
// 		tem_stcCamera.m_lMinValue = tem_lMinValue;
// 
// 		tem_vcCamera.push_back(tem_stcCamera);
// 	}
// 	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��б-
	tem_strName = _T("Tilt");
// 	tem_lRC = m_conVideoCtrl.GetTiltRange(&tem_lMinValue, &tem_lMaxValue);
// 	if (tem_lRC==0)
// 	{
// 		tem_lMark = 1;
// 		tem_stcCamera.m_strName = tem_strName;
// 		tem_stcCamera.m_lSuport = tem_lMark;
// 
// 		m_conVideoCtrl.GetTilt(&tem_lCurVlaue, &tem_lAuto);
// 		if (tem_lAuto == 1)
// 		{
// 			tem_stcCamera.m_lAuto = 1;
// 		}
// 		else
// 		{
// 			tem_stcCamera.m_lAuto = 0;
// 		}
// 		tem_stcCamera.m_lCurValue = 0;
// 		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
// 		tem_stcCamera.m_lMinValue = tem_lMinValue;
// 
// 		tem_vcCamera.push_back(tem_stcCamera);
// 	}
// 	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����-
	tem_strName = _T("Zoom");
// 	tem_lRC = m_conVideoCtrl.GetZoomRange(&tem_lMinValue, &tem_lMaxValue);
// 	if (tem_lRC==0)
// 	{
// 		tem_lMark = 1;
// 		tem_stcCamera.m_strName = tem_strName;
// 		tem_stcCamera.m_lSuport = tem_lMark;
// 
// 		m_conVideoCtrl.GetZoom(&tem_lCurVlaue, &tem_lAuto);
// 		if (tem_lAuto == 1)
// 		{
// 			tem_stcCamera.m_lAuto = 1;
// 		}
// 		else
// 		{
// 			tem_stcCamera.m_lAuto = 0;
// 		}
// 		tem_stcCamera.m_lCurValue = 0;
// 		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
// 		tem_stcCamera.m_lMinValue = tem_lMinValue;
// 
// 		tem_vcCamera.push_back(tem_stcCamera);
// 	}
//	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�Աȶ�-
	tem_strName = _T("Contrast");
	tem_lRC = m_conVideoCtrl.GetContrastRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetContrast(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 7;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//������-
	tem_strName = _T("Sharp");
	tem_lRC = m_conVideoCtrl.GetSharpnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetSharpness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 8;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//���Ͷ�-
	tem_strName = _T("Satura");
	tem_lRC = m_conVideoCtrl.GetSaturationRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetSaturation(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��ƽ��-
	tem_strName = _T("WhiteBlance");
	tem_lRC = m_conVideoCtrl.GetWhiteBalanceRange(&tem_lMinValue, &tem_lMaxValue);
//	tem_lRC = -1;
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetWhiteBalance(&tem_lCurVlaue, &tem_lAuto);
		tem_lAuto = 1;
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//���Ա�-
	tem_strName = _T("BackLight");
	tem_lRC = m_conVideoCtrl.GetBacklightComRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetBacklightCom(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�������
	tem_strName = _T("LightBox");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ҽ׵���
	tem_strName = _T("GrayScale");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��Χ�ع⿪��--------------------------------------------------------------------
	tem_strName = _T("HDR");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ϲ���ʽ
	tem_strName = _T("MergeMode");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;       
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;           //1-ˮƽ�ϲ���2-��ֱ�ϲ�
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ع�ƫ��
	tem_strName = _T("LightBox2");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 50;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��ʱ����
	tem_strName = _T("Delay");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 10;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ҽ׵���
	tem_strName = _T("HDRGRAY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 12;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//---------------------------------------------------------------------------------
	//����忪��
	tem_strName = _T("Doc");
	{
		tem_lMark = 0;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ֱ���
	tem_strName = _T("Res");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 2;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//ͼ������
	tem_strName = _T("Format");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��Χ�ع�Сģ�������Ա�CheckBoxѡ��
	tem_strName = _T("HDRBackLgt");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//HDRСģ��-----------------------------------
	//����1
	tem_strName = _T("LQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//�ҽ׵���1
	tem_strName = _T("LQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 9;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//��ʱ1
	tem_strName = _T("LQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 10;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//���Ա�1
	tem_strName = _T("LQUABCK");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 1;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����2
	tem_strName = _T("HQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 100;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//�ҽ׵���2
	tem_strName = _T("HQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 13;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//��ʱ2
	tem_strName = _T("HQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 10;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//���Ա�2
	tem_strName = _T("HQUABCK");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 1;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}


	/*��ȡĬ�ϲ�����CameraĬ�ϲ���
	//��Ȧ
	tem_strName = _T("Iris");
	tem_lRC = m_conVideoCtrl.GetIrisRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetIris(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;
		
		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{

		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Bright");
	tem_lRC = m_conVideoCtrl.GetBrightnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetBrightness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ع�
	tem_strName = _T("Expos");
	tem_lRC = m_conVideoCtrl.GetExposureRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetExposure(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Focus");
	tem_lRC = m_conVideoCtrl.GetFocusRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetFocus(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//GAMA
	tem_strName = _T("Gama");
	tem_lRC = m_conVideoCtrl.GetGammaRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetGamma(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Gain");
	tem_lRC = m_conVideoCtrl.GetGainRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetGain(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//ɫ��
	tem_strName = _T("Hue");
	tem_lRC = m_conVideoCtrl.GetHueRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetHue(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//ȫ��
	tem_strName = _T("Pan");
	tem_lRC = m_conVideoCtrl.GetPanRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetPan(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Roll");
	tem_lRC = m_conVideoCtrl.GetRollRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetRoll(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��б
	tem_strName = _T("Tilt");
	tem_lRC = m_conVideoCtrl.GetTiltRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetTilt(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Zoom");
	tem_lRC = m_conVideoCtrl.GetZoomRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetZoom(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�Աȶ�
	tem_strName = _T("Contrast");
	tem_lRC = m_conVideoCtrl.GetContrastRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetContrast(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//������
	tem_strName = _T("Sharp");
	tem_lRC = m_conVideoCtrl.GetSharpnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetSharpness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//���Ͷ�
	tem_strName = _T("Satura");
	tem_lRC = m_conVideoCtrl.GetSaturationRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetSaturation(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��ƽ��
	tem_strName = _T("WhiteBlance");
	tem_lRC = m_conVideoCtrl.GetWhiteBalanceRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetWhiteBalance(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//���Ա�
	tem_strName = _T("BackLight");
	tem_lRC = m_conVideoCtrl.GetBacklightComRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetBacklightCom(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	
	//�������
	tem_strName = _T("LightBox");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	*/



	//2����������XML-------------------------------------------------------
	TiXmlDocument      tem_xmlDoc;

	TiXmlDeclaration*  tem_xmlDec = new TiXmlDeclaration("1.0", "", "");
    tem_xmlDoc.LinkEndChild(tem_xmlDec);

	TiXmlElement*      tem_xmlElt = new TiXmlElement("property");
	tem_xmlDoc.LinkEndChild(tem_xmlElt);

	std::vector<PROPERTY>::iterator iter;
	for (iter=tem_vcCamera.begin(); iter!=tem_vcCamera.end();iter++)
	{
		CString      tem_strPetName = iter->m_strName;
		CStringA     tem_straPetName(tem_strPetName);
		const char*  tem_pcPetName = tem_straPetName.GetString();

		TiXmlElement*  tem_xmlElent = new TiXmlElement(tem_pcPetName); 
		tem_xmlElt->LinkEndChild(tem_xmlElent);
		
		tem_xmlElent->SetAttribute("support", iter->m_lSuport);
		tem_xmlElent->SetAttribute("auto", iter->m_lAuto);
		tem_xmlElent->SetAttribute("cur",iter->m_lCurValue);
		tem_xmlElent->SetAttribute("max", iter->m_lMaxValue);
		tem_xmlElent->SetAttribute("min", iter->m_lMinValue);	
	}

	//3������XML-----------------------------------------------------------
	CStringA      tem_straPath(g_strProXmlPath);
	const char*   tem_pcPath = tem_straPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcPath);
}


//���������Ĭ��ģ��
void CXRayViewerv10Dlg::Self_EnsureItems2(void)
{
	long       tem_lRC       = -1;    //����ֵ
	long       tem_lMark     = -1;    //�Ƿ�֧��
	long       tem_lAuto     = -1;    //�Զ�����
	long       tem_lCurVlaue = -1;    //��ǰֵ
	long       tem_lMaxValue = -1;    //���ֵ
	long       tem_lMinValue = -1;    //��Сֵ

	CString    tem_strName   = _T("");  //������

	PROPERTY   tem_stcCamera;

	std::vector<PROPERTY>  tem_vcCamera;	

	//1����ȡ����ͷ����-----------------------------------------------------
	//ָ��ģ�����
	//��Ȧ
	tem_strName = _T("Iris");
	{

		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����-
	tem_strName = _T("Bright");
	tem_lRC = m_conVideoCtrl.GetBrightnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetBrightness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ع�-
	tem_strName = _T("Expos");
	tem_lRC = m_conVideoCtrl.GetExposureRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetExposure(&tem_lCurVlaue, &tem_lAuto);
		tem_lAuto = 1;
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = -4;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Focus");
// 	tem_lRC = m_conVideoCtrl.GetFocusRange(&tem_lMinValue, &tem_lMaxValue);
// 	if (tem_lRC==0)
// 	{
// 		tem_lMark = 1;
// 		tem_stcCamera.m_strName = tem_strName;
// 		tem_stcCamera.m_lSuport = tem_lMark;
// 
// 		m_conVideoCtrl.GetFocus(&tem_lCurVlaue, &tem_lAuto);
// 		if (tem_lAuto == 1)
// 		{
// 			tem_stcCamera.m_lAuto = 1;
// 		}
// 		else
// 		{
// 			tem_stcCamera.m_lAuto = 0;
// 		}
// 		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
// 		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
// 		tem_stcCamera.m_lMinValue = tem_lMinValue;
// 
// 		tem_vcCamera.push_back(tem_stcCamera);
// 	}
// 	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//GAMA-
	tem_strName = _T("Gama");
	tem_lRC = m_conVideoCtrl.GetGammaRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetGamma(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 150;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����-
	tem_strName = _T("Gain");
	tem_lRC = m_conVideoCtrl.GetGainRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetGain(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 40;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//ɫ��
	tem_strName = _T("Hue");
	tem_lRC = m_conVideoCtrl.GetHueRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetHue(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//ȫ��-
	tem_strName = _T("Pan");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����
	tem_strName = _T("Roll");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��б-
	tem_strName = _T("Tilt");
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����-
	tem_strName = _T("Zoom");
// 	tem_lRC = m_conVideoCtrl.GetZoomRange(&tem_lMinValue, &tem_lMaxValue);
// 	if (tem_lRC==0)
// 	{
// 		tem_lMark = 1;
// 		tem_stcCamera.m_strName = tem_strName;
// 		tem_stcCamera.m_lSuport = tem_lMark;
// 
// 		m_conVideoCtrl.GetZoom(&tem_lCurVlaue, &tem_lAuto);
// 		if (tem_lAuto == 1)
// 		{
// 			tem_stcCamera.m_lAuto = 1;
// 		}
// 		else
// 		{
// 			tem_stcCamera.m_lAuto = 0;
// 		}
// 		tem_stcCamera.m_lCurValue = 0;
// 		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
// 		tem_stcCamera.m_lMinValue = tem_lMinValue;
// 
// 		tem_vcCamera.push_back(tem_stcCamera);
// 	}
// 	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�Աȶ�-
	tem_strName = _T("Contrast");
	tem_lRC = m_conVideoCtrl.GetContrastRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetContrast(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//������-
	tem_strName = _T("Sharp");
	tem_lRC = m_conVideoCtrl.GetSharpnessRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetSharpness(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 8;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//���Ͷ�-
	tem_strName = _T("Satura");
	tem_lRC = m_conVideoCtrl.GetSaturationRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetSaturation(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 3;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��ƽ��-
	tem_strName = _T("WhiteBlance");
	tem_lRC = m_conVideoCtrl.GetWhiteBalanceRange(&tem_lMinValue, &tem_lMaxValue);
//	tem_lRC = -1;
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetWhiteBalance(&tem_lCurVlaue, &tem_lAuto);
		tem_lAuto = 1;
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//���Ա�-
	tem_strName = _T("BackLight");
	tem_lRC = m_conVideoCtrl.GetBacklightComRange(&tem_lMinValue, &tem_lMaxValue);
	if (tem_lRC==0)
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;

		m_conVideoCtrl.GetBacklightCom(&tem_lCurVlaue, &tem_lAuto);
		if (tem_lAuto == 1)
		{
			tem_stcCamera.m_lAuto = 1;
		}
		else
		{
			tem_stcCamera.m_lAuto = 0;
		}
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	else
	{
		tem_lMark     = 0;
		tem_lAuto     = 0;
		tem_lCurVlaue = -1;
		tem_lMaxValue = -1;
		tem_lMinValue = -1;

		tem_stcCamera.m_strName   = tem_strName;
		tem_stcCamera.m_lSuport   = tem_lMark;
		tem_stcCamera.m_lAuto     = tem_lAuto;
		tem_stcCamera.m_lCurValue = tem_lCurVlaue;
		tem_stcCamera.m_lMaxValue = tem_lMaxValue;
		tem_stcCamera.m_lMinValue = tem_lMinValue;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�������
	tem_strName = _T("LightBox");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ҽ׵���
	tem_strName = _T("GrayScale");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 9;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��Χ�ع⿪��--------------------------------------------------------------------
	tem_strName = _T("HDR");
	{
		tem_lMark = 0;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ϲ���ʽ
	tem_strName = _T("MergeMode");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;       
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;           //1-ˮƽ�ϲ���2-��ֱ�ϲ�
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ع�ƫ��
	tem_strName = _T("LightBox2");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 50;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��ʱ����
	tem_strName = _T("Delay");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 10;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ҽ׵���
	tem_strName = _T("HDRGRAY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 12;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//---------------------------------------------------------------------------------
	//����忪��
	tem_strName = _T("Doc");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//�ֱ���
	tem_strName = _T("Res");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 2;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//ͼ������
	tem_strName = _T("Format");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//��Χ�ع�Сģ�������Ա�CheckBoxѡ��
	tem_strName = _T("HDRBackLgt");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//HDRСģ��-----------------------------------
	//����1
	tem_strName = _T("LQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//�ҽ׵���1
	tem_strName = _T("LQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 9;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//��ʱ1
	tem_strName = _T("LQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 10;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//���Ա�1
	tem_strName = _T("LQUABCK");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 1;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//����2
	tem_strName = _T("HQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 100;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//�ҽ׵���2
	tem_strName = _T("HQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 13;
		tem_stcCamera.m_lMaxValue = 17;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//��ʱ2
	tem_strName = _T("HQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 10;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//���Ա�2
	tem_strName = _T("HQUABCK");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;
		tem_stcCamera.m_lMaxValue = 1;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}


	//2����������XML-------------------------------------------------------
	TiXmlDocument      tem_xmlDoc;

	TiXmlDeclaration*  tem_xmlDec = new TiXmlDeclaration("1.0", "", "");
    tem_xmlDoc.LinkEndChild(tem_xmlDec);

	TiXmlElement*      tem_xmlElt = new TiXmlElement("property");
	tem_xmlDoc.LinkEndChild(tem_xmlElt);

	std::vector<PROPERTY>::iterator iter;
	for (iter=tem_vcCamera.begin(); iter!=tem_vcCamera.end();iter++)
	{
		CString      tem_strPetName = iter->m_strName;
		CStringA     tem_straPetName(tem_strPetName);
		const char*  tem_pcPetName = tem_straPetName.GetString();

		TiXmlElement*  tem_xmlElent = new TiXmlElement(tem_pcPetName); 
		tem_xmlElt->LinkEndChild(tem_xmlElent);
		
		tem_xmlElent->SetAttribute("support", iter->m_lSuport);
		tem_xmlElent->SetAttribute("auto", iter->m_lAuto);
		tem_xmlElent->SetAttribute("cur",iter->m_lCurValue);
		tem_xmlElent->SetAttribute("max", iter->m_lMaxValue);
		tem_xmlElent->SetAttribute("min", iter->m_lMinValue);	
	}

	//3������XML-----------------------------------------------------------
	CStringA      tem_straPath(g_strDocXmlPath);
	const char*   tem_pcPath = tem_straPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcPath);
}


int CXRayViewerv10Dlg::Self_FindTems(CString docpath)
{
	m_vcTemName.clear();
	m_vcTemPath.clear();
	int         tem_nFileCount = 0;    //���ļ�����
	BOOL        bGetRc      = NULL;
	CFileFind   temFinder   = NULL;
	CString     strFileName = NULL;
	CString     strSubDoc   = NULL;
	CString     strFilePath = NULL;


	bGetRc = temFinder.FindFile(docpath + "\\*.*");
	while (bGetRc)
	{
		bGetRc = temFinder.FindNextFile();
		if (temFinder.IsDots())
		{
			//ΪȱʡĿ¼
			continue;
		}
		else if (temFinder.IsDirectory())
		{
			//���Ϊ���ļ��У����汸��
			continue;
		} 
		else if (temFinder.IsCompressed())
		{
			//ѹ���ļ�
			continue;
		}
		else if (temFinder.IsSystem())
		{
			//ϵͳ�ļ�
			continue;
		}
		else
		{
			//���Ϊ�ļ������й���
			strFileName = temFinder.GetFileName();
			CString  strMiddle = strFileName;
			int      nIndex = strMiddle.ReverseFind('.');
			if (nIndex != -1)
			{
				strMiddle = strMiddle.Mid(nIndex+1);
				strMiddle.MakeLower();
				if (strMiddle == _T("xml"))		
				{
					//����ͼ���ļ��ͷ�ͼ���ļ�����FieName����
					tem_nFileCount++;
					strFilePath = _T("");
//					if (strFileName != _T("Ĭ��.xml"))
					{
						strFilePath = docpath + _T("\\") + strFileName;
						m_vcTemPath.push_back(strFilePath);
						strFileName = strFileName.Mid(0, nIndex);
						m_vcTemName.push_back(strFileName);
					}	
				}
			}
		}
	}	
	return tem_nFileCount;
}


void CXRayViewerv10Dlg::Self_ReadXml(CString xmlpath)
{
	const char*       tem_cInfo;
	int         tem_nMark     = 0;
	int         tem_nAuto     = 0;
	int         tem_nSetValue = 0;

	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	//����xml�ļ�
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//���ڵ�
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();
	
	//Iris�ڵ�
	TiXmlElement*    tem_xmlChildElt;
	tem_xmlChildElt = tem_xmlRootElt->FirstChildElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetIris(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastIris     = tem_nSetValue;
			m_conVideoCtrl.SetIris(tem_nSetValue, 0);
		}
	}

	//Bright�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetBrightness(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastBright   = tem_nSetValue;
			m_conVideoCtrl.SetBrightness(tem_nSetValue, 0);
		}
	}

	//Expos�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
//			m_conVideoCtrl.SetExposure(0, 1);
			m_conVideoCtrl.SetAutoExposure(1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastExpos    = tem_nSetValue;
			m_conVideoCtrl.SetExposure(tem_nSetValue, 0);
		}
	}

	//Focus�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetFocus(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastFocus    = tem_nSetValue;
			m_conVideoCtrl.SetFocus(tem_nSetValue, 0);
		}
	}

	//Gama�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
//			m_conVideoCtrl.SetGamma(0, 1);                //ֻ��ȡ�����ã��޸�Ϊ�ҽ�
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastGama     = tem_nSetValue;
//			m_conVideoCtrl.SetGamma(tem_nSetValue, 0);     //ֻ��ȡ�����ã��޸�Ϊ�ҽ�
		}
	}

	//Gain�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
//			m_conVideoCtrl.SetGain(0, 1);                    //ֻ��ȡ�����ã��޸�Ϊ�ҽ�
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastGain     = tem_nSetValue;
//			m_conVideoCtrl.SetGain(tem_nSetValue, 0);         //ֻ��ȡ�����ã��޸�Ϊ�ҽ�
		}
	}

	//Hue�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetHue(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastHue      = tem_nSetValue;
			m_conVideoCtrl.SetHue(tem_nSetValue, 0);
		}
	}

	//Pan�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetPan(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastPan      = tem_nSetValue;
			m_conVideoCtrl.SetPan(tem_nSetValue, 0);
		}
	}

	//Roll�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetRoll(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastRoll     = tem_nSetValue;
			m_conVideoCtrl.SetRoll(tem_nSetValue, 0);
		}
	}

	//Tilt�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetTilt(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastTilt     = tem_nSetValue;
			m_conVideoCtrl.SetTilt(tem_nSetValue, 0);
		}
	}

	//Zoom�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetZoom(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastZoom     = tem_nSetValue;
			m_conVideoCtrl.SetZoom(tem_nSetValue, 0);
		}
	}

	//Contrast�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetContrast(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastContrst  = tem_nSetValue;
			m_conVideoCtrl.SetContrast(tem_nSetValue, 0);
		}
	}

	//Sharp�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetSharpness(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastSharp    = tem_nSetValue;
			m_conVideoCtrl.SetSharpness(tem_nSetValue, 0);
		}
	}

	//Satura�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetSaturation(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastSatura   = tem_nSetValue;
			m_conVideoCtrl.SetSaturation(tem_nSetValue, 0);
		}
	}

	//WhiteBlance�ڵ�
	//����ƽ����Ϊ�Զ�����������
//	m_conVideoCtrl.SetWhiteBalance(0, 1);
	//����ʵ��������ð�ƽ��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetWhiteBalance(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastWhiteB   = tem_nSetValue;
			m_conVideoCtrl.SetWhiteBalance(tem_nSetValue, 0);
		}
	}
	

	//BackLight�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		if (tem_nAuto==1)
		{
			m_conVideoCtrl.SetBacklightCom(0, 1);
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastBackLight= tem_nSetValue;
//			m_conVideoCtrl.SetBacklightCom(tem_nSetValue, 0);
			//���Աȵ��������÷ֱ��ʺ��棬�������÷ֱ��ʻ��������Ա�
		}
	}

	//LightBox�ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nSetValue   = tem_xmlChildAtb->IntValue();
		
		//���õ���
		if (tem_nSetValue>50)
		{
			Self_SetRelay100();
		} 
		else
		{
			Self_SetRelayZero();
		}		
		Self_SetRelayValue(tem_nSetValue);
	}

	//�ҽ׽ڵ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();
		
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nSetValue   = tem_xmlChildAtb->IntValue();
		m_nLastGray     = tem_nSetValue;
		m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
		m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	}
	
	//HDR����
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		m_BHDR = TRUE;
	}
	else
	{
		m_BHDR = FALSE;
	}

	//�ϲ���ʽ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	if (tem_nSetValue==1)
	{
		m_nHDRMerge = 1;    //���Һϲ�
	} 
	else if(tem_nSetValue == 2)
	{
		m_nHDRMerge = 2;    //���ºϲ�
	}
	else
	{
		m_nHDRMerge = 0;    //�ϲ���ʽδ�򿪣���ʱ��Χ�ع�ر�
	}


	//����ƫ��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();

	m_nHDRLight = tem_nSetValue;

	//��ʱ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRDelay     = tem_nSetValue;

	//�ҽ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRGray      = tem_nSetValue;

	//����忪��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		m_BDOC = TRUE;
		//�����򿪣�Ԥ��ģʽ������������
		m_nViewMode = 3;
	}
	else
	{
		m_BDOC = FALSE;
		//�����رգ���͸���ض��򿪣�Ԥ��ģʽ����Ϊ3
// 		if (m_nViewMode == 3)
// 		{
// 			m_nViewMode = 2;
// 		}
		m_nViewMode = 1;
	}
	if (m_nViewMode == 0)
	{
		//�ֶ�����
		m_conVideoCtrl.ManualImageCrop(TRUE);
		m_conVideoCtrl.SetMessage(1);
	}
	else if (m_nViewMode == 1)
	{
		//�̶�����
		m_conVideoCtrl.ManualImageCrop(TRUE);
		m_conVideoCtrl.SetMessage(1);
		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conVideoCtrl.SetMessage(0);

	}
	else if(m_nViewMode == 2)
	{
		//Ԥ��ģʽ
		m_conVideoCtrl.ManualImageCrop(FALSE);
		m_conVideoCtrl.AdjuestImageCrop(FALSE);
	}
	else
	{
		//�Զ�����
		m_conVideoCtrl.ManualImageCrop(FALSE);
		m_conVideoCtrl.AdjuestImageCrop(TRUE);
	}
	
	//ͼ��ֱ���
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();

		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nSetValue   = tem_xmlChildAtb->IntValue();

		switch(tem_nSetValue)
		{
		case 0:
			m_nLastRes = 6;
			break;
		case 1:
			m_nLastRes = 7;
			break;
		case 2:
			m_nLastRes = 8;
			break;
		case 3:
			m_nLastRes = 9;
			break;
		default:
			m_nLastRes = 8;
			break;
		}		
	}
	if (m_nLastRes == m_nInterpolateReso)
	{
		//��ȡ���ֱ���������������Ϊ���ֱ���
		int  tem_nMaxIndex = Self_GetSpyRes(1);
//		m_conVideoCtrl.SetResolution(tem_nMaxIndex);
		m_conVideoCtrl.SetResolutionPro(tem_nMaxIndex, m_nVidoeMode);
	}
	else
	{
		//����Ϊ�ϴ�ʹ�õķֱ���
//		m_conVideoCtrl.SetResolution(m_nLastRes);
		m_conVideoCtrl.SetResolutionPro(m_nLastRes, m_nVidoeMode);
	}

	//���÷ֱ��ʺ����е���������һ�飬Ӧ����ֱ���
	m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
	m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	m_conVideoCtrl.SetBacklightCom(m_nLastBackLight, 0);


	//ͼ���ʽ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();

		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nSetValue   = tem_xmlChildAtb->IntValue();
		m_nLastImgType  = tem_nSetValue;
	}

	//��Χ�ع⡪�����Ա�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRBackLgt   = tem_nSetValue;

	//HDR-----------------------------------------------------------
	//LLGT------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowLight= tem_nSetValue;

	//LGRY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowGray= tem_nSetValue;

	//LDLY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowDelay= tem_nSetValue;

	//LBCK------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowBackLgt= tem_nSetValue;

	//HLGT------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigLight= tem_nSetValue;

	//HGRY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigGray= tem_nSetValue;

	//HDLY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigDelay= tem_nSetValue;

	//HBCK------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigBackLgt= tem_nSetValue;

}


void CXRayViewerv10Dlg::Self_ReadLanguageXml(CString xmlpath, vector <CString>& vec, CString nodename)
{
	const char*   tem_cInfo;
	int           tem_nMark     = 0;
	int           tem_nAuto     = 0;
	int           tem_nSetValue = 0;

	CStringA     tem_straXmlPath(xmlpath);
	const char*  tem_cXmlPath = tem_straXmlPath.GetString();

	CStringA     tem_straNodeName(nodename);
	const char*  tem_cNodeName = tem_straNodeName.GetString();


	//����xml�ļ�
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//���ڵ�---------------------------------------------------------------
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();

	TiXmlElement*    tem_xmlChildElt;
	tem_xmlChildElt = tem_xmlRootElt->FirstChildElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();


	CString  tem_strInfo = _T("");
	if (tem_nMark==1)
	{
		//����ǰ���������Ϣ
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		while (tem_xmlChildElt)
		{
			tem_cInfo = tem_xmlChildElt->Value();
			tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
			tem_nMark = tem_xmlChildAtb->IntValue();
			if (tem_nMark==1 && !strcmp(tem_cNodeName,tem_cInfo))
			{
				break;
			}
			tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		}

//		while (tem_xmlChildElt )
		{
			//��ȡ�ýڵ�����
			tem_cInfo = tem_xmlChildElt->Value();
			tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
			tem_nMark = tem_xmlChildAtb->IntValue();
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			while (tem_xmlChildAtb)
			{
				tem_cInfo       = tem_xmlChildAtb->Value();
				
				tem_strInfo     = tem_cInfo;
//				MessageBox(tem_strInfo);
				vec.push_back(tem_strInfo);
				tem_xmlChildAtb = tem_xmlChildAtb->Next();
			}
//			tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		}

	}
	else
	{
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		while (tem_xmlChildElt)
		{
			tem_cInfo = tem_xmlChildElt->Value();
			tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
			tem_nMark = tem_xmlChildAtb->IntValue();
			if (tem_nMark==0 && !strcmp(tem_cNodeName,tem_cInfo))
			{
				tem_xmlChildAtb = tem_xmlChildAtb->Next();
				while (tem_xmlChildAtb)
				{
					tem_cInfo       = tem_xmlChildAtb->Value();
					tem_strInfo     = tem_cInfo;
//					MessageBox(tem_strInfo);
					vec.push_back(tem_strInfo);
					tem_xmlChildAtb = tem_xmlChildAtb->Next();
				}
				break;
			}
			else
			{
				tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
			}		
		}
	}
}


CString CXRayViewerv10Dlg::Self_SlcSaveDoc(void)
{
	CString    tem_strSltPath;
	wchar_t    tem_crSltPath[MAX_PATH]; //Unicodeʹ��wchar_t��_t

	ZeroMemory(tem_crSltPath, sizeof(tem_crSltPath));
	BROWSEINFO   m_broseinfo;
	m_broseinfo.hwndOwner = m_hWnd;
	m_broseinfo.pidlRoot  = NULL;
	m_broseinfo.pszDisplayName = tem_crSltPath;
	m_broseinfo.lpszTitle = _T("ѡ�񱣴�Ŀ¼"); 
	m_broseinfo.ulFlags   = 0;
	m_broseinfo.lpfn      = NULL;
	m_broseinfo.lParam    = 0;
	m_broseinfo.iImage    = 0;
	LPITEMIDLIST   lp = SHBrowseForFolder(&m_broseinfo);
	if (lp&&SHGetPathFromIDList(lp, tem_crSltPath))
	{
		tem_strSltPath.Format(_T("%s"), tem_crSltPath);
//		m_strDefaultPath = tem_strSltPath;
		//ע������\\---------------------------------------------------------------------------------------
		
		//�����C��D�̣����һλ�Դ���\����������
		CString  tem_strLast = tem_strSltPath;
		tem_strLast = tem_strLast.Right(1);
		if (tem_strLast != _T("\\"))
		{
			tem_strSltPath += _T("\\");
		}
		::WritePrivateProfileString(_T("BaseSet"), _T("SaveDoc"), tem_strSltPath, m_strIniPath);
		GetDlgItem(IDC_STA_CURDOCPATH)->SetWindowText(tem_strSltPath);

		CRect  tem_rcRect;; 
		GetDlgItem(IDC_STA_CURDOCPATH)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

	} 
	
	return tem_strSltPath;
}


void CXRayViewerv10Dlg::Self_CapatureImg(CString imgname)
{
	BOOL       tem_BFirst       = TRUE;
	CString    tem_strImgName   = imgname;
	CString    tem_strThumbPath = m_strThumbDoc;
	CString    tem_strFilePath  = m_strSaveDoc;
	CString    tem_strPdfImg    = m_strThumbDoc;      //����PDF�ϲ�����
	CString    tem_strDcmImg    = m_strThumbDoc;      //����dcm���ģ��Լ��ϲ�����

	CString    tem_strInterImg  = m_strThumbDoc;      //��ֵԭͼ����·��

	tem_strThumbPath += _T("\\~");
	tem_strThumbPath += imgname;
	tem_strThumbPath += _T(".jpg");

	tem_strFilePath  += imgname;
	tem_strFilePath  += m_strFileFormat;

	tem_strPdfImg += _T("\\~~");
	tem_strPdfImg += imgname;
	tem_strPdfImg += _T(".jpg");

	tem_strDcmImg += _T("\\~~");
	tem_strDcmImg += imgname;
	tem_strDcmImg += _T(".jpg");

	tem_strInterImg += _T("\\~~~");
	tem_strInterImg += imgname;
	tem_strInterImg += _T(".jpg");


	if (m_nLastMergeMode == 1)
	{
		if (m_nLastImgType>=0 && m_nLastImgType<4)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//��ԭͼ����������Ŀ¼
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 1);

					//ͼ���ֵ
					Self_InterPolateImage(tem_strInterImg, tem_strFilePath, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conVideoCtrl.CaptureCombineEx(tem_strFilePath, 1);
				}
				
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strFilePath);
				}
				if (tem_BFirst)
				{
					MessageBox(m_vcTipsLge[3], m_vcTipsLge[0], MB_OK);
					tem_BFirst = FALSE;
				}
			}
			Self_CreateThumb(tem_strFilePath, tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			m_vcFilePath.push_back(tem_strFilePath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		} 
		else if (m_nLastImgType == 4)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//��ԭͼ����������Ŀ¼
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 1);
					
					//ͼ���ֵ
					Self_InterPolateImage(tem_strInterImg, tem_strPdfImg, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conVideoCtrl.CaptureCombineEx(tem_strPdfImg, 1);
				}
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strPdfImg);
				}
				if (tem_BFirst)
				{
					MessageBox(m_vcTipsLge[3], m_vcTipsLge[0], MB_OK);
					tem_BFirst = FALSE;
				}
			}
			Self_CreateThumb(tem_strPdfImg, tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			Self_GetPDFFromImg(tem_strPdfImg, tem_strFilePath);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strPdfImg);			
		}
		else if (m_nLastImgType == 5)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//��ԭͼ����������Ŀ¼
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 1);

					//ͼ���ֵ
					Self_InterPolateImage(tem_strInterImg, tem_strDcmImg, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conVideoCtrl.CaptureCombineEx(tem_strDcmImg, 1);
				}
				
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strDcmImg);
				}
				if (tem_BFirst)
				{
					MessageBox(m_vcTipsLge[3], m_vcTipsLge[0], MB_OK);
					tem_BFirst = FALSE;
				}
			}
			Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			//����dcmͼ��
			char*  tem_cName  = NULL;
			char*  tem_cId    = NULL;
			char*  tem_cBirth = NULL;
			char*  tem_cSex   = NULL;
			char*  tem_cDName = NULL;
			char*  tem_cDate  = NULL;
			char*  tem_cTime  = NULL;

			IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
			tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

			USES_CONVERSION;  
			char*   tem_cSrc = T2A(tem_strDcmImg);
			char*   tem_cDst = T2A(tem_strFilePath);
			tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
			
	}
	else if (m_nLastMergeMode==2)
	{
		if (m_nLastImgType>=0 && m_nLastImgType<4)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//��ԭͼ����������Ŀ¼
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 0);

					//ͼ���ֵ
					Self_InterPolateImage(tem_strInterImg, tem_strFilePath, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conVideoCtrl.CaptureCombineEx(tem_strFilePath, 0);
				}
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strFilePath);
				}
				if (tem_BFirst)
				{
					MessageBox(m_vcTipsLge[3], m_vcTipsLge[0], MB_OK);
					tem_BFirst = FALSE;
				}
			}
			Self_CreateThumb(tem_strFilePath, tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			m_vcFilePath.push_back(tem_strFilePath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		} 
		else if (m_nLastImgType == 4)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//��ԭͼ����������Ŀ¼
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 0);

					//ͼ���ֵ
					Self_InterPolateImage(tem_strInterImg, tem_strPdfImg, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conVideoCtrl.CaptureCombineEx(tem_strPdfImg, 0);
				}
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strPdfImg);
				}
				if (tem_BFirst)
				{
					MessageBox(m_vcTipsLge[3], m_vcTipsLge[0], MB_OK);
					tem_BFirst = FALSE;
				}
			}
			Self_CreateThumb(tem_strPdfImg, tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			Self_GetPDFFromImg(tem_strPdfImg, tem_strFilePath);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strPdfImg);			
		}
		else if (m_nLastImgType == 5)
		{
			for (int i=0; i<2; i++)
			{
				if (m_nLastRes==m_nInterpolateReso)
				{
					//��ԭͼ����������Ŀ¼
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 0);

					//ͼ���ֵ
					Self_InterPolateImage(tem_strInterImg, tem_strDcmImg, 0);
					::DeleteFile(tem_strInterImg);
				} 
				else
				{
					m_conVideoCtrl.CaptureCombineEx(tem_strDcmImg, 0);
				}
				
				if (m_nWaterMark == 1)
				{
					Self_AddWaterMark(tem_strDcmImg);
				}
				if (tem_BFirst)
				{
					MessageBox(m_vcTipsLge[3], m_vcTipsLge[0], MB_OK);
					tem_BFirst = FALSE;
				}
			}
			Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			//����dcmͼ��
			char*  tem_cName  = NULL;
			char*  tem_cId    = NULL;
			char*  tem_cBirth = NULL;
			char*  tem_cSex   = NULL;
			char*  tem_cDName = NULL;
			char*  tem_cDate  = NULL;
			char*  tem_cTime  = NULL;

			IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
			tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

			USES_CONVERSION;  
			char*   tem_cSrc = T2A(tem_strDcmImg);
			char*   tem_cDst = T2A(tem_strFilePath);
			tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
	}
	else
	{
		if (m_nLastImgType>=0 && m_nLastImgType<4)
		{
			//��ͨ����	
			if (m_nLastRes==m_nInterpolateReso)
			{
				//��ԭͼ����������Ŀ¼
				m_conVideoCtrl.CaptureImage(tem_strInterImg);

				//ͼ���ֵ
				Self_InterPolateImage(tem_strInterImg, tem_strFilePath, 0);
				::DeleteFile(tem_strInterImg);
			} 
			else
			{
				m_conVideoCtrl.CaptureImage(tem_strFilePath);
			}
			
			if (m_nWaterMark == 1)
			{
				Self_AddWaterMark(tem_strFilePath);
			}
			Self_CreateThumb(tem_strFilePath, tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			m_vcFilePath.push_back(tem_strFilePath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_nLastImgType == 4)
		{
			//pdf����
			/*����һ��OCX�Դ�pdf���գ����޷������Զ���ˮӡ*/
			/*
			m_conVideoCtrl.CapturePDF(tem_strFilePath);
			Self_GetImgFromPDF(tem_strFilePath, tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			m_vcFilePath.push_back(tem_strFilePath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			*/

			/*���̶���������ͨͼ����ת��Ϊpdf�ļ�*/
			//����ͼ�񱣴�������Ŀ¼
			if (m_nLastRes==m_nInterpolateReso)
			{
				//��ԭͼ����������Ŀ¼
				m_conVideoCtrl.CaptureImage(tem_strInterImg);

				//ͼ���ֵ
				Self_InterPolateImage(tem_strInterImg, tem_strDcmImg, 0);
				::DeleteFile(tem_strInterImg);
			} 
			else
			{
				m_conVideoCtrl.CaptureImage(tem_strDcmImg);	
			}

			if (m_nWaterMark == 1)
			{
				Self_AddWaterMark(tem_strDcmImg);
			}
			//��ȡ����ͼ
			Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ȡpdf�ļ�
			Self_GetPdfFromImg(tem_strDcmImg, tem_strFilePath);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
		else if (m_nLastImgType == 5)
		{
			//dcm����
			if (m_nLastRes==m_nInterpolateReso)
			{
				//��ԭͼ����������Ŀ¼
				m_conVideoCtrl.CaptureImage(tem_strInterImg);
				//ͼ���ֵ
				Self_InterPolateImage(tem_strInterImg, tem_strDcmImg, 0);
				::DeleteFile(tem_strInterImg);
			} 
			else
			{
				m_conVideoCtrl.CaptureImage(tem_strDcmImg);	
			}
			
			if (m_nWaterMark == 1)
			{
				Self_AddWaterMark(tem_strDcmImg);
			}
			Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			//����dcmͼ��
			char*  tem_cName  = NULL;
			char*  tem_cId    = NULL;
			char*  tem_cBirth = NULL;
			char*  tem_cSex   = NULL;
			char*  tem_cDName = NULL;
			char*  tem_cDate  = NULL;
			char*  tem_cTime  = NULL;

			IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
			tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

			USES_CONVERSION;  
			char*   tem_cSrc = T2A(tem_strDcmImg);
			char*   tem_cDst = T2A(tem_strFilePath);
			tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
	}
	Self_ShowImgInfo(tem_strFilePath);
	m_nImageCount++;
}


void CXRayViewerv10Dlg::Self_CaptureImgHDR(CString imgname)
{
	//�ļ�����---------------------------------------------------------------------------
	CString    tem_strLowImg    = m_strThumbDoc;      //Ƿ��ͼ��
	tem_strLowImg              += _T("\\lbmd");
	tem_strLowImg              += imgname;

	CString    tem_strNorImg    = m_strThumbDoc;      //����ͼ��
	tem_strNorImg              += _T("\\nbmd");
	tem_strNorImg              += imgname;

	CString    tem_strHigImg    = m_strThumbDoc;      //����ͼ��
	tem_strHigImg              += _T("\\hbmd");
	tem_strHigImg              += imgname;

	CString    tem_strHDRImg    = m_strThumbDoc;      //�ϳ�ͼ��
	tem_strHDRImg              += _T("\\bmd");
	tem_strHDRImg              += imgname;

	CString    tem_strThumbPath = m_strThumbDoc;      //����ͼ��
	tem_strThumbPath           += _T("\\~");
	tem_strThumbPath           += imgname;
	tem_strThumbPath           += _T(".jpg");

	CString    tem_strIntImg    = m_strThumbDoc;      //��ֵͼ��
	tem_strIntImg              += _T("\\~~~");
	tem_strIntImg              += imgname;

	CString    tem_strFilePath  = m_strSaveDoc;       //Ŀ���ļ�
	tem_strFilePath            += imgname;
	tem_strFilePath            += m_strFileFormat;
	
	if (m_nLastImgType>=0 && m_nLastImgType<4)
	{
		tem_strLowImg += m_strFileFormat;
		tem_strNorImg += m_strFileFormat;
		tem_strHigImg += m_strFileFormat;
		tem_strHDRImg += m_strFileFormat;
		tem_strIntImg += m_strFileFormat;
	} 
	else if(m_nLastImgType == 4 || m_nLastImgType == 5)
	{
		tem_strLowImg += _T(".jpg");
		tem_strNorImg += _T(".jpg");
		tem_strHigImg += _T(".jpg");
		tem_strHDRImg += _T(".jpg");
		tem_strIntImg += _T(".jpg");
	}

	//����ͼ��---------------------------------------------------------------------------
	m_conVideoCtrl.CaptureImage(tem_strNorImg);

	//���ڵ���---------------------------------------------------------------------------
	AdjustRelay(m_nLowLight, m_nLastRelay);
	//���ڻҽ�----------------------------------
	m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLowGray][0], 0);
	m_conVideoCtrl.SetGain(g_nGrayValue[m_nLowGray][1], 0);
	//�������Ա�------------------------------
	m_conVideoCtrl.SetBacklightCom(m_nLowBackLgt, 0);
	//������ʱ----------------------------------
	Self_TimeDelay(m_nLowDelay*100);
	//����-------------------------------------
	m_conVideoCtrl.CaptureImage(tem_strLowImg);


	//���ڵ���---------------------------------------------------------------------------
	AdjustRelay(m_nHigLight, m_nLowLight);
	//���ڻҽ�----------------------------------
	m_conVideoCtrl.SetGamma(g_nGrayValue[m_nHigGray][0], 0);
	m_conVideoCtrl.SetGain(g_nGrayValue[m_nHigGray][1], 0);
	//�������Ա�------------------------------
	m_conVideoCtrl.SetBacklightCom(m_nHigBackLgt, 0);
	//������ʱ----------------------------------
	Self_TimeDelay(m_nHigDelay*100);
	//����-------------------------------------
	m_conVideoCtrl.CaptureImage(tem_strHigImg);

	//�ϳ�ͼ��--------------------------------------------------------------------------
	Self_HDRMergeImgs(tem_strHigImg, tem_strNorImg, tem_strLowImg, tem_strHDRImg);
	::DeleteFile(tem_strHigImg);
	::DeleteFile(tem_strNorImg);
	::DeleteFile(tem_strLowImg);

	//�ָ�����--------------------------------------------------------------------------
	//�ָ�����---------------------------------
	AdjustRelay(m_nLastRelay, m_nHigLight);
	//�ָ��ҽ�---------------------------------
	m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);
	m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);	
	//�ָ����Ա�-----------------------------
	m_conVideoCtrl.SetBacklightCom(m_nLastBackLight, 0);

	//�Ƿ���Ҫ����ˮӡ-------------------------------------------------------------------
	if (m_nWaterMark == 1)
	{
		Self_AddWaterMark(tem_strHDRImg);
	}

	//��������ͼ------------------------------------------------------------------------
	Self_CreateThumb(tem_strHDRImg, tem_strThumbPath);

	//�Ƿ���Ҫ��ֵ----------------------------------------------------------------------
	if (m_nLastRes==m_nInterpolateReso)
	{
		Self_InterPolateImage(tem_strHDRImg, tem_strIntImg, 0);
		::DeleteFile(tem_strHDRImg);
		tem_strHDRImg = tem_strIntImg;
	}

	//�ж�ͼ���ʽ----------------------------------------------------------------------
	 if(m_nLastImgType == 4)
	 {
		 Self_GetPdfFromImg(tem_strHDRImg, tem_strFilePath);
	 }
	 else if (m_nLastImgType == 5)
	 {
		 char*  tem_cName  = NULL;
		 char*  tem_cId    = NULL;
		 char*  tem_cBirth = NULL;
		 char*  tem_cSex   = NULL;
		 char*  tem_cDName = NULL;
		 char*  tem_cDate  = NULL;
		 char*  tem_cTime  = NULL;

		 IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
		 tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

		 USES_CONVERSION;  
		 char*   tem_cSrc = T2A(tem_strHDRImg);
		 char*   tem_cDst = T2A(tem_strFilePath);
		 tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
	 }
	 else
	 {
		 CopyFile(tem_strHDRImg, tem_strFilePath, FALSE);
	 }
	 ::DeleteFile(tem_strHDRImg);
	
	 m_vcImgName.push_back(imgname);
	 m_vcThumbPath.push_back(tem_strThumbPath);
	 m_vcFilePath.push_back(tem_strFilePath);
	 ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	 Self_ShowImgInfo(tem_strFilePath);
	 m_nImageCount++;
}


void CXRayViewerv10Dlg::Self_HDRMergeImgs(CString higimg, CString norimg, CString lowimg, CString outimg)
{
	std::string tem_sHigImg = (CStringA)higimg; 
	std::string tem_sNorImg = (CStringA)norimg;
	std::string tem_sLowImg = (CStringA)lowimg;
	std::string tem_sOutImg = (CStringA)outimg;


	Mat   mat1 = imread(tem_sHigImg);
	Mat   mat2 = imread(tem_sNorImg);
	Mat   mat3 = imread(tem_sLowImg);

	int highWidth = mat1.rows;
	int highHeight = mat1.cols;
	int normalWidth = mat2.rows;
	int normalHeight = mat2.cols;
	int lowWidth = mat3.rows;
	int lowHeight = mat3.cols;

	Mat  dst_mat, tmp_mat;
	dst_mat = Mat(normalWidth, normalHeight, CV_8UC3, cv::Scalar(0, 0, 0));
	tmp_mat = Mat(normalWidth, normalHeight, CV_8UC1, cv::Scalar(0, 0, 0));

	int i, j;
	CvScalar s1, s2, s3;
	IplImage src1, src2, src3, dst_src, tmp_src;
	double weight=0.5;
	//�����е�Mat������ת��λ��IplImage����
	src1 = mat1;
	src2 = mat2;
	src3 = mat3;
	dst_src = dst_mat;
	tmp_src = tmp_mat;

	cvCvtColor(&src2, &tmp_src, CV_BGR2GRAY);
	int m=0, n=0;
	for(i=0; i< normalWidth; i++)
	{
		for(j=0; j<normalHeight; j++)
		{
			s1 = cvGet2D(&src1, i, j);
			s2 = cvGet2D(&tmp_src, i, j);
			s3 = cvGet2D(&src3, i, j);
			weight = 0.5 + (127 - s2.val[0]) * 0.002;
			s3.val[0] = (s1.val[0] * weight) + (s3.val[0] * (1-weight));
			s3.val[1] = (s1.val[1] * weight) + (s3.val[1] * (1-weight));
			s3.val[2] = (s1.val[2] * weight) + (s3.val[2] * (1-weight));
			cvSet2D(&dst_src, i, j, s3);
		}	
	}
	imwrite(tem_sOutImg, dst_mat);
}

void CXRayViewerv10Dlg::Self_CaptureHdrImg(CString imgname)
{
	BOOL       tem_BFirst       = TRUE;
	CString    tem_strImgName   = imgname;
	CString    tem_strThumbPath = m_strThumbDoc;
	CString    tem_strFilePath  = m_strSaveDoc;
	CString    tem_strPdfImg    = m_strThumbDoc;      //����PDF�ϲ�����
	CString    tem_strDcmImg    = m_strThumbDoc;      //����dcm���ģ��Լ��ϲ�����

	CString    tem_strInterImg  = m_strThumbDoc;      //��ֵԭͼ����·��

	tem_strThumbPath += _T("\\~");          //��������ͼ
	tem_strThumbPath += imgname;
	tem_strThumbPath += _T(".jpg");

	tem_strFilePath  += imgname;            //����ģʽ����ԭͼ
	tem_strFilePath  += m_strFileFormat;

	tem_strPdfImg += _T("\\~~");       //PDF����ԭͼ
	tem_strPdfImg += imgname;
	tem_strPdfImg += _T(".jpg");

	tem_strDcmImg += _T("\\~~");        //DCM����ԭͼ
	tem_strDcmImg += imgname;
	tem_strDcmImg += _T(".jpg");

	tem_strInterImg += _T("\\~~~");     //��ֵ����ԭͼ
	tem_strInterImg += imgname;
	tem_strInterImg += _T(".jpg");

	CString  tem_strOriImg = _T("");    //��֮ǰ�߼���ͨ��ͳһ��ͼ������������Ŀ¼
	CString  tem_strDstImg = _T("");

	if (m_nLastImgType>=0 && m_nLastImgType<4)
	{
		//��ͨͼ��
		tem_strOriImg  = m_strThumbDoc;
		tem_strOriImg += _T("\\~~");
		tem_strOriImg += imgname;        
		tem_strOriImg += m_strFileFormat;
	}
	else if(m_nLastImgType==4)
	{
		//pdf����
		tem_strOriImg = tem_strPdfImg;
	}
	else if(m_nLastImgType==5)
	{
		//dcm����
		tem_strOriImg = tem_strDcmImg;
	}

	//��ͼ*****************************************************************************
	if (m_nHDRMerge==1)
	{
		//���Һϲ�
		for (int i=0; i<2; i++)
		{
			m_conVideoCtrl.CaptureCombineEx(tem_strOriImg, 1);
							
			if (tem_BFirst)
			{
				//�޸ĵ�������m_nHDRLight
				AdjustRelay(m_nHDRLight, m_nLastRelay);
				//�����ҽ�m_nHDRGray
				if (m_nLastGray != m_nHDRGray)
				{
					m_conVideoCtrl.SetGamma(g_nGrayValue[m_nHDRGray][0], 0);   
					m_conVideoCtrl.SetGain(g_nGrayValue[m_nHDRGray][1], 0);
				}
				
				if (m_nLastBackLight != m_nHDRBackLgt)
				{
					m_conVideoCtrl.SetBacklightCom(m_nHDRBackLgt, 0);
				}

				//��ʱ����
				Self_TimeDelay(m_nHDRDelay*100);
				tem_BFirst = FALSE;
			}	
		}	 
	}
	else
	{
		//���ºϲ�
		for (int i=0; i<2; i++)
		{
			m_conVideoCtrl.CaptureCombineEx(tem_strOriImg, 0);

			if (tem_BFirst)
			{
				//�޸ĵ�������m_nHDRLight
				AdjustRelay(m_nHDRLight, m_nLastRelay);
				//�����ҽ�m_nHDRGray
				if (m_nLastGray != m_nHDRGray)
				{
					m_conVideoCtrl.SetGamma(g_nGrayValue[m_nHDRGray][0], 0);     
					m_conVideoCtrl.SetGain(g_nGrayValue[m_nHDRGray][1], 0);
				}
				
				if (m_nLastBackLight != m_nHDRBackLgt)
				{
					m_conVideoCtrl.SetBacklightCom(m_nHDRBackLgt, 0);
				}

				//��ʱ����
				Self_TimeDelay(m_nHDRDelay*10);
				tem_BFirst = FALSE;
			}	
		}	
	}

	//����ͼ����ʾ*********************************************************************
	Self_CreateThumb(tem_strOriImg, tem_strThumbPath);
	m_vcImgName.push_back(tem_strImgName);
	m_vcThumbPath.push_back(tem_strThumbPath);
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	//����ˮӡ*************************************************************************
	if (m_nWaterMark == 1)
	{
		Self_AddWaterMark(tem_strOriImg);
	}

	//�ж��Ƿ���Ҫ��ֵ******************************************************************
	/*2��ͼ��ߴ��ֵ��Ч�ʽϵͣ�����Ч�ʿɵ������㣬��ֵ�����кϲ�*/
	if (m_nLastRes==m_nInterpolateReso)
	{
		Self_InterPolateImage(tem_strOriImg, tem_strOriImg, 0);
	}
	
	//���ƻ��ʽת��********************************************************************
	if (m_nLastImgType>=0 && m_nLastImgType<4)
	{
		//��ͨͼ�񡪡����Ƶ�ָ��Ŀ¼
		CopyFile(tem_strOriImg, tem_strFilePath, FALSE);
	}
	else if(m_nLastImgType==4)
	{
		//pdf���ա�������pdf�ļ�
		Self_GetPdfFromImg(tem_strOriImg, tem_strFilePath);	
	}
	else if(m_nLastImgType==5)
	{
		//dcm���ա�������dcm�ļ�
		char*  tem_cName  = NULL;
		char*  tem_cId    = NULL;
		char*  tem_cBirth = NULL;
		char*  tem_cSex   = NULL;
		char*  tem_cDName = NULL;
		char*  tem_cDate  = NULL;
		char*  tem_cTime  = NULL;

		IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
		tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

		USES_CONVERSION;  
		char*   tem_cSrc = T2A(tem_strOriImg);
		char*   tem_cDst = T2A(tem_strFilePath);
		tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);	
	}

	//ɾ������**************************************************************************
	DeleteFile(tem_strOriImg);
	
	//�����ļ�vector********************************************************************
	m_vcFilePath.push_back(tem_strFilePath);

	//��ʾͼ����Ϣ�����¼���*************************************************************
	Self_ShowImgInfo(tem_strFilePath);
	m_nImageCount++;

	//�ָ���������ֵ*********************************************************************
//	int    tem_nRecover = -m_nHDRLight;
	AdjustRelay(m_nLastRelay, m_nHDRLight);
	//�ָ�����ͷ�ҽ�*********************************************************************
	if (m_nLastGray != m_nHDRGray)
	{
		m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
		m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	}
	
	if (m_nLastBackLight != m_nHDRBackLgt)
	{
		m_conVideoCtrl.SetBacklightCom(m_nLastBackLight, 0);
	}
}


void CXRayViewerv10Dlg::Self_AddWaterMark(CString imgpath)
{
	//1����ȡˮӡ��ʽ��Ϣ
	int       tem_nSite;
	int       tem_nOffSetX;   //ˮӡ����
	int       tem_nOffSetY; 
	int       tem_nSize   = Self_GetFontSize(m_nWaterSize);
	int       tem_nStrWidth;
	CString   tem_strFont = Self_GetFontName(m_nWaterFont);
	CString   tem_strInfo = _T("");

	CxImage*  tem_pImage;
	tem_pImage = new CxImage;
	tem_pImage->Load(imgpath, CMAX_IMAGE_FORMATS);
	tem_pImage->IncreaseBpp(24);

	CxImage::CXTEXTINFO WMTxtInfo;                  // ��Ȩ����ˮӡ
	tem_pImage->InitTextInfo( &WMTxtInfo );
	_stprintf(WMTxtInfo.lfont.lfFaceName, tem_strFont);
	WMTxtInfo.lfont.lfCharSet = GB2312_CHARSET;
	WMTxtInfo.lfont.lfHeight = tem_nSize;
//	WMTxtInfo.lfont.lfWeight = 20;
	WMTxtInfo.lfont.lfItalic = 0;
	WMTxtInfo.lfont.lfUnderline = 0;


	int      tem_nFind;
	CString  tem_strRead;
	CString  tem_strSinColor[3];
	CString  tem_strWaterColor = m_strWaterColor;
	tem_nFind = tem_strWaterColor.Find('|');
	int i=0;
	while (tem_nFind != -1)
	{
		tem_strRead = tem_strWaterColor.Mid(0, tem_nFind);
		tem_strSinColor[i]= tem_strRead;
		tem_strWaterColor = tem_strWaterColor.Mid(tem_nFind+1);
		tem_nFind  = tem_strWaterColor.Find('|');
		i++;
	}
	m_nRedValue   = _ttoi(tem_strSinColor[0]);
	m_nGreenValue = _ttoi(tem_strSinColor[1]);
	m_nBlueValue  = _ttoi(tem_strSinColor[2]);
	WMTxtInfo.fcolor = RGB(m_nRedValue, m_nGreenValue, m_nBlueValue);
	WMTxtInfo.opaque = 0;                        //����
	WMTxtInfo.b_opacity = (float)(1);            //͸����
	WMTxtInfo.b_round = (BYTE)10;
	
	
	if (m_nWaterMode == 1)
	{
		//ʱ��ˮӡ
		tem_strInfo = Self_GetTimeInfo();
	} 
	else
	{
		//����ˮӡ
		tem_strInfo = m_strWaterInfo;
	}
	
	//��ȡˮӡ�ı������سߴ�
	tem_nStrWidth = Self_GetFontWidth(WMTxtInfo.lfont, tem_strInfo);

	if (tem_strFont == _T("Arial"))
	{
		//Arial
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/12);   //15ʱ���ĸպã���Ӣ�����
	}
	else if (tem_strFont == _T("Calibri"))
	{
		//Calibri
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/4);    //10ʱ���ĸպã���Ӣ�Ļ��
	}
	else if (tem_strFont == _T("Times New Roman"))
	{
		//Times
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/7);
	}
	else if (tem_strFont == _T("����"))
	{
		//����
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/11);
	}
	else 
	{
		//���塢���塢���Ρ����塢�źڡ�����
		tem_nStrWidth = tem_nStrWidth/2;
	}


	/*
	CDC*    tem_pDC = GetDC();
	CSize   tem_szSize;

	CFont   tem_ftFont;
	tem_ftFont.CreatePointFont(120, _T("����"));
	CFont*  tem_ftOld = tem_pDC->SelectObject(&tem_ftFont);
	tem_szSize = tem_pDC->GetTextExtent(_T("�����Ϲ�ͼ��ϵͳ���޹�˾"));
	tem_nStrWidth = tem_szSize.cx;
	tem_pDC->SelectObject(&tem_ftOld);
	*/
	

	if (m_nWaterSite == 0)
	{
		//���Ͻ�
		tem_nOffSetX = 0;
		tem_nOffSetY = tem_nSize;
	}
	else if (m_nWaterSite == 1)
	{
		//���½�
		tem_nOffSetX = 0;
		tem_nOffSetY = tem_pImage->GetHeight();
	}
	else if (m_nWaterSite == 2)
	{
		//���Ͻ�
//		tem_nOffSetX = tem_pImage->GetWidth()-tem_nStrWidth;
		tem_nOffSetX = tem_pImage->GetWidth()-tem_nStrWidth;
		tem_nOffSetY = tem_nSize;
	}
	else if (m_nWaterSite == 3)
	{
		//���½�
//		tem_nOffSetX = tem_pImage->GetWidth()-100;
		tem_nOffSetX = tem_pImage->GetWidth()-tem_nStrWidth;
		tem_nOffSetY = tem_pImage->GetHeight();
	}
	else
	{
		//����
		tem_nOffSetX = tem_pImage->GetWidth()/2;
		tem_nOffSetY = tem_pImage->GetHeight()/2;
	}
	
	_stprintf(WMTxtInfo.text, tem_strInfo);
	tem_pImage->DrawStringEx(0, tem_nOffSetX, tem_nOffSetY, &WMTxtInfo);

	//���ݺ�׺�ж��ļ�����
	CString     tem_strFormat;
	tem_strFormat = PathFindExtension(imgpath);
	tem_strFormat.MakeLower();
	if (tem_strFormat==_T(".bmp"))
	{
		tem_pImage->Save(imgpath, CXIMAGE_FORMAT_BMP);
	}
	else if (tem_strFormat==_T(".jpg"))
	{
		tem_pImage->Save(imgpath, CXIMAGE_FORMAT_JPG);
	}
	else if (tem_strFormat==_T(".png"))
	{
		tem_pImage->Save(imgpath, CXIMAGE_FORMAT_PNG);
	}
	else if (tem_strFormat==_T(".tif"))
	{
		tem_pImage->Save(imgpath, CXIMAGE_FORMAT_TIF);
	}
	delete tem_pImage;


	/*
	_tcscpy( WMTxtInfo.text, m_strWaterInfo);
    _tcscpy(WMTxtInfo.lfont.lfFaceName, m_strWaterFont);
	WMTxtInfo.lfont.lfHeight = m_nWaterSize;
	WMTxtInfo.lfont.lfItalic = TRUE;
	//����m_strWaterColor
	int      tem_nRed          = 0;
	int      tem_nGreen        = 0;
	int      tem_nBlue         = 0;
	int      tem_nFind         = -1;
	CString  tem_strRead;
	CString  tem_strSinColor[3];
	CString  tem_strWaterColor = m_strWaterColor;
	tem_nFind = tem_strWaterColor.Find('|');
	int i=0;
	while (tem_nFind != -1)
	{
		tem_strRead = tem_strWaterColor.Mid(0, tem_nFind);
		tem_strSinColor[i]= tem_strRead;
		tem_strWaterColor = tem_strWaterColor.Mid(tem_nFind+1);
		tem_nFind  = tem_strWaterColor.Find('|');
		i++;
	}
	tem_nRed   = _ttoi(tem_strSinColor[0]);
	tem_nGreen = _ttoi(tem_strSinColor[1]);
	tem_nBlue  = _ttoi(tem_strSinColor[2]);
	WMTxtInfo.fcolor = RGB(tem_nRed, tem_nGreen, tem_nBlue);
	WMTxtInfo.opaque = FALSE;  // No background
	
	tem_pImage->DrawStringEx(0, tem_pImage->GetWidth()/3, tem_pImage->GetHeight()/3, &WMTxtInfo);
	tem_pImage->Save(imgpath, CXIMAGE_FORMAT_JPG);
	*/
	
	
}


int CXRayViewerv10Dlg::Self_GetFontWidth(LOGFONT text, CString textinfo)
{
	CFont     tem_fontInput;
	LOGFONT   tem_fontInfo;

	memset(&tem_fontInfo, 0, sizeof(LOGFONT));
	tem_fontInfo.lfHeight = text.lfHeight;
	_stprintf(tem_fontInfo.lfFaceName, text.lfFaceName);
	VERIFY(tem_fontInput.CreateFontIndirect(&tem_fontInfo));

	CClientDC  tem_dc(this);
	CFont* def_font = tem_dc.SelectObject(&tem_fontInput);
//	CSize  sztext = tem_dc.GetTextExtent(textinfo.GetBuffer(textinfo.GetLength()), wcslen(textinfo.GetBuffer(textinfo.GetLength())));
	CSize  sztext = tem_dc.GetTextExtent(textinfo);
	int    tem_nStrLength = sztext.cx;
//	int tem_nStrLength = _tcslen(textinfo);         //�ַ��ַ����ַ�����
//	int width = sztext.cx/_tcslen(_T("hello"));     //�����ַ�ƽ������

// 	TEXTMETRIC tem_tm;
// 	tem_dc.GetTextMetrics(&tem_tm);
// 	int  tem_Width = tem_tm.tmAveCharWidth;


	tem_dc.SelectObject(def_font);
	tem_fontInput.DeleteObject();

	
	

	return tem_nStrLength;
}


int CXRayViewerv10Dlg::Self_GetFontSize(int index)
{
	int tem_nFontSize = 0;
	switch (index)
	{
	case 0:
		tem_nFontSize = 10;
		break;
	case 1:
		tem_nFontSize = 20;
		break;
	case 2:
		tem_nFontSize = 30;
		break;
	case 3:
		tem_nFontSize = 40;
		break;
	case 4:
		tem_nFontSize = 50;
		break;
	case 5:
		tem_nFontSize = 70;
		break;
	case 6:
		tem_nFontSize = 90;
		break;
	case 7:
		tem_nFontSize = 120;
		break;
	case 8:
		tem_nFontSize = 150;
		break;
	case 9:
		tem_nFontSize = 200;
		break;
	default:
		tem_nFontSize = 20;
		break;
	}
	return tem_nFontSize;
}


CString CXRayViewerv10Dlg::Self_GetFontName(int index)
{
	CString   tem_strFontName = _T("");
	switch(index)
	{
	case 0:
		tem_strFontName = _T("Arial");
		break;
	case 1:
		tem_strFontName = _T("Calibri");
		break;
	case 2:
		tem_strFontName = _T("Times New Roman");
		break;
	case 3:
		tem_strFontName = _T("����");
		break;
	case 4:
		tem_strFontName = _T("����");
		break;
	case 5:
		tem_strFontName = _T("����");
		break;
	case 6:
		tem_strFontName = _T("����");
		break;
	case 7:
		tem_strFontName = _T("����");
		break;
	case 8:
		tem_strFontName = _T("΢���ź�");
		break;
	case 9:
		tem_strFontName = _T("������");
		break;
	default:
		tem_strFontName = _T("����");
		break;
	}
	return tem_strFontName;
}


CString CXRayViewerv10Dlg::Self_GetTimeInfo(void)
{
	SYSTEMTIME   tem_stDateTime;
	CString      tem_strDate = _T("");
	CString      tem_strTime = _T("");
	CString      tem_strTimeName  = _T("");       //ʱ������

	GetLocalTime(&tem_stDateTime);
	tem_strDate.Format(_T("%d-%02d-%02d "), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
	tem_strTime.Format(_T("%02d:%02d:%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond);

	tem_strTimeName  = tem_strDate;
	tem_strTimeName += tem_strTime;

	return tem_strTimeName;
}


CString CXRayViewerv10Dlg::Self_NamingFile(int count)
{
	int       tem_nOffset      = count;
	int       tem_nOffset1     = count+1;

	CString   tem_strCount     = _T("");
	CString   tem_strBegin     = _T("");

	SYSTEMTIME   tem_stDateTime;
	CString      tem_strDate = _T("");
	CString      tem_strTime = _T("");
	CString      tem_strDivide = _T("");


	CString   tem_strOrderName = _T("IMG_");   //��������
	CString   tem_strTimeName  = _T("");       //ʱ������
	CString   tem_strCustomName= _T("");       //�Զ�����
	CString   tem_strValue     = _T("");       //д�������ļ�

	CString   tem_strNewName   = _T("");       //��������

	switch(m_nNameMode)
	{
	case 0:
		//��������
		tem_nOffset += m_nNameBegin2;
		//�ѵ�ǰ�ļ���ֵд��ini�����ļ�
		tem_strValue.Format(_T("%d"), tem_nOffset+1);
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin2"), tem_strValue, m_strIniPath);
		tem_strCount.Format(_T("%04d"), tem_nOffset);
		tem_strOrderName += tem_strCount;
		tem_strNewName    = tem_strOrderName;
		
		
		/*
		tem_strCount.Format(_T("%04d"), tem_nOffset1);
		tem_strOrderName += tem_strCount;
		tem_strNewName    = tem_strOrderName;
		*/
		break;
	case 1:
		//ʱ������
		GetLocalTime(&tem_stDateTime);
		
		if (m_nNameDate == 0)
		{
			tem_strDate.Format(_T("%d%02d%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		} 
		else if (m_nNameDate == 1)
		{
			tem_strDate.Format(_T("%d.%02d.%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		} 
		else if (m_nNameDate == 2)
		{
			tem_strDate.Format(_T("%d-%02d-%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		} 
		else if (m_nNameDate == 3)
		{
			tem_strDate.Format(_T("%d_%02d_%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		} 
		else
		{
			tem_strDate.Format(_T("%d%02d%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
		}

		//���뱣��ǰ��λ
		tem_stDateTime.wMilliseconds = (unsigned short)tem_stDateTime.wMilliseconds/10;
		if (m_nNameTime == 0)
		{
			tem_strTime.Format(_T("%02d%02d%02d%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		} 
		else if (m_nNameTime == 1)
		{
			tem_strTime.Format(_T("%02d.%02d.%02d.%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		} 
		else if (m_nNameTime == 2)
		{
			tem_strTime.Format(_T("%02d-%02d-%02d-%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		} 
		else if (m_nNameTime == 3)
		{
			tem_strTime.Format(_T("%02d_%02d_%02d_%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		} 
		else
		{
			tem_strTime.Format(_T("%02d%02d%02d%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds);
		}
		tem_strTimeName  = tem_strDate;
		tem_strTimeName += m_strNameDivide;
		tem_strTimeName += tem_strTime;
		tem_strNewName   = tem_strTimeName;

		break;
	case 2:
		//�Զ�������

		tem_nOffset += m_nNameBegin;
		//�ѵ�ǰ�ļ���ֵд��ini�����ļ�
		tem_strValue.Format(_T("%d"), tem_nOffset+1);
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin"), tem_strValue, m_strIniPath);

		tem_strBegin.Format(_T("%04d"), tem_nOffset);
		tem_strCustomName  = m_strNamePre1;
		tem_strCustomName += m_strNamePre2;
		tem_strCustomName += m_strNamePre3;
		tem_strCustomName += tem_strBegin;
		tem_strNewName     = tem_strCustomName;
		break;
	default:
		tem_strCount.Format(_T("%04d"), count);
		tem_strOrderName += tem_strCount;
		tem_strNewName    = tem_strOrderName;
		break;
	}

	return tem_strNewName;
}


void CXRayViewerv10Dlg::Self_ReadNameRule(void)
{
	if (IDOK == m_dlgNameSet.DoModal())
	{
		//�ض������ļ�
		int     tem_nRead   = 0;
		CString tem_strRead = _T("");
		::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("û���ҵ�NameMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameMode = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("û���ҵ�NameDate��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameDate   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("û���ҵ�NameTime��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameTime   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("û���ҵ�NameDivide��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNameDivide = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("û���ҵ�NamePre1��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre1 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("û���ҵ�NamePre2��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre2 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("û���ҵ�NamePre3��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre3 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("û���ҵ�NameBegin��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameBegin   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("û���ҵ�NameBegin2��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameBegin2   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		m_nImageCount = 0;
	}
	
}


CString CXRayViewerv10Dlg::Self_CreateThumb(CString srcimg, CString dstimg)
{
	
	CString   tem_strSrcImg = srcimg;
	CString   tem_strDstImg = dstimg;

	int       tem_nImageType=GetTypeFromFileName(tem_strSrcImg);
	if(tem_nImageType==CXIMAGE_FORMAT_UNKNOWN)
	{
		return tem_strSrcImg;
	}
	CxImage*  tem_pImage;
	tem_pImage = new CxImage;
	tem_pImage->Load(tem_strSrcImg, tem_nImageType);
	if(tem_pImage->IsValid()==false)
	{
		return tem_strSrcImg;
	}
	if (tem_pImage->GetBpp()==1)
	{
		tem_pImage->IncreaseBpp(24);
	}
	int   cx = 160;
	int   cy = (int)160*tem_pImage->GetHeight()/tem_pImage->GetWidth();
	tem_pImage->Resample(cx, cy, 1, NULL);
	tem_pImage->Save(tem_strDstImg, CXIMAGE_FORMAT_JPG);

	delete tem_pImage;
	return tem_strDstImg;
}


int CXRayViewerv10Dlg::GetTypeFromFileName(LPCTSTR pstr)
{
	CString fileName(pstr);
	CString ext3=fileName.Right(3);
	CString ext4=fileName.Right(4);
#if CXIMAGE_SUPPORT_BMP
	if(ext3.CompareNoCase(_T("bmp"))==0)
		return CXIMAGE_FORMAT_BMP;
#endif

#if CXIMAGE_SUPPORT_GIF
	if(ext3.CompareNoCase(_T("gif"))==0)
		return CXIMAGE_FORMAT_GIF;
#endif

#if CXIMAGE_SUPPORT_JPG
	if(ext3.CompareNoCase(_T("jpg"))==0 || ext4.CompareNoCase(_T("jpeg"))==0)
		return CXIMAGE_FORMAT_JPG;
#endif

#if CXIMAGE_SUPPORT_PNG
	if(ext3.CompareNoCase(_T("png"))==0)
		return CXIMAGE_FORMAT_PNG;
#endif

#if CXIMAGE_SUPPORT_MNG
	if(ext3.CompareNoCase(_T("mng"))==0 || ext3.CompareNoCase(_T("jng"))==0 ||ext3.CompareNoCase(_T("png"))==0)
		return CXIMAGE_FORMAT_MNG;
#endif

#if CXIMAGE_SUPPORT_ICO
	if(ext3.CompareNoCase(_T("ico"))==0)
		return CXIMAGE_FORMAT_ICO;
#endif

#if CXIMAGE_SUPPORT_TIF
	if(ext3.CompareNoCase(_T("tif"))==0 || ext4.CompareNoCase(_T("tiff"))==0)
		return CXIMAGE_FORMAT_TIF;
#endif

#if CXIMAGE_SUPPORT_TGA
	if(ext3.CompareNoCase(_T("tga"))==0)
		return CXIMAGE_FORMAT_TGA;
#endif

#if CXIMAGE_SUPPORT_PCX
	if(ext3.CompareNoCase(_T("pcx"))==0)
		return CXIMAGE_FORMAT_PCX;
#endif

#if CXIMAGE_SUPPORT_WBMP
	if(ext4.CompareNoCase(_T("wbmp"))==0)
		return CXIMAGE_FORMAT_WBMP;
#endif

#if CXIMAGE_SUPPORT_WMF
	if(ext3.CompareNoCase(_T("wmf"))==0 || ext3.CompareNoCase(_T("emf"))==0)
		return CXIMAGE_FORMAT_WMF;
#endif

#if CXIMAGE_SUPPORT_J2K
	if(ext3.CompareNoCase(_T("j2k"))==0 || ext3.CompareNoCase(_T("jp2"))==0)
		return CXIMAGE_FORMAT_J2K;
#endif

#if CXIMAGE_SUPPORT_JBG
	if(ext3.CompareNoCase(_T("jbg"))==0)
		return CXIMAGE_FORMAT_JBG;
#endif

#if CXIMAGE_SUPPORT_JP2
	if(ext3.CompareNoCase(_T("j2k"))==0 || ext3.CompareNoCase(_T("jp2"))==0)
		return CXIMAGE_FORMAT_JP2;
#endif

#if CXIMAGE_SUPPORT_JPC
	if(ext3.CompareNoCase(_T("j2c"))==0 || ext3.CompareNoCase(_T("jpc"))==0)
		return CXIMAGE_FORMAT_JPC;
#endif

#if CXIMAGE_SUPPORT_PGX
	if(ext3.CompareNoCase(_T("pgx"))==0)
		return CXIMAGE_FORMAT_PGX;
#endif

#if CXIMAGE_SUPPORT_PNM
	if(ext3.CompareNoCase(_T("pnm"))==0 || ext3.CompareNoCase(_T("pgm"))==0 || ext3.CompareNoCase(_T("ppm"))==0)
		return CXIMAGE_FORMAT_PNM;
#endif

#if CXIMAGE_SUPPORT_RAS
	if(ext3.CompareNoCase(_T("ras"))==0)
		return CXIMAGE_FORMAT_RAS;
#endif

	return CXIMAGE_FORMAT_UNKNOWN;
}


BOOL CXRayViewerv10Dlg::ThumbaiList(int thumbwidth, int thumbheight)
{
	int          m_nImageIndex= 0;
	DWORD  dwStyle;
	//CImageList��ʼ��
	m_imagelist.Create(thumbwidth,thumbheight,ILC_COLOR24,0,1);

	//ListCtrl��ʼ��
	dwStyle = m_conListCtrl.GetExtendedStyle();
	dwStyle=dwStyle|LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_AUTOARRANGE;
	m_conListCtrl.SetExtendedStyle(dwStyle);
	m_conListCtrl.SetImageList(&m_imagelist,LVSIL_NORMAL);
	for(int i=0;i<m_imagelist.GetImageCount();i++)
	{
		m_imagelist.Remove(i);
	}
	m_conListCtrl.DeleteAllItems();
	m_imagelist.SetImageCount(m_vcImgName.size()); 

	wchar_t path[MAX_PATH]; 
	std::vector<CString>::iterator iter1;
	std::vector<CString>::iterator iter2;
	m_conListCtrl.SetRedraw(false);
	m_nImageIndex = 0;
	m_conListCtrl.SetTextBkColor(RGB(72,77,91));
	m_conListCtrl.SetTextColor(RGB(255, 255, 255));
	for(iter1=m_vcImgName.begin();iter1!=m_vcImgName.end();iter1++,m_nImageIndex++)
	{
		m_conListCtrl.InsertItem(m_nImageIndex,*iter1,m_nImageIndex);
	}
	m_conListCtrl.SetRedraw(true);
	m_conListCtrl.Invalidate();

	HBRUSH hBrushBorder    =::CreateSolidBrush(RGB(220,220,220));
	HBRUSH hBrushBkground  =::CreateSolidBrush(RGB(255,255,255));



	RECT rcBorder;
	rcBorder.left=rcBorder.top  =0;
	rcBorder.right              =thumbwidth;
	rcBorder.bottom             =thumbheight;

	float fRatio=(float)thumbheight/thumbwidth; 

	int XDest,YDest,nDestWidth,nDestHeight;
	m_nImageIndex=0;

	for(iter2=m_vcThumbPath.begin();iter2!=m_vcThumbPath.end();iter2++,m_nImageIndex++)
	{
		_stprintf(path,*iter2);
		int nImageType=GetTypeFromFileName(path);
		if(nImageType==CXIMAGE_FORMAT_UNKNOWN)
			continue;
		CxImage image;
		image.Load(path, nImageType);
		if(image.IsValid()==false)
			continue;
		float fImgRatio=(float)image.GetHeight()/image.GetWidth();  
		if(fImgRatio>fRatio)
		{
			nDestWidth=(int)thumbheight/fImgRatio;   
			XDest=(thumbwidth-nDestWidth)/2;
			YDest=0;
			nDestHeight=thumbheight;
		}
		else
		{
			XDest=0;
			nDestWidth=thumbwidth;
			nDestHeight=(int)thumbwidth*fImgRatio;  
			YDest=(thumbheight-nDestHeight)/2;
		}

		CClientDC cdc(this);
		HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
		HBITMAP bm=CreateCompatibleBitmap(cdc.m_hDC,thumbwidth,thumbheight);
		HBITMAP pOldBitmapImage=(HBITMAP)SelectObject(hDC,bm);

		::FillRect(hDC,&rcBorder,hBrushBkground);
		image.Stretch(hDC,XDest,YDest,nDestWidth,nDestHeight);
		::FrameRect(hDC,&rcBorder,hBrushBorder);
		SelectObject(hDC,pOldBitmapImage);
		CBitmap bitmap;
		bitmap.Attach(bm);
		m_imagelist.Replace(m_nImageIndex,&bitmap,NULL);
		m_conListCtrl.RedrawItems(m_nImageIndex,m_nImageIndex);

		DeleteDC(hDC);
		DeleteObject(bm);
	}
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBkground);
	int tem_nCount = m_conListCtrl.GetItemCount();
	if (tem_nCount>0)
	{

		m_conListCtrl.EnsureVisible(tem_nCount-1, FALSE);
	}
	m_conListCtrl.Invalidate();

	return TRUE;
}


CString CXRayViewerv10Dlg::Self_GetImgFromPDF(CString pdfpath, CString dstpath)
{
	CString     tem_strImagePath = dstpath;        //ͼ�񵼳�·��
	CString     tem_strResolution= _T("50");               //ͼ��ֱ���
	CString     tem_strDllPath   = _T("gsdll32.dll");

	int len = WideCharToMultiByte(CP_ACP, 0, pdfpath, -1, NULL, 0, NULL, NULL);
	char*   tem_cPDFFile = new char[len+1];    //����PDF·��+��
	WideCharToMultiByte(CP_ACP, 0, pdfpath, -1, tem_cPDFFile, len, NULL, NULL);


	len = WideCharToMultiByte(CP_ACP, 0, tem_strImagePath, -1, NULL, 0, NULL, NULL);
	char*   tem_cImage = new char[len+1];       //����ͼ��·��+��
	WideCharToMultiByte(CP_ACP, 0, tem_strImagePath, -1, tem_cImage, len, NULL, NULL);

	len = WideCharToMultiByte(CP_ACP, 0, tem_strResolution, -1, NULL, 0, NULL, NULL);
	char*   tem_cRes = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, tem_strResolution, -1, tem_cRes, len, NULL, NULL);

	len = WideCharToMultiByte(CP_ACP, 0, tem_strDllPath, -1, NULL, 0, NULL, NULL);
	char*   tem_cDll = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, tem_strDllPath, -1, tem_cDll, len, NULL, NULL);


	GhostPdf2Image(tem_cPDFFile, tem_cImage, tem_cRes, tem_cDll); //����PDF·���� ���ͼ��·���� �ֱ��ʣ� dll·��

	delete[] tem_cPDFFile;
	delete[] tem_cImage;
	delete[] tem_cRes;
	delete[] tem_cDll;

	return tem_strImagePath;
}


CString CXRayViewerv10Dlg::Self_GetPDFFromImg(CString imgpath, CString pdfpath)
{
	CString   tem_strInputPath  = imgpath;     //����ͼ��·��
	CString   tem_strOutputPath = pdfpath;     //����PDF·��


	//����PDF--------
	int       doc, page, image, code, pagenum=2;
	wstring    outfile;
	outfile = tem_strOutputPath.GetBuffer(0);
	tem_strOutputPath.ReleaseBuffer();
	PDFlib*    pPdf;
	pPdf = new PDFlib;
	try
	{
		//		pPdf->set_parameter("License", "w700602-009100-731090-Y6WPH2-5SE4A2");
		pPdf->set_parameter(_T("nodemostamp"), _T("false"));
		pPdf->set_parameter(_T("errorpolicy"), _T("return"));
		//		pPdf->set_parameter(_T("hypertextencoding"), _T("host"));

		code = pPdf->begin_document(outfile, _T(""));
		if (code == -1)
		{
			return tem_strInputPath;
		}
		//����PDF������Ϣ******************************************************
		pPdf->set_info(_T("Creator"), _T("SmartScan"));   
		pPdf->set_info(_T("Author"), _T("UDS"));   
		pPdf->set_info(_T("Title"), _T("UDSPDF")); 
		pPdf->set_info(_T("Subject"), _T("ɨ���ĵ�"));

		//ͼƬ����***********************************************************
		{

			wstring sFilePath(tem_strInputPath.GetBuffer());
			image = pPdf->load_image(_T("auto"), sFilePath, _T(""));
			pPdf->begin_page_ext(10, 10, _T(""));
			pPdf->fit_image(image, 0, 0, _T("adjustpage dpi=0"));  //����ͼ��
			pPdf->close_image(image);
			pPdf->end_page_ext(_T(""));
		}		
		pPdf->end_document(_T(""));	
	}
	catch (PDFlib::Exception e)
	{
		int     num=-1;
		wstring  str;
		CString str2, str3;
		str = e.get_errmsg();
		num = e.get_errnum();
		str2 = str.c_str();
		str3.Format(_T("%d"), num);
	}

	return tem_strOutputPath;
}


BOOL CXRayViewerv10Dlg::GhostPdf2Image(char* pdfpath, char* imgpath, char* resolution, char* gsdll)
{
	
	CString tem_strDllPath(gsdll);
	HMODULE hModule = LoadLibrary(tem_strDllPath);
	if (!hModule)
	{
		return FALSE;
	}

	if (!resolution)
	{
		char cResolution[8] = "50x50";
		resolution = cResolution;
	}	

	// *** Declare all the dynamic typedef function pointers
	typedef int (WINAPI *gsapi_new_instance)( char **, int );
	gsapi_new_instance lp_gsapi_new_instance ;
	lp_gsapi_new_instance = (gsapi_new_instance) GetProcAddress(hModule,"gsapi_new_instance");

	typedef int (WINAPI *gsapi_delete_instance) (char *);
	gsapi_delete_instance lp_gsapi_delete_instance;
	lp_gsapi_delete_instance = (gsapi_delete_instance) GetProcAddress(hModule,"gsapi_delete_instance");

	typedef int (WINAPI *gsapi_init_with_args) (char *,int,char *);
	gsapi_init_with_args lp_gsapi_init_with_args;
	lp_gsapi_init_with_args = (gsapi_init_with_args) GetProcAddress(hModule,"gsapi_init_with_args");

	typedef int (WINAPI *gsapi_exit) (char *);
	gsapi_exit lp_gsapi_exit;
	lp_gsapi_exit = (gsapi_exit) GetProcAddress(hModule,"gsapi_exit");

	char ArgResolution[80] = "-r";
	strcat(ArgResolution,resolution);

	char ArgOutputFile[MAX_PATH + 16] = "-sOutputFile=";
	strcat(ArgOutputFile,imgpath);

	const char * gsargv[10];
	int gsargc;
	gsargv[0] = "-dNOPAUSE";  // no prompts
	gsargv[1] = "-dBATCH";    // exit after processing
	gsargv[2] = "-dSAFER";    // Safe mode
	gsargv[3] = ArgResolution;
	gsargv[4] ="-dNOTRANSPARENCY";
	gsargv[5] = "-sDEVICE=jpeg"; 
	gsargv[6] = "-dAdjustWidth=0";
	gsargv[7] = "-dMaxStripSize=999999999";
	gsargv[8] = ArgOutputFile;
	gsargv[9] = pdfpath;
	gsargc=10;

	char *Inst = NULL;
	int code = 0;

	code = (lp_gsapi_new_instance)(&Inst,NULL);
	if (code == 0)
	{
		// Do the conversion
		code = (lp_gsapi_init_with_args) (Inst,gsargc,(char *) gsargv );
		if (code == 0)
			code = (lp_gsapi_exit) (Inst);

		// *** Release the handle
		(lp_gsapi_delete_instance) (Inst);
	}
	if (hModule)
		FreeLibrary(hModule);

	if (code == 0)
		return TRUE;
		
	return FALSE;
}


void CXRayViewerv10Dlg::OnDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int  tem_nListIndex = pNMItemActivate->iItem;
	if (tem_nListIndex>=0 && tem_nListIndex<m_conListCtrl.GetItemCount())
	{
		CString   tem_strSlcPath = m_vcFilePath[tem_nListIndex];
		ShellExecute(NULL, _T("open"), tem_strSlcPath, NULL, NULL, SW_SHOWNORMAL);
	}

	*pResult = 0;
}


void CXRayViewerv10Dlg::OnRclickListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_nRSlcIndex = pNMItemActivate->iItem;
	if (m_nRSlcIndex>=0 && m_nRSlcIndex<m_conListCtrl.GetItemCount())
	{
		CPoint  tem_ptRight;
		GetCursorPos(&tem_ptRight);
		CMenu*    pPopup = m_ListMenu.GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN, tem_ptRight.x, tem_ptRight.y, this);
	}
	
	*pResult = 0;
}


void CXRayViewerv10Dlg::On32771Delete()
{
	// TODO: �ڴ�����������������
	if (m_vcFilePath.size()==0)
	{
		return;
	}
	//ɾ��ָ���ļ�
	SHFILEOPSTRUCT FileOp;
	BOOL           m_BRC;    //ReturnCode����������
	CString        strSrcPath;
	//ɾ��������վ
	strSrcPath  = m_vcFilePath[m_nRSlcIndex];
	strSrcPath += '\0';
	CString  tem_strDstPath;
	tem_strDstPath = '\0';     //ɾ��������ֱ����ΪNULL
	CString     tem_strTitle;
	tem_strTitle = _T("����ɾ��...");
	tem_strTitle += '\0';
	FileOp.fFlags = FOF_ALLOWUNDO|FOF_MULTIDESTFILES|FOF_SIMPLEPROGRESS|FOF_NOCONFIRMATION;
	FileOp.lpszProgressTitle = tem_strTitle;
	FileOp.hwnd              = m_hWnd;
	FileOp.hNameMappings     = NULL;
	FileOp.pFrom             = strSrcPath;
	FileOp.pTo               = tem_strDstPath;    //Ŀ��Ŀ¼
	FileOp.wFunc             = FO_DELETE;

	//������ʾ--------------------------------------------------
	m_BRC = SHFileOperation(&FileOp);
	if (!FileOp.fAnyOperationsAborted)
	{
		if(m_BRC)   
		{
			//�������ִ���
		}		
	}
	else
	{
		//����������ֹ
	}
	CString   tem_strThumbPath = m_vcThumbPath[m_nRSlcIndex];
	DeleteFile(tem_strThumbPath);
	m_vcImgName.erase(m_vcImgName.begin()+m_nRSlcIndex);
	m_vcThumbPath.erase(m_vcThumbPath.begin()+m_nRSlcIndex);
	m_vcFilePath.erase(m_vcFilePath.begin()+m_nRSlcIndex);
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	//�������ͼ�������棬ɾ��ͼ��Ҫ���PicCtrl��ʾ
	if (m_BShowPicCtrl)
	{
		Self_ClearPicCtrl();
		m_cvSrcImage.release();
		m_cvDstImage.release();
		m_cvLastImg.release();
		m_cvNextImg.release();
	}

}


void CXRayViewerv10Dlg::On32772Property()
{
	// TODO: �ڴ�����������������
	CString   tem_strLastFile;
	if (m_vcFilePath.size()==0)
	{
		return;
	}
	tem_strLastFile = m_vcFilePath[m_nRSlcIndex];  //��ȡ

	SHELLEXECUTEINFO   sei; 
	sei.hwnd   =   this->GetSafeHwnd(); 
	sei.lpVerb   =  TEXT( "properties"); 
	sei.lpFile   =   tem_strLastFile; 
	sei.lpDirectory   =   NULL; 
	sei.lpParameters   =  NULL; 
	sei.nShow   =   SW_SHOWNORMAL; 
	sei.fMask   =   SEE_MASK_INVOKEIDLIST ; 
	sei.lpIDList   =   NULL; 
	sei.cbSize   =   sizeof(SHELLEXECUTEINFO); 
	ShellExecuteEx(&sei);
}


void CXRayViewerv10Dlg::Self_EnhenceRelay(void)
{
	int devicehandle;
	usb_relay_init();
	struct usb_relay_device_info *tem_pDeviceList;
	tem_pDeviceList = usb_relay_device_enumerate();
	devicehandle = usb_relay_device_open(tem_pDeviceList);

	usb_relay_device_close_one_relay_channel(devicehandle,1);
	usb_relay_device_close_one_relay_channel(devicehandle,2);

	usb_relay_device_close_one_relay_channel(devicehandle,1);
	usb_relay_device_open_one_relay_channel(devicehandle,2);

	usb_relay_device_open_one_relay_channel(devicehandle,1);
	usb_relay_device_open_one_relay_channel(devicehandle,2);

	usb_relay_device_open_one_relay_channel(devicehandle,1);
	usb_relay_device_close_one_relay_channel(devicehandle,2);

	usb_relay_device_close_one_relay_channel(devicehandle,1);
	usb_relay_device_close_one_relay_channel(devicehandle,2);

	usb_relay_device_close(devicehandle);


}


void CXRayViewerv10Dlg::Self_ReduceRelay(void)
{
	int devicehandle;
	usb_relay_init();
	struct usb_relay_device_info *tem_pDeviceList;
	tem_pDeviceList = usb_relay_device_enumerate();
	devicehandle = usb_relay_device_open(tem_pDeviceList);

	usb_relay_device_close_one_relay_channel(devicehandle,1);
	usb_relay_device_close_one_relay_channel(devicehandle,2);

	usb_relay_device_open_one_relay_channel(devicehandle,1);
	usb_relay_device_close_one_relay_channel(devicehandle,2);

	usb_relay_device_open_one_relay_channel(devicehandle,1);
	usb_relay_device_open_one_relay_channel(devicehandle,2);

	usb_relay_device_close_one_relay_channel(devicehandle,1);
	usb_relay_device_open_one_relay_channel(devicehandle,2);

	usb_relay_device_close_one_relay_channel(devicehandle,1);
	usb_relay_device_close_one_relay_channel(devicehandle,2);
	
	usb_relay_device_close(devicehandle);
	
}


void CXRayViewerv10Dlg::Self_SetRelayZero(void)
{
	int tem_nDeviceHandle;
	struct usb_relay_device_info *tem_pDeviceList;
	usb_relay_init();
	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	for (int i=0; i<100; i++)
	{
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
	}

	m_nLastRelay = 0;

	usb_relay_device_close(tem_nDeviceHandle);
}



void CXRayViewerv10Dlg::Self_SetRelay1(void)
{
	int tem_nDeviceHandle;
	struct usb_relay_device_info *tem_pDeviceList;
	usb_relay_init();
	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	for (int i=0; i<100; i++)
	{
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
	}
	//+1
	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
	usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

	usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
	usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

	usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
	usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);



	m_nLastRelay = 1;

	usb_relay_device_close(tem_nDeviceHandle);
}


void CXRayViewerv10Dlg::Self_SetRelay100(void)
{
	int tem_nDeviceHandle;
	struct usb_relay_device_info *tem_pDeviceList;
	usb_relay_init();
	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	for (int i=0; i<100; i++)
	{
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

		usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
		usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
	}

	m_nLastRelay = 100;

	usb_relay_device_close(tem_nDeviceHandle);
}


void CXRayViewerv10Dlg::Self_SetRelayValue(int dstvalue)
{

	int     tem_nDstValue     = dstvalue;
	int     tem_nDeviceHandle = NULL;

	usb_relay_init();
	struct usb_relay_device_info *tem_pDeviceList;

	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

	if (tem_nDstValue>m_nLastRelay)
	{
		//����
		for (int i=0; i<tem_nDstValue-m_nLastRelay; i++)
		{
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		}

	}
	else
	{
		//����
		for (int i=0; i<m_nLastRelay-tem_nDstValue; i++)
		{
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle, 1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle, 2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		}

	}
	m_nLastRelay = dstvalue;
	usb_relay_device_close(tem_nDeviceHandle);
}


int CXRayViewerv10Dlg::Self_GetRelayStatus(void)
{
	int devicehandle;
	usb_relay_init();
	struct usb_relay_device_info *tem_pDeviceList;
	tem_pDeviceList = usb_relay_device_enumerate();
	devicehandle = usb_relay_device_open(tem_pDeviceList);


	usb_relay_device_get_status(devicehandle, &m_nStatus);


	usb_relay_device_close(devicehandle);
	return 0;
}


BEGIN_EVENTSINK_MAP(CXRayViewerv10Dlg, CDialogEx)
	ON_EVENT(CXRayViewerv10Dlg, IDC_UDS_VIDEOCTRL1, 3, CXRayViewerv10Dlg::DeviceChangedUdsVideoctrl1, VTS_BSTR VTS_BSTR)
	ON_EVENT(CXRayViewerv10Dlg, IDC_UDS_VIDEOCTRL1, 4, CXRayViewerv10Dlg::DeviceOpenedUdsVideoctrl1, VTS_BSTR)
END_EVENTSINK_MAP()



void CXRayViewerv10Dlg::DeviceOpenedUdsVideoctrl1(LPCTSTR DevName)
{
	// TODO: �ڴ˴�������Ϣ�����������
	if (m_nViewMode == 0)
	{
		m_conVideoCtrl.ManualImageCrop(TRUE);
	}
	else if (m_nViewMode == 1)
	{
		m_conVideoCtrl.ManualImageCrop(TRUE);
		m_conVideoCtrl.SetMessage(1);
		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conVideoCtrl.SetMessage(0);	
	}
	else if(m_nViewMode == 2)
	{
		m_conVideoCtrl.ManualImageCrop(FALSE);
	}
	else
	{
		m_conVideoCtrl.ManualImageCrop(FALSE);
		m_conVideoCtrl.AdjuestImageCrop(TRUE);
	}
	
}


void CXRayViewerv10Dlg::DeviceChangedUdsVideoctrl1(LPCTSTR changeType, LPCTSTR deviceName)
{
	// TODO: �ڴ˴�������Ϣ�����������
	m_dlgOne.m_conRichEdit.SetSelectionCharFormat(m_dlgOne.m_fontRichEdit);
	m_dlgOne.m_conRichEdit.ReplaceSel(changeType);
	m_dlgOne.m_conRichEdit.ReplaceSel(_T(" - "));
	m_dlgOne.m_conRichEdit.ReplaceSel(deviceName);
	m_dlgOne.m_conRichEdit.ReplaceSel(_T("\n"));
	m_dlgOne.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


void CXRayViewerv10Dlg::Self_ShowImgInfo(CString imgpath)
{
	CString      tem_strFileByte;
//	CString      tem_strImageInfo  = _T("ͼ���С��");
	CString      tem_strImageInfo  = m_vcMainLang[9];
	
	CFile        tem_FileImg;
	ULONGLONG    tem_ullSize;
	
	if (tem_FileImg.Open(imgpath, CFile::modeRead))
	{
		tem_ullSize = tem_FileImg.GetLength();
		if (tem_ullSize>1024)
		{
			//ת��Ϊkb��ʾ
			tem_ullSize = tem_ullSize/1024;
			tem_strFileByte.Format(_T("%I64d"), tem_ullSize);
			tem_strImageInfo += tem_strFileByte;
			tem_strImageInfo += _T("kb");

		}
		else
		{
			//ʹ���ֽڱ�ʾ
			tem_strFileByte.Format(_T("%I64d"), tem_ullSize);
			tem_strImageInfo += tem_strFileByte;
			tem_strImageInfo += _T("b");
		}
	}
	m_dlgOne.m_conRichEdit.SetSelectionCharFormat(m_dlgOne.m_fontRichEdit);
	m_dlgOne.m_conRichEdit.ReplaceSel(tem_strImageInfo);
	m_dlgOne.m_conRichEdit.ReplaceSel(_T("\n"));
	m_dlgOne.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	
}


//ȫ��
//void CXRayViewerv10Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
//	MessageBox(_T("DB"));
//	CPoint   tem_pt;
//	GetCursorPos(&tem_pt);
//	ClientToScreen(&tem_pt);
//	CRect     tem_rc;
//	m_conVideoCtrl.GetWindowRect(&tem_rc);
//	
//	if (tem_rc.PtInRect(tem_pt))
//	{
//		if (m_BFullScreen)
//		{
//			MessageBox(_T("�ָ�"));
//			Self_NormalScreen();
//		} 
//		else
//		{
//			MessageBox(_T("ȫ��"));
//			Self_FullScreen();
//		}
//	}
//
//
//
//	CDialogEx::OnLButtonDblClk(nFlags, point);
//}


void CXRayViewerv10Dlg::OnBnClickedBtnFullscreen()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	/*
	CRect  tem_rcFullScreen;

	tem_rcFullScreen.top    = 0;
	tem_rcFullScreen.left   = 0;
	tem_rcFullScreen.right  = GetSystemMetrics(SM_CXSCREEN);
	tem_rcFullScreen.bottom = GetSystemMetrics(SM_CYSCREEN);

	GetDlgItem(IDC_TAB_CTRL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(&tem_rcFullScreen, TRUE);
	*/
	/*
	//1���жϵ�ǰ�Ƿ�Ϊȫ��
	if (m_BFullScreen)
	{
		return;
	}

	GetWindowPlacement(&m_OldWndPlacement);  
	CRect WindowRect;  
	GetWindowRect(&WindowRect);    
  
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowRect(&m_rcLastOCX);
	
	//��ȡ����������֮��Ŀͻ���λ��  
	CRect ClientRect;  
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);  
	ClientToScreen(&ClientRect);  

	//��ȡ��Ļ�ķֱ���  
	int nFullWidth  = GetSystemMetrics(SM_CXSCREEN);  
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);  
 
	//�Ի���ȫ����ʾ  
	m_FullScreenRect.left = WindowRect.left - ClientRect.left;  
	int m_top = WindowRect.top - ClientRect.top;  
	m_FullScreenRect.top    = m_top;  
	m_FullScreenRect.right  = WindowRect.right - ClientRect.right + nFullWidth;  
	m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + nFullHeight;  
 
	//����ȫ����ʾ  
	m_NewWndPlacement.length           = sizeof(WINDOWPLACEMENT);  
	m_NewWndPlacement.flags            = 0;  
	m_NewWndPlacement.showCmd          = SW_SHOWNORMAL;  
	m_NewWndPlacement.rcNormalPosition = m_FullScreenRect;  
	SetWindowPlacement(&m_NewWndPlacement);  
 	  
	GetDlgItem(IDC_TAB_CTRL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(SW_HIDE); 	 
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(0,0,nFullWidth,nFullHeight);
	Invalidate(); 

	ModifyStyle(SWP_NOSIZE|SWP_NOMOVE, NULL, SWP_DRAWFRAME );
	m_BFullScreen = TRUE;
	*/

	Self_FullScreen();
	m_conVideoCtrl.SetRectValue(0, 0, 0, 0);
}


void CXRayViewerv10Dlg::OnBnClickedBtnLast()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	BOOL  tem_BRC = FALSE;
	if (m_BShowPicCtrl)
	{
		tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
		if(tem_BRC)
		{
			m_fCurRatio+=0.05;
		}
	} 
	else
	{
		m_conVideoCtrl.ZoomIn();
	}
	
}

void CXRayViewerv10Dlg::OnBnClickedBtnNext()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	BOOL  tem_BRC = FALSE;
	if (m_BShowPicCtrl)
	{
		tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
		if(tem_BRC)
		{
			m_fCurRatio-=0.05;
		}
	} 
	else
	{
		m_conVideoCtrl.ZoomOut();
	}
	
	
}


void CXRayViewerv10Dlg::Self_FullScreen(void)
{
	if (m_BFullScreen)
	{
		return;
	}

	int  tem_nScrnWidth  = GetSystemMetrics(SM_CXSCREEN);
	int  tem_nScrnHeight = GetSystemMetrics(SM_CYSCREEN);

	//��ȡ��ǰ�Ĵ��ڵ���ʾ״̬�ʹ���λ�ã�һ���˳�ʱʹ��
	GetWindowPlacement(&m_stcOldWinPlc);
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowPlacement(&m_strOcxWinPlc);

	CRect  tem_rcWholeDlg;
	CRect  tem_rcClient;
	GetWindowRect(&tem_rcWholeDlg);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &tem_rcClient);
	ClientToScreen(&tem_rcClient);
	m_rcFullScreen.left   = tem_rcWholeDlg.left - tem_rcClient.left;
	m_rcFullScreen.top    = tem_rcWholeDlg.top - tem_rcClient.top;
	m_rcFullScreen.right  = tem_rcWholeDlg.right + tem_nScrnWidth - tem_rcClient.right;
	m_rcFullScreen.bottom = tem_rcWholeDlg.bottom + tem_nScrnHeight - tem_rcClient.bottom;

	//���ô��ڶ��������Ϊȫ������׼��������ȫ��״̬ 
	WINDOWPLACEMENT  tem_stcWndpl;  
	tem_stcWndpl.length = sizeof(WINDOWPLACEMENT);  
	tem_stcWndpl.flags = 0;  
	tem_stcWndpl.showCmd = SW_SHOWNORMAL;  
	tem_stcWndpl.rcNormalPosition = m_rcFullScreen;  
	SetWindowPlacement(&tem_stcWndpl);//�ú�������ָ�����ڵ���ʾ״̬����ʾ��Сλ�õȣ������Ǹó�����Ϊ��Ҫ�ĺ���  

	GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(CRect(0, 0, tem_nScrnWidth, tem_nScrnHeight));
	m_BFullScreen = TRUE;  
	GetDlgItem(IDC_TAB_CTRL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(SW_HIDE);
 	GetDlgItem(IDC_BTN_FULLSCREEN)->EnableWindow(FALSE);
// 	GetDlgItem(IDC_BTN_LAST)->EnableWindow(FALSE);
// 	GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);	
}


void CXRayViewerv10Dlg::Self_NormalScreen(void)
{
	if (!m_BFullScreen)
	{
		return;
	}
	
	//�ָ�Ĭ�ϴ���  
	m_BFullScreen = FALSE;
	GetDlgItem(IDC_TAB_CTRL)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(SW_SHOWNORMAL); 
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(&m_rcLastOCX);  
	GetDlgItem(IDC_BTN_FULLSCREEN)->EnableWindow(TRUE);

//	ShowWindow(SW_MAXIMIZE);
	CRect rcWorkArea; 
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0); 
	MoveWindow(&rcWorkArea); 

}


void CXRayViewerv10Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (m_BFullScreen)
	{
		lpMMI->ptMaxSize.x = m_rcFullScreen.Width();  
		lpMMI->ptMaxSize.y = m_rcFullScreen.Height();  
		lpMMI->ptMaxPosition.x = m_rcFullScreen.left;  
		lpMMI->ptMaxPosition.y = m_rcFullScreen.top;  
		lpMMI->ptMaxTrackSize.x = m_rcFullScreen.Width();  
		lpMMI->ptMaxTrackSize.y = m_rcFullScreen.Height();  

	}

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


//��ʾPictureCtrl��������ͼ��
void CXRayViewerv10Dlg::Self_ShowPicCtrl(void)
{
	if (m_vcImgName.size() == 0)
	{
		return;
	}
	BOOL    tem_BMark        = FALSE;
	CString tem_strImgPath   = _T("");
	CString tem_strDstPath   = m_strCVDoc;
	CString tem_strImgFormat = _T("");
	if (m_nPrcsIndex == -1)
	{
		for (int i=m_vcFilePath.size()-1; i>=0; i--)
		{
			m_nPrcsIndex   = i;
			tem_strImgPath = m_vcFilePath[i];
			//�ж��Ƿ�Ϊͼ���ļ�
			tem_strImgFormat = PathFindExtension(tem_strImgPath);
			tem_strImgFormat.MakeLower();
			if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
			{
				tem_BMark = TRUE;
				//��ʾͼ��


				//ȡ��ԭ����ѡ��
				//������������ͼ
				m_conListCtrl.SetFocus();
				int tem_nLastItem = m_conListCtrl.GetSelectedColumn();
				m_conListCtrl.SetItemState(m_conListCtrl.SetSelectionMark(tem_nLastItem),0,LVIS_SELECTED); 
				m_conListCtrl.SetItemState(i, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
				break;
			}
		}
	}

	else
	{
		tem_strImgPath = m_vcFilePath[m_nPrcsIndex];
		//�ж��Ƿ�Ϊͼ���ļ�
		tem_strImgFormat = PathFindExtension(tem_strImgPath);
		tem_strImgFormat.MakeLower();
		if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
		{
			tem_BMark = TRUE;
		}
		else
		{
			tem_BMark = FALSE;
			//��ʾͼ��


			/*
			for (int i=m_vcFilePath.size()-1; i>=0; i--)
			{
				m_nPrcsIndex   = i;
				tem_strImgPath = m_vcFilePath[i];
				//�ж��Ƿ�Ϊͼ���ļ�
				tem_strImgFormat = PathFindExtension(tem_strImgPath);
				tem_strImgFormat.MakeLower();
				if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
				{
					tem_BMark = TRUE;
					//������������ͼ
					// 			m_conListCtrl.SetFocus();
					// 			m_conListCtrl.SetItemState(i, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
					break;
				}
			}
			*/
		}
	}
	
	if (!tem_BMark)
	{
		//û��ͼ���ʽ�ļ�
		m_nPrcsIndex = -1;
		m_strTabImg = _T("");

		m_BShowPicCtrl = TRUE;
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_FULLSCREEN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_DRAG)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_CURDOC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_CURDOCPATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_NORMAL);

		//��ʾ��ʾ��Ϣ	
		Self_CVShowTipImage(_T("res\\tips.jpg"));

		::SendMessage(this->m_hWnd, WM_SIZE, 0, 0);

		return;
	}

	m_BShowPicCtrl = TRUE;
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_BTN_LAST)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_BTN_NEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_FULLSCREEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_DRAG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STA_CURDOC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STA_CURDOCPATH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_NORMAL);
	::SendMessage(this->m_hWnd, WM_SIZE, 0, 0);
	m_strTabImg = tem_strImgPath;
	Self_CVShowImage(tem_strImgPath);
}


void CXRayViewerv10Dlg::Self_ShowOcxCtrl(void)
{
	if (m_BShowPicCtrl)
	{
		Self_ClearPicCtrl();
		GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(TRUE);
// 		GetDlgItem(IDC_BTN_LAST)->ShowWindow(TRUE);
// 		GetDlgItem(IDC_BTN_NEXT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_FULLSCREEN)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_DRAG)->ShowWindow(TRUE);
		GetDlgItem(IDC_STA_CURDOC)->ShowWindow(TRUE);
		GetDlgItem(IDC_STA_CURDOCPATH)->ShowWindow(TRUE);
		::SendMessage(this->m_hWnd, WM_SIZE, 0, 0);

		m_BShowPicCtrl = FALSE;
	}
}


void CXRayViewerv10Dlg::Self_CVShowImage(CString imgpath)
{
	m_vcHistoryImg.clear();
	CString tem_strImgPath   = imgpath;
	CString tem_strDstPath   = m_strCVDoc;
	CString tem_strFileName  = _T("");
	
	tem_strFileName = PathFindFileName(tem_strImgPath);
	tem_strDstPath += _T("\\");
	tem_strDstPath += tem_strFileName;

	CopyFile(tem_strImgPath, tem_strDstPath, FALSE);

	m_strFilesPath     = tem_strImgPath;
	m_strBufferImgPath = tem_strDstPath;
	
	m_vcHistoryImg.push_back(tem_strImgPath);
	m_vcHistoryImg.push_back(tem_strDstPath);
	std::string strTempData = (CStringA)tem_strDstPath;
	m_cvSrcImage = imread(strTempData);
	if (!m_cvSrcImage.data)
	{
//		MessageBox(_T("����ͼ��ʧ�ܣ�"));
		MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
	}

	Self_ResetImageRect();
	Self_ResizeImage(GetDlgItem(IDC_STA_PIC), m_cvSrcImage);
	Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
	
}


void CXRayViewerv10Dlg::Self_CVShowTipImage(CString imgpath)
{
	CString tem_strImgPath   = imgpath;
	
	std::string strTempData = (CStringA)tem_strImgPath;
	m_cvTipsImg = imread(strTempData);

	m_rcImageRect.left     = 0;
	m_rcImageRect.top      = 0;
	m_rcImageRect.right    = m_cvTipsImg.cols;
	m_rcImageRect.bottom   = m_cvTipsImg.rows;
	
	Self_ResizeImage(GetDlgItem(IDC_STA_PIC), m_cvTipsImg);
	Self_ShowMatImage2(m_cvTipsImg, m_rcImageShow);
	m_cvSrcImage.release();
	m_cvDstImage.release();
}

void CXRayViewerv10Dlg::Self_ResetImageRect(void)
{
	if (!m_BPaintLine)
	{
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
	}
	else
	{
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvDstImage.cols;
		m_rcImageRect.bottom   = m_cvDstImage.rows;
	}
	
}


void CXRayViewerv10Dlg::Self_ResizeImage(CWnd* pWnd, Mat srcImg)
{
	float m_ratio;
	float m_i_w, m_i_h, m_p_w, m_p_h;
	pWnd->GetClientRect(&m_rcPicRect);
	m_i_w = (float)srcImg.cols;          //ͼ�������
	m_i_h = (float)srcImg.rows;
	m_p_w = (float)m_rcPicRect.right;    //�ؼ�������
	m_p_h = (float)m_rcPicRect.bottom;
	if (srcImg.cols<=m_rcPicRect.right && srcImg.rows<=m_rcPicRect.bottom)
	{
		//ͼ��ߴ�<=�߿�ߴ�
		m_nDrawX           = ((m_rcPicRect.right-m_rcPicRect.left)-srcImg.cols)/2;
		m_nDrawY           = ((m_rcPicRect.bottom-m_rcPicRect.top)-srcImg.rows)/2;
		m_rcPicRect.right  = srcImg.cols;
		m_rcPicRect.bottom = srcImg.rows;
		m_fCurRatio        = 1;
	}
	else if ((srcImg.cols*m_rcPicRect.bottom)>(srcImg.rows*m_rcPicRect.right))
	{
		//ͼ��̿�������ͼ�����������
		int  tem_nPicHeight = m_rcPicRect.bottom - m_rcPicRect.top;
		m_ratio = m_p_w/m_i_w;
		m_rcPicRect.bottom = (int)(srcImg.rows*m_ratio);
		m_nDrawX = 0;
		m_nDrawY = (tem_nPicHeight - m_rcPicRect.bottom)/2;
		m_fCurRatio = m_ratio;
	}
	else if ((srcImg.cols*m_rcPicRect.bottom)<(srcImg.rows*m_rcPicRect.right))
	{
		//ͼ��̸ߣ�����ͼ��߽�������
		int  tem_nPicWidth = m_rcPicRect.right - m_rcPicRect.left;
		m_ratio = m_p_h/m_i_h;
		m_rcPicRect.right = (int)(srcImg.cols*m_ratio);
		m_nDrawX = (tem_nPicWidth - m_rcPicRect.right)/2;
		m_nDrawY = 0;
		m_fCurRatio = m_ratio;
	}
	else
	{
		//�ߴ������ͬ������������ž���
		m_nDrawY = 0;
		m_nDrawY = 0;
		m_ratio = m_p_h/m_i_h;
		m_rcPicRect.right = (int)(srcImg.cols*m_ratio);
		m_rcPicRect.bottom = (int)(srcImg.rows*m_ratio);
		m_fCurRatio = m_ratio;
	}
	m_rcImageShow.left   = m_nDrawX;
	m_rcImageShow.top    = m_nDrawY;
	m_rcImageShow.right  = m_rcPicRect.right+m_nDrawX;
	m_rcImageShow.bottom = m_rcPicRect.bottom+m_nDrawY;
	m_nShowWidth  = m_rcPicRect.right;
	m_nShowHeight = m_rcPicRect.bottom;
}


void CXRayViewerv10Dlg::Self_ShowMatImage2(Mat img, CRect rect)
{
	IplImage  tem_iplImage(img);
	CDC*   tem_pDC = GetDlgItem(IDC_STA_PIC)->GetDC();
	HDC    tem_hDC = tem_pDC->GetSafeHdc();

	CvvImage    tem_cvMidImage;
	tem_cvMidImage.CopyOf(&tem_iplImage, tem_iplImage.nChannels);
	tem_cvMidImage.DrawToHDC(tem_hDC, &m_rcImageShow, &m_rcImageRect);
	ReleaseDC(tem_pDC);
	tem_cvMidImage.Destroy();
}


void CXRayViewerv10Dlg::OnItemchangedListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	//����if������ڱ�����һ��ListCtrl��������ItemChange����
	if (pNMLV->uChanged==LVIF_STATE)
	{
		if (pNMLV->uNewState & LVIS_SELECTED)
		{
			if (m_BShowPicCtrl)
			{
				int  tem_nListIndex = pNMLV->iItem;
				if (tem_nListIndex>=0 && tem_nListIndex<m_conListCtrl.GetItemCount())
				{
					//�ж�ͼ���Ƿ񱣴�
					if (m_vcHistoryImg.size()>2)
					{
						if (m_BNoSaved)
						{
//							int tem_nClose = MessageBox(_T("�޸���δ���棡�Ƿ񱣴棿"), _T("����"), MB_YESNO);
							int tem_nClose = MessageBox(m_vcMainLang[10], _T("UDS"), MB_YESNO);
							if (tem_nClose == 6)
							{
								//ȷ������
								CString tem_strNewImgPath = m_vcHistoryImg.back();
								CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
								m_BNoSaved = FALSE;
								Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
							}					
						}
					}
					//ɾ������ͼ��
					if (m_vcHistoryImg.size()>1)
					{
						std::vector<CString>::iterator item;
						for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end(); item++)
						{
							DeleteFile(*item);
						}

						m_vcHistoryImg.clear();				
					}			

					//���¼���ͼ��		
					m_nPrcsIndex = tem_nListIndex;
					CString  tem_strImgPath = m_vcFilePath[tem_nListIndex];
					CString  tem_strImgFormat = PathFindExtension(tem_strImgPath);
					if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
					{		
						Self_ClearPicCtrl();
						Self_CVShowImage(tem_strImgPath);	

					}
					else
					{
						//ѡ���ͼ���ļ������picture�ؼ�
						m_nPrcsIndex = -1;
						Self_ClearPicCtrl();
						//��ʾ��ʾ��Ϣ
						Self_CVShowTipImage(_T("res\\tips.jpg"));
						//��յ�ǰͼ��
						
					}	
				}
//				m_conListCtrl.SetItemState( tem_nListIndex, 0, -1);    //-1ȡ�������� 0ȡ��ѡ��
				
			}
			else
			{
				int  tem_nListIndex = pNMLV->iItem;
				if (tem_nListIndex>=0 && tem_nListIndex<m_conListCtrl.GetItemCount())
				{
					m_nPrcsIndex = tem_nListIndex;
				}
			}
		}
	}
	
// 	::SendMessage(GetDlgItem(IDC_LIST_IMAGE)->m_hWnd, WM_KILLFOCUS, 0, 0);
// 	GetDlgItem(IDC_BTN_NEXT)->SetFocus();


	*pResult = 0;
}


void CXRayViewerv10Dlg::OnHoverListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	*pResult = 1;
}


/*ͼ��������*/
void CXRayViewerv10Dlg::Self_ClearPicCtrl(void)
{
	CRect    tem_rcPicCtrl;
	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicCtrl);
	ScreenToClient(&tem_rcPicCtrl);
	CWnd*  tem_pWnd = NULL;
	CDC*   tem_pDc  = NULL;
	tem_pWnd = GetDlgItem(IDC_STA_PIC);

	tem_pDc = pWnd->GetDC();
//	tem_pDc->FillSolidRect(0, 0, tem_rcPicCtrl.right-tem_rcPicCtrl.left, tem_rcPicCtrl.bottom-tem_rcPicCtrl.top,RGB(240,240,240));
	tem_pDc->FillSolidRect(0, 0, tem_rcPicCtrl.right-tem_rcPicCtrl.left, tem_rcPicCtrl.bottom-tem_rcPicCtrl.top,RGB(72,77,91));
	m_conPicCtrl.SetBitmap(NULL);
}

//���洦��ͼ��
void CXRayViewerv10Dlg::Self_SaveLastImg(void)
{
	//�õ�����Ŀ¼
	CString   tem_strFileName = m_strCVDoc;

	//��ȡ�ļ���׺
	CString   tem_strFileFormat = PathFindExtension(m_strFilesPath);

	//��ȡ��ǰʱ�侫ȷ������
	SYSTEMTIME   tem_stDateTime;
	CString      tem_strDate = _T("");
	CString      tem_strTime = _T("");
	GetLocalTime(&tem_stDateTime);
	tem_strDate.Format(_T("%d%02d%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
	tem_strTime.Format(_T("%02d%02d%02d%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds); 

	//����µ��ļ���
	tem_strFileName += _T("\\");
	tem_strFileName += tem_strDate;
	tem_strFileName += tem_strTime;
	tem_strFileName += tem_strFileFormat;

	//����ͼ��
	std::string tem_sFilePath = (CStringA)tem_strFileName; 
	imwrite(tem_sFilePath, m_cvNextImg);
	m_vcHistoryImg.push_back(tem_strFileName);
}

//ͼ����ת
Mat CXRayViewerv10Dlg::ImageRotate(Mat img, int angle)
{
	int     tem_nDegree = angle;
	double  tem_dAngle  = tem_nDegree*CV_PI/180;
	double  a = sin(tem_dAngle), b = cos(tem_dAngle);
	int     tem_nWidth = img.cols;
	int     tem_nHeight= img.rows;
	int     m_width_rotate = int(tem_nHeight *fabs(a)+ tem_nWidth *fabs(b));
	int     m_height_rotate= int(tem_nWidth *fabs(a)+tem_nHeight *fabs(b));
	float   map[6];
	Mat     m_map_matrix(2,3,CV_32F, map);

	CvPoint2D32f center = cvPoint2D32f(tem_nWidth / 2, tem_nHeight / 2);  
	CvMat map_matrix2 = m_map_matrix;  
	cv2DRotationMatrix(center, tem_nDegree, 1.0, &map_matrix2); 
	map[2] += (m_width_rotate - tem_nWidth)/2;
	map[5] += (m_height_rotate - tem_nHeight)/2;

	Mat    tem_cvMidImage;
	tem_cvMidImage.create(cv::Size(m_width_rotate, m_height_rotate), img.type());
	warpAffine(img, tem_cvMidImage, m_map_matrix, cv::Size( m_width_rotate, m_height_rotate),1,0,0);
	return tem_cvMidImage;
}

//ͼ����
Mat CXRayViewerv10Dlg::ImageMirror(Mat img, bool mirrormark)
{
	Mat  tem_cvMidImg;
	tem_cvMidImg.create(img.size(), img.type());
	Mat  map_x;
	Mat  map_y;
	map_x.create(img.size(), CV_32FC1);
	map_y.create(img.size(), CV_32FC1);
	if (mirrormark)
	{
		//ˮƽ����
		for (int i=0; i<img.rows; ++i)
		{
			for (int j=0; j<img.cols; ++j)
			{
				map_x.at<float>(i,j) = (float)(img.cols-j);
				map_y.at<float>(i,j) = (float)i;		
			}
		}
		remap(img, tem_cvMidImg, map_x, map_y, CV_INTER_LINEAR);
	}
	else
	{
		//��ֱ����
		for (int i=0; i<img.rows; i++)
		{
			for (int j=0; j<img.cols; j++)
			{
				map_x.at<float>(i,j) = (float)j;
				map_y.at<float>(i,j) = (float)(img.rows-i);		
			}
		}
		remap(img, tem_cvMidImg, map_x, map_y,CV_INTER_LINEAR);
	}
	return tem_cvMidImg;
}

//��ɫ
Mat CXRayViewerv10Dlg::ImageInvert(Mat img)
{
	int    tem_nImgWidth  = img.cols;
	int    tem_nImgHeight = img.rows;
	int    tem_nImgStep   = img.step;;
	int    tem_nImgChannel= img.channels();
	uchar* tem_ucImgDate  = (uchar*)img.data;

	for (int i=0; i<tem_nImgHeight; i++)
	{
		for (int j=0; j<tem_nImgWidth; j++)
		{
			for (int k=0; k<tem_nImgChannel; k++)
			{
				tem_ucImgDate[i*tem_nImgStep+j*tem_nImgChannel+k]= 255-tem_ucImgDate[i*tem_nImgStep+j*tem_nImgChannel+k];
			}
		}
	}
	return img;
}

//��
Mat CXRayViewerv10Dlg::ImageSharp(Mat img)
{
	Mat   kernel(3, 3, CV_32F, Scalar(0));
	/*����1
	kernel.at<float>(0,0) = 0;    kernel.at<float>(0,1) = -1.0; kernel.at<float>(0,2) = 0;
	kernel.at<float>(1,0) = -1.0; kernel.at<float>(1,1) = 5.0;  kernel.at<float>(1,2) = -1.0;
	kernel.at<float>(2,0) = 0;    kernel.at<float>(2,1) = -1.0; kernel.at<float>(2,2) = 0;
	*/


	/*����2
	kernel.at<float>(0,0) = 1.0; kernel.at<float>(0,1) = 1.0;  kernel.at<float>(0,2) = 1.0;
	kernel.at<float>(1,0) = 1.0; kernel.at<float>(1,1) = -8.0; kernel.at<float>(1,2) = 1.0;
	kernel.at<float>(2,0) = 1.0; kernel.at<float>(2,1) = 1.0;  kernel.at<float>(2,2) = 1.0;
	*/

	kernel.at<float>(0,0) = -1.0/7; kernel.at<float>(0,1) = -2.0/7;  kernel.at<float>(0,2) = -1.0/7;
	kernel.at<float>(1,0) = -2.0/7; kernel.at<float>(1,1) = 19.0/7;   kernel.at<float>(1,2) = -2.0/7;
	kernel.at<float>(2,0) = -1.0/7; kernel.at<float>(2,1) = -2.0/7;  kernel.at<float>(2,2) = -1.0/7;

	Mat    tem_cvMidImage;
	tem_cvMidImage.create(img.size(), img.type());
	filter2D(img, tem_cvMidImage, img.depth(), kernel);    //depth����Ϊ-1ʱ������ͼ����ԭͼ����һ�¡�
	

	return tem_cvMidImage;
}

//���ȡ��Աȶ�
Mat CXRayViewerv10Dlg::BrightAndContrast(Mat img, int bright, int contrast)
{
	Mat   tem_cvMidImage = img.clone();
	Mat   tem_cvDstImage;
	tem_cvDstImage = Mat::zeros(img.size(), img.type());

	if (tem_cvMidImage.channels()==3)
	{
		for (int y=0; y<tem_cvMidImage.rows; y++)
		{
			for (int x=0; x<tem_cvMidImage.cols; x++)
			{
				for (int c=0; c<3; c++)
				{
					tem_cvDstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>((contrast*0.01+1)*(tem_cvMidImage.at<Vec3b>(y,x)[c])+bright);
				}
			}
		}
	}
	else if (tem_cvMidImage.channels()==1)
	{
		//�Ҷȡ��ڰ׵�ͨ��ͼ��
		for (int y=0; y<tem_cvMidImage.rows; y++)
		{
			for (int x=0; x<tem_cvMidImage.cols; x++)
			{
				tem_cvDstImage.at<uchar>(y,x) = saturate_cast<uchar>((contrast*0.01+1)*(tem_cvMidImage.at<uchar>(y,x))+bright);
			}
		}
	}

	return tem_cvDstImage;
}

//Gama����
Mat CXRayViewerv10Dlg::ImageGamma(Mat img, int gama)
{
	float  tem_fGama = (float)gama*1.0/100;
	Mat    tem_cvMidImage = img.clone();
	//��������ļ�LUT
	unsigned char LUT[256];
	for (int i=0; i<256; i++)
	{
		//Gamma�任����ʽ
		LUT[i] = saturate_cast<uchar>(pow((float)(i/255.0), tem_fGama) * 255.0f);
	}

	//�ж�ͼ��ͨ������
	if (tem_cvMidImage.channels() == 1)
	{
		MatIterator_<uchar> iterator = tem_cvMidImage.begin<uchar>();
		MatIterator_<uchar> iteratorEnd = tem_cvMidImage.end<uchar>();
		for (; iterator!=iteratorEnd;iterator++)
		{
			*iterator = LUT[(*iterator)];
		}
	} 
	else
	{
		//��ͨ�� ʱ��ÿ��ͨ����������
		MatIterator_<Vec3b> iterator = tem_cvMidImage.begin<Vec3b>();
		MatIterator_<Vec3b> iteratorEnd = tem_cvMidImage.end<Vec3b>();
		for ( ; iterator!=iteratorEnd; iterator++)
		{
			(*iterator)[0] = LUT[((*iterator)[0])];
			(*iterator)[1] = LUT[((*iterator)[1])];
			(*iterator)[2] = LUT[((*iterator)[2])];
		}
	}

	return tem_cvMidImage;
}


//��ͼ���������Ŵ���С�����С���ת
void CXRayViewerv10Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	ClientToScreen(&point);

	if (m_BPaintLine)
	{
		//��¼�������
		CRect tem_rcPic = m_rcImageShow;
		//��picture�ؼ������޸�Ϊͼ������
		m_conPicCtrl.ClientToScreen(tem_rcPic);
		if(tem_rcPic.PtInRect(point))
		{
			m_BLButtonDown = TRUE;
			SetCapture();
			SetCursor(LoadCursor(NULL,IDC_UPARROW));
			m_conPicCtrl.ScreenToClient(&point);
			m_ptOri = point;
			m_ptEnd = point;
		}
	}
	else if (m_BSlcRect)
	{
		//ѡ��**********************************
		CRect tem_rcPic;
		m_conPicCtrl.GetClientRect(tem_rcPic);
		m_conPicCtrl.ClientToScreen(tem_rcPic);
		if(tem_rcPic.PtInRect(point))
		{
			m_BLButtonDown = TRUE;
			SetCapture();
			m_conPicCtrl.ScreenToClient(&point);
			m_ptOri = point;
			m_ptEnd = point;
		}
	}
	else if (m_BLabel)
	{
		CRect tem_rcPic;
		m_conPicCtrl.GetClientRect(tem_rcPic);
		m_conPicCtrl.ClientToScreen(tem_rcPic);
		if(tem_rcPic.PtInRect(point))
		{
			m_BLButtonDown = TRUE;
			SetCapture();
			m_conPicCtrl.ScreenToClient(&point);
			m_ptOri = point;
			m_ptEnd = point;
		}
	}
	else
	{
		//�϶�***********************************
		m_BLButtonDown = TRUE;
		ClientToScreen(m_rcImageShow);
		if (m_rcImageShow.PtInRect(point))
		{
			SetCapture();
			SetCursor(LoadCursor(NULL,IDC_HAND));
			m_ptDragOri = point;       //�϶����
			m_ptDragEnd = point;
		}
		ScreenToClient(m_rcImageShow);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CXRayViewerv10Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (m_BLButtonDown)
	{
		if (m_BPaintLine)
		{
			//���ߺ���
			ClientToScreen(&point);		
			CRect tem_rcPic;
			m_conPicCtrl.GetClientRect(tem_rcPic);
			m_conPicCtrl.ClientToScreen(tem_rcPic);
			if(tem_rcPic.PtInRect(point))
			{
				m_conPicCtrl.ScreenToClient(&point);			
				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
				SetROP2(hdc,R2_NOTXORPEN);          
				HPEN hpen;
				hpen=CreatePen(PS_SOLID,2,RGB(255,0,0));
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));

				MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
				LineTo(hdc, m_ptEnd.x, m_ptEnd.y);
				m_ptEnd = point;
				MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
				LineTo(hdc, m_ptEnd.x, m_ptEnd.y);

				::DeleteObject(hpen);
			}

		}
		else if (m_BSlcRect)
		{
			ClientToScreen(&point);		
			CRect tem_rcPic;
			m_conPicCtrl.GetClientRect(tem_rcPic);
			m_conPicCtrl.ClientToScreen(tem_rcPic);
			if(tem_rcPic.PtInRect(point))
			{
				m_conPicCtrl.ScreenToClient(&point);			
				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
				SetROP2(hdc,R2_NOTXORPEN);          
				HPEN hpen;
				hpen=CreatePen(PS_SOLID,2,RGB(255,0,0));
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));
				::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
				m_ptEnd = point;
				::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
				::DeleteObject(hpen);
			}
		}
		else if(m_BLabel)
		{
			if (m_nLineMode == 0)
			{
				ClientToScreen(&point);		
				CRect tem_rcPic;
				m_conPicCtrl.GetClientRect(tem_rcPic);
				m_conPicCtrl.ClientToScreen(tem_rcPic);
				if(tem_rcPic.PtInRect(point))
				{
					m_conPicCtrl.ScreenToClient(&point);			
					HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
					SetROP2(hdc,R2_NOTXORPEN);   
					HPEN hpen;
					hpen=CreatePen(PS_SOLID, m_nLineWidth/2+1, m_refLineColor);
					SelectObject(hdc,hpen);
					SelectObject(hdc,GetStockObject(NULL_BRUSH));
					::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
					m_ptEnd = point;
					::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
					::DeleteObject(hpen);
				}
			} 
			else if(m_nLineMode==1)
			{
				//���ߺ���
				ClientToScreen(&point);		
				CRect tem_rcPic;
				m_conPicCtrl.GetClientRect(tem_rcPic);
				m_conPicCtrl.ClientToScreen(tem_rcPic);
				if(tem_rcPic.PtInRect(point))
				{
					m_conPicCtrl.ScreenToClient(&point);			
					HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
					SetROP2(hdc,R2_NOTXORPEN);          
					HPEN hpen;
					hpen=CreatePen(PS_SOLID, m_nLineWidth/2+1, m_refLineColor);
					SelectObject(hdc,hpen);
					SelectObject(hdc,GetStockObject(NULL_BRUSH));

					MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
					LineTo(hdc, m_ptEnd.x, m_ptEnd.y);
					m_ptEnd = point;
					MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
					LineTo(hdc, m_ptEnd.x, m_ptEnd.y);

					::DeleteObject(hpen);
				}
			}
			else if (m_nLineMode==2)
			{
				//���⻭
				m_conPicCtrl.ScreenToClient(&point);			
				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
				SetROP2(hdc,R2_COPYPEN);          
				HPEN hpen;
				hpen=CreatePen(PS_SOLID, m_nLineWidth/2+1, m_refLineColor);
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));

				m_ptEnd = point;
				MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
				LineTo(hdc, m_ptEnd.x, m_ptEnd.y);
				m_ptOri = point;
			
				

				::DeleteObject(hpen);
			}
		}
		else
		{			
			ClientToScreen(&point);	
			m_ptDragEnd = point;

			int tem_nDragSpeed = 5;   //�����϶��ٶȣ���ֵԽ���϶�Խ��
			int tem_nOffSetX = m_ptDragEnd.x-m_ptDragOri.x;
			int tem_nOffSetY = m_ptDragEnd.y-m_ptDragOri.y;
			//�϶��ػ�
			int tem_nImageWidth  = m_cvSrcImage.cols;   //ͼ��ԭʼ�ߴ�
			int tem_nImageHeight = m_cvSrcImage.rows;

			int tem_nThumbWidth  = 0;          //�Ŵ���С������ͼ�ߴ�
			int tem_nThumbHeight = 0;

			CRect   tem_rcPicRect; 
			GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
			ScreenToClient(&tem_rcPicRect);


			float   tem_fCurRatio = m_fCurRatio;

			int     tem_nDrawX, tem_nDrawY, tem_nDrawW, tem_nDrawH;   //ӳ������Լ�����

			//�Ŵ������ͼ�ߴ�
			tem_nThumbWidth  = (int)(tem_fCurRatio*tem_nImageWidth);
			tem_nThumbHeight = (int)(tem_fCurRatio*tem_nImageHeight);
			//1)����ͼ�ߴ�<picture�ؼ��ߴ�*****************************
			//�����϶�

			//2)����ͼ��<picture����������ͼ��>picture��
			if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
			{
				//ͼ����ʾ����
				m_rcImageRect.left     = 0;
				m_rcImageRect.right    = m_cvSrcImage.cols;

				//Դͼ��ʾ����ĵ���ʵ��m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight);
// 				m_rcImageRect.top     += (int)(tem_nOffSetY*1.0/m_fCurRatio);
// 				m_rcImageRect.bottom  += (int)(tem_nOffSetY*1.0/m_fCurRatio);

				m_rcImageRect.top     += (int)(m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight))/tem_nDragSpeed;
				m_rcImageRect.bottom  += (int)(m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight))/tem_nDragSpeed;
				if (m_rcImageRect.top<=0)
				{
					m_rcImageRect.top    = 0;
					m_rcImageRect.bottom = m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
				}
				if (m_rcImageRect.bottom>=m_cvSrcImage.rows)
				{
					m_rcImageRect.bottom = m_cvSrcImage.rows;
					m_rcImageRect.top    = m_cvSrcImage.rows - m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
				}
			}
			//3)����ͼ��>picctrl����������ͼ��<picctrl��
			else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
			{
				//ͼ����ʾ����

				m_rcImageRect.top      = 0;
				m_rcImageRect.bottom   = m_cvSrcImage.rows;
				//Դͼ��ʾ��������ǿ�m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth)
//  				m_rcImageRect.left    -= (int)(tem_nOffSetX*1.0/m_fCurRatio);
//  				m_rcImageRect.right   -= (int)(tem_nOffSetX*1.0/m_fCurRatio);

				m_rcImageRect.left    -= (int)(m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth))/tem_nDragSpeed;
				m_rcImageRect.right   -= (int)(m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth))/tem_nDragSpeed;	
				if (m_rcImageRect.left<=0)
				{
					m_rcImageRect.left  = 0;
					m_rcImageRect.right = m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
				}
				if (m_rcImageRect.right>=m_cvSrcImage.cols)
				{
					m_rcImageRect.right = m_cvSrcImage.cols;
					m_rcImageRect.left  = m_cvSrcImage.cols - m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
				}
			}
			//4)����ͼ��>picctrl����������ͼ��>picctrl��
			else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
			{
				//ͼ����ʾ����
// 				m_rcImageRect.top     += (int)(tem_nOffSetY*1.0/m_fCurRatio);
// 				m_rcImageRect.bottom  += (int)(tem_nOffSetY*1.0/m_fCurRatio);

				m_rcImageRect.top     += (int)(m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight))/tem_nDragSpeed;
				m_rcImageRect.bottom  += (int)(m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight))/tem_nDragSpeed;
				if (m_rcImageRect.top<=0)
				{
					m_rcImageRect.top    = 0;
					m_rcImageRect.bottom = m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
				}
				if (m_rcImageRect.bottom>=m_cvSrcImage.rows)
				{
					m_rcImageRect.bottom = m_cvSrcImage.rows;
					m_rcImageRect.top    = m_cvSrcImage.rows - m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
				}

// 				m_rcImageRect.left    -= (int)(tem_nOffSetX*1.0/m_fCurRatio);
// 				m_rcImageRect.right   -= (int)(tem_nOffSetX*1.0/m_fCurRatio);

				m_rcImageRect.left    -= (int)(m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth))/tem_nDragSpeed;
				m_rcImageRect.right   -= (int)(m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth))/tem_nDragSpeed;	
				if (m_rcImageRect.left<=0)
				{
					m_rcImageRect.left  = 0;
					m_rcImageRect.right = m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
				}
				if (m_rcImageRect.right>=m_cvSrcImage.cols)
				{
					m_rcImageRect.right = m_cvSrcImage.cols;
					m_rcImageRect.left  = m_cvSrcImage.cols - m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
				}
			}
			
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);

		}

	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CXRayViewerv10Dlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴�������Ϣ�����������
}


void CXRayViewerv10Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (m_BLButtonDown)
	{
		if (m_BPaintLine)
		{
			BOOL     tem_BOrientation = TRUE;   //��ת�����־λ��Ĭ��˳ʱ��
			double   tem_dRadian = 0;     //����
			int      tem_nAngle  = 0;     //�Ƕ�
			m_BLButtonDown = FALSE;
//			m_BPaintLine   = FALSE;
			ReleaseCapture();
			SetCursor(LoadCursor(NULL,IDC_ARROW));	

			//��������������תֱ����X������н�
			if (m_ptOri == m_ptEnd)
			{
				//δ���ߣ��޼н�
				tem_nAngle = 0;
				tem_BOrientation = TRUE;

			}
			if (m_ptOri.x==m_ptEnd.x && m_ptOri.y!=m_ptEnd.y)
			{
				//�н�Ϊ90�ȣ���ֱ����
				tem_nAngle = 90;
				//���ϵ���Ϊ˳�����µ���Ϊ��
				if (m_ptOri.y<m_ptEnd.y)
				{
					tem_BOrientation = TRUE;
				} 
				else
				{
					tem_BOrientation = FALSE;
				}

			}
			else if (m_ptOri.y==m_ptEnd.y && m_ptOri.x!=m_ptEnd.x)
			{
				//�н�Ϊ0�ȣ�ˮƽ����
				tem_nAngle = 0;
				tem_BOrientation = TRUE;
			}
			else
			{
				//��н�
				int   tem_nLineWidth  = abs(m_ptOri.x-m_ptEnd.x);
				int   tem_nLineHeight = abs(m_ptOri.y-m_ptEnd.y);
				tem_dRadian = atan(tem_nLineHeight*1.0/tem_nLineWidth);
				tem_nAngle  = (tem_dRadian*180/m_fPI);
				if (m_ptOri.x<m_ptEnd.x)
				{
					tem_BOrientation = TRUE;
				} 
				else
				{
					tem_BOrientation = FALSE;
				}
			}
			if (tem_BOrientation)
			{
				tem_nAngle *= -1;
			} 
			
			//��תͼ��
			m_nAngleCount += tem_nAngle;
			m_cvDstImage = ImageRotate(m_cvSrcImage, m_nAngleCount);
//			m_cvDstImage = ImageRotate(m_cvSrcImage, tem_nAngle);
			//������ͼ
			m_cvLastImg = m_cvSrcImage.clone();
			m_cvNextImg = m_cvDstImage.clone();

//			m_cvSrcImage = m_cvDstImage.clone();

			Self_ClearPicCtrl();
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvNextImg);
			Self_ShowMatImage2(m_cvNextImg, m_rcImageShow);
			Self_CreateLine();
//			Self_SaveLastImg();
		}
		else if (m_BSlcRect)
		{
			m_BLButtonDown = FALSE;
			m_BSlcRect     = FALSE;
			m_BSlcRected   = TRUE;
			ReleaseCapture();

			//�����������ϡ����¡����ϡ��������ַ���ѡȡ
			if (m_ptOri.x<m_ptEnd.x)
			{
				m_rcImageCrop.left = m_ptOri.x;
				m_rcImageCrop.right= m_ptEnd.x;
			}
			else
			{
				m_rcImageCrop.left = m_ptEnd.x;
				m_rcImageCrop.right= m_ptOri.x;
			}
			if (m_ptOri.y<m_ptEnd.y)
			{
				m_rcImageCrop.top  = m_ptOri.y;
				m_rcImageCrop.bottom=m_ptEnd.y;
			}
			else
			{
				m_rcImageCrop.top  = m_ptEnd.y;
				m_rcImageCrop.bottom=m_ptOri.y;
			}

			m_cvSrcImage.copyTo(m_cvLastImg);
			m_cvDstImage = Self_CropImage(m_cvSrcImage, m_rcImageShow, m_rcImageCrop);
			m_cvDstImage.copyTo(m_cvSrcImage);
			m_cvSrcImage.copyTo(m_cvNextImg);
			Self_ResetImageRect();
			Self_ResizeImage(pWnd, m_cvSrcImage);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			Self_SaveLastImg();
			m_BSlcRect   = FALSE;
			m_BSlcRected = FALSE;
		}
		else if (m_BLabel)
		{
				m_BLButtonDown = FALSE;
//				m_BLabel       = FALSE;
				ReleaseCapture();

			if (m_nLineMode == 0)
			{
				/*
				ClientToScreen(&point);		
				CRect tem_rcPic;
				m_conPicCtrl.GetClientRect(tem_rcPic);
				m_conPicCtrl.ClientToScreen(tem_rcPic);

				m_nLineWidth   = 5;
				m_refLineColor = 65280;

				m_conPicCtrl.ScreenToClient(&point);			
				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
				SetROP2(hdc,R2_COPYPEN);   
				HPEN hpen;
				hpen=CreatePen(PS_SOLID, m_nLineWidth, m_refLineColor);
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));
				::Rectangle(hdc, m_ptOri.x, m_ptOri.y, m_ptEnd.x, m_ptEnd.y); 
				::DeleteObject(hpen);
				*/

				//�����������ϡ����¡����ϡ��������ַ���ѡȡ
				if (m_ptOri.x<m_ptEnd.x)
				{
					m_rcImageCrop.left = m_ptOri.x;
					m_rcImageCrop.right= m_ptEnd.x;
				}
				else
				{
					m_rcImageCrop.left = m_ptEnd.x;
					m_rcImageCrop.right= m_ptOri.x;
				}
				if (m_ptOri.y<m_ptEnd.y)
				{
					m_rcImageCrop.top  = m_ptOri.y;
					m_rcImageCrop.bottom=m_ptEnd.y;
				}
				else
				{
					m_rcImageCrop.top  = m_ptEnd.y;
					m_rcImageCrop.bottom=m_ptOri.y;
				}
				//��ʼ�����ꡪ��m_pOri;  �յ����ꡪ��m_pEnd;
				m_cvSrcImage.copyTo(m_cvLastImg);
				m_cvDstImage = Self_DrawRetangle(m_cvSrcImage, m_rcImageShow, m_rcImageCrop, m_nLineWidth, m_refLineColor);
				m_nNoteCount++;

				m_cvDstImage.copyTo(m_cvSrcImage);
				m_cvSrcImage.copyTo(m_cvNextImg);
				Self_ResetImageRect();
				Self_ResizeImage(pWnd, m_cvSrcImage);
				Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
				Self_SaveLastImg();

				
			} 
			else if (m_nLineMode == 1)
			{
				m_rcImageCrop.left  = m_ptOri.x;
				m_rcImageCrop.top   = m_ptOri.y;
				m_rcImageCrop.right = m_ptEnd.x;
				m_rcImageCrop.bottom= m_ptEnd.y;
				
				m_cvSrcImage.copyTo(m_cvLastImg);

				m_cvDstImage = Self_DrawArrow(m_cvSrcImage, m_rcImageShow, m_rcImageCrop, m_nLineWidth, m_refLineColor);
				m_nNoteCount++;

				m_cvDstImage.copyTo(m_cvSrcImage);
				m_cvSrcImage.copyTo(m_cvNextImg);
				Self_ResetImageRect();
				Self_ResizeImage(pWnd, m_cvSrcImage);
				Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
				Self_SaveLastImg();

			}		
			else if (m_nLineMode == 3)
			{
				//��һС�α����
				m_ptEnd.x = m_ptOri.x;
				m_ptOri.y = m_ptOri.y - 30;

				HDC hdc=::GetDC(m_conPicCtrl.GetSafeHwnd());
//				SetROP2(hdc,R2_COPYPEN);          
				SetROP2(hdc,R2_NOTXORPEN); 
				HPEN hpen;
				hpen=CreatePen(PS_SOLID, m_nLineWidth/2+1, m_refLineColor);
				SelectObject(hdc,hpen);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));

				MoveToEx(hdc, m_ptOri.x, m_ptOri.y, NULL);
				LineTo(hdc, m_ptEnd.x, m_ptEnd.y);

				::DeleteObject(hpen);

				m_rcImageCrop.left  = m_ptOri.x;
				m_rcImageCrop.top   = m_ptOri.y;

				if (m_ptNoteSite.x!=0 || m_ptNoteSite.y!=0)
				{
					MoveToEx(hdc, m_ptNoteSite.x, m_ptNoteSite.y, NULL);
					LineTo(hdc, m_ptNoteSite.x, m_ptNoteSite.y + 30);
				}
				m_ptNoteSite = m_ptOri;
/*
				m_cvSrcImage.copyTo(m_cvLastImg);

				m_cvDstImage = Self_AddText(m_cvSrcImage, m_rcImageShow, m_rcImageCrop, _T("�Ϲ�ͼ��"), m_refLineColor, m_strFont, m_nFontSize, m_BBold, m_BItalic);

				m_cvDstImage.copyTo(m_cvSrcImage);
				m_cvSrcImage.copyTo(m_cvNextImg);
				Self_ResetImageRect();
				Self_ResizeImage(pWnd, m_cvSrcImage);
				Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
				Self_SaveLastImg();
*/
			}
		}
		else
		{
			m_BLButtonDown = FALSE;
			ReleaseCapture();
			SetCursor(LoadCursor(NULL,IDC_ARROW));	
			
		}

	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CXRayViewerv10Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	BOOL      tem_BRC;
	CPoint    tem_ptCurPoint = pt;

	if (zDelta>0)
	{
		//�Ŵ�
		tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
		if(tem_BRC)
		{
			m_fCurRatio+=0.05;
		}

	}
	else
	{
		//��С
		tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, FALSE);
		if(tem_BRC)
		{
			m_fCurRatio-=0.05;
		}

	}
	if (m_BPaintLine)
	{
		Self_CreateLine();
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CXRayViewerv10Dlg::Self_ZoomSize(Mat src, float ratio, bool zoommark)
{
	int tem_nImageWidth  = src.cols;   //ͼ��ԭʼ�ߴ�
	int tem_nImageHeight = src.rows;

	int tem_nThumbWidth  = 0;          //�Ŵ���С������ͼ�ߴ�
	int tem_nThumbHeight = 0;

	CRect   tem_rcPicRect; 
	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
	ScreenToClient(&tem_rcPicRect);


	float   tem_fCurRatio = ratio;

	int     tem_nDrawX, tem_nDrawY, tem_nDrawW, tem_nDrawH;   //ӳ������Լ�����

	if (zoommark)
	{
		//�Ŵ�************************************
		tem_fCurRatio += 0.05;        //һ�ηŴ�5%
	}
	else
	{
		//��С************************************
		tem_fCurRatio -= 0.05;        //һ����С5%
	}
	if (tem_fCurRatio>=2.0)
	{
		tem_fCurRatio=2.0;
		return FALSE;
	}
	else if (tem_fCurRatio<=0.05)
	{
		tem_fCurRatio=0.05;
		return FALSE;
	}

	//�Ŵ������ͼ�ߴ�
	tem_nThumbWidth  = (int)(tem_fCurRatio*tem_nImageWidth);
	tem_nThumbHeight = (int)(tem_fCurRatio*tem_nImageHeight);
	//1)�Ŵ������ͼ�ߴ�<picture�ؼ��ߴ�
	if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture��ʾ����
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//ͼ����ʾ����
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
	}
	//2)�Ŵ������ͼ��<picture����������ͼ��>picture��
	else if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture��ʾ����
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//ͼ����ʾ����
		m_rcImageRect.left     = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;

		//Դͼ��ʾ����ĵ���ʵ��m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);

	}
	//3)�Ŵ������ͼ��>picture����������ͼ��<picture��
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture��ʾ����
		tem_nDrawX           = 0;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//ͼ����ʾ����

		m_rcImageRect.top      = 0;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
		//Դͼ��ʾ��������ǿ�m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth)
		m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);	

	}
	//4���Ŵ������ͼ��>picture����������ͼ��>picture��
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture��ʾ����
		tem_nDrawX           = 0;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;

		//ͼ����ʾ����
		m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);


	}
	//���жϽ�����1:1��ʾ��־λ
	if (!m_BOriSize)    
	{
		if (zoommark)
		{
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		}
		else
		{
			Self_ClearPicCtrl();
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		}
	}
	
	return TRUE;
}


void CXRayViewerv10Dlg::Self_OriSize(Mat src)
{
	int tem_nImageWidth  = src.cols;   //ͼ��ԭʼ�ߴ�
	int tem_nImageHeight = src.rows;

	int tem_nThumbWidth  = src.cols;          //�Ŵ���С������ͼ�ߴ�
	int tem_nThumbHeight = src.rows;

	CRect   tem_rcPicRect; 
	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
	ScreenToClient(&tem_rcPicRect);

	int     tem_nDrawX, tem_nDrawY, tem_nDrawW, tem_nDrawH;   //ӳ������Լ�����

	//1)�Ŵ������ͼ�ߴ�<picture�ؼ��ߴ�
	if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture��ʾ����
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//ͼ����ʾ����
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
	}
	//2)�Ŵ������ͼ��<picture����������ͼ��>picture��
	else if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture��ʾ����
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//ͼ����ʾ����
		m_rcImageRect.left     = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;

		//Դͼ��ʾ����ĵ���ʵ��m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);

	}
	//3)�Ŵ������ͼ��>picture����������ͼ��<picture��
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture��ʾ����
		tem_nDrawX           = 0;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//ͼ����ʾ����

		m_rcImageRect.top      = 0;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
		//Դͼ��ʾ��������ǿ�m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth)
		m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);	

	}
	//4���Ŵ������ͼ��>picture����������ͼ��>picture��
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture��ʾ����
		/*
		tem_nDrawX           = 0;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		*/
		m_rcImageShow = tem_rcPicRect;


		//ͼ����ʾ����
		/*m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);*/

		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_rcImageRect.Width();
		m_rcImageRect.bottom   = m_rcImageRect.Height();


	}

	Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
	m_fCurRatio = 1.0;
}


Mat CXRayViewerv10Dlg::Self_CropImage(Mat img, CRect showRect, CRect cropRect)
{
	CRect   tem_rcShow = showRect;
	CRect   tem_rcCrop = cropRect;

	if (tem_rcCrop.left==tem_rcCrop.right || tem_rcCrop.top==tem_rcCrop.bottom)
	{
		return img;
	}

	//��㳬��ͼ��
	if (tem_rcCrop.left<tem_rcShow.left)
	{
		tem_rcCrop.left=tem_rcShow.left;
	}
	if (tem_rcCrop.top<tem_rcShow.top)
	{
		tem_rcCrop.top=tem_rcShow.top;
	}
	if (tem_rcCrop.right>tem_rcShow.right)
	{
		tem_rcCrop.right=tem_rcShow.right;
	}
	if (tem_rcCrop.bottom>tem_rcShow.bottom)
	{
		tem_rcCrop.bottom=tem_rcShow.bottom;
	}

	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //������ʾ����
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //������ʾ�߶�
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //��ʾ����
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //��ʾ�߶�

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //����������
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	float  tem_fWidthPropertion = tem_nCropWidth*1.0/tem_nShowWidth;          //�����������ʾ�����ռ��
	float  tem_fHeightPropertion= tem_nCropHeight*1.0/tem_nShowHeight;

	int    tem_nDstWidth   = img.cols* tem_fWidthPropertion;
	int    tem_nDstHeith   = img.rows*tem_fHeightPropertion;

	int    tem_nDstLeft    = img.cols*tem_fXPropertion;
	int    tem_nDstTop     = img.rows*tem_fYPropertion;

	CvRect  tem_crcDst;
	tem_crcDst.x   = tem_nDstLeft;
	tem_crcDst.y   = tem_nDstTop;
	tem_crcDst.width  = tem_nDstWidth;
	tem_crcDst.height =tem_nDstHeith;

	Self_ClearPicCtrl();

	if (m_BSlcRected)
	{
	}
	Mat    tem_cvMidImage(img, tem_crcDst);

	//�յ㳬��ͼ��
	return tem_cvMidImage;
}


Mat CXRayViewerv10Dlg::Self_DrawRetangle(Mat img, CRect showRect, CRect cropRect, int linewidth, COLORREF linecolor)
{
	CRect   tem_rcShow = showRect;
	CRect   tem_rcCrop = cropRect;

	if (tem_rcCrop.left==tem_rcCrop.right || tem_rcCrop.top==tem_rcCrop.bottom)
	{
		return img;
	}

	//��㳬��ͼ��
	if (tem_rcCrop.left<tem_rcShow.left)
	{
		tem_rcCrop.left=tem_rcShow.left;
	}
	if (tem_rcCrop.top<tem_rcShow.top)
	{
		tem_rcCrop.top=tem_rcShow.top;
	}
	if (tem_rcCrop.right>tem_rcShow.right)
	{
		tem_rcCrop.right=tem_rcShow.right;
	}
	if (tem_rcCrop.bottom>tem_rcShow.bottom)
	{
		tem_rcCrop.bottom=tem_rcShow.bottom;
	}

	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //������ʾ����
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //������ʾ�߶�
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //��ʾ����
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //��ʾ�߶�

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //����������
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	float  tem_fWidthPropertion = tem_nCropWidth*1.0/tem_nShowWidth;          //�����������ʾ�����ռ��
	float  tem_fHeightPropertion= tem_nCropHeight*1.0/tem_nShowHeight;

	int    tem_nDstWidth   = img.cols* tem_fWidthPropertion;
	int    tem_nDstHeith   = img.rows*tem_fHeightPropertion;

	int    tem_nDstLeft    = img.cols*tem_fXPropertion;
	int    tem_nDstTop     = img.rows*tem_fYPropertion;

	CvRect  tem_crcDst;
	tem_crcDst.x      = tem_nDstLeft;
	tem_crcDst.y      = tem_nDstTop;
	tem_crcDst.width  = tem_nDstWidth;
	tem_crcDst.height =tem_nDstHeith;

	Self_ClearPicCtrl();

	if (m_BSlcRected)
	{
	}
	Mat    tem_cvMidImage(img);
	//��ȡ������ɫ
	int  tem_nRed   = GetRValue(linecolor);
	int  tem_nGreen = GetGValue(linecolor);
	int  tem_nBlue  = GetBValue(linecolor);
	rectangle(tem_cvMidImage, tem_crcDst, Scalar(tem_nBlue, tem_nGreen, tem_nRed), linewidth, 8, 0);

	//�յ㳬��ͼ��
	return tem_cvMidImage;
}


BOOL CXRayViewerv10Dlg::Self_DisableCtrl(int index)
{
	return FALSE;
}


BOOL CXRayViewerv10Dlg::Self_EnsureSave(void)
{
	//ȷ��ͼ�����Ƿ񱣴�
	if (m_vcFilePath.size()==0)
	{
		return FALSE;
	}
	if (m_vcHistoryImg.size()>2)
	{
		if (m_BNoSaved)
		{
//			int tem_nClose = MessageBox(_T("�޸���δ���棡�Ƿ񱣴棿"), _T("����"), MB_YESNO);
			int tem_nClose = MessageBox(m_vcMainLang[10], _T("UDS"), MB_YESNO);
			if (tem_nClose == 6)
			{
				//ȷ������
				CString tem_strNewImgPath = m_vcHistoryImg.back();
				CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
				m_BNoSaved = FALSE;
				Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
			}
			//�����Ƿ񱣴��޸Ķ�Ҫ�������ͼ��
			std::vector<CString>::iterator  item;
			for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end(); item++)
			{
				DeleteFile(*item);
			}
		}
	}
	else if (m_vcHistoryImg.size()==2)
	{
		//ɾ������ͼ��
		DeleteFile(m_vcHistoryImg[1]);
	}

	m_vcHistoryImg.clear();

	return TRUE;
}


void CXRayViewerv10Dlg::Self_CreateLine(void)
{
	CRect  tem_rcPicCtrl;
	m_conPicCtrl.GetClientRect(&tem_rcPicCtrl);

	HDC    hdc = ::GetDC(m_conPicCtrl.GetSafeHwnd());
	SetROP2(hdc, R2_NOTXORPEN);

	HPEN   hpen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	SelectObject(hdc, hpen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));

	MoveToEx(hdc, tem_rcPicCtrl.left, tem_rcPicCtrl.Height()/2, NULL);
	LineTo(hdc, tem_rcPicCtrl.right, tem_rcPicCtrl.Height()/2);

	MoveToEx(hdc, tem_rcPicCtrl.Width()/2, tem_rcPicCtrl.top, NULL);
	LineTo(hdc, tem_rcPicCtrl.Width()/2, tem_rcPicCtrl.bottom);

	::DeleteObject(hpen);
}


void CXRayViewerv10Dlg::Self_UpdateThumb(int index, CString imgpath)
{
	if (index==-1)
	{
		return;
	}
	CString tem_strThumbPath = m_vcThumbPath[index];
	Self_CreateThumb(imgpath, tem_strThumbPath);
	Self_ReplaceImage(m_nThumbWidth, m_nThumbHeight, index);
}


void CXRayViewerv10Dlg::Self_ReplaceImage(int thumbwidth, int thumbheight, int item)
{
	CString    tem_strItemName = m_vcImgName[item];      //��ַ�����ƶ�Ӧvector�д�ŵ��ļ�����ʵ����
	CString    tem_strItemPath = m_vcFilePath[item];
	m_conListCtrl.SetItemText(item, 0, tem_strItemName);

	HBRUSH hBrushBorder    =::CreateSolidBrush(RGB(220, 220, 220));
	HBRUSH hBrushBkground  =::CreateSolidBrush(RGB(255, 255, 255));   
	float fRatio=(float)thumbheight/thumbwidth; 
	RECT rcBorder;
	rcBorder.left=rcBorder.top  =0;
	rcBorder.right              =thumbwidth;
	rcBorder.bottom             =thumbheight;

	int XDest,YDest,nDestWidth,nDestHeight;
	CxImage    image; 
	int nImageType=GetTypeFromFileName(tem_strItemPath);
	image.Load(tem_strItemPath, nImageType);
	float fImgRatio=(float)image.GetHeight()/image.GetWidth();  
	if(fImgRatio>fRatio)
	{
		nDestWidth=(int)thumbheight/fImgRatio;   
		XDest=(thumbwidth-nDestWidth)/2;
		YDest=0;
		nDestHeight=thumbheight;
	}
	else
	{
		XDest=0;
		nDestWidth=thumbwidth;
		nDestHeight=(int)thumbwidth*fImgRatio;  
		YDest=(thumbheight-nDestHeight)/2;
	}

	CClientDC cdc(this);
	HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
	HBITMAP bm=CreateCompatibleBitmap(cdc.m_hDC,thumbwidth,thumbheight);
	HBITMAP pOldBitmapImage=(HBITMAP)SelectObject(hDC,bm);

	::FillRect(hDC,&rcBorder,hBrushBkground);
	image.Stretch(hDC,XDest,YDest,nDestWidth,nDestHeight);
	::FrameRect(hDC,&rcBorder,hBrushBorder);
	SelectObject(hDC,pOldBitmapImage);
	CBitmap bitmap;
	bitmap.Attach(bm);
	m_imagelist.Replace(item,&bitmap,NULL);
	m_conListCtrl.RedrawItems(item, item);           //ListCtrl�ػ��Ӧ��ǰҳ����Item������
	DeleteDC(hDC);
	DeleteObject(bm);

	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBkground);	

}


int CXRayViewerv10Dlg::Self_Test(void)
{
	CRect   tem_rcOcx;

	CRect   tem_rcOldVideo;     //ԭ����ͷ����
	CRect   tem_rcOldRect;      //ԭ��������
	CRect   tem_rcNewVideo;     //������ͷ����

	//ԭ��Ƶ����Ŀ�����
	int   tem_nOVWidth  = tem_rcOldVideo.Width();
	int   tem_nOVHeight = tem_rcOldVideo.Height();

	//����Ƶ����Ŀ�����
	int   tem_nNVWidth  = tem_rcNewVideo.Width();
	int   tem_nNVHeight = tem_rcNewVideo.Height();

	//ԭ��������Ŀ���
	int   tem_nORWidth  = tem_rcOldRect.Width();
	int   tem_nORHeight= tem_rcOldRect.Height();

	//�²�������Ŀ���
	int   tem_nNRWidth  = (int)(tem_nORHeight*tem_nNVWidth/tem_nOVHeight*1.0);
	int   tem_nNRHeight = (int)(tem_nORWidth*tem_nNVHeight/tem_nOVWidth*1.0);

	//�²����������ʼ������
	int   tem_nNRX      = tem_rcNewVideo.left + ((tem_rcOldVideo.bottom-tem_rcOldRect.bottom)*tem_rcNewVideo.Width()/tem_rcOldVideo.Height()*1.0);
	int   tem_nNRY      = tem_rcNewVideo.top + ((tem_rcOldRect.left-tem_rcOldVideo.left)*tem_rcNewVideo.Height()/tem_rcOldVideo.Width()*1.0);

	return 0;
}


afx_msg LRESULT CXRayViewerv10Dlg::OnRefreshimg(WPARAM wParam, LPARAM lParam)
{
// 	CRect rtlbl; 
// 	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&rtlbl); 
// 	ScreenToClient(&rtlbl); //ת���ͻ��˽���
// 	InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
// 	UpdateWindow();
	return 0;
}


void CXRayViewerv10Dlg::OnBnClickedBtnDrag()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_dlgOne.Self_SetCtrlState();
	m_nViewMode = 2;
	CString  tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nViewMode);
	::WritePrivateProfileString(_T("BaseSet"), _T("ViewMode"), tem_strValue, m_strIniPath);

	::SendMessage(this->m_hWnd, WM_SCANSET, 23, 0);
}


CString CXRayViewerv10Dlg::Self_Img2DCM(CString imgpath)
{
	char*  tem_cName  = NULL;
	char*  tem_cId    = NULL;
	char*  tem_cBirth = NULL;
	char*  tem_cSex   = NULL;
	char*  tem_cDName = NULL;
	char*  tem_cDate  = NULL;
	char*  tem_cTime  = NULL;

	CString  tem_strInput  = imgpath;
	CString  tem_strOutPut = _T("");

	USES_CONVERSION; 
	//��������ͼ�������ͼ���·��
	LPWSTR  tem_lpInput = tem_strInput.GetBuffer();
	tem_strInput.ReleaseBuffer();
	PathRemoveExtension(tem_lpInput);
	tem_strOutPut = tem_lpInput;
	tem_strOutPut+= _T(".dcm");
	tem_strInput  = imgpath;
	
	
	IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
	tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

	 
	char*   tem_cSrc = T2A(tem_strInput);
	char*   tem_cDst = T2A(tem_strOutPut);
	tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);
	
	DeleteFile(tem_strInput);
	
	return tem_strOutPut;
}


int CXRayViewerv10Dlg::Self_GetSpyRes(int diyvalue)
{
	int     tem_nMaxIndex     = 0;
	long    tem_lValue1       = -1;
	long    tem_lValue2       = 10;
	long    tem_lMiddle       = 0;

	BOOL    tem_BMark         = TRUE;

	CString tem_strResolution = _T("");
	int    tem_nResCount = m_conVideoCtrl.GetResCount();  //�豸����������
	std::vector<int>  tem_vcResIndex;
	std::vector<int>  tem_vcResValue;

	tem_vcResIndex.clear();
	tem_vcResValue.clear();

	for (int i=0; i<tem_nResCount; i++)
	{

		tem_strResolution = m_conVideoCtrl.GetResolution(i);
		int        tem_nFindIndex = tem_strResolution.Find('*');
		CString    tem_strFirst = tem_strResolution;
		CString    tem_strLast  = tem_strResolution;
		tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
		tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
		int        tem_nFirst   = _ttoi(tem_strFirst);
		int        tem_nLast    = _ttoi(tem_strLast);

		tem_lValue1   = tem_nFirst*tem_nLast;
		tem_nMaxIndex = i;

		tem_vcResValue.push_back(tem_lValue1);
		tem_vcResIndex.push_back(i);
	}
	//��vector��������ͬʱ������Ӧ��Ӧ�ĵ�ֵ,��С����
	for (int i=0; i<tem_vcResValue.size()-1; i++)
	{
		for (int j=0; j<tem_vcResValue.size()-i-1; j++)
		{
			if (tem_vcResValue[j]>tem_vcResValue[j+1])
			{
				int tem_nValue = tem_vcResValue[j];
				tem_vcResValue[j] = tem_vcResValue[j+1];
				tem_vcResValue[j+1] = tem_nValue;
				int tem_nIndex = tem_vcResIndex[j];
				tem_vcResIndex[j] = tem_vcResIndex[j+1];
				tem_vcResIndex[j+1] = tem_nIndex;
			}
		}
	}

	int  tem_nSecond = tem_vcResIndex.at(tem_vcResIndex.size()-diyvalue);

	return tem_nSecond;
}


CString CXRayViewerv10Dlg::Self_InterPolateImage(CString srcImage, CString dstImage, int index)
{
	
	int       tem_nInterpolateIndex = index;
	int       tem_nGoalResoW        = 0;          //Ŀ��ֱ���
	int       tem_nGoalResoH        = 0;
	float     tem_fRateW            = 0;          //ת���ʿ�
	float     tem_fRateH            = 0;

	long*     tem_lWidth;
	tem_lWidth  = new long;
	long*     tem_lHeight;  
	tem_lHeight = new long;
	float     tem_fWidth;
	float     tem_fHeight;

	CString   tem_strSrcImage       = srcImage;     //ԭͼ·��
	CString   tem_strDstImage       = dstImage;     //Ŀ��ͼ·��

	CxImage   tem_cxSrcImage;
	tem_cxSrcImage.Load(tem_strSrcImage);
	m_conVideoCtrl.GetCurResolution(tem_lWidth, tem_lHeight);
	tem_fWidth  = *tem_lWidth;
	tem_fHeight = *tem_lHeight;
	

	tem_fRateW = 4480/(4032*1.0);
	tem_fRateH = 3360/(3024*1.0);


	tem_nGoalResoW = (int)(tem_cxSrcImage.GetWidth()*tem_fRateW );
	tem_nGoalResoH = (int)(tem_cxSrcImage.GetHeight()*tem_fRateH);

	tem_cxSrcImage.Resample(tem_nGoalResoW, tem_nGoalResoH);

	//�ж�ͼ���ʽ
	int      tem_nFormat   = -1;
	CString  tem_strFormat = _T("");
	tem_strFormat = srcImage;
	tem_nFormat = tem_strFormat.ReverseFind('.');
	tem_strFormat = tem_strFormat.Mid(tem_nFormat+1);
	tem_strFormat.MakeLower();
	if (tem_strFormat == _T("bmp"))
	{
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_BMP);
	}
	else if (tem_strFormat == _T("jpg"))
	{
		tem_cxSrcImage.SetJpegQuality(100);
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_JPG);
	}
	else if (tem_strFormat == _T("tif"))
	{
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_TIF);
	}
	else if (tem_strFormat == _T("png"))
	{
		tem_cxSrcImage.SetJpegQuality(50);
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_PNG);
	}

	tem_cxSrcImage.Destroy();
	
	return tem_strDstImage;
	

}


CString CXRayViewerv10Dlg::Self_GetPdfFromImg(CString srcImg, CString dstImg)
{
	CString   tem_strInputPath  = srcImg;     //����ͼ��·��
	CString   tem_strOutputPath = dstImg;     //����PDF·��


	//����PDF--------
	int       doc, page, image, code, pagenum=2;
	wstring    outfile;
	outfile = tem_strOutputPath.GetBuffer(0);
	tem_strOutputPath.ReleaseBuffer();
	PDFlib*    pPdf;
	pPdf = new PDFlib;
	try
	{
		//		pPdf->set_parameter("License", "w700602-009100-731090-Y6WPH2-5SE4A2");
		pPdf->set_parameter(_T("nodemostamp"), _T("false"));
		pPdf->set_parameter(_T("errorpolicy"), _T("return"));
		//		pPdf->set_parameter(_T("hypertextencoding"), _T("host"));

		code = pPdf->begin_document(outfile, _T(""));
		if (code == -1)
		{
			return srcImg;
		}
		//����PDF������Ϣ******************************************************
		pPdf->set_info(_T("Creator"), _T("SmartScan"));   
		pPdf->set_info(_T("Author"), _T("UDS"));   
		pPdf->set_info(_T("Title"), _T("UDSPDF")); 
		pPdf->set_info(_T("Subject"), _T("ɨ���ĵ�"));

		//ͼƬ����***********************************************************
		{

			wstring sFilePath(tem_strInputPath.GetBuffer());
			image = pPdf->load_image(_T("auto"), sFilePath, _T(""));
			pPdf->begin_page_ext(10, 10, _T(""));
			pPdf->fit_image(image, 0, 0, _T("adjustpage dpi=0"));  //����ͼ��
			pPdf->close_image(image);
			pPdf->end_page_ext(_T(""));
		}		
		pPdf->end_document(_T(""));	
	}
	catch (PDFlib::Exception e)
	{
		int     num=-1;
		wstring  str;
		CString str2, str3;
		str = e.get_errmsg();
		num = e.get_errnum();
		str2 = str.c_str();
		str3.Format(_T("%d"), num);
	}

	return tem_strOutputPath;
}


BOOL CXRayViewerv10Dlg::Self_FilterRes(CString res)
{
	long        tem_lValue     = 0;
	BOOL       tem_BMark      = FALSE;
	CString tem_strResolution = res;
	int        tem_nFindIndex = tem_strResolution.Find('*');
	CString    tem_strFirst = tem_strResolution;
	CString    tem_strLast  = tem_strResolution;
	tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
	tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
	int        tem_nFirst   = _ttoi(tem_strFirst);
	int        tem_nLast    = _ttoi(tem_strLast);

	tem_lValue   = tem_nFirst*tem_nLast;
	if (tem_lValue>=5000000)
	{
		tem_BMark = TRUE;
	} 
	
	return tem_BMark;
}

//valueĿ��ֵ��������Ԥ��ֵ��src����ԭֵ
void CXRayViewerv10Dlg::AdjustRelay(int value, int src)
{
	
	int tem_nDeviceHandle;
	struct usb_relay_device_info *tem_pDeviceList;
	usb_relay_init();
	tem_pDeviceList = usb_relay_device_enumerate();
	if (tem_pDeviceList==0)
	{
		return;
	}
	tem_nDeviceHandle = usb_relay_device_open(tem_pDeviceList);

//  if (value>0)
	if (value>src)
	{
		for (int i=0; i<(value-src); i++)
		{
			//����--------------------------------------------------------
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		}	
	} 
	else
	{
		for (int i=0; i<(src-value); i++)
		{
			//����---------------------------------------------------------
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_open_one_relay_channel(tem_nDeviceHandle,2);

			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,1);
			usb_relay_device_close_one_relay_channel(tem_nDeviceHandle,2);
		}
	}
	usb_relay_device_close(tem_nDeviceHandle);	
}

#include "MMsystem.h"   //��ʱ����,���Ⱥ���
#pragma comment(lib, "winmm.lib")
void CXRayViewerv10Dlg::Self_TimeDelay(int time_ms)
{
	DWORD    tem_dTimeBegin = timeGetTime();
	DWORD    tem_dTimeEnd   = 0;
	do 
	{
		tem_dTimeEnd = timeGetTime();
	} while (tem_dTimeEnd-tem_dTimeBegin<=time_ms);
}


Mat CXRayViewerv10Dlg::Self_DrawArrow(Mat img, CRect showRect, CRect cropRect, int linewidth, COLORREF linecolor)
{
	CRect   tem_rcShow = showRect;
	CRect   tem_rcCrop = cropRect;
	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //������ʾ����
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //������ʾ�߶�
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //��ʾ����
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //��ʾ�߶�

	if (tem_rcCrop.left==tem_rcCrop.right || tem_rcCrop.top==tem_rcCrop.bottom)
	{
		return img;
	}

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //����������
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	int    tem_nDstWidth   = img.cols* tem_fXPropertion;
	int    tem_nDstHeith   = img.rows*tem_fYPropertion;
	cv::Point  tem_ptNewOri(tem_nDstWidth, tem_nDstHeith);

	tem_fXPropertion     = (tem_rcCrop.right-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);         //�յ��������
	tem_fYPropertion     = (tem_rcCrop.bottom-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	tem_nDstWidth   = img.cols* tem_fXPropertion;
	tem_nDstHeith   = img.rows*tem_fYPropertion;
	cv::Point  tem_ptNewEnd(tem_nDstWidth, tem_nDstHeith);


	Self_ClearPicCtrl();
	
	Mat    tem_cvMidImage(img);
	int  tem_nRed   = GetRValue(linecolor);
	int  tem_nGreen = GetGValue(linecolor);
	int  tem_nBlue  = GetBValue(linecolor);

	
	tem_cvMidImage = drawArrow(img, tem_ptNewOri, tem_ptNewEnd, m_nArrowLen, m_nArrowAngle, Scalar(tem_nBlue, tem_nGreen, tem_nRed), m_nLineWidth, CV_AA);
	
	return tem_cvMidImage;


	/*
	CPoint    p1     = CPoint(50, 50);
	CPoint    p2     = CPoint(100, 100);
	double    theta  = 30;
	int       length = 50;



	theta=3.1415926*theta/180;//ת��Ϊ����
	double Px,Py,P1x,P1y,P2x,P2y;
	//��P2Ϊԭ��õ�����P2P1��P��
	Px=p1.x-p2.x;
	Py=p1.y-p2.y;
	//����P��תtheta�ǵõ�����P1
	P1x=Px*cos(theta)-Py*sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	//����P��ת-theta�ǵõ�����P2
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	//�����������ƶ�����
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*length/x1;
	P1y=P1y*length/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	P2y=P2y*length/x2;
	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	CClientDC dc(this);//��ȡ�ͻ�����DC
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(p1.x,p1.y);
	dc.LineTo(p2.x,p2.y);
	dc.SelectObject(&pen1);
	dc.MoveTo(p2.x,p2.y);
	dc.LineTo(P1x,P1y);
	dc.MoveTo(p2.x,p2.y);
	dc.LineTo(P2x,P2y);
	dc.SelectObject(oldpen);
	*/
}


//����˵����Matͼ�� ͼ���ϵ�������㣬 ͼ���ϵ������յ㣬 ��ͷͷ�����۳��ȣ� ��ͷ���ۼнǣ� ����ɫ�� �߿��� ����
Mat CXRayViewerv10Dlg::drawArrow(Mat img, cv::Point pStart, cv::Point pEnd, int len, int alpha, cv::Scalar& color, int thickness, int lineType)
{
	const double tem_PI = 3.1415926;

	cv::Point arrow;
	double angle = atan2((double)(pStart.y - pEnd.y), (double)(pStart.x - pEnd.x));
	line(img, pStart, pEnd, color, thickness, lineType);

	//������Ǳߵ���һ�˵Ķ˵�λ�ã�����Ļ��������Ҫ����ͷ��ָ��Ҳ����pStart��pEnd��λ�ã� 
	arrow.x = pEnd.x + len * cos(angle + tem_PI * alpha / 180);
	arrow.y = pEnd.y + len * sin(angle + tem_PI * alpha / 180);
	line(img, pEnd, arrow, color, thickness, lineType);

	arrow.x = pEnd.x + len * cos(angle - tem_PI * alpha / 180);
	arrow.y = pEnd.y + len * sin(angle - tem_PI * alpha / 180);
	line(img, pEnd, arrow, color, thickness, lineType);
	
	return img;
}


Mat CXRayViewerv10Dlg::Self_AddText(Mat src, CRect showRect, CRect cropRect, CString textinfo, COLORREF color, CString font, int fontsize, bool bold, bool italic)
{
	CRect   tem_rcShow = showRect;
	CRect   tem_rcCrop = cropRect;
	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //������ʾ����
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //������ʾ�߶�
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //��ʾ����
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //��ʾ�߶�

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //����������
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	int    tem_nDstWidth   = src.cols* tem_fXPropertion;
	int    tem_nDstHeith   = src.rows*tem_fYPropertion;
	

	wchar_t*    tem_wsInfo = textinfo.GetBuffer();                //����
	int         tem_nRed   = GetRValue(color);                    //��ɫ
	int         tem_nGreen = GetGValue(color);
	int         tem_nBlue  = GetBValue(color);
	wchar_t*    tem_wsFont = m_strFont.GetBuffer();
	int         tem_nSize  = fontsize;
	
	
	int   iSize;
	char* pszMultiByte;
	char* pszFont;

	//���ؽ����ַ������軺�����Ĵ�С���Ѿ������ַ���β��'\0'
	iSize = WideCharToMultiByte(CP_ACP, 0, tem_wsInfo, -1, NULL, 0, NULL, NULL); 
	pszMultiByte = (char*)malloc(iSize*sizeof(char)); //����Ҫ pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
	WideCharToMultiByte(CP_ACP, 0, tem_wsInfo, -1, pszMultiByte, iSize, NULL, NULL);

	iSize = WideCharToMultiByte(CP_ACP, 0, tem_wsFont, -1, NULL, 0, NULL, NULL); 
	pszFont = (char*)malloc(iSize*sizeof(char)); //����Ҫ pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
	WideCharToMultiByte(CP_ACP, 0, tem_wsFont, -1, pszFont, iSize, NULL, NULL);

	putTextEx(src, pszMultiByte, cv::Point(tem_nDstWidth, tem_nDstHeith), Scalar(tem_nBlue, tem_nGreen, tem_nRed), tem_nSize, pszFont, m_BItalic, false, m_BBold);    //Scalar(B, G, R)

	

	return src;
}


void CXRayViewerv10Dlg::GetStringSize(HDC hDC, const char* str, int* w, int* h)
{
	SIZE size;
	GetTextExtentPoint32A(hDC, str, strlen(str), &size);
	if (w != 0) *w = size.cx;
	if (h != 0) *h = size.cy;
}


void CXRayViewerv10Dlg::putTextEx(Mat& dst, const char* str, cv::Point org, Scalar color, int fontSize, const char* fn, bool italic, bool underline, bool bold)
{
	CV_Assert(dst.data != 0 && (dst.channels() == 1 || dst.channels() == 3));

	int x, y, r, b;
	if (org.x > dst.cols || org.y > dst.rows) return;
	x = org.x < 0 ? -org.x : 0;
	y = org.y < 0 ? -org.y : 0;

	LOGFONTA lf;
	lf.lfHeight = -fontSize;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
//	lf.lfWeight = 5;                      //������Ϊ��ϸ0~1000���������Ϊ400���Ӵ�Ϊ700
	if (bold)
	{
		lf.lfWeight = 700;
	}
	else
	{
		lf.lfWeight = 400;
	}
	
	lf.lfItalic = italic;   //б��
	lf.lfUnderline = underline; //�»���
	lf.lfStrikeOut = 0;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = 0;
	strcpy_s(lf.lfFaceName, fn);

	HFONT hf = CreateFontIndirectA(&lf);
	HDC hDC = CreateCompatibleDC(0);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hf);

	int strBaseW = 0, strBaseH = 0;
	int singleRow = 0;
	char buf[1 << 12];
	strcpy_s(buf, str);
	char *bufT[1 << 12];  // ������ڷָ��ַ�����ʣ����ַ������ܻᳬ����
	//��������
	{
		int nnh = 0;
		int cw, ch;

		const char* ln = strtok_s(buf, "\n",bufT);
		while (ln != 0)
		{
			GetStringSize(hDC, ln, &cw, &ch);
			strBaseW = max(strBaseW, cw);
			strBaseH = max(strBaseH, ch);

			ln = strtok_s(0, "\n",bufT);
			nnh++;
		}
		singleRow = strBaseH;
		strBaseH *= nnh;
	}

	if (org.x + strBaseW < 0 || org.y + strBaseH < 0)
	{
		SelectObject(hDC, hOldFont);
		DeleteObject(hf);
		DeleteObject(hDC);
		return;
	}

	r = org.x + strBaseW > dst.cols ? dst.cols - org.x - 1 : strBaseW - 1;
	b = org.y + strBaseH > dst.rows ? dst.rows - org.y - 1 : strBaseH - 1;
	org.x = org.x < 0 ? 0 : org.x;
	org.y = org.y < 0 ? 0 : org.y;

	BITMAPINFO bmp = { 0 };
	BITMAPINFOHEADER& bih = bmp.bmiHeader;
	int strDrawLineStep = strBaseW * 3 % 4 == 0 ? strBaseW * 3 : (strBaseW * 3 + 4 - ((strBaseW * 3) % 4));

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = strBaseW;
	bih.biHeight = strBaseH;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;
	bih.biSizeImage = strBaseH * strDrawLineStep;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	void* pDibData = 0;
	HBITMAP hBmp = CreateDIBSection(hDC, &bmp, DIB_RGB_COLORS, &pDibData, 0, 0);

	CV_Assert(pDibData != 0);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);

	//color.val[2], color.val[1], color.val[0]
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, 0);
	//SetStretchBltMode(hDC, COLORONCOLOR);

	strcpy_s(buf, str);
	const char* ln = strtok_s(buf, "\n",bufT);
	int outTextY = 0;
	while (ln != 0)
	{
		TextOutA(hDC, 0, outTextY, ln, strlen(ln));
		outTextY += singleRow;
		ln = strtok_s(0, "\n",bufT);
	}
	uchar* dstData = (uchar*)dst.data;
	int dstStep = dst.step / sizeof(dstData[0]);
	unsigned char* pImg = (unsigned char*)dst.data + org.x * dst.channels() + org.y * dstStep;
	unsigned char* pStr = (unsigned char*)pDibData + x * 3;
	for (int tty = y; tty <= b; ++tty)
	{
		unsigned char* subImg = pImg + (tty - y) * dstStep;
		unsigned char* subStr = pStr + (strBaseH - tty - 1) * strDrawLineStep;
		for (int ttx = x; ttx <= r; ++ttx)
		{
			for (int n = 0; n < dst.channels(); ++n){
				double vtxt = subStr[n] / 255.0;
				int cvv = vtxt * color.val[n] + (1 - vtxt) * subImg[n];
				subImg[n] = cvv > 255 ? 255 : (cvv < 0 ? 0 : cvv);
			}

			subStr += 3;
			subImg += dst.channels();
		}
	}


	SelectObject(hDC, hOldBmp);
	SelectObject(hDC, hOldFont);
	DeleteObject(hf);
	DeleteObject(hBmp);
	DeleteDC(hDC);
}