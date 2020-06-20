// adView.cpp : CadView ���ʵ��
//

#include "stdafx.h"
#include "ad.h"

#include "MainFrm.h"
#include "adDoc.h"
#include "adView.h"
#include "AddVexDlg.h"
#include "VexInfoDlg.h"
#include "ArcInfoDlg.h"
#include "ShowInfoDlg.h"
#include "ArcEditDlg.h"
#include "AreaSizeDlg.h"
#include "math.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CadView

IMPLEMENT_DYNCREATE(CadView, CFormView)

BEGIN_MESSAGE_MAP(CadView, CFormView)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MENU_ADD_VEX, &CadView::OnMenuAddVex)
	ON_COMMAND(ID_MENU_DEL_VEX, &CadView::OnMenuDelVex)
	ON_COMMAND(ID_MENU_ADD_ARC, &CadView::OnMenuAddArc)
	ON_COMMAND(ID_MENU_DEL_ARC, &CadView::OnMenuDelArc)
	ON_COMMAND(ID_MENU_SHOW_VEX_INFO, &CadView::OnMenuShowInfo)
	//ON_COMMAND(ID_FILE_SAVE, &CadView::OnFileSave)
	//ON_COMMAND(ID_FILE_OPEN, &CadView::OnFileOpen)
	ON_COMMAND(ID_MENU_SHOW_ARC_INFO, &CadView::OnShowArcInfo)
	ON_COMMAND(ID_AREA_SIZE, &CadView::OnAreaSize)
	ON_COMMAND(ID_MENU_FIND_PATH, &CadView::OnMenuFindPath)
	ON_COMMAND(ID_MENU_RESET_ALL_COLOR, &CadView::OnMenuResetAllColor)
	ON_COMMAND(ID_Visit_ALL, &CadView::OnVisitAll)
	ON_COMMAND(ID_MENU_ORTHLIST_GRAP, &CadView::OnMenuOrthlistGrap)
	ON_COMMAND(ID_MENU_CHILD_SIBING_TREE, &CadView::OnMenuChildSibingDfsTree)
	ON_UPDATE_COMMAND_UI(ID_MENU_ORTHLIST_GRAP, &CadView::OnUpdateMenuOrthlistGrap)
	ON_UPDATE_COMMAND_UI(ID_MENU_CHILD_SIBING_TREE, &CadView::OnUpdateMenuChildSibingTree)
	ON_UPDATE_COMMAND_UI(ID_MENU_ADD_VEX, &CadView::OnUpdateMenuAddVex)
	ON_UPDATE_COMMAND_UI(ID_MENU_DEL_VEX, &CadView::OnUpdateMenuDelVex)
	ON_UPDATE_COMMAND_UI(ID_MENU_ADD_ARC, &CadView::OnUpdateMenuAddArc)
	ON_UPDATE_COMMAND_UI(ID_MENU_DEL_ARC, &CadView::OnUpdateMenuDelArc)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_VEX_INFO, &CadView::OnUpdateMenuShowVexInfo)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_ARC_INFO, &CadView::OnUpdateMenuShowArcInfo)
	ON_UPDATE_COMMAND_UI(ID_MENU_FIND_PATH, &CadView::OnUpdateMenuFindPath)
	ON_UPDATE_COMMAND_UI(ID_Visit_ALL, &CadView::OnUpdateVisitAll)
	ON_UPDATE_COMMAND_UI(ID_MENU_RESET_ALL_COLOR, &CadView::OnUpdateMenuResetAllColor)
	ON_UPDATE_COMMAND_UI(ID_AREA_SIZE, &CadView::OnUpdateAreaSize)
	//ON_COMMAND(ID_FILE_NEW, &CadView::OnFileNew)
	ON_COMMAND(ID_MENU_CHECK_ANNULUS, &CadView::OnMenuCheckAnnulus)
	ON_COMMAND(ID_MENU_CHILD_SIBING_BFS_TREE, &CadView::OnMenuChildSibingBfsTree)
	ON_UPDATE_COMMAND_UI(ID_MENU_CHILD_SIBING_BFS_TREE, &CadView::OnUpdateMenuChildSibingBfsTree)
	ON_UPDATE_COMMAND_UI(ID_MENU_CHECK_ANNULUS, &CadView::OnUpdateMenuCheckAnnulus)
	ON_COMMAND(ID_MENU_CRITICAL_PATH, &CadView::OnMenuCriticalPath)
	ON_UPDATE_COMMAND_UI(ID_MENU_CRITICAL_PATH, &CadView::OnUpdateMenuCriticalPath)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_SHORT_PATH, &CadView::OnMenuShortPath)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHORT_PATH, &CadView::OnUpdateMenuShortPath)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CadView ����/����

CadView::CadView()
: CFormView(CadView::IDD)
, iMaxWidth(MINI_AREA_WIDTH)
, iMaxHeight(MINI_AREA_HEIGHT)
,iViewMode( GRAP_VIEW)
, lastPoint(30,30)
{
}

CadView::~CadView()
{
	pView = NULL;
}

void CadView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= WS_CLIPCHILDREN;
	return CFormView::PreCreateWindow(cs);
}

void CadView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	pView = this;

	if (!pView)
	{
		MessageBox("ȡ����ͼָ�����");
		PostMessage(WM_QUIT);
	}


	SetAreaSize( iMaxWidth , iMaxHeight);

	if (fileName!="")
	{
		AdjMatrixGrap.CreateFromFile( fileName ) ;
		OrthGrap.CreateOrthListFromMatrix();
	}
	
}


// CadView ���

#ifdef _DEBUG
void CadView::AssertValid() const
{
	CFormView::AssertValid();
}

void CadView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CadDoc* CadView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CadDoc)));
	return (CadDoc*)m_pDocument;
}
#endif //_DEBUG


// CadView ��Ϣ�������






CDragStatic* CadView::NewDragStatic(LPCTSTR strTitle, CPoint pt , int radius)
{
	CDragStatic *p= new CDragStatic();
	p->Create(strTitle,this,pt,radius);
	p->ShowWindow(SW_SHOW);
	return p;
}


void CadView::DrawString(CDC* pDC,CString str, CPoint a,CPoint b, COLORREF clr)
{
	pDC->SetBkMode (TRANSPARENT);   
	pDC->SetTextColor ( clr );
	CFont font;   
	LOGFONT stFont; //���嶨��ṹ    

	//���������ʽ    
	memset(&stFont, 0, sizeof(LOGFONT));   
	stFont.lfHeight=MulDiv(14, -pDC->GetDeviceCaps(LOGPIXELSY), 72);   
	stFont.lfWeight=FW_NORMAL;   
	stFont.lfClipPrecision=CLIP_LH_ANGLES; 
	stFont.lfUnderline= TRUE;
	stFont.lfItalic = TRUE;
	strcpy_s(stFont.lfFaceName,"Arial");

	double nAngle=-atan2((double)(b.y-a.y),(double)(b.x-a.x)); 
	nAngle=nAngle*1800/3.1415;
	//�趨�µ���ת�Ƕ�    
	stFont.lfEscapement=(LONG)nAngle;  
	font.CreateFontIndirect(&stFont);   
	CFont* pOldFont=pDC ->SelectObject(&font);   


	int xx =(int) ((float)(b.x-a.x)/2+a.x);
	int yy =(int) ((float)(b.y-a.y)/2+a.y);

	//�������    
	pDC->TextOut(xx ,yy ,str);   
	//ԭ������    
	pDC->SelectObject(pOldFont);   
	font.DeleteObject();  
}

void CadView::OnDraw(CDC* pDC)
{
		RECT clientRect;
	GetClientRect(&clientRect);
	HRGN rgn = CreateRectRgnIndirect(&clientRect);
	ClipChildren(m_hWnd, rgn);
	SelectClipRgn(pDC->m_hDC, rgn);


	CDC dcMemory;
	CBitmap bitmap;
	CRect m_rcClient;
	GetClientRect(m_rcClient);
	CBrush a;
	a.CreateSolidBrush(RGB(33,33,33));
	if (!pDC->IsPrinting())
	{
		if (dcMemory.CreateCompatibleDC(pDC))
		{
			if (bitmap.CreateCompatibleBitmap(pDC,m_rcClient.right,m_rcClient.bottom))
			{
				dcMemory.SelectObject(&bitmap);
				dcMemory.FillRect(m_rcClient,&a);

				pDC->DPtoLP( m_rcClient );
				dcMemory.MoveTo( iMaxWidth-2 ,0);
				dcMemory.LineTo( iMaxWidth-2 ,iMaxHeight-2 );
				dcMemory.LineTo( 0 ,iMaxHeight-2 );
				
				if( iViewMode == GRAP_VIEW )
				{
					DrawArc(&dcMemory);
				}
				else if( iViewMode == DFS_VIEW )
				{
					DrawCSArc(&dcMemory , ChSibDFSTree.root);
				}
				else if ( iViewMode == BFS_VIEW )
				{
					DrawCSArc(&dcMemory , ChSibBFSTree.root);
				}

				pDC->BitBlt(m_rcClient.left,m_rcClient.top,m_rcClient.right,m_rcClient.bottom,&dcMemory,0,0,SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}

		DeleteObject(rgn);
}


void CadView::DrawCSArc(CDC* pDC , CSNode * tree)
{
	CPoint a;
	CPoint b;
	CSNode *p = NULL;
	if (tree)
	{
		p = tree->firstChild;
		if( p )
		{
			do
			{				
				ArrowTo( pDC ,tree->DragBox->GetPoint() ,p->DragBox->GetPoint() ,RGB( 255, 0, 255 ) , 2 );
				p = p->nextSibling;
			}while( p );
		DrawCSArc( pDC , tree->firstChild)	;	
		}
		if (tree->nextSibling)
		{
			DrawCSArc( pDC, tree->nextSibling );
		}

	}
}


void CadView::DrawArc(CDC* pDC)
{
	CPoint a;
	CPoint b;	
	OrthListArcBox *p=NULL;
	CString strWeight;
	if(OrthGrap.m_iVexNum>=2)
	{


		for (int index=0 ,i=0;i<OrthGrap.m_iVexNum;index++)
		{
			if(OrthGrap.xlist[index].m_bUsed)
			{
				i++;
				p=OrthGrap.xlist[index].m_pThisTail;//ֻ���뻡

				while (p)
				{
					a= OrthGrap.xlist[p->headVex].DragBox->GetPoint();
					b= OrthGrap.xlist[p->tailVex].DragBox->GetPoint();
					strWeight.Format("$ %d",p->data.quan);
					ArrowTo( pDC ,a ,b ,p->color ,p->PenWidth,OrthGrap.xlist[p->tailVex].DragBox->GetRadius() );
					DrawString(pDC ,strWeight, a, b, p->color);
					p=p->m_pNextSameTail;
				}

			}
		}

	}

}

void CadView::UpdateMessage(int flag )
{
	CString strMessage;
	switch(flag)
	{
	case 0:
		strMessage.Format("%d���ڵ㣬%d������",OrthGrap.m_iVexNum,OrthGrap.m_iArcNum);
		((CMainFrame *)AfxGetApp()->m_pMainWnd)->ShowGrapInfo(strMessage);
		break;
	case GRAP_VIEW:
		((CMainFrame *)AfxGetApp()->m_pMainWnd)->ShowViewInfo("ʮ��������ͼ");
		break;
	case DFS_VIEW:
		((CMainFrame *)AfxGetApp()->m_pMainWnd)->ShowViewInfo("�����������ɭ����ͼ");
		break;
	case BFS_VIEW:
		((CMainFrame *)AfxGetApp()->m_pMainWnd)->ShowViewInfo("�����������ɭ����ͼ");
		break;
	}

}
/*
void CadView::ArrowTo( CDC* pDC,const CPoint from,const CPoint to, COLORREF clr , int PenWidth, int toRadius)
{
int nWidth =10;             //�����εױ߿��
	float fTheta = 10;           //�����ζ��ǽǶ�
	
	CPoint pBase;
	CPoint aptPoly[3];
	float vecLine[2];
	float vecLeft[2];
	float fLength;
	float th;
	float ta;
//////////////////////////////////////////////////////////////////////////

	vecLine[0] = (float) to.x - from.x;
	vecLine[1] = (float) to.y - from.y;

	fLength = (float) sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);

	ta = nWidth / (2.0f * (tanf(fTheta) / 2.0f) * fLength);

	pBase.x = (int) (to.x + -ta * vecLine[0]);
	pBase.y = (int) (to.y + -ta * vecLine[1]);

//////////////////////////////////////////////////////////////////////////

	aptPoly[0].x = pBase.x;
	aptPoly[0].y = pBase.y;

	// build the line vector
	vecLine[0] = (float) aptPoly[0].x - from.x;
	vecLine[1] = (float) aptPoly[0].y - from.y;

	// build the arrow base vector - normal to the line
	vecLeft[0] = -vecLine[1];
	vecLeft[1] = vecLine[0];

	// setup length parameters
	fLength = (float) sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
	th = nWidth / (2.0f * fLength);
	ta = nWidth / (2.0f * (tanf(fTheta) / 2.0f) * fLength);

	// find the base of the arrow

	pBase.x = (int) (aptPoly[0].x + -ta * vecLine[0]);
	pBase.y = (int) (aptPoly[0].y + -ta * vecLine[1]);

	aptPoly[1].x = (int) (pBase.x + th * vecLeft[0]);
	aptPoly[1].y = (int) (pBase.y + th * vecLeft[1]);
	aptPoly[2].x = (int) (pBase.x + -th * vecLeft[0]);
	aptPoly[2].y = (int) (pBase.y + -th * vecLeft[1]);

	MoveToEx(*pDC, from.x, from.y, NULL);
	
	CPen* pOldPen;
	CPen pen( BS_SOLID ,PenWidth ,clr);
	pOldPen = pDC->SelectObject(&pen);

	CBrush br,*pbrOld;
	br.CreateSolidBrush(clr);
	pbrOld = pDC->SelectObject(&br);
	pDC->LineTo(aptPoly[0].x, aptPoly[0].y);
	pDC->Polygon(aptPoly, 3);
}
*/
void CadView::ArrowTo( CDC* pDC,const CPoint from,const CPoint to, COLORREF clr , int PenWidth, int toRadius)
{
	//���յ�E�����Ϊlene_next�ĵط���һ�����ߣ���ԭ����������next�㣬�ڸô�����������������next�����Ϊlennext_two
	//�ĵ㣬���յ�ֱ�����������������������һ����ͷ
	int xe = to.x;
	int ye = to.y;
	int xs = from.x;
	int ys = from.y; 
	double lenarrow, a_sin, a_cos, lene_next , lennext_two;
	lenarrow=sqrt((double)(xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));//��ͷ����
	a_sin=(ye-ys)/lenarrow;//������sinֵ
	a_cos=(xe-xs)/lenarrow;//������cosֵ
	lene_next=18;//������E������һ��������next�ľ���
	lennext_two=8;//��next��������ͷ�ߵ��յ�ľ���
	double x1,y1,x2,y2;//��ͷ�������ߵ��յ�
	//E����涨��lene_next����x�������xe-lene_next*a_cos��
	CPoint ptnext(xe-toRadius*a_cos,ye-toRadius*a_sin);//��ͷ��Բ�߽�Ľ���
	CPoint ptnextnext(ptnext.x*a_cos,ptnext.y*a_sin); //��ͷ���������εױ��յ�����


	//�ҵ�next����ڴ����϶���Ϊlennext_two�������㣬x����ƽ�ƣ���y����ƽ�ƣ���һ��С��ֱ�������Σ��������������γɱ����������
	//x������ƽ��lennext_two*a_sin����Ϊsin��cos�����������ģ������������ĸ��������ʽ�Ӷ�ͨ�ã�x,y��Ҳ�����á�
	TRACE("%d,%d,%d,%d\n",to.x,to.y,ptnext.x,ptnext.y);
	x1=ptnext.x-lene_next*a_cos+lennext_two*a_sin;
	x2=ptnext.x-lene_next*a_cos-lennext_two*a_sin;
	y1=ptnext.y-lene_next*a_sin-lennext_two*a_cos;
	y2=ptnext.y-lene_next*a_sin+lennext_two*a_cos;
	
	MoveToEx(*pDC, xs, ys, NULL);
	CPen* pOldPen;
	CPen pen( BS_SOLID ,PenWidth ,clr);
	pOldPen = pDC->SelectObject(&pen);

	//pDC->MoveTo(xs,ys);
	pDC->LineTo(ptnext);
	//pDC->MoveTo(xe,ye);
	pDC->LineTo(x1,y1);
	pDC->MoveTo(ptnext);
	pDC->LineTo(x2,y2);


}

void CadView::ShowMessageBox(Status flag)
{
	CString strMsg = "�����ˣ�";
	switch(flag)
	{
	case SUCCESS:
		return;
	case VEX_EXIST:
		strMsg = "�����Ѵ���";
		break;
	case ARC_EXIST:
		strMsg = "���Ѵ���";
		break;
	case VEX_NOT_FOUND:
		strMsg = "���㲻����";
		break;
	case ARC_NOT_FOUND:
		strMsg = "��������";
		break;
	case NEW_ARC_ERR:
		strMsg = "�����»�ʧ��";
		break;
	case VEX_TOO_MANY:
		strMsg = "�������ѵ�����";
		break;

	}
	MessageBox(strMsg);
}


void CadView::AddVex(void)
{
	CString strkey;
	CAddVexDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		strkey= dlg.m_strKey;
		int s = OrthGrap.AddVex(strkey, dlg.strMoreInfo ,lastPoint);
		ShowMessageBox( s );
		Invalidate();
		UpdateMessage();
		ChSibBFSTree.bNeedChange = true;
	}
}

void CadView::AddArc(void)
{
	CString strkey1;
	CString strkey2;
	int strWeight;
	CArcEditDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		strkey1= dlg.strFirKey;
		strkey2= dlg.strSecKey;
		strWeight = dlg.uWeight;

		int s = OrthGrap.AddArc(OrthGrap.LocateVex(strkey1),OrthGrap.LocateVex(strkey2), strWeight);
		int s2 = SUCCESS;
		if(dlg.bDouble)
		{
			s2=	OrthGrap.AddArc(OrthGrap.LocateVex(strkey2),OrthGrap.LocateVex(strkey1), strWeight);
		}
		if (s2 != SUCCESS )//ֻ��ʾһ����ʾ��
			ShowMessageBox( s2 );
		else
			ShowMessageBox( s );
		Invalidate();
		UpdateMessage();
		ChSibBFSTree.bNeedChange = true;
	}
}

void CadView::DelArc(void)
{
	CArcEditDlg dlg;
	dlg.SetKind( KIND_DEL );
	if(dlg.DoModal()==IDOK)
	{
		int s = OrthGrap.DelArc(OrthGrap.LocateVex(dlg.strFirKey),OrthGrap.LocateVex(dlg.strSecKey));	
		int s2 = SUCCESS;
		if(dlg.bDouble)
		{
			s2=	OrthGrap.DelArc(OrthGrap.LocateVex(dlg.strSecKey),OrthGrap.LocateVex(dlg.strFirKey));
			ShowMessageBox( s2 );
		}
		if (s2 != SUCCESS )//ֻ��ʾһ����ʾ��
			ShowMessageBox( s );

		Invalidate();
		UpdateMessage();
		ChSibBFSTree.bNeedChange = true;
	}

}

void CadView::DelVex(void)
{
	CString strkey;
	CVexInfoDlg dlg;
	dlg.kindFlag=KIND_DEL;
	if(dlg.DoModal()==IDOK)
	{
		strkey= dlg.strKey;
		int s = OrthGrap.DelVex(strkey);
		ShowMessageBox( s );
		Invalidate();
		UpdateMessage();
		ChSibBFSTree.bNeedChange = true;
	}
}


void CadView::OnMenuAddVex()
{
	AddVex();
}

void CadView::OnMenuDelVex()
{
	DelVex();
}

void CadView::OnMenuAddArc()
{
	AddArc();
}

void CadView::OnMenuDelArc()
{
	DelArc();
}

void CadView::OnMenuShowInfo()
{
	CVexInfoDlg dlg;
	dlg.DoModal();
}

void CadView::OnShowArcInfo()
{
	CArcInfoDlg dlg;
	dlg.DoModal();
}


// ���û�����С
void CadView::SetAreaSize(int x,int y)
{
	iMaxWidth = max( x , iMaxWidth );
	iMaxHeight = max( y , iMaxHeight );
	CSize  ss( iMaxWidth, iMaxHeight);
	CRect rect=CRect( 0, 0 , iMaxWidth , iMaxHeight );
	SetScrollSizes(MM_TEXT, ss);
	GetParentFrame()->RecalcLayout();
	WINDOWPLACEMENT lpwndpl ;
	(AfxGetApp()->GetMainWnd())-> GetWindowPlacement( &lpwndpl);
	if (lpwndpl.showCmd != SW_SHOWMAXIMIZED)
	{
		ResizeParentToFit();
	}
	

}


//�Զ����㻭���С����ʹ��������Ӧ
void CadView::AutoCalcAreaSize()
{
	iMaxWidth = MINI_AREA_WIDTH;
	iMaxHeight = MINI_AREA_HEIGHT;
	
	CPoint a ( 0,0 ) ;
	if( iViewMode == GRAP_VIEW )
	{
		for (int i=0 ;i<MAX_VERTEX_NUM ;i++)
		{
			OrthListVexNode node = OrthGrap.xlist[i];
			if (node.m_bUsed)
			{
				a= node.DragBox->GetPoint();
				a.x += node.DragBox->GetRadius();
				a.y += node.DragBox->GetRadius();
				iMaxWidth = max( a.x  , iMaxWidth );
				iMaxHeight = max( a.y , iMaxHeight );
			}

		}
	}
	else if( iViewMode == DFS_VIEW && !ChSibDFSTree.bNeedChange ) 
	{
		ChSibDFSTree.MaxPoint( ChSibDFSTree.root, a );
		iMaxWidth = max( a.x +20 , iMaxWidth );
		iMaxHeight = max( a.y +20 , iMaxHeight );

	}
	else if( iViewMode == BFS_VIEW && !ChSibBFSTree.bNeedChange ) 
	{
		ChSibBFSTree.MaxPoint( ChSibBFSTree.root, a );
		iMaxWidth = max( a.x +20 , iMaxWidth );
		iMaxHeight = max( a.y +20 , iMaxHeight );

	}

}

void CadView::OnAreaSize()
{
	CAreaSizeDlg dlg;
	dlg.width = iMaxWidth;
	dlg.height = iMaxHeight;
	if(dlg.DoModal()==IDOK)
		SetAreaSize(iMaxWidth, iMaxHeight);
}

void CadView::OnMenuFindPath()
{
	CArcEditDlg dlg;
	dlg.SetKind( KIND_FIND );
	if(dlg.DoModal()!=IDOK)
		return;
	if(dlg.bDouble)
		OrthGrap.ResetAllArcColor();

	if( !OrthGrap.FindPath( dlg.strFirKey , dlg.strSecKey ))
	{
		MessageBox("û��·����" ,"���ҽ��" , MB_OK | MB_ICONEXCLAMATION);
	}

}

void CadView::OnMenuResetAllColor()
{
	OrthGrap.ResetAllArcColor();
	OrthGrap.ResetAllVexStyle();
}

void CadView::OnVisitAll()
{
	CShowInfoDlg dlg;
	dlg.DoModal();

}


void CadView::OnMenuOrthlistGrap()
{
	ScrollWindow(GetScrollPos(SB_HORZ) ,GetScrollPos(SB_VERT));
	SetScrollPos( SB_HORZ ,0 );
	SetScrollPos( SB_VERT ,0 );
	iViewMode = GRAP_VIEW;
	for (int i=0; i<MAX_VERTEX_NUM; i++)
	{
		if (OrthGrap.xlist[i].m_bUsed)
		{
			OrthGrap.xlist[i].DragBox->ShowWindow(SW_SHOW);
		}
	}
	ChSibDFSTree.HideVex( ChSibDFSTree.root ,SW_HIDE);
	ChSibBFSTree.HideVex( ChSibBFSTree.root ,SW_HIDE);
	AutoCalcAreaSize();
	UpdateMessage(1);
	SetAreaSize( iMaxWidth , iMaxHeight);
	Invalidate(FALSE);
}

void CadView::OnMenuChildSibingDfsTree()
{
	ScrollWindow(GetScrollPos(SB_HORZ) ,GetScrollPos(SB_VERT));
	SetScrollPos( SB_HORZ ,0 );
	SetScrollPos( SB_VERT ,0 );

	iViewMode = DFS_VIEW ;
	for (int i=0; i<MAX_VERTEX_NUM; i++)
	{
		if (OrthGrap.xlist[i].m_bUsed)
		{
			OrthGrap.xlist[i].DragBox->ShowWindow(SW_HIDE);
		}
	}
	OrthGrap.CreateDFSForest();
	ChSibBFSTree.HideVex( ChSibBFSTree.root ,SW_HIDE);
	ChSibDFSTree.HideVex( ChSibDFSTree.root ,SW_SHOW);
	AutoCalcAreaSize();
	SetAreaSize( iMaxWidth , iMaxHeight);
	UpdateMessage(DFS_VIEW);
	Invalidate(FALSE);
}

void CadView::OnMenuChildSibingBfsTree()
{
	ScrollWindow(GetScrollPos(SB_HORZ) ,GetScrollPos(SB_VERT));
	SetScrollPos( SB_HORZ ,0 );
	SetScrollPos( SB_VERT ,0 );
	iViewMode = BFS_VIEW;
	for (int i=0; i<MAX_VERTEX_NUM; i++)
	{
		if (OrthGrap.xlist[i].m_bUsed)
		{
			OrthGrap.xlist[i].DragBox->ShowWindow(SW_HIDE);
		}
	}

	OrthGrap.CreateBFSForest();
	ChSibDFSTree.HideVex( ChSibDFSTree.root ,SW_HIDE);
	ChSibBFSTree.HideVex( ChSibBFSTree.root ,SW_SHOW);
	AutoCalcAreaSize();
	SetAreaSize( iMaxWidth , iMaxHeight);
	UpdateMessage(BFS_VIEW);
	Invalidate(FALSE);
	//MessageBox("�˹�����δ��ɣ�");
}

void CadView::OnUpdateMenuOrthlistGrap(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->SetCheck( true );
	} 
	else
	{
		pCmdUI->SetCheck( false );
	}
	
}

void CadView::OnUpdateMenuChildSibingTree(CCmdUI *pCmdUI)
{
	if ( iViewMode == DFS_VIEW )
	{
		pCmdUI->SetCheck( true );
	} 
	else
	{
		pCmdUI->SetCheck( false );
	}
}

void CadView::OnUpdateMenuAddVex(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}

void CadView::OnUpdateMenuDelVex(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}
}

void CadView::OnUpdateMenuAddArc(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}

void CadView::OnUpdateMenuDelArc(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}

void CadView::OnUpdateMenuShowVexInfo(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}

void CadView::OnUpdateMenuShowArcInfo(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}

void CadView::OnUpdateMenuFindPath(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}

void CadView::OnUpdateVisitAll(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}

void CadView::OnUpdateMenuResetAllColor(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}

void CadView::OnUpdateAreaSize(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}

}


void CadView::OnMenuCheckAnnulus()
{
	if(OrthGrap. CheckAnnulus())
		MessageBox("��ͼ���л���","���ҽ��",MB_OK|MB_ICONEXCLAMATION );
	else
		MessageBox("��ͼ���޻���","���ҽ��",MB_OK|MB_ICONEXCLAMATION );
}



void CadView::OnUpdateMenuChildSibingBfsTree(CCmdUI *pCmdUI)
{
	if ( iViewMode == BFS_VIEW )
	{
		pCmdUI->SetCheck( true );
	} 
	else
	{
		pCmdUI->SetCheck( false );
	}

}

void CadView::OnUpdateMenuCheckAnnulus(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}
}

void CadView::OnMenuCriticalPath()
{
	
	if( ! OrthGrap.CriticalPath())
		MessageBox("���ҹؼ�·��ʧ�ܣ�\n��ͼ���ܲ���AOE��","��ʾ",MB_OK|MB_ICONWARNING);
}

void CadView::OnUpdateMenuCriticalPath(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}
}

void CadView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( iViewMode == GRAP_VIEW )
	{
		CPoint pt=point;
		ClientToScreen(&pt); 
		CMenu pSubMenu;
		pSubMenu.LoadMenu(IDR_MAINFRAME);
		pSubMenu.GetSubMenu(1)->TrackPopupMenu(0 ,pt.x,pt.y,this);//�����˵�
		lastPoint = point;
	}
	CFormView::OnRButtonDown(nFlags, point);
}

void CadView::OnMenuShortPath()
{
	if(!pShortPathDlg)
	{
		pShortPathDlg = new CShortPathDlg();
		pShortPathDlg->Create(IDD_DIALOG_SHORT_PATH,this);
		
	}
	pShortPathDlg->ShowWindow(SW_SHOW);
}

void CadView::OnUpdateMenuShortPath(CCmdUI *pCmdUI)
{
	if ( iViewMode == GRAP_VIEW )
	{
		pCmdUI->Enable( true );
	} 
	else
	{
		pCmdUI->Enable( false );
	}
}

void CadView::ClipChildren(HWND hwnd, HRGN parent)
{
	HWND child = ::GetWindow(hwnd, GW_CHILD);
	while(child)
	{
		RECT rect;
		::GetWindowRect(child, &rect);
		::ScreenToClient(hwnd, (LPPOINT)&rect.left);
		::ScreenToClient(hwnd, (LPPOINT)&rect.right);
		HRGN rgn = ::CreateEllipticRgnIndirect(&rect);
		::CombineRgn(parent, parent, rgn, RGN_DIFF);
		::DeleteObject(rgn);
		child = ::GetWindow(child, GW_HWNDNEXT);
	}
}

BOOL CadView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*
	RECT clientRect;
	GetClientRect(&clientRect);
	HRGN rgn = CreateRectRgnIndirect(&clientRect);
	ClipChildren(m_hWnd, rgn);
	SelectClipRgn(pDC->m_hDC, rgn);
	DeleteObject(rgn);
	FillRect(pDC->m_hDC, &clientRect, (HBRUSH)GetStockObject(GRAY_BRUSH));*/
	return TRUE;
}
