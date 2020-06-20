// DlgAddVex.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ad.h"
#include "AddVexDlg.h"


// CAddVexDlg �Ի���

IMPLEMENT_DYNAMIC(CAddVexDlg, CDialog)

CAddVexDlg::CAddVexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddVexDlg::IDD, pParent)
	, m_strKey(_T(""))
	, strMoreInfo(_T("��ע����"))
{

}

CAddVexDlg::~CAddVexDlg()
{
}

void CAddVexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KEY, m_strKey);
	DDX_Text(pDX, IDC_MORE_INFO, strMoreInfo);
}


BEGIN_MESSAGE_MAP(CAddVexDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddVexDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCLE, &CAddVexDlg::OnBnClickedCancle)
END_MESSAGE_MAP()


// CAddVexDlg ��Ϣ�������


void CAddVexDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_strKey.Replace(" ","");
	m_strKey.Replace("-","");
	if (!(m_strKey == ""))
		OnOK();
}

void CAddVexDlg::OnBnClickedCancle()
{
	OnCancel();
}
