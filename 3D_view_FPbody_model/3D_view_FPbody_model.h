// 3D_view_FPbody_model.h : main header file for the 3D_VIEW_FPBODY_MODEL application
//

#if !defined(AFX_3D_VIEW_FPBODY_MODEL_H__3AA31049_DAC5_4875_8D71_E3C49F368CE9__INCLUDED_)
#define AFX_3D_VIEW_FPBODY_MODEL_H__3AA31049_DAC5_4875_8D71_E3C49F368CE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelApp:
// See 3D_view_FPbody_model.cpp for the implementation of this class
//

class CMy3D_view_FPbody_modelApp : public CWinApp
{
public:
	CMy3D_view_FPbody_modelApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3D_view_FPbody_modelApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy3D_view_FPbody_modelApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3D_VIEW_FPBODY_MODEL_H__3AA31049_DAC5_4875_8D71_E3C49F368CE9__INCLUDED_)
