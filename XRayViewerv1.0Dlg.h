
// XRayViewerv1.0Dlg.h : ͷ�ļ�
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
#include "IMAGEAndDCM.h"    //JPGתDCM��
#include "Shellapi.h"
#include "pdflib.h"
#include "pdflib.hpp"
#include "UDSWaterSet.h"
#include "cv.h"
#include "opencv2/photo.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "CvvImage.h"      //ATL��cvvImageͬʱ������CImage
#include "PngButton.h"
#include "UDSSelectFormat.h"
#include <iostream>
#include "Shellapi.h"
#include <afxtempl.h> //��ȡ��������



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


UINT ThreadDelay(LPVOID lpParam);   //��ʱ�߳����
struct ThreadInfo
{
	HWND     hWnd;     //���ھ�������ڷ�����Ϣ
	int      time;     //�ӳ�ʱ��
	int      mode;     //��־λ
};

// CXRayViewerv10Dlg �Ի���
class CXRayViewerv10Dlg : public CDialogEx
{
// ����
public:
	CXRayViewerv10Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XRAYVIEWERV10_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int        m_nMinWidth;        //���ڵ���С���
	int        m_nMinHeight;       //���ڵ���С�߶�
	int        m_nLastTemplate;    //�ϴ�ʹ��ģ��
	int        m_nLastRes;         //�ϴ�ʹ�÷ֱ���
	int        m_nLastImgType;     //�ϴ�ʹ��ͼ������
	int        m_nLastPreRotate;
	int        m_nLastMergeMode;
	int        m_nLastWaterMark;
	int        m_nNameMode;
	int        m_nNameDate;
	int        m_nNameTime;
	int        m_nNameBegin;
	int        m_nNameBegin2;       //����������ʼλ

	int        m_nLastRelay;      //�ϴ��趨�ĵƹ�ֵ
	int        m_nLastIris;
	int        m_nLastBright;     //�ϴε�����ֵ
	int        m_nLastExpos;
	int        m_nLastFocus;
	int        m_nLastGama;
	int        m_nLastGain;
	int        m_nLastHue;
	int        m_nLastPan;
	int        m_nLastRoll;
	int        m_nLastTilt;
	int        m_nLastZoom;
	int        m_nLastContrst;    //�ϴεĶԱȶȣ��������л�tabʱ������slid������Ϣ
	int        m_nLastSharp;
	int        m_nLastSatura;
	int        m_nLastWhiteB;
	int        m_nLastBackLight;
	int        m_nLastGray;       //�ҽ�
	int        m_nImageCount;     //���ռ���
	int        m_nThumbWidth;    
	int        m_nThumbHeight;
	int        m_nRSlcIndex;      //�Ҽ�ѡ������
	int        m_nHDRBackLgt;     //��Χ�ع�Сģ���е����Ա�ѡ��

	int        m_nRedValue;
	int        m_nGreenValue;
	int        m_nBlueValue;
	int        m_nWaterMark;
	int        m_nWaterSite;
	int        m_nWaterSize;
	int        m_nWaterFont;
	int        m_nWaterMode;      //ʱ��ˮӡ

	int        m_nViewMode;       //��Ұģʽ

	int        m_nAngleCount;     //��ת���ۼ�

	int        m_nPrcsIndex;      //��ǰ����ͼ�������

	long       m_lLeftSite;       //���п�����
	long       m_lTopSite;
	long       m_lRightSite;
	long       m_lBottomSite;

	CString    m_strWaterColor;
	CString    m_strWaterInfo;    //ˮӡ��Ϣ
	CString    m_strTabImg;       //Tab�ؼ��л�ʱ����ʾͼ��

	unsigned int m_nStatus;

	long       m_lReturnCode;     //������

	BOOL       m_BShowTab;        //�Ƿ���ʾTabCtrl
	BOOL       m_BShowList;       //�Ƿ���ʾListCtrl
	BOOL       m_BFullScreen;     //�Ƿ�ȫ��
	BOOL       m_BShowPicCtrl;    //��ʾPicCtrl
	BOOL       m_BSpaceDown;      //�������ְ�����Ӧ�������뵯��
	BOOL       m_BEscDown;        //���ּ�����Ӧ
	BOOL       m_BClickTab;       //���Tab�ؼ���ֹ����ˢ�£�����ͼ�񱻸���
	BOOL       m_BOriSize;        //1:1��ʾ
	BOOL       m_BCtrl;           //�Ƿ���Ctrl��

	CString    m_strNameDivide;
	CString    m_strNamePre1;
	CString    m_strNamePre2;
	CString    m_strNamePre3;
	CString    m_strLastTem;      //�ϴ�ʹ��ģ��
	CString    m_strDevPID;       //�豸PID_VID��Ϣ
	CString    m_strDevVID;
	CString    m_strDevCode;      //�豸��֤��
	CString    m_strMyCode1;
	CString    m_strConfigDoc;    //������ģ���ļ����ڵ�Ŀ¼
	CString    m_strXmlDoc;       //����Ŀ¼
	CString    m_strThumbDoc;     //����ͼĿ¼
	CString    m_strCVDoc;        //ͼ������Ŀ¼
	CString    m_strIniPath;      //ini�����ļ�·��
	CString    m_strXmlPath;      //xml�����ļ�·��
	CString    m_strSaveDoc;      //����Ŀ¼
	CString    m_strFileFormat;   //�ļ���ʽ
	
	CRect           m_rcFullScreen;
	WINDOWPLACEMENT m_stcOldWinPlc;     //�ṹ���а����˴�������Ļ�ϵ�λ����Ϣ
	WINDOWPLACEMENT m_strOcxWinPlc;

	CRect           m_FullScreenRect; 
	CRect           m_rcLastOCX;
	WINDOWPLACEMENT m_OldWndPlacement; // ȫ��ʱ�Ի����λ������  
	WINDOWPLACEMENT m_NewWndPlacement; // ȫ����Ի����λ������  
	

	CMenu          m_ListMenu;

	CUDSONE           m_dlgOne;
	CUDSTWO           m_dlgTwo;
	CUDSTHREE         m_dlgThree;
	CUDSNameSet       m_dlgNameSet;
	CUDSWaterSet      m_dlgWaterSet;
	CUDSSelectFormat  m_dlgSlcFormat;

	std::vector<CString>   m_vcTemName;
	std::vector<CString>   m_vcTemPath;
	std::vector<CString>   m_vcImgName;         //ͼ����    
	std::vector<CString>   m_vcThumbPath;       //����ͼ·��
	std::vector<CString>   m_vcFilePath;       //�����ļ�·��

	ATL::CImage        m_imgBK;                  //����ͼ��
	CListCtrl       m_conListCtrl;
	CImageList      m_imagelist;

	CUds_videoctrl1 m_conVideoCtrl;
	CTabCtrl        m_conTab;

	CWnd*           pWnd;

	int        m_nLastBrit;          //�ϴε���������ֵ
	int        m_nLastCtst;          //�ϴε����ĶԱȶ�ֵ
	int        m_nLastCGama;

	Mat        m_cvSrcImage;
	Mat        m_cvDstImage;
	Mat        m_cvLastImg;
	Mat        m_cvNextImg;
	Mat        m_cvTipsImg;          //��ʾ��Ϣͼ��

	CRect      m_rcPicRect;          //Picture�ؼ�����
	CRect      m_rcImageShow;        //ͼ����ʾ���꣬�����Picture�ؼ�
	CRect      m_rcImageCrop;        //ͼ���ѡ���꣬�����Picture�ؼ�
	CRect      m_rcImageRect;        //��Ҫ��ʾ��ͼ��rect


	int        m_nDrawX;             //ͼ�����ź�������
	int        m_nDrawY;
	int        m_nImageBright;       //ͼ������
	int        m_nImageContrast;     //ͼ��Աȶ�
	int        m_nOffsetX, m_nOffsetY;
	int        m_nShowWidth;         //��ʼ����ʾ���
	int        m_nShowHeight;        //��ʼ����ʾ�߶�

	float      m_fCurRatio;           //��ǰ���ű���
	float      m_fPI;                  //Բ���ʳ���

	BOOL      m_BNoSaved;              //�Ƿ񱣴�

	CString   m_strFilesPath;
	CString   m_strBufferImgPath;

	std::vector<CString> m_vcHistoryImg;

	BOOL      m_BPaintLine;
	BOOL      m_BSlcRect;
	BOOL      m_BLButtonDown;
	BOOL      m_BSlcRected;          //ѡ��������־λ
	BOOL      m_BSelectTab;          //ͼ��༭�Ĳ���״̬��ֹ�л���ǩ
	BOOL      m_BLabel;              //��ע���λ
	

	CPoint    m_ptOri,  m_ptEnd;
	CPoint    m_ptDragOri, m_ptDragEnd;   //�϶��ߴ�

	COLORREF  m_clrCtrlColor;
	COLORREF  m_clrBackColor;
	COLORREF  m_clrTextColor;

	BOOL      m_BShowTips;       //�Ƿ���ʾ����Ի���
	BOOL      m_BSaveFmt;        //�Ƿ񱣴�Ϊԭ��ʽ

	CString   m_strLangXmlPath;         //����xml�ļ�·��
	std::vector<CString> m_vcMainLang;  //�����ڵ����Դ���
	std::vector<CString> m_vcTipsLge;

	int       m_nInterpolateReso;       //��ֵ�ֱ��ʵ�����


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
	void Self_EnsureItems(void);      //���������ģ��
	void Self_EnsureItems2(void);     //����͸���ģ��
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

	//��Χ�����
	BOOL     m_BHDR;
	int      m_nHDRMerge;    //�ϲ���ʽ
	int      m_nHDRLight;    //�������ȵ���
	int      m_nHDRDelay;    //��ʱ
	int      m_nHDRGray;     //�ҽ�

	BOOL     m_BDOC;
	void AdjustRelay(int value, int src);
	void Self_TimeDelay(int time_ms);

	//��ע
	int         m_nLineMode;         //0-���Σ� 1-��ͷ�� 2-���⻭��3-����ı�
	int         m_nLineWidth;        //�߿�
	int         m_nArrowLen;         //��ͷ���ǳ���
	int         m_nArrowAngle;       //��ͷ���ǽǶ�
	COLORREF    m_refLineColor;      //���Լ��������ɫ

	int         m_nFontSize;         //�����С
	CString     m_strFont;           //����
	CString     m_strInfo;           //�����Ϣ
	BOOL        m_BBold;             //�Ӵ�
	BOOL        m_BItalic;           //б��

	int         m_nNoteCount;        //��ע����λ
	CPoint      m_ptNoteSite;        //��һ��λ�ӱ�ע��λ��

	Mat Self_DrawArrow(Mat img, CRect showRect, CRect cropRect, int linewidth, COLORREF linecolor);
	Mat Self_DrawRetangle(Mat img, CRect showRect, CRect cropRect, int linewidth, COLORREF linecolor);
	Mat drawArrow(Mat img, cv::Point pStart, cv::Point pEnd, int len, int alpha, cv::Scalar& color, int thickness, int lineType);
	Mat Self_AddText(Mat src, CRect showRect, CRect cropRect, CString textinfo, COLORREF color, CString font, int fontsize, bool bold, bool italic);
	void GetStringSize(HDC hDC, const char* str, int* w, int* h);
	void putTextEx(Mat& dst, const char* str, cv::Point org, Scalar color, int fontSize, const char* fn, bool italic, bool underline, bool bold);


	//HDR����
	int       m_nHDRCapDelay;       //HDR������

	BOOL      m_BHDRCap;            //HDR���㿪��
	int       m_nNorLight;          //������������
	int       m_nLowLight;          //Ƿ��ʱ��������
	int       m_nHigLight;          //����ʱ��������

	int       m_nNorGray;           //�����ҽ�
	int       m_nLowGray;           //Ƿ�ػҽ�
	int       m_nHigGray;           //���ػҽ�

	int       m_nNorDelay;          //����ͼ����ʱ(�ӵ�ǰ������������ȵ�����10��Ҫ��ʱ��)
	int       m_nLowDelay;          //Ƿ����ʱ
	int       m_nHigDelay;          //������ʱ

	int       m_nNorBackLgt;        //�������Ա�
	int       m_nLowBackLgt;        //Ƿ�����Ա�
	int       m_nHigBackLgt;        //�������Ա�

	//LDR����
	int       m_nNorLightL;          //������������
	int       m_nLowLightL;          //Ƿ��ʱ��������
	int       m_nHigLightL;          //����ʱ��������

	int       m_nNorGrayL;           //�����ҽ�
	int       m_nLowGrayL;           //Ƿ�ػҽ�
	int       m_nHigGrayL;           //���ػҽ�

	int       m_nNorDelayL;          //����ͼ����ʱ(�ӵ�ǰ������������ȵ�����10��Ҫ��ʱ��)
	int       m_nLowDelayL;          //Ƿ����ʱ
	int       m_nHigDelayL;          //������ʱ

	int       m_nNorBackLgtL;        //�������Ա�
	int       m_nLowBackLgtL;        //Ƿ�����Ա�
	int       m_nHigBackLgtL;        //�������Ա�


	void Self_CaptureImgHDR(CString imgname, int mode);
	void Self_HDRMergeImgs(CString higimg, CString norimg, CString lowimg, CString outimg);

	//����
	int       m_nVidoeMode;        //MJPG/YUY2
	int       m_nFocusValue;       //��ǰ����ֵ
	int       m_nDevIndex;         //��ǰ���豸����
	HINSTANCE m_hDllInst;          //���ص���dll     
	void Self_HDRMergeImgs3_1(CString HigImg, CString NorImg, CString LowImg, CString outImg, int mode);

	//���ܶȺ͵��ܶ�����
	int                  m_nHdrMergeMode;
	std::vector<CString> m_vcSomeStrInfo;
	std::vector<float>   m_vcLShutter;
	std::vector<float>   m_vcHShutter;
	float Self_GetShutter(int lightvalue);
	int Self_GetIntervalTime(void);

	//����
	int  m_nIntervalTime;        //��ʱ����Ϊ����10��������ȵ�ʱ�䣬��λms
	int  m_nIniTime;             //�����ļ��а����ļ��ʱ�䣬�ü��ʱ������Զ�����
	BOOL m_BFirstCap;
	double Self_GetAvgGray(CString imgpath);
	void Self_HDRMergeImgEx(CString LowImg, CString NorImg, CString HigImg, CString OutImg, int mode, int lowlight_L, int norlight_L, int higlight_L, int lowlight_H, int norlight_H, int higlight_H);

	//������
	int m_nTextLgtT; //͸�����֣���������
	int m_nTextCstT; //͸�����֣��Աȶ�
	int m_nTextLgtL; //��͸�����֣���������
	int m_nTextCstL; //��͸�����֣��Աȶ�
protected:
	afx_msg LRESULT OnSettext(WPARAM wParam, LPARAM lParam);
public:
	CWinThread* hThreadHandle;  //�����߳̾��
	ThreadInfo  stcThreadInfo;
	CString     m_strCurImgName; //�����߳�����
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
