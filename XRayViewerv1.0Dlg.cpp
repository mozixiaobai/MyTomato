
// XRayViewerv1.0Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "XRayViewerv1.0Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString  g_strProXmlPath;        //透射稿默认模板
CString  g_strDocXmlPath;        //反射稿默认模板
std::vector<CString> g_vcRes;
std::vector<int>     g_vcSlid;
int g_nGrayValue[18][2]={{169,42}, {100,32}, {106,33}, {112,34}, {119,35}, {125,36}, {131,37}, {137,38}, {144,39}, {150,40},{156,41}, {162,42}, {169,43}, {175,44}, {181,45}, {187,46}, {194,47}, {200,48}};
CString  g_strEditInfo;


//加载调焦dll
typedef long(*pcamInitCameraLib)(); pcamInitCameraLib  camInitCameraLib;           //初始化
typedef long(*pcamGetDevCount)(long&); pcamGetDevCount camGetDevCount;             //摄像头个数
typedef long(*pcamGetDevPid)(long, char*); pcamGetDevPid camGetDevPid;             //PID
typedef long(*pcamGetDevVid)(long, char*); pcamGetDevVid camGetDevVid;             //VID
typedef char*(*pcamGetDevName)(long); pcamGetDevName   camGetDevName;              //获取设备名称
typedef long(*pcamSetFocusValue)(long, long); pcamSetFocusValue camSetFocusValue;  //设置焦点值

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CXRayViewerv10Dlg 对话框




CXRayViewerv10Dlg::CXRayViewerv10Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXRayViewerv10Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_BShowTab    = TRUE;
	m_BShowList   = TRUE;
	m_BFullScreen = FALSE;
	m_BShowPicCtrl= FALSE;
	m_BFirstCap   = TRUE;

	
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
ON_MESSAGE(WM_SETTEXT, &CXRayViewerv10Dlg::OnSettext)
ON_MESSAGE(WM_THREADOVER, &CXRayViewerv10Dlg::OnThreadover)
END_MESSAGE_MAP()


// CXRayViewerv10Dlg 消息处理程序

BOOL CXRayViewerv10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

//	ShowWindow(SW_MAXIMIZE);     //无最大化按钮，窗口最大化会遮挡任务栏， 因此采用其他方法替代
	CRect rcWorkArea; 
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0); 
	MoveWindow(&rcWorkArea); 


	// TODO: 在此添加额外的初始化代码
	/***********************************
	* 0、配置GDI+
	* 1、变量初始化
	* 2、配置文件路径
	* 3、启动Camera
	* 4、读取配置文件
	* 5、设置分辨率
	*    设置裁切框
	* 6、确定Camera支持哪些属性，并导出至xml
	* 7、加载模板，并设置Camera
	* 8、Tab Ctrl初始化
	* 9、读取文件格式
	* 10、菜单初始化
	* 11、判断默认目录是否存在
	* 12、界面美化
	*
	***********************************/
	/*0、配置GDI+*/
	GdiplusStartupInput m_StartupInput;
	ULONG_PTR m_pGdiToKen;
	GdiplusStartup(&m_pGdiToKen, &m_StartupInput, NULL);


	/*1、变量初始化*/
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
	m_strFont     = _T("宋体");
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

	m_nIntervalTime = 1000;
	

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
	

	/*2、获取配置、模板目录*/
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
//	g_strProXmlPath += _T("默认.xml");
//	g_strProXmlPath += _T("Default.xml");
	g_strProXmlPath += _T("透射稿默认.xml");

	g_strDocXmlPath  = m_strXmlDoc;
	g_strDocXmlPath += _T("\\");
	g_strDocXmlPath += _T("反射稿默认.xml");

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

	Self_ReadLanguageXml(m_strLangXmlPath, m_vcMainLang, _T("Main"));    //获取Main节点下的名称
	Self_ReadLanguageXml(m_strLangXmlPath, m_vcTipsLge, _T("Tips"));
	


//	Self_FindTems(m_strXmlDoc);

	/*3、启动Camera*/
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

	/*4、读取配置文件*/
	Self_ReadIni(m_strIniPath);
	Self_ReadWaterIni(m_strIniPath);

	/*5、设置分辨率、旋转方向、拍照模式*/
	//判断保存的分辨率是否是插值分辨率

	

	int  tem_nResNum = m_conVideoCtrl.GetResCount();
	m_nInterpolateReso = tem_nResNum;
	for (int i=0; i<tem_nResNum; i++)
	{
		CString tem_strResolution = m_conVideoCtrl.GetResolution(i);
		//判断分辨率是否<500W,小于500W则直接过滤
		if (Self_FilterRes(tem_strResolution))
		{
			g_vcRes.push_back(tem_strResolution);
		}	
	}
	g_vcRes.push_back(_T("4480×3360"));

	if (m_nLastRes == m_nInterpolateReso)
	{
	 	//获取最大分辨率索引，并设置为最大分辨率
	 	int  tem_nMaxIndex = Self_GetSpyRes(1);
	 	m_conVideoCtrl.SetResolution(tem_nMaxIndex);
	}
	else
	{
	 	//设置为上次使用的分辨率
	 	m_conVideoCtrl.SetResolution(m_nLastRes);
	}

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

	//默认灰度拍照
	m_conVideoCtrl.SetColorMode(2);

	//	m_conVideoCtrl.AdjuestImageCrop(TRUE);    //设置自动裁切
	//	m_conVideoCtrl.ManualImageCrop(TRUE);     //设置手动裁切


	//说明：将固定裁切框的设置放在摄像头初始化完成的事件中


	/*6、确定Camera属性*/
	if (!PathFileExists(g_strProXmlPath))
	{
		Self_EnsureItems();
	}
	if (!PathFileExists(g_strDocXmlPath))
	{
		Self_EnsureItems2();     //导出反射稿默认模板
	}

	/*7、加载模板，设置Camera*/
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
	if (m_strLastTem == _T("透射稿"))
	{
		Self_ReadXml(g_strProXmlPath);
	} 
	else
	{
		Self_ReadXml(g_strDocXmlPath);
	}


	/*8、Tab Ctrl*/
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
	/*9、读取文件格式*/
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

	/*10、菜单初始化*/
	m_ListMenu.LoadMenuW(IDR_MENU_LIST);

	/*11*/
	if (!PathFileExists(m_strSaveDoc))
	{
		//不存在，获取桌面路径，并修改默认路径参数
		TCHAR MyDir[_MAX_PATH];  
		SHGetSpecialFolderPath(this->GetSafeHwnd(),MyDir,CSIDL_DESKTOP,0);
		m_strSaveDoc  = MyDir;
		m_strSaveDoc += _T("\\");
	}
	GetDlgItem(IDC_STA_CURDOCPATH)->SetWindowText(m_strSaveDoc);
	::WritePrivateProfileString(_T("BaseSet"), _T("SaveDoc"), m_strSaveDoc, m_strIniPath);

	GetDlgItem(IDC_STA_CURDOC)->SetWindowText(m_vcMainLang[3]);

	/*12、界面美化*/
	//a、ListCtrl背景设置
	m_conListCtrl.SetBkColor(m_clrCtrlColor);

	//b、对话框背景设置
	CDialogEx::SetBackgroundColor(m_clrBackColor);
	LoadPicture(m_imgBK, IDB_PNG_BKBLACK, _T("PNG"));

	//c、按钮图标
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

	/*13、设置摄像头焦点*/
	//a、变量初始化--------------------------
	m_hDllInst = LoadLibrary(_T("CmCapture.dll"));
	if (m_hDllInst)
	{
		//1、加载dll函数---------------------------------------------------------------------
		camInitCameraLib = (pcamInitCameraLib)GetProcAddress(m_hDllInst, "camInitCameraLib");
		camGetDevPid = (pcamGetDevPid)GetProcAddress(m_hDllInst, "camGetDevPid");
		camGetDevVid = (pcamGetDevVid)GetProcAddress(m_hDllInst, "camGetDevVid");
		camGetDevCount = (pcamGetDevCount)GetProcAddress(m_hDllInst, "camGetDevCount");
		camGetDevName = (pcamGetDevName)GetProcAddress(m_hDllInst, "camGetDevName");
		camSetFocusValue = (pcamSetFocusValue)GetProcAddress(m_hDllInst, "camSetFocusValue");

		//2、获取当前设备索引-----------------------------------------------------------------
		int tem_nRC = -1;
		tem_nRC = camInitCameraLib();
		for (int i=0; i<tem_nDevNum; i++)
		{
			char* tem_cCamName = camGetDevName(i);
			CString tem_strCamName(tem_cCamName);
			if (tem_strCamName.Find(_T("Document Scanner")) != -1)
			{
				m_nDevIndex = i;
				break;
			}
		}

		
		tem_nRC = camSetFocusValue(m_nDevIndex, m_nFocusValue);
	}

	/*14、计算快门曲线*/
	/*移交至子程序处理*/
	/*
	float tem_fShutterL, tem_fShutterN, tem_fShutterH;

	//a、低密度快门
	tem_fShutterL = tem_fShutterN = tem_fShutterH = 0.0;
	tem_fShutterL = Self_GetShutter(m_nLowLightL);
	tem_fShutterN = Self_GetShutter(m_nNorLightL);
	tem_fShutterH = Self_GetShutter(m_nHigLightL);
	m_vcLShutter.push_back(tem_fShutterL);
	m_vcLShutter.push_back(tem_fShutterN);
	m_vcLShutter.push_back(tem_fShutterH);

	//b、高密度快门
	tem_fShutterL = tem_fShutterN = tem_fShutterH = 0.0;
	tem_fShutterL = Self_GetShutter(m_nLowLight);
	tem_fShutterN = Self_GetShutter(m_nNorLight);
	tem_fShutterH = Self_GetShutter(m_nHigLight);
	m_vcHShutter.push_back(tem_fShutterL);
	m_vcHShutter.push_back(tem_fShutterN);
	m_vcHShutter.push_back(tem_fShutterH);
	*/

	/*15、计算拍摄时间间隔*/
//  	Self_TimeDelay(5*100);  //500ms延时，否则摄像头未准备好，崩溃
	if (m_nIniTime == 0)
	{
		m_nIntervalTime = Self_GetIntervalTime();
	} 
	else
	{
//		m_nIntervalTime = (21-m_nIniTime)*1000;
		m_nIntervalTime = m_nIniTime*1000;
	}
 	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CXRayViewerv10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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
		dcMem.FillSolidRect(tem_rcClient, RGB(72, 77, 91));	//设置画布颜色
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CXRayViewerv10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH CXRayViewerv10Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID()==IDC_STA_CURDOC || pWnd->GetDlgCtrlID()==IDC_STA_CURDOCPATH)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_clrTextColor);
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CXRayViewerv10Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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
			//空格键
			if (m_BSpaceDown)
			{
				::SendMessage(this->m_hWnd, WM_SCANSET, 11, 0);
				m_BSpaceDown = FALSE;
			}
			return TRUE;
			break;
		case VK_ESCAPE:
			//退出键
			if (m_BEscDown)
			{
				//判断此时是全屏还是普通状态
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
			//回车键
			return TRUE;
			break;
		case VK_DELETE:
			//删除
			break;
		case 0x5A:
			if (m_BCtrl)
			{
				//手动裁切
				m_BCtrl = FALSE;
				m_conVideoCtrl.ManualImageCrop(TRUE);
				m_conVideoCtrl.SetMessage(1);
			}
			break;
		case VK_F1:
			if (m_BCtrl)
			{
				//手动裁切
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
		case VK_F1:
			m_BCtrl = TRUE;
			::SendMessage(this->m_hWnd, WM_SCANSET, 16, 0);
			break;
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

	//鼠标在哪，将焦点给谁，很方便——————————————————————————
	//对于SliderCtrl——Release消息，则需要考虑屏蔽鼠标滚轮消息
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

	// TODO: 在此处添加消息处理程序代码
	/*先于OnInitDialog执行*/
	if (::IsWindow(GetDlgItem(IDC_TAB_CTRL)->GetSafeHwnd()))
	{	
		if (IsIconic())
		{
			return;
		}

		CClientDC  dc(this);
		int   tem_nOcxWidth;     //用于对其OCX控件下面控件的位置
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
			//扫描正常形态，左中右
			//1、TabCtrl---------------------------------------------------------
			tem_nCx     = 5;
			tem_nCy     = 5;
			tem_nWidth  = (int)((tem_nCellWidth*1.0)*3.2-32);                                    //TabCtrl宽 3-inch
			tem_nHeight = (int)(tem_nScreenHeight - (tem_nCellHeight*1.0)*tem_fOffsetY);       //底部预留0.7-inch, 考虑任务栏遮挡
			GetDlgItem(IDC_TAB_CTRL)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			CRect  tem_rcTab;
			m_conTab.GetClientRect(&tem_rcTab);
			tem_rcTab.top     += 22;
			tem_rcTab.left += 2;

			m_dlgOne.MoveWindow(&tem_rcTab);
//			m_dlgTwo.MoveWindow(&tem_rcTab);
			m_dlgThree.MoveWindow(&tem_rcTab);

			//2、ListCtrl--------------------------------------------------------
			tem_nWidth  = (int)((tem_nCellWidth*1.0)*2.5-32);                                  //TabCtrl宽 2.5-inch
			tem_nHeight = (int)(tem_nScreenHeight - (tem_nCellHeight*1.0)*tem_fOffsetY);       //底部预留0.7-inch, 考虑任务栏遮挡
			tem_nCx     = tem_nScreenWidth - tem_nWidth-5;
			tem_nCy     = 5;
			GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(tem_nCx, tem_nCy, tem_nWidth, tem_nHeight, TRUE);

			//2、OCX-------------------------------------------------------------
			m_conTab.GetClientRect(&tem_rcTab);
			CRect  tem_rcList;
			m_conListCtrl.GetClientRect(&tem_rcList);

			tem_nCx     = tem_rcTab.right + 10;
			tem_nCy     = 5;
			tem_nWidth  = tem_nScreenWidth - (tem_nCx + 15 +tem_rcList.Width());
			tem_nHeight = (int)(tem_nScreenHeight - (tem_nCellHeight*1.0)*tem_fOffsetY - (tem_nCellHeight*1.0)*0.3);     //预留1.5 inch，因为OCX下面还有按钮
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

			//3、按钮-------------------------------------------------------------
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
			//扫描全屏形态

		}
		else if (m_BShowTab && (!m_BShowList))
		{
			//编辑状态，左中
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

	// TODO: 在此处添加消息处理程序代码
	
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
		//显示PicCtrl控件，并加载图像
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_conVideoCtrl.StopRun();
	m_conVideoCtrl.Uninitial();
	FreeLibrary(m_hDllInst);

	//	Self_SetRelayZero();

	//方案一：直接置为1，当外部调节按钮时会出现误差
//	Self_SetRelayValue(1);

	//方案二：先置0，再调一，不会出错，但要关一次
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

	//确定图像处理是否保存
	if (m_vcFilePath.size()==0)
	{
		return;
	}
	if (m_vcHistoryImg.size()>2)
	{
		if (m_BNoSaved)
		{
//			int tem_nClose = MessageBox(_T("修改尚未保存！是否保存？"), _T("保存"), MB_YESNO);
			int tem_nClose = MessageBox(m_vcMainLang[10], _T("UDS"), MB_YESNO);
			if (tem_nClose == 6)
			{
				//确定保存
				CString tem_strNewImgPath = m_vcHistoryImg.back();
				CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
			}
		}
	}

	//删除缓存文件
//	DeleteFile(m_strBufferImgPath);
	if (m_vcHistoryImg.size()>1)
	{
		//逆向删除2后面的所有图像
		std::vector<CString>::iterator iter;
		for (iter=m_vcHistoryImg.begin()+1; iter!=m_vcHistoryImg.end(); iter++)
		{
			DeleteFile(*iter);
		}
	}
	m_vcHShutter.clear();
	m_vcLShutter.clear();

	CDialogEx::OnClose();
}


BOOL CXRayViewerv10Dlg::Self_FindCamera(CString xmlpath)
{
	const char*       tem_cInfo;
	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	//加载xml文件
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//根节点
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

	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("没有找到Template信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strLastTem = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ResIndex"), _T("没有找到ResIndex信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	switch(tem_nRead)
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
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ImgType"), _T("没有找到ImgType信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastImgType = tem_nRead;
	tem_strRead.ReleaseBuffer();


	::GetPrivateProfileString(_T("BaseSet"), _T("PreRotate"), _T("没有找到PreRotate信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastPreRotate = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("MergeMode"), _T("没有找到MergeMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastMergeMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMark"), _T("没有找到WaterMark信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastWaterMark = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("没有找到NameMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("没有找到NameDate信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameDate   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("没有找到NameTime信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameTime   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("没有找到NameDivide信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNameDivide = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("没有找到NamePre1信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre1 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("没有找到NamePre2信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre2 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("没有找到NamePre3信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre3 = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("没有找到NameBegin信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameBegin   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("没有找到NameBegin2信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nNameBegin2   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveDoc"), _T("没有找到主头SaveDoc信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strSaveDoc = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewMode"), _T("没有找到ViewMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_nViewMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewLeft"), _T("没有找到ViewLeft信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_lLeftSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewTop"), _T("没有找到ViewTop信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead  = _ttoi(tem_strRead);
	m_lTopSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewRight"), _T("没有找到ViewRight信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	m_lRightSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewBottom"), _T("没有找到ViewBottom信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_lBottomSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("没有找到SaveTips信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("没有找到SaveFormat信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	::GetPrivateProfileString(_T("BaseSet"), _T("lowvalue"), _T("没有找到lowvalue信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nLowLight   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("higvalue"), _T("没有找到SaveFormat信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nHigLight   = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("VidoeMode"), _T("没有找到VidoeMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nVidoeMode  = tem_nRead;
	tem_strRead.ReleaseBuffer();	

	::GetPrivateProfileString(_T("BaseSet"), _T("FocusValue"), _T("没有找到FocusValue信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nFocusValue = tem_nRead;
	tem_strRead.ReleaseBuffer();	

	::GetPrivateProfileString(_T("BaseSet"), _T("Computer"), _T("没有找到Computer信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_nIniTime    = tem_nRead;
	tem_strRead.ReleaseBuffer();	

	::GetPrivateProfileString(_T("BaseSet"), _T("TextT"), _T("没有找到TextT信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_strRead.ReleaseBuffer();
	int tem_nIndex = tem_strRead.Find(_T("#"));
	CString tem_strIndex = tem_strRead.Mid(0, tem_nIndex);
	tem_nRead = _ttoi(tem_strIndex);
	m_nTextLgtT = tem_nRead;
	tem_strIndex = tem_strRead.Mid(tem_nIndex+1);
	tem_nRead = _ttoi(tem_strIndex);
	m_nTextCstT = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("TextN"), _T("没有找到TextN信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_strRead.ReleaseBuffer();
	tem_nIndex = tem_strRead.Find(_T("#"));
	tem_strIndex = tem_strRead.Mid(0, tem_nIndex);
	tem_nRead = _ttoi(tem_strIndex);
	m_nTextLgtL = tem_nRead;
	tem_strIndex = tem_strRead.Mid(tem_nIndex+1);
	tem_nRead = _ttoi(tem_strIndex);
	m_nTextCstL = tem_nRead;
	tem_strRead.ReleaseBuffer();
}


void CXRayViewerv10Dlg::Self_ReadWaterIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMark"), _T("没有找到WaterMark信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterMark = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterSite"), _T("没有找到主头WaterSite信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterSite = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterSize"), _T("没有找到主头WaterSize信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterSize = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterFont"), _T("没有找到主头WaterFont信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterFont = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterColor"), _T("没有找到主头WaterColor信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strWaterColor = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterInfo"), _T("没有找到主头WaterInfo信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strWaterInfo = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("WaterMode"), _T("没有找到主头WaterMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nWaterMode = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
}


afx_msg LRESULT CXRayViewerv10Dlg::OnScanset(WPARAM wParam, LPARAM lParam)
{
	int tem_nOperation = (int)wParam;    //操作码
	int tem_nInfo      = (int)lParam;    //操作信息
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
			//应用模板
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
		//联动------------------------
//		m_dlgTwo.m_nLastRes = tem_nInfo;
//		m_dlgTwo.Self_UpdateSlider(4);
		//功能实现--------------------
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
			//重新设置灰阶
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
// 				m_conVideoCtrl.ManualImageCrop(TRUE);
// 				m_conVideoCtrl.SetMessage(1);
// 				m_conVideoCtrl.SetRectValue(239+191, 6, 466+191, 119);
// 				m_conVideoCtrl.SetMessage(0);	
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
		//自动亮度
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
		//手动亮度
		if (tem_nInfo!=m_nLastBright)
		{
			m_conVideoCtrl.SetBrightness(tem_nInfo, 0);
			m_nLastBright = tem_nInfo;
// 			m_dlgTwo.m_nLastBright = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(0);
		}
		break;
	case 7:
		//自动对比度
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
		//手动对比度
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
		//将参数恢复至当前模板，即重新加载当前模板


		break;
	case 15:
		//设置裁切框
		
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
		//确认裁切框
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
//			m_nLastRelay = tem_nInfo;
// 			m_dlgTwo.m_nLastLightBox = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(2);
		}
		break;
	//case 19,case 20灯箱两端校准机制，当灯箱亮度为0或100，自动校准；缺点，亮度停留在0或100，灯箱一直校准，造成软件卡顿
	case 19:
		/*取消0校准机制
		Self_SetRelayZero();
		m_dlgTwo.m_nLastLightBox = 0;
		m_dlgTwo.Self_UpdateSlider(2);
		*/
		if (tem_nInfo!=m_nLastRelay)
		{
			Self_SetRelayValue(tem_nInfo);
//			m_nLastRelay = tem_nInfo;
// 			m_dlgTwo.m_nLastLightBox = tem_nInfo;
// 			m_dlgTwo.Self_UpdateSlider(2);
		}
		break;
	case 20:
		/*取消100校准机制
		Self_SetRelay100();
		m_dlgTwo.m_nLastLightBox = 100;
		m_dlgTwo.Self_UpdateSlider(2);
		*/
		if (tem_nInfo!=m_nLastRelay)
		{
			Self_SetRelayValue(tem_nInfo);
//			m_nLastRelay = tem_nInfo;
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
		m_BDOC = FALSE;

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
		//灰阶
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
		m_BDOC = TRUE;

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
			//重新加载透射稿模板
			Self_ReadXml(g_strProXmlPath);
			m_dlgOne.Self_ResetUI(g_strProXmlPath);
		}
		else
		{
			//重新加载反射稿模板
			Self_ReadXml(g_strDocXmlPath);
			m_dlgOne.Self_ResetUI(g_strDocXmlPath);
		}	
		m_nLastTemplate = tem_nInfo;
		break;
	case 28:
		if (tem_nInfo==0)
		{
			//加载透射稿模板
			for (unsigned int i=0; i<m_vcTemPath.size(); i++, tem_nItem++)
			{
				tem_strSlcTem = m_vcTemPath[i];
				if (tem_strSlcTem.Find(_T("透射稿默认")) >= 0)
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
			//加载反射稿模板
			for (unsigned int i=0; i<m_vcTemPath.size(); i++, tem_nItem++)
			{
				tem_strSlcTem = m_vcTemPath[i];
				if (tem_strSlcTem.Find(_T("反射稿默认")) >= 0)
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
		if (tem_nInfo==1)
		{
			//高密度拍摄
			tem_strImgName  = Self_NamingFile(m_nImageCount);
			m_strCurImgName = tem_strImgName;

			m_nCurImgMode   = 1; //高密度标识位

			Self_CaptureImgHDRThread(m_strCurImgName, 1, 0);
// 			Self_CaptureImgHDR(tem_strImgName, 1);
			m_nPrcsIndex = -1;
		} 
		else
		{
			//低密度拍摄
			tem_strImgName  = Self_NamingFile(m_nImageCount);
			m_strCurImgName = tem_strImgName;

			m_nCurImgMode   = 0; //低密度标志位

			Self_CaptureImgHDRThread(m_strCurImgName, 0, 0);
//			Self_CaptureImgHDR(tem_strImgName, 0);
			m_nPrcsIndex = -1;

		}
		
		break;
	case 31:
		if (tem_nInfo==0)
		{
			Self_ReadXml(g_strProXmlPath);
			m_dlgOne.Self_ResetUI(g_strProXmlPath);
			m_dlgOne.Self_SetSlider(g_strProXmlPath);
			m_nLastTemplate = tem_nItem;
			m_BDOC = FALSE;
		}
		else
		{
			Self_ReadXml(g_strDocXmlPath);
			m_dlgOne.Self_ResetUI(g_strDocXmlPath);
			m_dlgOne.Self_SetSlider(g_strDocXmlPath);
			m_nLastTemplate = tem_nItem;
			m_BDOC = TRUE;
		}
		break;
	case 32:
		if (tem_nInfo!=m_nFocusValue)
		{
			camSetFocusValue(m_nDevIndex, tem_nInfo);
			m_nFocusValue = tem_nInfo;
		}
		break;
	case 33:
		if (tem_nInfo != m_nIniTime)
		{
//			m_nIntervalTime = (21-tem_nInfo)*1000;
			m_nIntervalTime = tem_nInfo*1000;
			m_nIniTime = tem_nInfo;
		}
		
		break;
	case 34:
		if (tem_nInfo == 0)
		{
			//自动设置获取平均时间
			m_nIntervalTime = Self_GetIntervalTime();
		}
		else
		{
			//默认时间设置为2秒
//			m_nIntervalTime = (21-tem_nInfo)*1000;
			m_nIntervalTime = tem_nInfo*1000;
			m_nIniTime = tem_nInfo;
		}
		break;
	case 35:
		//设置灯箱亮度以及对比度，并延时
		if (m_nTextCstT!=-1)
		{
			m_conVideoCtrl.SetContrast(m_nTextCstT, 0);
		}
		if (m_nTextLgtT!=-1)
		{
			AdjustRelay(m_nTextLgtT, m_nLastRelay);
		}
		Self_TimeDelay(m_nIntervalTime);
		//拍照
		tem_strImgName  = Self_NamingFile(m_nImageCount);
		Self_CapatureImg(tem_strImgName);
		m_nPrcsIndex = -1;
		//恢复灯箱亮度以及对比度
		if (m_nTextCstT!=-1)
		{
			m_conVideoCtrl.SetContrast(m_nLastContrst, 0);	
		}
		break;
	case 36:
		//设置灯箱亮度以及对比度，并延时
		if (m_nTextCstT!=-1)
		{
			m_conVideoCtrl.SetContrast(m_nTextCstL, 0);
		}
		if (m_nTextLgtT!=-1)
		{
			AdjustRelay(m_nTextLgtL, m_nLastRelay);
		}
		Self_TimeDelay(m_nIntervalTime);
		//拍照
		tem_strImgName  = Self_NamingFile(m_nImageCount);
		Self_CapatureImg(tem_strImgName);
		m_nPrcsIndex = -1;
		//恢复灯箱亮度以及对比度
		if (m_nTextCstT!=-1)
		{
			m_conVideoCtrl.SetContrast(m_nLastContrst, 0);	
		}
		break;
	default:
		break;
	}
	return 0;
}


afx_msg LRESULT CXRayViewerv10Dlg::OnTemplate(WPARAM wParam, LPARAM lParam)
{
	int tem_nOperation = (int)wParam;    //操作码
	int tem_nInfo      = (int)lParam;    //操作信息
	CString*   tem_strInfo;
	tem_strInfo = new CString;
	long       tem_lCur;                 //没有实质作用
	long       tem_lAuto;                //没有实质作用

	switch(tem_nOperation)
	{
	case 0:
		break;
	//CheckBox-对应的消息
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
		/*取消0校准机制
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
		/*取消100校准机制
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
		//更新模板
		m_dlgOne.Self_SlcNewTem();
		break;
	case 21:
		//调用TWO类实现模板保存
		tem_strInfo = (CString*)lParam;
// 		m_dlgTwo.Self_CreateXml(*tem_strInfo);
//		MessageBox(*tem_strInfo);

		break;
	case 22:
		//更新子窗口一的模板列表，并选定该模板
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
		//分辨率切换
		//联动-----------
		m_dlgOne.m_nLastRes = tem_nInfo;
		m_dlgOne.Self_UpdateSlider(4);
		//功能实现-------
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
		//图像格式切换
		//联动--------------
		m_dlgOne.m_nLastImgType = tem_nInfo;
		m_dlgOne.Self_UpdateSlider(5);
		//功能实现-----------
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
			//勾选反射稿
			m_dlgOne.Self_UpdateSlider(6);
		}			
		else
		{
			//取消
			//判断当前的m_nViewMode,不是自动则不管，为自动则置为其他方式

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
		//HDR灰阶
		if (tem_nInfo!=m_nHDRGray)
		{
			m_nHDRGray = tem_nInfo;
		}
		break;
	case 33:
		//HDR逆光对比
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
		//Low光源
		m_nLowLight = tem_nInfo;
		break;
	case  35:
		//Low延时
		m_nLowDelay = tem_nInfo;
		break;
	case 36:
		//Low灰阶
		m_nLowGray = tem_nInfo;
		break;
	case 37:
		//Low逆光对比
		m_nLowBackLgt = tem_nInfo;
		break;
	case 38:
		//High光源
		m_nHigLight = tem_nInfo;
		break;
	case 39:
		//High延时
		m_nHigDelay = tem_nInfo;
		break;
	case 40:
		//High灰阶
		m_nHigGray = tem_nInfo;
		break;
	case 41:
		//Hight逆光对比
		m_nHigBackLgt = tem_nInfo;
		break;
	default:
		break;
	}
	return 0;
}


afx_msg LRESULT CXRayViewerv10Dlg::OnImgprocess(WPARAM wParam, LPARAM lParam)
{
	int      tem_nOperation = (int)wParam;    //操作码
	int      tem_nInfo      = (int)lParam;    //操作信息
	CString  tem_strProcess = _T("");         //用于色彩平衡后重新加载图像
	std::string strTempData;  

	/*case 0:转DCM*/
	int      tem_nRead      = 0;
	CString  tem_strRead    = _T("");
	CString  tem_strDcmPath = _T("");
//	std::vector<CString>::iterator item;
	int      tem_nIndex     = 0;
	switch(tem_nOperation)
	{
	case 0:
		//保存
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			//0)弹出保存格式对话款，选择保存格式
			if (m_BShowTips)
			{
				if (IDOK ==m_dlgSlcFormat.DoModal())
				{
					//重读配置文件
					::GetPrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("没有找到SaveTips信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

					::GetPrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("没有找到SaveFormat信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

			//1)更新buffer图像信息
			m_strBufferImgPath = m_vcHistoryImg.back();
			//2)替换原文件
			CopyFile(m_strBufferImgPath, m_strFilesPath, FALSE);
			std::vector<CString>::iterator item;
			for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end()-1; item++)
			{
				DeleteFile(*item);
			}



			if (m_BSaveFmt)
			{
				//保存为Dcm格式，并更新视图以及其他信息
				
				//4)将图像转为dcm,新的图像路径为m_strBufferImgPath
				Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
				tem_strDcmPath = Self_Img2DCM(m_strFilesPath);

				//5)查找该项索引，并对m_vcFilePath进行更新
				for (item=m_vcFilePath.begin(); item!=m_vcFilePath.end();item++, tem_nIndex++)
				{
					if (*item == m_strFilesPath)
					{
						m_vcFilePath[tem_nIndex] = tem_strDcmPath;
						break;
					}
				}

				//6)更新图像显示，提示dcm不能被处理
				Self_ClearPicCtrl();
				Self_CVShowTipImage(_T("res\\tips.jpg"));
				m_cvSrcImage.release();
				m_cvDstImage.release();
				m_cvLastImg.release();
				m_cvNextImg.release();

				//7)重置vector
				m_vcHistoryImg.clear();



			} 
			else
			{
				//保存为原格式，并更新视图以及其他信息

				//4)更新图像显示
				std::string strTempData = (CStringA)m_strBufferImgPath; 
				m_cvSrcImage.release();
				m_cvDstImage.release();
				m_cvLastImg.release();
				m_cvNextImg.release();
				m_cvSrcImage = imread(strTempData);
				Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
				//5)重置vector
				m_vcHistoryImg.clear();
				m_vcHistoryImg.push_back(m_strFilesPath);
				m_vcHistoryImg.push_back(m_strBufferImgPath);
				//6)更新变量
				m_BNoSaved  = FALSE;
				//7)更新缩略图
				Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
			}
		
			
		}
		break;
	case 1:
		//撤销
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			CString  tem_strNewImg = m_vcHistoryImg.back();
			//删除最后一张图像
			DeleteFile(tem_strNewImg);
			//删除vector最后一个元素
			m_vcHistoryImg.erase(m_vcHistoryImg.end()-1);
			//更新地址
			tem_strNewImg = m_vcHistoryImg.back();		
			std::string tem_sNewImg = (CStringA)tem_strNewImg; 
			m_cvSrcImage  = imread(tem_sNewImg);	//重新加载图像则需要重新计算区域，例如裁切后图像尺寸发生变化
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
		//重置
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		if (m_vcHistoryImg.size()>2)
		{
			//1)重新加载图像
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
			//2)删除其他缓存图像
			std::vector<CString>::iterator item;
			for (item=m_vcHistoryImg.begin()+2; item!=m_vcHistoryImg.end(); item++)
			{
				DeleteFile(*item);
			}
			//3)重置vector
			m_vcHistoryImg.clear();
			m_vcHistoryImg.push_back(m_strFilesPath);
			m_vcHistoryImg.push_back(m_strBufferImgPath);
			//4)更新变量
			m_BNoSaved  = FALSE;
		}
		break;
	case 3:
		//左旋
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//右旋
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//180度旋转
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//水平镜像
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//垂直镜像
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//手动旋转
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//反色
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//锐化
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//裁切
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		m_BNoSaved = TRUE;
		m_BSlcRect = TRUE;
		Self_ResetImageRect();
		//重新加载图像
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);

		break;
	case 12:
		//适应屏幕
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		Self_ClearPicCtrl();
		Self_ResetImageRect();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 13:
		//亮度调整
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			//将亮度调节条置回原位

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
		//对比度调整
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//饱和度调整
		break;
	case 16:
		//Gama调整
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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
		//保存色彩调整
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
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

			//重新加载依次，否则可能出现黑屏
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

			//重新加载依次，否则可能出现黑屏
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

			//重新加载依次，否则可能出现黑屏
			tem_strProcess = m_vcHistoryImg.back();
			strTempData = (CStringA)tem_strProcess; 
			m_cvSrcImage = imread(strTempData);
			Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
			m_BLabel     = FALSE;
			m_nNoteCount = 0;
			break;
		}
		::SetFocus(m_hWnd);        //避免窗口无法响应OnMouseWheel消息
		break;
	case 18:
		//放弃色彩调整
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		if (tem_nInfo == 8)
		{
			//放弃旋转
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
			//放弃色彩平衡
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
			//放弃画框
			for (int i=0; i<m_nNoteCount&&m_vcHistoryImg.size()>2; i++)
			{
				CString  tem_strNewImg = m_vcHistoryImg.back();
				//删除最后一张图像
				DeleteFile(tem_strNewImg);
				//删除vector最后一个元素
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
		::SetFocus(m_hWnd);        //避免窗口无法响应OnMouseWheel消息
		m_BSelectTab = FALSE;
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 19:
		
		if (!m_cvSrcImage.data)
		{
//			MessageBox(_T("加载图像失败！"));
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		//原方法：调用放大缩小函数，实现1:1原图显示
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
		//画框-------------------------------------------
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
		//重新加载图像
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		m_ptNoteSite.x = 0;
		m_ptNoteSite.y = 0;
		break;
	case 21:
		//画箭头
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
		//重新加载图像
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
		//随意画
		if (!m_cvSrcImage.data)
		{
			MessageBox(m_vcMainLang[8], _T("UDS"), MB_OK);
			break;
		}
		
		m_nLineMode = 2;
		m_BNoSaved = TRUE;
		m_BLabel   = TRUE;
		Self_ResetImageRect();
		//重新加载图像
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 25:
		//添加文字标注
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
		//重新加载图像
		Self_ClearPicCtrl();
		Self_ResizeImage(pWnd, m_cvSrcImage);
		Self_ShowMatImage2(m_cvSrcImage, m_rcImageShow);
		break;
	case 26:
		//字体
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
			m_strFont = _T("宋体");
			break;
		case 4:
			m_strFont = _T("楷体");
			break;
		case 5:
			m_strFont = _T("仿宋");
			break;
		case 6:
			m_strFont = _T("黑体");
			break;
		case 7:
			m_strFont = _T("隶书");
			break;
		case 8:
			m_strFont = _T("微软雅黑");
			break;
		case 9:
			m_strFont = _T("新宋体");
			break;
		}
		break;
	case 27:
		//字体大小
		m_nFontSize = tem_nInfo;
		break;
	case 28:
		//加粗
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
		//斜体
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
		//内容
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


//导出透射稿默认模板
void CXRayViewerv10Dlg::Self_EnsureItems(void)
{
	long       tem_lRC       = -1;    //返回值
	long       tem_lMark     = -1;    //是否支持
	long       tem_lAuto     = -1;    //自动调节
	long       tem_lCurVlaue = -1;    //当前值
	long       tem_lMaxValue = -1;    //最大值
	long       tem_lMinValue = -1;    //最小值

	CString    tem_strName   = _T("");  //属性名

	PROPERTY   tem_stcCamera;

	std::vector<PROPERTY>  tem_vcCamera;	

	//1、获取摄像头属性-----------------------------------------------------
	//指定模板参数
	//光圈
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

	//亮度-
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

	//曝光-
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

	//焦点
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

	//增益-
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

	//色调
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

	//全景-
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

	//滚动
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

	//倾斜-
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

	//缩放-
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

	//对比度-
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

	//清晰度-
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

	//饱和度-
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

	//白平衡-
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

	//逆光对比-
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

	//灯箱调节
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

	//灰阶调节
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

	//包围曝光开关--------------------------------------------------------------------
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

	//合并方式
	tem_strName = _T("MergeMode");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;       
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 1;           //1-水平合并，2-垂直合并
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//曝光偏移
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

	//延时调节
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

	//灰阶调节
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
	//反射稿开关
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

	//分辨率
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

	//图像类型
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

	//包围曝光小模板中逆光对比CheckBox选项
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

	//LDR——低密度拍摄，小模板-----------------------------------
	//灯箱
	tem_strName = _T("LQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;      //中间亮度——Cur
		tem_stcCamera.m_lMaxValue = 40;     //最大亮度——Max
		tem_stcCamera.m_lMinValue = 1;       //最小亮度——Min

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//灰阶调节
	tem_strName = _T("LQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;      //Cur
		tem_stcCamera.m_lMaxValue = 11;      //Max
		tem_stcCamera.m_lMinValue = 11;      //Min

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//延时
	tem_strName = _T("LQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;          
		tem_stcCamera.m_lCurValue = 30;       //Cur
		tem_stcCamera.m_lMaxValue = 30;       //Max
		tem_stcCamera.m_lMinValue = 30;       //Min

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//逆光对比
	tem_strName = _T("LQUABCK");
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
	//HDR——高密度拍摄，小模板-----------------------------------
	//灯箱
	tem_strName = _T("HQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//灰阶调节
	tem_strName = _T("HQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;
		tem_stcCamera.m_lMaxValue = 11;
		tem_stcCamera.m_lMinValue = 11;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//延时
	tem_strName = _T("HQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 30;
		tem_stcCamera.m_lMinValue = 30;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//逆光对比
	tem_strName = _T("HQUABCK");
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


	/*获取默认参数，Camera默认参数
	//光圈
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

	//亮度
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

	//曝光
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

	//焦点
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

	//增益
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

	//色调
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

	//全景
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

	//滚动
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

	//倾斜
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

	//缩放
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

	//对比度
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

	//清晰度
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

	//饱和度
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

	//白平衡
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

	//逆光对比
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
	
	//灯箱调节
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



	//2、导出属性XML-------------------------------------------------------
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

	//3、保存XML-----------------------------------------------------------
	CStringA      tem_straPath(g_strProXmlPath);
	const char*   tem_pcPath = tem_straPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcPath);
}


//导出反射稿默认模板
void CXRayViewerv10Dlg::Self_EnsureItems2(void)
{
	long       tem_lRC       = -1;    //返回值
	long       tem_lMark     = -1;    //是否支持
	long       tem_lAuto     = -1;    //自动调节
	long       tem_lCurVlaue = -1;    //当前值
	long       tem_lMaxValue = -1;    //最大值
	long       tem_lMinValue = -1;    //最小值

	CString    tem_strName   = _T("");  //属性名

	PROPERTY   tem_stcCamera;

	std::vector<PROPERTY>  tem_vcCamera;	

	//1、获取摄像头属性-----------------------------------------------------
	//指定模板参数
	//光圈
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

	//亮度-
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

	//曝光-
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

	//焦点
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

	//增益-
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

	//色调
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

	//全景-
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

	//滚动
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

	//倾斜-
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

	//缩放-
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

	//对比度-
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

	//清晰度-
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

	//饱和度-
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

	//白平衡-
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

	//逆光对比-
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

	//灯箱调节
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

	//灰阶调节
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

	//包围曝光开关--------------------------------------------------------------------
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

	//合并方式
	tem_strName = _T("MergeMode");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;       
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 0;           //1-水平合并，2-垂直合并
		tem_stcCamera.m_lMaxValue = 0;
		tem_stcCamera.m_lMinValue = 0;

		tem_vcCamera.push_back(tem_stcCamera);
	}

	//曝光偏移
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

	//延时调节
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

	//灰阶调节
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
	//反射稿开关
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

	//分辨率
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

	//图像类型
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

	//包围曝光小模板中逆光对比CheckBox选项
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

	//LDR小模板_低密度-----------------------------------
	//灯箱
	tem_strName = _T("LQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = 40;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//灰阶调节
	tem_strName = _T("LQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;
		tem_stcCamera.m_lMaxValue = 11;
		tem_stcCamera.m_lMinValue = 11;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//延时1
	tem_strName = _T("LQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 30;
		tem_stcCamera.m_lMinValue = 30;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//逆光对比1
	tem_strName = _T("LQUABCK");
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

	//HDR_高密度拍摄
	tem_strName = _T("HQUABGT");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 10;
		tem_stcCamera.m_lMaxValue = 100;
		tem_stcCamera.m_lMinValue = 1;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//灰阶调节2
	tem_strName = _T("HQUAGRY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 11;
		tem_stcCamera.m_lMaxValue = 11;
		tem_stcCamera.m_lMinValue = 11;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//延时2
	tem_strName = _T("HQUADLY");
	{
		tem_lMark = 1;
		tem_stcCamera.m_strName = tem_strName;
		tem_stcCamera.m_lSuport = tem_lMark;
		tem_stcCamera.m_lAuto = 0;
		tem_stcCamera.m_lCurValue = 30;
		tem_stcCamera.m_lMaxValue = 30;
		tem_stcCamera.m_lMinValue = 30;

		tem_vcCamera.push_back(tem_stcCamera);
	}
	//逆光对比2
	tem_strName = _T("HQUABCK");
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


	//2、导出属性XML-------------------------------------------------------
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

	//3、保存XML-----------------------------------------------------------
	CStringA      tem_straPath(g_strDocXmlPath);
	const char*   tem_pcPath = tem_straPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcPath);
}


int CXRayViewerv10Dlg::Self_FindTems(CString docpath)
{
	m_vcTemName.clear();
	m_vcTemPath.clear();
	int         tem_nFileCount = 0;    //子文件数量
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
			//为缺省目录
			continue;
		}
		else if (temFinder.IsDirectory())
		{
			//检测为子文件夹，保存备用
			continue;
		} 
		else if (temFinder.IsCompressed())
		{
			//压缩文件
			continue;
		}
		else if (temFinder.IsSystem())
		{
			//系统文件
			continue;
		}
		else
		{
			//检测为文件，进行过滤
			strFileName = temFinder.GetFileName();
			CString  strMiddle = strFileName;
			int      nIndex = strMiddle.ReverseFind('.');
			if (nIndex != -1)
			{
				strMiddle = strMiddle.Mid(nIndex+1);
				strMiddle.MakeLower();
				if (strMiddle == _T("xml"))		
				{
					//区别图像文件和非图像文件，将FieName保存
					tem_nFileCount++;
					strFilePath = _T("");
//					if (strFileName != _T("默认.xml"))
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

	//加载xml文件
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//根节点
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();
	
	//Iris节点
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

	//Bright节点
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

	//Expos节点
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

	//Focus节点
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

	//Gama节点
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
//			m_conVideoCtrl.SetGamma(0, 1);                //只读取不设置，修改为灰阶
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastGama     = tem_nSetValue;
//			m_conVideoCtrl.SetGamma(tem_nSetValue, 0);     //只读取不设置，修改为灰阶
		}
	}

	//Gain节点
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
//			m_conVideoCtrl.SetGain(0, 1);                    //只读取不设置，修改为灰阶
		}
		else
		{
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			tem_nSetValue   = tem_xmlChildAtb->IntValue();
			m_nLastGain     = tem_nSetValue;
//			m_conVideoCtrl.SetGain(tem_nSetValue, 0);         //只读取不设置，修改为灰阶
		}
	}

	//Hue节点
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

	//Pan节点
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

	//Roll节点
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

	//Tilt节点
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

	//Zoom节点
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

	//Contrast节点
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

	//Sharp节点
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

	//Satura节点
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

	//WhiteBlance节点
	//将白平衡设为自动，并不可用
//	m_conVideoCtrl.SetWhiteBalance(0, 1);
	//根据实际情况设置白平衡
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
	

	//BackLight节点
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
			//逆光对比调整至设置分辨率后面，否则设置分辨率会重置逆光对比
		}
	}

	//LightBox节点
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
		
		//设置灯箱
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

	//灰阶节点
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
	
	//HDR开关
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

	//合并方式
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
		m_nHDRMerge = 1;    //左右合并
	} 
	else if(tem_nSetValue == 2)
	{
		m_nHDRMerge = 2;    //上下合并
	}
	else
	{
		m_nHDRMerge = 0;    //合并方式未打开，此时包围曝光关闭
	}


	//灯箱偏移
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();

	m_nHDRLight = tem_nSetValue;

	//延时
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRDelay     = tem_nSetValue;

	//灰阶
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRGray      = tem_nSetValue;

	//反射稿开关
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	if (tem_nMark==1)
	{
		m_BDOC = TRUE;
		//反射稿打开，预览模式可以随意设置
		m_nViewMode = 3;
	}
	else
	{
		m_BDOC = FALSE;
		//反射稿关闭，则透射稿必定打开，预览模式不可为3
// 		if (m_nViewMode == 3)
// 		{
// 			m_nViewMode = 2;
// 		}
		m_nViewMode = 1;
	}
	if (m_nViewMode == 0)
	{
		//手动裁切
		m_conVideoCtrl.ManualImageCrop(TRUE);
		m_conVideoCtrl.SetMessage(1);
	}
	else if (m_nViewMode == 1)
	{
		//固定区域
		m_conVideoCtrl.ManualImageCrop(TRUE);
		m_conVideoCtrl.SetMessage(1);
		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conVideoCtrl.SetMessage(0);

	}
	else if(m_nViewMode == 2)
	{
		//预览模式
		m_conVideoCtrl.ManualImageCrop(FALSE);
		m_conVideoCtrl.AdjuestImageCrop(FALSE);
	}
	else
	{
		//自动裁切
		m_conVideoCtrl.ManualImageCrop(FALSE);
		m_conVideoCtrl.AdjuestImageCrop(TRUE);
	}
	
	//图像分辨率
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	/*
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
		//获取最大分辨率索引，并设置为最大分辨率
		int  tem_nMaxIndex = Self_GetSpyRes(1);
//		m_conVideoCtrl.SetResolution(tem_nMaxIndex);
		m_conVideoCtrl.SetResolutionPro(tem_nMaxIndex, m_nVidoeMode);
	}
	else
	{
		//设置为上次使用的分辨率
//		m_conVideoCtrl.SetResolution(m_nLastRes);
		m_conVideoCtrl.SetResolutionPro(m_nLastRes, m_nVidoeMode);
	}
	*/
	//设置分辨率后所有的设置重置一遍，应先设分辨率
	m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);     
	m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);
	m_conVideoCtrl.SetBacklightCom(m_nLastBackLight, 0);
	

	//图像格式
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();
	/*
	if (tem_nMark==1)
	{
		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nAuto       = tem_xmlChildAtb->IntValue();

		tem_xmlChildAtb = tem_xmlChildAtb->Next();
		tem_nSetValue   = tem_xmlChildAtb->IntValue();
		m_nLastImgType  = tem_nSetValue;
	}
	*/

	//包围曝光——逆光对比
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	tem_nMark       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nAuto       = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHDRBackLgt   = tem_nSetValue;

	//LDR-----------------------------------------------------------
	//LLGT------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorLightL    = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigLightL    = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowLightL    = tem_nSetValue;

	//LGRY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorGrayL     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigGrayL     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowGrayL     = tem_nSetValue;

	//LDLY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorDelayL    = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigDelayL    = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowDelayL    = tem_nSetValue;

	//LBCK------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorBackLgtL  = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigBackLgtL  = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowBackLgtL  = tem_nSetValue;

	//HDR-----------------------------------------------------------
	//HLGT------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorLight     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigLight     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowLight     = tem_nSetValue;

	//HGRY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorGray      = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigGray      = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowGray      = tem_nSetValue;

	//HDLY------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorDelay     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigDelay     = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowDelay     = tem_nSetValue;

	//HBCK------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nNorBackLgt   = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nHigBackLgt   = tem_nSetValue;

	tem_xmlChildAtb = tem_xmlChildAtb->Next();
	tem_nSetValue   = tem_xmlChildAtb->IntValue();
	m_nLowBackLgt   = tem_nSetValue;
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


	//加载xml文件
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//根节点---------------------------------------------------------------
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();

	TiXmlElement*    tem_xmlChildElt;
	tem_xmlChildElt = tem_xmlRootElt->FirstChildElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();


	CString  tem_strInfo = _T("");
	if (tem_nMark==1)
	{
		//跳过前面的中文信息
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
			//获取该节点名称
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
	wchar_t    tem_crSltPath[MAX_PATH]; //Unicode使用wchar_t型_t

	ZeroMemory(tem_crSltPath, sizeof(tem_crSltPath));
	BROWSEINFO   m_broseinfo;
	m_broseinfo.hwndOwner = m_hWnd;
	m_broseinfo.pidlRoot  = NULL;
	m_broseinfo.pszDisplayName = tem_crSltPath;
	m_broseinfo.lpszTitle = _T("选择保存目录"); 
	m_broseinfo.ulFlags   = 0;
	m_broseinfo.lpfn      = NULL;
	m_broseinfo.lParam    = 0;
	m_broseinfo.iImage    = 0;
	LPITEMIDLIST   lp = SHBrowseForFolder(&m_broseinfo);
	if (lp&&SHGetPathFromIDList(lp, tem_crSltPath))
	{
		tem_strSltPath.Format(_T("%s"), tem_crSltPath);
//		m_strDefaultPath = tem_strSltPath;
		//注意后面的\\---------------------------------------------------------------------------------------
		
		//如果是C、D盘，最后一位自带“\”不用添加
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
	CString    tem_strPdfImg    = m_strThumbDoc;      //用于PDF合并拍照
	CString    tem_strDcmImg    = m_strThumbDoc;      //用于dcm单拍，以及合并拍照

	CString    tem_strInterImg  = m_strThumbDoc;      //插值原图保存路径

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
					//将原图保存至缓存目录
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 1);

					//图像插值
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
					//将原图保存至缓存目录
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 1);
					
					//图像插值
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
					//将原图保存至缓存目录
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 1);

					//图像插值
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
			//生成dcm图像
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
					//将原图保存至缓存目录
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 0);

					//图像插值
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
					//将原图保存至缓存目录
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 0);

					//图像插值
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
					//将原图保存至缓存目录
					m_conVideoCtrl.CaptureCombineEx(tem_strInterImg, 0);

					//图像插值
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
			//生成dcm图像
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
			//普通拍照	
			if (m_nLastRes==m_nInterpolateReso)
			{
				//将原图保存至缓存目录
				m_conVideoCtrl.CaptureImage(tem_strInterImg);

				//图像插值
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
			//pdf拍照
			/*流程一：OCX自带pdf拍照，但无法添加自定义水印*/
			/*
			m_conVideoCtrl.CapturePDF(tem_strFilePath);
			Self_GetImgFromPDF(tem_strFilePath, tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			m_vcFilePath.push_back(tem_strFilePath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			*/

			/*流程二：拍摄普通图像再转换为pdf文件*/
			//拍摄图像保存至缓存目录
			if (m_nLastRes==m_nInterpolateReso)
			{
				//将原图保存至缓存目录
				m_conVideoCtrl.CaptureImage(tem_strInterImg);

				//图像插值
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
			//获取缩略图
			Self_CreateThumb(tem_strDcmImg , tem_strThumbPath);
			m_vcImgName.push_back(tem_strImgName);
			m_vcThumbPath.push_back(tem_strThumbPath);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//获取pdf文件
			Self_GetPdfFromImg(tem_strDcmImg, tem_strFilePath);
			m_vcFilePath.push_back(tem_strFilePath);
			DeleteFile(tem_strDcmImg);
		}
		else if (m_nLastImgType == 5)
		{
			//dcm拍照
			if (m_nLastRes==m_nInterpolateReso)
			{
				//将原图保存至缓存目录
				m_conVideoCtrl.CaptureImage(tem_strInterImg);
				//图像插值
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
			//生成dcm图像
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
	//如果拍摄模式为<透射稿>则校准灯箱
	if (!m_BDOC)
	{
		int tem_nSave = m_nLastRelay;
		Self_SetRelayZero();
		m_nLastRelay = tem_nSave;
		AdjustRelay(m_nLastRelay, 0);
	}
}


void CXRayViewerv10Dlg::Self_CaptureImgHDR(CString imgname, int mode)
{
	m_dlgOne.Self_HideCtrls(1);
	m_vcSomeStrInfo.clear();
	
	//文件命名---------------------------------------------------------------------------
	CString    tem_strLowImg    = m_strThumbDoc;      //欠曝图像
	tem_strLowImg              += _T("\\lbmd");
	tem_strLowImg              += imgname;

	CString    tem_strNorImg    = m_strThumbDoc;      //正常图像
	tem_strNorImg              += _T("\\nbmd");
	tem_strNorImg              += imgname;

	CString    tem_strHigImg    = m_strThumbDoc;      //过曝图像
	tem_strHigImg              += _T("\\hbmd");
	tem_strHigImg              += imgname;

	CString    tem_strHDRImg    = m_strThumbDoc;      //合成图像
	tem_strHDRImg              += _T("\\bmd");
	tem_strHDRImg              += imgname;

	CString    tem_strThumbPath = m_strThumbDoc;      //缩略图像
	tem_strThumbPath           += _T("\\~");
	tem_strThumbPath           += imgname;
	tem_strThumbPath           += _T(".jpg");

	CString    tem_strIntImg    = m_strThumbDoc;      //插值图像
	tem_strIntImg              += _T("\\~~~");
	tem_strIntImg              += imgname;

	CString    tem_strFilePath  = m_strSaveDoc;       //目标文件
	tem_strFilePath            += imgname;
	tem_strFilePath            += m_strFileFormat;
	
	if (m_nLastImgType>=0 && m_nLastImgType<3)
	{
		tem_strLowImg += m_strFileFormat;
		tem_strNorImg += m_strFileFormat;
		tem_strHigImg += m_strFileFormat;
		tem_strHDRImg += m_strFileFormat;
		tem_strIntImg += m_strFileFormat;
	} 
	else if(m_nLastImgType == 4 || m_nLastImgType == 5 ||m_nLastImgType == 3)  //3-tif,tif无法合成
	{
		tem_strLowImg += _T(".jpg");
		tem_strNorImg += _T(".jpg");
		tem_strHigImg += _T(".jpg");
		tem_strHDRImg += _T(".jpg");
		tem_strIntImg += _T(".jpg");
	}
	
	/*
	*     说明
	*   由于不同拍照间不需要再设置不同灰阶和逆光对比，因此将这两项设置注释，以提升效率
	*
	*/
	
	if (mode == 1)
	{
		if (m_nNorLight != m_nLastRelay)
		{
			//调节灯箱**********************************
			AdjustRelay(m_nNorLight, m_nLastRelay);
			//调节灰阶----------------------------------
//  		m_conVideoCtrl.SetGamma(g_nGrayValue[m_nNorGray][0], 0);
//  		m_conVideoCtrl.SetGain(g_nGrayValue[m_nNorGray][1], 0);
			//调节逆光对比------------------------------
	// 		m_conVideoCtrl.SetBacklightCom(m_nNorBackLgt, 0);
			//根据当前亮度与目标亮度差设置延时-----------
			Self_TimeDelay(m_nIntervalTime);
		}	
	} 
	else
	{
		if (m_nNorLightL != m_nLastRelay)
		{
			//调节灯箱**********************************
			AdjustRelay(m_nNorLightL, m_nLastRelay);
			//调节灰阶----------------------------------
	// 		m_conVideoCtrl.SetGamma(g_nGrayValue[m_nNorGrayL][0], 0);
	// 		m_conVideoCtrl.SetGain(g_nGrayValue[m_nNorGrayL][1], 0);
			//调节逆光对比------------------------------
	// 		m_conVideoCtrl.SetBacklightCom(m_nNorBackLgtL, 0);
			//根据当前亮度与目标亮度差设置延时-----------
			Self_TimeDelay(m_nIntervalTime);
		}
	}
	m_conVideoCtrl.CaptureImage(tem_strNorImg);
	
	m_dlgOne.Self_HideCtrls(2);
	
	if (mode == 1)
	{
		//调节灯箱**********************************
		AdjustRelay(m_nLowLight, m_nNorLight);
		//调节灰阶----------------------------------
// 		m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLowGray][0], 0);
// 		m_conVideoCtrl.SetGain(g_nGrayValue[m_nLowGray][1], 0);
		//调节逆光对比------------------------------
// 		m_conVideoCtrl.SetBacklightCom(m_nLowBackLgt, 0);
		//根据当前亮度与目标亮度差设置延时-----------
		Self_TimeDelay(m_nIntervalTime);
	} 
	else
	{
		//调节灯箱**********************************
		AdjustRelay(m_nLowLightL, m_nNorLightL);
		//调节灰阶----------------------------------
// 		m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLowGrayL][0], 0);
// 		m_conVideoCtrl.SetGain(g_nGrayValue[m_nLowGrayL][1], 0);
		//调节逆光对比------------------------------
// 		m_conVideoCtrl.SetBacklightCom(m_nLowBackLgtL, 0);
		//根据当前亮度与目标亮度差设置延时-----------
		Self_TimeDelay(m_nIntervalTime);
	}
	//拍照-------------------------------------
	m_conVideoCtrl.CaptureImage(tem_strLowImg);
	m_dlgOne.Self_HideCtrls(3);

	if (mode == 1)
	{
		//调节灯箱**********************************
		AdjustRelay(m_nHigLight, m_nLowLight);
		//调节灰阶----------------------------------
// 		m_conVideoCtrl.SetGamma(g_nGrayValue[m_nHigGray][0], 0);
// 		m_conVideoCtrl.SetGain(g_nGrayValue[m_nHigGray][1], 0);
		//调节逆光对比------------------------------
// 		m_conVideoCtrl.SetBacklightCom(m_nHigBackLgt, 0);
		//根据当前亮度与目标亮度差设置延时-----------
		Self_TimeDelay(m_nIntervalTime);
	} 
	else
	{
		//调节灯箱**********************************
		AdjustRelay(m_nHigLightL, m_nLowLightL);
		//调节灰阶----------------------------------
// 		m_conVideoCtrl.SetGamma(g_nGrayValue[m_nHigGrayL][0], 0);
// 		m_conVideoCtrl.SetGain(g_nGrayValue[m_nHigGrayL][1], 0);
		//调节逆光对比------------------------------
// 		m_conVideoCtrl.SetBacklightCom(m_nHigBackLgtL, 0);
		//根据当前亮度与目标亮度差设置延时-----------
		Self_TimeDelay(m_nIntervalTime);
	}
	//拍照-------------------------------------
	m_conVideoCtrl.CaptureImage(tem_strHigImg);
	m_dlgOne.Self_HideCtrls(4);

	//恢复参数--------------------------------------------------------------------------
	if (mode == 1)
	{
		//先校准，再恢复---------------------------------
		int tem_nSave = m_nLastRelay;
		Self_SetRelayZero();
		m_nLastRelay = tem_nSave; 
		AdjustRelay(m_nLastRelay, 0);
//		AdjustRelay(m_nLastRelay, m_nHigLight);
	} 
	else
	{
		//先校准，再恢复---------------------------------
		int tem_nSave = m_nLastRelay;
		Self_SetRelayZero();
		m_nLastRelay = tem_nSave; 
		AdjustRelay(m_nLastRelay, 0);
//		AdjustRelay(m_nLastRelay, m_nHigLightL);
	}
	//恢复灰阶---------------------------------
	// 	m_conVideoCtrl.SetGamma(g_nGrayValue[m_nLastGray][0], 0);
	// 	m_conVideoCtrl.SetGain(g_nGrayValue[m_nLastGray][1], 0);	
	//恢复逆光对比-----------------------------
	// 	m_conVideoCtrl.SetBacklightCom(m_nLastBackLight, 0);

	Self_HDRMergeImgEx(tem_strLowImg, tem_strNorImg, tem_strHigImg, tem_strHDRImg, mode, m_nLowLightL, m_nNorLightL, m_nHigLightL, m_nLowLight, m_nNorLight, m_nHigLight);
	m_dlgOne.Self_HideCtrls(5);

	m_nHdrMergeMode = mode;
	m_vcSomeStrInfo.push_back(tem_strLowImg);
	m_vcSomeStrInfo.push_back(tem_strNorImg);
	m_vcSomeStrInfo.push_back(tem_strHigImg);
	m_vcSomeStrInfo.push_back(tem_strHDRImg);
	m_vcSomeStrInfo.push_back(tem_strThumbPath);
	m_vcSomeStrInfo.push_back(tem_strIntImg);
	m_vcSomeStrInfo.push_back(tem_strFilePath);
	m_vcSomeStrInfo.push_back(imgname);

	
	

	/*将合成图像移至接收到下层返回消息处，在此处合成1、while不断检测文件有系统开销；2、检测的文件的速度快于子程序释放图像速度，没有下面延时可能内存异常*/
	/*
	//合成图像--------------------------------------------------------------------------
	if(PathFileExists(tem_strHDRImg))
	{
		::DeleteFile(tem_strHDRImg);
	}
//	Self_HDRMergeImgs(tem_strHigImg, tem_strNorImg, tem_strLowImg, tem_strHDRImg);   //方法一
//	Self_HDRMergeImgs3_1(tem_strHigImg, tem_strNorImg, tem_strLowImg, tem_strHDRImg, mode);  //方法二
	Self_HDRMergeImgEx(tem_strLowImg, tem_strNorImg, tem_strHigImg, tem_strHDRImg, mode, m_nLowLightL, m_nNorLightL, m_nHigLightL, m_nLowLight, m_nNorLight, m_nHigLight);
	//等待子程序生成完毕再继续-----------------------------------------------------------
	BOOL  tem_BComplted = TRUE;
	while(tem_BComplted)
	{
		//查询文件是否存在------------------
		if(PathFileExists(tem_strHDRImg))
		{
			break;
		}

	}
	Self_TimeDelay(300);
	//删除缓存图像----------------------------------------------------------------------
// 	::DeleteFile(tem_strHigImg);
// 	::DeleteFile(tem_strNorImg);
// 	::DeleteFile(tem_strLowImg);
	

	//是否需要添加水印-------------------------------------------------------------------
	if (m_nWaterMark == 1)
	{
		Self_AddWaterMark(tem_strHDRImg);
	}

	//创建缩略图------------------------------------------------------------------------
	Self_CreateThumb(tem_strHDRImg, tem_strThumbPath);

	//是否需要插值----------------------------------------------------------------------
	if (m_nLastRes==m_nInterpolateReso)
	{
		Self_InterPolateImage(tem_strHDRImg, tem_strIntImg, 0);
		::DeleteFile(tem_strHDRImg);
		tem_strHDRImg = tem_strIntImg;
	}

	//判断图像格式----------------------------------------------------------------------
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
	 else if (m_nLastImgType == 3)
	 {
		 //将jpg图像转为tif图像
		 CxImage tem_cxJPG;
		 tem_cxJPG.Load(tem_strHDRImg, CMAX_IMAGE_FORMATS);
		 tem_cxJPG.SetCodecOption(5, CXIMAGE_FORMAT_TIF);
		 tem_cxJPG.Save(tem_strFilePath, CXIMAGE_FORMAT_TIF);	 
	 }
	 else
	 {
		 CopyFile(tem_strHDRImg, tem_strFilePath, FALSE);
	 }
//	 ::DeleteFile(tem_strHDRImg);
	
	 m_vcImgName.push_back(imgname);
	 m_vcThumbPath.push_back(tem_strThumbPath);
	 m_vcFilePath.push_back(tem_strFilePath);
	 ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	 Self_ShowImgInfo(tem_strFilePath);
	 m_nImageCount++;
	 MessageBox(_T("Over"));
	 */
}


void CXRayViewerv10Dlg::Self_CaptureImgHDRThread(CString imgname, int mode, int ex)
{	
	//文件命名---------------------------------------------------------------------------
	CString    tem_strLowImg    = m_strThumbDoc;      //欠曝图像
	tem_strLowImg              += _T("\\lbmd");
	tem_strLowImg              += imgname;

	CString    tem_strNorImg    = m_strThumbDoc;      //正常图像
	tem_strNorImg              += _T("\\nbmd");
	tem_strNorImg              += imgname;

	CString    tem_strHigImg    = m_strThumbDoc;      //过曝图像
	tem_strHigImg              += _T("\\hbmd");
	tem_strHigImg              += imgname;

	CString    tem_strHDRImg    = m_strThumbDoc;      //合成图像
	tem_strHDRImg              += _T("\\bmd");
	tem_strHDRImg              += imgname;

	CString    tem_strThumbPath = m_strThumbDoc;      //缩略图像
	tem_strThumbPath           += _T("\\~");
	tem_strThumbPath           += imgname;
	tem_strThumbPath           += _T(".jpg");

	CString    tem_strIntImg    = m_strThumbDoc;      //插值图像
	tem_strIntImg              += _T("\\~~~");
	tem_strIntImg              += imgname;

	CString    tem_strFilePath  = m_strSaveDoc;       //目标文件
	tem_strFilePath            += imgname;
	tem_strFilePath            += m_strFileFormat;
	
	if (m_nLastImgType>=0 && m_nLastImgType<3)
	{
		tem_strLowImg += m_strFileFormat;
		tem_strNorImg += m_strFileFormat;
		tem_strHigImg += m_strFileFormat;
		tem_strHDRImg += m_strFileFormat;
		tem_strIntImg += m_strFileFormat;
	} 
	else if(m_nLastImgType == 4 || m_nLastImgType == 5 ||m_nLastImgType == 3)  //3-tif,tif无法合成
	{
		tem_strLowImg += _T(".jpg");
		tem_strNorImg += _T(".jpg");
		tem_strHigImg += _T(".jpg");
		tem_strHDRImg += _T(".jpg");
		tem_strIntImg += _T(".jpg");
	}
	/*
	*     说明
	*   由于不同拍照间不需要再设置不同灰阶和逆光对比，因此将这两项设置注释，以提升效率
	*
	*/
	if (ex == 0)
	{
		m_dlgOne.Self_HideCtrls(1);
		m_vcSomeStrInfo.clear();

		if (mode == 1)
		{
			if (m_nNorLight != m_nLastRelay)
			{
				//调节灯箱**********************************
				AdjustRelay(m_nNorLight, m_nLastRelay);
				stcThreadInfo.hWnd = this->m_hWnd;
				stcThreadInfo.time = m_nIntervalTime;
				stcThreadInfo.mode = 1;
				hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
			}	
			else
			{
				//亮度=10，不需要延时
				stcThreadInfo.hWnd = this->m_hWnd;
				stcThreadInfo.time = 0;
				stcThreadInfo.mode = 1;
				hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
			}
		} 
		else
		{
			if (m_nNorLightL != m_nLastRelay)
			{
				//调节灯箱**********************************
				AdjustRelay(m_nNorLightL, m_nLastRelay);
				stcThreadInfo.hWnd = this->m_hWnd;
				stcThreadInfo.time = m_nIntervalTime;
				stcThreadInfo.mode = 1;
				hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
			}
			else
			{
				//亮度=10，不需要延时
				stcThreadInfo.hWnd = this->m_hWnd;
				stcThreadInfo.time = 0;
				stcThreadInfo.mode = 1;
				hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
			}
		}
		
	}
	else if (ex == 1)
	{
		m_conVideoCtrl.CaptureImage(tem_strNorImg);
		m_dlgOne.Self_HideCtrls(2);
		if (mode == 1)
		{
			//调节灯箱**********************************
			AdjustRelay(m_nLowLight, m_nNorLight);
		} 
		else
		{
			//调节灯箱**********************************
			AdjustRelay(m_nLowLightL, m_nNorLightL);
		}
		stcThreadInfo.hWnd = this->m_hWnd;
		stcThreadInfo.time = m_nIntervalTime;
		stcThreadInfo.mode = 2;
		hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
	}
	else if (ex == 2)
	{
		m_conVideoCtrl.CaptureImage(tem_strLowImg);
		m_dlgOne.Self_HideCtrls(3);
		if (mode == 1)
		{
			//调节灯箱**********************************
			AdjustRelay(m_nHigLight, m_nLowLight);
		} 
		else
		{
			//调节灯箱**********************************
			AdjustRelay(m_nHigLightL, m_nLowLightL);
		}
		stcThreadInfo.hWnd = this->m_hWnd;
		stcThreadInfo.time = m_nIntervalTime;
		stcThreadInfo.mode = 3;
		hThreadHandle = AfxBeginThread(ThreadDelay, &stcThreadInfo, THREAD_PRIORITY_NORMAL, 0, NULL);
	}
	else if (ex == 3)
	{
		m_conVideoCtrl.CaptureImage(tem_strHigImg);
		m_dlgOne.Self_HideCtrls(4);

		//恢复参数--------------------------------------------------------------------------
		if (mode == 1)
		{
			//先校准，再恢复---------------------------------
			int tem_nSave = m_nLastRelay;
			Self_SetRelayZero();
			m_nLastRelay = tem_nSave; 
			AdjustRelay(m_nLastRelay, 0);
		} 
		else
		{
			//先校准，再恢复---------------------------------
			int tem_nSave = m_nLastRelay;
			Self_SetRelayZero();
			m_nLastRelay = tem_nSave; 
			AdjustRelay(m_nLastRelay, 0);
		}
		Self_HDRMergeImgEx(tem_strLowImg, tem_strNorImg, tem_strHigImg, tem_strHDRImg, mode, m_nLowLightL, m_nNorLightL, m_nHigLightL, m_nLowLight, m_nNorLight, m_nHigLight);
		m_dlgOne.Self_HideCtrls(5);

		m_nHdrMergeMode = mode;
		m_vcSomeStrInfo.push_back(tem_strLowImg);
		m_vcSomeStrInfo.push_back(tem_strNorImg);
		m_vcSomeStrInfo.push_back(tem_strHigImg);
		m_vcSomeStrInfo.push_back(tem_strHDRImg);
		m_vcSomeStrInfo.push_back(tem_strThumbPath);
		m_vcSomeStrInfo.push_back(tem_strIntImg);
		m_vcSomeStrInfo.push_back(tem_strFilePath);
		m_vcSomeStrInfo.push_back(imgname);
	}
}

#include "MMsystem.h"   //延时函数,精度毫秒
#pragma comment(lib, "winmm.lib")
UINT ThreadDelay(LPVOID lpParam)  
{
	ThreadInfo* tem_pInfo = (ThreadInfo*)lpParam;
	HWND tem_hWnd = tem_pInfo->hWnd;
	int tem_nTime = tem_pInfo->time;
	int tem_nMode = tem_pInfo->mode;

	DWORD tem_nBegin = timeGetTime();
	DWORD tem_nEnd = 0;
	do 
	{
		tem_nEnd = timeGetTime();
	} while (tem_nEnd-tem_nBegin<=tem_nTime);

	::PostMessage(tem_hWnd, WM_THREADOVER, 0, tem_nMode);

	return 0;
}


afx_msg LRESULT CXRayViewerv10Dlg::OnThreadover(WPARAM wParam, LPARAM lParam)
{
	int tem_nInfo = (int)lParam;
	Self_CaptureImgHDRThread(m_strCurImgName, m_nCurImgMode, tem_nInfo);
	
	
	return 0;
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
	//把所有的Mat型数据转换位了IplImage类型
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


void CXRayViewerv10Dlg::Self_HDRMergeImgs3_1(CString HigImg, CString NorImg, CString LowImg, CString outImg, int mode)
{
	
	/*1、加载图像*/
	std::vector<Mat> images;
	CStringA straLowImg(LowImg); string tem_sLowImg = straLowImg.GetBuffer(0); straLowImg.ReleaseBuffer();
	CStringA straNorImg(NorImg); string tem_sNorImg = straNorImg.GetBuffer(0); straNorImg.ReleaseBuffer();
	CStringA straHigImg(HigImg); string tem_sHigImg = straHigImg.GetBuffer(0); straHigImg.ReleaseBuffer();

	Mat tem_mtLowImg = imread(tem_sLowImg); 	images.push_back(tem_mtLowImg);
	Mat tem_mtNorImg = imread(tem_sNorImg); 	images.push_back(tem_mtNorImg);
	Mat tem_mtHigImg = imread(tem_sHigImg); 	images.push_back(tem_mtHigImg);

	tem_mtLowImg.release(); tem_mtNorImg.release(); tem_mtHigImg.release();
	/*2、估计相机相应*/
	Mat response;
	Ptr<CalibrateDebevec> calibrate = createCalibrateDebevec();
	if (mode == 1)
	{
		//高密度
		calibrate->process(images, response, m_vcHShutter);
	}
	else
	{
		//低密度
		calibrate->process(images, response, m_vcLShutter);
	}

	/*3、曝光合成*/
	cv::Size size = images[0].size();
	Mat fusion = Mat::zeros(size, CV_32F);
	Ptr<MergeMertens> merge_mertens = createMergeMertens();
	merge_mertens->process(images, fusion);

	/*4、图像输出*/
	Mat tem_mtFusion = fusion*255;
	CStringA tem_straOutImg(outImg); string tem_sOutImg = tem_straOutImg.GetBuffer(0); tem_straOutImg.ReleaseBuffer();
	imwrite(tem_sOutImg, tem_mtFusion);
}


float CXRayViewerv10Dlg::Self_GetShutter(int lightvalue)
{
	if (lightvalue == 0)
	{
		return 0;
	}
	float tem_dLux = 0.0;
	tem_dLux = (-0.00854875)*lightvalue*lightvalue + (69.13044485)*lightvalue + (1367.25160760);

	float tem_dShetter = tem_dLux/2000.0;
	return tem_dShetter;
}


void CXRayViewerv10Dlg::Self_CaptureHdrImg(CString imgname)
{
	BOOL       tem_BFirst       = TRUE;
	CString    tem_strImgName   = imgname;
	CString    tem_strThumbPath = m_strThumbDoc;
	CString    tem_strFilePath  = m_strSaveDoc;
	CString    tem_strPdfImg    = m_strThumbDoc;      //用于PDF合并拍照
	CString    tem_strDcmImg    = m_strThumbDoc;      //用于dcm单拍，以及合并拍照

	CString    tem_strInterImg  = m_strThumbDoc;      //插值原图保存路径

	tem_strThumbPath += _T("\\~");          //拍摄缩略图
	tem_strThumbPath += imgname;
	tem_strThumbPath += _T(".jpg");

	tem_strFilePath  += imgname;            //其他模式拍摄原图
	tem_strFilePath  += m_strFileFormat;

	tem_strPdfImg += _T("\\~~");       //PDF拍摄原图
	tem_strPdfImg += imgname;
	tem_strPdfImg += _T(".jpg");

	tem_strDcmImg += _T("\\~~");        //DCM拍摄原图
	tem_strDcmImg += imgname;
	tem_strDcmImg += _T(".jpg");

	tem_strInterImg += _T("\\~~~");     //插值拍摄原图
	tem_strInterImg += imgname;
	tem_strInterImg += _T(".jpg");

	CString  tem_strOriImg = _T("");    //与之前逻辑不通，统一将图像拍摄至缓存目录
	CString  tem_strDstImg = _T("");

	if (m_nLastImgType>=0 && m_nLastImgType<4)
	{
		//普通图像
		tem_strOriImg  = m_strThumbDoc;
		tem_strOriImg += _T("\\~~");
		tem_strOriImg += imgname;        
		tem_strOriImg += m_strFileFormat;
	}
	else if(m_nLastImgType==4)
	{
		//pdf拍照
		tem_strOriImg = tem_strPdfImg;
	}
	else if(m_nLastImgType==5)
	{
		//dcm拍照
		tem_strOriImg = tem_strDcmImg;
	}

	//出图*****************************************************************************
	if (m_nHDRMerge==1)
	{
		//左右合并
		for (int i=0; i<2; i++)
		{
			m_conVideoCtrl.CaptureCombineEx(tem_strOriImg, 1);
							
			if (tem_BFirst)
			{
				//修改灯箱亮度m_nHDRLight
				AdjustRelay(m_nHDRLight, m_nLastRelay);
				//调整灰阶m_nHDRGray
				if (m_nLastGray != m_nHDRGray)
				{
					m_conVideoCtrl.SetGamma(g_nGrayValue[m_nHDRGray][0], 0);   
					m_conVideoCtrl.SetGain(g_nGrayValue[m_nHDRGray][1], 0);
				}
				
				if (m_nLastBackLight != m_nHDRBackLgt)
				{
					m_conVideoCtrl.SetBacklightCom(m_nHDRBackLgt, 0);
				}

				//延时函数
				Self_TimeDelay(m_nHDRDelay*100);
				tem_BFirst = FALSE;
			}	
		}	 
	}
	else
	{
		//上下合并
		for (int i=0; i<2; i++)
		{
			m_conVideoCtrl.CaptureCombineEx(tem_strOriImg, 0);

			if (tem_BFirst)
			{
				//修改灯箱亮度m_nHDRLight
				AdjustRelay(m_nHDRLight, m_nLastRelay);
				//调整灰阶m_nHDRGray
				if (m_nLastGray != m_nHDRGray)
				{
					m_conVideoCtrl.SetGamma(g_nGrayValue[m_nHDRGray][0], 0);     
					m_conVideoCtrl.SetGain(g_nGrayValue[m_nHDRGray][1], 0);
				}
				
				if (m_nLastBackLight != m_nHDRBackLgt)
				{
					m_conVideoCtrl.SetBacklightCom(m_nHDRBackLgt, 0);
				}

				//延时函数
				Self_TimeDelay(m_nHDRDelay*10);
				tem_BFirst = FALSE;
			}	
		}	
	}

	//缩略图并显示*********************************************************************
	Self_CreateThumb(tem_strOriImg, tem_strThumbPath);
	m_vcImgName.push_back(tem_strImgName);
	m_vcThumbPath.push_back(tem_strThumbPath);
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	//添加水印*************************************************************************
	if (m_nWaterMark == 1)
	{
		Self_AddWaterMark(tem_strOriImg);
	}

	//判断是否需要插值******************************************************************
	/*2倍图像尺寸插值，效率较低；提升效率可单张拍摄，插值，自行合并*/
	if (m_nLastRes==m_nInterpolateReso)
	{
		Self_InterPolateImage(tem_strOriImg, tem_strOriImg, 0);
	}
	
	//复制或格式转换********************************************************************
	if (m_nLastImgType>=0 && m_nLastImgType<4)
	{
		//普通图像——复制到指定目录
		CopyFile(tem_strOriImg, tem_strFilePath, FALSE);
	}
	else if(m_nLastImgType==4)
	{
		//pdf拍照——生成pdf文件
		Self_GetPdfFromImg(tem_strOriImg, tem_strFilePath);	
	}
	else if(m_nLastImgType==5)
	{
		//dcm拍照——生成dcm文件
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

	//删除缓存**************************************************************************
	DeleteFile(tem_strOriImg);
	
	//更新文件vector********************************************************************
	m_vcFilePath.push_back(tem_strFilePath);

	//显示图像信息，更新计数*************************************************************
	Self_ShowImgInfo(tem_strFilePath);
	m_nImageCount++;

	//恢复灯箱亮度值*********************************************************************
//	int    tem_nRecover = -m_nHDRLight;
	AdjustRelay(m_nLastRelay, m_nHDRLight);
	//恢复摄像头灰阶*********************************************************************
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
	//1、获取水印格式信息
	int       tem_nSite;
	int       tem_nOffSetX;   //水印坐标
	int       tem_nOffSetY; 
	int       tem_nSize   = Self_GetFontSize(m_nWaterSize);
	int       tem_nStrWidth;
	CString   tem_strFont = Self_GetFontName(m_nWaterFont);
	CString   tem_strInfo = _T("");

	CxImage*  tem_pImage;
	tem_pImage = new CxImage;
	tem_pImage->Load(imgpath, CMAX_IMAGE_FORMATS);
	tem_pImage->IncreaseBpp(24);

	CxImage::CXTEXTINFO WMTxtInfo;                  // 授权文字水印
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
	WMTxtInfo.opaque = 0;                        //背景
	WMTxtInfo.b_opacity = (float)(1);            //透明度
	WMTxtInfo.b_round = (BYTE)10;
	
	
	if (m_nWaterMode == 1)
	{
		//时间水印
		tem_strInfo = Self_GetTimeInfo();
	} 
	else
	{
		//文字水印
		tem_strInfo = m_strWaterInfo;
	}
	
	//获取水印文本的像素尺寸
	tem_nStrWidth = Self_GetFontWidth(WMTxtInfo.lfont, tem_strInfo);

	if (tem_strFont == _T("Arial"))
	{
		//Arial
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/12);   //15时中文刚好，但英文溢出
	}
	else if (tem_strFont == _T("Calibri"))
	{
		//Calibri
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/4);    //10时中文刚好，但英文会出
	}
	else if (tem_strFont == _T("Times New Roman"))
	{
		//Times
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/7);
	}
	else if (tem_strFont == _T("隶书"))
	{
		//隶书
		tem_nStrWidth = (tem_nStrWidth/2 + tem_nStrWidth/11);
	}
	else 
	{
		//宋体、楷体、仿宋、黑体、雅黑、新宋
		tem_nStrWidth = tem_nStrWidth/2;
	}


	/*
	CDC*    tem_pDC = GetDC();
	CSize   tem_szSize;

	CFont   tem_ftFont;
	tem_ftFont.CreatePointFont(120, _T("宋体"));
	CFont*  tem_ftOld = tem_pDC->SelectObject(&tem_ftFont);
	tem_szSize = tem_pDC->GetTextExtent(_T("北京紫光图文系统有限公司"));
	tem_nStrWidth = tem_szSize.cx;
	tem_pDC->SelectObject(&tem_ftOld);
	*/
	

	if (m_nWaterSite == 0)
	{
		//左上角
		tem_nOffSetX = 0;
		tem_nOffSetY = tem_nSize;
	}
	else if (m_nWaterSite == 1)
	{
		//左下角
		tem_nOffSetX = 0;
		tem_nOffSetY = tem_pImage->GetHeight();
	}
	else if (m_nWaterSite == 2)
	{
		//右上角
//		tem_nOffSetX = tem_pImage->GetWidth()-tem_nStrWidth;
		tem_nOffSetX = tem_pImage->GetWidth()-tem_nStrWidth;
		tem_nOffSetY = tem_nSize;
	}
	else if (m_nWaterSite == 3)
	{
		//右下角
//		tem_nOffSetX = tem_pImage->GetWidth()-100;
		tem_nOffSetX = tem_pImage->GetWidth()-tem_nStrWidth;
		tem_nOffSetY = tem_pImage->GetHeight();
	}
	else
	{
		//居中
		tem_nOffSetX = tem_pImage->GetWidth()/2;
		tem_nOffSetY = tem_pImage->GetHeight()/2;
	}
	
	_stprintf(WMTxtInfo.text, tem_strInfo);
	tem_pImage->DrawStringEx(0, tem_nOffSetX, tem_nOffSetY, &WMTxtInfo);

	//根据后缀判断文件类型
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
	//解析m_strWaterColor
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
//	int tem_nStrLength = _tcslen(textinfo);         //字符字符串字符个数
//	int width = sztext.cx/_tcslen(_T("hello"));     //单个字符平均长度

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
		tem_strFontName = _T("宋体");
		break;
	case 4:
		tem_strFontName = _T("楷体");
		break;
	case 5:
		tem_strFontName = _T("仿宋");
		break;
	case 6:
		tem_strFontName = _T("黑体");
		break;
	case 7:
		tem_strFontName = _T("隶书");
		break;
	case 8:
		tem_strFontName = _T("微软雅黑");
		break;
	case 9:
		tem_strFontName = _T("新宋体");
		break;
	default:
		tem_strFontName = _T("宋体");
		break;
	}
	return tem_strFontName;
}


CString CXRayViewerv10Dlg::Self_GetTimeInfo(void)
{
	SYSTEMTIME   tem_stDateTime;
	CString      tem_strDate = _T("");
	CString      tem_strTime = _T("");
	CString      tem_strTimeName  = _T("");       //时间命名

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


	CString   tem_strOrderName = _T("IMG_");   //次序命名
	CString   tem_strTimeName  = _T("");       //时间命名
	CString   tem_strCustomName= _T("");       //自定义名
	CString   tem_strValue     = _T("");       //写入配置文件

	CString   tem_strNewName   = _T("");       //返回名称

	switch(m_nNameMode)
	{
	case 0:
		//次序命名
		tem_nOffset += m_nNameBegin2;
		//把当前的计数值写入ini配置文件
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
		//时间命名
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

		//毫秒保留前两位
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
		//自定义命名

		tem_nOffset += m_nNameBegin;
		//把当前的计数值写入ini配置文件
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
		//重读配置文件
		int     tem_nRead   = 0;
		CString tem_strRead = _T("");
		::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("没有找到NameMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameMode = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("没有找到NameDate信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameDate   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("没有找到NameTime信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameTime   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("没有找到NameDivide信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNameDivide = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("没有找到NamePre1信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre1 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("没有找到NamePre2信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre2 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("没有找到NamePre3信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strNamePre3 = tem_strRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("没有找到NameBegin信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nRead = _ttoi(tem_strRead);
		m_nNameBegin   = tem_nRead;
		tem_strRead.ReleaseBuffer();

		::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("没有找到NameBegin2信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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
	//CImageList初始化
	m_imagelist.Create(thumbwidth,thumbheight,ILC_COLOR24,0,1);

	//ListCtrl初始化
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
	CString     tem_strImagePath = dstpath;        //图像导出路径
	CString     tem_strResolution= _T("50");               //图像分辨率
	CString     tem_strDllPath   = _T("gsdll32.dll");

	int len = WideCharToMultiByte(CP_ACP, 0, pdfpath, -1, NULL, 0, NULL, NULL);
	char*   tem_cPDFFile = new char[len+1];    //导入PDF路径+名
	WideCharToMultiByte(CP_ACP, 0, pdfpath, -1, tem_cPDFFile, len, NULL, NULL);


	len = WideCharToMultiByte(CP_ACP, 0, tem_strImagePath, -1, NULL, 0, NULL, NULL);
	char*   tem_cImage = new char[len+1];       //导出图像路径+名
	WideCharToMultiByte(CP_ACP, 0, tem_strImagePath, -1, tem_cImage, len, NULL, NULL);

	len = WideCharToMultiByte(CP_ACP, 0, tem_strResolution, -1, NULL, 0, NULL, NULL);
	char*   tem_cRes = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, tem_strResolution, -1, tem_cRes, len, NULL, NULL);

	len = WideCharToMultiByte(CP_ACP, 0, tem_strDllPath, -1, NULL, 0, NULL, NULL);
	char*   tem_cDll = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, tem_strDllPath, -1, tem_cDll, len, NULL, NULL);


	GhostPdf2Image(tem_cPDFFile, tem_cImage, tem_cRes, tem_cDll); //输入PDF路径， 输出图像路径， 分辨率， dll路径

	delete[] tem_cPDFFile;
	delete[] tem_cImage;
	delete[] tem_cRes;
	delete[] tem_cDll;

	return tem_strImagePath;
}


CString CXRayViewerv10Dlg::Self_GetPDFFromImg(CString imgpath, CString pdfpath)
{
	CString   tem_strInputPath  = imgpath;     //导入图像路径
	CString   tem_strOutputPath = pdfpath;     //导出PDF路径


	//导出PDF--------
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
		//设置PDF属性信息******************************************************
		pPdf->set_info(_T("Creator"), _T("SmartScan"));   
		pPdf->set_info(_T("Author"), _T("UDS"));   
		pPdf->set_info(_T("Title"), _T("UDSPDF")); 
		pPdf->set_info(_T("Subject"), _T("扫描文档"));

		//图片导入***********************************************************
		{

			wstring sFilePath(tem_strInputPath.GetBuffer());
			image = pPdf->load_image(_T("auto"), sFilePath, _T(""));
			pPdf->begin_page_ext(10, 10, _T(""));
			pPdf->fit_image(image, 0, 0, _T("adjustpage dpi=0"));  //导入图像
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	if (m_vcFilePath.size()==0)
	{
		return;
	}
	//删除指定文件
	SHFILEOPSTRUCT FileOp;
	BOOL           m_BRC;    //ReturnCode操作返回码
	CString        strSrcPath;
	//删除至回收站
	strSrcPath  = m_vcFilePath[m_nRSlcIndex];
	strSrcPath += '\0';
	CString  tem_strDstPath;
	tem_strDstPath = '\0';     //删除操作，直接置为NULL
	CString     tem_strTitle;
	tem_strTitle = _T("正在删除...");
	tem_strTitle += '\0';
	FileOp.fFlags = FOF_ALLOWUNDO|FOF_MULTIDESTFILES|FOF_SIMPLEPROGRESS|FOF_NOCONFIRMATION;
	FileOp.lpszProgressTitle = tem_strTitle;
	FileOp.hwnd              = m_hWnd;
	FileOp.hNameMappings     = NULL;
	FileOp.pFrom             = strSrcPath;
	FileOp.pTo               = tem_strDstPath;    //目标目录
	FileOp.wFunc             = FO_DELETE;

	//弹窗提示--------------------------------------------------
	m_BRC = SHFileOperation(&FileOp);
	if (!FileOp.fAnyOperationsAborted)
	{
		if(m_BRC)   
		{
			//操作出现错误
		}		
	}
	else
	{
		//出现意外中止
	}
	CString   tem_strThumbPath = m_vcThumbPath[m_nRSlcIndex];
	DeleteFile(tem_strThumbPath);
	m_vcImgName.erase(m_vcImgName.begin()+m_nRSlcIndex);
	m_vcThumbPath.erase(m_vcThumbPath.begin()+m_nRSlcIndex);
	m_vcFilePath.erase(m_vcFilePath.begin()+m_nRSlcIndex);
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	//如果是在图像处理界面，删完图像还要清空PicCtrl显示
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
	// TODO: 在此添加命令处理程序代码
	CString   tem_strLastFile;
	if (m_vcFilePath.size()==0)
	{
		return;
	}
	tem_strLastFile = m_vcFilePath[m_nRSlcIndex];  //获取

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
		//调亮
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
		//调暗
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
	// TODO: 在此处添加消息处理程序代码
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
	// TODO: 在此处添加消息处理程序代码
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
//	CString      tem_strImageInfo  = _T("图像大小：");
	CString      tem_strImageInfo  = m_vcMainLang[9];
	
	CFile        tem_FileImg;
	ULONGLONG    tem_ullSize;
	
	if (tem_FileImg.Open(imgpath, CFile::modeRead))
	{
		tem_ullSize = tem_FileImg.GetLength();
		if (tem_ullSize>1024)
		{
			//转换为kb显示
			tem_ullSize = tem_ullSize/1024;
			tem_strFileByte.Format(_T("%I64d"), tem_ullSize);
			tem_strImageInfo += tem_strFileByte;
			tem_strImageInfo += _T("kb");

		}
		else
		{
			//使用字节表示
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


//全屏
//void CXRayViewerv10Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
//			MessageBox(_T("恢复"));
//			Self_NormalScreen();
//		} 
//		else
//		{
//			MessageBox(_T("全屏"));
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
	// TODO: 在此添加控件通知处理程序代码
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
	//1、判断当前是否为全屏
	if (m_BFullScreen)
	{
		return;
	}

	GetWindowPlacement(&m_OldWndPlacement);  
	CRect WindowRect;  
	GetWindowRect(&WindowRect);    
  
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowRect(&m_rcLastOCX);
	
	//获取各个控制条之外的客户区位置  
	CRect ClientRect;  
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);  
	ClientToScreen(&ClientRect);  

	//获取屏幕的分辨率  
	int nFullWidth  = GetSystemMetrics(SM_CXSCREEN);  
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);  
 
	//对话框全屏显示  
	m_FullScreenRect.left = WindowRect.left - ClientRect.left;  
	int m_top = WindowRect.top - ClientRect.top;  
	m_FullScreenRect.top    = m_top;  
	m_FullScreenRect.right  = WindowRect.right - ClientRect.right + nFullWidth;  
	m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + nFullHeight;  
 
	//进入全屏显示  
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	
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

	//获取当前的窗口的显示状态和窗体位置，一共退出时使用
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

	//设置窗口对象参数，为全屏做好准备并进入全屏状态 
	WINDOWPLACEMENT  tem_stcWndpl;  
	tem_stcWndpl.length = sizeof(WINDOWPLACEMENT);  
	tem_stcWndpl.flags = 0;  
	tem_stcWndpl.showCmd = SW_SHOWNORMAL;  
	tem_stcWndpl.rcNormalPosition = m_rcFullScreen;  
	SetWindowPlacement(&tem_stcWndpl);//该函数设置指定窗口的显示状态和显示大小位置等，是我们该程序最为重要的函数  

	GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(CRect(0, 0, tem_nScrnWidth, tem_nScrnHeight));
	m_BFullScreen = TRUE;  
	GetDlgItem(IDC_TAB_CTRL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(SW_HIDE);
 	GetDlgItem(IDC_BTN_FULLSCREEN)->EnableWindow(FALSE);

	//全屏时设置为预览模式
	m_conVideoCtrl.ManualImageCrop(FALSE);
	m_conVideoCtrl.AdjuestImageCrop(FALSE);
}


void CXRayViewerv10Dlg::Self_NormalScreen(void)
{
	if (!m_BFullScreen)
	{
		return;
	}
	
	//恢复默认窗口  
	m_BFullScreen = FALSE;
	GetDlgItem(IDC_TAB_CTRL)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_LIST_IMAGE)->ShowWindow(SW_SHOWNORMAL); 
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(&m_rcLastOCX);  
	GetDlgItem(IDC_BTN_FULLSCREEN)->EnableWindow(TRUE);

//	ShowWindow(SW_MAXIMIZE);
	CRect rcWorkArea; 
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0); 
	MoveWindow(&rcWorkArea); 
	
	if (m_BDOC)
	{
		//自动纠偏裁切
		m_conVideoCtrl.ManualImageCrop(FALSE);
		m_conVideoCtrl.AdjuestImageCrop(TRUE);
	} 
	else
	{
		//固定区域
		m_conVideoCtrl.ManualImageCrop(TRUE);
		m_conVideoCtrl.SetMessage(1);
		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conVideoCtrl.SetMessage(0);
	}

}


void CXRayViewerv10Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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


//显示PictureCtrl，并加载图像
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
			//判断是否为图像文件
			tem_strImgFormat = PathFindExtension(tem_strImgPath);
			tem_strImgFormat.MakeLower();
			if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
			{
				tem_BMark = TRUE;
				//显示图像


				//取消原高亮选项
				//高亮该项缩略图
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
		//判断是否为图像文件
		tem_strImgFormat = PathFindExtension(tem_strImgPath);
		tem_strImgFormat.MakeLower();
		if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
		{
			tem_BMark = TRUE;
		}
		else
		{
			tem_BMark = FALSE;
			//显示图像


			/*
			for (int i=m_vcFilePath.size()-1; i>=0; i--)
			{
				m_nPrcsIndex   = i;
				tem_strImgPath = m_vcFilePath[i];
				//判断是否为图像文件
				tem_strImgFormat = PathFindExtension(tem_strImgPath);
				tem_strImgFormat.MakeLower();
				if (tem_strImgFormat != _T(".pdf") && tem_strImgFormat != _T(".dcm"))
				{
					tem_BMark = TRUE;
					//高亮该项缩略图
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
		//没有图像格式文件
		m_nPrcsIndex = -1;
		m_strTabImg = _T("");

		m_BShowPicCtrl = TRUE;
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_FULLSCREEN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_DRAG)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_CURDOC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_CURDOCPATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_PIC)->ShowWindow(SW_NORMAL);

		::SendMessage(this->m_hWnd, WM_SIZE, 0, 0);

		//显示提示信息	
		Self_CVShowTipImage(_T("res\\tips.jpg"));

		return;
	}

	m_BShowPicCtrl = TRUE;
	GetDlgItem(IDC_UDS_VIDEOCTRL1)->ShowWindow(SW_HIDE);
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
//		MessageBox(_T("加载图像失败！"));
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
	m_i_w = (float)srcImg.cols;          //图像宽、高
	m_i_h = (float)srcImg.rows;
	m_p_w = (float)m_rcPicRect.right;    //控件宽、高
	m_p_h = (float)m_rcPicRect.bottom;
	if (srcImg.cols<=m_rcPicRect.right && srcImg.rows<=m_rcPicRect.bottom)
	{
		//图像尺寸<=边框尺寸
		m_nDrawX           = ((m_rcPicRect.right-m_rcPicRect.left)-srcImg.cols)/2;
		m_nDrawY           = ((m_rcPicRect.bottom-m_rcPicRect.top)-srcImg.rows)/2;
		m_rcPicRect.right  = srcImg.cols;
		m_rcPicRect.bottom = srcImg.rows;
		m_fCurRatio        = 1;
	}
	else if ((srcImg.cols*m_rcPicRect.bottom)>(srcImg.rows*m_rcPicRect.right))
	{
		//图像教宽，按照图像宽进行缩放
		int  tem_nPicHeight = m_rcPicRect.bottom - m_rcPicRect.top;
		m_ratio = m_p_w/m_i_w;
		m_rcPicRect.bottom = (int)(srcImg.rows*m_ratio);
		m_nDrawX = 0;
		m_nDrawY = (tem_nPicHeight - m_rcPicRect.bottom)/2;
		m_fCurRatio = m_ratio;
	}
	else if ((srcImg.cols*m_rcPicRect.bottom)<(srcImg.rows*m_rcPicRect.right))
	{
		//图像教高，按照图像高进行缩放
		int  tem_nPicWidth = m_rcPicRect.right - m_rcPicRect.left;
		m_ratio = m_p_h/m_i_h;
		m_rcPicRect.right = (int)(srcImg.cols*m_ratio);
		m_nDrawX = (tem_nPicWidth - m_rcPicRect.right)/2;
		m_nDrawY = 0;
		m_fCurRatio = m_ratio;
	}
	else
	{
		//尺寸比例相同，按宽或高缩放均可
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
	// TODO: 在此添加控件通知处理程序代码
	//两个if语句用于避免点击一次ListCtrl触发三次ItemChange函数
	if (pNMLV->uChanged==LVIF_STATE)
	{
		if (pNMLV->uNewState & LVIS_SELECTED)
		{
			if (m_BShowPicCtrl)
			{
				int  tem_nListIndex = pNMLV->iItem;
				if (tem_nListIndex>=0 && tem_nListIndex<m_conListCtrl.GetItemCount())
				{
					//判断图像是否保存
					if (m_vcHistoryImg.size()>2)
					{
						if (m_BNoSaved)
						{
//							int tem_nClose = MessageBox(_T("修改尚未保存！是否保存？"), _T("保存"), MB_YESNO);
							int tem_nClose = MessageBox(m_vcMainLang[10], _T("UDS"), MB_YESNO);
							if (tem_nClose == 6)
							{
								//确定保存
								CString tem_strNewImgPath = m_vcHistoryImg.back();
								CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
								m_BNoSaved = FALSE;
								Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
							}					
						}
					}
					//删除缓存图像
					if (m_vcHistoryImg.size()>1)
					{
						std::vector<CString>::iterator item;
						for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end(); item++)
						{
							DeleteFile(*item);
						}

						m_vcHistoryImg.clear();				
					}			

					//重新加载图像		
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
						//选择非图像文件，清空picture控件
						m_nPrcsIndex = -1;
						Self_ClearPicCtrl();
						//显示提示信息
						Self_CVShowTipImage(_T("res\\tips.jpg"));
						//清空当前图像
						
					}	
				}
//				m_conListCtrl.SetItemState( tem_nListIndex, 0, -1);    //-1取消高亮， 0取消选择
				
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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 1;
}


/*图像处理函数*/
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

//保存处理图像
void CXRayViewerv10Dlg::Self_SaveLastImg(void)
{
	//拿到缓存目录
	CString   tem_strFileName = m_strCVDoc;

	//获取文件后缀
	CString   tem_strFileFormat = PathFindExtension(m_strFilesPath);

	//获取当前时间精确到毫秒
	SYSTEMTIME   tem_stDateTime;
	CString      tem_strDate = _T("");
	CString      tem_strTime = _T("");
	GetLocalTime(&tem_stDateTime);
	tem_strDate.Format(_T("%d%02d%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay);
	tem_strTime.Format(_T("%02d%02d%02d%02d"), tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond, tem_stDateTime.wMilliseconds); 

	//输出新的文件名
	tem_strFileName += _T("\\");
	tem_strFileName += tem_strDate;
	tem_strFileName += tem_strTime;
	tem_strFileName += tem_strFileFormat;

	//保存图像
	std::string tem_sFilePath = (CStringA)tem_strFileName; 
	imwrite(tem_sFilePath, m_cvNextImg);
	m_vcHistoryImg.push_back(tem_strFileName);
}

//图像旋转
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

//图像镜像
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
		//水平镜像
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
		//垂直镜像
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

//反色
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

//锐化
Mat CXRayViewerv10Dlg::ImageSharp(Mat img)
{
	Mat   kernel(3, 3, CV_32F, Scalar(0));
	/*算子1
	kernel.at<float>(0,0) = 0;    kernel.at<float>(0,1) = -1.0; kernel.at<float>(0,2) = 0;
	kernel.at<float>(1,0) = -1.0; kernel.at<float>(1,1) = 5.0;  kernel.at<float>(1,2) = -1.0;
	kernel.at<float>(2,0) = 0;    kernel.at<float>(2,1) = -1.0; kernel.at<float>(2,2) = 0;
	*/


	/*算子2
	kernel.at<float>(0,0) = 1.0; kernel.at<float>(0,1) = 1.0;  kernel.at<float>(0,2) = 1.0;
	kernel.at<float>(1,0) = 1.0; kernel.at<float>(1,1) = -8.0; kernel.at<float>(1,2) = 1.0;
	kernel.at<float>(2,0) = 1.0; kernel.at<float>(2,1) = 1.0;  kernel.at<float>(2,2) = 1.0;
	*/

	kernel.at<float>(0,0) = -1.0/7; kernel.at<float>(0,1) = -2.0/7;  kernel.at<float>(0,2) = -1.0/7;
	kernel.at<float>(1,0) = -2.0/7; kernel.at<float>(1,1) = 19.0/7;   kernel.at<float>(1,2) = -2.0/7;
	kernel.at<float>(2,0) = -1.0/7; kernel.at<float>(2,1) = -2.0/7;  kernel.at<float>(2,2) = -1.0/7;

	Mat    tem_cvMidImage;
	tem_cvMidImage.create(img.size(), img.type());
	filter2D(img, tem_cvMidImage, img.depth(), kernel);    //depth参数为-1时，生成图像与原图保持一致。
	

	return tem_cvMidImage;
}

//亮度、对比度
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
		//灰度、黑白单通道图像
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

//Gama调整
Mat CXRayViewerv10Dlg::ImageGamma(Mat img, int gama)
{
	float  tem_fGama = (float)gama*1.0/100;
	Mat    tem_cvMidImage = img.clone();
	//建立查表文件LUT
	unsigned char LUT[256];
	for (int i=0; i<256; i++)
	{
		//Gamma变换表达式
		LUT[i] = saturate_cast<uchar>(pow((float)(i/255.0), tem_fGama) * 255.0f);
	}

	//判断图像通道数量
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
		//三通道 时对每个通道单独处理
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


//视图处理——放大、缩小、裁切、旋转
void CXRayViewerv10Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ClientToScreen(&point);

	if (m_BPaintLine)
	{
		//记录画线起点
		CRect tem_rcPic = m_rcImageShow;
		//将picture控件区域修改为图像区域
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
		//选区**********************************
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
		//拖动***********************************
		m_BLButtonDown = TRUE;
		ClientToScreen(m_rcImageShow);
		if (m_rcImageShow.PtInRect(point))
		{
			SetCapture();
			SetCursor(LoadCursor(NULL,IDC_HAND));
			m_ptDragOri = point;       //拖动起点
			m_ptDragEnd = point;
		}
		ScreenToClient(m_rcImageShow);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CXRayViewerv10Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_BLButtonDown)
	{
		if (m_BPaintLine)
		{
			//画线函数
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
				//画线函数
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
				//随意画
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

			int tem_nDragSpeed = 5;   //控制拖动速度，数值越大拖动越慢
			int tem_nOffSetX = m_ptDragEnd.x-m_ptDragOri.x;
			int tem_nOffSetY = m_ptDragEnd.y-m_ptDragOri.y;
			//拖动重绘
			int tem_nImageWidth  = m_cvSrcImage.cols;   //图像原始尺寸
			int tem_nImageHeight = m_cvSrcImage.rows;

			int tem_nThumbWidth  = 0;          //放大、缩小后缩略图尺寸
			int tem_nThumbHeight = 0;

			CRect   tem_rcPicRect; 
			GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
			ScreenToClient(&tem_rcPicRect);


			float   tem_fCurRatio = m_fCurRatio;

			int     tem_nDrawX, tem_nDrawY, tem_nDrawW, tem_nDrawH;   //映射起点以及宽高

			//放大后缩略图尺寸
			tem_nThumbWidth  = (int)(tem_fCurRatio*tem_nImageWidth);
			tem_nThumbHeight = (int)(tem_fCurRatio*tem_nImageHeight);
			//1)缩放图尺寸<picture控件尺寸*****************************
			//不能拖动

			//2)缩放图宽<picture宽，且缩放图高>picture高
			if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
			{
				//图像显示区域
				m_rcImageRect.left     = 0;
				m_rcImageRect.right    = m_cvSrcImage.cols;

				//源图显示区域的的真实高m_cvSrcImage.rows*(tem_nOffSetY*1.0/tem_nThumbHeight);
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
			//3)缩放图宽>picctrl宽，且缩放图高<picctrl高
			else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
			{
				//图像显示区域

				m_rcImageRect.top      = 0;
				m_rcImageRect.bottom   = m_cvSrcImage.rows;
				//源图显示区域的真是宽m_cvSrcImage.cols*(tem_nOffSetX*1.0/tem_nThumbWidth)
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
			//4)缩放图宽>picctrl宽，且缩放图高>picctrl高
			else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
			{
				//图像显示区域
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

	// TODO: 在此处添加消息处理程序代码
}


void CXRayViewerv10Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_BLButtonDown)
	{
		if (m_BPaintLine)
		{
			BOOL     tem_BOrientation = TRUE;   //旋转方向标志位，默认顺时针
			double   tem_dRadian = 0;     //弧度
			int      tem_nAngle  = 0;     //角度
			m_BLButtonDown = FALSE;
//			m_BPaintLine   = FALSE;
			ReleaseCapture();
			SetCursor(LoadCursor(NULL,IDC_ARROW));	

			//根据坐标点求出旋转直线与X轴正向夹角
			if (m_ptOri == m_ptEnd)
			{
				//未画线，无夹角
				tem_nAngle = 0;
				tem_BOrientation = TRUE;

			}
			else if (m_ptOri.x==m_ptEnd.x && m_ptOri.y!=m_ptEnd.y)
			{
				//夹角为90度，垂直方向
				tem_nAngle = 90;
				//从上到下为顺，从下到上为逆
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
				//夹角为0度，水平方向
				tem_nAngle = 0;
				tem_BOrientation = TRUE;
			}
			else
			{
				//求夹角
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
			
			//旋转图像
			m_nAngleCount += tem_nAngle;
			m_cvDstImage = ImageRotate(m_cvSrcImage, m_nAngleCount);
//			m_cvDstImage = ImageRotate(m_cvSrcImage, tem_nAngle);
			//更新视图
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

			//考虑鼠标从左上、左下、右上、右下四种方向画选取
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

				//考虑鼠标从左上、左下、右上、右下四种方向画选取
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
				//起始点坐标——m_pOri;  终点坐标——m_pEnd;
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
				//画一小段标记线
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

				m_cvDstImage = Self_AddText(m_cvSrcImage, m_rcImageShow, m_rcImageCrop, _T("紫光图文"), m_refLineColor, m_strFont, m_nFontSize, m_BBold, m_BItalic);

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	BOOL      tem_BRC;
	CPoint    tem_ptCurPoint = pt;

	if (zDelta>0)
	{
		//放大
		tem_BRC = Self_ZoomSize(m_cvSrcImage, m_fCurRatio, TRUE);
		if(tem_BRC)
		{
			m_fCurRatio+=0.05;
		}

	}
	else
	{
		//缩小
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
	int tem_nImageWidth  = src.cols;   //图像原始尺寸
	int tem_nImageHeight = src.rows;

	int tem_nThumbWidth  = 0;          //放大、缩小后缩略图尺寸
	int tem_nThumbHeight = 0;

	CRect   tem_rcPicRect; 
	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
	ScreenToClient(&tem_rcPicRect);


	float   tem_fCurRatio = ratio;

	int     tem_nDrawX, tem_nDrawY, tem_nDrawW, tem_nDrawH;   //映射起点以及宽高

	if (zoommark)
	{
		//放大************************************
		tem_fCurRatio += 0.05;        //一次放大5%
	}
	else
	{
		//缩小************************************
		tem_fCurRatio -= 0.05;        //一次缩小5%
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

	//放大后缩略图尺寸
	tem_nThumbWidth  = (int)(tem_fCurRatio*tem_nImageWidth);
	tem_nThumbHeight = (int)(tem_fCurRatio*tem_nImageHeight);
	//1)放大后缩略图尺寸<picture控件尺寸
	if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
	}
	//2)放大后缩略图宽<picture宽，且缩略图高>picture高
	else if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域
		m_rcImageRect.left     = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;

		//源图显示区域的的真实高m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);

	}
	//3)放大后缩略图宽>picture宽，且缩略图高<picture高
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = 0;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域

		m_rcImageRect.top      = 0;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
		//源图显示区域的真是宽m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth)
		m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);	

	}
	//4）放大后缩略图宽>picture宽，且缩略图高>picture高
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = 0;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;

		//图像显示区域
		m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);


	}
	//该判断仅用于1:1显示标志位
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
	int tem_nImageWidth  = src.cols;   //图像原始尺寸
	int tem_nImageHeight = src.rows;

	int tem_nThumbWidth  = src.cols;          //放大、缩小后缩略图尺寸
	int tem_nThumbHeight = src.rows;

	CRect   tem_rcPicRect; 
	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
	ScreenToClient(&tem_rcPicRect);

	int     tem_nDrawX, tem_nDrawY, tem_nDrawW, tem_nDrawH;   //映射起点以及宽高

	//1)放大后缩略图尺寸<picture控件尺寸
	if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域
		m_rcImageRect.left     = 0;
		m_rcImageRect.top      = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
	}
	//2)放大后缩略图宽<picture宽，且缩略图高>picture高
	else if (tem_nThumbWidth<tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = (tem_rcPicRect.Width()-tem_nThumbWidth)/2;
		tem_nDrawY           = 0;
		tem_nDrawW           = tem_nThumbWidth;
		tem_nDrawH           = tem_rcPicRect.Height();
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域
		m_rcImageRect.left     = 0;
		m_rcImageRect.right    = m_cvSrcImage.cols;

		//源图显示区域的的真实高m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);
		m_rcImageRect.top      = (m_cvSrcImage.rows-m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight))/2;
		m_rcImageRect.bottom   = m_rcImageRect.top+m_cvSrcImage.rows*(tem_rcPicRect.Height()*1.0/tem_nThumbHeight);

	}
	//3)放大后缩略图宽>picture宽，且缩略图高<picture高
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight<tem_rcPicRect.Height())
	{
		//picture显示区域
		tem_nDrawX           = 0;
		tem_nDrawY           = (tem_rcPicRect.Height()-tem_nThumbHeight)/2;
		tem_nDrawW           = tem_rcPicRect.Width();
		tem_nDrawH           = tem_nThumbHeight;
		m_rcImageShow.left   = tem_nDrawX;
		m_rcImageShow.top    = tem_nDrawY;
		m_rcImageShow.right  = tem_nDrawX + tem_nDrawW;
		m_rcImageShow.bottom = tem_nDrawY + tem_nDrawH;
		//图像显示区域

		m_rcImageRect.top      = 0;
		m_rcImageRect.bottom   = m_cvSrcImage.rows;
		//源图显示区域的真是宽m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth)
		m_rcImageRect.left     = (m_cvSrcImage.cols-m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth))/2;
		m_rcImageRect.right    = m_rcImageRect.left+m_cvSrcImage.cols*(tem_rcPicRect.Width()*1.0/tem_nThumbWidth);	

	}
	//4）放大后缩略图宽>picture宽，且缩略图高>picture高
	else if (tem_nThumbWidth>tem_rcPicRect.Width() && tem_nThumbHeight>tem_rcPicRect.Height())
	{
		//picture显示区域
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


		//图像显示区域
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

	//起点超出图像
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

	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //裁切显示宽度
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //裁切显示高度
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //显示宽度
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //显示高度

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //起点坐标比例
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	float  tem_fWidthPropertion = tem_nCropWidth*1.0/tem_nShowWidth;          //裁切区域对显示区域的占比
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

	//终点超出图像
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

	//起点超出图像
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

	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //裁切显示宽度
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //裁切显示高度
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //显示宽度
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //显示高度

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //起点坐标比例
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	float  tem_fWidthPropertion = tem_nCropWidth*1.0/tem_nShowWidth;          //裁切区域对显示区域的占比
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
	//获取画框颜色
	int  tem_nRed   = GetRValue(linecolor);
	int  tem_nGreen = GetGValue(linecolor);
	int  tem_nBlue  = GetBValue(linecolor);
	rectangle(tem_cvMidImage, tem_crcDst, Scalar(tem_nBlue, tem_nGreen, tem_nRed), linewidth, 8, 0);

	//终点超出图像
	return tem_cvMidImage;
}


BOOL CXRayViewerv10Dlg::Self_DisableCtrl(int index)
{
	return FALSE;
}


BOOL CXRayViewerv10Dlg::Self_EnsureSave(void)
{
	//确定图像处理是否保存
	if (m_vcFilePath.size()==0)
	{
		return FALSE;
	}
	if (m_vcHistoryImg.size()>2)
	{
		if (m_BNoSaved)
		{
//			int tem_nClose = MessageBox(_T("修改尚未保存！是否保存？"), _T("保存"), MB_YESNO);
			int tem_nClose = MessageBox(m_vcMainLang[10], _T("UDS"), MB_YESNO);
			if (tem_nClose == 6)
			{
				//确定保存
				CString tem_strNewImgPath = m_vcHistoryImg.back();
				CopyFile(tem_strNewImgPath, m_strFilesPath, FALSE);
				m_BNoSaved = FALSE;
				Self_UpdateThumb(m_nPrcsIndex, m_strFilesPath);
			}
			//无论是否保存修改都要清除缓存图像
			std::vector<CString>::iterator  item;
			for (item=m_vcHistoryImg.begin()+1; item!=m_vcHistoryImg.end(); item++)
			{
				DeleteFile(*item);
			}
		}
	}
	else if (m_vcHistoryImg.size()==2)
	{
		//删除缓存图像
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
	CString    tem_strItemName = m_vcImgName[item];      //地址和名称对应vector中存放的文件的真实索引
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
	m_conListCtrl.RedrawItems(item, item);           //ListCtrl重绘对应当前页面中Item的索引
	DeleteDC(hDC);
	DeleteObject(bm);

	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBkground);	

}


int CXRayViewerv10Dlg::Self_Test(void)
{
	CRect   tem_rcOcx;

	CRect   tem_rcOldVideo;     //原摄像头区域
	CRect   tem_rcOldRect;      //原裁切区域
	CRect   tem_rcNewVideo;     //新摄像头区域

	//原视频区域的宽、高
	int   tem_nOVWidth  = tem_rcOldVideo.Width();
	int   tem_nOVHeight = tem_rcOldVideo.Height();

	//新视频区域的宽、高
	int   tem_nNVWidth  = tem_rcNewVideo.Width();
	int   tem_nNVHeight = tem_rcNewVideo.Height();

	//原裁切区域的宽高
	int   tem_nORWidth  = tem_rcOldRect.Width();
	int   tem_nORHeight= tem_rcOldRect.Height();

	//新裁切区域的宽高
	int   tem_nNRWidth  = (int)(tem_nORHeight*tem_nNVWidth/tem_nOVHeight*1.0);
	int   tem_nNRHeight = (int)(tem_nORWidth*tem_nNVHeight/tem_nOVWidth*1.0);

	//新裁切区域的起始点坐标
	int   tem_nNRX      = tem_rcNewVideo.left + ((tem_rcOldVideo.bottom-tem_rcOldRect.bottom)*tem_rcNewVideo.Width()/tem_rcOldVideo.Height()*1.0);
	int   tem_nNRY      = tem_rcNewVideo.top + ((tem_rcOldRect.left-tem_rcOldVideo.left)*tem_rcNewVideo.Height()/tem_rcOldVideo.Width()*1.0);

	return 0;
}


afx_msg LRESULT CXRayViewerv10Dlg::OnRefreshimg(WPARAM wParam, LPARAM lParam)
{
// 	CRect rtlbl; 
// 	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&rtlbl); 
// 	ScreenToClient(&rtlbl); //转到客户端界面
// 	InvalidateRect(&rtlbl);//最后刷新对话框背景 
// 	UpdateWindow();
	return 0;
}


void CXRayViewerv10Dlg::OnBnClickedBtnDrag()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//根据输入图像求输出图像的路径
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
	delete tem_dcm;

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
	int    tem_nResCount = m_conVideoCtrl.GetResCount();  //设备分量率数量
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
	//对vector进行排序，同时索引对应相应的的值,由小到大
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
	int       tem_nGoalResoW        = 0;          //目标分辨率
	int       tem_nGoalResoH        = 0;
	float     tem_fRateW            = 0;          //转换率宽
	float     tem_fRateH            = 0;

	long*     tem_lWidth;
	tem_lWidth  = new long;
	long*     tem_lHeight;  
	tem_lHeight = new long;
	float     tem_fWidth;
	float     tem_fHeight;

	CString   tem_strSrcImage       = srcImage;     //原图路径
	CString   tem_strDstImage       = dstImage;     //目标图路径

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

	//判断图像格式
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
	CString   tem_strInputPath  = srcImg;     //导入图像路径
	CString   tem_strOutputPath = dstImg;     //导出PDF路径


	//导出PDF--------
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
		//设置PDF属性信息******************************************************
		pPdf->set_info(_T("Creator"), _T("SmartScan"));   
		pPdf->set_info(_T("Author"), _T("UDS"));   
		pPdf->set_info(_T("Title"), _T("UDSPDF")); 
		pPdf->set_info(_T("Subject"), _T("扫描文档"));

		//图片导入***********************************************************
		{

			wstring sFilePath(tem_strInputPath.GetBuffer());
			image = pPdf->load_image(_T("auto"), sFilePath, _T(""));
			pPdf->begin_page_ext(10, 10, _T(""));
			pPdf->fit_image(image, 0, 0, _T("adjustpage dpi=0"));  //导入图像
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

//value目标值，即灯箱预设值，src灯箱原值
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
			//调亮--------------------------------------------------------
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
			//调暗---------------------------------------------------------
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

#include "MMsystem.h"   //延时函数,精度毫秒
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
	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //裁切显示宽度
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //裁切显示高度
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //显示宽度
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //显示高度

	if (tem_rcCrop.left==tem_rcCrop.right || tem_rcCrop.top==tem_rcCrop.bottom)
	{
		return img;
	}

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //起点坐标比例
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	int    tem_nDstWidth   = img.cols* tem_fXPropertion;
	int    tem_nDstHeith   = img.rows*tem_fYPropertion;
	cv::Point  tem_ptNewOri(tem_nDstWidth, tem_nDstHeith);

	tem_fXPropertion     = (tem_rcCrop.right-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);         //终点坐标比例
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



	theta=3.1415926*theta/180;//转换为弧度
	double Px,Py,P1x,P1y,P2x,P2y;
	//以P2为原点得到向量P2P1（P）
	Px=p1.x-p2.x;
	Py=p1.y-p2.y;
	//向量P旋转theta角得到向量P1
	P1x=Px*cos(theta)-Py*sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	//伸缩向量至制定长度
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*length/x1;
	P1y=P1y*length/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	P2y=P2y*length/x2;
	//平移变量到直线的末端
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	CClientDC dc(this);//获取客户窗口DC
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


//参数说明：Mat图像， 图像上的坐标起点， 图像上的坐标终点， 箭头头部反折长度， 箭头反折夹角， 线颜色， 线宽， 线型
Mat CXRayViewerv10Dlg::drawArrow(Mat img, cv::Point pStart, cv::Point pEnd, int len, int alpha, cv::Scalar& color, int thickness, int lineType)
{
	const double tem_PI = 3.1415926;

	cv::Point arrow;
	double angle = atan2((double)(pStart.y - pEnd.y), (double)(pStart.x - pEnd.x));
	line(img, pStart, pEnd, color, thickness, lineType);

	//计算箭角边的另一端的端点位置（上面的还是下面的要看箭头的指向，也就是pStart和pEnd的位置） 
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
	int    tem_nCropWidth  = tem_rcCrop.right-tem_rcCrop.left;    //裁切显示宽度
	int    tem_nCropHeight = tem_rcCrop.bottom-tem_rcCrop.top;    //裁切显示高度
	int    tem_nShowWidth  = tem_rcShow.right-tem_rcShow.left;    //显示宽度
	int    tem_nShowHeight = tem_rcShow.bottom-tem_rcShow.top;    //显示高度

	float  tem_fXPropertion     = (tem_rcCrop.left-tem_rcShow.left)*1.0/(tem_rcShow.right-tem_rcShow.left);   //起点坐标比例
	float  tem_fYPropertion     = (tem_rcCrop.top-tem_rcShow.top)*1.0/(tem_rcShow.bottom-tem_rcShow.top);
	int    tem_nDstWidth   = src.cols* tem_fXPropertion;
	int    tem_nDstHeith   = src.rows*tem_fYPropertion;
	

	wchar_t*    tem_wsInfo = textinfo.GetBuffer();                //内容
	int         tem_nRed   = GetRValue(color);                    //颜色
	int         tem_nGreen = GetGValue(color);
	int         tem_nBlue  = GetBValue(color);
	wchar_t*    tem_wsFont = m_strFont.GetBuffer();
	int         tem_nSize  = fontsize;
	
	
	int   iSize;
	char* pszMultiByte;
	char* pszFont;

	//返回接受字符串所需缓冲区的大小，已经包含字符结尾符'\0'
	iSize = WideCharToMultiByte(CP_ACP, 0, tem_wsInfo, -1, NULL, 0, NULL, NULL); 
	pszMultiByte = (char*)malloc(iSize*sizeof(char)); //不需要 pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
	WideCharToMultiByte(CP_ACP, 0, tem_wsInfo, -1, pszMultiByte, iSize, NULL, NULL);

	iSize = WideCharToMultiByte(CP_ACP, 0, tem_wsFont, -1, NULL, 0, NULL, NULL); 
	pszFont = (char*)malloc(iSize*sizeof(char)); //不需要 pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
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
//	lf.lfWeight = 5;                      //重量即为粗细0~1000，正常情况为400，加粗为700
	if (bold)
	{
		lf.lfWeight = 700;
	}
	else
	{
		lf.lfWeight = 400;
	}
	
	lf.lfItalic = italic;   //斜体
	lf.lfUnderline = underline; //下划线
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
	char *bufT[1 << 12];  // 这个用于分隔字符串后剩余的字符，可能会超出。
	//处理多行
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


int CXRayViewerv10Dlg::Self_GetIntervalTime(void)
{
	std::vector<CString> tem_vcBuffers;
	//预览模式
	m_conVideoCtrl.ManualImageCrop(FALSE);
	m_conVideoCtrl.AdjuestImageCrop(FALSE);

	int tem_nCapCount = 0;
	/*a、拍摄首张图像*/
// 	CString tem_strBegin = m_strThumbDoc;
// 	tem_strBegin += _T("\\计算间隔时间.jpg");
// 	m_conVideoCtrl.CaptureImage(tem_strBegin);
	

	/*b、调节灯箱亮度*/
	AdjustRelay(50, 10);
	DWORD tem_DBegin = GetTickCount();
	double tem_dLastGray = 0.0, tem_dNextGray = 5.0, tem_dMidGray=0.0;
	/*c、拍摄第一幅图像*/
	CString tem_strLast = m_strThumbDoc;
	tem_strLast += _T("\\CountTime_1.jpg");
	
	m_conVideoCtrl.CaptureImage(tem_strLast);
	tem_vcBuffers.push_back(tem_strLast);
	if(PathFileExists(tem_strLast))
	{
		tem_nCapCount++;
		tem_dLastGray = Self_GetAvgGray(tem_strLast);
	}
	
	while(abs(tem_dNextGray-tem_dLastGray)>=3)
	{
		CString tem_strNext = m_strThumbDoc;
		CString str;
		str.Format(_T("%d"), tem_nCapCount);
		tem_strNext += _T("\\CountTime_2_");
		tem_strNext += str;
		tem_strNext += _T(".jpg");
		/*d、拍摄下一幅图像*/
		m_conVideoCtrl.CaptureImage(tem_strNext);
		tem_vcBuffers.push_back(tem_strNext);
		if(PathFileExists(tem_strNext))
		{
			tem_nCapCount++;
			tem_dNextGray = Self_GetAvgGray(tem_strNext);
		}
		
		if (abs(tem_dNextGray-tem_dLastGray)<3)
		{
			break;
		} 
		else
		{
			tem_dLastGray = tem_dNextGray;
			tem_dNextGray = 0;
		}
	}
	DWORD tem_DEnd = GetTickCount();
// 	CString str;
// 	str.Format(_T("%d"), (tem_DEnd-tem_DBegin));
// 	MessageBox(str);
	/*e、求平均时长*/
	int tem_nAvgTime = 2000;
	if (tem_nCapCount!=0)
	{
		tem_nAvgTime = (int)(tem_DEnd-tem_DBegin)/tem_nCapCount;
	}
	
	/*f、删除缓存图像，恢复灯箱亮度*/
	std::vector<CString>::iterator tem_it;
	for (tem_it = tem_vcBuffers.begin(); tem_it != tem_vcBuffers.end(); tem_it++)
	{
		::DeleteFile(*tem_it);
	}
// 	::DeleteFile(tem_strBegin);
// 	::DeleteFile(tem_strLast);
// 	::DeleteFile(tem_strNext);

	AdjustRelay(10, 50);

	if (m_BDOC)
	{
		//恢复为自动裁切
		m_conVideoCtrl.ManualImageCrop(FALSE);
		m_conVideoCtrl.AdjuestImageCrop(TRUE);
	} 
	else
	{
		//恢复为固定区域
		m_conVideoCtrl.ManualImageCrop(TRUE);
		m_conVideoCtrl.SetMessage(1);
		m_conVideoCtrl.SetRectValue(m_lLeftSite, m_lTopSite, m_lRightSite, m_lBottomSite);
		m_conVideoCtrl.SetMessage(0);
	}
	

	return tem_nAvgTime;
}


double CXRayViewerv10Dlg::Self_GetAvgGray(CString imgpath)
{
	/*1、加载图像*/
	CStringA tem_straImgPath(imgpath);
	string tem_sImgPath = tem_straImgPath.GetBuffer(0);
	tem_straImgPath.ReleaseBuffer();
	Mat tem_cvImg = imread(tem_sImgPath, IMREAD_GRAYSCALE);

	/*2、像素遍历，获取平均灰度*/
	double tem_dAvgGray = 0.0;
	double tem_dSumGray = 0.0;
	int    tem_nRow     = tem_cvImg.rows;
	int    tem_nCol     = tem_cvImg.cols*tem_cvImg.channels();
	for(int i=0; i<tem_nRow; i++)
	{
		uchar*  tem_pRow = tem_cvImg.ptr<uchar>(i);
		for (int j=0; j<tem_nCol; j++)
		{
			tem_dSumGray += tem_pRow[j];
		}
	}

//	tem_dAvgGray = (double)tem_dSumGray/(tem_cvImg.rows*tem_cvImg.cols);
	tem_dAvgGray = (double)tem_dSumGray/((tem_cvImg.rows*tem_cvImg.cols)/6);
	tem_cvImg.release();

	return tem_dAvgGray;
}


void CXRayViewerv10Dlg::Self_HDRMergeImgEx(CString LowImg, CString NorImg, CString HigImg, CString OutImg, int mode, int lowlight_L, int norlight_L, int higlight_L, int lowlight_H, int norlight_H, int higlight_H)
{
	CString tem_strSendInfo = _T("");
	tem_strSendInfo  = LowImg; tem_strSendInfo += _T("#$");
	tem_strSendInfo += NorImg; tem_strSendInfo += _T("#$");
	tem_strSendInfo += HigImg; tem_strSendInfo += _T("#$");
	tem_strSendInfo += OutImg; tem_strSendInfo += _T("#$");
	
	CString tem_strMid = _T("");
	tem_strMid.Format(_T("%d"), mode); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");

	tem_strMid.Format(_T("%d"), lowlight_L); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");
	tem_strMid.Format(_T("%d"), norlight_L); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");
	tem_strMid.Format(_T("%d"), higlight_L); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");

	tem_strMid.Format(_T("%d"), lowlight_H); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");
	tem_strMid.Format(_T("%d"), norlight_H); tem_strSendInfo += tem_strMid; tem_strSendInfo += _T("#$");
	tem_strMid.Format(_T("%d"), higlight_H); tem_strSendInfo += tem_strMid; 

	CString  tem_strAllInfo = _T("\"");
	tem_strAllInfo += tem_strSendInfo;
	tem_strAllInfo += _T("\"");
	ShellExecute(NULL, _T("open"), _T("UDSGenerateIt.exe"), tem_strAllInfo, NULL, SW_SHOWNORMAL);
}


afx_msg LRESULT CXRayViewerv10Dlg::OnSettext(WPARAM wParam, LPARAM lParam)
{
	CString tem_strInfo = _T("");
	::GetPrivateProfileString(_T("BaseSet"), _T("TalkCode"), _T("没有找到TalkCode信息"), tem_strInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);

	if (tem_strInfo == _T("3"))
	{
	
	CString tem_strLowImg    = m_vcSomeStrInfo[0];
	CString tem_strNorImg    = m_vcSomeStrInfo[1];
	CString tem_strHigImg    = m_vcSomeStrInfo[2];
	CString tem_strHDRImg    = m_vcSomeStrInfo[3];
	CString tem_strThumbPath = m_vcSomeStrInfo[4];
	CString tem_strIntImg    = m_vcSomeStrInfo[5];
	CString tem_strFilePath  = m_vcSomeStrInfo[6];
	CString imgname          = m_vcSomeStrInfo[7];
	
	m_dlgOne.Self_HideCtrls(8);
	//等待子程序生成完毕再继续-----------------------------------------------------------
	//删除缓存图像----------------------------------------------------------------------
	::DeleteFile(tem_strHigImg);
	::DeleteFile(tem_strNorImg);
	::DeleteFile(tem_strLowImg);

	//是否需要添加水印-------------------------------------------------------------------
	if (m_nWaterMark == 1)
	{
		Self_AddWaterMark(tem_strHDRImg);
		m_dlgOne.Self_HideCtrls(9);
	}

	//创建缩略图------------------------------------------------------------------------
	Self_CreateThumb(tem_strHDRImg, tem_strThumbPath);
	m_dlgOne.Self_HideCtrls(10);

	//是否需要插值----------------------------------------------------------------------
	if (m_nLastRes==m_nInterpolateReso)
	{
		Self_InterPolateImage(tem_strHDRImg, tem_strIntImg, 0);
		::DeleteFile(tem_strHDRImg);
		tem_strHDRImg = tem_strIntImg;
	}

	//判断图像格式----------------------------------------------------------------------
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

		delete tem_dcm;
	
	}
	else if (m_nLastImgType == 3)
	{
		//将jpg图像转为tif图像
		CxImage tem_cxJPG;
		tem_cxJPG.Load(tem_strHDRImg, CMAX_IMAGE_FORMATS);
		tem_cxJPG.SetCodecOption(5, CXIMAGE_FORMAT_TIF);
		tem_cxJPG.Save(tem_strFilePath, CXIMAGE_FORMAT_TIF);	 
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
	m_dlgOne.Self_HideCtrls(11);

	Self_ShowImgInfo(tem_strFilePath);
	m_nImageCount++;
	m_vcSomeStrInfo.clear();

	m_dlgOne.Self_HideCtrls(0);
	}
	else if (tem_strInfo == _T("1"))
	{
		m_dlgOne.Self_HideCtrls(6);
	}
	else if (tem_strInfo == _T("2"))
	{
		m_dlgOne.Self_HideCtrls(7);
	}
	::WritePrivateProfileString(_T("BaseSet"), _T("TalkCode"), _T("0"), m_strIniPath);
//	MessageBox(_T("Over"));
	return 0;
}