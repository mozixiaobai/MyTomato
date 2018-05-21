#pragma once
#define WM_IMGPROCESS  WM_USER+1003
#include "Uxtheme.h"    //��������GroupBox��������ɫ
#pragma comment(lib, "Uxtheme.lib")
#include "PngButton.h"
#include <vector>
#include "tinyxml.h"

using namespace std;


// CUDSTHREE �Ի���

class CUDSTHREE : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSTHREE)

public:
	CUDSTHREE(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSTHREE();

// �Ի�������
	enum { IDD = IDD_DLG_THREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWnd*    m_pSubWnd;
	HWND     m_hSubWnd;

	int      m_staBrit;
	int      m_staCtst;
	int      m_staSatr;
	float    m_staGama;


	int      m_nBrit;
	int      m_nCtst;
	int      m_nSatr;
	int      m_nGama;

	int     m_nOperation;   //�����룬����ɫ��ƽ��

	ATL::CImage        m_imgBK; 

	COLORREF   m_clrCtrlColor;
	COLORREF   m_clrBackColor;   //���ڱ�����ɫ
	COLORREF   m_clrTextColor; 

	CSliderCtrl m_slidCBright;
	CSliderCtrl m_slidCContrst;
	CSliderCtrl m_slidCGama;
	CSliderCtrl m_slidCSature;

	CString      m_strLgeXmlPath;          //����xml�ļ�·��
	std::vector<CString> m_vcTab3Lge;      //Tab3�������Դ洢vector

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnLrotate();
	afx_msg void OnBnClickedBtnRrotate();
	afx_msg void OnBnClickedBtnRotate180();
	afx_msg void OnBnClickedBtnLmirro();
	afx_msg void OnBnClickedBtnVmirro();
	afx_msg void OnBnClickedBtnRotateself();
	afx_msg void OnBnClickedBtnInvert();
	afx_msg void OnBnClickedBtnSharp();
	afx_msg void OnBnClickedBtnCrop();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnBackout();
	afx_msg void OnBnClickedBtnRest();
	
	
	afx_msg void OnCustomdrawSliderCbri(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderCcontrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderCsature(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderCgama(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnFitscreen();
	afx_msg void OnReleasedcaptureSliderCbri(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnSure();
	afx_msg void OnBnClickedBtnUnsure();
	afx_msg void OnReleasedcaptureSliderCcontrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReleasedcaptureSliderCsature(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReleasedcaptureSliderCgama(NMHDR *pNMHDR, LRESULT *pResult);
	
	BOOL Self_DisableCtrl(int index);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	
	CPngButton m_btnLRotate;
	CPngButton m_btnRRotate;
	CPngButton m_btnHMirro;
	CPngButton m_btnVMirro;
	CPngButton m_btnRotate180;
	CPngButton m_btnRotateSelf;
	CToolTipCtrl   m_tipInfo3; 
	
	CPngButton m_btnReset;
	CPngButton m_btnSave;
	CPngButton m_btnFitScreen;
	CPngButton m_btnBackOut;
	CPngButton m_btnCrop;
	CPngButton m_btnInvert;
	CPngButton m_btnSharp;
	CPngButton m_btnSure;
	CPngButton m_btnUnsure;
	CPngButton m_btnOriSize;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnOrisize();
	
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);
	CString Self_GetMyDocument(void);
	void Self_ResetSlider(int mode);
	afx_msg void OnBnClickedBtnMarkit();


	int          m_nNote;              //��ע��ʾλ�� 0-�رգ�1-���򡢻���ͷ��2-��ע

	int          m_nLineWidth;         //�߿�
	COLORREF     m_clrLineColor;       //��ɫ
	CComboBox    m_conLineWidth;
	CMFCColorButton m_conColor;

	int          m_nFontSize;         //�����С
	CString      m_strFont;           //����
	CString      m_strInfo;           //�����Ϣ
	BOOL         m_BBold;             //�Ӵ�
	BOOL         m_BItalic;           //б��


	afx_msg void OnSelchangeCmbLinewidth();
	afx_msg void OnClickedMfccolorCcolor();
	
	afx_msg void OnBnClickedBtnArrow();
	afx_msg void OnBnClickedBtnPaintself();
	void Self_SetCtrl(int index);
	afx_msg void OnBnClickedBtnCtext();
	CComboBox m_conFont;
	CComboBox m_conFontSize;
	afx_msg void OnSelchangeCmbCfont();
	afx_msg void OnSelchangeCmbCfontsize();
	afx_msg void OnClickedChkCbold();
	afx_msg void OnClickedChkCitalic();
	afx_msg void OnBnClickedBtnCaddtext();
	CPngButton m_btnRetangle;
	CPngButton m_btnArrow;
	CPngButton m_btnText;
	CPngButton m_btnAddText;
	CString m_editInfo;
	afx_msg void OnBnClickedBtnCbackup2();
	CPngButton m_btnBackUp2;
};
