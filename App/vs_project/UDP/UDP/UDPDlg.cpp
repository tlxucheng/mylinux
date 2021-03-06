// UDPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UDP.h"
#include "UDPDlg.h"

#include "amqp.h"
#include "amqp_tcp_socket.h"
#include "stdint.h"

#include <iostream>
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib,"rabbitmq.4.lib")

#define T_UDP                      0
#define T_TCP                      1
#define T_TLS                      2
#define T_SCTP                     3

#define T_RABBITMQ                 10

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDPDlg dialog

CUDPDlg::CUDPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUDPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUDPDlg)
	m_localPortNum = 1234;
    m_peerPortNum = 5672;  /* TCP/UDP 5060 */
	m_dataToSend = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSocket = NULL;
	m_bIsConnected = FALSE;
}

void CUDPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUDPDlg)
	DDX_Control(pDX, IDC_PEERIPADDR, m_peerIPaddr);
	DDX_Control(pDX, IDC_LOCALIPADDR, m_localIPaddr);
	DDX_Text(pDX, IDC_LOCALPORTNUM, m_localPortNum);
	DDX_Text(pDX, IDC_PEERPORTNUM, m_peerPortNum);
	DDX_Text(pDX, IDC_DATATOSEND, m_dataToSend);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO1, m_comboTrantype);
	DDX_Control(pDX, IDC_EXCHANGE, m_exchange);
	DDX_Control(pDX, IDC_ROUTINGKEY, m_routingkey);
	DDX_Control(pDX, IDC_RMQUSER, m_RmqUser);
	DDX_Control(pDX, IDC_RMQPWD, m_RmqPwd);
}

BEGIN_MESSAGE_MAP(CUDPDlg, CDialog)
	//{{AFX_MSG_MAP(CUDPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNSENDDATA, OnBtnSendData)
	ON_BN_CLICKED(IDC_BTNCTRLCONN, OnBtnCtrlConn)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUDPDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDPDlg message handlers

BOOL CUDPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	AfxSocketInit();	

	m_peerIPaddr.SetAddress(192,168,0,105);
	m_localIPaddr.SetAddress(192,168,0,107);

    m_comboTrantype.AddString(_T("UDP"));
    m_comboTrantype.AddString(_T("TCP"));
    m_comboTrantype.AddString(_T("TLS"));
    m_comboTrantype.AddString(_T("RABBITMQ"));
    m_comboTrantype.SetCurSel(1);  

	GetDlgItem(IDC_DATATOSEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNSENDDATA)->EnableWindow(FALSE);

    GetDlgItem(IDC_EXCHANGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ROUTINGKEY)->EnableWindow(FALSE);

    GetDlgItem(IDC_RMQUSER)->EnableWindow(FALSE);
	GetDlgItem(IDC_RMQPWD)->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUDPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUDPDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUDPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUDPDlg::OnBtnSendData() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

    if(0)
	{
		if (NULL == m_pSocket || !m_bIsConnected)
		{
			AfxMessageBox(TEXT("尚未打开端口!"));
			return;
		}
		else if (m_dataToSend.IsEmpty())
		{
			AfxMessageBox(TEXT("请在编辑框中输入要发送的数据!"));
			return;
		}
		
		m_pSocket->SendTo(m_dataToSend, m_dataToSend.GetLength(), 
								 m_peerPortNum, m_strPeerIPaddr);
	}
	else
	{
		test_rabbitmq();
	}
}

void CUDPDlg::SetTransport(CString strbox)
{
    if("UDP" == strbox)
	{
		m_pTranport = T_UDP;
	}
	else if("TCP" == strbox)
	{
		m_pTranport = T_TCP;
	}
	else if("TLS" == strbox)
	{
		m_pTranport = T_TLS;
	}
	else if("RABBITMQ" == strbox)
	{
		m_pTranport = T_RABBITMQ;
	}
	else
	{
	}

	return;
}

void CUDPDlg::test_rabbitmq()
{
	//char const hostname[64] = "192.168.0.108";
	//int port = 5672;
    //int status;
	char exchange[64] = {0};
	char routingkey[64] = {0};
	char rmq_user[64] = {0};
	char rmq_pwd[64] = {0};
	//char const messagebody[128] = "MFC RabbitMQ Client Test";
	amqp_socket_t *socket = NULL;
	amqp_connection_state_t conn;

	conn = amqp_new_connection();
	socket = amqp_tcp_socket_new(conn);

	if(!socket){
		//cout << "create socket failed!";
		//exit(1);
	}

	BYTE field[4];
		
	m_peerIPaddr.GetAddress(field[0], field[1], field[2], field[3]);
	m_strPeerIPaddr.Format(TEXT("%d.%d.%d.%d"), field[0], field[1], field[2], field[3]);

    m_exchange.GetWindowText(exchange, sizeof(exchange));
    m_routingkey.GetWindowText(routingkey, sizeof(routingkey));

    m_RmqUser.GetWindowText(rmq_user, sizeof(rmq_user));
    m_RmqPwd.GetWindowText(rmq_pwd, sizeof(rmq_pwd));

	if(amqp_socket_open(socket, m_strPeerIPaddr, m_peerPortNum)){

		//cout << "opening TCP socket failed" << endl;
		//exit(1);
	}
	if(1 != amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, rmq_user, rmq_pwd).reply_type){

		//cout << "login failed" << endl;
	}

	amqp_channel_open(conn, 1);

    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    props.content_type = amqp_cstring_bytes("text/plain");
    props.delivery_mode = 2; /* persistent delivery mode */
	amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange),amqp_cstring_bytes(routingkey), 0, 0,
		               &props, amqp_cstring_bytes(m_dataToSend));


#if 0 
	char message[1024] = {"MFC RabbitMQ Client Test\n"};
	amqp_bytes_t  message_bytes;
	message_bytes.len = sizeof(message);
	message_bytes.bytes = message;

	amqp_basic_publish(conn, 1, amqp_cstring_bytes(""), amqp_cstring_bytes("test_simple_queue"), 0, 0, NULL, message_bytes);
#endif
	//cout << "send msg over!" << endl;

	return;
}

void CUDPDlg::OnBtnCtrlConn() 
{
	// TODO: Add your control notification handler code here
	CString strbox;
	int nSel;
    int ret = 0;

	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_comboTrantype.GetCurSel();
    m_comboTrantype.GetLBText(nSel, strbox);
	//AfxMessageBox(TEXT(strbox));
   
	SetTransport(strbox);

	if (NULL != m_pSocket)
	{
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket = NULL;
	}

	if (!m_bIsConnected)
	{
		//m_bIsConnected = TRUE;

		UpdateData(TRUE); /* 将控件中输入的值更新到变量中 */
		
		BYTE field[4];
		
		m_peerIPaddr.GetAddress(field[0], field[1], field[2], field[3]);
		
		m_strPeerIPaddr.Format(TEXT("%d.%d.%d.%d"),
			field[0], field[1], field[2], field[3]);
		
		if(T_UDP == m_pTranport)
		{
			m_pSocket = new CMySocket();
			ret = m_pSocket->Create(m_localPortNum, SOCK_DGRAM);
			//ret = m_pSocket->Bind(m_peerPortNum, m_strPeerIPaddr);
			if(0 == ret)
			{
				AfxMessageBox(TEXT("创建udp socket失败!"));
			}
			else
			{
				AfxMessageBox(TEXT("创建udp socket成功!"));
				m_bIsConnected = TRUE;
			    GetDlgItem(IDC_BTNCTRLCONN)->SetWindowText(TEXT("断开连接"));
			}
		}
		else if(T_TCP == m_pTranport)
	    {
			m_pSocket = new CMySocket();
            m_pSocket->Create(m_localPortNum);
			m_pSocket->Bind(m_peerPortNum, m_strPeerIPaddr);
			ret = m_pSocket->Connect(m_strPeerIPaddr, m_peerPortNum);
			if(0 == ret)
			{
				//AfxMessageBox(TEXT("连接失败"));
				m_pSocket->OnConnect(GetLastError());
				//DWORD nErrno = GetLastError();
			}
			else
			{
				AfxMessageBox(TEXT("连接成功"));
                m_bIsConnected = TRUE;
				GetDlgItem(IDC_BTNCTRLCONN)->SetWindowText(TEXT("断开连接"));
			}
		}	
	}
	else
	{
		m_bIsConnected = FALSE;
		GetDlgItem(IDC_BTNCTRLCONN)->SetWindowText(TEXT("建立连接"));
	}

	GetDlgItem(IDC_LOCALPORTNUM)->EnableWindow(!m_bIsConnected);
	GetDlgItem(IDC_LOCALIPADDR)->EnableWindow(!m_bIsConnected);
	GetDlgItem(IDC_PEERPORTNUM)->EnableWindow(!m_bIsConnected);
	GetDlgItem(IDC_PEERIPADDR)->EnableWindow(!m_bIsConnected);	
	GetDlgItem(IDC_BTNSENDDATA)->EnableWindow(m_bIsConnected);
	GetDlgItem(IDC_DATATOSEND)->EnableWindow(m_bIsConnected);

	GetDlgItem(IDC_COMBO1)->EnableWindow(!m_bIsConnected);
}

void CUDPDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strbox;
	int nSel;
	//获取组合框控件的列表框中选中项的索引   
	nSel = m_comboTrantype.GetCurSel();
	// 根据选中项索引获取该项字符串   
	m_comboTrantype.GetLBText(nSel, strbox);
    //AfxMessageBox(TEXT(strbox));

	SetTransport(strbox);

	if(m_pTranport == T_RABBITMQ)
	{
		GetDlgItem(IDC_LOCALPORTNUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_LOCALIPADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_PEERPORTNUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_PEERIPADDR)->EnableWindow(TRUE);	

		GetDlgItem(IDC_BTNCTRLCONN)->EnableWindow(FALSE);

		GetDlgItem(IDC_BTNSENDDATA)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATATOSEND)->EnableWindow(TRUE);

		GetDlgItem(IDC_EXCHANGE)->EnableWindow(TRUE);
	    GetDlgItem(IDC_ROUTINGKEY)->EnableWindow(TRUE);

		GetDlgItem(IDC_RMQUSER)->EnableWindow(TRUE);
	    GetDlgItem(IDC_RMQPWD)->EnableWindow(TRUE);

		m_peerIPaddr.SetAddress(192,168,0,108);
		// m_peerPortNum = 5672; //不起作用
		/*
        m_exchange.SetWindowTextA("amq.direct");
        m_routingkey.SetWindowTextA("test");
        */

		m_exchange.SetWindowTextA("ccm_extgbal_xc_test");
        m_routingkey.SetWindowTextA("ccm_extspec_xc_test_0");

        m_RmqUser.SetWindowTextA("admin");
        m_RmqPwd.SetWindowTextA("123456");
	}
	else
	{
		GetDlgItem(IDC_LOCALPORTNUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_LOCALIPADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_PEERPORTNUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_PEERIPADDR)->EnableWindow(TRUE);	

		GetDlgItem(IDC_BTNCTRLCONN)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTNSENDDATA)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATATOSEND)->EnableWindow(FALSE);

	    GetDlgItem(IDC_EXCHANGE)->EnableWindow(FALSE);
	    GetDlgItem(IDC_ROUTINGKEY)->EnableWindow(FALSE);
	}
}
