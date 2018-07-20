
// XRayViewerv1.0Dlg.h : 头文件
//

#pragma once
#define MOVE_LEFT    1
#define MOVE_RIGHT   2
#define MOVE_TOP     3
#define MOVE_LTOP    4
#define MOVE_RTOP    5
#define MOVE_BOTTOM  6
#define MOVE_LBOTTOM 7
#define MOVE_RBOTTOM 8

#define WM_SCANSET     WM_USER+1001
#define WM_TEMPLATE    WM_USER+1002
#define WM_IMGPROCESS  WM_USER+1003
#define WM_REFRESHIMG  WM_USER+1004
#define WM_THREADOVER  WM_USER+1005



#include "uds_videoctrl1.h"
#include "UDSONE.h"
#include "UDSTWO.h"
#include "UDSTHREE.h"
#include <vector>
#include "tinyxml.h"
#include <string>
#include "UDSNameSet.h"
#include "ximage.h"
#include "IMAGEAndDCM.h"    //JPG转DCM库
#include "Shellapi.h"
#include "pdflib.h"
#include "pdflib.hpp"
#include "UDSWaterSet.h"
#include "cv.h"
#include "opencv2/photo.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "CvvImage.h"      //ATL和cvvImage同时定义了CImage
#include "PngButton.h"
#include "UDSSelectFormat.h"
#include <iostream>
#include "Shellapi.h"
#include <afxtempl.h> //获取电脑配置



using namespace cv;
using namespace std;
using namespace pdflib;

typedef struct tagPROPERTY
{
	CString   m_strName;
	long      m_lSuport;
	long      m_lAuto;
	long      m_lCurValue;
	long      m_lMaxValue;
	long      m_lMinValue;
}PROPERTY;


UINT ThreadDelay(LPVOID lpParam);   //延时线程入口
struct ThreadInfo
{
	HWND     hWnd;     //窗口句柄，用于发送消息
	int      time;     //延迟时间
	int      mode;     //标志位
};

// CXRayViewerv10Dlg 对话框
class CXRayViewerv10Dlg : public CDialogEx
{
// 构造
public:
	CXRayViewerv10Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_XRAYVIEWERV10_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int        m_nMinWidth;        //窗口的最小宽度
	int        m_nMinHeight;       //窗口的最小高度
	int        m_nLastTemplate;    //上次使用模板
	int        m_nLastRes;         //上次使用分辨率
	int        m_nLastImgType;     //上次使用图像类型
	int        m_nLastPreRotate;
	int        m_nLastMergeMode;
	int        m_nLastWaterMark;
	int        m_nNameMode;
	int        m_nNameDate;
	int        m_nNameTime;
	int        m_nNameBegin;
	int        m_nNameBegin2;       //次序命名起始位

	int        m_nLastRelay;      //上次设定的灯光值
	int        m_nLastIris;
	int        m_nLastBright;     //上次的亮度值
	int        m_nLastExpos;
	int        m_nLastFocus;
	int        m_nLastGama;
	int        m_nLastGain;
	int        m_nLastHue;
	int        m_nLastPan;
	int        m_nLastRoll;
	int        m_nLastTilt;
	int        m_nLastZoom;
	int        m_nLastContrst;    //上次的对比度，避免在切换tab时，触发slid发送消息
	int        m_nLastSharp;
	int        m_nLastSatura;
	int        m_nLastWhiteB;
	int        m_nLastBackLight;
	int        m_nLastGray;       //灰阶
	int        m_nImageCount;     //拍照计数
	int        m_nThumbWidth;    
	int        m_nThumbHeight;
	int        m_nRSlcIndex;      //右键选中索引
	int        m_nHDRBackLgt;     //包围曝光小模板中的逆光对比选项

	int        m_nRedValue;
	int        m_nGreenValue;
	int        m_nBlueValue;
	int        m_nWaterMark;
	int        m_nWaterSite;
	int        m_nWaterSize;
	int        m_nWaterFont;
	int        m_nWaterMode;      //时间水印

	int        m_nViewMode;       //视野模式

	int        m_nAngleCount;     //旋转角累计

	int        m_nPrcsIndex;      //当前处理图像的索引

	long       m_lLeftSite;       //裁切框坐标
	long       m_lTopSite;
	long       m_lRightSite;
	long       m_lBottomSite;

	CString    m_strWaterColor;
	CString    m_strWaterInfo;    //水印信息
	CString    m_strTabImg;       //Tab控件切换时的显示图像

	unsigned int m_nStatus;

	long       m_lReturnCode;     //返回码

	BOOL       m_BShowTab;        //是否显示TabCtrl
	BOOL       m_BShowList;       //是否显示ListCtrl
	BOOL       m_BFullScreen;     //是否全屏
	BOOL       m_BShowPicCtrl;    //显示PicCtrl
	BOOL       m_BSpaceDown;      //用于区分按键响应，按下与弹起
	BOOL       m_BEscDown;        //区分键盘响应
	BOOL       m_BClickTab;       //点击Tab控件禁止背景刷新，放置图像被覆盖
	BOOL       m_BOriSize;        //1:1显示
	BOOL       m_BCtrl;           //是否按下Ctrl键

	CString    m_strNameDivide;
	CString    m_strNamePre1;
	CString    m_strNamePre2;
	CString    m_strNamePre3;
	CString    m_strLastTem;      //上次使用模板
	CString    m_strDevPID;       //设备PID_VID信息
	CString    m_strDevVID;
	CString    m_strDevCode;      //设备验证码
	CString    m_strMyCode1;
	CString    m_strConfigDoc;    //配置与模板文件所在的目录
	CString    m_strXmlDoc;       //缓存目录
	CString    m_strThumbDoc;     //缩略图目录
	CString    m_strCVDoc;        //图像处理缓存目录
	CString    m_strIniPath;      //ini配置文件路径
	CString    m_strXmlPath;      //xml配置文件路径
	CString    m_strSaveDoc;      //保存目录
	CString    m_strFileFormat;   //文件格式
	
	CRect           m_rcFullScreen;
	WINDOWPLACEMENT m_stcOldWinPlc;     //结构体中包含了窗口在屏幕上的位置信息
	WINDOWPLACEMENT m_strOcxWinPlc;

	CRect           m_FullScreenRect; 
	CRect           m_rcLastOCX;
	WINDOWPLACEMENT m_OldWndPlacement; // 全屏时对话框的位置属性  
	WINDOWPLACEMENT m_NewWndPlacement; // 全屏后对话框的位置属性  
	

	CMenu          m_ListMenu;

	CUDSONE           m_dlgOne;
	CUDSTWO           m_dlgTwo;
	CUDSTHREE         m_dlgThree;
	CUDSNameSet       m_dlgNameSet;
	CUDSWaterSet      m_dlgWaterSet;
	CUDSSelectFormat  m_dlgSlcFormat;

	std::vector<CString>   m_vcTemName;
	std::vector<CString>   m_vcTemPath;
	std::vector<CString>   m_vcImgName;         //图像名    
	std::vector<CString>   m_vcThumbPath;       //缩略图路径
	std::vector<CString>   m_vcFilePath;       //拍摄文件路径

	ATL::CImage        m_imgBK;                  //背景图像
	CListCtrl       m_conListCtrl;
	CImageList      m_imagelist;

	CUds_videoctrl1 m_conVideoCtrl;
	CTabCtrl        m_conTab;

	CWnd*           pWnd;

	int        m_nLastBrit;          //上次调整的亮度值
	int        m_nLastCtst;          //上次调整的对比度值
	int        m_nLastCGama;

	Mat        m_cvSrcImage;
	Mat        m_cvDstImage;
	Mat        m_cvLastImg;
	Mat        m_cvNextImg;
	Mat        m_cvTipsImg;          //提示信息图像

	CRect      m_rcPicRect;          //Picture控件坐标
	CRect      m_rcImageShow;        //图像显示坐标，相对于Picture控件
	CRect      m_rcImageCrop;        //图像框选坐标，相对于Picture控件
	CRect      m_rcImageRect;        //需要显示的图像rect


	int        m_nDrawX;             //图像缩放后绘制起点
	int        m_nDrawY;
	int        m_nImageBright;       //图像亮度
	int        m_nImageContrast;     //图像对比度
	int        m_nOffsetX, m_nOffsetY;
	int        m_nShowWidth;         //初始化显示宽度
	int        m_nShowHeight;        //初始化显示高度

	float      m_fCurRatio;           //当前缩放比例
	float      m_fPI;                  //圆周率常量

	BOOL      m_BNoSaved;              //是否保存

	CString   m_strFilesPath;
	CString   m_strBufferImgPath;

	std::vector<CString> m_vcHistoryImg;

	BOOL      m_BPaintLine;
	BOOL      m_BSlcRect;
	BOOL      m_BLButtonDown;
	BOOL      m_BSlcRected;          //选区结束标志位
	BOOL      m_BSelectTab;          //图像编辑的部分状态禁止切换标签
	BOOL      m_BLabel;              //标注标记位
	

	CPoint    m_ptOri,  m_ptEnd;
	CPoint    m_ptDragOri, m_ptDragEnd;   //拖动尺寸

	COLORREF  m_clrCtrlColor;
	COLORREF  m_clrBackColor;
	COLORREF  m_clrTextColor;

	BOOL      m_BShowTips;       //是否显示保存对话框
	BOOL      m_BSaveFmt;        //是否保存为原格式

	CString   m_strLangXmlPath;         //语言xml文件路径
	std::vector<CString> m_vcMainLang;  //主窗口的语言存贮
	std::vector<CString> m_vcTipsLge;

	int       m_nInterpolateReso;       //插值分辨率的索引


	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnClose();
	CString Self_GetMyDocument(void);
	void Self_ReadIni(CString inipath);
protected:
	afx_msg LRESULT OnScanset(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTemplate(WPARAM wParam, LPARAM lParam);
public:
	void Self_EnsureItems(void);      //导出反射稿模板
	void Self_EnsureItems2(void);     //导出透射稿模板
	int Self_FindTems(CString docpath);
	void Self_ReadXml(CString xmlpath);
	CString Self_SlcSaveDoc(void);
	void Self_CapatureImg(CString imgname);
	CString Self_NamingFile(int count);
	void Self_ReadNameRule(void);
	CString Self_CreateThumb(CString srcimg, CString dstimg);
	int GetTypeFromFileName(LPCTSTR pstr);
	BOOL ThumbaiList(int thumbwidth, int thumbheight);
	CString Self_GetImgFromPDF(CString pdfpath, CString dstpath);
	BOOL GhostPdf2Image(char* pdfpath, char* imgpath, char* resolution, char* gsdll);
	afx_msg void OnDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On32771Delete();
	afx_msg void On32772Property();
	CString Self_GetPDFFromImg(CString imgpath, CString pdfpath);
	void Self_ReadWaterIni(CString inipath);
	void Self_AddWaterMark(CString imgpath);
	void Self_EnhenceRelay(void);
	void Self_ReduceRelay(void);
	int Self_GetFontSize(int index);
	CString Self_GetFontName(int index);
	CString Self_GetTimeInfo(void);
	DECLARE_EVENTSINK_MAP()
	void DeviceChangedUdsVideoctrl1(LPCTSTR changeType, LPCTSTR deviceName);
	void DeviceOpenedUdsVideoctrl1(LPCTSTR DevName);
	void Self_ShowImgInfo(CString imgpath);
	void Self_SetRelayZero(void);
	void Self_SetRelayValue(int dstvalue);
	int Self_GetRelayStatus(void);
	void Self_SetRelay100(void);
	BOOL Self_FindCamera(CString xmlpath);
	afx_msg void OnBnClickedBtnFullscreen();
	void Self_NormalScreen(void);
	afx_msg void OnBnClickedBtnNext();
	void Self_FullScreen(void);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_conPicCtrl;
	void Self_ShowPicCtrl(void);
	void Self_ResetImageRect(void);
	void Self_ResizeImage(CWnd* pWnd, Mat srcImg);
	void Self_ShowMatImage2(Mat img, CRect rect);
	void Self_CVShowImage(CString imgpath);
	afx_msg void OnItemchangedListImage(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnImgprocess(WPARAM wParam, LPARAM lParam);
public:
	Mat ImageRotate(Mat img, int angle);
	void Self_ClearPicCtrl(void);
	void Self_SaveLastImg(void);
	Mat ImageMirror(Mat img, bool mirrormark);
	Mat ImageInvert(Mat img);
	Mat ImageSharp(Mat img);
	Mat BrightAndContrast(Mat img, int bright, int contrast);
	Mat ImageGamma(Mat img, int gama);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	BOOL Self_ZoomSize(Mat src, float ratio, bool zoommark);
	Mat Self_CropImage(Mat img, CRect showRect, CRect cropRect);
	BOOL Self_DisableCtrl(int index);
	void Self_ShowOcxCtrl(void);
	int Self_GetFontWidth(LOGFONT text, CString textinfo);
	BOOL Self_EnsureSave(void);
	afx_msg void OnHoverListImage(NMHDR *pNMHDR, LRESULT *pResult);
	void Self_CreateLine(void);
	void Self_UpdateThumb(int index, CString imgpath);
	void Self_ReplaceImage(int thumbwidth, int thumbheight, int item);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int Self_Test(void);
	CToolTipCtrl   m_tipInfo; 
	CPngButton m_btnFullScreen;
	CPngButton m_btnZoomIn;
	CPngButton m_btnZoomOut;
	CPngButton m_btnDrag;
	afx_msg void OnBnClickedBtnLast();
protected:
	afx_msg LRESULT OnRefreshimg(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnDrag();
	
	afx_msg void OnSelchangingTabCtrl(NMHDR *pNMHDR, LRESULT *pResult);
protected:
//	afx_msg LRESULT OnManagetem(WPARAM wParam, LPARAM lParam);
public:
	void Self_CVShowTipImage(CString imgpath);
	CString Self_Img2DCM(CString imgpath);
	void Self_OriSize(Mat src);
	void Self_SetRelay1(void);
	void Self_ReadLanguageXml(CString xmlpath, vector <CString>& vec, CString nodename);
	int Self_GetSpyRes(int diyvalue);
	CString Self_InterPolateImage(CString srcImage, CString dstImage, int index);
	CString Self_GetPdfFromImg(CString srcImg, CString dstImg);
	BOOL Self_FilterRes(CString res);
	void Self_CaptureHdrImg(CString imgname);

	//包围测光与
	BOOL     m_BHDR;
	int      m_nHDRMerge;    //合并方式
	int      m_nHDRLight;    //灯箱亮度调整
	int      m_nHDRDelay;    //延时
	int      m_nHDRGray;     //灰阶

	BOOL     m_BDOC;
	void AdjustRelay(int value, int src);
	void Self_TimeDelay(int time_ms);

	//标注
	int         m_nLineMode;         //0-矩形， 1-箭头， 2-随意画，3-添加文本
	int         m_nLineWidth;        //线宽
	int         m_nArrowLen;         //箭头倒角长度
	int         m_nArrowAngle;       //箭头倒角角度
	COLORREF    m_refLineColor;      //线以及字体的颜色

	int         m_nFontSize;         //字体大小
	CString     m_strFont;           //字体
	CString     m_strInfo;           //添加信息
	BOOL        m_BBold;             //加粗
	BOOL        m_BItalic;           //斜体

	int         m_nNoteCount;        //标注计数位
	CPoint      m_ptNoteSite;        //上一次位子标注的位置

	Mat Self_DrawArrow(Mat img, CRect showRect, CRect cropRect, int linewidth, COLORREF linecolor);
	Mat Self_DrawRetangle(Mat img, CRect showRect, CRect cropRect, int linewidth, COLORREF linecolor);
	Mat drawArrow(Mat img, cv::Point pStart, cv::Point pEnd, int len, int alpha, cv::Scalar& color, int thickness, int lineType);
	Mat Self_AddText(Mat src, CRect showRect, CRect cropRect, CString textinfo, COLORREF color, CString font, int fontsize, bool bold, bool italic);
	void GetStringSize(HDC hDC, const char* str, int* w, int* h);
	void putTextEx(Mat& dst, const char* str, cv::Point org, Scalar color, int fontSize, const char* fn, bool italic, bool underline, bool bold);


	//HDR拍摄
	int       m_nHDRCapDelay;       //HDR拍摄间隔

	BOOL      m_BHDRCap;            //HDR拍摄开关
	int       m_nNorLight;          //正常灯箱亮度
	int       m_nLowLight;          //欠曝时灯箱亮度
	int       m_nHigLight;          //过曝时灯箱亮度

	int       m_nNorGray;           //正常灰阶
	int       m_nLowGray;           //欠曝灰阶
	int       m_nHigGray;           //过曝灰阶

	int       m_nNorDelay;          //首张图像延时(从当前灯箱的其他亮度调节至10需要的时长)
	int       m_nLowDelay;          //欠曝延时
	int       m_nHigDelay;          //过曝延时

	int       m_nNorBackLgt;        //正常逆光对比
	int       m_nLowBackLgt;        //欠曝逆光对比
	int       m_nHigBackLgt;        //过曝逆光对比

	//LDR拍摄
	int       m_nNorLightL;          //正常灯箱亮度
	int       m_nLowLightL;          //欠曝时灯箱亮度
	int       m_nHigLightL;          //过曝时灯箱亮度

	int       m_nNorGrayL;           //正常灰阶
	int       m_nLowGrayL;           //欠曝灰阶
	int       m_nHigGrayL;           //过曝灰阶

	int       m_nNorDelayL;          //首张图像延时(从当前灯箱的其他亮度调节至10需要的时长)
	int       m_nLowDelayL;          //欠曝延时
	int       m_nHigDelayL;          //过曝延时

	int       m_nNorBackLgtL;        //正常逆光对比
	int       m_nLowBackLgtL;        //欠曝逆光对比
	int       m_nHigBackLgtL;        //过曝逆光对比


	void Self_CaptureImgHDR(CString imgname, int mode);
	void Self_HDRMergeImgs(CString higimg, CString norimg, CString lowimg, CString outimg);

	//调焦
	int       m_nVidoeMode;        //MJPG/YUY2
	int       m_nFocusValue;       //当前焦点值
	int       m_nDevIndex;         //当前打开设备索引
	HINSTANCE m_hDllInst;          //加载调焦dll     
	void Self_HDRMergeImgs3_1(CString HigImg, CString NorImg, CString LowImg, CString outImg, int mode);

	//高密度和低密度拍照
	int                  m_nHdrMergeMode;
	std::vector<CString> m_vcSomeStrInfo;
	std::vector<float>   m_vcLShutter;
	std::vector<float>   m_vcHShutter;
	float Self_GetShutter(int lightvalue);
	int Self_GetIntervalTime(void);

	//测速
	int  m_nIntervalTime;        //该时间间隔为调节10格灯箱亮度的时间，单位ms
	int  m_nIniTime;             //配置文件中包含的间隔时间，该间隔时间包括自动设置
	BOOL m_BFirstCap;
	double Self_GetAvgGray(CString imgpath);
	void Self_HDRMergeImgEx(CString LowImg, CString NorImg, CString HigImg, CString OutImg, int mode, int lowlight_L, int norlight_L, int higlight_L, int lowlight_H, int norlight_H, int higlight_H);

	//拍文字
	int m_nTextLgtT; //透明文字，灯箱亮度
	int m_nTextCstT; //透明文字，对比度
	int m_nTextLgtL; //非透明文字，灯箱亮度
	int m_nTextCstL; //非透明文字，对比度
protected:
	afx_msg LRESULT OnSettext(WPARAM wParam, LPARAM lParam);
public:
	CWinThread* hThreadHandle;  //保存线程句柄
	ThreadInfo  stcThreadInfo;
	CString     m_strCurImgName; //用于线程拍摄
	int         m_nCurImgMode;
	void Self_CaptureImgHDRThread(CString imgname, int mode, int ex);
protected:
	afx_msg LRESULT OnThreadover(WPARAM wParam, LPARAM lParam);
public:
	int Self_GetIntervalTime2(void);
	double Self_GetAvgGray2(CString imgpath, cv::Rect *slcRect);
	double Self_GetAvgGray3(CString imgpath, cv::Rect slcRect);
	int GetMemoryInfoEx(void);
	void GetCpuInfo(CString& chProcessorName, CString& chProcessorType, DWORD& dwNum, DWORD& dwMaxClockSpeed);
};
