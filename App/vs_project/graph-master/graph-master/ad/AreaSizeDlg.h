#pragma once


// CAreaSizeDlg �Ի���
// ���������С�ĶԻ���


class CAreaSizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CAreaSizeDlg)

public:
	CAreaSizeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAreaSizeDlg();

// �Ի�������
	enum { IDD = IDD_AREA_SIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//��
	UINT width;
public:
	//��
	UINT height;
public:
	//�Զ�����
	bool m_bAuto;

public:
	afx_msg void OnBnClickedAuto();
public:
	afx_msg void OnBnClickedOk();
};
