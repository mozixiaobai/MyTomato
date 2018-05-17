#pragma once
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSInputNewName 对话框

class CUDSInputNewName : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSInputNewName)

public:
	CUDSInputNewName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSInputNewName();

// 对话框数据
	enum { IDD = IDD_DLG_RENAMETEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_editValue;

	CString    m_strLgeXmlPath;         //语言xml文件路径
	std::vector<CString> m_vcNewNameLge;   //Tab1窗口语言存储vector

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnChangeEditInputnewname();
	CString Self_GetMyDocument(void);
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
	
};
