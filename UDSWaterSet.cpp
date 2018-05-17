// UDSWaterSet.cpp : 实现文件
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSWaterSet.h"
#include "afxdialogex.h"


// CUDSWaterSet 对话框

IMPLEMENT_DYNAMIC(CUDSWaterSet, CDialogEx)

CUDSWaterSet::CUDSWaterSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSWaterSet::IDD, pParent)
{

	m_editValue = _T("");
}

CUDSWaterSet::~CUDSWaterSet()
{
}

void CUDSWaterSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_SITE, m_conSite);
	DDX_Control(pDX, IDC_COM_SIZE, m_conSize);
	DDX_Control(pDX, IDC_COM_FONT, m_conFont);
	//  DDX_Control(pDX, IDC_COLOR_MFCCTRL, m_conMfcFont);
	DDX_Control(pDX, IDC_COLOR_MFCCTRL, m_conMFCColor);
	DDX_Text(pDX, IDC_EDIT_INFO, m_editValue);
}


BEGIN_MESSAGE_MAP(CUDSWaterSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUDSWaterSet::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSWaterSet::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHK_WATERTIME, &CUDSWaterSet::OnClickedChkWatertime)
	ON_CBN_SELCHANGE(IDC_COM_SITE, &CUDSWaterSet::OnSelchangeComSite)
	ON_CBN_SELCHANGE(IDC_COM_SIZE, &CUDSWaterSet::OnSelchangeComSize)
	ON_CBN_SELCHANGE(IDC_COM_FONT, &CUDSWaterSet::OnSelchangeComFont)
	ON_BN_CLICKED(IDC_COLOR_MFCCTRL, &CUDSWaterSet::OnClickedColorMfcctrl)
END_MESSAGE_MAP()


// CUDSWaterSet 消息处理程序


BOOL CUDSWaterSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/***************************
	*
	* 1、变量初始化
	* 2、水印位置
	* 3、水印大小
	* 4、水印字体
	* 5、水印颜色
	* 6、读取配置文件
	* 7、设定控件相应值
	* 9、窗口语言初始化
	*
	*
	*
	*
	****************************/

	/*1、变量初始化*/
	m_nRedValue   = 255;
	m_nGreenValue = 0;
	m_nBlueValue  = 0;

	m_strInipath  = Selg_GetMyDocument();
	m_strInipath += _T("\\");
	m_strInipath += _T("UDSXRayData");
	m_strInipath += _T("\\");

	m_strLgeXmlPath  = m_strInipath;
	m_strLgeXmlPath += _T("language.xml");

	m_strInipath += _T("BaseConfig.ini");


	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcWaterLge, _T("WaterSet"));

	/*2、水印位置*/
	m_conSite.InsertString(0, m_vcWaterLge[9]);
	m_conSite.InsertString(1, m_vcWaterLge[10]);
	m_conSite.InsertString(2, m_vcWaterLge[11]);
	m_conSite.InsertString(3, m_vcWaterLge[12]);
	m_conSite.InsertString(4, m_vcWaterLge[13]);

	/*3、水印大小*/
	m_conSize.InsertString(0, _T("10"));
	m_conSize.InsertString(1, _T("20"));
	m_conSize.InsertString(2, _T("30"));
	m_conSize.InsertString(3, _T("40"));
	m_conSize.InsertString(4, _T("50"));
	m_conSize.InsertString(5, _T("70"));
	m_conSize.InsertString(6, _T("90"));
	m_conSize.InsertString(7, _T("120"));
	m_conSize.InsertString(8, _T("150"));
	m_conSize.InsertString(9, _T("200"));

	/*4、水印字体*/
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
	
	

	/*6、读取配置文件*/
	Self_ReadWaterIni(m_strInipath);

	/*7、设置控件默认项*/
	m_conSite.SetCurSel(m_nWaterSite);
	m_conSize.SetCurSel(m_nWaterSize);
	m_conFont.SetCurSel(m_nWaterFont);

	/*5、水印颜色*/
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

	
	COLORREF    tem_clrColor = RGB(m_nRedValue, m_nGreenValue, m_nBlueValue);
	m_conMFCColor.SetColor(tem_clrColor);
	m_conMFCColor.SetColumnsNumber(5);

	m_editValue = m_strWaterInfo;
	UpdateData(FALSE);

	/*8、Checkbox初始化*/
	if (m_nWaterMode==1)
	{
		((CButton*)GetDlgItem(IDC_CHK_WATERTIME))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT_INFO)->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_WATERTIME))->SetCheck(FALSE);
	}

	/*9、窗口语言初始化*/
	HWND   tem_hWnd;
	tem_hWnd = this->GetSafeHwnd();
	CWnd*  tem_pWnd;
	tem_pWnd = FromHandle(tem_hWnd);
	tem_pWnd->SetWindowText(m_vcWaterLge[0]);

	GetDlgItem(IDC_STA_SITEX)->SetWindowText(m_vcWaterLge[1]);
	GetDlgItem(IDC_STA_SIZE)->SetWindowText(m_vcWaterLge[2]);
	GetDlgItem(IDC_STA_FONT)->SetWindowText(m_vcWaterLge[3]);
	GetDlgItem(IDC_STA_WATERCOLOR)->SetWindowText(m_vcWaterLge[4]);
	GetDlgItem(IDC_CHK_WATERTIME)->SetWindowText(m_vcWaterLge[5]);
	GetDlgItem(IDC_STA_WATERINGO)->SetWindowText(m_vcWaterLge[6]);
	GetDlgItem(IDOK)->SetWindowText(m_vcWaterLge[7]);
	GetDlgItem(IDCANCEL)->SetWindowText(m_vcWaterLge[8]);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


CString CUDSWaterSet::Selg_GetMyDocument(void)
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


void CUDSWaterSet::Self_ReadWaterIni(CString inipath)
{	
	int     tem_nRead      = 0;
	CString tem_strRead    =_T("");
	CString tem_strIniPath = inipath;

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


void CUDSWaterSet::OnClickedChkWatertime()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED==IsDlgButtonChecked(IDC_CHK_WATERTIME))
	{
		GetDlgItem(IDC_EDIT_INFO)->EnableWindow(FALSE);
		m_nWaterMode = 1;
	}
	else
	{
		GetDlgItem(IDC_EDIT_INFO)->EnableWindow(TRUE);
		m_nWaterMode = 0;
	}
}


void CUDSWaterSet::OnSelchangeComSite()
{
	// TODO: 在此添加控件通知处理程序代码
	int   tem_nCurSel = m_conSite.GetCurSel();
	m_nWaterSite = tem_nCurSel;
}


void CUDSWaterSet::OnSelchangeComSize()
{
	// TODO: 在此添加控件通知处理程序代码
	int   tem_nCurSel = m_conSize.GetCurSel();
	m_nWaterSize = tem_nCurSel;
}


void CUDSWaterSet::OnSelchangeComFont()
{
	// TODO: 在此添加控件通知处理程序代码
	int    tem_nCurSel = m_conFont.GetCurSel();
	m_nWaterFont = tem_nCurSel;
}


void CUDSWaterSet::OnClickedColorMfcctrl()
{
	// TODO: 在此添加控件通知处理程序代码
	COLORREF  tem_clrCurColor;
	tem_clrCurColor = m_conMFCColor.GetColor();

	m_nRedValue   = GetRValue(tem_clrCurColor);
	m_nGreenValue = GetGValue(tem_clrCurColor);
	m_nBlueValue  = GetBValue(tem_clrCurColor);

	CString  tem_strColor;
	tem_strColor.Format(_T("%d"), m_nRedValue);
	m_strWaterColor  = tem_strColor;
	m_strWaterColor += _T("|");
	
	tem_strColor.Format(_T("%d"), m_nGreenValue);
	m_strWaterColor += tem_strColor;
	m_strWaterColor += _T("|");

	tem_strColor.Format(_T("%d"), m_nBlueValue);
	m_strWaterColor += tem_strColor;
	m_strWaterColor += _T("|");

}


void CUDSWaterSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int      tem_nWrite   = 0;
	CString  tem_strWrite = _T("");

	tem_nWrite = m_nWaterSite;
	tem_strWrite.Format(_T("%d"), tem_nWrite);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterSite"), tem_strWrite, m_strInipath);

	tem_nWrite = m_nWaterSize;
	tem_strWrite.Format(_T("%d"), tem_nWrite);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterSize"), tem_strWrite, m_strInipath);

	tem_nWrite = m_nWaterFont;
	tem_strWrite.Format(_T("%d"), tem_nWrite);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterFont"), tem_strWrite, m_strInipath);

	tem_strWrite = m_strWaterColor;
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterColor"), tem_strWrite, m_strInipath);

	tem_strWrite = m_editValue;
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterInfo"), tem_strWrite, m_strInipath);

	tem_nWrite = m_nWaterMode;
	tem_strWrite.Format(_T("%d"), tem_nWrite);
	::WritePrivateProfileString(_T("BaseSet"), _T("WaterMode"), tem_strWrite, m_strInipath);
	

	CDialogEx::OnOK();
}


void CUDSWaterSet::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CUDSWaterSet::Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename)
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