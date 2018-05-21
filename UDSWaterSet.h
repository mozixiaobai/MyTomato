#pragma once
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSWaterSet �Ի���

class CUDSWaterSet : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSWaterSet)

public:
	CUDSWaterSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSWaterSet();

// �Ի�������
	enum { IDD = IDD_DLG_WATERMARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int        m_nRedValue;
	int        m_nGreenValue;
	int        m_nBlueValue;
	int        m_nWaterSite;
	int        m_nWaterSize;
	int        m_nWaterFont;
	int        m_nWaterMode;      //ʱ��ˮӡ

	CString    m_strInipath;
	CString    m_strWaterColor;
	CString    m_strWaterInfo;    //ˮӡ��Ϣ

	CComboBox m_conSite;
	CComboBox m_conSize;
	CComboBox m_conFont;
	CMFCColorButton m_conMFCColor;

	CString    m_strLgeXmlPath;         //����xml�ļ�·��
	std::vector<CString> m_vcWaterLge;   //Tab1�������Դ洢vector

	virtual BOOL OnInitDialog();
	void Self_ReadWaterIni(CString inipath);
	CString Selg_GetMyDocument(void);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_editValue;
	afx_msg void OnClickedChkWatertime();
	afx_msg void OnSelchangeComSite();
	afx_msg void OnSelchangeComSize();
	afx_msg void OnSelchangeComFont();
	afx_msg void OnClickedColorMfcctrl();
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
};
