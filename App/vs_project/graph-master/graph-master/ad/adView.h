// adView.h : CadView ��Ľӿ�
//


#pragma once
#include "afxwin.h"
#include "adDoc.h"
#include "atltypes.h"
#include "ChildSiblingTree.h"

#define GRAP_VIEW	1	//ʮ��������ͼ
#define BFS_VIEW	2	//�����������ɭ����ͼ
#define DFS_VIEW	3	//�����������ɭ����ͼ


class CadView : public CFormView
{
protected: // �������л�����
	CadView();
	DECLARE_DYNCREATE(CadView)

public:
	enum{ IDD = IDD_AD_FORM };

// ����
public:
	CadDoc* GetDocument() const;

// ����
public:


// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()



protected:
	virtual void OnDraw(CDC* pDC);
public:
	//����ַ���
	void DrawString(CDC* pDC,CString str, CPoint a,CPoint b, COLORREF clr) ;
public:
	//��������ʮ������
	void DrawArc(CDC* pDC);
public:	
	//��������������
	void DrawCSArc(CDC* pDC , CSNode * tree);
public:
	//����״̬������
	void UpdateMessage(int flag = 0);
public:
	//����ͷ
	void ArrowTo( CDC* pDC,const CPoint from,const CPoint to, COLORREF clr ,int PenWidth,int toRadius=32);
public:
	//��ʾ��Ϣ�����ɾ���ȣ�
	void ShowMessageBox(Status flag);
public:
	//��Ӷ���
	void AddVex(void);
public:
	//��ӱ�
	void AddArc(void);
public:
	//ɾ������
	void DelVex(void);
public:
	//ɾ����
	void DelArc(void);
public:
	//�����������
	void DepthFirstSearch(void);
public:
	//�����������
	void BreadthFirstSearth(void);
public:
	// ���û�����С
	void SetAreaSize( int x, int y );
public:
	// �Զ����û�����С
	void AutoCalcAreaSize();
public:
	//�����¿ؼ�
	CDragStatic* NewDragStatic(LPCTSTR strTitle, CPoint pt , int radius);
public:
	// �������
	int iMaxWidth;
public:
	// ����߶�
	int iMaxHeight;
public:
	//��ͼģʽ
	int iViewMode;
public:
	afx_msg void OnMenuAddVex();
public:
	afx_msg void OnMenuDelVex();
public:
	afx_msg void OnMenuAddArc();
public:
	afx_msg void OnMenuDelArc();
public:
	afx_msg void OnMenuShowInfo();
public:
	afx_msg void OnShowArcInfo();
public:
	afx_msg void OnAreaSize();
public:
	afx_msg void OnMenuFindPath();
public:
	afx_msg void OnMenuResetAllColor();
public:
	afx_msg void OnVisitAll();
public:
	afx_msg void OnMenuVisitAll();
public:
	afx_msg void OnMenuOrthlistGrap();
public:
	afx_msg void OnMenuChildSibingDfsTree();
public:
	afx_msg void OnUpdateMenuOrthlistGrap(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuChildSibingTree(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuAddVex(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuDelVex(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuAddArc(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuDelArc(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuShowVexInfo(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuShowArcInfo(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuFindPath(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateVisitAll(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuResetAllColor(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateAreaSize(CCmdUI *pCmdUI);
public:
	afx_msg void OnMenuCheckAnnulus();
public:
	afx_msg void OnMenuChildSibingBfsTree();
public:
	afx_msg void OnUpdateMenuChildSibingBfsTree(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuCheckAnnulus(CCmdUI *pCmdUI);
	afx_msg void OnMenuCriticalPath();
	afx_msg void OnUpdateMenuCriticalPath(CCmdUI *pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuShortPath();
	afx_msg void OnUpdateMenuShortPath(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void ClipChildren(HWND hwnd, HRGN parent);
private:
	// �������������,������Ҽ������ĵ�
	CPoint lastPoint;
};

#ifndef _DEBUG  // adView.cpp �еĵ��԰汾
inline CadDoc* CadView::GetDocument() const
   { return reinterpret_cast<CadDoc*>(m_pDocument); }
#endif

