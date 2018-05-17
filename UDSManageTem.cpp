// UDSManageTem.cpp : 实现文件
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSManageTem.h"
#include "afxdialogex.h"


// CUDSManageTem 对话框

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


// CUDSManageTem 消息处理程序


BOOL CUDSManageTem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	dwStyle  |= LVS_EX_GRIDLINES;       //设置网格线

	m_conListCtrl.SetExtendedStyle(dwStyle);
	m_conListCtrl.InsertColumn(0, _T("模板名称"), LVCFMT_CENTER, 150, -1);

	CString    tem_strTemName;
	std::vector<CString>::iterator item_name;
	for (item_name=m_vcXmlName.begin(); item_name!=m_vcXmlName.end(); item_name++)
	{
		tem_strTemName = *item_name;
		m_conListCtrl.InsertItem(m_nRows, tem_strTemName);
		m_nRows++;
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
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
//					if (strFileName != _T("Default.xml"))
					if (strFileName != _T("透射稿默认.xml") && strFileName != _T("反射稿默认.xml"))
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CUDSManageTem::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nSlcIndex!=-1)
	{
		if (IDOK == MessageBox(_T("确定删除？"), _T("紫图UDS"), MB_OKCANCEL))
		{
			DeleteFile(m_vcXmlPath[m_nSlcIndex]);

			m_vcXmlName.erase(m_vcXmlName.begin() + m_nSlcIndex);
			m_vcXmlPath.erase(m_vcXmlPath.begin() + m_nSlcIndex);
			m_conListCtrl.DeleteItem(m_nSlcIndex);
		}
	}
	m_nSlcIndex = -1;
}


