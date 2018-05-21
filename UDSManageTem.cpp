// UDSManageTem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSManageTem.h"
#include "afxdialogex.h"


// CUDSManageTem �Ի���

IMPLEMENT_DYNAMIC(CUDSManageTem, CDialogEx)

CUDSManageTem::CUDSManageTem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSManageTem::IDD, pParent)
{

}

CUDSManageTem::~CUDSManageTem()
{
}

void CUDSManageTem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TEM, m_conListCtrl);
}


BEGIN_MESSAGE_MAP(CUDSManageTem, CDialogEx)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TEM, &CUDSManageTem::OnItemchangedListTem)
	ON_BN_CLICKED(IDCANCEL, &CUDSManageTem::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CUDSManageTem::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TEM, &CUDSManageTem::OnClickListTem)
END_MESSAGE_MAP()


// CUDSManageTem ��Ϣ�������


BOOL CUDSManageTem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_nRows       = 0;
	m_nSlcIndex   = -1;

	m_strDocPath  = Self_GetMyDocument();
	m_strDocPath += _T("\\");
	m_strDocPath += _T("UDSXRayData");
	m_strDocPath += _T("\\");
	m_strDocPath += _T("xml");

	Self_FindAllTem(m_strDocPath);

	DWORD    dwStyle;
	dwStyle   = LVS_EX_FULLROWSELECT;
	dwStyle  |= LVS_EX_GRIDLINES;       //����������

	m_conListCtrl.SetExtendedStyle(dwStyle);
	m_conListCtrl.InsertColumn(0, _T("ģ������"), LVCFMT_CENTER, 150, -1);

	CString    tem_strTemName;
	std::vector<CString>::iterator item_name;
	for (item_name=m_vcXmlName.begin(); item_name!=m_vcXmlName.end(); item_name++)
	{
		tem_strTemName = *item_name;
		m_conListCtrl.InsertItem(m_nRows, tem_strTemName);
		m_nRows++;
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


CString CUDSManageTem::Self_GetMyDocument(void)
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


int CUDSManageTem::Self_FindAllTem(CString docpath)
{
	m_vcXmlName.clear();
	m_vcXmlPath.clear();
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
//					if (strFileName != _T("Default.xml"))
					if (strFileName != _T("͸���Ĭ��.xml") && strFileName != _T("�����Ĭ��.xml"))
					{
						m_vcXmlName.push_back(strFileName);
						strFilePath = docpath + _T("\\") + strFileName;
						m_vcXmlPath.push_back(strFilePath);
					}
				}
			}
		}
	}	
	return tem_nFileCount;
}


void CUDSManageTem::OnClickListTem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int  tem_nIndex = pNMItemActivate->iItem;
	if (tem_nIndex>=0 && tem_nIndex<m_conListCtrl.GetItemCount())
	{
		m_nSlcIndex = tem_nIndex;
	}
	else
	{
		m_nSlcIndex = -1;
	}

	*pResult = 0;
}


void CUDSManageTem::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CUDSManageTem::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_nSlcIndex!=-1)
	{
		if (IDOK == MessageBox(_T("ȷ��ɾ����"), _T("��ͼUDS"), MB_OKCANCEL))
		{
			DeleteFile(m_vcXmlPath[m_nSlcIndex]);

			m_vcXmlName.erase(m_vcXmlName.begin() + m_nSlcIndex);
			m_vcXmlPath.erase(m_vcXmlPath.begin() + m_nSlcIndex);
			m_conListCtrl.DeleteItem(m_nSlcIndex);
		}
	}
	m_nSlcIndex = -1;
}


