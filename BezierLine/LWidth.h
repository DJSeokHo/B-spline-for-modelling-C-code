#if !defined(AFX_LWIDTH_H__B8FCCAA1_8714_11D8_B394_00E04C391319__INCLUDED_)
#define AFX_LWIDTH_H__B8FCCAA1_8714_11D8_B394_00E04C391319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWidth.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWidth dialog

class LWidth : public CDialog
{
// Construction
public:
	LWidth(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LWidth)
	enum { IDD = IDD_DIALOG1 };
	int		m_LWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWidth)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LWidth)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWIDTH_H__B8FCCAA1_8714_11D8_B394_00E04C391319__INCLUDED_)
