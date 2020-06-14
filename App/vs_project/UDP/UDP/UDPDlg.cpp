// UDPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UDP.h"
#include "UDPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define T_UDP                      0
#define T_TCP                      1
#define T_TLS                      2
#define T_SCTP                     3

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
    m_peerPortNum = 5060;
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
    m_comboTrantype.SetCurSel(1);  

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
	else
	{
	}

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
			m_pSocket->Create(m_localPortNum, SOCK_DGRAM);
			m_pSocket->Bind(m_peerPortNum, m_strPeerIPaddr);
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
}

void CUDPDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString strbox;
	//int nSel;
	// 获取组合框控件的列表框中选中项的索引   
	//nSel = m_comboTrantype.GetCurSel();
	// 根据选中项索引获取该项字符串   
	//m_comboTrantype.GetLBText(nSel, strbox);
}
