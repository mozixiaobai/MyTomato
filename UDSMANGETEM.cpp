// UDSMANGETEM.cpp : 实现文件
//

#include "stdafx.h"
#include "XRayViewerv1.0.h"
#include "UDSMANGETEM.h"
#include "afxdialogex.h"
#include "UDSNEWTEMNAME.h"


// CUDSMANGETEM 对话框
CString    g_strNewName;

IMPLEMENT_DYNAMIC(CUDSMANGETEM, CDialogEx)

CUDSMANGETEM::CUDSMANGETEM(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSMANGETEM::IDD, pParent)
{

}

CUDSMANGETEM::~CUDSMANGETEM()
{
}

void CUDSMANGETEM::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_MANGETEM, m_conManageTem);
}


BEGIN_MESSAGE_MAP(CUDSMANGETEM, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NEWTE, &CUDSMANGETEM::OnBnClickedBtnNewte)
	ON_BN_CLICKED(IDC_BTN_TEMDELETE, &CUDSMANGETEM::OnBnClickedBtnTemdelete)
	ON_BN_CLICKED(IDC_BTN_TEMNAME, &CUDSMANGETEM::OnBnClickedBtnTemname)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, &CUDSMANGETEM::OnBnClickedBtnDefault)
	ON_BN_CLICKED(IDC_BTN_TEMOUTPUT, &CUDSMANGETEM::OnBnClickedBtnTemoutput)
	ON_BN_CLICKED(IDCANCEL, &CUDSMANGETEM::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_CMB_MANGETEM, &CUDSMANGETEM::OnSelchangeCmbMangetem)
//	ON_WM_CLOSE()
END_MESSAGE_MAP()



BOOL CUDSMANGETEM::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/************************
	*        目录
	* 1、查询模板
	* 2、显示模板
	* 3、窗口语言初始化
	*
	*
	************************/
	

	m_pMainWnd = AfxGetApp()->GetMainWnd();
	m_hMainWnd = m_pMainWnd->GetSafeHwnd();

	m_strNewestTem = _T("");


	/*1、查询模板*/
	m_nSlcIndex  = -1;
	m_strDocPath  = Self_GetMyDocument();

	m_strLgeXmlPath  = m_strDocPath;
	m_strLgeXmlPath += _T("\\UDSXRayData\\language.xml");

	m_strDocPath += _T("\\UDSXRayData\\xml");

	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcTemMagLge, _T("ManageTem"));
	Self_ReadLanguageXml(m_strLgeXmlPath, m_vcTipsLge, _T("Tips"));

	Self_FindAllTems(m_strDocPath);

	/*2、显示模板*/
	int  tem_nIndex = 0;
	std::vector<CString>::iterator  tem_item;
	for (tem_item=m_vcXmlName.begin(); tem_item!=m_vcXmlName.end(); tem_item++, tem_nIndex++)
	{
		m_conManageTem.InsertString(tem_nIndex, *tem_item);
	}
	if (m_vcXmlName.size()>0)
	{
		m_conManageTem.SetCurSel(0);
		m_nSlcIndex = 0;
	}
	
	/*3、窗口语言初始化*/
	HWND    tem_hWnd = this->GetSafeHwnd();
	CWnd*   tem_pWnd;
	tem_pWnd = FromHandle(tem_hWnd);
	tem_pWnd->SetWindowText(m_vcTemMagLge[0]);

	GetDlgItem(IDC_STA_MANGETEM)->SetWindowText(m_vcTemMagLge[1]);

	GetDlgItem(IDC_BTN_TEMDELETE)->SetWindowText(m_vcTemMagLge[2]);
	GetDlgItem(IDC_BTN_TEMNAME)->SetWindowText(m_vcTemMagLge[3]);
	GetDlgItem(IDCANCEL)->SetWindowText(m_vcTemMagLge[4]);
	GetDlgItem(IDC_BTN_NEWTE)->SetWindowText(m_vcTemMagLge[5]);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSMANGETEM::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


HBRUSH CUDSMANGETEM::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

// CUDSMANGETEM 消息处理程序


//模板新建
void CUDSMANGETEM::OnBnClickedBtnNewte()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (IDOK == m_dlgTemName.DoModal())
	{
		//判断是否为空
		if (g_strNewName == _T(""))
		{
			return;
		}
		//判断是否重名
		std::vector<CString>::iterator  tem_item;
		for (tem_item=m_vcXmlName.begin(); tem_item!=m_vcXmlName.end(); tem_item++)
		{
			if (*tem_item==g_strNewName)
			{
				if (IDOK != MessageBox(m_vcTipsLge[4], m_vcTipsLge[0], MB_OKCANCEL))
				{
					return;
				} 
				else
				{
					break;
				}
			}
		}
		
		CString*   tem_strXmlName = new CString(g_strNewName);
		//创建xml
		::SendMessage(m_hMainWnd, WM_TEMPLATE, 21, (WPARAM)(tem_strXmlName));

		//更新xml
		m_conManageTem.InsertString(-1, g_strNewName);
		m_vcXmlName.push_back(g_strNewName);

		CString tem_strOldName = m_vcXmlPath[0];
		CString tem_strNewName = _T("");
		CString  tem_strTem = tem_strOldName;
		TCHAR*   tem_cTemStr;
		tem_cTemStr = tem_strTem.GetBuffer();
		tem_strTem.ReleaseBuffer();
		PathRemoveFileSpec(tem_cTemStr);

		tem_strNewName  = tem_cTemStr;
		tem_strNewName += _T("\\");
		tem_strNewName += g_strNewName;
		tem_strNewName += _T(".xml");

		m_vcXmlPath.push_back(tem_strNewName);
		m_strNewestTem = g_strNewName;
		g_strNewName   = _T("");
	}
}


//模板删除
void CUDSMANGETEM::OnBnClickedBtnTemdelete()
{
	// TODO: 在此添加控件通知处理程序代码
	//删除模板********
	//默认模板不可删除
	m_nSlcIndex = m_conManageTem.GetCurSel();
	CString  tem_strName = m_vcXmlName[m_nSlcIndex];
//	if (tem_strName == _T("默认"))
//	if (tem_strName == _T("Default"))
	if (tem_strName == _T("透射稿默认") || tem_strName == _T("反射稿默认"))
	{
		MessageBox(_T("默认模板不可删除！"), _T("UDS紫图"), MB_OK);
//		MessageBox(_T("The default template cannot be deleted! "), _T("UDS"), MB_OK);
		return;
	}
	//删除文件
	if (m_nSlcIndex!=-1)
	{
		DeleteFile(m_vcXmlPath[m_nSlcIndex]);

		m_vcXmlName.erase(m_vcXmlName.begin() + m_nSlcIndex);
		m_vcXmlPath.erase(m_vcXmlPath.begin() + m_nSlcIndex);

		m_conManageTem.DeleteString(m_nSlcIndex);
		m_conManageTem.SetCurSel(0);
		m_nSlcIndex = 0;
	}
}


//模板改名
void CUDSMANGETEM::OnBnClickedBtnTemname()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取当前选定项
	m_nSlcIndex = m_conManageTem.GetCurSel();
	CString  tem_strName = m_vcXmlName[m_nSlcIndex];
//	if (tem_strName == _T("默认"))
//	if (tem_strName == _T("Default"))
	if (tem_strName == _T("透射稿默认") && tem_strName == _T("反射稿默认"))
	{
		MessageBox(_T("默认模板不可改名！"), _T("UDS紫图"), MB_OK);
//		MessageBox(_T("The default template cannot be renamed! "), _T("UDS"), MB_OK);
		return;
	}
	CString tem_strOldName = m_vcXmlPath[m_nSlcIndex];
	CString tem_strNewName = _T("");

	if (IDOK == m_dlgInputName.DoModal())
	{
		if (g_strNewName == _T(""))
		{
			return;
		}
		//修改文件名
		CString  tem_strTem = tem_strOldName;
		TCHAR*   tem_cTemStr;
		tem_cTemStr = tem_strTem.GetBuffer();
		tem_strTem.ReleaseBuffer();
		PathRemoveFileSpec(tem_cTemStr);

		tem_strNewName  = tem_cTemStr;
		tem_strNewName += _T("\\");
		tem_strNewName += g_strNewName;
		tem_strNewName += _T(".xml");
		if (tem_strOldName != tem_strNewName)
		{
			int      tem_nLen =WideCharToMultiByte(CP_ACP, 0, tem_strOldName, -1, NULL, 0, NULL, NULL);  
			char*    ptxtSrc =new char[tem_nLen +1];  
			WideCharToMultiByte(CP_ACP, 0, tem_strOldName, -1, ptxtSrc, tem_nLen, NULL, NULL); 

			tem_nLen =WideCharToMultiByte(CP_ACP, 0, tem_strNewName, -1, NULL, 0, NULL, NULL);  
			char*    ptxtDst =new char[tem_nLen +1];  
			WideCharToMultiByte(CP_ACP, 0, tem_strNewName, -1, ptxtDst, tem_nLen, NULL, NULL);  
			int  tem_rcRename = rename(ptxtSrc, ptxtDst);

			//更新vector
			m_vcXmlName[m_nSlcIndex] = g_strNewName;
			m_vcXmlPath[m_nSlcIndex] = tem_strNewName;
			m_strNewestTem = g_strNewName;

			//重新加载模板管理界面列表
			m_conManageTem.ResetContent();
			int  tem_nIndex = 0;
			std::vector<CString>::iterator tem_item;
			for (tem_item=m_vcXmlName.begin(); tem_item!=m_vcXmlName.end(); tem_item++, tem_nIndex++)
			{
				m_conManageTem.InsertString(tem_nIndex, *tem_item);
			}
			tem_nIndex = 0;
			for (tem_item=m_vcXmlName.begin(); tem_item!=m_vcXmlName.end(); tem_item++, tem_nIndex++)
			{
				if (*tem_item == g_strNewName)
				{
					m_conManageTem.SetCurSel(tem_nIndex);
					break;
				}
			}
			
			//重新加载选择模板界面列表
		}	
	} 
	g_strNewName = _T("");
}

//*********************************************************
//默认模板
void CUDSMANGETEM::OnBnClickedBtnDefault()
{
	// TODO: 在此添加控件通知处理程序代码
}


//导出模板
void CUDSMANGETEM::OnBnClickedBtnTemoutput()
{
	// TODO: 在此添加控件通知处理程序代码
}


//窗口退出
void CUDSMANGETEM::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//发送消息，刷新模板列表
	CString*   tem_strXmlName = new CString(m_strNewestTem);
	//创建xml
	::SendMessage(m_hMainWnd, WM_TEMPLATE, 22, (WPARAM)(tem_strXmlName));

	CDialogEx::OnCancel();
}


CString CUDSMANGETEM::Self_GetMyDocument(void)
{
	CString        tem_strMyDocument = _T("");
	TCHAR          tem_cMyDocument[MAX_PATH] = {0};
	LPITEMIDLIST   tem_Pid = NULL;
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &tem_Pid);
	if (tem_Pid && SHGetPathFromIDList(tem_Pid, tem_cMyDocument))
	{
		tem_strMyDocument = tem_cMyDocument;
		return tem_strMyDocument;
	}
	return tem_strMyDocument;
}


int CUDSMANGETEM::Self_FindAllTems(CString docpath)
{
	m_vcXmlName.clear();
	m_vcXmlPath.clear();
	int         tem_nFileCount = 0;    //子文件数量
	BOOL        bGetRc      = NULL;
	CFileFind   temFinder   = NULL;
	CString     strFileName = NULL;
	CString     strSubDoc   = NULL;
	CString     strFilePath = NULL;

	bGetRc = temFinder.FindFile(docpath + "\\*.*");
	while (bGetRc)
	{
		bGetRc = temFinder.FindNextFile();
		if (temFinder.IsDots())
		{
			//为缺省目录
			continue;
		}
		else if (temFinder.IsDirectory())
		{
			//检测为子文件夹，保存备用
			continue;
		} 
		else if (temFinder.IsCompressed())
		{
			//压缩文件
			continue;
		}
		else if (temFinder.IsSystem())
		{
			//系统文件
			continue;
		}
		else
		{
			//检测为文件，进行过滤
			strFileName = temFinder.GetFileName();
			CString  strMiddle = strFileName;
			int      nIndex = strMiddle.ReverseFind('.');
			if (nIndex != -1)
			{
				strMiddle = strMiddle.Mid(nIndex+1);
				strMiddle.MakeLower();
				if (strMiddle == _T("xml"))		
				{
					//区别图像文件和非图像文件，将FieName保存
					tem_nFileCount++;
					strFilePath = _T("");
//					if (strFileName != _T("默认.xml"))
					{
						CString tem_strFileName = strFileName.Left(strFileName.GetLength()-4);
						m_vcXmlName.push_back(tem_strFileName);
						strFilePath = docpath + _T("\\") + strFileName;
						m_vcXmlPath.push_back(strFilePath);
					}
				}
			}
		}
	}	
	return tem_nFileCount;
}


void CUDSMANGETEM::OnSelchangeCmbMangetem()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSlcIndex = m_conManageTem.GetCurSel();
}


void CUDSMANGETEM::Self_ReadLanguageXml(CString xmlpath, vector<CString>& vec, CString nodename)
{
	const char*   tem_cInfo;
	int           tem_nMark     = 0;
	int           tem_nAuto     = 0;
	int           tem_nSetValue = 0;

	CStringA     tem_straXmlPath(xmlpath);
	const char*  tem_cXmlPath = tem_straXmlPath.GetString();

	CStringA     tem_straNodeName(nodename);
	const char*  tem_cNodeName = tem_straNodeName.GetString();


	//加载xml文件
	TiXmlDocument   tem_xmlDoc;
	tem_xmlDoc.LoadFile(tem_cXmlPath);

	//根节点---------------------------------------------------------------
	TiXmlElement*    tem_xmlRootElt = tem_xmlDoc.RootElement();

	TiXmlElement*    tem_xmlChildElt;
	tem_xmlChildElt = tem_xmlRootElt->FirstChildElement();
	tem_cInfo = tem_xmlChildElt->Value();
	TiXmlAttribute*  tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
	tem_nMark = tem_xmlChildAtb->IntValue();


	CString  tem_strInfo = _T("");
	if (tem_nMark==1)
	{
		//跳过前面的中文信息
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		while (tem_xmlChildElt)
		{
			tem_cInfo = tem_xmlChildElt->Value();
			tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
			tem_nMark = tem_xmlChildAtb->IntValue();
			if (tem_nMark==1 && !strcmp(tem_cNodeName,tem_cInfo))
			{
				break;
			}
			tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		}

		//		while (tem_xmlChildElt )
		{
			//获取该节点名称
			tem_cInfo = tem_xmlChildElt->Value();
			tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
			tem_nMark = tem_xmlChildAtb->IntValue();
			tem_xmlChildAtb = tem_xmlChildAtb->Next();
			while (tem_xmlChildAtb)
			{
				tem_cInfo       = tem_xmlChildAtb->Value();

				tem_strInfo     = tem_cInfo;
				//				MessageBox(tem_strInfo);
				vec.push_back(tem_strInfo);
				tem_xmlChildAtb = tem_xmlChildAtb->Next();
			}
			//			tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		}

	}
	else
	{
		tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
		while (tem_xmlChildElt)
		{
			tem_cInfo = tem_xmlChildElt->Value();
			tem_xmlChildAtb= tem_xmlChildElt->FirstAttribute();
			tem_nMark = tem_xmlChildAtb->IntValue();
			if (tem_nMark==0 && !strcmp(tem_cNodeName,tem_cInfo))
			{
				tem_xmlChildAtb = tem_xmlChildAtb->Next();
				while (tem_xmlChildAtb)
				{
					tem_cInfo       = tem_xmlChildAtb->Value();
					tem_strInfo     = tem_cInfo;
					//					MessageBox(tem_strInfo);
					vec.push_back(tem_strInfo);
					tem_xmlChildAtb = tem_xmlChildAtb->Next();
				}
				break;
			}
			else
			{
				tem_xmlChildElt = tem_xmlChildElt->NextSiblingElement();
			}		
		}
	}
}
