// ShowInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ad.h"
#include "ShowInfoDlg.h"


// CShowInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CShowInfoDlg, CDialog)

CShowInfoDlg::CShowInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowInfoDlg::IDD, pParent)
	, strMessage(_T(""))
	, strKey(_T(""))
	, iDB_FS(0)
{

}

CShowInfoDlg::~CShowInfoDlg()
{
}

void CShowInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MESSAGE, strMessage);
	DDX_Control(pDX, IDC_COMBO_KEY_LIST, ctrlKeyList);
	DDX_Control(pDX, IDC_COMBO_DFS_OR_BFS, ctrlDB_FS);
	DDX_CBIndex(pDX, IDC_COMBO_DFS_OR_BFS, iDB_FS);
}


BEGIN_MESSAGE_MAP(CShowInfoDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DFS_OR_BFS, &CShowInfoDlg::OnChange)
	ON_CBN_SELCHANGE(IDC_COMBO_KEY_LIST, &CShowInfoDlg::OnChangeKey)
END_MESSAGE_MAP()


// CShowInfoDlg ��Ϣ�������

BOOL CShowInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	ctrlDB_FS.AddString("�������");
	ctrlDB_FS.AddString("�������");
	ctrlDB_FS.SetCurSel(0);
	for (int i=0 ;i<MAX_VERTEX_NUM;i++)
	{
		if (OrthGrap.xlist[i].m_bUsed)
		{
			ctrlKeyList.AddString(OrthGrap.xlist[i].data.key);
		}
	}

	if (strKey!="")
	{
		UpdateMessage();
		int  index = ctrlKeyList.FindString( -1 ,strKey);
		if(index!=-1)
			ctrlKeyList.SetCurSel(index);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CShowInfoDlg::OnChange()
{
	UpdateData();
	iDB_FS   =   ctrlDB_FS.GetCurSel(); 
	if( iDB_FS   ==   CB_ERR)   
		return; 
	UpdateMessage();
}

void CShowInfoDlg::UpdateMessage(void)
{
	int pos = OrthGrap.LocateVex(strKey);
	if ( pos != -1 )
	{
		if ( iDB_FS == 0 )
		{
			SetWindowText("������ȱ�������");
			strMessage = OrthGrap.DFSVisitOrder( pos );
		}
		else
		{
			SetWindowText( "������ȱ�������" );
			strMessage = OrthGrap.BFSVisitOrder( pos );
		}
		UpdateData(FALSE);
	}

}

void CShowInfoDlg::OnChangeKey()
{
	UpdateData();
	int   nSel   =   ctrlKeyList.GetCurSel();   
	if(nSel   ==   CB_ERR)   
		return;   
	ctrlKeyList.GetLBText(nSel,strKey); 
	UpdateMessage();
}
