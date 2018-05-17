// UDSTHREE.cpp : 实现文件
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSTHREE.h"
#include "afxdialogex.h"


// CUDSTHREE 对话框
extern CString  g_strEditInfo;

IMPLEMENT_DYNAMIC(CUDSTHREE, CDialogEx)

CUDSTHREE::CUDSTHREE(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSTHREE::IDD, pParent)
{

	//  m_staBri = 0;
	//  m_staCtrst = 0;
	m_staBrit = 0;
	m_staCtst = 0;
	//  m_staGama = 0;
	m_staSatr = 0;
	m_staGama = 0.0f;
	m_editInfo = _T("");
}

CUDSTHREE::~CUDSTHREE()
{
}

void CUDSTHREE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_CBRI, m_slidCBright);
	DDX_Control(pDX, IDC_SLIDER_CCONTRAST, m_slidCContrst);
	DDX_Control(pDX, IDC_SLIDER_CGAMA, m_slidCGama);
	DDX_Control(pDX, IDC_SLIDER_CSATURE, m_slidCSature);
	//  DDX_Text(pDX, IDC_STA_CBRI, m_staBri);
	//  DDX_Text(pDX, IDC_STA_CBRIV, m_staCtrst);
	//  DDX_Control(pDX, IDC_STA_CBRIV, m_staBri);
	//  DDX_Control(pDX, IDC_STA_CCONTRASTV, m_staCtst);
	DDX_Text(pDX, IDC_STA_CBRIV, m_staBrit);
	DDX_Text(pDX, IDC_STA_CCONTRASTV, m_staCtst);
	//  DDX_Text(pDX, IDC_STA_CGAMAV, m_staGama);
	DDX_Text(pDX, IDC_STA_CSATUREV, m_staSatr);
	DDX_Text(pDX, IDC_STA_CGAMAV, m_staGama);
	DDX_Control(pDX, IDC_BTN_LROTATE, m_btnLRotate);
	DDX_Control(pDX, IDC_BTN_RROTATE, m_btnRRotate);
	DDX_Control(pDX, IDC_BTN_LMIRRO, m_btnHMirro);
	DDX_Control(pDX, IDC_BTN_VMIRRO, m_btnVMirro);
	DDX_Control(pDX, IDC_BTN_ROTATE180, m_btnRotate180);
	DDX_Control(pDX, IDC_BTN_ROTATESELF, m_btnRotateSelf);
	DDX_Control(pDX, IDC_BTN_REST, m_btnReset);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_FITSCREEN, m_btnFitScreen);
	DDX_Control(pDX, IDC_BTN_BACKOUT, m_btnBackOut);
	DDX_Control(pDX, IDC_BTN_CROP, m_btnCrop);
	DDX_Control(pDX, IDC_BTN_INVERT, m_btnInvert);
	DDX_Control(pDX, IDC_BTN_SHARP, m_btnSharp);
	DDX_Control(pDX, IDC_BTN_SURE, m_btnSure);
	DDX_Control(pDX, IDC_BTN_UNSURE, m_btnUnsure);
	DDX_Control(pDX, IDC_BTN_ORISIZE, m_btnOriSize);
	//  DDX_Control(pDX, IDC_CMB_LINEWIDTH, m_conFont);
	DDX_Control(pDX, IDC_MFCCOLOR_CCOLOR, m_conColor);
	DDX_Control(pDX, IDC_CMB_LINEWIDTH, m_conLineWidth);
	DDX_Control(pDX, IDC_CMB_CFONT, m_conFont);
	DDX_Control(pDX, IDC_CMB_CFONTSIZE, m_conFontSize);
	DDX_Control(pDX, IDC_BTN_MARKIT, m_btnRetangle);
	DDX_Control(pDX, IDC_BTN_ARROW, m_btnArrow);
	DDX_Control(pDX, IDC_BTN_CTEXT, m_btnText);
	DDX_Control(pDX, IDC_BTN_CADDTEXT, m_btnAddText);
	DDX_Text(pDX, IDC_EDIT_CTEXTINFO, m_editInfo);
	DDX_Control(pDX, IDC_BTN_CBACKUP2, m_btnBackUp2);
}


BEGIN_MESSAGE_MAP(CUDSTHREE, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_LROTATE, &CUDSTHREE::OnBnClickedBtnLrotate)
	ON_BN_CLICKED(IDC_BTN_RROTATE, &CUDSTHREE::OnBnClickedBtnRrotate)
	ON_BN_CLICKED(IDC_BTN_ROTATE180, &CUDSTHREE::OnBnClickedBtnRotate180)
	ON_BN_CLICKED(IDC_BTN_LMIRRO, &CUDSTHREE::OnBnClickedBtnLmirro)
	ON_BN_CLICKED(IDC_BTN_VMIRRO, &CUDSTHREE::OnBnClickedBtnVmirro)
	ON_BN_CLICKED(IDC_BTN_ROTATESELF, &CUDSTHREE::OnBnClickedBtnRotateself)
	ON_BN_CLICKED(IDC_BTN_INVERT, &CUDSTHREE::OnBnClickedBtnInvert)
	ON_BN_CLICKED(IDC_BTN_SHARP, &CUDSTHREE::OnBnClickedBtnSharp)
	ON_BN_CLICKED(IDC_BTN_CROP, &CUDSTHREE::OnBnClickedBtnCrop)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CUDSTHREE::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_BACKOUT, &CUDSTHREE::OnBnClickedBtnBackout)
	ON_BN_CLICKED(IDC_BTN_REST, &CUDSTHREE::OnBnClickedBtnRest)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CBRI, &CUDSTHREE::OnCustomdrawSliderCbri)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CCONTRAST, &CUDSTHREE::OnCustomdrawSliderCcontrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CSATURE, &CUDSTHREE::OnCustomdrawSliderCsature)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CGAMA, &CUDSTHREE::OnCustomdrawSliderCgama)
	ON_BN_CLICKED(IDC_BTN_FITSCREEN, &CUDSTHREE::OnBnClickedBtnFitscreen)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CBRI, &CUDSTHREE::OnReleasedcaptureSliderCbri)
//	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_CCONTRAST, &CUDSTHREE::OnOutofmemorySliderCcontrast)
//	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_CGAMA, &CUDSTHREE::OnOutofmemorySliderCgama)
//	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_CSATURE, &CUDSTHREE::OnOutofmemorySliderCsature)
	ON_BN_CLICKED(IDC_BTN_SURE, &CUDSTHREE::OnBnClickedBtnSure)
	ON_BN_CLICKED(IDC_BTN_UNSURE, &CUDSTHREE::OnBnClickedBtnUnsure)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CCONTRAST, &CUDSTHREE::OnReleasedcaptureSliderCcontrast)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CSATURE, &CUDSTHREE::OnReleasedcaptureSliderCsature)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CGAMA, &CUDSTHREE::OnReleasedcaptureSliderCgama)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_ORISIZE, &CUDSTHREE::OnBnClickedBtnOrisize)
	ON_BN_CLICKED(IDC_BTN_MARKIT, &CUDSTHREE::OnBnClickedBtnMarkit)
	ON_CBN_SELCHANGE(IDC_CMB_LINEWIDTH, &CUDSTHREE::OnSelchangeCmbLinewidth)
	ON_BN_CLICKED(IDC_MFCCOLOR_CCOLOR, &CUDSTHREE::OnClickedMfccolorCcolor)
	ON_BN_CLICKED(IDC_BTN_ARROW, &CUDSTHREE::OnBnClickedBtnArrow)
	ON_BN_CLICKED(IDC_BTN_PAINTSELF, &CUDSTHREE::OnBnClickedBtnPaintself)
	ON_BN_CLICKED(IDC_BTN_CTEXT, &CUDSTHREE::OnBnClickedBtnCtext)
	ON_CBN_SELCHANGE(IDC_CMB_CFONT, &CUDSTHREE::OnSelchangeCmbCfont)
	ON_CBN_SELCHANGE(IDC_CMB_CFONTSIZE, &CUDSTHREE::OnSelchangeCmbCfontsize)
	ON_BN_CLICKED(IDC_CHK_CBOLD, &CUDSTHREE::OnClickedChkCbold)
	ON_BN_CLICKED(IDC_CHK_CITALIC, &CUDSTHREE::OnClickedChkCitalic)
	ON_BN_CLICKED(IDC_BTN_CADDTEXT, &CUDSTHREE::OnBnClickedBtnCaddtext)
	ON_BN_CLICKED(IDC_BTN_CBACKUP2, &CUDSTHREE::OnBnClickedBtnCbackup2)
END_MESSAGE_MAP()


// CUDSTHREE 消息处理程序


BOOL CUDSTHREE::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/**************************
	*
	* 1、变量初始化
	* 2、slider ctrl初始化
	* 3、static初始化
	* 4、button
	* 5、界面美化
	* 6、窗口语言初始化
	* 7、标注界面初始化
	* 8、标注参数初始化
	*
	**************************/
	
	/*1、变量初始化*/
	m_pSubWnd = GetParentOwner();
	m_hSubWnd = m_pSubWnd->m_hWnd;
	m_nBrit   = 0;
	m_nCtst   = 0;
	m_nSatr   = 0;
	m_nGama   = 0;
	m_nOperation = 0;

	m_clrCtrlColor  = RGB(72, 77, 91);
	m_clrBackColor  = RGB(72, 77, 91);
	m_clrTextColor  = RGB(255, 255, 255);

	//获取语言xml文件路径
	m_strLgeXmlPath  = Self_GetMyDocument();
	m_strLgeXmlPath += _T("\\UDSXRayData\\");
	m_strLgeXmlPath += _T("language.xml");
	
	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcTab3Lge, _T("Tab3"));

	/*2、slider ctrl初始化*/
	m_slidCBright.SetRange(-100, 100, TRUE);
	m_slidCBright.SetPos(0);
	m_slidCBright.SetPageSize(1);

	m_slidCContrst.SetRange(-100, 100, TRUE);
	m_slidCContrst.SetPos(0);
	m_slidCContrst.SetPageSize(1);

	m_slidCSature.SetRange(-100, 100, TRUE);
	m_slidCSature.SetPos(0);
	m_slidCSature.SetPageSize(1);

	m_slidCGama.SetRange(20, 400, TRUE);
	m_slidCGama.SetPos(100);
	m_slidCGama.SetPageSize(1);

	/*3、static初始化*/
	m_staBrit = 0;
	m_staCtst = 0;
	m_staSatr = 0;
	m_staGama = 0;
	UpdateData(FALSE);

	/*4、button*/
	GetDlgItem(IDC_BTN_SURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(FALSE);

	/*5、界面美化*/
	//a、窗口背景颜色设置
	CDialogEx::SetBackgroundColor(m_clrBackColor);
	LoadPicture(m_imgBK, IDB_PNG_BKBLACK, _T("PNG"));

	m_btnSave.Init(IDB_PNG_SAVE, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnReset.Init(IDB_PNG_RESET, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnBackOut.Init(IDB_PNG_BACKUP, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnFitScreen.Init(IDB_PNG_FITSCEEN, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnOriSize.Init(IDB_PNG_1_1, BTN_IMG_4, BTN_TYPE_NORMAL);
	
	m_btnLRotate.Init(IDB_PNG_LROTATE, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnRRotate.Init(IDB_PNG_RROTATE, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnHMirro.Init(IDB_PNG_HMIRRO, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnVMirro.Init(IDB_PNG_VMIRRO, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnRotate180.Init(IDB_PNG_180ROTATE, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnRotateSelf.Init(IDB_PNG_DIYROTATE, BTN_IMG_4, BTN_TYPE_NORMAL);

	m_btnCrop.Init(IDB_PNG_CROP, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnInvert.Init(IDB_PNG_INVERT, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnSharp.Init(IDB_PNG_SHARP, BTN_IMG_4, BTN_TYPE_NORMAL);

	m_btnSure.Init(IDB_PNG_CANCEL, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnUnsure.Init(IDB_PNG_OK, BTN_IMG_4, BTN_TYPE_NORMAL);

	m_btnRetangle.Init(IDB_PNG_RETANGLE, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnArrow.Init(IDB_PNG_ARROW, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnText.Init(IDB_PNG_T, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnAddText.Init(IDB_PNG_CADD, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnBackUp2.Init(IDB_PNG_BACKUP2, BTN_IMG_4, BTN_TYPE_NORMAL);


	m_tipInfo3.Create(this);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_SAVE), m_vcTab3Lge[4]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_BACKOUT),m_vcTab3Lge[5]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_REST), m_vcTab3Lge[6]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_FITSCREEN), m_vcTab3Lge[7]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_ORISIZE), m_vcTab3Lge[8]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_LROTATE), m_vcTab3Lge[9]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_RROTATE), m_vcTab3Lge[10]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_LMIRRO), m_vcTab3Lge[12]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_VMIRRO), m_vcTab3Lge[13]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_ROTATE180), m_vcTab3Lge[11]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_ROTATESELF), m_vcTab3Lge[14]);

	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_CROP), m_vcTab3Lge[15]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_INVERT), m_vcTab3Lge[16]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_SHARP), m_vcTab3Lge[17]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_SURE), m_vcTab3Lge[18]);
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_UNSURE), m_vcTab3Lge[19]);

	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_MARKIT), _T("矩形框"));
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_ARROW), _T("箭头标注"));
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_CTEXT), _T("添加注释"));
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_CADDTEXT), _T("添加"));
	m_tipInfo3.AddTool(GetDlgItem(IDC_BTN_CBACKUP2), _T("撤销"));

	m_tipInfo3.SetDelayTime(TTDT_INITIAL, 100);
	m_tipInfo3.SetDelayTime(TTDT_AUTOPOP, 5000);
	m_tipInfo3.SetDelayTime(TTDT_RESHOW, 100);
	m_tipInfo3.SetTipTextColor(RGB(255, 255, 255));
	m_tipInfo3.SetTipBkColor(RGB(0, 0, 0));
	m_tipInfo3.Activate(TRUE);

	SetWindowTheme(GetDlgItem(IDC_STA_ADD2)->GetSafeHwnd(), _T(""), _T("")); 
	SetWindowTheme(GetDlgItem(IDC_STA_CADD1)->GetSafeHwnd(), _T(""), _T("")); 
	SetWindowTheme(GetDlgItem(IDC_GRP_CONE3)->GetSafeHwnd(), _T(""), _T("")); 
	SetWindowTheme(GetDlgItem(IDC_GRP_CONE4)->GetSafeHwnd(), _T(""), _T("")); 
	SetWindowTheme(GetDlgItem(IDC_GRP_CNOTE)->GetSafeHwnd(), _T(""), _T(""));

	/*6、窗口语言初始化*/
	GetDlgItem(IDC_STA_ADD2)->SetWindowText(m_vcTab3Lge[0]);
	GetDlgItem(IDC_STA_CADD1)->SetWindowText(m_vcTab3Lge[1]);
	GetDlgItem(IDC_GRP_CONE3)->SetWindowText(m_vcTab3Lge[2]);
	GetDlgItem(IDC_GRP_CONE4)->SetWindowText(m_vcTab3Lge[3]);

	GetDlgItem(IDC_STA_CBRI)->SetWindowText(m_vcTab3Lge[20]);
	GetDlgItem(IDC_STA_CCONTRAST)->SetWindowText(m_vcTab3Lge[21]);
	GetDlgItem(IDC_STA_CGAMA)->SetWindowText(m_vcTab3Lge[22]);

	GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_HIDE);

	/*7、标注界面初始化*/
	Self_SetCtrl(0);
//	GetDlgItem(IDC_STA_LINEWIDTH)->ShowWindow(SW_NORMAL);
//	GetDlgItem(IDC_CMB_LINEWIDTH)->ShowWindow(SW_NORMAL);
//	GetDlgItem(IDC_STA_LINECOLOR)->ShowWindow(SW_NORMAL);
//	GetDlgItem(IDC_MFCCOLOR_CCOLOR)->ShowWindow(SW_NORMAL);

//	GetDlgItem(IDC_STA_CFONT)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_CMB_CFONT)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_STA_CFONTSIZE)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_CMB_CFONTSIZE)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_CHK_CBOLD)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_STA_CTEXT)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_CHK_CITALIC)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_STA_CITALIC)->ShowWindow(SW_HIDE);

	/*8、标注参数初始化*/
	m_nNote      = 0;
	m_nLineWidth = 5;
	m_conLineWidth.InsertString(0, _T("2"));
	m_conLineWidth.InsertString(1, _T("3"));
	m_conLineWidth.InsertString(2, _T("5"));
	m_conLineWidth.InsertString(3, _T("7"));
	m_conLineWidth.InsertString(4, _T("10"));
	m_conLineWidth.InsertString(5, _T("12"));
	m_conLineWidth.InsertString(6, _T("14"));
	m_conLineWidth.InsertString(7, _T("16"));
	m_conLineWidth.InsertString(8, _T("18"));
	m_conLineWidth.InsertString(9, _T("20"));
	m_conLineWidth.InsertString(10, _T("25"));
	m_conLineWidth.InsertString(11, _T("30"));
	m_conLineWidth.SetCurSel(2);

	m_clrLineColor = 255;
	m_conColor.SetColor(m_clrLineColor);
	m_conColor.SetColumnsNumber(3);

	m_nFontSize = 120;
	m_conFontSize.InsertString(0, _T("10"));
	m_conFontSize.InsertString(1, _T("20"));
	m_conFontSize.InsertString(2, _T("30"));
	m_conFontSize.InsertString(3, _T("40"));
	m_conFontSize.InsertString(4, _T("50"));
	m_conFontSize.InsertString(5, _T("70"));
	m_conFontSize.InsertString(6, _T("90"));
	m_conFontSize.InsertString(7, _T("120"));
	m_conFontSize.InsertString(8, _T("150"));
	m_conFontSize.InsertString(9, _T("200"));
	m_conFontSize.SetCurSel(7);

	m_strFont = _T("宋体");
	m_conFont.InsertString(0, _T("Arial"));
	m_conFont.InsertString(1, _T("Calibri"));
	m_conFont.InsertString(2, _T("Times New Roman"));
	m_conFont.InsertString(3, _T("宋体"));
	m_conFont.InsertString(4, _T("楷体"));
	m_conFont.InsertString(5, _T("仿宋"));
	m_conFont.InsertString(6, _T("黑体"));
	m_conFont.InsertString(7, _T("隶书"));
	m_conFont.InsertString(8, _T("微软雅黑"));
	m_conFont.InsertString(9, _T("新宋体"));
	m_conFont.SetCurSel(3);

	m_BBold = FALSE;
	((CButton*)GetDlgItem(IDC_CHK_CBOLD))->SetCheck(m_BBold);

	m_BItalic = FALSE;
	((CButton*)GetDlgItem(IDC_CHK_CITALIC))->SetCheck(m_BItalic);

	m_strInfo = _T("");


	



	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CUDSTHREE::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_tipInfo3.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CUDSTHREE::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID()==IDC_STA_CBRI || pWnd->GetDlgCtrlID()==IDC_STA_CBRIV || pWnd->GetDlgCtrlID()==IDC_STA_CCONTRAST || 
		pWnd->GetDlgCtrlID()==IDC_STA_CCONTRASTV || pWnd->GetDlgCtrlID()==IDC_STA_CGAMA || pWnd->GetDlgCtrlID()==IDC_STA_CGAMAV)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_clrTextColor);
	}

	
	if (m_nNote == 0)
	{
		if (pWnd->GetDlgCtrlID()==IDC_STA_LINECOLOR || pWnd->GetDlgCtrlID()==IDC_STA_LINEWIDTH || pWnd->GetDlgCtrlID()==IDC_STA_CFONTSIZE ||
			pWnd->GetDlgCtrlID()==IDC_STA_CITALIC || pWnd->GetDlgCtrlID()==IDC_STA_CTEXT|| pWnd->GetDlgCtrlID()==IDC_STA_CTEXTINFO ||
			pWnd->GetDlgCtrlID()==IDC_STA_CFONT)
		{
			hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(191, 191, 191));
		}
	}
	else if (m_nNote == 1)
	{
		if (pWnd->GetDlgCtrlID()==IDC_STA_LINECOLOR || pWnd->GetDlgCtrlID()==IDC_STA_LINEWIDTH)
		{
			hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(m_clrTextColor);
		}
		else if (pWnd->GetDlgCtrlID()==IDC_STA_CFONTSIZE || pWnd->GetDlgCtrlID()==IDC_STA_CITALIC || pWnd->GetDlgCtrlID()==IDC_STA_CTEXT|| 
			pWnd->GetDlgCtrlID()==IDC_STA_CTEXTINFO || pWnd->GetDlgCtrlID()==IDC_STA_CFONT)
		{
			hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(191, 191, 191));
		}
	}
	else if (m_nNote == 2)
	{
		if (pWnd->GetDlgCtrlID()==IDC_STA_LINECOLOR || pWnd->GetDlgCtrlID()==IDC_STA_LINEWIDTH || pWnd->GetDlgCtrlID()==IDC_STA_CFONTSIZE ||
			pWnd->GetDlgCtrlID()==IDC_STA_CITALIC || pWnd->GetDlgCtrlID()==IDC_STA_CTEXT|| pWnd->GetDlgCtrlID()==IDC_STA_CTEXTINFO ||
			pWnd->GetDlgCtrlID()==IDC_STA_CFONT)
		{
			hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(m_clrTextColor);
		}
	}
	


	if(pWnd->GetDlgCtrlID()==IDC_SLIDER_CBRI || pWnd->GetDlgCtrlID()==IDC_SLIDER_CCONTRAST || pWnd->GetDlgCtrlID()==IDC_SLIDER_CGAMA)
	{
		return (HBRUSH) CreateSolidBrush(m_clrCtrlColor); 
	}

	if (pWnd->GetDlgCtrlID()==IDC_STA_ADD2 || pWnd->GetDlgCtrlID()==IDC_STA_CADD1 || pWnd->GetDlgCtrlID()==IDC_GRP_CONE3 ||
		pWnd->GetDlgCtrlID()==IDC_GRP_CONE4 || pWnd->GetDlgCtrlID()==IDC_GRP_CNOTE)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CUDSTHREE::OnPaint()
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


void CUDSTHREE::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 0, 0);
}


void CUDSTHREE::OnBnClickedBtnBackout()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 1, 0);
}


void CUDSTHREE::OnBnClickedBtnRest()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 2, 0);
}


void CUDSTHREE::OnBnClickedBtnLrotate()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 3, 0);
}


void CUDSTHREE::OnBnClickedBtnRrotate()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 4, 0);
}


void CUDSTHREE::OnBnClickedBtnRotate180()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 5, 0);
}


void CUDSTHREE::OnBnClickedBtnLmirro()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 6, 0);
}


void CUDSTHREE::OnBnClickedBtnVmirro()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 7, 0);
}


void CUDSTHREE::OnBnClickedBtnRotateself()
{
	// TODO: 在此添加控件通知处理程序代码
//	Self_DisableCtrl(2);    //通过主界面判断是否有图像再进行该函数的调用
	m_nOperation = 8;
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 8, 0);
}


void CUDSTHREE::OnBnClickedBtnInvert()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 9, 0);
}


void CUDSTHREE::OnBnClickedBtnSharp()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 10, 0);
}


void CUDSTHREE::OnBnClickedBtnCrop()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 11, 0);
}


void CUDSTHREE::OnBnClickedBtnFitscreen()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 12, 0);
}


void CUDSTHREE::OnBnClickedBtnSure()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 17, m_nOperation);

	if (m_nOperation == 13 || m_nOperation == 14 || m_nOperation == 16)
	{
		m_slidCBright.SetPos(0);
		m_slidCContrst.SetPos(0);
		m_slidCGama.SetPos(100);
	}
	else if (m_nOperation == 20 || m_nOperation == 21 || m_nOperation == 31)
	{
		m_nNote = 0;
	}

	Self_DisableCtrl(1);
}


void CUDSTHREE::OnBnClickedBtnUnsure()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (m_nOperation == 13 || m_nOperation == 14 || m_nOperation == 16)
	{
		m_slidCBright.SetPos(0);
		m_slidCContrst.SetPos(0);
		m_slidCGama.SetPos(100);
	}
	else if (m_nOperation == 20 || m_nOperation == 21 || m_nOperation == 31)
	{
		m_nNote = 0;
	}
	
	Self_DisableCtrl(1);

	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 18, m_nOperation);
}


void CUDSTHREE::OnCustomdrawSliderCbri(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nBrit   = m_slidCBright.GetPos();
	m_staBrit = m_nBrit;
	UpdateData(FALSE);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_CBRIV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	*pResult = 0;
}


void CUDSTHREE::OnReleasedcaptureSliderCbri(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
//	Self_DisableCtrl(0);

	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 13, m_nBrit);

	m_nOperation = 13;

	

	*pResult = 0;
}


void CUDSTHREE::OnCustomdrawSliderCcontrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nCtst   = m_slidCContrst.GetPos();
	m_staCtst = m_nCtst;
	UpdateData(FALSE);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_CCONTRASTV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	*pResult = 0;
}


void CUDSTHREE::OnReleasedcaptureSliderCcontrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
//	Self_DisableCtrl(0);
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 14, m_nCtst);

	m_nOperation = 14;

	

	*pResult = 0;
}


void CUDSTHREE::OnCustomdrawSliderCsature(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nSatr   = m_slidCSature.GetPos();
	m_staSatr = m_nSatr;
	UpdateData(FALSE);

	*pResult = 0;
}


void CUDSTHREE::OnReleasedcaptureSliderCsature(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}


void CUDSTHREE::OnCustomdrawSliderCgama(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nGama   = m_slidCGama.GetPos();
	m_staGama = (float)m_nGama*1.0/100;
	UpdateData(FALSE);

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_CGAMAV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	*pResult = 0;
}


void CUDSTHREE::OnReleasedcaptureSliderCgama(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
//	Self_DisableCtrl(0);
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 16, m_nGama);

	m_nOperation = 16;

	

	*pResult = 0;
}


BOOL CUDSTHREE::Self_DisableCtrl(int index)
{
	switch(index)
	{
	case 0:
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BACKOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REST)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FITSCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ORISIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ROTATE180)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_VMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ROTATESELF)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CROP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_INVERT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SHARP)->EnableWindow(FALSE);
		m_btnSure.SetFourState();
		GetDlgItem(IDC_BTN_SURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_NORMAL);
		m_btnUnsure.SetFourState();
		GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_NORMAL);
		
		//标注项控件状态
		GetDlgItem(IDC_BTN_MARKIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ARROW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CTEXT)->EnableWindow(FALSE);
		m_nNote = 0;
		Self_SetCtrl(m_nNote);
		break;
	case 1:
		m_btnSave.SetFourState();
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
		m_btnBackOut.SetFourState();
		GetDlgItem(IDC_BTN_BACKOUT)->EnableWindow(TRUE);
		m_btnReset.SetFourState();
		GetDlgItem(IDC_BTN_REST)->EnableWindow(TRUE);
		m_btnFitScreen.SetFourState();
		GetDlgItem(IDC_BTN_FITSCREEN)->EnableWindow(TRUE);
		m_btnOriSize.SetFourState();
		GetDlgItem(IDC_BTN_ORISIZE)->EnableWindow(TRUE);
		m_btnLRotate.SetFourState();
		GetDlgItem(IDC_BTN_LROTATE)->EnableWindow(TRUE);
		m_btnRRotate.SetFourState();
		GetDlgItem(IDC_BTN_RROTATE)->EnableWindow(TRUE);
		m_btnRotate180.SetFourState();
		GetDlgItem(IDC_BTN_ROTATE180)->EnableWindow(TRUE);
		m_btnHMirro.SetFourState();
		GetDlgItem(IDC_BTN_LMIRRO)->EnableWindow(TRUE);
		m_btnVMirro.SetFourState();
		GetDlgItem(IDC_BTN_VMIRRO)->EnableWindow(TRUE);
		m_btnRotateSelf.SetFourState();
		GetDlgItem(IDC_BTN_ROTATESELF)->EnableWindow(TRUE);
		m_btnCrop.SetFourState();
		GetDlgItem(IDC_BTN_CROP)->EnableWindow(TRUE);
		m_btnInvert.SetFourState();
		GetDlgItem(IDC_BTN_INVERT)->EnableWindow(TRUE);
		m_btnSharp.SetFourState();
		GetDlgItem(IDC_BTN_SHARP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_CBRI)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_CCONTRAST)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_CGAMA)->EnableWindow(TRUE);

		//标注项控件状态
		m_btnRetangle.SetFourState();
		GetDlgItem(IDC_BTN_MARKIT)->EnableWindow(TRUE);
		m_btnArrow.SetFourState();
		GetDlgItem(IDC_BTN_ARROW)->EnableWindow(TRUE);
		m_btnText.SetFourState();
		GetDlgItem(IDC_BTN_CTEXT)->EnableWindow(TRUE);
		m_nNote = 0;
		Self_SetCtrl(m_nNote);
		break;
	case 2:
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BACKOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REST)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FITSCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ORISIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ROTATE180)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_VMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ROTATESELF)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CROP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_INVERT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SHARP)->EnableWindow(FALSE);
		m_btnSure.SetFourState();
		GetDlgItem(IDC_BTN_SURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_NORMAL);
		m_btnUnsure.SetFourState();
		GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_SLIDER_CBRI)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_CCONTRAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_CGAMA)->EnableWindow(FALSE);

		//标注项控件状态
		GetDlgItem(IDC_BTN_MARKIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ARROW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CTEXT)->EnableWindow(FALSE);
		m_nNote = 0;
		Self_SetCtrl(m_nNote);
		break;
	case 3:
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BACKOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REST)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FITSCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ORISIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RROTATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ROTATE180)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_VMIRRO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ROTATESELF)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CROP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_INVERT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SHARP)->EnableWindow(FALSE);
		m_btnSure.SetFourState();
		GetDlgItem(IDC_BTN_SURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_NORMAL);
		m_btnUnsure.SetFourState();
		GetDlgItem(IDC_BTN_UNSURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_SLIDER_CBRI)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_CCONTRAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_CGAMA)->EnableWindow(FALSE);
		break;
	}
	return 0;
}


void CUDSTHREE::OnBnClickedBtnOrisize()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 19, 0);
}


void CUDSTHREE::Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename)
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


CString CUDSTHREE::Self_GetMyDocument(void)
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


void CUDSTHREE::Self_ResetSlider(int mode)
{
	if (mode == 0)
	{
		m_slidCBright.SetPos(0);
	} 
	else if (mode == 1)
	{
		m_slidCContrst.SetPos(0);
	} 
	else
	{
		m_slidCGama.SetPos(100);
	}
	GetDlgItem(IDC_BTN_SURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_UNSURE)->ShowWindow(SW_HIDE);
}


//画框--------------------------------------------
void CUDSTHREE::OnBnClickedBtnMarkit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nNote = 1;
//	Self_SetCtrl(m_nNote);
	m_nOperation = 20;
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 20, 0);

	m_btnBackUp2.SetFourState();
	GetDlgItem(IDC_BTN_CBACKUP2)->EnableWindow(TRUE);
}

//画箭头-------------------------------------------
void CUDSTHREE::OnBnClickedBtnArrow()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nNote = 1;
//	Self_SetCtrl(m_nNote);
	m_nOperation = 21;
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 21, 0);
	m_btnBackUp2.SetFourState();
	GetDlgItem(IDC_BTN_CBACKUP2)->EnableWindow(TRUE);
}

//随意画-------------------------------------------
void CUDSTHREE::OnBnClickedBtnPaintself()
{
	// TODO: 在此添加控件通知处理程序代码
//	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 24, 0);
}


void CUDSTHREE::OnSelchangeCmbLinewidth()
{
	// TODO: 在此添加控件通知处理程序代码
	int      tem_nSlcIndex = m_conLineWidth.GetCurSel();
	CString  tem_strInfo   = _T("");
	m_conLineWidth.GetLBText(tem_nSlcIndex, tem_strInfo);
	m_nLineWidth = _ttoi(tem_strInfo);
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 22, m_nLineWidth);
}

void CUDSTHREE::OnClickedMfccolorCcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	m_clrLineColor = m_conColor.GetColor();
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 23, m_clrLineColor);
}

void CUDSTHREE::Self_SetCtrl(int index)
{
	if (index == 0)
	{
		GetDlgItem(IDC_STA_LINEWIDTH)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CMB_LINEWIDTH)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_CFONT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_CFONT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMB_LINEWIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_CFONT)->EnableWindow(FALSE);
		GetDlgItem(IDC_MFCCOLOR_CCOLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_CFONTSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_CBOLD)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_CITALIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CTEXTINFO)->EnableWindow(FALSE);
		m_btnAddText.SetFourState();
		GetDlgItem(IDC_BTN_CADDTEXT)->EnableWindow(FALSE);	

		GetDlgItem(IDC_BTN_CBACKUP2)->EnableWindow(FALSE);

		CRect  tem_rcRect;
		GetDlgItem(IDC_STA_LINEWIDTH)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_LINECOLOR)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);	

		GetDlgItem(IDC_STA_CFONTSIZE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CTEXT)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CITALIC)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CTEXTINFO)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
	}
	else if (index == 1)
	{
		GetDlgItem(IDC_STA_LINEWIDTH)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CMB_LINEWIDTH)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_STA_CFONT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_CFONT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMB_CFONT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_LINEWIDTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_MFCCOLOR_CCOLOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_CFONTSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_CBOLD)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_CITALIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CTEXTINFO)->EnableWindow(FALSE);
		m_btnAddText.SetFourState();
		GetDlgItem(IDC_BTN_CADDTEXT)->EnableWindow(FALSE);	
//		GetDlgItem(IDC_BTN_CBACKUP2)->EnableWindow(FALSE);

		CRect  tem_rcRect;
		GetDlgItem(IDC_STA_LINEWIDTH)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_LINECOLOR)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);	

		GetDlgItem(IDC_STA_CFONTSIZE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CTEXT)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CITALIC)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CTEXTINFO)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
	}
	else if (index == 2)
	{
		GetDlgItem(IDC_STA_LINEWIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_LINEWIDTH)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STA_CFONT)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_CMB_CFONT)->ShowWindow(SW_NORMAL);

		GetDlgItem(IDC_CMB_LINEWIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_CFONT)->EnableWindow(TRUE);
		GetDlgItem(IDC_MFCCOLOR_CCOLOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_CFONTSIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_CBOLD)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_CITALIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CTEXTINFO)->EnableWindow(TRUE);

		m_btnAddText.SetFourState();
		GetDlgItem(IDC_BTN_CADDTEXT)->EnableWindow(TRUE);

		m_btnBackUp2.SetFourState();
		GetDlgItem(IDC_BTN_CBACKUP2)->EnableWindow(TRUE);

		CRect  tem_rcRect;
		GetDlgItem(IDC_STA_CFONT)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_LINECOLOR)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
		 
		GetDlgItem(IDC_STA_CFONTSIZE)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CTEXT)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CITALIC)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);

		GetDlgItem(IDC_STA_CTEXTINFO)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); 
		InvalidateRect(&tem_rcRect);
	}
}

//添加文本---------------------------------------------
void CUDSTHREE::OnBnClickedBtnCtext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nNote = 2;
//	Self_SetCtrl(m_nNote);
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 25, 0);
}


void CUDSTHREE::OnSelchangeCmbCfont()
{
	// TODO: 在此添加控件通知处理程序代码
	int      tem_nIndex  = m_conFont.GetCurSel();
	CString  tem_strInfo = _T("");
	m_conFont.GetLBText(tem_nIndex, tem_strInfo);
	m_strFont = tem_strInfo;
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 26, tem_nIndex);	
}


void CUDSTHREE::OnSelchangeCmbCfontsize()
{
	// TODO: 在此添加控件通知处理程序代码
	int  tem_nIndex = m_conFontSize.GetCurSel();
	CString  tem_strInfo   = _T("");
	m_conFontSize.GetLBText(tem_nIndex, tem_strInfo);
	m_nFontSize = _ttoi(tem_strInfo);
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 27, m_nFontSize);
}


void CUDSTHREE::OnClickedChkCbold()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_CBOLD))
	{
		m_BBold = TRUE;
	}
	else
	{
		m_BBold = FALSE;
	}
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 28, m_BBold);
}


void CUDSTHREE::OnClickedChkCitalic()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_CITALIC))
	{
		m_BItalic = TRUE;
	}
	else
	{
		m_BItalic = FALSE;
	}
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 29, m_BItalic);
}


void CUDSTHREE::OnBnClickedBtnCaddtext()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取Edit控件文本内容
	UpdateData(TRUE);
	g_strEditInfo = m_editInfo;
	if (g_strEditInfo.IsEmpty())
	{
		MessageBox(_T("请输入标注内容！"), _T("UDS"), MB_OK);
	}
	else
	{
		m_nOperation = 31;
		::SendMessage(m_hSubWnd, WM_IMGPROCESS, 31, m_BItalic);
	}
	
}


void CUDSTHREE::OnBnClickedBtnCbackup2()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hSubWnd, WM_IMGPROCESS, 1, 0);
}
