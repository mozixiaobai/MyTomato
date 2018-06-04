// ProgressBarEx.cpp : 实现文件
//

#include "stdafx.h"
#include "ProgressBarEx.h"


// CProgressBarEx
extern BOOL g_BBarColor;

IMPLEMENT_DYNAMIC(CProgressBarEx, CProgressCtrl)

CProgressBarEx::CProgressBarEx()
{

}

CProgressBarEx::~CProgressBarEx()
{
}


BEGIN_MESSAGE_MAP(CProgressBarEx, CProgressCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CProgressBarEx 消息处理程序




void CProgressBarEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CBrush BackgroundBrush;   
	CBrush ForeBrush;
	if (g_BBarColor)
	{
		BackgroundBrush.CreateSolidBrush(RGB(255,255,255)); 
		ForeBrush.CreateSolidBrush(RGB(0,255, 0));
	}
	else
	{
		BackgroundBrush.CreateSolidBrush(RGB(255,255,255)); 
		ForeBrush.CreateSolidBrush(RGB(220,51,0));
	}

	CRect r;
	this->GetClientRect(r);
	double With=r.Width();
	int min,max;
	this->GetRange(min,max);
	int pos= this->GetPos();
	double unit=(double)r.Width()/(max-min);
	dc.FillRect(r,&BackgroundBrush);    
	r.right=pos*unit;   
	dc.FillRect(r,&ForeBrush);   
	// 不为绘图消息调用 CProgressCtrl::OnPaint()
}
