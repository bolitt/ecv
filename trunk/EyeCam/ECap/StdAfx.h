// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CD6296E8_D42D_4CE0_88F9_CA2348669D59__INCLUDED_)
#define AFX_STDAFX_H__CD6296E8_D42D_4CE0_88F9_CA2348669D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <string>
#include <iostream>

// HQDL headers:
#include <HQDL/DataType.h>
#include <HQDL/HQDLAPIUser.h>

// xercesc headers:
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

// Common header:
#include "Converter.h"
#include "Common.h"

#define MAXWIDTH     2048
#define MAXHEIGHT    1536
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CD6296E8_D42D_4CE0_88F9_CA2348669D59__INCLUDED_)
