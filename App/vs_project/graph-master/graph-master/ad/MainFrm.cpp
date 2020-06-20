// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "ad.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,          //״ָ̬ʾ��
	IDS_MESSAGE,			//�ڵ㻡��Ϣָʾ��
	IDS_VIEW_MESSAGE,		//��ͼ��Ϣָʾ��

};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(ID_SEPARATOR),ID_SEPARATOR,SBPS_NOBORDERS ,180);
	m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(IDS_MESSAGE),IDS_MESSAGE,SBPS_STRETCH,0);
	m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(IDS_VIEW_MESSAGE),IDS_VIEW_MESSAGE,SBPS_NOBORDERS ,140);
	
	// TODO: �������Ҫ��������ͣ������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	
	//����ʾ�ĵ���
	//cs.style&=~(LONG) FWS_ADDTOTITLE;
	//��λ����
	cs.x = GetSystemMetrics( SM_CXSCREEN )/2-320;
	cs.y = GetSystemMetrics( SM_CYSCREEN )/2-240;
	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame ��Ϣ�������


void CMainFrame::ShowGrapInfo(CString info)
{
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(IDS_MESSAGE) ,info);

}

void CMainFrame::ShowViewInfo(CString info)
{
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(IDS_VIEW_MESSAGE) ,"   "+info);

}




void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x   =   560;   
	lpMMI->ptMinTrackSize.y   =   500; 

	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

