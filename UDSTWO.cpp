// UDSTWO.cpp : 实现文件
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSTWO.h"
#include "afxdialogex.h"


extern CString  g_strProXmlPath;
extern CString  g_strDocXmlPath; 
extern std::vector<CString> g_vcRes;
// CUDSTWO 对话框

IMPLEMENT_DYNAMIC(CUDSTWO, CDialogEx)

CUDSTWO::CUDSTWO(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSTWO::IDD, pParent)
{

	m_editTemnameV = _T("");
}

CUDSTWO::~CUDSTWO()
{
}

void CUDSTWO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_IRIS, m_slidIris);
	DDX_Control(pDX, IDC_SLIDER_BBRIGHT, m_slidBBright);
	DDX_Control(pDX, IDC_SLIDER_EXPOS, m_slidExpos);
	DDX_Control(pDX, IDC_SLIDER_FOCUS, m_slidFocus);
	DDX_Control(pDX, IDC_SLIDER_GAMA, m_slidGama);
	DDX_Control(pDX, IDC_SLIDER_GAIN, m_slidGain);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_slidHue);
	DDX_Control(pDX, IDC_SLIDER_FULLVIEW, m_slidPan);
	DDX_Control(pDX, IDC_SLIDER_ROLL, m_slidRoll);
	DDX_Control(pDX, IDC_SLIDER_SLOP, m_slidSlop);
	DDX_Control(pDX, IDC_SLIDER_ZOOM, m_slidZoom);
	DDX_Control(pDX, IDC_SLIDER_BCONTRAST, m_slidBContrast);
	DDX_Control(pDX, IDC_SLIDER_CLEAR, m_slidClear);
	DDX_Control(pDX, IDC_SLIDER_SATURE, m_slidSatura);
	DDX_Control(pDX, IDC_SLIDER_WHITEB, m_slidWhitBlance);
	//  DDX_Control(pDX, IDC_STA_BACKLIGHT, m_slidBackLight);
	DDX_Control(pDX, IDC_SLIDER_BACKLIGHT, m_slidBackLight);
	DDX_Text(pDX, IDC_EDIT_TEMNAME, m_editTemnameV);
	DDX_Control(pDX, IDC_SLIDER_LIGHTBOX, m_slidBLightBox);
	DDX_Control(pDX, IDC_BTN_OUTPUT, m_btnOutput);
	DDX_Control(pDX, IDC_BTN_MANAGE, m_btnManage);
	DDX_Control(pDX, IDC_BTN_FOLD, m_btnFold);
	DDX_Control(pDX, IDC_BTN_BRECOVER, m_btnBRecover);
	DDX_Control(pDX, IDC_SLIDER_CGRAY, m_slidGray);
	DDX_Control(pDX, IDC_SLIDER_LIGHTBOX2, m_slidBLightBox2);
	DDX_Control(pDX, IDC_SLIDER_BDELAY, m_slidDelay);
	DDX_Control(pDX, IDC_CMB_BRES, m_conBReslution);
	DDX_Control(pDX, IDC_CMB_BFORMAT, m_conBFormat);
	DDX_Control(pDX, IDC_SLIDER_BHDRGRAY, m_slidBHDRGray);
	DDX_Control(pDX, IDC_SLD_HDRLLGT, m_slidHdrLLgt);
	DDX_Control(pDX, IDC_SLD_HDRHLGT, m_slidHdrHLgt);
	DDX_Control(pDX, IDC_SLID_HDRLGRY, m_slidHdrLGry);
	DDX_Control(pDX, IDC_SLID_HDRHGRY, m_slidHdrHGry);
	DDX_Control(pDX, IDC_SLID_HDRLDLY, m_slidHdrLDly);
	DDX_Control(pDX, IDC_SLID_HDRHDLY, m_slidHdrHDly);
}


BEGIN_MESSAGE_MAP(CUDSTWO, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OUTPUT, &CUDSTWO::OnBnClickedBtnOutput)
	ON_BN_CLICKED(IDC_CHK_IRIS, &CUDSTWO::OnClickedChkIris)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_IRIS, &CUDSTWO::OnCustomdrawSliderIris)
	ON_BN_CLICKED(IDC_CHK_BBRIGHT, &CUDSTWO::OnClickedChkBbright)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BBRIGHT, &CUDSTWO::OnCustomdrawSliderBbright)
	ON_BN_CLICKED(IDC_CHK_BACKLIGHT, &CUDSTWO::OnClickedChkBacklight)
	ON_BN_CLICKED(IDC_CHK_BCONTRAST, &CUDSTWO::OnClickedChkBcontrast)
	ON_BN_CLICKED(IDC_CHK_CLEAR, &CUDSTWO::OnClickedChkClear)
	ON_BN_CLICKED(IDC_CHK_EXPOS, &CUDSTWO::OnClickedChkExpos)
	ON_BN_CLICKED(IDC_CHK_FOCUS, &CUDSTWO::OnClickedChkFocus)
	ON_BN_CLICKED(IDC_CHK_FULLVIEW, &CUDSTWO::OnClickedChkFullview)
	ON_BN_CLICKED(IDC_CHK_GAIN, &CUDSTWO::OnClickedChkGain)
	ON_BN_CLICKED(IDC_CHK_GAMA, &CUDSTWO::OnClickedChkGama)
	ON_BN_CLICKED(IDC_CHK_HUE, &CUDSTWO::OnClickedChkHue)
	ON_BN_CLICKED(IDC_CHK_ROLL, &CUDSTWO::OnClickedChkRoll)
	ON_BN_CLICKED(IDC_CHK_SATURE, &CUDSTWO::OnClickedChkSature)
	ON_BN_CLICKED(IDC_CHK_SLOP, &CUDSTWO::OnClickedChkSlop)
	ON_BN_CLICKED(IDC_CHK_WHITEB, &CUDSTWO::OnClickedChkWhiteb)
	ON_BN_CLICKED(IDC_CHK_ZOOM, &CUDSTWO::OnClickedChkZoom)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BACKLIGHT, &CUDSTWO::OnCustomdrawSliderBacklight)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BCONTRAST, &CUDSTWO::OnCustomdrawSliderBcontrast)
//	ON_COMMAND(IDC_SLIDER_CGAMA, &CUDSTWO::OnSliderCgama)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CLEAR, &CUDSTWO::OnCustomdrawSliderClear)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_EXPOS, &CUDSTWO::OnCustomdrawSliderExpos)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_FOCUS, &CUDSTWO::OnCustomdrawSliderFocus)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_FULLVIEW, &CUDSTWO::OnCustomdrawSliderFullview)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAIN, &CUDSTWO::OnCustomdrawSliderGain)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAMA, &CUDSTWO::OnCustomdrawSliderGama)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_HUE, &CUDSTWO::OnCustomdrawSliderHue)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ROLL, &CUDSTWO::OnCustomdrawSliderRoll)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SATURE, &CUDSTWO::OnCustomdrawSliderSature)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SLOP, &CUDSTWO::OnCustomdrawSliderSlop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_WHITEB, &CUDSTWO::OnCustomdrawSliderWhiteb)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ZOOM, &CUDSTWO::OnCustomdrawSliderZoom)
	ON_BN_CLICKED(IDC_BTN_MANAGE, &CUDSTWO::OnBnClickedBtnManage)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_LIGHTBOX, &CUDSTWO::OnCustomdrawSliderLightbox)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_FOLD, &CUDSTWO::OnBnClickedBtnFold)
	ON_MESSAGE(WM_ADDTEM, &CUDSTWO::OnAddtem)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CGRAY, &CUDSTWO::OnCustomdrawSliderCgray)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_LIGHTBOX2, &CUDSTWO::OnCustomdrawSliderLightbox2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BDELAY, &CUDSTWO::OnCustomdrawSliderBdelay)
	ON_BN_CLICKED(IDC_CHK_BHDR, &CUDSTWO::OnClickedChkBhdr)
	ON_BN_CLICKED(IDC_CHK_BREFLECT, &CUDSTWO::OnClickedChkBreflect)
	ON_BN_CLICKED(IDC_CHK_VMERGE, &CUDSTWO::OnClickedChkVmerge)
	ON_BN_CLICKED(IDC_CHK_HMERGE, &CUDSTWO::OnClickedChkHmerge)
	ON_CBN_SELCHANGE(IDC_CMB_BRES, &CUDSTWO::OnSelchangeCmbBres)
	ON_CBN_SELCHANGE(IDC_CMB_BFORMAT, &CUDSTWO::OnSelchangeCmbBformat)
	ON_BN_CLICKED(IDC_BTN_BRECOVER, &CUDSTWO::OnBnClickedBtnBrecover)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BHDRGRAY, &CUDSTWO::OnCustomdrawSliderBhdrgray)
	ON_BN_CLICKED(IDC_CHK_BACKLGT, &CUDSTWO::OnClickedChkBacklgt)
	ON_BN_CLICKED(IDC_CHK_HDRBACKLGT, &CUDSTWO::OnClickedChkHdrbacklgt)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_HDRLLGT, &CUDSTWO::OnCustomdrawSldHdrllgt)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_HDRHLGT, &CUDSTWO::OnCustomdrawSldHdrhlgt)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_HDRLGRY, &CUDSTWO::OnCustomdrawSlidHdrlgry)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_HDRHGRY, &CUDSTWO::OnCustomdrawSlidHdrhgry)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_HDRLDLY, &CUDSTWO::OnCustomdrawSlidHdrldly)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_HDRHDLY, &CUDSTWO::OnCustomdrawSlidHdrhdly)
	ON_BN_CLICKED(IDC_CHK_HDRLBCK, &CUDSTWO::OnClickedChkHdrlbck)
	ON_BN_CLICKED(IDC_CHK_HDRHBCK, &CUDSTWO::OnClickedChkHdrhbck)
END_MESSAGE_MAP()


// CUDSTWO 消息处理程序


BOOL CUDSTWO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/****************************
	*
	* 0、
	* 1、变量初始化
	* 2、读取xml，界面初始化
	* 3、界面美化
	* 4、界面语言初始化
	*
	*
	*
	****************************/
	/*0、*/
	



	/*1、变量初始化*/
	m_pSubWnd = GetParentOwner();
	m_hSubWnd = m_pSubWnd->m_hWnd;

	m_nIris        = 0;      
	m_nBright      = 0;    
	m_nExpos       = 0;      
	m_nFocus       = 0;     
	m_nGama        = 0;       
	m_nGain        = 0;       
	m_nHue         = 0;        
	m_nPan         = 0;       
	m_nRoll        = 0;     
	m_nSlope       = 0;      
	m_nZoom        = 0;       
	m_nContrast    = 0;   
	m_nClear       = 0;     
	m_nSaturab     = 0;    
	m_nWhiteblance = 0;
	m_nBacklight   = 0; 

	m_nLastBright  = 0;
	m_nLastContrast= 0;
	m_nLastLightBox= 0;
	m_nGap         = 27;
	m_nLastRes     = 0;
	m_nLastImgType = 0;

	m_BFold        = TRUE;
	m_BEnableSta   = FALSE;

	m_clrCtrlColor  = RGB(72, 77, 91);
	m_clrBackColor  = RGB(72, 77, 91);
	m_clrTextColor  = RGB(255, 255, 255);

	m_strXmlDoc  = Self_GetMyDocument();
	m_strXmlDoc += _T("\\");
	m_strXmlDoc += _T("UDSXRayData");
	m_strXmlDoc += _T("\\");

	m_strLgeXmlPath  = m_strXmlDoc;
	m_strLgeXmlPath += _T("language.xml");

	m_strIniPath = m_strXmlDoc;
	m_strIniPath+= _T("BaseConfig.ini");
	m_strXmlDoc += _T("xml");

	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcTab2Lge, _T("Tab2"));
	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcTipsLge, _T("Tips"));
	/*2、读取xml并初始化界面控件*/
	//分辨率列表
	int tem_nResIndex = 0;
	std::vector<CString>::iterator  item_res;
	for (item_res=g_vcRes.begin(); item_res!=g_vcRes.end(); item_res++, tem_nResIndex++)
	{
		m_conBReslution.InsertString(tem_nResIndex, *item_res);
	}

	//图像格式列表
	m_conBFormat.InsertString(0, _T("bmp"));
	m_conBFormat.InsertString(1, _T("jpg"));
	m_conBFormat.InsertString(2, _T("png"));
	m_conBFormat.InsertString(3, _T("tif"));
	m_conBFormat.InsertString(4, _T("pdf"));
	m_conBFormat.InsertString(5, _T("dcm"));

	int     tem_nRead      = 0;
	CString tem_strRead    = _T("");
	CString tem_strLastTem = _T("");
	

	::GetPrivateProfileString(_T("BaseSet"), _T("Template"), _T("没有找到Template信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_strLastTem = tem_strRead;
	tem_strRead.ReleaseBuffer();

	Self_FindAllTem(m_strXmlDoc);
	BOOL    tem_bTem = TRUE;
	for (int i=0; i<m_vcXmlName.size(); i++)
	{
		if (tem_strLastTem == m_vcXmlName[i])
		{
			tem_bTem = FALSE;
			//加载模板--------------------------------------
			CString   tem_strTemPath = m_vcXmlPath[i];
			Self_ReadXml(tem_strTemPath);
		}
	}
	if (tem_bTem)
	{
		Self_ReadXml(g_strProXmlPath);
	}

//	Self_ReadXml(g_strProXmlPath);

	/*3、界面美化*/
	//a、窗口背景设置
	CDialogEx::SetBackgroundColor(m_clrBackColor);
	LoadPicture(m_imgBK, IDB_PNG_BKBLACK, _T("PNG"));

	SetWindowTheme(GetDlgItem(IDC_GRP_BONE)->GetSafeHwnd(), _T(""), _T("")); 

//	m_btnOutput.Init(IDB_PNG_OUTPUT, BTN_IMG_3, BTN_TYPE_NORMAL);
//	m_btnManage.Init(IDB_PNG_MANAGE, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnFold.Init(IDB_PNG_DOWN, BTN_IMG_3, BTN_TYPE_NORMAL);

	m_tipInfo.Create(this);
//	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_OUTPUT), _T("导出模板"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_MANAGE), m_vcTab2Lge[20]);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_FOLD), m_vcTab2Lge[18]);
	

	m_tipInfo.SetDelayTime(TTDT_INITIAL, 100);
	m_tipInfo.SetDelayTime(TTDT_AUTOPOP, 5000);
	m_tipInfo.SetDelayTime(TTDT_RESHOW, 100);
	m_tipInfo.SetTipTextColor(RGB(255, 255, 255));
	m_tipInfo.SetTipBkColor(RGB(0, 0, 0));
	m_tipInfo.Activate(TRUE);

	/*4、界面语言初始化*/
	GetDlgItem(IDC_GRP_BONE)->SetWindowText(m_vcTab2Lge[0]);
	GetDlgItem(IDC_STA_EXPOS)->SetWindowText(m_vcTab2Lge[1]);
	GetDlgItem(IDC_STA_LIGHTBOX)->SetWindowText(m_vcTab2Lge[2]);
	GetDlgItem(IDC_STA_BBRIGHT)->SetWindowText(m_vcTab2Lge[3]);
	GetDlgItem(IDC_STA_BCONTRAST)->SetWindowText(m_vcTab2Lge[4]);
	GetDlgItem(IDC_STA_CLEAR)->SetWindowText(m_vcTab2Lge[5]);
	GetDlgItem(IDC_STA_GAMA)->SetWindowText(m_vcTab2Lge[6]);
	GetDlgItem(IDC_STA_GAIN)->SetWindowText(m_vcTab2Lge[7]);
//	GetDlgItem(IDC_STA_FOCUS)->SetWindowText(m_vcTab2Lge[8]);
	GetDlgItem(IDC_STA_SATURE)->SetWindowText(m_vcTab2Lge[9]);
//	GetDlgItem(IDC_STA_IRIS)->SetWindowText(m_vcTab2Lge[10]);
	GetDlgItem(IDC_STA_HUE)->SetWindowText(m_vcTab2Lge[11]);
//	GetDlgItem(IDC_STA_FULLVIEW)->SetWindowText(m_vcTab2Lge[12]);
//	GetDlgItem(IDC_STA_ROLL)->SetWindowText(m_vcTab2Lge[13]);
//	GetDlgItem(IDC_STA_SLOP)->SetWindowText(m_vcTab2Lge[14]);
//	GetDlgItem(IDC_STA_ZOOM)->SetWindowText(m_vcTab2Lge[15]);
	GetDlgItem(IDC_STA_WHITEB)->SetWindowText(m_vcTab2Lge[16]);
//	GetDlgItem(IDC_STA_BACKLIGHT)->SetWindowText(m_vcTab2Lge[17]);
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH CUDSTWO::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	BOOL  tem_BCtrlDisable = FALSE;
	if (pWnd->GetDlgCtrlID()==IDC_STA_BBRIGHT || pWnd->GetDlgCtrlID()==IDC_STA_EXPOS || 
		pWnd->GetDlgCtrlID()==IDC_STA_GAMA || pWnd->GetDlgCtrlID()==IDC_STA_GAIN ||
		pWnd->GetDlgCtrlID()==IDC_STA_HUE || 
		pWnd->GetDlgCtrlID()==IDC_STA_BCONTRAST ||
		pWnd->GetDlgCtrlID()==IDC_STA_CLEAR || pWnd->GetDlgCtrlID()==IDC_STA_SATURE || pWnd->GetDlgCtrlID()==IDC_STA_WHITEB||
		pWnd->GetDlgCtrlID()==IDC_STA_LIGHTBOX || pWnd->GetDlgCtrlID()==IDC_STA_TEMNAME ||
		pWnd->GetDlgCtrlID()==IDC_STA_BHDR || pWnd->GetDlgCtrlID()==IDC_STA_BVMERGE || pWnd->GetDlgCtrlID()==IDC_STA_BHMERGE ||
		pWnd->GetDlgCtrlID()==IDC_STA_CGRAY || pWnd->GetDlgCtrlID()==IDC_STA_CGRAYV || pWnd->GetDlgCtrlID()==IDC_STA_BRES ||
		pWnd->GetDlgCtrlID()==IDC_STA_BFORMAT || pWnd->GetDlgCtrlID()==IDC_STA_BREFLECT ||
		pWnd->GetDlgCtrlID()==IDC_STA_HDRLLGT || pWnd->GetDlgCtrlID()==IDC_STA_HDRLDLY || pWnd->GetDlgCtrlID()==IDC_STA_HDRLGRY ||
		pWnd->GetDlgCtrlID()==IDC_STA_HDRLLGTV || pWnd->GetDlgCtrlID()==IDC_STA_HDRLDLYV || pWnd->GetDlgCtrlID()==IDC_STA_HDRLGRYV ||
		pWnd->GetDlgCtrlID()==IDC_STA_HDRHLGT || pWnd->GetDlgCtrlID()==IDC_STA_HDRHDLY || pWnd->GetDlgCtrlID()==IDC_STA_HDRHGRY ||
		pWnd->GetDlgCtrlID()==IDC_STA_HDRHLGTV || pWnd->GetDlgCtrlID()==IDC_STA_HDRHDLYV || pWnd->GetDlgCtrlID()==IDC_STA_HDRHGRYV)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		std::vector<int>::iterator  item;
		for (item=m_vcDisableSta.begin(); item!=m_vcDisableSta.end(); item++)
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


	if (pWnd->GetDlgCtrlID()==IDC_STA_BMERGE || pWnd->GetDlgCtrlID()==IDC_STA_LIGHTBOX2 || pWnd->GetDlgCtrlID()==IDC_STA_BDELAY ||
		pWnd->GetDlgCtrlID()==IDC_STA_BVMERGE || pWnd->GetDlgCtrlID()==IDC_STA_BHMERGE ||
		pWnd->GetDlgCtrlID()==IDC_STA_DELAYV || pWnd->GetDlgCtrlID()==IDC_STA_LIGHTBOXV2 || pWnd->GetDlgCtrlID()==IDC_STA_BHDRGRAY||
		pWnd->GetDlgCtrlID()==IDC_STA_BHDRGRAYV)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		if (m_BEnableSta)
		{
			pDC->SetTextColor(m_clrTextColor);
		}
		else
		{
			pDC->SetTextColor(RGB(191, 191, 191));
		}
	}




	if (pWnd->GetDlgCtrlID()==IDC_STA_BBRIGHTV || pWnd->GetDlgCtrlID()==IDC_STA_EXPOSV || 
		pWnd->GetDlgCtrlID()==IDC_STA_GAMAV || pWnd->GetDlgCtrlID()==IDC_STA_GAINV ||
		pWnd->GetDlgCtrlID()==IDC_STA_HUEV || 
		pWnd->GetDlgCtrlID()==IDC_STA_BCONTRASTV ||
		pWnd->GetDlgCtrlID()==IDC_STA_CLEARV || pWnd->GetDlgCtrlID()==IDC_STA_SATURAV || pWnd->GetDlgCtrlID()==IDC_STA_WBV||
		pWnd->GetDlgCtrlID()==IDC_STA_LIGHTBOXV)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		std::vector<int>::iterator  item;
		for (item=m_vcDisableStaV.begin(); item!=m_vcDisableStaV.end(); item++)
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

	if(pWnd->GetDlgCtrlID()==IDC_SLIDER_BBRIGHT ||pWnd->GetDlgCtrlID()==IDC_SLIDER_EXPOS ||
		pWnd->GetDlgCtrlID()==IDC_SLIDER_GAMA ||pWnd->GetDlgCtrlID()==IDC_SLIDER_GAIN ||
		pWnd->GetDlgCtrlID()==IDC_SLIDER_HUE || 
		pWnd->GetDlgCtrlID()==IDC_SLIDER_BCONTRAST ||
		pWnd->GetDlgCtrlID()==IDC_SLIDER_CLEAR || pWnd->GetDlgCtrlID()==IDC_SLIDER_SATURE ||pWnd->GetDlgCtrlID()==IDC_SLIDER_WHITEB ||
		pWnd->GetDlgCtrlID()==IDC_SLIDER_LIGHTBOX ||
		pWnd->GetDlgCtrlID()==IDC_SLIDER_LIGHTBOX2 || pWnd->GetDlgCtrlID()==IDC_SLIDER_BDELAY || pWnd->GetDlgCtrlID()==IDC_SLIDER_CGRAY ||
		pWnd->GetDlgCtrlID()==IDC_SLIDER_BHDRGRAY ||
		pWnd->GetDlgCtrlID()==IDC_SLD_HDRLLGT || pWnd->GetDlgCtrlID()==IDC_SLID_HDRLDLY || pWnd->GetDlgCtrlID()==IDC_SLID_HDRLGRY ||
		pWnd->GetDlgCtrlID()==IDC_SLD_HDRHLGT || pWnd->GetDlgCtrlID()==IDC_SLID_HDRHDLY || pWnd->GetDlgCtrlID()==IDC_SLID_HDRHGRY)
	{
		return (HBRUSH) CreateSolidBrush(m_clrCtrlColor); 
	}

	if (pWnd->GetDlgCtrlID()==IDC_GRP_BONE)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}



	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CUDSTWO::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_tipInfo.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUDSTWO::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
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
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CUDSTWO::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (::IsWindow(GetDlgItem(IDC_STA_EXPOS)->GetSafeHwnd()))
	{
		if (IsIconic())
		{
			return;
		}
		//获取窗口区域
		CRect   tem_rcSubBRect;
		GetClientRect(&tem_rcSubBRect);
		int   tem_nx      = 0;
		int   tem_ny      = 0;
		int   tem_nWidth  = 0;
		int   tem_nHeight = 0;

		int   tem_nScreenWidth  = GetSystemMetrics(SM_CXSCREEN) ;    //屏幕宽
		int   tem_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);     //屏幕高

		if (tem_nScreenWidth>1900)
		{
			m_nGap = 35;
		}
		else
		{
			m_nGap = 25;
		}

		if (m_BFold)
		{
			Self_HideCtrl(m_BFold);
			tem_nx = 25;
			tem_ny = 35;
			if (tem_nScreenWidth>1900)
			{
				tem_nWidth  = 130;
			}
			else
			{
				tem_nWidth  = 100;
			}
			tem_nHeight = 30;
			GetDlgItem(IDC_STA_EXPOS)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_LIGHTBOX)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BBRIGHT)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BCONTRAST)->MoveWindow(tem_nx-5, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_SATURE)->MoveWindow(tem_nx-5, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_CLEAR)->MoveWindow(tem_nx-5, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_GAMA)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_GAIN)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			//Gama和增益替换为灰阶
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_CGRAY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			//End

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_WHITEB)->MoveWindow(tem_nx-5, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_FOCUS)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);	


			tem_ny += m_nGap;
			GetDlgItem(IDC_CHK_BHDR)->MoveWindow(tem_nx, tem_ny, 12, 12, TRUE);

			GetDlgItem(IDC_STA_BHDR)->MoveWindow(tem_nx+15, tem_ny, 70, 30, TRUE);


			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BMERGE)->MoveWindow(tem_nx, tem_ny, 80, 30, TRUE);

			GetDlgItem(IDC_CHK_VMERGE)->MoveWindow(tem_nx+90, tem_ny, 12, 12, TRUE);
			GetDlgItem(IDC_STA_BVMERGE)->MoveWindow(tem_nx+112, tem_ny, 40, 30, TRUE);

			GetDlgItem(IDC_CHK_HMERGE)->MoveWindow(tem_nx+162, tem_ny, 12, 12, TRUE);
			GetDlgItem(IDC_STA_BHMERGE)->MoveWindow(tem_nx+194, tem_ny, 40, 30, TRUE);
			
 			tem_ny += m_nGap;
 			GetDlgItem(IDC_STA_LIGHTBOX2)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
 
 			tem_ny += m_nGap;
 			GetDlgItem(IDC_STA_BDELAY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BHDRGRAY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap*3/2;
			GetDlgItem(IDC_CHK_BREFLECT)->MoveWindow(tem_nx, tem_ny, 12, 12, TRUE);

			GetDlgItem(IDC_STA_BREFLECT)->MoveWindow(tem_nx+15, tem_ny, 160, 30, TRUE);


			//--------------------------------------------------------------------------------------------------
			tem_nx = tem_rcSubBRect.right-40;
			tem_ny = 35;
			tem_nWidth  = 40;
			tem_nHeight = 30;
			GetDlgItem(IDC_STA_EXPOSV)->MoveWindow(tem_nx-15, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			GetDlgItem(IDC_CHK_EXPOS)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+3, 12, 12, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_LIGHTBOXV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BBRIGHTV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BCONTRASTV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_SATURAV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_CLEARV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_GAMAV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_GAINV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			//Gama和增益替换为灰阶
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_CGRAYV)->MoveWindow(tem_nx-15, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			GetDlgItem(IDC_CHK_BACKLGT)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+3, 12, 12, TRUE);
			//End

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_WBV)->MoveWindow(tem_nx-15, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			GetDlgItem(IDC_CHK_WHITEB)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+3, 12, 12, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_FOCUSV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_LIGHTBOXV2)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_DELAYV)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BHDRGRAYV)->MoveWindow(tem_nx-15, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);
			GetDlgItem(IDC_CHK_HDRBACKLGT)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+m_nGap*2+3, 12, 12, TRUE);

			if (tem_nScreenWidth>1900)
			{
				GetDlgItem(IDC_BTN_FOLD)->MoveWindow(tem_nx-15, tem_ny+m_nGap*4, 32, 32, TRUE);
			}
			else
			{
				GetDlgItem(IDC_BTN_FOLD)->MoveWindow(tem_nx-15, tem_ny+32+m_nGap*2, 32, 32, TRUE);
			}

			
			tem_ny = 35;
			if (tem_nScreenWidth>1900)
			{
				tem_nx = 105;
				tem_nWidth  = tem_rcSubBRect.Width()-150;
			}
			else
			{
				tem_nx = 75;
				tem_nWidth  = tem_rcSubBRect.Width()-120;
			}
			
			tem_nHeight = 20;
			GetDlgItem(IDC_SLIDER_EXPOS)->MoveWindow(tem_nx, tem_ny, tem_nWidth-15, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_LIGHTBOX)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_BBRIGHT)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_BCONTRAST)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_SATURE)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_CLEAR)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_SLIDER_GAMA)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_ny += 30;
// 			GetDlgItem(IDC_SLIDER_GAIN)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			//Gama和增益替换为灰阶
			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_CGRAY)->MoveWindow(tem_nx, tem_ny, tem_nWidth-15, tem_nHeight, TRUE);
			//End

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_WHITEB)->MoveWindow(tem_nx, tem_ny, tem_nWidth-15, tem_nHeight, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_SLIDER_FOCUS)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_LIGHTBOX2)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_BDELAY)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_BHDRGRAY)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth-15, tem_nHeight, TRUE);


			//布局包围曝光
			tem_nx = 5;
			tem_ny = 10;
			tem_nWidth  = tem_rcSubBRect.Width()-10;
			tem_nHeight = m_nGap*15;
			GetDlgItem(IDC_GRP_BONE)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight+m_nGap, TRUE);

			tem_nx = 10;
			tem_ny = m_nGap*15;
			tem_nWidth  = 100;
			tem_nHeight = 25;
			GetDlgItem(IDC_BTN_BRECOVER)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);

			tem_nx     += 120;
			tem_nWidth  = 80;
			tem_nHeight = 25;
			GetDlgItem(IDC_BTN_MANAGE)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);

// 			tem_nx = 5;
// 			tem_ny = 340;
// 			tem_nWidth  = 60;
// 			tem_nHeight = 30;
// 			GetDlgItem(IDC_STA_TEMNAME)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_nx = 70;
// 			tem_ny = 335;
// 			tem_nWidth  = 100;
// 			tem_nHeight = 25;
// 			GetDlgItem(IDC_EDIT_TEMNAME)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_nx = 180;
// 			tem_ny = 333;
// 			tem_nWidth  = 32;
// 			tem_nHeight = 32;
// 			GetDlgItem(IDC_BTN_OUTPUT)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_nx = 217;
// 			tem_ny = 333;
// 			tem_nWidth  = 32;
// 			tem_nHeight = 32;
// 			GetDlgItem(IDC_BTN_MANAGE)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
		} 
		else
		{
			Self_HideCtrl(m_BFold);
			tem_nx = 25;
			tem_ny = 35;
			if (tem_nScreenWidth>1900)
			{
				tem_nWidth  = 130;
			}
			else
			{
				tem_nWidth  = 100;
			}
			tem_nHeight = 30;
			GetDlgItem(IDC_STA_EXPOS)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_LIGHTBOX)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BBRIGHT)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BCONTRAST)->MoveWindow(tem_nx-5, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_SATURE)->MoveWindow(tem_nx-5, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_CLEAR)->MoveWindow(tem_nx-5, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_GAMA)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_GAIN)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			//Gama和增益替换为灰阶
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_CGRAY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			//End

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_WHITEB)->MoveWindow(tem_nx-5, tem_ny, tem_nWidth, tem_nHeight, TRUE);

//			tem_ny += m_nGap;
//			GetDlgItem(IDC_STA_FOCUS)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_IRIS)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HUE)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_FULLVIEW)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_ROLL)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_SLOP)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_ZOOM)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

//			tem_ny += m_nGap;
//			GetDlgItem(IDC_STA_BACKLIGHT)->MoveWindow(tem_nx-15, tem_ny, 80, tem_nHeight, TRUE);

			//包围曝光-----------------------------------------------------------------
			tem_ny += m_nGap;
			tem_ny += 10;
			GetDlgItem(IDC_CHK_BHDR)->MoveWindow(tem_nx, tem_ny, 12, 12, TRUE);

			GetDlgItem(IDC_STA_BHDR)->MoveWindow(tem_nx+15, tem_ny, 80, 30, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BMERGE)->MoveWindow(tem_nx, tem_ny, 80, 30, TRUE);

			GetDlgItem(IDC_CHK_VMERGE)->MoveWindow(tem_nx+90, tem_ny, 12, 12, TRUE);
			GetDlgItem(IDC_STA_BVMERGE)->MoveWindow(tem_nx+112, tem_ny, 40, 30, TRUE);

			GetDlgItem(IDC_CHK_HMERGE)->MoveWindow(tem_nx+162, tem_ny, 12, 12, TRUE);
			GetDlgItem(IDC_STA_BHMERGE)->MoveWindow(tem_nx+194, tem_ny, 40, 30, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_LIGHTBOX2)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BDELAY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BHDRGRAY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_CHK_BREFLECT)->MoveWindow(tem_nx, tem_ny, 12, 12, TRUE);

			GetDlgItem(IDC_STA_BREFLECT)->MoveWindow(tem_nx+15, tem_ny, 160, 30, TRUE);
			//end---------------------------------------------------------------------

			//HDR-----------------------------------------------------------------------------------
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRLLGT)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRLDLY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRLGRY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRHLGT)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRHDLY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRHGRY)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			//end-----------------------------------------------------------------------------------

			tem_ny += m_nGap;
			tem_ny += 5;

			if (tem_nScreenWidth>1900)
			{
				GetDlgItem(IDC_STA_BRES)->MoveWindow(tem_nx, tem_ny+2, 90, tem_nHeight, TRUE);
				GetDlgItem(IDC_CMB_BRES)->MoveWindow(tem_nx+90, tem_ny, tem_nWidth-30, tem_nHeight, TRUE);
			}
			else
			{
				GetDlgItem(IDC_STA_BRES)->MoveWindow(tem_nx, tem_ny+2, 70, tem_nHeight, TRUE);
				GetDlgItem(IDC_CMB_BRES)->MoveWindow(tem_nx+70, tem_ny, tem_nWidth+20, tem_nHeight, TRUE);
			}
			

			tem_ny += m_nGap;
			tem_ny +=3;

			if (tem_nScreenWidth>1900)
			{
				GetDlgItem(IDC_STA_BFORMAT)->MoveWindow(tem_nx, tem_ny+3, 90, tem_nHeight, TRUE);
				GetDlgItem(IDC_CMB_BFORMAT)->MoveWindow(tem_nx+90, tem_ny, tem_nWidth-30, tem_nHeight, TRUE);
			}
			else
			{
				GetDlgItem(IDC_STA_BFORMAT)->MoveWindow(tem_nx, tem_ny+3, 70, tem_nHeight, TRUE);
				GetDlgItem(IDC_CMB_BFORMAT)->MoveWindow(tem_nx+70, tem_ny, tem_nWidth+20, tem_nHeight, TRUE);
			}
			

			if (tem_nScreenWidth>1900)
			{
				GetDlgItem(IDC_BTN_FOLD)->MoveWindow(tem_rcSubBRect.Width()-45, tem_ny-15, 32, 32, TRUE);
			}
			else
			{
				GetDlgItem(IDC_BTN_FOLD)->MoveWindow(tem_rcSubBRect.Width()-45, tem_ny-15, 32, 32, TRUE);
			}
			

			tem_nx = tem_rcSubBRect.right-40;
			tem_ny = 35;
			tem_nWidth  = 40;
			tem_nHeight = 30;
			GetDlgItem(IDC_STA_EXPOSV)->MoveWindow(tem_nx-15, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			GetDlgItem(IDC_CHK_EXPOS)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+3, 12, 12, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_LIGHTBOXV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BBRIGHTV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BCONTRASTV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_SATURAV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_CLEARV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_GAMAV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_ny += 30;
// 			GetDlgItem(IDC_STA_GAINV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			//Gama和增益替换为灰阶
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_CGRAYV)->MoveWindow(tem_nx-15, tem_ny, tem_nWidth, tem_nHeight, TRUE);
			GetDlgItem(IDC_CHK_BACKLGT)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+3, 12, 12, TRUE);
			//End

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_WBV)->MoveWindow(tem_nx-15, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			GetDlgItem(IDC_CHK_WHITEB)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+3, 12, 12, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_FOCUSV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_IRISV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HUEV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_PANV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_ROLLV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_SLOPV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_ZOOMV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_STA_BACKLIGHTV)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			//包围曝光------------------------------------------------------------------------------
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_LIGHTBOXV2)->MoveWindow(tem_nx, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_DELAYV)->MoveWindow(tem_nx, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_BHDRGRAYV)->MoveWindow(tem_nx-15, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);
			GetDlgItem(IDC_CHK_HDRBACKLGT)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+m_nGap*5/2+3, 12, 12, TRUE);
			//end-----------------------------------------------------------------------------------

			//HDR-----------------------------------------------------------------------------------
			tem_ny += m_nGap;
			tem_ny += 3/2*m_nGap;
			GetDlgItem(IDC_STA_HDRLLGTV)->MoveWindow(tem_nx, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRLDLYV)->MoveWindow(tem_nx, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRLGRYV)->MoveWindow(tem_nx-15, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);
			GetDlgItem(IDC_CHK_HDRLBCK)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+m_nGap*5/2, 12, 12, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRHLGTV)->MoveWindow(tem_nx, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRHDLYV)->MoveWindow(tem_nx, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_STA_HDRHGRYV)->MoveWindow(tem_nx-15, tem_ny+m_nGap*5/2, tem_nWidth, tem_nHeight, TRUE);
			GetDlgItem(IDC_CHK_HDRHBCK)->MoveWindow(tem_rcSubBRect.right-25, tem_ny+m_nGap*5/2, 12, 12, TRUE);
			//end-----------------------------------------------------------------------------------


//			GetDlgItem(IDC_BTN_FOLD)->MoveWindow(tem_nx-15, tem_ny+m_nGap*3, 32, 32, TRUE);

			tem_ny = 35;
			if (tem_nScreenWidth>1900)
			{
				tem_nx = 105;
				tem_nWidth  = tem_rcSubBRect.Width()-150;
			}
			else
			{
				tem_nx = 75;
				tem_nWidth  = tem_rcSubBRect.Width()-120;
			}
			tem_nHeight = 20;
			GetDlgItem(IDC_SLIDER_EXPOS)->MoveWindow(tem_nx, tem_ny, tem_nWidth-15, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_LIGHTBOX)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_BBRIGHT)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_BCONTRAST)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_SATURE)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_CLEAR)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += 30;
// 			GetDlgItem(IDC_SLIDER_GAMA)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
// 
// 			tem_ny += 30;
// 			GetDlgItem(IDC_SLIDER_GAIN)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			//Gama和增益替换为灰阶
			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_CGRAY)->MoveWindow(tem_nx, tem_ny, tem_nWidth-15, tem_nHeight, TRUE);
			//End

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_WHITEB)->MoveWindow(tem_nx, tem_ny, tem_nWidth-15, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_SLIDER_FOCUS)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_SLIDER_IRIS)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_HUE)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_SLIDER_FULLVIEW)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_SLIDER_ROLL)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_SLIDER_SLOP)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_SLIDER_ZOOM)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_ny += m_nGap;
// 			GetDlgItem(IDC_SLIDER_BACKLIGHT)->MoveWindow(tem_nx+3, tem_ny, tem_nWidth-3, tem_nHeight, TRUE);

			//包围曝光--------------------------------------------------------------------------------------
			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_LIGHTBOX2)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_BDELAY)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth, tem_nHeight, TRUE);

			tem_ny += m_nGap;
			GetDlgItem(IDC_SLIDER_BHDRGRAY)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth-15, tem_nHeight, TRUE);
			//end-------------------------------------------------------------------------------------------

			//HDR-------------------------------------------------------------------------------------------
			tem_ny += m_nGap;
			tem_ny += 3/2*m_nGap;
			GetDlgItem(IDC_SLD_HDRLLGT)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth-15, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_SLID_HDRLDLY)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth-15, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_SLID_HDRLGRY)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth-15, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_SLD_HDRHLGT)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth-15, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_SLID_HDRHDLY)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth-15, tem_nHeight, TRUE);
			tem_ny += m_nGap;
			GetDlgItem(IDC_SLID_HDRHGRY)->MoveWindow(tem_nx, tem_ny+m_nGap*2+10, tem_nWidth-15, tem_nHeight, TRUE);
			//end-------------------------------------------------------------------------------------------

			tem_nx = 5;
			tem_ny = 10;
			tem_nWidth  = tem_rcSubBRect.Width()-10;
			tem_nHeight = m_nGap*23;
			GetDlgItem(IDC_GRP_BONE)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight+m_nGap*2, TRUE);

			tem_nx = 10;
			tem_ny = m_nGap*23.5;
			tem_nWidth  = 100;
			tem_nHeight = 25;
			GetDlgItem(IDC_BTN_BRECOVER)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);

			tem_nx     += 120;
			tem_nWidth  = 80;
			tem_nHeight = 25;
			GetDlgItem(IDC_BTN_MANAGE)->MoveWindow(tem_nx, tem_ny+m_nGap*2, tem_nWidth, tem_nHeight, TRUE);


// 			tem_nx = 5;
// 			tem_ny = 600;
// 			tem_nWidth  = 60;
// 			tem_nHeight = 30;
// 			GetDlgItem(IDC_STA_TEMNAME)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_nx = 70;
// 			tem_ny = 595;
// 			tem_nWidth  = 100;
// 			tem_nHeight = 25;
// 			GetDlgItem(IDC_EDIT_TEMNAME)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_nx = 180;
// 			tem_ny = 593;
// 			tem_nWidth  = 32;
// 			tem_nHeight = 32;
// 			GetDlgItem(IDC_BTN_OUTPUT)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);

// 			tem_nx = 217;
// 			tem_ny = 593;
// 			tem_nWidth  = 32;
// 			tem_nHeight = 32;
// 			GetDlgItem(IDC_BTN_MANAGE)->MoveWindow(tem_nx, tem_ny, tem_nWidth, tem_nHeight, TRUE);
		}
	}
}


CString CUDSTWO::Self_GetMyDocument(void)
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

void CUDSTWO::Self_ReadXml(CString xmlpath)
{
	int	ID_SLD[18][4]={{IDC_STA_IRIS, IDC_SLIDER_IRIS, IDC_STA_IRISV, IDC_CHK_IRIS}, {IDC_STA_BBRIGHT, IDC_SLIDER_BBRIGHT, IDC_STA_BBRIGHTV, IDC_CHK_BBRIGHT}, {IDC_STA_EXPOS, IDC_SLIDER_EXPOS, IDC_STA_EXPOSV, IDC_CHK_EXPOS},
	{IDC_STA_FOCUS, IDC_SLIDER_FOCUS, IDC_STA_FOCUSV, IDC_CHK_FOCUS}, {IDC_STA_GAMA, IDC_SLIDER_GAMA, IDC_STA_GAMAV, IDC_CHK_GAMA}, {IDC_STA_GAIN, IDC_SLIDER_GAIN, IDC_STA_GAINV, IDC_CHK_GAIN}, 
	{IDC_STA_HUE, IDC_SLIDER_HUE, IDC_STA_HUEV, IDC_CHK_HUE}, {IDC_STA_FULLVIEW, IDC_SLIDER_FULLVIEW, IDC_STA_PANV, IDC_CHK_FULLVIEW}, {IDC_STA_ROLL, IDC_SLIDER_ROLL, IDC_STA_ROLLV, IDC_CHK_ROLL}, 
	{IDC_STA_SLOP, IDC_SLIDER_SLOP, IDC_STA_SLOPV, IDC_CHK_SLOP}, {IDC_STA_ZOOM, IDC_SLIDER_ZOOM, IDC_STA_ZOOMV, IDC_CHK_ZOOM}, {IDC_STA_BCONTRAST, IDC_SLIDER_BCONTRAST, IDC_STA_BCONTRASTV, IDC_CHK_BCONTRAST}, 
	{IDC_STA_CLEAR, IDC_SLIDER_CLEAR, IDC_STA_CLEARV, IDC_CHK_CLEAR}, {IDC_STA_SATURE, IDC_SLIDER_SATURE, IDC_STA_SATURAV, IDC_CHK_SATURE}, {IDC_STA_WHITEB, IDC_SLIDER_WHITEB, IDC_STA_WBV, IDC_CHK_WHITEB}, 
	{IDC_STA_BACKLIGHT, IDC_SLIDER_BACKLIGHT, IDC_STA_BACKLIGHTV, IDC_CHK_BACKLIGHT}, {IDC_STA_LIGHTBOX, IDC_SLIDER_LIGHTBOX, IDC_STA_LIGHTBOXV, IDC_CHK_BACKLIGHT}, {IDC_STA_CGRAY, IDC_SLIDER_CGRAY, IDC_STA_CGRAYV, 0}};

	int            tem_nAuto = 0;
	
	CStringA       tem_straXmlPath(xmlpath);
	const char*    tem_pcXmlPath = tem_straXmlPath.GetString();

	TiXmlDocument    tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_pcXmlPath);

	//根节点
	const char*     tem_pcRootName;
	TiXmlElement*   tem_xmlRootElt = tem_xmlDoc.RootElement();
	tem_pcRootName = tem_xmlRootElt->Value();                   //获取根节点的名称


	//第一个子节点
	TiXmlElement*   tem_xmlChildElt = tem_xmlRootElt->FirstChildElement();
	tem_pcRootName =tem_xmlChildElt->Value();                  //第一个子节点的名称

	for (int i=0; i<18; i++)
	{
		if (i==0 || i==3 || i==4 || i==5 || i==7 || i==8 || i==9 || i==10)
		{
			tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
			tem_pcRootName =tem_xmlChildElt->Value(); 
			continue;
		}
		//第一个属性
		TiXmlAttribute* tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
		int  tem_nValue = tem_xmlAttribute->IntValue();
		if (tem_nValue == 1)
		{
			//支持该参数
			GetDlgItem(ID_SLD[i][0])->EnableWindow(TRUE);
			tem_xmlAttribute = tem_xmlAttribute->Next();
			tem_nAuto = tem_xmlAttribute->IntValue();

			if (i==2 || i==14)
			{
				//考虑自动曝光和自动白平衡
				if (tem_nAuto==1)
				{
					((CButton*)GetDlgItem(ID_SLD[i][3]))->SetCheck(TRUE);
					GetDlgItem(ID_SLD[i][1])->EnableWindow(FALSE);
				} 
				else
				{
					((CButton*)GetDlgItem(ID_SLD[i][3]))->SetCheck(FALSE);	
					GetDlgItem(ID_SLD[i][1])->EnableWindow(TRUE);
				}

			}
			else
			{
				GetDlgItem(ID_SLD[i][2])->EnableWindow(TRUE);
			}	

			
			tem_xmlAttribute = tem_xmlAttribute->Next();
			tem_nValue = tem_xmlAttribute->IntValue();
			CString tem_strValue;
			tem_strValue.Format(_T("%d"), tem_nValue);
			GetDlgItem(ID_SLD[i][2])->SetWindowText(tem_strValue);

			
			tem_xmlAttribute = tem_xmlAttribute->Next();
			int tem_nMaxValue = tem_xmlAttribute->IntValue();
			tem_xmlAttribute = tem_xmlAttribute->Next();
			int tem_nMinValue = tem_xmlAttribute->IntValue();
			if (i==15)
			{
				if (tem_nValue==0)
				{
					m_nBacklight = 0;
					((CButton*)GetDlgItem(IDC_CHK_BACKLGT))->SetCheck(FALSE);
				}
				else
				{
					m_nBacklight = 1;
					((CButton*)GetDlgItem(IDC_CHK_BACKLGT))->SetCheck(TRUE);
				}
			}
			else
			{
				((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->SetRange(tem_nMinValue, tem_nMaxValue);	
				((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->SetPos(tem_nValue);
				((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->SetPageSize(1);
			}	
			UpdateData(FALSE);
		}
		else
		{
			//不支持该参数
			GetDlgItem(ID_SLD[i][0])->EnableWindow(TRUE);
			m_vcDisableSta.push_back(ID_SLD[i][0]);

			GetDlgItem(ID_SLD[i][1])->EnableWindow(FALSE);

			GetDlgItem(ID_SLD[i][2])->EnableWindow(TRUE);
			GetDlgItem(ID_SLD[i][2])->SetWindowText(_T("0"));
			m_vcDisableStaV.push_back(ID_SLD[i][2]);

//			GetDlgItem(ID_SLD[i][3])->EnableWindow(FALSE);
		}
		if (i<17)
		{
			tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
			tem_pcRootName =tem_xmlChildElt->Value();  
		}
	}

	//HDR开关
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	TiXmlAttribute* tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	int  tem_nValue  = tem_xmlAttribute->IntValue();
	int  tem_nMaxValue = 0;
	int  tem_nMinValue = 0;

	if (tem_nValue == 1)
	{
		//HDR打开----------------------------------------------
		((CButton*)GetDlgItem(IDC_CHK_BHDR))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_BREFLECT))->SetCheck(FALSE);

		//合并方式
		tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
		tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
		int  tem_nValue  = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nAuto        = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nValue       = tem_xmlAttribute->IntValue();
		if (tem_nValue == 1)
		{
			//左右合并
			GetDlgItem(IDC_CHK_VMERGE)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_HMERGE)->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(TRUE);	
		}
		else
		{
			//上下合并
			GetDlgItem(IDC_CHK_VMERGE)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_HMERGE)->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);
		}

		//灯箱偏移
		tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
		tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
		tem_nValue  = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nAuto        = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nValue       = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMaxValue = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMinValue = tem_xmlAttribute->IntValue();
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHTBOX2))->SetRange(tem_nMinValue, tem_nMaxValue);	
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHTBOX2))->SetPos(tem_nValue);
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHTBOX2))->SetPageSize(1);
		m_nLightBox2       = tem_nValue;

		GetDlgItem(IDC_SLIDER_LIGHTBOX2)->EnableWindow(TRUE);

		//延时
		tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
		tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
		tem_nValue  = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nAuto        = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nValue       = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMaxValue = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMinValue = tem_xmlAttribute->IntValue();
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BDELAY))->SetRange(tem_nMinValue, tem_nMaxValue);	
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BDELAY))->SetPos(tem_nValue);
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BDELAY))->SetPageSize(1);
		m_nDelay       = tem_nValue;

		GetDlgItem(IDC_SLIDER_BDELAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_STA_BHDR)->EnableWindow(TRUE);
		m_BEnableSta = TRUE;

		//灰阶
		tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
		tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
		tem_nValue  = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nAuto        = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nValue       = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMaxValue    = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMinValue    = tem_xmlAttribute->IntValue();
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BHDRGRAY))->SetRange(tem_nMinValue, tem_nMaxValue);	
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BHDRGRAY))->SetPos(tem_nValue);
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BHDRGRAY))->SetPageSize(1);
		m_nHdrGray       = tem_nValue;

		GetDlgItem(IDC_SLIDER_BHDRGRAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_STA_BHDRGRAYV)->EnableWindow(TRUE);
		m_BEnableSta = TRUE;

		GetDlgItem(IDC_CHK_HDRBACKLGT)->EnableWindow(TRUE);
	}
	else
	{
		//HDR关闭-----------------------------------------------
		((CButton*)GetDlgItem(IDC_CHK_BHDR))->SetCheck(FALSE);

		//合并方式
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);
		GetDlgItem(IDC_CHK_VMERGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_HMERGE)->EnableWindow(FALSE);
		//修改合并方式的状态--------

		//灯箱偏移
		tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
		tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
		tem_nValue  = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nAuto        = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nValue       = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMaxValue = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMinValue = tem_xmlAttribute->IntValue();
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHTBOX2))->SetRange(tem_nMinValue, tem_nMaxValue);	
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHTBOX2))->SetPos(tem_nValue);
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHTBOX2))->SetPageSize(1);
		m_nLightBox2       = tem_nValue;

		GetDlgItem(IDC_SLIDER_LIGHTBOX2)->EnableWindow(FALSE);


		//延时
		tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
		tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
		tem_nValue  = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nAuto        = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nValue       = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMaxValue = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMinValue = tem_xmlAttribute->IntValue();
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BDELAY))->SetRange(tem_nMinValue, tem_nMaxValue);	
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BDELAY))->SetPos(tem_nValue);
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BDELAY))->SetPageSize(1);
		m_nDelay       = tem_nValue;

		GetDlgItem(IDC_SLIDER_BDELAY)->EnableWindow(FALSE);

		//灰阶
		tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
		tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
		tem_nValue  = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nAuto        = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nValue       = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMaxValue    = tem_xmlAttribute->IntValue();
		tem_xmlAttribute = tem_xmlAttribute->Next();
		tem_nMinValue    = tem_xmlAttribute->IntValue();
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BHDRGRAY))->SetRange(tem_nMinValue, tem_nMaxValue);	
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BHDRGRAY))->SetPos(tem_nValue);
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BHDRGRAY))->SetPageSize(1);
		m_nHdrGray       = tem_nValue;

		GetDlgItem(IDC_SLIDER_BHDRGRAY)->EnableWindow(FALSE);

		GetDlgItem(IDC_STA_BHDR)->EnableWindow(TRUE);
	
		m_BEnableSta = FALSE;

		GetDlgItem(IDC_CHK_HDRBACKLGT)->EnableWindow(FALSE);
	}

	
	//反射稿开关
	tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_nValue  = tem_xmlAttribute->IntValue();
	if (tem_nValue == 1)
	{
		((CButton*)GetDlgItem(IDC_CHK_BREFLECT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_BHDR))->SetCheck(FALSE);

		GetDlgItem(IDC_CHK_VMERGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_HMERGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_LIGHTBOX2)->EnableWindow(FALSE);

		GetDlgItem(IDC_SLIDER_BDELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_HDRBACKLGT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STA_BHDR)->EnableWindow(TRUE);

		m_BEnableSta = FALSE;
	}

	CRect  tem_rcRect;
	GetDlgItem(IDC_STA_BMERGE)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_LIGHTBOX2)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_BDELAY)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);
	GetDlgItem(IDC_STA_BVMERGE)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	GetDlgItem(IDC_STA_BHMERGE)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);
	

	//图像分辨率
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_nValue  = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nAuto        = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	m_nLastRes       = tem_nValue;

	m_conBReslution.SetCurSel(m_nLastRes);
	

	//图像格式
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_nValue  = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nAuto        = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	m_nLastImgType   = tem_nValue;

	m_conBFormat.SetCurSel(m_nLastImgType);

	//包围曝光-逆光对比
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_nValue       = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nAuto        = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	m_nHDRBackLgt    = tem_nValue;
	if (m_nHDRBackLgt == 0)
	{
		m_nHDRBackLgt = 0;
		((CButton*)GetDlgItem(IDC_CHK_HDRBACKLGT))->SetCheck(FALSE);
	}
	else 
	{
		m_nHDRBackLgt = 1;
		((CButton*)GetDlgItem(IDC_CHK_HDRBACKLGT))->SetCheck(TRUE);
	}

	//HDR---------------------------------------------------------------
	
	//灯箱1
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMaxValue    = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMinValue    = tem_xmlAttribute->IntValue();
	m_nLowLight      = tem_nValue;
	((CSliderCtrl*)GetDlgItem(IDC_SLD_HDRLLGT))->SetRange(tem_nMinValue, tem_nMaxValue);	
	((CSliderCtrl*)GetDlgItem(IDC_SLD_HDRLLGT))->SetPos(tem_nValue);
	((CSliderCtrl*)GetDlgItem(IDC_SLD_HDRLLGT))->SetPageSize(1);
	
	//灰阶1
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMaxValue = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMinValue = tem_xmlAttribute->IntValue();
	m_nLowGray      = tem_nValue;
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRLGRY))->SetRange(tem_nMinValue, tem_nMaxValue);	
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRLGRY))->SetPos(tem_nValue);
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRLGRY))->SetPageSize(1);

	//延时1
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMaxValue = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMinValue = tem_xmlAttribute->IntValue();
	m_nLowDelay      = tem_nValue;
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRLDLY))->SetRange(tem_nMinValue, tem_nMaxValue);	
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRLDLY))->SetPos(tem_nValue);
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRLDLY))->SetPageSize(1);

	//逆光对比1
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	m_nLowBackLgt      = tem_nValue;
	if (tem_nValue == 0)
	{
		((CButton*)GetDlgItem(IDC_CHK_HDRLBCK))->SetCheck(FALSE);
	}
	else 
	{
		((CButton*)GetDlgItem(IDC_CHK_HDRLBCK))->SetCheck(TRUE);
	}


	//灯箱2
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMaxValue = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMinValue = tem_xmlAttribute->IntValue();
	m_nHigLight      = tem_nValue;
	((CSliderCtrl*)GetDlgItem(IDC_SLD_HDRHLGT))->SetRange(tem_nMinValue, tem_nMaxValue);	
	((CSliderCtrl*)GetDlgItem(IDC_SLD_HDRHLGT))->SetPos(tem_nValue);
	((CSliderCtrl*)GetDlgItem(IDC_SLD_HDRHLGT))->SetPageSize(1);

	//灰阶2
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMaxValue = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMinValue = tem_xmlAttribute->IntValue();
	m_nHigGray      = tem_nValue;
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRHGRY))->SetRange(tem_nMinValue, tem_nMaxValue);	
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRHGRY))->SetPos(tem_nValue);
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRHGRY))->SetPageSize(1);

	//延时2
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMaxValue = tem_xmlAttribute->IntValue();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nMinValue = tem_xmlAttribute->IntValue();
	m_nHigDelay      = tem_nValue;
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRHDLY))->SetRange(tem_nMinValue, tem_nMaxValue);	
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRHDLY))->SetPos(tem_nValue);
	((CSliderCtrl*)GetDlgItem(IDC_SLID_HDRHDLY))->SetPageSize(1);

	//逆光对比2
	tem_xmlChildElt  = tem_xmlChildElt->NextSiblingElement();
	tem_xmlAttribute = tem_xmlChildElt->FirstAttribute();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_xmlAttribute = tem_xmlAttribute->Next();
	tem_nValue       = tem_xmlAttribute->IntValue();
	m_nHigBackLgt      = tem_nValue;
	if (tem_nValue == 0)
	{
		((CButton*)GetDlgItem(IDC_CHK_HDRHBCK))->SetCheck(FALSE);
	}
	else 
	{
		((CButton*)GetDlgItem(IDC_CHK_HDRHBCK))->SetCheck(TRUE);
	}
	
}


//光圈-----------------------------------
void CUDSTWO::OnClickedChkIris()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_IRIS))
	{
		GetDlgItem(IDC_SLIDER_IRIS)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 1, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_IRIS)->EnableWindow(TRUE);
		m_nIris = m_slidIris.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 1, m_nIris);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderIris(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	m_nIris = m_slidIris.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nIris);
	GetDlgItem(IDC_STA_IRISV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_IRISV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 1, m_nIris);
	
	*/
	*pResult = 0;
}

//亮度----------------------------------
void CUDSTWO::OnClickedChkBbright()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_BBRIGHT))
	{
		GetDlgItem(IDC_SLIDER_BBRIGHT)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 2, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_BBRIGHT)->EnableWindow(TRUE);
		m_nBright = m_slidBBright.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 2, m_nBright);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderBbright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nBright = m_slidBBright.GetPos();
    CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nBright);
	GetDlgItem(IDC_STA_BBRIGHTV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_BBRIGHTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 2, m_nBright);
	m_nLastBright = m_nBright;
	
	*pResult = 0;
}

//曝光----------------------------------
void CUDSTWO::OnClickedChkExpos()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_EXPOS))
	{
		GetDlgItem(IDC_SLIDER_EXPOS)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 3, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_EXPOS)->EnableWindow(TRUE);
		m_nExpos = m_slidExpos.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 3, m_nExpos);
	}
	
}


void CUDSTWO::OnCustomdrawSliderExpos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nExpos = m_slidExpos.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nExpos);
	GetDlgItem(IDC_STA_EXPOSV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_EXPOSV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 3, m_nExpos);

	*pResult = 0;
}

//焦点----------------------------------
void CUDSTWO::OnClickedChkFocus()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_FOCUS))
	{
		GetDlgItem(IDC_SLIDER_FOCUS)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 4, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_FOCUS)->EnableWindow(TRUE);
		m_nFocus = m_slidFocus.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 4, m_nFocus);
	}
	*/
	
}


void CUDSTWO::OnCustomdrawSliderFocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	m_nFocus = m_slidFocus.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nFocus);
	GetDlgItem(IDC_STA_FOCUSV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_FOCUSV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 4, m_nFocus);
	*/
	*pResult = 0;
}

//Gama----------------------------------
void CUDSTWO::OnClickedChkGama()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_GAMA))
	{
		GetDlgItem(IDC_SLIDER_GAMA)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 5, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_GAMA)->EnableWindow(TRUE);
		m_nGama = m_slidGama.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 5, m_nGama);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderGama(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nGama = m_slidGama.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nGama);
	GetDlgItem(IDC_STA_GAMAV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_GAMAV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 5, m_nGama);

	*pResult = 0;
}

//增益----------------------------------
void CUDSTWO::OnClickedChkGain()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_GAIN))
	{
		GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 6, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(TRUE);
		m_nGain = m_slidGain.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 6, m_nGain);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderGain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nGain = m_slidGain.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nGain);
	GetDlgItem(IDC_STA_GAINV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_GAINV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 6, m_nGain);

	*pResult = 0;
}

//色调----------------------------------
void CUDSTWO::OnClickedChkHue()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_HUE))
	{
		GetDlgItem(IDC_SLIDER_HUE)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 7, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_HUE)->EnableWindow(TRUE);
		m_nHue = m_slidHue.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 7, m_nHue);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderHue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nHue = m_slidHue.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nHue);
	GetDlgItem(IDC_STA_HUEV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_HUEV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 7, m_nHue);

	*pResult = 0;
}

//全景
void CUDSTWO::OnClickedChkFullview()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_FULLVIEW))
	{
		GetDlgItem(IDC_SLIDER_FULLVIEW)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 8, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_FULLVIEW)->EnableWindow(TRUE);
		m_nPan = m_slidPan.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 8, m_nPan);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderFullview(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	m_nPan = m_slidPan.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nPan);
	GetDlgItem(IDC_STA_PANV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_PANV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 8, m_nPan);
	*/
	*pResult = 0;
}

//滚动----------------------------------
void CUDSTWO::OnClickedChkRoll()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_ROLL))
	{
		GetDlgItem(IDC_SLIDER_ROLL)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 9, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_ROLL)->EnableWindow(TRUE);
		m_nRoll = m_slidRoll.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 9, m_nRoll);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderRoll(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	m_nRoll = m_slidRoll.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nRoll);
	GetDlgItem(IDC_STA_ROLLV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_ROLLV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 9, m_nRoll);
	*/
	*pResult = 0;
}

//倾斜----------------------------------
void CUDSTWO::OnClickedChkSlop()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_SLOP))
	{
		GetDlgItem(IDC_SLIDER_SLOP)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 10, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_SLOP)->EnableWindow(TRUE);
		m_nSlope = m_slidSlop.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 10, m_nSlope);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderSlop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	m_nSlope = m_slidSlop.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nSlope);
	GetDlgItem(IDC_STA_SLOPV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_SLOPV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 10, m_nSlope);
	*/
	*pResult = 0;
}

//缩放----------------------------------
void CUDSTWO::OnClickedChkZoom()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_ZOOM))
	{
		GetDlgItem(IDC_SLIDER_ZOOM)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 11, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_ZOOM)->EnableWindow(TRUE);
		m_nZoom = m_slidZoom.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 11, m_nZoom);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderZoom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	m_nZoom = m_slidZoom.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nZoom);
	GetDlgItem(IDC_STA_ZOOMV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_ZOOMV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 11, m_nZoom);
	*/
	*pResult = 0;
}

//对比度-------------------------------
void CUDSTWO::OnClickedChkBcontrast()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_BCONTRAST))
	{
		GetDlgItem(IDC_SLIDER_BCONTRAST)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 12, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_BCONTRAST)->EnableWindow(TRUE);
		m_nContrast = m_slidBContrast.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 12, m_nContrast);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderBcontrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nContrast = m_slidBContrast.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nContrast);
	GetDlgItem(IDC_STA_BCONTRASTV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_BCONTRASTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 12, m_nContrast);

	m_nLastContrast = m_nContrast;

	*pResult = 0;
}

//清晰度-------------------------------
void CUDSTWO::OnClickedChkClear()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_CLEAR))
	{
		GetDlgItem(IDC_SLIDER_CLEAR)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 13, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_CLEAR)->EnableWindow(TRUE);
		m_nClear = m_slidClear.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 13, m_nClear);
	}
	*/

}


void CUDSTWO::OnCustomdrawSliderClear(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nClear = m_slidClear.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nClear);
	GetDlgItem(IDC_STA_CLEARV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_CLEARV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 13, m_nClear);

	*pResult = 0;
}

//饱和度-------------------------------
void CUDSTWO::OnClickedChkSature()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_SATURE))
	{
		GetDlgItem(IDC_SLIDER_SATURE)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 14, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_SATURE)->EnableWindow(TRUE);
		m_nSaturab = m_slidSatura.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 14, m_nSaturab);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderSature(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nSaturab = m_slidSatura.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nSaturab);
	GetDlgItem(IDC_STA_SATURAV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_SATURAV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 14, m_nSaturab);

	*pResult = 0;
}

//白平衡-------------------------------
void CUDSTWO::OnClickedChkWhiteb()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_WHITEB))
	{
		GetDlgItem(IDC_SLIDER_WHITEB)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 15, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_WHITEB)->EnableWindow(TRUE);
		m_nWhiteblance = m_slidWhitBlance.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 15, m_nWhiteblance);
	}
}


void CUDSTWO::OnCustomdrawSliderWhiteb(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nWhiteblance = m_slidWhitBlance.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nWhiteblance);
	GetDlgItem(IDC_STA_WBV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_WBV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	//判断白平衡是否自动，若为自动则不发送设置信息
	if (BST_CHECKED!=IsDlgButtonChecked(IDC_CHK_WHITEB))
	{
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 15, m_nWhiteblance);
	}
	

	*pResult = 0;
}

//逆光对比-------------------------------
void CUDSTWO::OnClickedChkBacklight()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_BACKLIGHT))
	{
		GetDlgItem(IDC_SLIDER_BACKLIGHT)->EnableWindow(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 16, 5211314);
	} 
	else
	{
		GetDlgItem(IDC_SLIDER_BACKLIGHT)->EnableWindow(TRUE);
		m_nBacklight = m_slidBackLight.GetPos();
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 16, m_nBacklight);
	}
	*/
}


void CUDSTWO::OnCustomdrawSliderBacklight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	m_nBacklight = m_slidBackLight.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nBacklight);
	GetDlgItem(IDC_STA_BACKLIGHTV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_BACKLIGHTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 16, m_nBacklight);
	*/
	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSliderLightbox(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nLightBox = m_slidBLightBox.GetPos();
	CString tem_strValue = _T("");
	if (m_nLightBox ==0 )
	{
		tem_strValue.Format(_T("%d"), m_nLightBox);
		GetDlgItem(IDC_STA_LIGHTBOXV)->SetWindowText(tem_strValue);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 18, m_nLightBox);
	}
	else if (m_nLightBox == 100)
	{
		tem_strValue.Format(_T("%d"), m_nLightBox);
		GetDlgItem(IDC_STA_LIGHTBOXV)->SetWindowText(tem_strValue);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 19, m_nLightBox);
	} 
	else
	{
		tem_strValue.Format(_T("%d"), m_nLightBox);
		GetDlgItem(IDC_STA_LIGHTBOXV)->SetWindowText(tem_strValue);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 17, m_nLightBox);
	}

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_LIGHTBOXV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	m_nLastLightBox = m_nLightBox;
	
	*pResult = 0;
}


//----------------------------------------------------------------------------------------------
void CUDSTWO::OnBnClickedBtnOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	//1、判断Edit控件是否为NULL
	UpdateData(TRUE);
	if (m_editTemnameV.IsEmpty())
	{
		MessageBox(m_vcTab2Lge[6], m_vcTipsLge[0], MB_OK);
		return;
	}

	//2、判断是否包含非法字符
	if (m_editTemnameV.Find('/')>=0 || m_editTemnameV.Find('\\')>=0 || m_editTemnameV.Find('|')>=0 ||
		m_editTemnameV.Find(':')>=0 || m_editTemnameV.Find('\?')>=0 || m_editTemnameV.Find('\"')>=0 ||
		m_editTemnameV.Find('*')>=0 || m_editTemnameV.Find('<')>=0 || m_editTemnameV.Find('<')>=0)
	{
		MessageBox(m_vcTab2Lge[5], m_vcTipsLge[0], MB_OK);
		return;
	}

	//3、判断是否与已存在模板重名
	CString  tem_strTemName = m_editTemnameV;
	tem_strTemName += _T(".xml");
	Self_FindAllTem(m_strXmlDoc);
	std::vector<CString>::iterator   item;
	for (item=m_vcXmlName.begin(); item!=m_vcXmlName.end(); item++)
	{
		if (*item == tem_strTemName)
		{
			if (IDOK != MessageBox(m_vcTab2Lge[4], _T("紫图UDS"), MB_OKCANCEL))
			{
				return;
			} 
		}
	}

	//4、将模板信息导入到xml文件
	int	ID_SLD[17][4]={{IDC_STA_IRIS, IDC_SLIDER_IRIS, IDC_STA_IRISV, IDC_CHK_IRIS}, {IDC_STA_BBRIGHT, IDC_SLIDER_BBRIGHT, IDC_STA_BBRIGHTV, IDC_CHK_BBRIGHT}, {IDC_STA_EXPOS, IDC_SLIDER_EXPOS, IDC_STA_EXPOSV, IDC_CHK_EXPOS},
	{IDC_STA_FOCUS, IDC_SLIDER_FOCUS, IDC_STA_FOCUSV, IDC_CHK_FOCUS}, {IDC_STA_GAMA, IDC_SLIDER_GAMA, IDC_STA_GAMAV, IDC_CHK_GAMA}, {IDC_STA_GAIN, IDC_SLIDER_GAIN, IDC_STA_GAINV, IDC_CHK_GAIN}, 
	{IDC_STA_HUE, IDC_SLIDER_HUE, IDC_STA_HUEV, IDC_CHK_HUE}, {IDC_STA_FULLVIEW, IDC_SLIDER_FULLVIEW, IDC_STA_PANV, IDC_CHK_FULLVIEW}, {IDC_STA_ROLL, IDC_SLIDER_ROLL, IDC_STA_ROLLV, IDC_CHK_ROLL}, 
	{IDC_STA_SLOP, IDC_SLIDER_SLOP, IDC_STA_SLOPV, IDC_CHK_SLOP}, {IDC_STA_ZOOM, IDC_SLIDER_ZOOM, IDC_STA_ZOOMV, IDC_CHK_ZOOM}, {IDC_STA_BCONTRAST, IDC_SLIDER_BCONTRAST, IDC_STA_BCONTRASTV, IDC_CHK_BCONTRAST}, 
	{IDC_STA_CLEAR, IDC_SLIDER_CLEAR, IDC_STA_CLEARV, IDC_CHK_CLEAR}, {IDC_STA_SATURE, IDC_SLIDER_SATURE, IDC_STA_SATURAV, IDC_CHK_SATURE}, {IDC_STA_WHITEB, IDC_SLIDER_WHITEB, IDC_STA_WBV, IDC_CHK_WHITEB}, 
	{IDC_STA_BACKLIGHT, IDC_SLIDER_BACKLIGHT, IDC_STA_BACKLIGHTV, IDC_CHK_BACKLIGHT}, {IDC_STA_LIGHTBOX, IDC_SLIDER_LIGHTBOX, IDC_STA_LIGHTBOXV, IDC_CHK_BACKLIGHT}};
	
	CString ID_NAME[17]={_T("Iris"), _T("Bright"), _T("Expos"), _T("Focus"), _T("Gama"), _T("Gain"), _T("Hue"), _T("Pan"),
	                     _T("Roll"), _T("Tilt"), _T("Zoom"), _T("Contrast"), _T("Sharp"), _T("Satura"), _T("WhiteBlance"), _T("BackLight"), _T("LightBox")};
	TiXmlDocument       tem_xmlDoc;

	TiXmlDeclaration*   tem_xmlDec = new TiXmlDeclaration("1.0", "", "");
	tem_xmlDoc.LinkEndChild(tem_xmlDec);

	CStringA     tem_straRootNode(m_editTemnameV);
	const char*  tem_pcRootNode = tem_straRootNode.GetString();

	TiXmlElement*       tem_xmlElt = new TiXmlElement(tem_pcRootNode);
	tem_xmlDoc.LinkEndChild(tem_xmlElt);

	for (int i=0; i<17; i++)
	{
		BOOL tem_BEnabled = GetDlgItem(ID_SLD[i][1])->IsWindowEnabled();
		if (tem_BEnabled)
		{
			CString      tem_strNodeName = ID_NAME[i];
			CStringA     tem_straNodeName(tem_strNodeName);
			const char*  tem_pcNodeName = tem_straNodeName.GetString();

			TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
			tem_xmlElt->LinkEndChild(tem_xmlElent);

			tem_xmlElent->SetAttribute("support", 1);

//			if (BST_CHECKED == IsDlgButtonChecked(ID_SLD[i][3]))
//			{
//				tem_xmlElent->SetAttribute("auto", 1);
//			}
//			else
//			{
				tem_xmlElent->SetAttribute("auto", 0);
//			}

			int   tem_nCurValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetPos();
			tem_xmlElent->SetAttribute("set", tem_nCurValue);

 			int   tem_nMaxValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetRangeMax();
			tem_xmlElent->SetAttribute("max", tem_nMaxValue);

			int   tem_nMinValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetRangeMin();
			tem_xmlElent->SetAttribute("min", tem_nMinValue);
			

		}
		else
		{
			CString      tem_strNodeName = ID_NAME[i];
			CStringA     tem_straNodeName(tem_strNodeName);
			const char*  tem_pcNodeName = tem_straNodeName.GetString();

			TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
			tem_xmlElt->LinkEndChild(tem_xmlElent);

			tem_xmlElent->SetAttribute("support", 0);
			tem_xmlElent->SetAttribute("auto", 0);
			tem_xmlElent->SetAttribute("set", -1);
			tem_xmlElent->SetAttribute("max", -1);
			tem_xmlElent->SetAttribute("min", -1);			
		}
	}
	//保存至xml目录
	CString  tem_strTemPath = m_strXmlDoc;
	tem_strTemPath += _T("\\");
	tem_strTemPath += m_editTemnameV;
	tem_strTemPath += _T(".xml");
	CStringA    tem_straTemPath(tem_strTemPath);
	const char* tem_pcTemPath = tem_straTemPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcTemPath);

	CString   tem_strItemName = m_editTemnameV;
	::WritePrivateProfileString(_T("BaseSet"), _T("Template"), tem_strItemName, m_strIniPath);

	m_editTemnameV = _T("");
	UpdateData(FALSE);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 20, 0);
}


void CUDSTWO::OnBnClickedBtnManage()
{
	// TODO: 在此添加控件通知处理程序代码
//	m_dlgManageTem.DoModal();
	m_dlgManageTem2.DoModal();

}


void CUDSTWO::Self_CreatXML(TEMPLATEINFO* tem)
{

}


int CUDSTWO::Self_FindAllTem(CString docpath)
{
	m_vcXmlName.clear();
	m_vcXmlPath.clear();
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
					strFilePath = docpath + _T("\\") + strFileName;
					m_vcXmlPath.push_back(strFilePath);
					strFileName = strFileName.Mid(0, nIndex);
					m_vcXmlName.push_back(strFileName);
				}
			}
		}
	}	
	return tem_nFileCount;
}


void CUDSTWO::Self_UpdateSlider(int index)
{
	CRect  tem_rcRect;
	switch(index)
	{
	case 0:
		//亮度-----------
		if (m_nLastBright != m_nBright)
		{
			m_slidBBright.SetPos(m_nLastBright);
			m_nBright = m_nLastBright;
		}
		break;
	case 1:
		//对比度---------
		if (m_nLastContrast != m_nContrast)
		{
			m_slidBContrast.SetPos(m_nLastContrast);
			m_nContrast = m_nLastContrast;
		}
		break;
	case 2:
		//灯箱-----------
		if (m_nLastLightBox != m_nLightBox)
		{
			m_slidBLightBox.SetPos(m_nLastLightBox);
			m_nLightBox = m_nLastLightBox;
		}
		break;
	case 3:
		//灰阶----------
		if (m_nLastGray != m_nGray)
		{
			m_slidGray.SetPos(m_nLastGray);
			m_nGray = m_nLastGray;
		}
		break;
	case 4:
		//分辨率----------
		if(m_nLastRes != m_conBReslution.GetCurSel())
		{
			m_conBReslution.SetCurSel(m_nLastRes);
		}
		break;
	case 5:
		//图像类型联动----
		if (m_nLastImgType != m_conBFormat.GetCurSel())
		{
			m_conBFormat.SetCurSel(m_nLastImgType);
		}
		break;
	case 6:
		//联动，选中反射稿勾选框
		((CButton*)GetDlgItem(IDC_CHK_BREFLECT))->SetCheck(TRUE);

		m_BEnableSta = FALSE;

		((CButton*)GetDlgItem(IDC_CHK_BHDR))->SetCheck(FALSE);
		GetDlgItem(IDC_CHK_VMERGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_HMERGE)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);	
		GetDlgItem(IDC_SLIDER_LIGHTBOX2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_BDELAY)->EnableWindow(FALSE);	

		
		GetDlgItem(IDC_STA_BMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_LIGHTBOX2)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BDELAY)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
		GetDlgItem(IDC_STA_BVMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BHMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
		break;
	case 7:
		//联动，取消反射稿勾选框
		((CButton*)GetDlgItem(IDC_CHK_BREFLECT))->SetCheck(FALSE);
		break;
	}
}


void CUDSTWO::OnBnClickedBtnFold()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BFold)
	{
		//原为折叠状态
		m_BFold = FALSE;
		::SendMessage(this->m_hWnd, WM_SIZE, 0, 0);
		m_btnFold.Init(IDB_PNG_UP, BTN_IMG_3, BTN_TYPE_NORMAL);

		m_tipInfo.AddTool(GetDlgItem(IDC_BTN_FOLD), m_vcTab2Lge[19]);
	} 
	else
	{
		//原为展开状态
		m_BFold = TRUE;
		::SendMessage(this->m_hWnd, WM_SIZE, 0, 0);
		m_btnFold.Init(IDB_PNG_DOWN, BTN_IMG_3, BTN_TYPE_NORMAL);

		m_tipInfo.AddTool(GetDlgItem(IDC_BTN_FOLD), m_vcTab2Lge[18]);
	}
	
}


void CUDSTWO::Self_HideCtrl(BOOL hide)
{
	if (hide)
	{
		//折叠状态，隐藏控件
//		GetDlgItem(IDC_STA_FOCUS)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_SLIDER_FOCUS)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_STA_FOCUSV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_IRIS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_IRIS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_IRISV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_HUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_HUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_HUEV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_FULLVIEW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_FULLVIEW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_PANV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_ROLL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_ROLL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_ROLLV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_SLOP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_SLOP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_SLOPV)->ShowWindow(SW_HIDE);

//		GetDlgItem(IDC_STA_ZOOM)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_SLIDER_ZOOM)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_STA_ZOOMV)->ShowWindow(SW_HIDE);

//		GetDlgItem(IDC_STA_SATURE)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_SLIDER_SATURE)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_STA_SATURAV)->ShowWindow(SW_HIDE);

// 		GetDlgItem(IDC_STA_WHITEB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_SLIDER_WHITEB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STA_WBV)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_CHK_WHITEB)->ShowWindow(SW_HIDE);

//		GetDlgItem(IDC_STA_BACKLIGHT)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_SLIDER_BACKLIGHT)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_STA_BACKLIGHTV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_BRES)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_BRES)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_BFORMAT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_BFORMAT)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_STA_HDRLLGT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLD_HDRLLGT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_HDRLLGTV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_HDRLDLY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLID_HDRLDLY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_HDRLDLYV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_HDRLGRY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLID_HDRLGRY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_HDRLGRYV)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHK_HDRLBCK)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_HDRHLGT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLD_HDRHLGT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_HDRHLGTV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_HDRHDLY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLID_HDRHDLY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_HDRHDLYV)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_HDRHGRY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLID_HDRHGRY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_HDRHGRYV)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHK_HDRHBCK)->ShowWindow(SW_HIDE);
		
	}
	else
	{
		//展开状态，显示控件
//		GetDlgItem(IDC_STA_FOCUS)->ShowWindow(SW_NORMAL);
//		GetDlgItem(IDC_SLIDER_FOCUS)->ShowWindow(SW_NORMAL);
//		GetDlgItem(IDC_STA_FOCUSV)->ShowWindow(SW_NORMAL);

// 		GetDlgItem(IDC_STA_IRIS)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_SLIDER_IRIS)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_STA_IRISV)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_HUE)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLIDER_HUE)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_HUEV)->ShowWindow(SW_NORMAL);

// 		GetDlgItem(IDC_STA_FULLVIEW)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_SLIDER_FULLVIEW)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_STA_PANV)->ShowWindow(SW_NORMAL);

// 		GetDlgItem(IDC_STA_ROLL)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_SLIDER_ROLL)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_STA_ROLLV)->ShowWindow(SW_NORMAL);

// 		GetDlgItem(IDC_STA_SLOP)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_SLIDER_SLOP)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_STA_SLOPV)->ShowWindow(SW_NORMAL);

//		GetDlgItem(IDC_STA_ZOOM)->ShowWindow(SW_NORMAL);
//		GetDlgItem(IDC_SLIDER_ZOOM)->ShowWindow(SW_NORMAL);
//		GetDlgItem(IDC_STA_ZOOMV)->ShowWindow(SW_NORMAL);

//		GetDlgItem(IDC_STA_SATURE)->ShowWindow(SW_NORMAL);
//		GetDlgItem(IDC_SLIDER_SATURE)->ShowWindow(SW_NORMAL);
//		GetDlgItem(IDC_STA_SATURAV)->ShowWindow(SW_NORMAL);

// 		GetDlgItem(IDC_STA_WHITEB)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_SLIDER_WHITEB)->ShowWindow(SW_NORMAL);
// 		GetDlgItem(IDC_STA_WBV)->ShowWindow(SW_NORMAL);
//      GetDlgItem(IDC_CHK_WHITEB)->ShowWindow(SW_NORMAL);

//		GetDlgItem(IDC_STA_BACKLIGHT)->ShowWindow(SW_NORMAL);
//		GetDlgItem(IDC_SLIDER_BACKLIGHT)->ShowWindow(SW_NORMAL);
//		GetDlgItem(IDC_STA_BACKLIGHTV)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_BRES)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CMB_BRES)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_BFORMAT)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CMB_BFORMAT)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_HDRLLGT)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLD_HDRLLGT)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_HDRLLGTV)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_HDRLDLY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLID_HDRLDLY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_HDRLDLYV)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_HDRLGRY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLID_HDRLGRY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_HDRLGRYV)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CHK_HDRLBCK)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_HDRHLGT)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLD_HDRHLGT)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_HDRHLGTV)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_HDRHDLY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLID_HDRHDLY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_HDRHDLYV)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_HDRHGRY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLID_HDRHGRY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STA_HDRHGRYV)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CHK_HDRHBCK)->ShowWindow(SW_NORMAL);		
	}

}


afx_msg LRESULT CUDSTWO::OnAddtem(WPARAM wParam, LPARAM lParam)
{
	MessageBox(_T("shoudao"));
	return 0;
}


void CUDSTWO::Self_CreateXml(CString xmlpath)
{
	//4、将模板信息导入到xml文件
	int	ID_SLD[18][4]={{IDC_STA_IRIS, IDC_SLIDER_IRIS, IDC_STA_IRISV, IDC_CHK_IRIS}, {IDC_STA_BBRIGHT, IDC_SLIDER_BBRIGHT, IDC_STA_BBRIGHTV, IDC_CHK_BBRIGHT}, {IDC_STA_EXPOS, IDC_SLIDER_EXPOS, IDC_STA_EXPOSV, IDC_CHK_EXPOS},
	{IDC_STA_FOCUS, IDC_SLIDER_FOCUS, IDC_STA_FOCUSV, IDC_CHK_FOCUS}, {IDC_STA_GAMA, IDC_SLIDER_GAMA, IDC_STA_GAMAV, IDC_CHK_GAMA}, {IDC_STA_GAIN, IDC_SLIDER_GAIN, IDC_STA_GAINV, IDC_CHK_GAIN}, 
	{IDC_STA_HUE, IDC_SLIDER_HUE, IDC_STA_HUEV, IDC_CHK_HUE}, {IDC_STA_FULLVIEW, IDC_SLIDER_FULLVIEW, IDC_STA_PANV, IDC_CHK_FULLVIEW}, {IDC_STA_ROLL, IDC_SLIDER_ROLL, IDC_STA_ROLLV, IDC_CHK_ROLL}, 
	{IDC_STA_SLOP, IDC_SLIDER_SLOP, IDC_STA_SLOPV, IDC_CHK_SLOP}, {IDC_STA_ZOOM, IDC_SLIDER_ZOOM, IDC_STA_ZOOMV, IDC_CHK_ZOOM}, {IDC_STA_BCONTRAST, IDC_SLIDER_BCONTRAST, IDC_STA_BCONTRASTV, IDC_CHK_BCONTRAST}, 
	{IDC_STA_CLEAR, IDC_SLIDER_CLEAR, IDC_STA_CLEARV, IDC_CHK_CLEAR}, {IDC_STA_SATURE, IDC_SLIDER_SATURE, IDC_STA_SATURAV, IDC_CHK_SATURE}, {IDC_STA_WHITEB, IDC_SLIDER_WHITEB, IDC_STA_WBV, IDC_CHK_WHITEB}, 
	{IDC_STA_BACKLIGHT, IDC_SLIDER_BACKLIGHT, IDC_STA_BACKLIGHTV, IDC_CHK_BACKLIGHT}, {IDC_STA_LIGHTBOX, IDC_SLIDER_LIGHTBOX, IDC_STA_LIGHTBOXV, IDC_CHK_BACKLIGHT},  {IDC_STA_CGRAY, IDC_SLIDER_CGRAY, IDC_STA_CGRAYV, 0}};

	CString ID_NAME[18]={_T("Iris"), _T("Bright"), _T("Expos"), _T("Focus"), _T("Gama"), _T("Gain"), _T("Hue"), _T("Pan"), _T("Roll"), _T("Tilt"),
		                 _T("Zoom"), _T("Contrast"), _T("Sharp"), _T("Satura"), _T("WhiteBlance"), _T("BackLight"), _T("LightBox"), _T("GrayScale")};
	TiXmlDocument       tem_xmlDoc;

	TiXmlDeclaration*   tem_xmlDec = new TiXmlDeclaration("1.0", "", "");
	tem_xmlDoc.LinkEndChild(tem_xmlDec);

	CString  tem_strRootNode = _T("uds");
	tem_strRootNode += xmlpath;
	CStringA     tem_straRootNode(tem_strRootNode);
	const char*  tem_pcRootNode = tem_straRootNode.GetString();

	TiXmlElement*       tem_xmlElt = new TiXmlElement(tem_pcRootNode);
	tem_xmlDoc.LinkEndChild(tem_xmlElt);


	for (int i=0; i<18; i++)
	{
		BOOL tem_BEnabled = GetDlgItem(ID_SLD[i][1])->IsWindowEnabled();    //判断ID_SLD[i][0]返回值错误
		if (i==2 || i==14)
		{
			//只有曝光和白平衡有自动选项，因此单独判断
			CString      tem_strNodeName = ID_NAME[i];
			CStringA     tem_straNodeName(tem_strNodeName);
			const char*  tem_pcNodeName = tem_straNodeName.GetString();

			TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
			tem_xmlElt->LinkEndChild(tem_xmlElent);

			tem_xmlElent->SetAttribute("support", 1);

			//判断CheckBox是否勾选
//			if (tem_BEnabled)
			if(BST_CHECKED==IsDlgButtonChecked(ID_SLD[i][3]))
			{
				tem_xmlElent->SetAttribute("auto", 1);
			}
			else
			{
				tem_xmlElent->SetAttribute("auto", 0);
			}
			

			int   tem_nCurValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetPos();
			tem_xmlElent->SetAttribute("set", tem_nCurValue);

			int   tem_nMaxValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetRangeMax();
			tem_xmlElent->SetAttribute("max", tem_nMaxValue);

			int   tem_nMinValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetRangeMin();
			tem_xmlElent->SetAttribute("min", tem_nMinValue);

		}
		else if (i == 15)
		{
			CString      tem_strNodeName = ID_NAME[i];
			CStringA     tem_straNodeName(tem_strNodeName);
			const char*  tem_pcNodeName = tem_straNodeName.GetString();

			TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
			tem_xmlElt->LinkEndChild(tem_xmlElent);
			tem_xmlElent->SetAttribute("support", 1);
			tem_xmlElent->SetAttribute("auto", 0);
			if (m_nBacklight)
			{
				tem_xmlElent->SetAttribute("set", 1);	
			} 
			else
			{
				tem_xmlElent->SetAttribute("set", 0);	
			}
			tem_xmlElent->SetAttribute("max", 0);
			tem_xmlElent->SetAttribute("min", 0);	
		}
		else if (tem_BEnabled)
		{
			CString      tem_strNodeName = ID_NAME[i];
			CStringA     tem_straNodeName(tem_strNodeName);
			const char*  tem_pcNodeName = tem_straNodeName.GetString();

			TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
			tem_xmlElt->LinkEndChild(tem_xmlElent);

			tem_xmlElent->SetAttribute("support", 1);
		
			
			tem_xmlElent->SetAttribute("auto", 0);

			int   tem_nCurValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetPos();
			tem_xmlElent->SetAttribute("set", tem_nCurValue);

			int   tem_nMaxValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetRangeMax();
			tem_xmlElent->SetAttribute("max", tem_nMaxValue);

			int   tem_nMinValue = ((CSliderCtrl*)GetDlgItem(ID_SLD[i][1]))->GetRangeMin();
			tem_xmlElent->SetAttribute("min", tem_nMinValue);
		}
		else
		{
			CString      tem_strNodeName = ID_NAME[i];
			CStringA     tem_straNodeName(tem_strNodeName);
			const char*  tem_pcNodeName = tem_straNodeName.GetString();

			TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
			tem_xmlElt->LinkEndChild(tem_xmlElent);

			tem_xmlElent->SetAttribute("support", 0);
			tem_xmlElent->SetAttribute("auto", 0);
			tem_xmlElent->SetAttribute("set", -1);
			tem_xmlElent->SetAttribute("max", -1);
			tem_xmlElent->SetAttribute("min", -1);			
		}
	}

	
	//判断HDR开关
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_BHDR))
	{
		CString      tem_strNodeName = _T("HDR");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 1);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 0);
		tem_xmlElent->SetAttribute("max", 0);
		tem_xmlElent->SetAttribute("min", 0);	
	} 
	else
	{
		CString      tem_strNodeName = _T("HDR");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 0);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 0);
		tem_xmlElent->SetAttribute("max", 0);
		tem_xmlElent->SetAttribute("min", 0);	
	}

	//判断MergeMode
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HMERGE))
	{
		CString      tem_strNodeName = _T("MergeMode");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 1);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 1);
		tem_xmlElent->SetAttribute("max", 0);
		tem_xmlElent->SetAttribute("min", 0);	
	} 
	else
	{
		CString      tem_strNodeName = _T("MergeMode");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 1);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 2);
		tem_xmlElent->SetAttribute("max", 0);
		tem_xmlElent->SetAttribute("min", 0);	
	}

	//判断LightBox2
	if (GetDlgItem(IDC_SLIDER_LIGHTBOX2)->IsWindowEnabled())
	{
		CString      tem_strNodeName = _T("LightBox2");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 1);
		tem_xmlElent->SetAttribute("auto", 0);

		int   tem_nCurValue = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHTBOX2))->GetPos();
		tem_xmlElent->SetAttribute("set", tem_nCurValue);
		tem_xmlElent->SetAttribute("max", 100);
		tem_xmlElent->SetAttribute("min", 0);
	} 
	else
	{
		CString      tem_strNodeName = _T("LightBox2");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 0);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 0);
		tem_xmlElent->SetAttribute("max", 100);
		tem_xmlElent->SetAttribute("min", 0);
	}
	

	//判断Delay
	if (GetDlgItem(IDC_SLIDER_BDELAY)->IsWindowEnabled())
	{
		CString      tem_strNodeName = _T("Delay");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 1);
		tem_xmlElent->SetAttribute("auto", 0);

		int   tem_nCurValue = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BDELAY))->GetPos();
		tem_xmlElent->SetAttribute("set", tem_nCurValue);
		tem_xmlElent->SetAttribute("max", 100);
		tem_xmlElent->SetAttribute("min", 10);
	} 
	else
	{
		CString      tem_strNodeName = _T("Delay");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 0);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 0);
		tem_xmlElent->SetAttribute("max", 100);
		tem_xmlElent->SetAttribute("min", 10);
	}

	//判断灰阶
	if (GetDlgItem(IDC_SLIDER_BHDRGRAY)->IsWindowEnabled())
	{
		CString      tem_strNodeName = _T("HDRGRAY");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 1);
		tem_xmlElent->SetAttribute("auto", 0);

		int   tem_nCurValue = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_BHDRGRAY))->GetPos();
		tem_xmlElent->SetAttribute("set", tem_nCurValue);
		tem_xmlElent->SetAttribute("max", 17);
		tem_xmlElent->SetAttribute("min", 1);
	} 
	else
	{
		CString      tem_strNodeName = _T("HDRGRAY");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 1);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 11);
		tem_xmlElent->SetAttribute("max", 17);
		tem_xmlElent->SetAttribute("min", 1);
	}


	//判断反射稿开关
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_BREFLECT))
	{
		CString      tem_strNodeName = _T("Doc");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 1);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 0);
		tem_xmlElent->SetAttribute("max", 0);
		tem_xmlElent->SetAttribute("min", 0);	
	} 
	else
	{
		CString      tem_strNodeName = _T("Doc");
		CStringA     tem_straNodeName(tem_strNodeName);
		const char*  tem_pcNodeName = tem_straNodeName.GetString();

		TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
		tem_xmlElt->LinkEndChild(tem_xmlElent);

		tem_xmlElent->SetAttribute("support", 0);
		tem_xmlElent->SetAttribute("auto", 0);
		tem_xmlElent->SetAttribute("set", 0);
		tem_xmlElent->SetAttribute("max", 0);
		tem_xmlElent->SetAttribute("min", 0);	
	}

	//判断分辨率索引
	CString      tem_strNodeName = _T("Res");
	CStringA     tem_straNodeName(tem_strNodeName);
	const char*  tem_pcNodeName = tem_straNodeName.GetString();

	TiXmlElement* tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);

	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);

	int   tem_nCurValue = m_conBReslution.GetCurSel();
	tem_xmlElent->SetAttribute("set", tem_nCurValue);

	tem_xmlElent->SetAttribute("max", 0);
	tem_xmlElent->SetAttribute("min", 0);	


	//判断图像类型索引
	tem_strNodeName = _T("Format");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);

	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);

	tem_nCurValue = m_conBFormat.GetCurSel();
	tem_xmlElent->SetAttribute("set", tem_nCurValue);

	tem_xmlElent->SetAttribute("max", 0);
	tem_xmlElent->SetAttribute("min", 0);

	//判断包围曝光-逆光对比
	tem_strNodeName = _T("HDRBackLgt");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);

	if (m_nHDRBackLgt)
	{
		tem_xmlElent->SetAttribute("set", 1);
	} 
	else
	{
		tem_xmlElent->SetAttribute("set", 0);
	}
	tem_xmlElent->SetAttribute("max", 0);
	tem_xmlElent->SetAttribute("min", 0);

	//HDR_L灯箱
	tem_strNodeName = _T("LQUABGT");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);
	tem_xmlElent->SetAttribute("set", m_nLowLight);
	tem_xmlElent->SetAttribute("max", 100);
	tem_xmlElent->SetAttribute("min", 0);

	//HDR_L灰阶
	tem_strNodeName = _T("LQUAGRY");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);
	tem_xmlElent->SetAttribute("set", m_nLowGray);
	tem_xmlElent->SetAttribute("max", 17);
	tem_xmlElent->SetAttribute("min", 1);

	//HDR_L延时
	tem_strNodeName = _T("LQUADLY");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);
	tem_xmlElent->SetAttribute("set", m_nLowDelay);
	tem_xmlElent->SetAttribute("max", 100);
	tem_xmlElent->SetAttribute("min", 10);

	//HDR_L逆光对比
	tem_strNodeName = _T("LQUABCK");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);
	tem_xmlElent->SetAttribute("set", m_nLowBackLgt);
	tem_xmlElent->SetAttribute("max", 1);
	tem_xmlElent->SetAttribute("min", 0);

	//HDR_H灯箱
	tem_strNodeName = _T("HQUABGT");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);
	tem_xmlElent->SetAttribute("set", m_nHigLight);
	tem_xmlElent->SetAttribute("max", 100);
	tem_xmlElent->SetAttribute("min", 0);

	//HDR_H灰阶
	tem_strNodeName = _T("HQUAGRY");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);
	tem_xmlElent->SetAttribute("set", m_nHigGray);
	tem_xmlElent->SetAttribute("max", 17);
	tem_xmlElent->SetAttribute("min", 1);

	//HDR_H延时
	tem_strNodeName = _T("HQUADLY");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);
	tem_xmlElent->SetAttribute("set", m_nHigDelay);
	tem_xmlElent->SetAttribute("max", 100);
	tem_xmlElent->SetAttribute("min", 10);

	//HDR_H逆光对比
	tem_strNodeName = _T("HQUABCK");
	tem_straNodeName = tem_strNodeName;
	tem_pcNodeName = tem_straNodeName.GetString();

	tem_xmlElent = new TiXmlElement(tem_pcNodeName);
	tem_xmlElt->LinkEndChild(tem_xmlElent);
	tem_xmlElent->SetAttribute("support", 1);
	tem_xmlElent->SetAttribute("auto", 0);
	tem_xmlElent->SetAttribute("set", m_nHigBackLgt);
	tem_xmlElent->SetAttribute("max", 1);
	tem_xmlElent->SetAttribute("min", 0);

	//保存至xml目录
	CString  tem_strTemPath = m_strXmlDoc;
	tem_strTemPath += _T("\\");
	tem_strTemPath += xmlpath;
	tem_strTemPath += _T(".xml");
	CStringA    tem_straTemPath(tem_strTemPath);
	const char* tem_pcTemPath = tem_straTemPath.GetString();
	tem_xmlDoc.SaveFile(tem_pcTemPath);	
}


void CUDSTWO::Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename)
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


void CUDSTWO::OnCustomdrawSliderCgray(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nGray = m_slidGray.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nGray);
	GetDlgItem(IDC_STA_CGRAYV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_CGRAYV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 23, m_nGray);

	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSliderLightbox2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nLightBox2 = m_slidBLightBox2.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nLightBox2);
	GetDlgItem(IDC_STA_LIGHTBOXV2)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_LIGHTBOXV2)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

    ::SendMessage(m_hSubWnd, WM_TEMPLATE, 28, m_nLightBox2);
	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSliderBdelay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nDelay = m_slidDelay.GetPos();

	float tem_fDelay = (float)m_nDelay*1.0/10;
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%.1f"), tem_fDelay);
	GetDlgItem(IDC_STA_DELAYV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;
	GetDlgItem(IDC_STA_DELAYV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 29, m_nDelay);
	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSliderBhdrgray(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nHdrGray = m_slidBHDRGray.GetPos();

	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nHdrGray);
	GetDlgItem(IDC_STA_BHDRGRAYV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;
	GetDlgItem(IDC_STA_BHDRGRAYV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 32, m_nHdrGray);


	*pResult = 0;
}


void CUDSTWO::OnClickedChkBhdr()
{
	// TODO: 在此添加控件通知处理程序代码
	//HDR开关
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_BHDR))
	{
		m_BEnableSta = TRUE;
		((CButton*)GetDlgItem(IDC_CHK_BREFLECT))->SetCheck(FALSE);

		GetDlgItem(IDC_CHK_VMERGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_HMERGE)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(TRUE);	
		GetDlgItem(IDC_SLIDER_LIGHTBOX2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_BDELAY)->EnableWindow(TRUE);	
		GetDlgItem(IDC_SLIDER_BHDRGRAY)->EnableWindow(TRUE);

		GetDlgItem(IDC_CHK_HDRBACKLGT)->EnableWindow(TRUE);

		/*没有这几行代码，static在切换状态时会出现bug*/
		CRect  tem_rcRect;
		GetDlgItem(IDC_STA_BMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_LIGHTBOX2)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BDELAY)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BHDRGRAY)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
		
		GetDlgItem(IDC_STA_BVMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BHMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		//发送消息
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 26, 1);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 30, 0);

	} 
	else
	{
		m_BEnableSta = FALSE;

		GetDlgItem(IDC_CHK_VMERGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_HMERGE)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);	
		GetDlgItem(IDC_SLIDER_LIGHTBOX2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_BDELAY)->EnableWindow(FALSE);   
		GetDlgItem(IDC_SLIDER_BHDRGRAY)->EnableWindow(FALSE); 

		GetDlgItem(IDC_CHK_HDRBACKLGT)->EnableWindow(FALSE);

		CRect  tem_rcRect;
		GetDlgItem(IDC_STA_BMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_LIGHTBOX2)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BDELAY)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BHDRGRAY)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BVMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BHMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		::SendMessage(m_hSubWnd, WM_TEMPLATE, 26, 0);
	}
}


void CUDSTWO::OnClickedChkBreflect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_BREFLECT))
	{
		m_BEnableSta = FALSE;

		((CButton*)GetDlgItem(IDC_CHK_BHDR))->SetCheck(FALSE);
		GetDlgItem(IDC_CHK_VMERGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_HMERGE)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);	
		GetDlgItem(IDC_SLIDER_LIGHTBOX2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_BDELAY)->EnableWindow(FALSE);	
		GetDlgItem(IDC_SLIDER_BHDRGRAY)->EnableWindow(FALSE);	

		GetDlgItem(IDC_CHK_HDRBACKLGT)->EnableWindow(FALSE);

		CRect  tem_rcRect;
		GetDlgItem(IDC_STA_BMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
		
		GetDlgItem(IDC_STA_LIGHTBOX2)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
		
		GetDlgItem(IDC_STA_BDELAY)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BHDRGRAY)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BVMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_BHMERGE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		::SendMessage(m_hSubWnd, WM_TEMPLATE, 26, 0);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 30, 1);
	}
	else
	{
		//取消反射稿，对于tab2不能确定包围曝光是否打开，对于tab1必须制定一种其他状态
		//tab1指定状态为浏览模式
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 30, 0);

	}
}


void CUDSTWO::OnClickedChkVmerge()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_VMERGE))
	{
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 27, 2);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_HMERGE))->SetCheck(TRUE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 27, 1);
	}
}


void CUDSTWO::OnClickedChkHmerge()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HMERGE))
	{
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(FALSE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 27, 1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_VMERGE))->SetCheck(TRUE);
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 27, 2);
	}
}


void CUDSTWO::OnSelchangeCmbBres()
{
	// TODO: 在此添加控件通知处理程序代码
	int tem_nCurSel = m_conBReslution.GetCurSel();
	if (tem_nCurSel == m_nLastRes)
	{
		return;
	}
	::SendMessage(m_hSubWnd, WM_TEMPLATE, 24, tem_nCurSel);

	m_nLastRes = tem_nCurSel;
}


void CUDSTWO::OnSelchangeCmbBformat()
{
	// TODO: 在此添加控件通知处理程序代码
	int tem_nCurSel = m_conBFormat.GetCurSel();
	if (tem_nCurSel == m_nLastImgType)
	{
		return;
	}
	::SendMessage(m_hSubWnd, WM_TEMPLATE, 25, tem_nCurSel);

	m_nLastImgType = tem_nCurSel;
}


void CUDSTWO::OnBnClickedBtnBrecover()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_TEMPLATE, 31, 0);
}

void CUDSTWO::OnClickedChkBacklgt()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_BACKLGT))
	{
		m_nBacklight = 1;
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 16, 1);
	} 
	else
	{	
		m_nBacklight = 0;
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 16, 0);
	}
}


void CUDSTWO::OnClickedChkHdrbacklgt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HDRBACKLGT))
	{
		m_nHDRBackLgt = 1;
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 33, 1);
	} 
	else
	{
		m_nHDRBackLgt = 0;
		::SendMessage(m_hSubWnd, WM_TEMPLATE, 33, 0);
	}
}


void CUDSTWO::OnCustomdrawSldHdrllgt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nLowLight = m_slidHdrLLgt.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nLowLight);
	GetDlgItem(IDC_STA_HDRLLGTV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_HDRLLGTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 34, m_nLowLight);

	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSldHdrhlgt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nHigLight = m_slidHdrHLgt.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nHigLight);
	GetDlgItem(IDC_STA_HDRHLGTV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_HDRHLGTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 38, m_nHigLight);

	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSlidHdrlgry(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nLowGray = m_slidHdrLGry.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nLowGray);
	GetDlgItem(IDC_STA_HDRLGRYV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_HDRLGRYV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 36, m_nLowGray);

	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSlidHdrhgry(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nHigGray = m_slidHdrHGry.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nHigGray);
	GetDlgItem(IDC_STA_HDRHGRYV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_HDRHGRYV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 40, m_nHigGray);

	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSlidHdrldly(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nLowDelay = m_slidHdrLDly.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nLowDelay);
	GetDlgItem(IDC_STA_HDRLDLYV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_HDRLDLYV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 35, m_nLowDelay);

	*pResult = 0;
}


void CUDSTWO::OnCustomdrawSlidHdrhdly(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nHigDelay = m_slidHdrHDly.GetPos();
	CString tem_strValue = _T("");
	tem_strValue.Format(_T("%d"), m_nHigDelay);
	GetDlgItem(IDC_STA_HDRHDLYV)->SetWindowText(tem_strValue);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_HDRHDLYV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	::SendMessage(m_hSubWnd, WM_TEMPLATE, 39, m_nHigDelay);

	*pResult = 0;
}


void CUDSTWO::OnClickedChkHdrlbck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HDRLBCK))
	{
		m_nLowBackLgt = 1;
	} 
	else
	{
		m_nLowBackLgt = 0;
	}
	::SendMessage(m_hSubWnd, WM_TEMPLATE, 37, m_nLowBackLgt);
}


void CUDSTWO::OnClickedChkHdrhbck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HDRHBCK))
	{
		m_nHigBackLgt = 1;
	} 
	else
	{
		m_nHigBackLgt = 0;
	}
	::SendMessage(m_hSubWnd, WM_TEMPLATE, 41, m_nHigBackLgt);
}
