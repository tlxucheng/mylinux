#pragma once
#include "afxcmn.h"


// CArcInfoDlg �Ի���
// ��ʾ����Ϣ�ĶԻ���

class CArcInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CArcInfoDlg)

public:
	CArcInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CArcInfoDlg();

// �Ի�������
	enum { IDD = IDD_ARC_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrlArcList;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
