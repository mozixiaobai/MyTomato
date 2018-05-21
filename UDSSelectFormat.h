#pragma once
#include "resource.h"
#include <vector>
#include "tinyxml.h"

using namespace std;

// CUDSSelectFormat �Ի���

class CUDSSelectFormat : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSSelectFormat)

public:
	CUDSSelectFormat(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSSelectFormat();

// �Ի�������
	enum { IDD = IDD_DLG_SLCFORMAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	BOOL     m_BShowTip;      //�Ƿ���ʾ�ô���
	BOOL     m_BSaveFormat;   //�����ʽ�ı��

	CString    m_strLgeXmlPath;         //����xml�ļ�·��
	std::vector<CString> m_vcFormatLge;   //Tab1�������Դ洢vector

	CString  m_strIniPath;    //ini�ļ�·��
	CString Self_GetMyDocument(void);
	afx_msg void OnClickedChkUsedfmt();
	afx_msg void OnClickedChkNewfmt();
	afx_msg void OnClickedChkNotshow();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
};
