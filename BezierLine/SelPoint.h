#if !defined(AFX_SELPOINT_H__DE904A01_921B_11D8_B394_00E04C391319__INCLUDED_)
#define AFX_SELPOINT_H__DE904A01_921B_11D8_B394_00E04C391319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelPoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelPoint dialog

class SelPoint : public CDialog
{
// Construction
public:
	int SelNum;
	SelPoint(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelPoint)
	enum { IDD = IDD_DIALOG_SelPoint };
	CListBox	m_PointNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelPoint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelPoint)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSelchangeList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELPOINT_H__DE904A01_921B_11D8_B394_00E04C391319__INCLUDED_)
