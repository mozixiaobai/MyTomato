#pragma once
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSNEWTEMNAME 对话框

class CUDSNEWTEMNAME : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSNEWTEMNAME)

public:
	CUDSNEWTEMNAME(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSNEWTEMNAME();

// 对话框数据
	enum { IDD = IDD_DLG_NEWTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	CString    m_strLgeXmlPath;         //语言xml文件路径
	std::vector<CString> m_vcNewLge;   //Tab1窗口语言存储vector

	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditTemname();
	CString m_editValue;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString Self_GetMyDocument(void);
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
};
