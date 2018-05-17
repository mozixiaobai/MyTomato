#pragma once
#include <vector>


// CUDSManageTem 对话框

class CUDSManageTem : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSManageTem)

public:
	CUDSManageTem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSManageTem();

// 对话框数据
	enum { IDD = IDD_DLG_MANAGETEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int     m_nRows;
	int     m_nSlcIndex;

	CString m_strDocPath; 

	std::vector<CString>  m_vcXmlName;
	std::vector<CString>  m_vcXmlPath;

	virtual BOOL OnInitDialog();
	CListCtrl m_conListCtrl;
	int Self_FindAllTem(CString docpath);
	CString Self_GetMyDocument(void);
//	afx_msg void OnItemchangedListTem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickListTem(NMHDR *pNMHDR, LRESULT *pResult);
};
