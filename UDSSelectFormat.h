#pragma once
#include "resource.h"
#include <vector>
#include "tinyxml.h"

using namespace std;

// CUDSSelectFormat 对话框

class CUDSSelectFormat : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSSelectFormat)

public:
	CUDSSelectFormat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSSelectFormat();

// 对话框数据
	enum { IDD = IDD_DLG_SLCFORMAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	BOOL     m_BShowTip;      //是否显示该窗口
	BOOL     m_BSaveFormat;   //保存格式的标记

	CString    m_strLgeXmlPath;         //语言xml文件路径
	std::vector<CString> m_vcFormatLge;   //Tab1窗口语言存储vector

	CString  m_strIniPath;    //ini文件路径
	CString Self_GetMyDocument(void);
	afx_msg void OnClickedChkUsedfmt();
	afx_msg void OnClickedChkNewfmt();
	afx_msg void OnClickedChkNotshow();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
};
