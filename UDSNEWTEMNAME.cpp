// UDSNEWTEMNAME.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSNEWTEMNAME.h"
#include "afxdialogex.h"

extern CString    g_strNewName;
// CUDSNEWTEMNAME �Ի���

IMPLEMENT_DYNAMIC(CUDSNEWTEMNAME, CDialogEx)

CUDSNEWTEMNAME::CUDSNEWTEMNAME(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSNEWTEMNAME::IDD, pParent)
{

	m_editValue = _T("");
}

CUDSNEWTEMNAME::~CUDSNEWTEMNAME()
{
}

void CUDSNEWTEMNAME::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEMNAME, m_editValue);
}


BEGIN_MESSAGE_MAP(CUDSNEWTEMNAME, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_TEMNAME, &CUDSNEWTEMNAME::OnChangeEditTemname)
	ON_BN_CLICKED(IDOK, &CUDSNEWTEMNAME::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSNEWTEMNAME::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUDSNEWTEMNAME ��Ϣ�������


BOOL CUDSNEWTEMNAME::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editValue = _T("");
	UpdateData(FALSE);

	m_strLgeXmlPath  = Self_GetMyDocument();
	m_strLgeXmlPath += _T("\\UDSXRayData\\language.xml");
	
	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcNewLge, _T("NewTem"));

	HWND   tem_hWnd;
	tem_hWnd = this->GetSafeHwnd();
	CWnd*  tem_pWnd;
	tem_pWnd = FromHandle(tem_hWnd);
	tem_pWnd->SetWindowText(m_vcNewLge[0]);

	GetDlgItem(IDC_STA_TEMNAME)->SetWindowText(m_vcNewLge[1]);
	GetDlgItem(IDOK)->SetWindowText(m_vcNewLge[2]);
	GetDlgItem(IDCANCEL)->SetWindowText(m_vcNewLge[3]);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSNEWTEMNAME::OnChangeEditTemname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_editValue.Find('/')>=0 || m_editValue.Find('\\')>=0 || m_editValue.Find('|')>=0 ||
		m_editValue.Find(':')>=0 || m_editValue.Find('\?')>=0 || m_editValue.Find('\"')>=0 ||
		m_editValue.Find('*')>=0 || m_editValue.Find('<')>=0 || m_editValue.Find('<')>=0)
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


void CUDSNEWTEMNAME::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_strNewName = m_editValue;
	CDialogEx::OnOK();
}


void CUDSNEWTEMNAME::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_strNewName = _T("");
	CDialogEx::OnCancel();
}


CString CUDSNEWTEMNAME::Self_GetMyDocument(void)
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


void CUDSNEWTEMNAME::Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename)
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
