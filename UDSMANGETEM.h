#pragma once
#define WM_TEMPLATE    WM_USER+1002
#define WM_ADDTEM      WM_USER+1006
#include "UDSNEWTEMNAME.h"
#include "UDSInputNewName.h"
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSMANGETEM 对话框

class CUDSMANGETEM : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSMANGETEM)

public:
	CUDSMANGETEM(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSMANGETEM();

// 对话框数据
	enum { IDD = IDD_DLG_MANGETEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd*    m_pSubWnd;
	HWND     m_hSubWnd;
	CWnd*    m_pMainWnd;
	HWND     m_hMainWnd;

	int      m_nSlcIndex;
	

	CString  m_strDocPath;
	CString  m_strNewestTem;    //最新保存的模板，用于模板保存后的选定，可能会有多次保存

	std::vector<CString>  m_vcXmlName;
	std::vector<CString>  m_vcXmlPath;


	CUDSNEWTEMNAME     m_dlgTemName;
	CUDSInputNewName   m_dlgInputName;
	CComboBox m_conManageTem;


	CString    m_strLgeXmlPath;           //语言xml文件路径
	std::vector<CString> m_vcTemMagLge;   //模板管理窗口语言存储vector
	std::vector<CString> m_vcTipsLge;


	afx_msg void OnBnClickedBtnNewte();
	afx_msg void OnBnClickedBtnTemdelete();
	afx_msg void OnBnClickedBtnTemname();
	afx_msg void OnBnClickedBtnDefault();
	afx_msg void OnBnClickedBtnTemoutput();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString Self_GetMyDocument(void);
	int Self_FindAllTems(CString docpath);
	afx_msg void OnSelchangeCmbMangetem();
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
};
