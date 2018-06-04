// ProgressBarEx.cpp : ʵ���ļ�
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



// CProgressBarEx ��Ϣ�������




void CProgressBarEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
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
	// ��Ϊ��ͼ��Ϣ���� CProgressCtrl::OnPaint()
}
