
// XRayViewerv1.0.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "XRayViewerv1.0Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXRayViewerv10App

BEGIN_MESSAGE_MAP(CXRayViewerv10App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CXRayViewerv10App ����

CXRayViewerv10App::CXRayViewerv10App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CXRayViewerv10App ����

CXRayViewerv10App theApp;


// CXRayViewerv10App ��ʼ��

BOOL CXRayViewerv10App::InitInstance()
{
	//��������������ֻ֤��һ��ʵ������-------------------------------------
	m_hMutex = CreateMutex(NULL,TRUE,_T("UDSSmartImage"));
	if (m_hMutex == NULL)
	{
		return FALSE;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
		return FALSE;
	}
	//---------------------------------------------------------------------

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxInitRichEdit();   //û�иþ䣬���RichEdit�������ؼ�����ʾ�쳣

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CXRayViewerv10Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CXRayViewerv10App::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_hMutex != NULL)
	{
		CloseHandle(m_hMutex);	//�رվ��
	}

	return CWinApp::ExitInstance();
}
