#pragma once



// CAddVexDlg �Ի���

class CAddVexDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddVexDlg)

public:
	CAddVexDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddVexDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADD_VEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//�ؼ���
	CString m_strKey;
public:
	afx_msg void OnBnClickedOk();
public:
	// ��ע
	CString strMoreInfo;
public:
	afx_msg void OnBnClickedCancle();
};
