// UDSNameSet.cpp : 实现文件
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSNameSet.h"
#include "afxdialogex.h"



// CUDSNameSet 对话框

IMPLEMENT_DYNAMIC(CUDSNameSet, CDialogEx)

CUDSNameSet::CUDSNameSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSNameSet::IDD, pParent)
{

	m_EditDivide = _T("");
	m_EditPre1 = _T("");
	m_EditPre2 = _T("");
	m_EditPre3 = _T("");
	m_EditBegin = _T("");
}

CUDSNameSet::~CUDSNameSet()
{
}

void CUDSNameSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_DATE, m_conComDate);
	DDX_Control(pDX, IDC_CMB_TIME, m_conComTime);
	DDX_Text(pDX, IDC_EDIT_DIVITION, m_EditDivide);
	DDX_Text(pDX, IDC_EDIT_PRE1, m_EditPre1);
	DDX_Text(pDX, IDC_EDIT_PRE2, m_EditPre2);
	DDX_Text(pDX, IDC_EDIT_PRE3, m_EditPre3);
	DDX_Text(pDX, IDC_EDIT_PRE4, m_EditBegin);
}


BEGIN_MESSAGE_MAP(CUDSNameSet, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_ORDER, &CUDSNameSet::OnClickedChkOrder)
	ON_BN_CLICKED(IDC_CHK_TIME, &CUDSNameSet::OnClickedChkTime)
	ON_BN_CLICKED(IDC_CHK_COSTOM, &CUDSNameSet::OnClickedChkCostom)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CUDSNameSet::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSNameSet::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_PRE1, &CUDSNameSet::OnChangeEditPre1)
	ON_EN_CHANGE(IDC_EDIT_PRE2, &CUDSNameSet::OnChangeEditPre2)
	ON_EN_CHANGE(IDC_EDIT_PRE3, &CUDSNameSet::OnChangeEditPre3)
	ON_BN_CLICKED(IDC_BTN_RESETORDER, &CUDSNameSet::OnBnClickedBtnResetorder)
END_MESSAGE_MAP()


// CUDSNameSet 消息处理程序


BOOL CUDSNameSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*****************************
	* 
	* 1、读取配置文件
	* 2、Checkbox初始化
	* 3、Comobox、Edit初始化
	* 4、初始化
	* 5、界面语言初始化
	*
	*
	*
	*****************************/

	/*0、变量初始化*/
	m_BClear = FALSE;

	/*1、读取配置文件*/
	m_strLgeXmlPath  = Self_GetMyDocument();
	m_strLgeXmlPath += _T("\\UDSXRayData\\language.xml");

	m_strIniPath = Self_GetIniPath();
	Self_ReadIni(m_strIniPath);

	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcNameLge, _T("NamingSet"));

	/*2、CheckBox*/
	switch(m_nNmaeMode)
	{
	case 0:
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(0);
		break;
	case 1:
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(1);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(TRUE);
		Self_SetCtrl(2);
		break;
	default:
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(0);
		break;
	}

	/*3、Comobox和Edit初始化*/
	m_conComDate.ResetContent();
	m_conComDate.InsertString(0, m_vcNameLge[7]);
	m_conComDate.InsertString(1, m_vcNameLge[8]);
	m_conComDate.InsertString(2, m_vcNameLge[9]);
	m_conComDate.InsertString(3, m_vcNameLge[10]);

	m_conComTime.ResetContent();
	m_conComTime.InsertString(0, m_vcNameLge[11]);
	m_conComTime.InsertString(1, m_vcNameLge[12]);
	m_conComTime.InsertString(2, m_vcNameLge[13]);
	m_conComTime.InsertString(3, m_vcNameLge[14]);

	if (m_nNameDate>=0 && m_nNameDate<=3)
	{
		m_conComDate.SetCurSel(m_nNameDate);
	}
	else
	{
		m_conComDate.SetCurSel(0);
	}

	if (m_nNameTime>=0 && m_nNameTime<=3)
	{
		m_conComTime.SetCurSel(m_nNameTime);
	}
	else
	{
		m_conComTime.SetCurSel(0);
	}

	m_EditDivide = m_strNameDivide;
	m_EditPre1   = m_strNamePre1;
	m_EditPre2   = m_strNamePre2;
	m_EditPre3   = m_strNamePre3;
	
	m_EditBegin.Format(_T("%04d"), m_nNameBegin);
	UpdateData(FALSE);

//	CString   tem_strNameRule = _T("注：以下字符不能表示文件名 < > / \\ | : \" * ?");
	CString   tem_strNameRule = m_vcNameLge[6];
//	tem_strNameRule += _T("   < > / \\ | : \" * ? \n\nNote2:The last textbox only can be entered the Numbers! If you input other text, changes will not be saved!");
	tem_strNameRule += _T("   以下字符不能表示文件名 < > / \\ | : \" * ?");
	GetDlgItem(IDC_STA_NAMERULE)->SetWindowText(tem_strNameRule);

	/*5、界面语言初始化*/
	HWND   tem_hWnd;
	tem_hWnd = this->GetSafeHwnd();
	CWnd*  tem_pWnd;
	tem_pWnd = FromHandle(tem_hWnd);
	tem_pWnd->SetWindowText(m_vcNameLge[0]);

	GetDlgItem(IDC_CHK_ORDER)->SetWindowText(m_vcNameLge[1]);
	GetDlgItem(IDC_CHK_TIME)->SetWindowText(m_vcNameLge[2]);
	GetDlgItem(IDC_CHK_COSTOM)->SetWindowText(m_vcNameLge[3]);
	GetDlgItem(IDOK)->SetWindowText(m_vcNameLge[4]);
	GetDlgItem(IDCANCEL)->SetWindowText(m_vcNameLge[5]);
	GetDlgItem(IDC_BTN_RESETORDER)->SetWindowText(m_vcNameLge[15]);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH CUDSNameSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STA_NAMERULE)
	{
		CFont    tem_ftFont;
		tem_ftFont.CreatePointFont(120, _T("楷体"));
		pDC->SelectObject(&tem_ftFont);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


CString CUDSNameSet::Self_GetIniPath(void)
{
	CString        tem_strMyDocument = _T("");
	TCHAR          tem_cMyDocument[MAX_PATH] = {0};
	LPITEMIDLIST   tem_Pid = NULL;
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &tem_Pid);
	if (tem_Pid && SHGetPathFromIDList(tem_Pid, tem_cMyDocument))
	{
		tem_strMyDocument = tem_cMyDocument;
	}
	tem_strMyDocument += _T("\\");
	tem_strMyDocument += _T("UDSXRayData");
	tem_strMyDocument += _T("\\");
	tem_strMyDocument += _T("BaseConfig.ini");
	return tem_strMyDocument;
	
}


void CUDSNameSet::Self_ReadIni(CString inipath)
{
	int      tem_nNameInfo   = 0;
	CString  tem_strNameInfo = _T("");

	::GetPrivateProfileString(_T("BaseSet"), _T("NameMode"), _T("没有找到NameMode信息"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nNameInfo = _ttoi(tem_strNameInfo);
	m_nNmaeMode   = tem_nNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDate"), _T("没有找到NameDate信息"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nNameInfo = _ttoi(tem_strNameInfo);
	m_nNameDate   = tem_nNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameTime"), _T("没有找到NameTime信息"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nNameInfo = _ttoi(tem_strNameInfo);
	m_nNameTime   = tem_nNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameDivide"), _T("没有找到NameDivide信息"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNameDivide = tem_strNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre1"), _T("没有找到NamePre1信息"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre1 = tem_strNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre2"), _T("没有找到NamePre2信息"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre2 = tem_strNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NamePre3"), _T("没有找到NamePre3信息"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strNamePre3 = tem_strNameInfo;
	tem_strNameInfo.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("NameBegin"), _T("没有找到NameBegin信息"), tem_strNameInfo.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nNameInfo = _ttoi(tem_strNameInfo);
	m_nNameBegin   = tem_nNameInfo;
	tem_strNameInfo.ReleaseBuffer();
}


BOOL CUDSNameSet::Self_SetCtrl(int chkindex)
{
	GetDlgItem(IDC_CMB_DATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(FALSE);
	switch(chkindex)
	{
	case 0:
		GetDlgItem(IDC_CMB_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_CMB_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(FALSE);
		break;
	case 2:
		GetDlgItem(IDC_CMB_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(TRUE);
		break;
	default:
		GetDlgItem(IDC_CMB_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DIVITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRE4)->EnableWindow(FALSE);
		break;
	}
	return TRUE;
}


void CUDSNameSet::OnClickedChkOrder()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_ORDER))
	{
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(0);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(1);
	}
}


void CUDSNameSet::OnClickedChkTime()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_TIME))
	{
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(FALSE);
		Self_SetCtrl(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_COSTOM))->SetCheck(TRUE);
		Self_SetCtrl(2);
	}
}


void CUDSNameSet::OnClickedChkCostom()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_COSTOM))
	{
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		Self_SetCtrl(2);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_ORDER))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(FALSE);
		Self_SetCtrl(0);
	}
}



void CUDSNameSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tem_strIniInfo = _T("");

	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_ORDER))
	{
		tem_strIniInfo = _T("0");
	} 
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_TIME))
	{
		tem_strIniInfo = _T("1");
	} 
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_COSTOM))
	{
		tem_strIniInfo = _T("2");
	} 
	else
	{
		tem_strIniInfo = _T("0");
	}
	::WritePrivateProfileString(_T("BaseSet"), _T("NameMode"), tem_strIniInfo, m_strIniPath);


	m_nNameDate = m_conComDate.GetCurSel();
	tem_strIniInfo.Format(_T("%d"), m_nNameDate);
	::WritePrivateProfileString(_T("BaseSet"), _T("NameDate"), tem_strIniInfo, m_strIniPath);

	m_nNameTime = m_conComTime.GetCurSel();
	tem_strIniInfo.Format(_T("%d"), m_nNameTime);
	::WritePrivateProfileString(_T("BaseSet"), _T("NameTime"), tem_strIniInfo, m_strIniPath);
	
	UpdateData(TRUE);

	::WritePrivateProfileString(_T("BaseSet"), _T("NameDivide"), m_EditDivide, m_strIniPath);
	::WritePrivateProfileString(_T("BaseSet"), _T("NamePre1"), m_EditPre1, m_strIniPath);
	::WritePrivateProfileString(_T("BaseSet"), _T("NamePre2"), m_EditPre2, m_strIniPath);
	::WritePrivateProfileString(_T("BaseSet"), _T("NamePre3"), m_EditPre3, m_strIniPath);

	m_nNameBegin = _ttoi(m_EditBegin);
	if (m_nNameBegin>=0 && m_nNameBegin<=9999)
	{
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin"), m_EditBegin, m_strIniPath);
	}
	else
	{
		m_nNameBegin = 0;
		m_EditBegin  = _T("0");
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin"), m_EditBegin, m_strIniPath);
	}

	if (m_BClear)
	{
		//将配置文件次序计数起始位置为1
		::WritePrivateProfileString(_T("BaseSet"), _T("NameBegin2"), _T("1"), m_strIniPath);

	}


	CDialogEx::OnOK();
}


void CUDSNameSet::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

CString CUDSNameSet::Self_GetMyDocument(void)
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


void CUDSNameSet::Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename)
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

void CUDSNameSet::OnChangeEditPre1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_EditPre1.Find('/')>=0 || m_EditPre1.Find('\\')>=0 || m_EditPre1.Find('|')>=0 ||
		m_EditPre1.Find(':')>=0 || m_EditPre1.Find('\?')>=0 || m_EditPre1.Find('\"')>=0 ||
		m_EditPre1.Find('*')>=0 || m_EditPre1.Find('<')>=0 || m_EditPre1.Find('>')>=0)
	{
		int  tem_nEditSize = m_EditPre1.GetLength();
		m_EditPre1 = m_EditPre1.Left(tem_nEditSize-1);

		UpdateData(FALSE);
		if (m_EditPre1.GetLength()>0)
		{
			//设置Edit光标至末尾
			((CEdit*)GetDlgItem(IDC_EDIT_PRE1))->SetSel(m_EditPre1.GetLength(), m_EditPre1.GetLength());
		}
	}
}


void CUDSNameSet::OnChangeEditPre2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_EditPre2.Find('/')>=0 || m_EditPre2.Find('\\')>=0 || m_EditPre2.Find('|')>=0 ||
		m_EditPre2.Find(':')>=0 || m_EditPre2.Find('\?')>=0 || m_EditPre2.Find('\"')>=0 ||
		m_EditPre2.Find('*')>=0 || m_EditPre2.Find('<')>=0 || m_EditPre2.Find('>')>=0)
	{
		int  tem_nEditSize = m_EditPre2.GetLength();
		m_EditPre2 = m_EditPre2.Left(tem_nEditSize-1);

		UpdateData(FALSE);
		if (m_EditPre2.GetLength()>0)
		{
			//设置Edit光标至末尾
			((CEdit*)GetDlgItem(IDC_EDIT_PRE2))->SetSel(m_EditPre2.GetLength(), m_EditPre2.GetLength());
		}
	}
}


void CUDSNameSet::OnChangeEditPre3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_EditPre3.Find('/')>=0 || m_EditPre3.Find('\\')>=0 || m_EditPre3.Find('|')>=0 ||
		m_EditPre3.Find(':')>=0 || m_EditPre3.Find('\?')>=0 || m_EditPre3.Find('\"')>=0 ||
		m_EditPre3.Find('*')>=0 || m_EditPre3.Find('<')>=0 || m_EditPre3.Find('>')>=0)
	{
		int  tem_nEditSize = m_EditPre3.GetLength();
		m_EditPre3 = m_EditPre3.Left(tem_nEditSize-1);

		UpdateData(FALSE);
		if (m_EditPre3.GetLength()>0)
		{
			//设置Edit光标至末尾
			((CEdit*)GetDlgItem(IDC_EDIT_PRE3))->SetSel(m_EditPre3.GetLength(), m_EditPre3.GetLength());
		}
	}
}


void CUDSNameSet::OnBnClickedBtnResetorder()
{
	// TODO: 在此添加控件通知处理程序代码
	m_BClear = TRUE;
}
