#if !defined(AFX_UDPSOCKET_H__C62CE353_F46C_4090_A53B_8A37E097E514__INCLUDED_)
#define AFX_UDPSOCKET_H__C62CE353_F46C_4090_A53B_8A37E097E514__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UdpSocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySocket command target

class CMySocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CMySocket();
	virtual ~CMySocket();

	

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	
	SOCKADDR_IN m_clientAddr;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSOCKET_H__C62CE353_F46C_4090_A53B_8A37E097E514__INCLUDED_)
