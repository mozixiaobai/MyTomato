#pragma once


// CProgressBarEx

class CProgressBarEx : public CProgressCtrl
{
	DECLARE_DYNAMIC(CProgressBarEx)

public:
	CProgressBarEx();
	virtual ~CProgressBarEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


