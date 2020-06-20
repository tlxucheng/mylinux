// ad.h : ad Ӧ�ó������ͷ�ļ�
//
#pragma once

typedef int ( CALLBACK * FUNC ) ( PCHAR );

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "OrthListGrap.h"
#include "AdjMatrixGrap.h"
#include "ChildSiblingTree.h"
#include "adView.h"
#include "limits"
#include "ShortPathDlg.h"
// CadApp:
// �йش����ʵ�֣������ ad.cpp
//

class CadApp : public CWinApp
{
public:
	CadApp();
	~CadApp();
public:
	HMODULE m_hModule;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
public:
	void InitSkin();

	bool ResToFile(int ResID, CString ResKind,CString &fileName);
	void UpdateIcon(void);
};

extern CadApp theApp;
extern COrthListGrap OrthGrap;
extern CAdjMatrixGrap AdjMatrixGrap;
extern CadView *pView;
extern CChildSiblingTree ChSibDFSTree;
extern CChildSiblingTree ChSibBFSTree;
extern CString fileName;
extern CShortPathDlg* pShortPathDlg;
static  int MAX_INT = (std::numeric_limits<int>::max)()/2;