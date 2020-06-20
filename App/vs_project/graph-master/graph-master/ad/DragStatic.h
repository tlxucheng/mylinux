#pragma once
#include "atltypes.h"

#define VEX_NORMAL			0
#define VEX_HEAD			1
#define VEX_TAIL			2 
#define VEX_CIRCLE_POINT	3



// CDragStatic

class CDragStatic : public CWnd
{
	DECLARE_DYNAMIC(CDragStatic)


public:
	CDragStatic();
	virtual ~CDragStatic();

protected:
	DECLARE_MESSAGE_MAP()
protected:
	//virtual void PreSubclassWindow();
private:
	CPoint m_ptCenter;
	int m_nRadius;
public:
	//����Ƿ���
	//bool m_bLBdown;
public:
	//�ؼ�����
	CRect m_Rect;
public:
	//����Ƿ�����
	//bool m_bOver;
public:
	//�����ʽ
	UINT m_utextFomat;
public:
	//���������
	//CPoint m_Point;
public:
	//�������
	//CPoint nowPos;
public:
	//�ֺͿؼ�����ɫ
	COLORREF m_crText,m_crOverBG,m_crBG;
public:
	//����������ɫ
	void SetTextColor(COLORREF crText);
public:
	//���ñ���ɫ
	void SetBGColer(COLORREF crBG);
public:
	//�������������ʾ
	void SetMuliLineMode(bool bMuliLine);
public:
	//�����������ɫ
	void SetOverBGColor(COLORREF crOverBG);
public:
	//���²���ʾ��ʾ��
	void UpdateMyView(int msgFalg);
public:
	//���������
	CPoint GetPoint(void);
public:
	//���ÿؼ���ʾ���
	void SetStyle(int style);
	CRgn       m_rgn; 

public:
//	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	afx_msg void OnMove(int x, int y);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnDestroy();
public:
	afx_msg void OnShowVexInfo();
public:
	afx_msg void OnMenuAddVex();
public:
	afx_msg void OnMenuDelArc();
public:
	afx_msg void OnMenuDelVex();
public:
	afx_msg void OnMenuAddArc();
public:
	afx_msg void OnMenuShowArcInfo();
public:
	afx_msg void OnMenuVisitAll();
public:
	afx_msg void OnMenuFindPath();
public:
	afx_msg void OnMenuResetAllColor();
public:
	afx_msg void OnMenuCriticalPath();
public:
	afx_msg void OnMenuShortPath();
public:
	afx_msg void OnMenuCheckAnnulus();
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL Create(CString title,
				CWnd* pParentWnd,
				CPoint pt=CPoint(30,30) ,
				int radius = 32
             );


	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	// ��ȡ�뾶
	int GetRadius(void);
};


