
// XRayViewerv1.0.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXRayViewerv10App:
// �йش����ʵ�֣������ XRayViewerv1.0.cpp
//

class CXRayViewerv10App : public CWinApp
{
public:
	CXRayViewerv10App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

	HANDLE    m_hMutex;  //������ע��������
	virtual int ExitInstance();
};

extern CXRayViewerv10App theApp;