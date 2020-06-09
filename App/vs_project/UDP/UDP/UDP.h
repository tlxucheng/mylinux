// UDP.h : main header file for the UDP application
//

#if !defined(AFX_UDP_H__89E46553_4FCE_41CE_B122_952A7CE3C34D__INCLUDED_)
#define AFX_UDP_H__89E46553_4FCE_41CE_B122_952A7CE3C34D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUDPApp:
// See UDP.cpp for the implementation of this class
//

class CUDPApp : public CWinApp
{
public:
	CUDPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUDPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDP_H__89E46553_4FCE_41CE_B122_952A7CE3C34D__INCLUDED_)
