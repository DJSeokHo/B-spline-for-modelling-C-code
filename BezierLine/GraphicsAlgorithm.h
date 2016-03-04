// GraphicsAlgorithm.h : main header file for the GRAPHICSALGORITHM application
//

#if !defined(AFX_GRAPHICSALGORITHM_H__58CBEE25_854F_11D8_B394_00E04C391319__INCLUDED_)
#define AFX_GRAPHICSALGORITHM_H__58CBEE25_854F_11D8_B394_00E04C391319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmApp:
// See GraphicsAlgorithm.cpp for the implementation of this class
//

class CGraphicsAlgorithmApp : public CWinApp
{
public:
	CGraphicsAlgorithmApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsAlgorithmApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGraphicsAlgorithmApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSALGORITHM_H__58CBEE25_854F_11D8_B394_00E04C391319__INCLUDED_)
