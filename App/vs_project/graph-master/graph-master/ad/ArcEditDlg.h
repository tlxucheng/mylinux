#pragma once

#define KIND_ADD 0
#define KIND_DEL 1
#define KIND_FIND 2

// CArcEdit �Ի���
// ���� <��� ɾ�� ����> �Ի���


class CArcEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CArcEditDlg)

public:
	CArcEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CArcEditDlg();


// �Ի�������
	enum { IDD = IDD_DIALOG_ARC_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()


public:
	//�ؼ���һ
	CString strFirKey;
public:
	//�ؼ��ֶ�
	CString strSecKey;
public:
	//Ȩ��
	int uWeight;
public:
	//�Ի������� �� ��� ɾ�� ����
	int kindFlag;
public:
	//��ѡ��˫��ߵ�
	BOOL bDouble;


public:
	//���öԻ�������
	void SetKind( int kind );
public:
	afx_msg void OnBnClickedOk();
public:
	virtual BOOL OnInitDialog();

};
