#pragma once
#include "afxwin.h"


// CShowInfoDlg �Ի���
//	��ʾ������Ȼ��������������еĶԻ���

class CShowInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowInfoDlg)

public:
	CShowInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowInfoDlg();

// �Ի�������
	enum { IDD = IDD_SHOW_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	//��������
	CString strMessage;
public:
	//������ʽ��Ͽ�
	CComboBox ctrlDB_FS;
public:
	//�ؼ�����Ͽ�
	CComboBox ctrlKeyList;
public:
	//�ؼ��ֵ�ǰ
	CString strKey;
public:
	//������ʽ
	int iDB_FS;

public:
	//���±�������
	void UpdateMessage(void);

public:
	afx_msg void OnChangeKey();
public:
	afx_msg void OnChange();

};
