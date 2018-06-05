#pragma once
#define WM_SCANSET   WM_USER+1001
#include <vector>
#include "tinyxml.h"
#include "Uxtheme.h"    //用于设置GroupBox标题栏颜色
#pragma comment(lib, "Uxtheme.lib")
#include "PngButton.h"
#include "ProgressBarEx.h"

using namespace std;



// CUDSONE 对话框

class CUDSONE : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSONE)

public:
	CUDSONE(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSONE();

// 对话框数据
	enum { IDD = IDD_DLG_ONG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd*      m_pParentWnd;
	HWND       m_hParentWnd;

	int        m_nLastRes;
	int        m_nLastImgType;
	int        m_nLastPreRotate;
	int        m_nLastMergeMode;
	int        m_nLastWaterMark;
	int        m_nLastTemPlate;

	int        m_nLastBright;
	int        m_nLastContrast;
	int        m_nLastLightBox;
	int        m_nLastGrayScal;   //灰阶

	int        m_nViewMode;       //视野模式

	long       m_lLeftSite;       //裁切框坐标
	long       m_lTopSite;
	long       m_lRightSite;
	long       m_lBottomSite;


	BOOL       m_BInitDlg;
	BOOL       m_BDocMode;       //反射稿开关

	ATL::CImage        m_imgBK; 

	CString    m_strIniPath;     //配置文件路径
	CString    m_strTemDoc;      //模板文件夹
	CString    m_strLastTem;     
	CString    m_strSaveDoc;

	COLORREF   m_clrCtrlColor;   //控件背景颜色
	COLORREF   m_clrBackColor;   //窗口背景颜色
	COLORREF   m_clrTextColor;   //字体颜色

	std::vector<CString>   m_vcTemName;
	std::vector<CString>   m_vcTemPath;

	CString    m_strLgeXmlPath;         //语言xml文件路径
	std::vector<CString> m_vcTab1Lge;   //Tab1窗口语言存储vector


	CComboBox m_conTemplate;
	CComboBox m_conResolution;
	CComboBox m_conImgType;

	CRichEditCtrl m_conRichEdit;
	CHARFORMAT    m_fontRichEdit;

	virtual BOOL OnInitDialog();
	CString Self_GetMyDocument(void);
	afx_msg void OnSelchangeCmbTem();
	afx_msg void OnSelchangeCmbRes();
	afx_msg void OnSelchangeCmbType();
	afx_msg void OnRadioR0();
	afx_msg void OnRadioR1();
	afx_msg void OnRadioR2();
	afx_msg void OnRadioR3();
	afx_msg void OnClickedChkHmerge();
	afx_msg void OnClickedChkVmerge();
	afx_msg void OnClickedChkWatermark();
	afx_msg void OnCustomdrawSlidBright(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedChkBri();
	afx_msg void OnCustomdrawSlidContrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedChkContrast();
	void Self_ReadIni(CString inipath);
	int Self_FindTems(CString docpath);
	CSliderCtrl m_slidABright;
	CSliderCtrl m_slidAContrast;
	void Self_SetSlider(CString xmlpath);
	afx_msg void OnBnClickedBtnSlcdoc();
	afx_msg void OnBnClickedBtnScan();
	afx_msg void OnBnClickedBtnWater();
	afx_msg void OnBnClickedBtnName();
	afx_msg void OnBnClickedBtnDefault();
	afx_msg void OnBnClickedBtnEnhence();
	afx_msg void OnBnClickedBtnReduce();
	
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnCustomdrawSlidLight(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slidALightBox;
	void Self_UpdateSlider(int index);
	void Self_SlcNewTem(void);
	afx_msg void OnRadioFreerect();
	afx_msg void OnRadioMaxrect();
	afx_msg void OnRadioPartview();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	afx_msg void OnBnClickedBtnScan2();
	CPngButton     m_btnScan;
	CButton     m_btnSDoc;
	CButton     m_btnWater;
	CButton     m_btnName;
	CPngButton     m_btnSetView;
	CButton     m_btnRecoverTem;
	CToolTipCtrl   m_tipInfo; 
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	void Self_SetCtrlState(void);
	void Self_RefrushTem(CString slgtem);
	
	void Self_ReadLanguageXml(CString xmlpath, vector <CString>& vec, CString nodename);
	CPngButton m_btnHDR;
	CPngButton m_btnLDRCap;
	CSliderCtrl m_slidGray;
	afx_msg void OnCustomdrawSlidAgraylevel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnScanhdr();
	afx_msg void OnBnClickedRadioDocument();
	void Self_ResetUI(CString xmlpath);
	afx_msg void OnClickedChkTrans();
	afx_msg void OnClickedChkDocument();
	afx_msg void OnRadioAuto();
	afx_msg void OnClickedChkHdr();
	afx_msg void OnBnClickedBtnHdrcap();
	CPngButton m_btnHDRCap;
	afx_msg void OnClickedChkAtrantem();
	afx_msg void OnClickedChkAreflcttem();
	std::vector<int> m_vcDisableSTA;   //不可用的static控件
	afx_msg void OnBnClickedBtnLdrcap();
	afx_msg void OnCustomdrawSlidAdfocus(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slidAdjFocus;

	int       m_nFocusValue;       //当前焦点值
	void Self_HideCtrls(int mode);
//	CProgressCtrl m_conProgress;
	CProgressBarEx m_conProgress;
//	CStatic m_staProgress;
	CString m_staProgress;
	afx_msg void OnCustomdrawSlidAcomputer(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slidComputer;
	int         m_nComputer;      //电脑性能指标
	afx_msg void OnClickedChkComputer();
//	CStatic m_staProgressInfo;
	CString m_staProgressInfo;
	CString m_staComputerD;
};
