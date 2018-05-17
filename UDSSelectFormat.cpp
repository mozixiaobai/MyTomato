// UDSSelectFormat.cpp : 实现文件
//

#include "stdafx.h"
#include "UDSSelectFormat.h"
#include "afxdialogex.h"


// CUDSSelectFormat 对话框

IMPLEMENT_DYNAMIC(CUDSSelectFormat, CDialogEx)

CUDSSelectFormat::CUDSSelectFormat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSSelectFormat::IDD, pParent)
{

}

CUDSSelectFormat::~CUDSSelectFormat()
{
}

void CUDSSelectFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUDSSelectFormat, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_USEDFMT, &CUDSSelectFormat::OnClickedChkUsedfmt)
	ON_BN_CLICKED(IDC_CHK_NEWFMT, &CUDSSelectFormat::OnClickedChkNewfmt)
	ON_BN_CLICKED(IDC_CHK_NOTSHOW, &CUDSSelectFormat::OnClickedChkNotshow)
	ON_BN_CLICKED(IDOK, &CUDSSelectFormat::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSSelectFormat::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUDSSelectFormat 消息处理程序


BOOL CUDSSelectFormat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//2、获取ini配置文件路径
	m_strIniPath  = Self_GetMyDocument();
	m_strIniPath += _T("\\");
	m_strIniPath += _T("UDSXRayData");
	m_strIniPath += _T("\\");

	m_strLgeXmlPath  = m_strIniPath;
	m_strLgeXmlPath += _T("language.xml");

	m_strIniPath += _T("BaseConfig.ini");

	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcFormatLge, _T("SlcFormat"));

	//3、读取配置项
	int tem_nRead       = 0;
	CString tem_strRead = _T("");
	::GetPrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("没有找到SaveTips信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	if (tem_nRead == 0)
	{
		m_BShowTip = FALSE;
	}
	else
	{
		m_BShowTip = TRUE;
	}
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("没有找到SaveFormat信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead     = _ttoi(tem_strRead);
	if (tem_nRead == 0)
	{
		m_BSaveFormat = FALSE;
	}
	else
	{
		m_BSaveFormat = TRUE;
	}
	tem_strRead.ReleaseBuffer();

	//4、界面初始化
	if (m_BShowTip)
	{
		((CButton*)GetDlgItem(IDC_CHK_NOTSHOW))->SetCheck(FALSE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_NOTSHOW))->SetCheck(TRUE);
	}

	if (m_BSaveFormat)
	{
		((CButton*)GetDlgItem(IDC_CHK_NEWFMT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_USEDFMT))->SetCheck(FALSE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_NEWFMT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_USEDFMT))->SetCheck(TRUE);
	}

	/*5、窗口语言初始化*/
	HWND   tem_hWnd;
	tem_hWnd = this->GetSafeHwnd();
	CWnd*  tem_pWnd;
	tem_pWnd = FromHandle(tem_hWnd);
	tem_pWnd->SetWindowText(m_vcFormatLge[0]);

	GetDlgItem(IDC_CHK_USEDFMT)->SetWindowText(m_vcFormatLge[1]);
	GetDlgItem(IDC_CHK_NEWFMT)->SetWindowText(m_vcFormatLge[2]);
	GetDlgItem(IDC_CHK_NOTSHOW)->SetWindowText(m_vcFormatLge[3]);
	GetDlgItem(IDOK)->SetWindowText(m_vcFormatLge[4]);
	GetDlgItem(IDCANCEL)->SetWindowText(m_vcFormatLge[5]);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


CString CUDSSelectFormat::Self_GetMyDocument(void)
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


void CUDSSelectFormat::OnClickedChkUsedfmt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_USEDFMT))
	{
		((CButton*)GetDlgItem(IDC_CHK_NEWFMT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_USEDFMT))->SetCheck(TRUE);
		m_BSaveFormat = FALSE;
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_NEWFMT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_USEDFMT))->SetCheck(FALSE);
		m_BSaveFormat = TRUE;
	}
}


void CUDSSelectFormat::OnClickedChkNewfmt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED ==IsDlgButtonChecked(IDC_CHK_NEWFMT))
	{
		((CButton*)GetDlgItem(IDC_CHK_NEWFMT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHK_USEDFMT))->SetCheck(FALSE);
		m_BSaveFormat = TRUE;
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_NEWFMT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHK_USEDFMT))->SetCheck(TRUE);
		m_BSaveFormat = FALSE;
	}
}


void CUDSSelectFormat::OnClickedChkNotshow()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_NOTSHOW))
	{
		m_BShowTip = FALSE;
	} 
	else
	{
		m_BShowTip = TRUE;
	}
}


void CUDSSelectFormat::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//写入配置文件
	if (m_BShowTip)
	{
		::WritePrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("1"), m_strIniPath);
	} 
	else
	{
		::WritePrivateProfileString(_T("BaseSet"), _T("SaveTips"), _T("0"), m_strIniPath);
	}

	if (m_BSaveFormat)
	{
		::WritePrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("1"), m_strIniPath);
	} 
	else
	{
		::WritePrivateProfileString(_T("BaseSet"), _T("SaveFormat"), _T("0"), m_strIniPath);
	}
	CDialogEx::OnOK();
}


void CUDSSelectFormat::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CUDSSelectFormat::Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename)
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
