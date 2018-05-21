// UDSInputNewName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSInputNewName.h"
#include "afxdialogex.h"

extern CString    g_strNewName;
// CUDSInputNewName �Ի���

IMPLEMENT_DYNAMIC(CUDSInputNewName, CDialogEx)

CUDSInputNewName::CUDSInputNewName(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSInputNewName::IDD, pParent)
{

	m_editValue = _T("");
}

CUDSInputNewName::~CUDSInputNewName()
{
}

void CUDSInputNewName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUTNEWNAME, m_editValue);
}


BEGIN_MESSAGE_MAP(CUDSInputNewName, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUDSInputNewName::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSInputNewName::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_INPUTNEWNAME, &CUDSInputNewName::OnChangeEditInputnewname)
END_MESSAGE_MAP()


// CUDSInputNewName ��Ϣ�������


BOOL CUDSInputNewName::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editValue = _T("");
	UpdateData(FALSE);

	m_strLgeXmlPath  = Self_GetMyDocument();
	m_strLgeXmlPath += _T("\\UDSXRayData\\language.xml");

	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcNewNameLge, _T("RenameTem"));

	HWND   tem_hWnd;
	tem_hWnd = this->GetSafeHwnd();
	CWnd*  tem_pWnd;
	tem_pWnd = FromHandle(tem_hWnd);
	tem_pWnd->SetWindowText(m_vcNewNameLge[0]);

	GetDlgItem(IDC_STA_INPUTNEWNAME)->SetWindowText(m_vcNewNameLge[1]);
	GetDlgItem(IDOK)->SetWindowText(m_vcNewNameLge[2]);
	GetDlgItem(IDCANCEL)->SetWindowText(m_vcNewNameLge[3]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSInputNewName::OnChangeEditInputnewname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����Ƿ�����Ƿ��ַ��������Ƿ��ַ�ֱ������
	UpdateData(TRUE);
	if (m_editValue.Find('/')>=0 || m_editValue.Find('\\')>=0 || m_editValue.Find('|')>=0 ||
		m_editValue.Find(':')>=0 || m_editValue.Find('\?')>=0 || m_editValue.Find('\"')>=0 ||
		m_editValue.Find('*')>=0 || m_editValue.Find('<')>=0 || m_editValue.Find('>')>=0)
	{
		int  tem_nEditSize = m_editValue.GetLength();
		m_editValue = m_editValue.Left(tem_nEditSize-1);
		
		UpdateData(FALSE);
		if (m_editValue.GetLength()>0)
		{
			//����Edit�����ĩβ
			((CEdit*)GetDlgItem(IDC_EDIT_INPUTNEWNAME))->SetSel(m_editValue.GetLength(), m_editValue.GetLength());
		}
		
	}


}


void CUDSInputNewName::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_strNewName = m_editValue;

	CDialogEx::OnOK();
}


void CUDSInputNewName::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_strNewName = _T("");
	CDialogEx::OnCancel();
}



CString CUDSInputNewName::Self_GetMyDocument(void)
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


void CUDSInputNewName::Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename)
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