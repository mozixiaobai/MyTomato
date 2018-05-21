#pragma once
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSNameSet �Ի���

class CUDSNameSet : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSNameSet)

public:
	CUDSNameSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSNameSet();

// �Ի�������
	enum { IDD = IDD_DLG_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int       m_nNmaeMode;
	int       m_nNameDate;
	int       m_nNameTime;
	int       m_nNameBegin;        //�Զ���������ʼλ
	
	BOOL      m_BClear;            //��0��ʶλ

	CString   m_strNameDivide;
	CString   m_strNamePre1;
	CString   m_strNamePre2;
	CString   m_strNamePre3;
	CString   m_strIniPath;

	CString    m_strLgeXmlPath;         //����xml�ļ�·��
	std::vector<CString> m_vcNameLge;   //Tab1�������Դ洢vector

	virtual BOOL OnInitDialog();
	CString Self_GetIniPath(void);
	void Self_ReadIni(CString inipath);
	BOOL Self_SetCtrl(int chkindex);
	CComboBox m_conComDate;
	CComboBox m_conComTime;
	CString m_EditDivide;
	CString m_EditPre1;
	CString m_EditPre2;
	CString m_EditPre3;
	CString m_EditBegin;
	afx_msg void OnClickedChkOrder();
	afx_msg void OnClickedChkTime();
	afx_msg void OnClickedChkCostom();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString Self_GetMyDocument(void);
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
	afx_msg void OnChangeEditPre1();
	afx_msg void OnChangeEditPre2();
	afx_msg void OnChangeEditPre3();
	afx_msg void OnBnClickedBtnResetorder();
};
