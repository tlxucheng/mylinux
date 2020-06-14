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
		AfxMessageBox(TEXT("UDP连接已经关闭!"));
	}
	else if (SOCKET_ERROR == recBytes)
	{
		AfxMessageBox(TEXT("接受数据失败!"));
	}
	else
	{
		//CString strBuf;
		//strBuf.Format(TEXT("收到数据: %s"),  recBuf);
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
         AfxMessageBox(_T("所指定的地址已被使用"));
         break;
      case WSAEADDRNOTAVAIL:
         AfxMessageBox(_T("所指定的地址从本地计算机不可用"));
         break;
      case WSAEAFNOSUPPORT:
         AfxMessageBox(_T("所指定地址不能对该套接字"));
         break;
      case WSAECONNREFUSED:
         AfxMessageBox(_T("在尝试连接被拒绝"));
         break;
      case WSAEDESTADDRREQ:
         AfxMessageBox(_T("需要目标地址"));
         break;
      case WSAEFAULT:
         AfxMessageBox(_T("参数不正确"));
         break;
      case WSAEINVAL:
         AfxMessageBox(_T("无效主机地址"));
         break;
      case WSAEISCONN:
         AfxMessageBox(_T("套接字已连接"));
         break;
      case WSAEMFILE:
         AfxMessageBox(_T("没有其他文件描述符不可用"));
         break;
      case WSAENETUNREACH:
         AfxMessageBox(_T("网络无法从目前的宿为止"));
         break;
      case WSAENOBUFS:
         AfxMessageBox(_T("没有缓冲区空间可用"));
         break;
      case WSAENOTCONN:
         AfxMessageBox(_T("套接字已连接"));
         break;
      case WSAENOTSOCK:
         AfxMessageBox(_T("描述符不是套接字"));
         break;
      case WSAETIMEDOUT:
         AfxMessageBox(_T("尝试连接超时"));
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