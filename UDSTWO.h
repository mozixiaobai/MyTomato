#pragma once
#define WM_TEMPLATE   WM_USER+1002
#define WM_ADDTEM     WM_USER+1006


#include "tinyxml.h"
#include "UDSManageTem.h"
#include <string>
#include <vector>
#include "Uxtheme.h"    //用于设置GroupBox标题栏颜色
#pragma comment(lib, "Uxtheme.lib")
#include "PngButton.h"
#include "UDSMANGETEM.h"

using namespace std;


typedef struct tagTEMPLATEINFO
{
	int   iris;        //光圈
	int   bright;      //亮度
	int   expos;       //曝光
	int   focus;       //焦点
	int   gama;        //Gama
	int   gain;        //增益
	int   hue;         //色调
	int   fullview;    //全景
	int   roll;        //滚动
	int   slope;       //倾斜
	int   zoom;        //缩放
	int   contrast;    //对比度
	int   clear;       //清晰度
	int   saturab;     //饱和度
	int   whiteblance; //白平衡
	int   backlight;   //逆光对比
}TEMPLATEINFO;

// CUDSTWO 对话框

class CUDSTWO : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSTWO)

public:
	CUDSTWO(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSTWO();

// 对话框数据
	enum { IDD = IDD_DLG_TWO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd*    m_pSubWnd;
	HWND     m_hSubWnd;

	int      m_nIris;        //光圈
	int      m_nBright;      //亮度
	int      m_nExpos;       //曝光
	int      m_nFocus;       //焦点
	int      m_nGama;        //Gama
	int      m_nGain;        //增益
	int      m_nHue;         //色调
	int      m_nPan;         //全景
	int      m_nRoll;        //滚动
	int      m_nSlope;       //倾斜
	int      m_nZoom;        //缩放
	int      m_nContrast;    //对比度
	int      m_nClear;       //清晰度
	int      m_nSaturab;     //饱和度
	int      m_nWhiteblance; //白平衡
	int      m_nBacklight;   //逆光对比
	int      m_nLightBox;    //灯箱
	int      m_nGray;        //灰阶
	int      m_nLightBox2;   //灰阶灯箱偏移
	int      m_nDelay;       //延时
	int      m_nHdrGray;     //灰阶
	int      m_nHDRBackLgt;  //包围曝光-逆光对比

	int      m_nLastBright;
	int      m_nLastContrast;
	int      m_nLastLightBox;
	int      m_nLastGray;

	int      m_nLastRes;
	int      m_nLastImgType;


	BOOL     m_nInitDlg;    
	BOOL     m_BFold;         //折叠设置

	CString  m_editTemnameV;  //Edit控件变量

	CString  m_strXmlDoc;
	CString  m_strIniPath;

	COLORREF   m_clrCtrlColor;
	COLORREF   m_clrBackColor;   //窗口背景颜色
	COLORREF   m_clrTextColor; 

	std::vector<CString>  m_vcXmlName;
	std::vector<CString>  m_vcXmlPath;

	std::vector<int>      m_vcDisableSta;
	std::vector<int>      m_vcDisableStaV;

	BOOL                  m_BEnableSta;

	TEMPLATEINFO          m_stcTemInfo;

	CUDSManageTem         m_dlgManageTem;
	CUDSMANGETEM          m_dlgManageTem2;

	ATL::CImage        m_imgBK; 

	CString    m_strLgeXmlPath;         //语言xml文件路径
	std::vector<CString> m_vcTab2Lge;   //Tab2窗口语言存储vector
	std::vector<CString> m_vcTipsLge;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOutput();
	void Self_CreatXML(TEMPLATEINFO* tem);
	void Self_ReadXml(CString xmlpath);
	CSliderCtrl m_slidIris;
	CSliderCtrl m_slidBBright;
	CSliderCtrl m_slidExpos;
	CSliderCtrl m_slidFocus;
	CSliderCtrl m_slidGama;
	CSliderCtrl m_slidGain;
	CSliderCtrl m_slidHue;
	CSliderCtrl m_slidPan;
	CSliderCtrl m_slidRoll;
	CSliderCtrl m_slidSlop;
	CSliderCtrl m_slidZoom;
	CSliderCtrl m_slidBContrast;
	CSliderCtrl m_slidClear;
	CSliderCtrl m_slidSatura;
	CSliderCtrl m_slidWhitBlance;
	CSliderCtrl m_slidBackLight;
	afx_msg void OnClickedChkIris();
	afx_msg void OnCustomdrawSliderIris(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedChkBbright();
	afx_msg void OnCustomdrawSliderBbright(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedChkBacklight();
	afx_msg void OnClickedChkBcontrast();
	afx_msg void OnClickedChkClear();
	afx_msg void OnClickedChkExpos();
	afx_msg void OnClickedChkFocus();
	afx_msg void OnClickedChkFullview();
	afx_msg void OnClickedChkGain();
	afx_msg void OnClickedChkGama();
	afx_msg void OnClickedChkHue();
	afx_msg void OnClickedChkRoll();
	afx_msg void OnClickedChkSature();
	afx_msg void OnClickedChkSlop();
	afx_msg void OnClickedChkWhiteb();
	afx_msg void OnClickedChkZoom();
	afx_msg void OnCustomdrawSliderBacklight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderBcontrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderClear(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderExpos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderFocus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderFullview(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderGain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderGama(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderHue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderRoll(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderSature(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderSlop(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderWhiteb(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderZoom(NMHDR *pNMHDR, LRESULT *pResult);
	
	CString Self_GetMyDocument(void);
	int Self_FindAllTem(CString docpath);
	afx_msg void OnBnClickedBtnManage();
	afx_msg void OnCustomdrawSliderLightbox(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slidBLightBox;
	void Self_UpdateSlider(int index);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CToolTipCtrl   m_tipInfo; 
	CButton m_btnOutput;
	CPngButton m_btnFold;
	CButton m_btnManage;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnFold();
	
	void Self_HideCtrl(BOOL hide);
protected:
//	afx_msg LRESULT OnManagetem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddtem(WPARAM wParam, LPARAM lParam);
public:
	void Self_CreateXml(CString xmlpath);
	void Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename);

	int  m_nGap;                //控件垂直间隔
	CButton m_btnBRecover;
	CSliderCtrl m_slidGray;
	afx_msg void OnCustomdrawSliderCgray(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slidBLightBox2;
	CSliderCtrl m_slidDelay;
	afx_msg void OnCustomdrawSliderLightbox2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSliderBdelay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedChkBhdr();
	afx_msg void OnClickedChkBreflect();
	afx_msg void OnClickedChkVmerge();
	afx_msg void OnClickedChkHmerge();
	CComboBox m_conBReslution;
	CComboBox m_conBFormat;
	afx_msg void OnSelchangeCmbBres();
	afx_msg void OnSelchangeCmbBformat();
	afx_msg void OnBnClickedBtnBrecover();
	afx_msg void OnCustomdrawSliderBhdrgray(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slidBHDRGray;
	afx_msg void OnClickedChkBacklgt();
	afx_msg void OnClickedChkHdrbacklgt();

	//HDR---------------------------
	int       m_nLowLight;          //欠曝时灯箱亮度
	int       m_nHigLight;          //过曝时灯箱亮度

	int       m_nLowGray;           //欠曝灰阶
	int       m_nHigGray;           //过曝灰阶

	int       m_nLowDelay;          //欠曝延时
	int       m_nHigDelay;          //过曝延时

	int       m_nLowBackLgt;        //欠曝逆光对比
	int       m_nHigBackLgt;        //过曝逆光对比
	afx_msg void OnCustomdrawSldHdrllgt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSldHdrhlgt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidHdrlgry(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidHdrhgry(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidHdrldly(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawSlidHdrhdly(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedChkHdrlbck();
	afx_msg void OnClickedChkHdrhbck();
	CSliderCtrl m_slidHdrLLgt;
	CSliderCtrl m_slidHdrHLgt;
	CSliderCtrl m_slidHdrLGry;
	CSliderCtrl m_slidHdrHGry;
	CSliderCtrl m_slidHdrLDly;
	CSliderCtrl m_slidHdrHDly;
};
