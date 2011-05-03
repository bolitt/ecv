// ECap.h : main header file for the ECap application
//

#if !defined(AFX_ECAP_H__26F7522B_4704_4C9F_8577_5C617CD05CA6__INCLUDED_)
#define AFX_ECAP_H__26F7522B_4704_4C9F_8577_5C617CD05CA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// ECapApp:
// See ECap.cpp for the implementation of this class
//

class ECapApp : public CWinApp
{
public:
	ECapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ECapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(ECapApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECAP_H__26F7522B_4704_4C9F_8577_5C617CD05CA6__INCLUDED_)
