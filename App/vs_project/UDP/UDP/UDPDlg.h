// UDPDlg.h : header file
//

#if !defined(AFX_UDPDLG_H__33A34A35_42F8_4C9E_AE7D_F9145790A952__INCLUDED_)
#define AFX_UDPDLG_H__33A34A35_42F8_4C9E_AE7D_F9145790A952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UdpSocket.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CUDPDlg dialog

class CUDPDlg : public CDialog
{
// Construction
public:
	CUDPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUDPDlg)
	enum { IDD = IDD_UDP_DIALOG };
	CIPAddressCtrl	m_peerIPaddr;
	CIPAddressCtrl	m_localIPaddr;
	UINT	m_localPortNum;
	UINT	m_peerPortNum;
	CString	m_dataToSend;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	CUdpSocket *m_pSocket;
	CString m_strPeerIPaddr;
	BOOL m_bIsConnected;
	// Generated message map functions
	//{{AFX_MSG(CUDPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSendData();
	afx_msg void OnBtnCtrlConn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboTrantype;
	afx_msg void OnCbnSelchangeCombo1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPDLG_H__33A34A35_42F8_4C9E_AE7D_F9145790A952__INCLUDED_)
