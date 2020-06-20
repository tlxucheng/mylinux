#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CShortPathDlg �Ի���

class CShortPathDlg : public CDialog
{
	DECLARE_DYNAMIC(CShortPathDlg)

public:
	CShortPathDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShortPathDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHORT_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl ctrlShortPathList;
	CComboBox ctrlBeginKeyCombo;
	CString key;
	void UpdateInfo(CString key);
	afx_msg void OnCbnSelchangeComboKey();
	afx_msg void OnNMDblclkListShortPath(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void PostNcDestroy();
public:
	void InitCtrl(void);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonMiniSize();
};
