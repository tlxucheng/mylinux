// adDoc.cpp : CadDoc ���ʵ��
//

#include "stdafx.h"
#include "ad.h"

#include "adDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CadDoc

IMPLEMENT_DYNCREATE(CadDoc, CDocument)

BEGIN_MESSAGE_MAP(CadDoc, CDocument)
END_MESSAGE_MAP()


// CadDoc ����/����

CadDoc::CadDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CadDoc::~CadDoc()
{
}

BOOL CadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	if ( pView && pView ->iViewMode != GRAP_VIEW )
	{
		 pView ->OnMenuOrthlistGrap();
	}
	OrthGrap.Clear();
	ChSibDFSTree.DelVex(ChSibDFSTree.root);
	ChSibBFSTree.DelVex(ChSibDFSTree.root);
	ChSibBFSTree.bNeedChange = true;
	ChSibDFSTree.bNeedChange = true;
	if( pView)
	{
		pView ->UpdateMessage();
		pView ->Invalidate(FALSE);
	}
	this->SetModifiedFlag(FALSE);
	return TRUE;
}




// CadDoc ���л�

void CadDoc::Serialize(CArchive& ar)
{
	//this->getFil
	if (ar.IsStoring())
	{
		TRACE(_T("store"));

	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		TRACE(_T("read"));

	}
}


// CadDoc ���

#ifdef _DEBUG
void CadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CadDoc ����


BOOL CadDoc::OnSaveDocument(LPCTSTR lpszPathName)
{

	AdjMatrixGrap.CreateAdjMatrixGrap();
	AdjMatrixGrap.Save(lpszPathName);
	this->SetModifiedFlag(FALSE);
	return TRUE;
}


BOOL CadDoc::OnOpenDocument(LPCTSTR lpszPathName)
{

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	if( !AdjMatrixGrap.CreateFromFile(lpszPathName))
		return FALSE;
	
	if ( pView->iViewMode != GRAP_VIEW )
	{
			pView->OnMenuOrthlistGrap();
	}
	OrthGrap.CreateOrthListFromMatrix();
	ChSibBFSTree.bNeedChange = true;
	ChSibDFSTree.bNeedChange = true;
	pView->Invalidate();
	this->SetModifiedFlag(FALSE);
	return TRUE;
}
