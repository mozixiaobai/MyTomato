// UDSONE.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSONE.h"
#include "afxdialogex.h"


extern CString  g_strProXmlPath;
extern CString  g_strDocXmlPath;        
extern std::vector<CString> g_vcRes;
extern std::vector<int>     g_vcSlid;

// CUDSONE �Ի���
IMPLEMENT_DYNAMIC(CUDSONE, CDialogEx)

CUDSONE::CUDSONE(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSONE::IDD, pParent)
{

}

CUDSONE::~CUDSONE()
{
}

void CUDSONE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_TEM, m_conTemplate);
	DDX_Control(pDX, IDC_CMB_RES, m_conResolution);
	DDX_Control(pDX, IDC_CMB_TYPE, m_conImgType);
	DDX_Control(pDX, IDC_SLID_BRIGHT, m_slidABright);
	DDX_Control(pDX, IDC_SLID_CONTRAST, m_slidAContrast);
	DDX_Control(pDX, IDC_RICHEDIT_INFO, m_conRichEdit);
	DDX_Control(pDX, IDC_SLID_LIGHT, m_slidALightBox);
	DDX_Control(pDX, IDC_BTN_SCAN, m_btnScan);
	DDX_Control(pDX, IDC_BTN_SLCDOC, m_btnSDoc);
	DDX_Control(pDX, IDC_BTN_WATER, m_btnWater);
	DDX_Control(pDX, IDC_BTN_NAME, m_btnName);
	DDX_Control(pDX, IDC_BTN_REDUCE, m_btnSetView);
	DDX_Control(pDX, IDC_BTN_DEFAULT, m_btnRecoverTem);
	DDX_Control(pDX, IDC_BTN_SCANHDR, m_btnHDR);
	DDX_Control(pDX, IDC_SLID_AGRAYLEVEL, m_slidGray);
	DDX_Control(pDX, IDC_BTN_HDRCAP, m_btnHDRCap);
	DDX_Control(pDX, IDC_BTN_LDRCAP, m_btnLDRCap);
	DDX_Control(pDX, IDC_SLID_ADFOCUS, m_slidAdjFocus);
}


BEGIN_MESSAGE_MAP(CUDSONE, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CMB_TEM, &CUDSONE::OnSelchangeCmbTem)
	ON_CBN_SELCHANGE(IDC_CMB_RES, &CUDSONE::OnSelchangeCmbRes)
	ON_CBN_SELCHANGE(IDC_CMB_TYPE, &CUDSONE::OnSelchangeCmbType)
	ON_COMMAND(IDC_RADIO_R0, &CUDSONE::OnRadioR0)
	ON_COMMAND(IDC_RADIO_R1, &CUDSONE::OnRadioR1)
	ON_COMMAND(IDC_RADIO_R2, &CUDSONE::OnRadioR2)
	ON_COMMAND(IDC_RADIO_R3, &CUDSONE::OnRadioR3)
	ON_BN_CLICKED(IDC_CHK_HMERGE, &CUDSONE::OnClickedChkHmerge)
	ON_BN_CLICKED(IDC_CHK_VMERGE, &CUDSONE::OnClickedChkVmerge)
	ON_BN_CLICKED(IDC_CHK_WATERMARK, &CUDSONE::OnClickedChkWatermark)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_BRIGHT, &CUDSONE::OnCustomdrawSlidBright)
	ON_BN_CLICKED(IDC_CHK_BRI, &CUDSONE::OnClickedChkBri)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_CONTRAST, &CUDSONE::OnCustomdrawSlidContrast)
	ON_BN_CLICKED(IDC_CHK_CONTRAST, &CUDSONE::OnClickedChkContrast)
	ON_BN_CLICKED(IDC_BTN_SLCDOC, &CUDSONE::OnBnClickedBtnSlcdoc)
	ON_BN_CLICKED(IDC_BTN_SCAN, &CUDSONE::OnBnClickedBtnScan)
	ON_BN_CLICKED(IDC_BTN_WATER, &CUDSONE::OnBnClickedBtnWater)
	ON_BN_CLICKED(IDC_BTN_NAME, &CUDSONE::OnBnClickedBtnName)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, &CUDSONE::OnBnClickedBtnDefault)
	ON_BN_CLICKED(IDC_BTN_ENHENCE, &CUDSONE::OnBnClickedBtnEnhence)
	ON_BN_CLICKED(IDC_BTN_REDUCE, &CUDSONE::OnBnClickedBtnReduce)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CUDSONE::OnBnClickedBtnClose)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_LIGHT, &CUDSONE::OnCustomdrawSlidLight)
	ON_COMMAND(IDC_RADIO_FREERECT, &CUDSONE::OnRadioFreerect)
	ON_COMMAND(IDC_RADIO_MAXRECT, &CUDSONE::OnRadioMaxrect)
	ON_COMMAND(IDC_RADIO_PARTVIEW, &CUDSONE::OnRadioPartview)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SCAN2, &CUDSONE::OnBnClickedBtnScan2)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_AGRAYLEVEL, &CUDSONE::OnCustomdrawSlidAgraylevel)
	ON_BN_CLICKED(IDC_BTN_SCANHDR, &CUDSONE::OnBnClickedBtnScanhdr)
	ON_BN_CLICKED(IDC_RADIO_DOCUMENT, &CUDSONE::OnBnClickedRadioDocument)
	ON_BN_CLICKED(IDC_CHK_TRANS, &CUDSONE::OnClickedChkTrans)
	ON_BN_CLICKED(IDC_CHK_DOCUMENT, &CUDSONE::OnClickedChkDocument)
	ON_COMMAND(IDC_RADIO_AUTO, &CUDSONE::OnRadioAuto)
	ON_BN_CLICKED(IDC_CHK_HDR, &CUDSONE::OnClickedChkHdr)
	ON_BN_CLICKED(IDC_BTN_HDRCAP, &CUDSONE::OnBnClickedBtnHdrcap)
	ON_BN_CLICKED(IDC_CHK_ATRANTEM, &CUDSONE::OnClickedChkAtrantem)
	ON_BN_CLICKED(IDC_CHK_AREFLCTTEM, &CUDSONE::OnClickedChkAreflcttem)
	ON_BN_CLICKED(IDC_BTN_LDRCAP, &CUDSONE::OnBnClickedBtnLdrcap)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_ADFOCUS, &CUDSONE::OnCustomdrawSlidAdfocus)
END_MESSAGE_MAP()


// CUDSONE ��Ϣ�������


BOOL CUDSONE::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*******************************
	*
	* 1��������ʼ�� 
	* 2�������ļ�·��
	* 3����ȡ�����ļ�
	* 4�������ʼ��
	* 5��RichEdit��ʼ��
	* 6��Radio��ʼ��
	* 7����������
	* 8����ťͼ��
	* 9���������Գ�ʼ��
	* 
	*
	*******************************/
	/*1��������ʼ��*/
	m_pParentWnd = GetParentOwner();
	m_hParentWnd = m_pParentWnd->m_hWnd;
	m_BInitDlg = TRUE;

	m_nLastBright   = 0;
	m_nLastContrast = 0;
	m_nLastLightBox = 0;
	m_nLastGrayScal = 0;

	m_nViewMode     = 0;
	m_lLeftSite     = 0;
	m_lTopSite      = 0;
	m_lRightSite    = 0;
	m_lBottomSite   = 0;

	m_clrCtrlColor  = RGB(72, 77, 91);
	m_clrBackColor  = RGB(72, 77, 91);
	m_clrTextColor  = RGB(255, 255, 255);

	/*2�������ļ�·��*/
	m_strIniPath  = Self_GetMyDocument();
	m_strIniPath += _T("\\");
	m_strIniPath += _T("UDSXRayData");
	m_strIniPath += _T("\\");

	m_strLgeXmlPath  = m_strIniPath;
	m_strLgeXmlPath += _T("language.xml");

	m_strTemDoc   = m_strIniPath;
	m_strTemDoc  += _T("xml");

	m_strIniPath += _T("BaseConfig.ini");


	/*3����ȡ�����ļ�*/
	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcTab1Lge, _T("Tab1"));
	Self_ReadIni(m_strIniPath);

	
	/*4�������ʼ��*/
	//a��ģ��ѡ���ʼ��
	/*0515
	Self_FindTems(m_strTemDoc);
	std::vector<CString>::iterator item_tem;
	int tem_nIndex = 0;
	for (item_tem=m_vcTemName.begin(); item_tem!=m_vcTemName.end(); item_tem++, tem_nIndex++)
	{
		m_conTemplate.InsertString(tem_nIndex, *item_tem);
	}

	CString  tem_strTemPath;
	BOOL     tem_bTem = TRUE;
	for (int i=0; i<m_vcTemName.size(); i++)
	{
		if (m_strLastTem == m_vcTemName[i])
		{
			tem_bTem = FALSE;
			m_conTemplate.SetCurSel(i);
			tem_strTemPath = m_vcTemPath[i];
			m_nLastTemPlate= i;
		}
	}
	if (tem_bTem)
	{
		m_conTemplate.SetCurSel(m_vcTemName.size());
		tem_strTemPath = g_strProXmlPath;
		m_nLastTemPlate= m_vcTemPath.size();
	}
	*/
	if (m_strLastTem==_T("͸���"))
	{
		((CButton*)GetDlgItem(IDC_CHK_ATRANTEM))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_AREFLCTTEM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);

		GetDlgItem(IDC_SLID_LIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_ACOMPUTER)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_HDRCAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LDRCAP)->EnableWindow(TRUE);

		m_vcDisableSTA.push_back(IDC_STA_AUTO);

		Self_SetSlider(g_strProXmlPath);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_ATRANTEM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_AREFLCTTEM))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(TRUE);

		GetDlgItem(IDC_SLID_LIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLID_ACOMPUTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_HDRCAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LDRCAP)->EnableWindow(FALSE);

		m_vcDisableSTA.push_back(IDC_STA_LIGHTBOX);
		m_vcDisableSTA.push_back(IDC_STA_ALIGHTV);
		m_vcDisableSTA.push_back(IDC_STA_ACOMPUTER);
		m_vcDisableSTA.push_back(IDC_STA_ACOMPUTERV);

		Self_SetSlider(g_strDocXmlPath);
	}

	

	//b���ֱ��ʡ�ͼ�����ͳ�ʼ��
	int tem_nResIndex = 0;
	std::vector<CString>::iterator  item_res;
	for (item_res=g_vcRes.begin(); item_res!=g_vcRes.end(); item_res++, tem_nResIndex++)
	{
		m_conResolution.InsertString(tem_nResIndex, *item_res);
	}
	m_conResolution.SetCurSel(m_nLastRes);

	m_conImgType.InsertString(0, _T("bmp"));
	m_conImgType.InsertString(1, _T("jpg"));
	m_conImgType.InsertString(2, _T("png"));
	m_conImgType.InsertString(3, _T("tif"));
	m_conImgType.InsertString(4, _T("pdf"));
	m_conImgType.InsertString(5, _T("dcm"));
	m_conImgType.SetCurSel(m_nLastImgType);

	//d��radio��ʼ��	
	switch(m_nLastPreRotate)
	{
	case 0:
		((CButton*)GetDlgItem(IDC_RADIO_R0))->SetCheck(TRUE);

		break;
	case 1:
		((CButton*)GetDlgItem(IDC_RADIO_R1))->SetCheck(TRUE);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_RADIO_R2))->SetCheck(TRUE);
		break;
	case 3:
		((CButton*)GetDlgItem(IDC_RADIO_R3))->SetCheck(TRUE);
		break;
	default:
		((CButton*)GetDlgItem(IDC_RADIO_R0))->SetCheck(TRUE);
		break;
	}

	//e���ϲ���ʽ��ˮӡ��ʼ��
	switch(m_nLastMergeMode)
	{
	case 0:
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		break;
	case 1:
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(TRUE);
		break;
	default:
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		break;
	}

	if (m_nLastWaterMark==1)
	{
		((CButton*)GetDlgItem(IDC_CHK_WATERMARK))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_WATERMARK))->SetCheck(FALSE);
	}

	/*5��RichEdit��ʼ��*/
	ZeroMemory(&m_fontRichEdit, sizeof(CHARFORMAT));
	m_fontRichEdit.dwMask|=CFM_COLOR;
	m_fontRichEdit.crTextColor = RGB(255, 255, 255);
	m_fontRichEdit.dwMask|=CFM_SIZE;
	m_fontRichEdit.yHeight = 200;
	m_fontRichEdit.dwMask|=CFM_FACE;
	wcscpy(m_fontRichEdit.szFaceName, _T("����"));
	m_conRichEdit.SetSelectionCharFormat(m_fontRichEdit);

	/*6��Radio��ʼ��,����塢͸����߼�����*/
	/*0515
	if (m_BDocMode)
	{
		//������
		((CButton*)GetDlgItem(IDC_CHK_DOCUMENT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_TRANS))->SetCheck(FALSE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(TRUE);
	} 
	else
	{
		//͸����
		((CButton*)GetDlgItem(IDC_CHK_DOCUMENT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_TRANS))->SetCheck(TRUE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(FALSE);
	}
	*/

	if (m_nViewMode == 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(TRUE);
//		((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);
//		((CButton*)GetDlgItem(IDC_RADIO_PARTVIEW))->SetCheck(FALSE);

//		GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(TRUE);
	} 
	else if(m_nViewMode == 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(TRUE);
//		((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);
//		((CButton*)GetDlgItem(IDC_RADIO_PARTVIEW))->SetCheck(FALSE);
		

//		GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);
	}
	else if (m_nViewMode == 2)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
//		((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);
//		((CButton*)GetDlgItem(IDC_RADIO_PARTVIEW))->SetCheck(TRUE);
		

//		GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);
	}
	else if (m_nViewMode == 3)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
//		((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(TRUE);

//		GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);
	}

	/*7����������*/
	//���ø��ı��ؼ�����ɫ
	m_conRichEdit.SetBackgroundColor(FALSE, m_clrCtrlColor);
	//a�����ô��ڱ�����ɫ
	CDialogEx::SetBackgroundColor(m_clrBackColor);
	LoadPicture(m_imgBK, IDB_PNG_BKBLACK, _T("PNG"));
	
	/*8����ťͼ��*/
	m_btnScan.Init(IDB_PNG_SCAN, BTN_IMG_4, BTN_TYPE_NORMAL);
//	m_btnSDoc.Init(IDB_PNG_DOC, BTN_IMG_3, BTN_TYPE_NORMAL);
//	m_btnName.Init(IDB_PNG_NAME, BTN_IMG_3, BTN_TYPE_NORMAL);
//	m_btnWater.Init(IDB_PNG_WATER, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnSetView.Init(IDB_PNG_VIEW, BTN_IMG_4, BTN_TYPE_NORMAL);
//	m_btnRecoverTem.Init(IDB_PNG_RECOVER, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnHDR.Init(IDB_PNG_HDR, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnHDRCap.Init(IDB_PNG_HDRCAP, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnLDRCap.Init(IDB_PNG_LDRCAP, BTN_IMG_4, BTN_TYPE_NORMAL);

	m_tipInfo.Create(this);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_SCAN), m_vcTab1Lge[19]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_SLCDOC), m_vcTab1Lge[22]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_WATER), m_vcTab1Lge[20]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_NAME), m_vcTab1Lge[21]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_REDUCE), m_vcTab1Lge[18]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_DEFAULT), m_vcTab1Lge[17]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_SCANHDR), _T("��Χ�ع�"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_HDRCAP), _T("���ܶ�����"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_LDRCAP), _T("���ܶ�����"));

	m_tipInfo.SetDelayTime(TTDT_INITIAL, 100);
	m_tipInfo.SetDelayTime(TTDT_AUTOPOP, 5000);
	m_tipInfo.SetDelayTime(TTDT_RESHOW, 100);
	m_tipInfo.SetTipTextColor(RGB(255, 255, 255));
	m_tipInfo.SetTipBkColor(RGB(0, 0, 0));
	m_tipInfo.Activate(TRUE);

	//Group
	SetWindowTheme(GetDlgItem(IDC_GRP_AADD1)->GetSafeHwnd(), _T(""), _T(""));  //����GroupBox������������ɫ
	SetWindowTheme(GetDlgItem(IDC_GRP_ATWO)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GRP_A100)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GRP_SCAN)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STA_ASIX)->GetSafeHwnd(), _T(""), _T(""));

	/*9���������Գ�ʼ��*/
	GetDlgItem(IDC_GRP_AADD1)->SetWindowText(m_vcTab1Lge[0]);
	GetDlgItem(IDC_GRP_ATWO)->SetWindowText(m_vcTab1Lge[1]);
	
//	GetDlgItem(IDC_GRP_A100)->SetWindowText(m_vcTab1Lge[2]);
	GetDlgItem(IDC_GRP_SCAN)->SetWindowText(m_vcTab1Lge[3]);
	GetDlgItem(IDC_STA_ASIX)->SetWindowText(m_vcTab1Lge[4]);
//	GetDlgItem(IDC_STA_TEM)->SetWindowText(m_vcTab1Lge[5]);
	GetDlgItem(IDC_STA_BRIGHT)->SetWindowText(m_vcTab1Lge[6]);
	GetDlgItem(IDC_STA_CONTRAST)->SetWindowText(m_vcTab1Lge[7]);
	GetDlgItem(IDC_STA_LIGHTBOX)->SetWindowText(m_vcTab1Lge[8]);
	GetDlgItem(IDC_STA_ROTATE)->SetWindowText(m_vcTab1Lge[9]);
	GetDlgItem(IDC_STA_RESOLUTION)->SetWindowText(m_vcTab1Lge[10]);
	GetDlgItem(IDC_STA_IMAGETYPE)->SetWindowText(m_vcTab1Lge[11]);
	GetDlgItem(IDC_STA_RAFREERECT)->SetWindowText(m_vcTab1Lge[12]);
//	GetDlgItem(IDC_STA_RAMAXRECT)->SetWindowText(m_vcTab1Lge[13]);
	GetDlgItem(IDC_STA_CHKHMERGE)->SetWindowText(m_vcTab1Lge[14]);
	GetDlgItem(IDC_STA_CHKVMERGE)->SetWindowText(m_vcTab1Lge[15]);
	GetDlgItem(IDC_STA_CHKWATERMARK)->SetWindowText(m_vcTab1Lge[16]);
	
	/*10�������ؼ���ʼ��*/
	m_slidAdjFocus.SetRange(0, 255, TRUE);
	m_slidAdjFocus.SetPageSize(1);
	//��ȡ��ǰ����ֵ�������ý���ֵ



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CUDSONE::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_tipInfo.RelayEvent(pMsg);
	}
	//�ж�����Ƿ���SliderCtrl������


	

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CUDSONE::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//��̬�ı�������
	BOOL  tem_BCtrlDisable = FALSE;
	if (pWnd->GetDlgCtrlID()==IDC_STA_BRIGHT || pWnd->GetDlgCtrlID()==IDC_STA_ABRIGHTV || pWnd->GetDlgCtrlID()==IDC_STA_CONTRAST || 
		pWnd->GetDlgCtrlID()==IDC_STA_ACONTRASTV || pWnd->GetDlgCtrlID()==IDC_STA_LIGHT ||
		pWnd->GetDlgCtrlID()==IDC_STA_ROTATE || pWnd->GetDlgCtrlID()==IDC_STA_RESOLUTION || pWnd->GetDlgCtrlID()==IDC_STA_IMAGETYPE ||
		/*pWnd->GetDlgCtrlID()==IDC_STA_TEM || */pWnd->GetDlgCtrlID()==IDC_STA_RAR0 || pWnd->GetDlgCtrlID()==IDC_STA_RAR1 ||
		pWnd->GetDlgCtrlID()==IDC_STA_RAR2 || pWnd->GetDlgCtrlID()==IDC_STA_RAR3 || pWnd->GetDlgCtrlID()==IDC_STA_RAFREERECT||
		/*pWnd->GetDlgCtrlID()==IDC_STA_RAMAXRECT || */pWnd->GetDlgCtrlID()==IDC_STA_RAPARTVIEW || pWnd->GetDlgCtrlID()==IDC_STA_CHKHMERGE ||
		pWnd->GetDlgCtrlID()==IDC_STA_CHKVMERGE || pWnd->GetDlgCtrlID()==IDC_STA_CHKWATERMARK ||
		/*pWnd->GetDlgCtrlID()==IDC_STA_AGRAYLEVEL || *//*pWnd->GetDlgCtrlID()==IDC_STA_AGRAYLEVELV || */pWnd->GetDlgCtrlID()==IDC_STA_AMERGE ||
		pWnd->GetDlgCtrlID()==IDC_STA_AGETRECT/* || pWnd->GetDlgCtrlID()==IDC_STA_AUTOCROP*/ || pWnd->GetDlgCtrlID()==IDC_STA_ASAVE ||
		pWnd->GetDlgCtrlID()==IDC_STA_ADFOCUS || pWnd->GetDlgCtrlID()==IDC_STA_ADFOCUSV || /*pWnd->GetDlgCtrlID()==IDC_STA_TRANS ||*/
		pWnd->GetDlgCtrlID()==IDC_STA_AUTO || pWnd->GetDlgCtrlID()==IDC_STA_HDR ||
		pWnd->GetDlgCtrlID()==IDC_STA_ATRANSTEM || pWnd->GetDlgCtrlID()==IDC_STA_AREFLCTTEM)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_clrTextColor);

	}
	if ( pWnd->GetDlgCtrlID()==IDC_STA_LIGHTBOX || pWnd->GetDlgCtrlID()==IDC_STA_ALIGHTV ||
		pWnd->GetDlgCtrlID()==IDC_STA_ACOMPUTER || pWnd->GetDlgCtrlID()==IDC_STA_ACOMPUTERV ||
		pWnd->GetDlgCtrlID()==IDC_STA_AUTO)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		std::vector<int>::iterator  item;
		for (item=m_vcDisableSTA.begin(); item!=m_vcDisableSTA.end(); item++)
		{
			if (pWnd->GetDlgCtrlID()==*item)
			{
				pDC->SetTextColor(RGB(191, 191, 191));
				tem_BCtrlDisable = TRUE;
				break;
			}
		}
		if (!tem_BCtrlDisable)
		{
			pDC->SetTextColor(m_clrTextColor);
			tem_BCtrlDisable = FALSE;
		}
	}


	if(pWnd->GetDlgCtrlID()==IDC_SLID_BRIGHT || pWnd->GetDlgCtrlID()==IDC_SLID_CONTRAST ||pWnd->GetDlgCtrlID()==IDC_SLID_LIGHT ||
		pWnd->GetDlgCtrlID()==IDC_SLID_GAYLEVEL || /*pWnd->GetDlgCtrlID()==IDC_SLID_AGRAYLEVEL ||*/ pWnd->GetDlgCtrlID()==IDC_SLID_ADFOCUS ||
		pWnd->GetDlgCtrlID()==IDC_SLID_ACOMPUTER)
	{
		return (HBRUSH) CreateSolidBrush(m_clrCtrlColor); 
	}

	if (pWnd->GetDlgCtrlID()==IDC_GRP_AADD1 || pWnd->GetDlgCtrlID()==IDC_GRP_ATWO || /*pWnd->GetDlgCtrlID()==IDC_GRP_A100 ||*/
		pWnd->GetDlgCtrlID()==IDC_GRP_SCAN || pWnd->GetDlgCtrlID()==IDC_STA_ASIX)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CUDSONE::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
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
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


CString CUDSONE::Self_GetMyDocument(void)
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


void CUDSONE::Self_ReadIni(CString inipath)
{
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("û���ҵ�Template��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strLastTem = tem_strRead;
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();


	/*
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

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveDoc"), _T("û���ҵ���ͷSaveDoc��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strSaveDoc = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewMode"), _T("û���ҵ�ViewMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_nViewMode = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewLeft"), _T("û���ҵ�ViewLeft��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead   = _ttoi(tem_strRead);
	m_lLeftSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewTop"), _T("û���ҵ�ViewTop��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead  = _ttoi(tem_strRead);
	m_lTopSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewRight"), _T("û���ҵ�ViewRight��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	m_lRightSite = tem_nRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("ViewBottom"), _T("û���ҵ�ViewBottom��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	m_lBottomSite = tem_nRead;
	tem_strRead.ReleaseBuffer();
}


int CUDSONE::Self_FindTems(CString docpath)
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


void CUDSONE::Self_SetSlider(CString xmlpath)
{
	int              tem_nAuto     = 0;
	int              tem_nSetValue = 0;
	int              tem_nMaxValue = 0;
	int              tem_nMinValue = 0;
	const char*      tem_cInfo;

	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	TiXmlDocument    tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);


	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();
	TiXmlElement*    tem_xmlChildElt= tem_xmlRootElt->FirstChildElement();
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	m_slidABright.SetRange(tem_nMinValue, tem_nMaxValue);
	m_slidABright.SetPos(tem_nSetValue);
	m_slidABright.SetPageSize(1);
	CString tem_strSetValue = _T("");
	tem_strSetValue.Format(_T("%d"), tem_nSetValue);
	GetDlgItem(IDC_STA_ABRIGHTV)->SetWindowText(tem_strSetValue);
// 	if (tem_nAuto==1)
// 	{
// 		m_slidABright.EnableWindow(FALSE);
// 		((CButton*)GetDlgItem(IDC_CHK_BRI))->SetCheck(TRUE);
// 	}
// 	else
	{
		m_slidABright.EnableWindow(TRUE);
	//	((CButton*)GetDlgItem(IDC_CHK_BRI))->SetCheck(FALSE);
	}


	for(int i=0; i<10; i++)
	{
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	}
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	m_slidAContrast.SetRange(tem_nMinValue, tem_nMaxValue);
	m_slidAContrast.SetPos(tem_nSetValue);
	m_slidAContrast.SetPageSize(1);
	tem_strSetValue.Format(_T("%d"), tem_nSetValue);
	GetDlgItem(IDC_STA_ACONTRASTV)->SetWindowText(tem_strSetValue);
// 	if (tem_nAuto==1)
// 	{
// 		m_slidAContrast.EnableWindow(FALSE);
// 		((CButton*)GetDlgItem(IDC_CHK_CONTRAST))->SetCheck(TRUE);
// 	}
// 	else
	{
		m_slidAContrast.EnableWindow(TRUE);
	//	((CButton*)GetDlgItem(IDC_CHK_CONTRAST))->SetCheck(FALSE);
	}

	for(int i=0; i<5; i++)
	{
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	}
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	m_slidALightBox.SetRange(tem_nMinValue, tem_nMaxValue);
	m_slidALightBox.SetPos(tem_nSetValue);
	m_slidALightBox.SetPageSize(1);
	tem_strSetValue.Format(_T("%d"), tem_nSetValue);
	GetDlgItem(IDC_STA_ALIGHTV)->SetWindowText(tem_strSetValue);

	//�ҽ�-----------------------------------------------------
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	/*0515
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	m_slidGray.SetRange(tem_nMinValue, tem_nMaxValue);
	m_slidGray.SetPos(tem_nSetValue);
	m_slidGray.SetPageSize(1);
	tem_strSetValue.Format(_T("%d"), tem_nSetValue);
	GetDlgItem(IDC_STA_AGRAYLEVELV)->SetWindowText(tem_strSetValue);
	*/

	//---------------------------------------------------------
	//HDR����
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//�ϲ���ʽ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//����ƫ��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//��ʱ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//�ҽ�
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();

	//����忪��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo       = tem_xmlChildElt->Value();
	tem_xmlChildAtb = tem_xmlChildElt->FirstAttribute();
	if (tem_xmlChildAtb->IntValue() == 0)
	{
		//�����رգ�͸���ش�
// 		m_btnHDR.SetFourState();
// 		m_btnHDR.EnableWindow(TRUE);
		m_BDocMode = FALSE;
// 		if (m_nViewMode == 3)
// 		{
// 			m_nViewMode = 2;
// 		}
		m_nViewMode = 1;
	}
	else
	{
		//������
//		m_btnHDR.EnableWindow(FALSE);
		m_BDocMode = TRUE;
		m_nViewMode = 3;
	}


	//ͼ��ֱ���
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	m_nLastRes     = tem_nSetValue;

	//ͼ���ʽ
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	m_nLastImgType  = tem_nSetValue;
	

	// 	if (tem_nAuto==1)
	// 	{
	// 		m_slidAContrast.EnableWindow(FALSE);
	// 		((CButton*)GetDlgItem(IDC_CHK_CONTRAST))->SetCheck(TRUE);
	// 	}
	// 	else
//	{
//		m_slidAContrast.EnableWindow(TRUE);
	//	((CButton*)GetDlgItem(IDC_CHK_CONTRAST))->SetCheck(FALSE);
//	}


}

//ѡ��ģ��
void CUDSONE::OnSelchangeCmbTem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int       tem_nCurSel   = 0;
	CString   tem_strCurSel = _T("");
	CString   tem_strTemPath= _T("");
	tem_nCurSel = m_conTemplate.GetCurSel();
	m_conTemplate.GetLBText(tem_nCurSel, tem_strCurSel);

//	if (tem_nCurSel != m_nLastTemPlate)
	{
		tem_strTemPath = m_vcTemPath[tem_nCurSel];
	}
//	else
// 	{
// 		return;
// 	}
	m_nLastTemPlate = tem_nCurSel;
	::SendMessage(m_hParentWnd, WM_SCANSET, 0, tem_nCurSel);
	Self_SetSlider(tem_strTemPath);
	

	::WritePrivateProfileString(_T("BaseSet"), _T("Template"), tem_strCurSel, m_strIniPath); 
}

//ѡ��ֱ���
void CUDSONE::OnSelchangeCmbRes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int     tem_nCurSel   = m_conResolution.GetCurSel();
	if (tem_nCurSel==m_nLastRes)
	{
		return;
	}
	
	CString tem_strCurSel = _T("");
	::SendMessage(m_hParentWnd, WM_SCANSET, 1, tem_nCurSel);

	tem_strCurSel.Format(_T("%d"), tem_nCurSel);
	::WritePrivateProfileString(_T("BaseSet"), _T("ResIndex"), tem_strCurSel, m_strIniPath); 

	m_nLastRes = tem_nCurSel;
}

//ѡ��ͼ������
void CUDSONE::OnSelchangeCmbType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int     tem_nCurSel   = m_conImgType.GetCurSel();
	if (tem_nCurSel==m_nLastImgType)
	{
		return;
	}
	CString tem_strCurSel = _T("");
	::SendMessage(m_hParentWnd, WM_SCANSET, 2, tem_nCurSel);

	tem_strCurSel.Format(_T("%d"), tem_nCurSel);
	::WritePrivateProfileString(_T("BaseSet"), _T("ImgType"), tem_strCurSel, m_strIniPath); 
	m_nLastImgType = tem_nCurSel;
}

//��ת
void CUDSONE::OnRadioR0()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_R0))
	{
		int     tem_nCurSel   = 0;
		CString tem_strCurSel = _T("");
		::SendMessage(m_hParentWnd, WM_SCANSET, 3, tem_nCurSel);

		tem_strCurSel.Format(_T("%d"), tem_nCurSel);
		::WritePrivateProfileString(_T("BaseSet"), _T("PreRotate"), tem_strCurSel, m_strIniPath); 
	} 

}


void CUDSONE::OnRadioR1()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_R1))
	{
		int     tem_nCurSel   = 1;
		CString tem_strCurSel = _T("");
		::SendMessage(m_hParentWnd, WM_SCANSET, 3, tem_nCurSel);

		tem_strCurSel.Format(_T("%d"), tem_nCurSel);
		::WritePrivateProfileString(_T("BaseSet"), _T("PreRotate"), tem_strCurSel, m_strIniPath); 
	} 
}


void CUDSONE::OnRadioR2()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_R2))
	{
		int     tem_nCurSel   = 2;
		CString tem_strCurSel = _T("");
		::SendMessage(m_hParentWnd, WM_SCANSET, 3, tem_nCurSel);

		tem_strCurSel.Format(_T("%d"), tem_nCurSel);
		::WritePrivateProfileString(_T("BaseSet"), _T("PreRotate"), tem_strCurSel, m_strIniPath); 
	} 
}


void CUDSONE::OnRadioR3()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_R3))
	{
		int     tem_nCurSel   = 3;
		CString tem_strCurSel = _T("");
		::SendMessage(m_hParentWnd, WM_SCANSET, 3, tem_nCurSel);

		tem_strCurSel.Format(_T("%d"), tem_nCurSel);
		::WritePrivateProfileString(_T("BaseSet"), _T("PreRotate"), tem_strCurSel, m_strIniPath); 
	} 
}

//�ϲ���ʽ
void CUDSONE::OnClickedChkHmerge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int     tem_nCurSel   = 0;
	CString tem_strCurSel = _T("");
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HMERGE))
	{
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		tem_nCurSel = 1;
	}
	else
	{
		if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_VMERGE))
		{
			tem_nCurSel = 2;
		}
		else
		{
			tem_nCurSel = 0;
		}
	}
	::SendMessage(m_hParentWnd, WM_SCANSET, 4, tem_nCurSel);

	tem_strCurSel.Format(_T("%d"), tem_nCurSel);
	::WritePrivateProfileString(_T("BaseSet"), _T("MergeMode"), tem_strCurSel, m_strIniPath); 
}


void CUDSONE::OnClickedChkVmerge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int     tem_nCurSel   = 0;
	CString tem_strCurSel = _T("");
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_VMERGE))
	{
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);
		tem_nCurSel = 2;
	}
	else
	{
		if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HMERGE))
		{
			tem_nCurSel = 1;
		}
		else
		{
			tem_nCurSel = 0;
		}
	}
	::SendMessage(m_hParentWnd, WM_SCANSET, 4, tem_nCurSel);

	tem_strCurSel.Format(_T("%d"), tem_nCurSel);
	::WritePrivateProfileString(_T("BaseSet"), _T("MergeMode"), tem_strCurSel, m_strIniPath); 
}

//ˮӡ
void CUDSONE::OnClickedChkWatermark()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ˮӡ����
	int     tem_nCurSel   = 0;
	CString tem_strCurSel = _T("");
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_WATERMARK))
	{
		tem_nCurSel = 1;
	} 
	else
	{
		tem_nCurSel = 0;
	}
	::SendMessage(m_hParentWnd, WM_SCANSET, 13, tem_nCurSel);
	tem_strCurSel.Format(_T("%d"), tem_nCurSel);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterMark"), tem_strCurSel, m_strIniPath); 
}

//����
void CUDSONE::OnClickedChkBri()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_BRI))
	{
		((CButton*)GetDlgItem(IDC_CHK_BRI))->SetCheck(TRUE);
		GetDlgItem(IDC_SLID_BRIGHT)->EnableWindow(FALSE);
		::SendMessage(m_hParentWnd, WM_SCANSET, 5, 5121314);

	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_BRI))->SetCheck(FALSE);
		GetDlgItem(IDC_SLID_BRIGHT)->EnableWindow(TRUE);
		int  tem_nCurValue = m_slidABright.GetPos();
		::SendMessage(m_hParentWnd, WM_SCANSET, 5, tem_nCurValue);
	}
	*/
}


void CUDSONE::OnCustomdrawSlidBright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int  tem_nCurSel = m_slidABright.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), tem_nCurSel);
	GetDlgItem(IDC_STA_ABRIGHTV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_ABRIGHTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); //ת���ͻ��˽���
	InvalidateRect(&tem_rcRect);//���ˢ�¶Ի��򱳾� 

	::SendMessage(m_hParentWnd, WM_SCANSET, 6, tem_nCurSel);

	m_nLastBright = tem_nCurSel;

	*pResult = 0;
}


//�Աȶ�
void CUDSONE::OnClickedChkContrast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_CONTRAST))
	{
		((CButton*)GetDlgItem(IDC_CHK_CONTRAST))->SetCheck(TRUE);
		GetDlgItem(IDC_SLID_CONTRAST)->EnableWindow(FALSE);
		::SendMessage(m_hParentWnd, WM_SCANSET, 7, 5121314);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_CONTRAST))->SetCheck(FALSE);
		GetDlgItem(IDC_SLID_CONTRAST)->EnableWindow(TRUE);
		int  tem_nCurValue = m_slidAContrast.GetPos();
		::SendMessage(m_hParentWnd, WM_SCANSET, 7, tem_nCurValue);
	}
	*/
}


void CUDSONE::OnCustomdrawSlidContrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int  tem_nCurSel = m_slidAContrast.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), tem_nCurSel);
	GetDlgItem(IDC_STA_ACONTRASTV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_ACONTRASTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); //ת���ͻ��˽���
	InvalidateRect(&tem_rcRect);//���ˢ�¶Ի��򱳾� 

	::SendMessage(m_hParentWnd, WM_SCANSET, 8, tem_nCurSel);

	m_nLastContrast = tem_nCurSel;

	*pResult = 0;
}


void CUDSONE::OnCustomdrawSlidLight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int     tem_nCurSel = m_slidALightBox.GetPos();
	CString tem_strValue = _T("");
	if (tem_nCurSel==0)
	{
		tem_strValue.Format(_T("%d"), tem_nCurSel);
		GetDlgItem(IDC_STA_ALIGHTV)->SetWindowText(tem_strValue);
		::SendMessage(m_hParentWnd, WM_SCANSET, 19, tem_nCurSel);
	}
	else if (tem_nCurSel==100)
	{
		tem_strValue.Format(_T("%d"), tem_nCurSel);
		GetDlgItem(IDC_STA_ALIGHTV)->SetWindowText(tem_strValue);
		::SendMessage(m_hParentWnd, WM_SCANSET, 20, tem_nCurSel);
	}
	else
	{
		tem_strValue.Format(_T("%d"), tem_nCurSel);
		GetDlgItem(IDC_STA_ALIGHTV)->SetWindowText(tem_strValue);
		::SendMessage(m_hParentWnd, WM_SCANSET, 18, tem_nCurSel);
	}

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_ALIGHTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); //ת���ͻ��˽���
	InvalidateRect(&tem_rcRect);//���ˢ�¶Ի��򱳾� 
	
	m_nLastLightBox = tem_nCurSel;

	*pResult = 0;
}


void CUDSONE::OnBnClickedBtnSlcdoc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ѡ�񱣴�·��
	::SendMessage(m_hParentWnd, WM_SCANSET, 9, 0);
}


void CUDSONE::OnBnClickedBtnWater()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ˮӡ����
	::SendMessage(m_hParentWnd, WM_SCANSET, 10, 0);
}


void CUDSONE::OnBnClickedBtnScan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����ɨ��
	::SendMessage(m_hParentWnd, WM_SCANSET, 11, 0);
}


void CUDSONE::OnBnClickedBtnName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��������
	::SendMessage(m_hParentWnd, WM_SCANSET, 12, 0);
}


void CUDSONE::OnBnClickedBtnDefault()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//1��ԭ��Ϣ�����ڵ�����������windows�Ի���
//	::SendMessage(m_hParentWnd, WM_SCANSET, 14, 0);
	
	//2������Ϣ���������¼��ص�ǰģ��
	int       tem_nCurSel   = 0;

	CString   tem_strCurSel = _T("");
	CString   tem_strTemPath= _T("");

	tem_nCurSel = m_conTemplate.GetCurSel();
	m_conTemplate.GetLBText(tem_nCurSel, tem_strCurSel);

	tem_strTemPath = m_vcTemPath[tem_nCurSel];
	
	::SendMessage(m_hParentWnd, WM_SCANSET, 27, tem_nCurSel);
	Self_SetSlider(tem_strTemPath);
	
}


void CUDSONE::OnBnClickedBtnEnhence()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hParentWnd, WM_SCANSET, 15, 0);
}


void CUDSONE::OnBnClickedBtnReduce()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
//	((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_PARTVIEW))->SetCheck(FALSE);

	GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);

	m_nViewMode = 1;
	CString  tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nViewMode);
	::WritePrivateProfileString(_T("BaseSet"), _T("ViewMode"), tem_strValue, m_strIniPath);

	::SendMessage(m_hParentWnd, WM_SCANSET, 16, 0);
}


void CUDSONE::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hParentWnd, WM_SCANSET, 17, 0);
}


void CUDSONE::Self_UpdateSlider(int index)
{
	switch(index)
	{
	case 0:
		//����-----------
		if (m_nLastBright != m_slidABright.GetPos())
		{
			m_slidABright.SetPos(m_nLastBright);
		}
		break;
	case 1:
		//�Աȶ�---------
		if (m_nLastContrast != m_slidAContrast.GetPos())
		{
			m_slidAContrast.SetPos(m_nLastContrast);
		}
		break;
	case 2:
		//����-----------
		if (m_nLastLightBox != m_slidALightBox.GetPos())
		{
			m_slidALightBox.SetPos(m_nLastLightBox);
		}
		break;
	case 3:
		if (m_nLastGrayScal != m_slidGray.GetPos())
		{
			m_slidGray.SetPos(m_nLastGrayScal);
		}
		break;
	case 4:
		//�ֱ����б�����-----------
		if (m_nLastRes != m_conResolution.GetCurSel())
		{
			m_conResolution.SetCurSel(m_nLastRes);
		}
		break;
	case 5:
		//ͼ����������-------------
		if (m_nLastImgType != m_conImgType.GetCurSel())
		{
			m_conImgType.SetCurSel(m_nLastImgType);
		}
		break;
	case 6:
		//������ѡ�з���年ѡ��
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_DOCUMENT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_TRANS))->SetCheck(FALSE);
		m_btnHDR.EnableWindow(FALSE);
		
		break;
	case 7:
		//������ȡ������年ѡ��
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_DOCUMENT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_TRANS))->SetCheck(TRUE);
		if (m_nViewMode == 3)
		{
			((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
//			((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);
		}
		m_btnHDR.SetFourState();
		m_btnHDR.EnableWindow(TRUE);
		break;
	case 8:
		m_btnHDR.EnableWindow(FALSE);
		break;
	}
}


void CUDSONE::Self_SlcNewTem(void)
{
	m_conTemplate.ResetContent();
	Self_FindTems(m_strTemDoc);
	std::vector<CString>::iterator item_tem;
	int tem_nIndex = 0;
	for (item_tem=m_vcTemName.begin(); item_tem!=m_vcTemName.end(); item_tem++, tem_nIndex++)
	{
		m_conTemplate.InsertString(tem_nIndex, *item_tem);
	}
//	m_conTemplate.InsertString(-1, _T("Ĭ��"));
//	m_conTemplate.InsertString(-1, _T("Default"));
	m_conTemplate.InsertString(-1, _T("͸���Ĭ��"));
	m_conTemplate.InsertString(-1, _T("�����Ĭ��"));
	//��ȡ�����ĵ����趨��ǰѡ��
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("û���ҵ�Template��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strLastTem = tem_strRead;
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	CString  tem_strTemPath;
	for (int i=0; i<m_vcTemName.size(); i++)
	{
		if (m_strLastTem == m_vcTemName[i])
		{
			m_conTemplate.SetCurSel(i);
			tem_strTemPath = m_vcTemPath[i];
			m_nLastTemPlate= i;
			break;
		}
	}

}


//͸���ģʽ------------------------------------------------------------------------------------------------------
void CUDSONE::OnClickedChkTrans()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_TRANS))
	{
		((CButton*)GetDlgItem(IDC_CHK_DOCUMENT))->SetCheck(FALSE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(FALSE);
		//����͸���ģ��
		for (int i=0; i<m_conTemplate.GetCount(); i++)
		{
			CString tem_strCurSel;
			m_conTemplate.GetLBText(i, tem_strCurSel);
			if (tem_strCurSel.Find(_T("͸���Ĭ��"))>=0)
			{
				m_conTemplate.SetCurSel(i);
				break;
			}
		}
		::SendMessage(m_hParentWnd, WM_SCANSET, 28, 0);
		::WritePrivateProfileString(_T("BaseSet"), _T("Template"), _T("͸���Ĭ��"), m_strIniPath); 
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_DOCUMENT))->SetCheck(TRUE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(TRUE);
		//���ط����ģ��
		for (int i=0; i<m_conTemplate.GetCount(); i++)
		{
			CString tem_strCurSel;
			m_conTemplate.GetLBText(i, tem_strCurSel);
			if (tem_strCurSel.Find(_T("�����Ĭ��"))>=0)
			{
				m_conTemplate.SetCurSel(i);
				break;
			}
		}
		::SendMessage(m_hParentWnd, WM_SCANSET, 28, 1);
		::WritePrivateProfileString(_T("BaseSet"), _T("Template"), _T("�����Ĭ��"), m_strIniPath); 
	}
}

//�����ģʽ------------------------------------------------------------------------------------------------------
void CUDSONE::OnClickedChkDocument()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_DOCUMENT))
	{
		((CButton*)GetDlgItem(IDC_CHK_TRANS))->SetCheck(FALSE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(TRUE);
		//���ط����ģ��
		for (int i=0; i<m_conTemplate.GetCount(); i++)
		{
			CString tem_strCurSel;
			m_conTemplate.GetLBText(i, tem_strCurSel);
			if (tem_strCurSel.Find(_T("�����Ĭ��"))>=0)
			{
				m_conTemplate.SetCurSel(i);
				break;
			}
		}
		::SendMessage(m_hParentWnd, WM_SCANSET, 28, 1);
		::WritePrivateProfileString(_T("BaseSet"), _T("Template"), _T("�����Ĭ��"), m_strIniPath); 		
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_TRANS))->SetCheck(TRUE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(FALSE);
		//����͸���ģ��
		for (int i=0; i<m_conTemplate.GetCount(); i++)
		{
			CString tem_strCurSel;
			m_conTemplate.GetLBText(i, tem_strCurSel);
			if (tem_strCurSel.Find(_T("͸���Ĭ��"))>=0)
			{
				m_conTemplate.SetCurSel(i);
				break;
			}
		}
		::SendMessage(m_hParentWnd, WM_SCANSET, 28, 0);
		::WritePrivateProfileString(_T("BaseSet"), _T("Template"), _T("͸���Ĭ��"), m_strIniPath); 
	}
}

//��ѡ����
void CUDSONE::OnRadioFreerect()
{
	// TODO: �ڴ���������������
	((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(TRUE);
//	((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);
	

//	m_btnSetView.SetFourState();
//    GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(TRUE);
	
	


	//����ͼ��״̬��ʾ
//	m_btnSetView.Init(IDB_PNG_VIEW, BTN_IMG_4, BTN_TYPE_NORMAL);
// 	CRect  tem_rcButton;
// 	GetDlgItem(IDC_BTN_REDUCE)->GetClientRect(&tem_rcButton);
// 	InvalidateRect(tem_rcButton, TRUE);


	m_nViewMode = 1;
	CString  tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nViewMode);
	::WritePrivateProfileString(_T("BaseSet"), _T("ViewMode"), tem_strValue, m_strIniPath);

	::SendMessage(m_hParentWnd, WM_SCANSET, 22, 0);
}

//�̶�����
void CUDSONE::OnRadioMaxrect()
{
	// TODO: �ڴ���������������
	((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);

	GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);

	m_nViewMode = 1;
	CString  tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nViewMode);
	::WritePrivateProfileString(_T("BaseSet"), _T("ViewMode"), tem_strValue, m_strIniPath);

	::SendMessage(m_hParentWnd, WM_SCANSET, 22, 0);
}

//�Զ�����
void CUDSONE::OnRadioAuto()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
//	((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(TRUE);

//	GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);

	m_nViewMode = 3;
	CString  tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nViewMode);
	::WritePrivateProfileString(_T("BaseSet"), _T("ViewMode"), tem_strValue, m_strIniPath);

	::SendMessage(m_hParentWnd, WM_SCANSET, 26, 0);
}

//�ֲ�Ԥ��-����
void CUDSONE::OnRadioPartview()
{
	// TODO: �ڴ���������������
	/*
	((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_PARTVIEW))->SetCheck(TRUE);

	GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);

	m_nViewMode = 2;
	CString  tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nViewMode);
	::WritePrivateProfileString(_T("BaseSet"), _T("ViewMode"), tem_strValue, m_strIniPath);

	::SendMessage(m_hParentWnd, WM_SCANSET, 23, 0);
	*/
}

//�����ģʽ-����
void CUDSONE::OnBnClickedRadioDocument()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_DOCUMENT))->SetCheck(TRUE);

	::SendMessage(m_hParentWnd, WM_SCANSET, 26, 0);
	*/
}


void CUDSONE::OnBnClickedBtnScan2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hParentWnd, WM_SCANSET, 11, 0);
}


void CUDSONE::Self_SetCtrlState(void)
{
	((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
//	((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_PARTVIEW))->SetCheck(TRUE);

	GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);
}


void CUDSONE::Self_RefrushTem(CString slgtem)
{
	//���ģ���б�
	m_conTemplate.ResetContent();
	//���»�ȡ�������б�
	Self_FindTems(m_strTemDoc);
	std::vector<CString>::iterator item_tem;
	int tem_nIndex    = 0;
	int tem_nSetIndex = 0;
	for (item_tem=m_vcTemName.begin(); item_tem!=m_vcTemName.end(); item_tem++, tem_nIndex++)
	{
		m_conTemplate.InsertString(tem_nIndex, *item_tem);
		if (*item_tem == slgtem)
		{
			tem_nSetIndex = tem_nIndex;
		}
	}
	m_conTemplate.SetCurSel(tem_nSetIndex);
}


void CUDSONE::Self_ReadLanguageXml(CString xmlpath, vector <CString>& vec, CString nodename)
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


void CUDSONE::OnCustomdrawSlidAgraylevel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*1����static����*/
	int  tem_nCurSel = m_slidGray.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), tem_nCurSel);
	GetDlgItem(IDC_STA_AGRAYLEVELV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_AGRAYLEVELV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect);                              //ת���ͻ��˽���
	InvalidateRect(&tem_rcRect);                              //���ˢ�¶Ի��򱳾� 



	/*2������ʵ��*/
 	::SendMessage(m_hParentWnd, WM_SCANSET, 24, tem_nCurSel);
 	m_nLastGrayScal = tem_nCurSel;

	*pResult = 0;
}


void CUDSONE::OnBnClickedBtnScanhdr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hParentWnd, WM_SCANSET, 25, 0);
}


void CUDSONE::Self_ResetUI(CString xmlpath)
{
	int              tem_nOpen     = 0;
	int              tem_nAuto     = 0;
	int              tem_nSetValue = 0;
	int              tem_nMaxValue = 0;
	int              tem_nMinValue = 0;
	const char*      tem_cInfo;

	CStringA    tem_straXmlPath(xmlpath);
	const char* tem_cXmlPath = tem_straXmlPath.GetString();

	TiXmlDocument    tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);


	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();
	TiXmlElement*    tem_xmlChildElt= tem_xmlRootElt->FirstChildElement();
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();


	for(int i=0; i<22; i++)
	{
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	}
	tem_cInfo = tem_xmlChildElt->Value();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nOpen      = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nAuto      = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMaxValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nMinValue  = tem_xmlChildAtb->IntValue();

	//�ж�ģ����DOC�Ƿ���
	if (tem_nOpen)
	{
		//������
		m_BDocMode = TRUE;
		m_nViewMode = 3;
	}
	else
	{
		//�����رգ�͸���ش򿪣�Ԥ��ģʽ����Ϊ3
		m_BDocMode = FALSE;
		m_nViewMode = 1;
// 		if (m_nViewMode == 3)
// 		{
// 			m_nViewMode = 2;
// 		}
	}
// 	if (m_BDocMode)
// 	{
// 		//������
// 		((CButton*)GetDlgItem(IDC_CHK_DOCUMENT))->SetCheck(TRUE);
// 		((CButton*)GetDlgItem(IDC_CHK_TRANS))->SetCheck(FALSE);
// 		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(TRUE);
// 	} 
// 	else
// 	{
// 		//͸����
// 		((CButton*)GetDlgItem(IDC_CHK_DOCUMENT))->SetCheck(FALSE);
// 		((CButton*)GetDlgItem(IDC_CHK_TRANS))->SetCheck(TRUE);
// 		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(FALSE);
// 	}

	if (m_nViewMode == 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(TRUE);
//		((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);

		GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(TRUE);
	} 
	else if(m_nViewMode == 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(TRUE);
		//((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);

		GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);
	}
	else if (m_nViewMode == 2)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
//		((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(FALSE);

		GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);
	}
	else if (m_nViewMode == 3)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREERECT))->SetCheck(FALSE);
//		((CButton*)GetDlgItem(IDC_RADIO_MAXRECT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_AUTO))->SetCheck(TRUE);

		GetDlgItem(IDC_BTN_REDUCE)->EnableWindow(FALSE);
	}


	//�ֱ���UI��ʼ��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	m_conResolution.SetCurSel(tem_nSetValue);

	//ͼ���ʽUI��ʼ��
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_nSetValue  = tem_xmlChildAtb->IntValue();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	tem_xmlChildAtb= tem_xmlChildAtb->Next();
	m_conImgType.SetCurSel(tem_nSetValue);

}



void CUDSONE::OnClickedChkHdr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HDR))
	{
		::SendMessage(m_hParentWnd, WM_SCANSET, 29, 1);
	}
	else
	{
		::SendMessage(m_hParentWnd, WM_SCANSET, 29, 0);
	}
}


//���ܶ�����-------------------------------------------
void CUDSONE::OnBnClickedBtnHdrcap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hParentWnd, WM_SCANSET, 30, 0);
}


//���ܶ�����-------------------------------------------
void CUDSONE::OnBnClickedBtnLdrcap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hParentWnd, WM_SCANSET, 32, 0);
}


void CUDSONE::OnClickedChkAtrantem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_ATRANTEM))
	{
		((CButton*)GetDlgItem(IDC_CHK_AREFLCTTEM))->SetCheck(FALSE);
		::WritePrivateProfileString(_T("BaseSet"), _T("Template"), _T("͸���"), m_strIniPath);
		::SendMessage(m_hParentWnd, WM_SCANSET, 31, 0);

		m_vcDisableSTA.clear();
		GetDlgItem(IDC_SLID_LIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_ACOMPUTER)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(FALSE);
		m_btnHDRCap.SetFourState();
		m_btnLDRCap.SetFourState();
		GetDlgItem(IDC_BTN_HDRCAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LDRCAP)->EnableWindow(TRUE);

		m_vcDisableSTA.push_back(IDC_STA_AUTO);

	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_AREFLCTTEM))->SetCheck(TRUE);
		::WritePrivateProfileString(_T("BaseSet"), _T("Template"), _T("�����"), m_strIniPath);
		::SendMessage(m_hParentWnd, WM_SCANSET, 31, 1);

		m_vcDisableSTA.clear();
		GetDlgItem(IDC_SLID_LIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLID_ACOMPUTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_HDRCAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LDRCAP)->EnableWindow(FALSE);

		m_vcDisableSTA.push_back(IDC_STA_LIGHTBOX);
		m_vcDisableSTA.push_back(IDC_STA_ALIGHTV);
		m_vcDisableSTA.push_back(IDC_STA_ACOMPUTER);
		m_vcDisableSTA.push_back(IDC_STA_ACOMPUTERV);
	}

	CRect  tem_rcRect;
	GetDlgItem(IDC_STA_LIGHTBOX)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_ALIGHTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_ACOMPUTER)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_ACOMPUTERV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_AUTO)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);
}


void CUDSONE::OnClickedChkAreflcttem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_AREFLCTTEM))
	{
		((CButton*)GetDlgItem(IDC_CHK_ATRANTEM))->SetCheck(FALSE);
		::WritePrivateProfileString(_T("BaseSet"), _T("Template"), _T("�����"), m_strIniPath);
		::SendMessage(m_hParentWnd, WM_SCANSET, 31, 1);

		m_vcDisableSTA.clear();
		GetDlgItem(IDC_SLID_LIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLID_ACOMPUTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_HDRCAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LDRCAP)->EnableWindow(FALSE);

		m_vcDisableSTA.push_back(IDC_STA_LIGHTBOX);
		m_vcDisableSTA.push_back(IDC_STA_ALIGHTV);
		m_vcDisableSTA.push_back(IDC_STA_ACOMPUTER);
		m_vcDisableSTA.push_back(IDC_STA_ACOMPUTERV);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_ATRANTEM))->SetCheck(TRUE);
		::WritePrivateProfileString(_T("BaseSet"), _T("Template"), _T("͸���"), m_strIniPath);
		::SendMessage(m_hParentWnd, WM_SCANSET, 31, 0);

		m_vcDisableSTA.clear();
		GetDlgItem(IDC_SLID_LIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLID_ACOMPUTER)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_AUTO)->EnableWindow(FALSE);
		m_btnHDRCap.SetFourState();
		m_btnLDRCap.SetFourState();
		GetDlgItem(IDC_BTN_HDRCAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LDRCAP)->EnableWindow(TRUE);

		m_vcDisableSTA.push_back(IDC_STA_AUTO);
	}

	CRect  tem_rcRect;
	GetDlgItem(IDC_STA_LIGHTBOX)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_ALIGHTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_ACOMPUTER)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_ACOMPUTERV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_AUTO)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);
}

void CUDSONE::OnCustomdrawSlidAdfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*1����static����*/
	int  tem_nCurSel = m_slidAdjFocus.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), tem_nCurSel);
	GetDlgItem(IDC_STA_ADFOCUSV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_ADFOCUSV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect);                              //ת���ͻ��˽���
	InvalidateRect(&tem_rcRect);                              //���ˢ�¶Ի��򱳾� 


	*pResult = 0;
}
