#pragma once
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSInputNewName �Ի���

class CUDSInputNewName : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSInputNewName)

public:
	CUDSInputNewName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSInputNewName();

// �Ի�������
	enum { IDD = IDD_DLG_RENAMETEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_editValue;

	CString    m_strLgeXmlPath;         //����xml�ļ�·��
	std::vector<CString> m_vcNewNameLge;   //Tab1�������Դ洢vector

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnChangeEditInputnewname();
	CString Self_GetMyDocument(void);
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
	
};
