#pragma once
#include "afxwin.h"

#define KIND_ADD 0
#define KIND_DEL 1
// CVexInfoDlg �Ի���
// ��ʾ������Ϣ�ĶԻ���


class CVexInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CVexInfoDlg)

public:
	CVexInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVexInfoDlg();

// �Ի�������
	enum { IDD = IDD_VEX_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();

public:
	//����ؼ���
	CString strKey;
public:
	//�Ի�������
	int kindFlag;
public:
	//���
	int iInDegree;
public:
	//����
	int iOutDegree;
public:
	//��ע
	CString strMoreInfo;
public:
	//�ؼ�����Ͽ�
	CComboBox ctrlKeyList;

public:
	//���¶�����Ϣ
	void UpdateInfo(CString key);

public:
	afx_msg void OnCbnSelchangeComboKeyList();

};
