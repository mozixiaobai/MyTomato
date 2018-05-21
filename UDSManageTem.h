#pragma once
#include <vector>


// CUDSManageTem �Ի���

class CUDSManageTem : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSManageTem)

public:
	CUDSManageTem(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSManageTem();

// �Ի�������
	enum { IDD = IDD_DLG_MANAGETEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
