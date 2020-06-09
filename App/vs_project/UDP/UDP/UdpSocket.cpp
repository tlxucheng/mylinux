// UdpSocket.cpp : implementation file
//

#include "stdafx.h"
#include "UDP.h"
#include "UdpSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket

CUdpSocket::CUdpSocket()
{
}

CUdpSocket::~CUdpSocket()
{
	if (INVALID_SOCKET != this->m_hSocket)
	{
		Close();
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUdpSocket, CSocket)
	//{{AFX_MSG_MAP(CUdpSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket member functions

void CUdpSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	TCHAR recBuf[1024];
	int len = sizeof(SOCKADDR_IN);

	ZeroMemory(recBuf, sizeof(recBuf));

	int recBytes = ReceiveFrom(recBuf, 1023, (SOCKADDR*)&m_clientAddr, &len, 0);

	if (0 == recBytes)
	{
		AfxMessageBox(TEXT("UDP�����Ѿ��ر�!"));
	}
	else if (SOCKET_ERROR == recBytes)
	{
		AfxMessageBox(TEXT("��������ʧ��!"));
	}
	else
	{
		CString strBuf;
		strBuf.Format(TEXT("�յ�����: %s"),  recBuf);
		AfxMessageBox(strBuf, MB_OK);		
	}

	CSocket::OnReceive(nErrorCode);
}
