// UdpSocket.cpp : implementation file
//

#include "stdafx.h"
#include "UDP.h"
#include "UdpSocket.h"
#include "UDPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
	if (INVALID_SOCKET != this->m_hSocket)
	{
		Close();
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMySocket member functions

void CMySocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	TCHAR recBuf[1024];
	int len = sizeof(SOCKADDR_IN);
	CString recv_msg;

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
		//CString strBuf;
		//strBuf.Format(TEXT("�յ�����: %s"),  recBuf);
		//AfxMessageBox(strBuf, MB_OK);

        //((CUDPDlg*)theApp.GetMainWnd())->SetDlgItemTextW(IDC_DATATORECV, recBuf);
		((CUDPDlg*)(AfxGetApp()->m_pMainWnd))->GetDlgItem(IDC_DATATORECV)->SetWindowText(recBuf);
	}


	CSocket::OnReceive(nErrorCode);
}

void CMySocket::OnConnect(int nErrorCode)                                          
{
   if (0 != nErrorCode)
   {
      switch (nErrorCode)
      {
      case WSAEADDRINUSE:
         AfxMessageBox(_T("��ָ���ĵ�ַ�ѱ�ʹ��"));
         break;
      case WSAEADDRNOTAVAIL:
         AfxMessageBox(_T("��ָ���ĵ�ַ�ӱ��ؼ����������"));
         break;
      case WSAEAFNOSUPPORT:
         AfxMessageBox(_T("��ָ����ַ���ܶԸ��׽���"));
         break;
      case WSAECONNREFUSED:
         AfxMessageBox(_T("�ڳ������ӱ��ܾ�"));
         break;
      case WSAEDESTADDRREQ:
         AfxMessageBox(_T("��ҪĿ���ַ"));
         break;
      case WSAEFAULT:
         AfxMessageBox(_T("��������ȷ"));
         break;
      case WSAEINVAL:
         AfxMessageBox(_T("��Ч������ַ"));
         break;
      case WSAEISCONN:
         AfxMessageBox(_T("�׽���������"));
         break;
      case WSAEMFILE:
         AfxMessageBox(_T("û�������ļ�������������"));
         break;
      case WSAENETUNREACH:
         AfxMessageBox(_T("�����޷���Ŀǰ����Ϊֹ"));
         break;
      case WSAENOBUFS:
         AfxMessageBox(_T("û�л������ռ����"));
         break;
      case WSAENOTCONN:
         AfxMessageBox(_T("�׽���������"));
         break;
      case WSAENOTSOCK:
         AfxMessageBox(_T("�����������׽���"));
         break;
      case WSAETIMEDOUT:
         AfxMessageBox(_T("�������ӳ�ʱ"));
         break;
      default:
         TCHAR szError[256];
         _stprintf_s(szError, _T("OnConnect error: %d"), nErrorCode);
         AfxMessageBox(szError);
         break;
      }
      //AfxMessageBox(_T("Please close the application"));
   }
   CAsyncSocket::OnConnect(nErrorCode);
}