#pragma once
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSNEWTEMNAME �Ի���

class CUDSNEWTEMNAME : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSNEWTEMNAME)

public:
	CUDSNEWTEMNAME(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSNEWTEMNAME();

// �Ի�������
	enum { IDD = IDD_DLG_NEWTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	CString    m_strLgeXmlPath;         //����xml�ļ�·��
	std::vector<CString> m_vcNewLge;   //Tab1�������Դ洢vector

	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditTemname();
	CString m_editValue;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString Self_GetMyDocument(void);
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
};
