// ad.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ad.h"
#include "MainFrm.h"

#include "adDoc.h"
#include "adView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CadApp

BEGIN_MESSAGE_MAP(CadApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CadApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CadApp ����

CadApp::CadApp()
{
}

CadApp::~CadApp()
{
	FreeLibrary(m_hModule);
}
// Ψһ��һ�� CadApp ����

CadApp theApp;
COrthListGrap OrthGrap;
CChildSiblingTree ChSibDFSTree;
CChildSiblingTree ChSibBFSTree;
CAdjMatrixGrap AdjMatrixGrap;
CString fileName = "";
CShortPathDlg* pShortPathDlg = NULL;

CadView *pView;

void CadApp::InitSkin()
{
	CString strDLLName;
	CString strSknName;
	CHAR szSknName [ MAX_PATH ];
	if(ResToFile( IDR_SKIN_DLL,"DLL", strDLLName))
		if(ResToFile( IDR_SKIN,"SKN", strSknName))
		{
			m_hModule  = LoadLibrary ( strDLLName );
			FUNC pFunc = ( FUNC ) GetProcAddress ( theApp.m_hModule, "LoadSkin" );
			strcpy_s ( szSknName, strSknName );
			pFunc ( szSknName );
		}
}


bool CadApp::ResToFile(int ResID, CString ResKind, CString &fileName)
{
	HRSRC  res=::FindResource(NULL,  MAKEINTRESOURCE(ResID),  ResKind);
	HGLOBAL  gl=::LoadResource(NULL,res);
	LPVOID  lp=::LockResource(gl);   //  ���ң����أ�������Դ  
	
	char strFileName[MAX_PATH];
	GetTempPath(MAX_PATH,strFileName);
	GetTempFileName(strFileName,"Guo",0,strFileName);

	HANDLE fp=::CreateFile(strFileName,
		GENERIC_WRITE,
		FILE_SHARE_READ ,
		NULL,
		CREATE_ALWAYS, 
		0, 
		NULL);  

		DWORD aa;              
	if (!::WriteFile (fp,lp,::SizeofResource(AfxGetResourceHandle(),res),&aa,NULL))
	{
		return false;      //sizeofResource �õ���Դ�ļ��Ĵ�С 
	}

	::CloseHandle (fp);       //�رվ��
	::FreeResource (gl);     //�ͷ��ڴ�
	fileName = strFileName;
	return true;
}



// CadApp ��ʼ��

BOOL CadApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	CWinApp::InitInstance();

	InitSkin();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Grap_GuoYukun_jk071"));
	  
	// ���ر�׼ INI �ļ�ѡ��(���� MRU)
	LoadStdProfileSettings(4); 
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CadDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CadView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	COleObjectFactory::UpdateRegistryAll();
	
	
	//ɾ���Ҽ��½���
	RegDeleteKey(HKEY_CLASSES_ROOT,_T(".grs\\ShellNew"));
	
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);   

	fileName=cmdInfo.m_strFileName;   
	if(fileName!="")   
	{   
		cmdInfo.m_nShellCommand=CCommandLineInfo::FileNew;   
	}   

	//   Dispatch   commands   specified   on   the   command   line   
	if   (!ProcessShellCommand(cmdInfo))   
		return   FALSE;   


	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���

	
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CadApp ��Ϣ�������


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

CDocument* CadApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
  /*
	CFileFind finder;
	if(finder.FindFile(lpszFileName))
	{

		
		if(AdjMatrixGrap.CreateFromFile(lpszFileName))
		{
			if ( pView->iViewMode != GRAP_VIEW )
			{
				pView->OnMenuOrthlistGrap();
			}
			OrthGrap.CreateOrthListFromMatrix();
			ChSibBFSTree.bNeedChange = true;
			ChSibDFSTree.bNeedChange = true;
			pView->Invalidate();
		}

		return ((CFrameWnd *)this->m_pMainWnd)->GetActiveView()->GetDocument();
	}
	else
	{
		MessageBox(NULL,_T("�ļ������ڣ�"),_T("�ļ��򿪴���"),MB_OK);
		return NULL;
	}
	*/
	return CWinApp::OpenDocumentFile(lpszFileName);
}

