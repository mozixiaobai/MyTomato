#pragma once
#define WM_TEMPLATE    WM_USER+1002
#define WM_ADDTEM      WM_USER+1006
#include "UDSNEWTEMNAME.h"
#include "UDSInputNewName.h"
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSMANGETEM �Ի���

class CUDSMANGETEM : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSMANGETEM)

public:
	CUDSMANGETEM(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSMANGETEM();

// �Ի�������
	enum { IDD = IDD_DLG_MANGETEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWnd*    m_pSubWnd;
	HWND     m_hSubWnd;
	CWnd*    m_pMainWnd;
	HWND     m_hMainWnd;

	int      m_nSlcIndex;
	

	CString  m_strDocPath;
	CString  m_strNewestTem;    //���±����ģ�壬����ģ�屣����ѡ�������ܻ��ж�α���

	std::vector<CString>  m_vcXmlName;
	std::vector<CString>  m_vcXmlPath;


	CUDSNEWTEMNAME     m_dlgTemName;
	CUDSInputNewName   m_dlgInputName;
	CComboBox m_conManageTem;


	CString    m_strLgeXmlPath;           //����xml�ļ�·��
	std::vector<CString> m_vcTemMagLge;   //ģ����������Դ洢vector
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
