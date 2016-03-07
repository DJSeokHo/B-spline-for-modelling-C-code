// 3D_view_FPbody_modelView.h : interface of the CMy3D_view_FPbody_modelView class
//
/////////////////////////////////////////////////////////////////////////////
#include "m_coordinate.h"
#include "Operat.h"
#include "NumForIndex.h"

#if !defined(AFX_3D_VIEW_FPBODY_MODELVIEW_H__68DE8BB9_D47C_47FE_8C6B_27F70938B5A6__INCLUDED_)
#define AFX_3D_VIEW_FPBODY_MODELVIEW_H__68DE8BB9_D47C_47FE_8C6B_27F70938B5A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy3D_view_FPbody_modelView : public CView
{
protected: // create from serialization only
	CMy3D_view_FPbody_modelView();
	DECLARE_DYNCREATE(CMy3D_view_FPbody_modelView)

// Attributes
public:
	CMy3D_view_FPbody_modelDoc* GetDocument();

	double rad;
	
	Operat *OPRT;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3D_view_FPbody_modelView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Create2DTextLists();
	float DrawSpaceSize;
	BOOL sheerYESNO;

	void DrawCoordinate();
	void RenderScene();
	GLdouble Real_Ortho_ViewPort_Ratio;
	HGLRC m_hRC;
	BOOL SetupPixelFormat();
	CDC* m_pDC;
	BOOL InitializeOpenGL();
	
	m_coordinate *mcoordinate;

	virtual ~CMy3D_view_FPbody_modelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GLuint m_2DTextList;
// Generated message map functions
protected:
	//{{AFX_MSG(CMy3D_view_FPbody_modelView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKslopeYes();
	afx_msg void OnKslopeNo();
	afx_msg void OnStartchange();
	afx_msg void OnEndchange();
	afx_msg void OnAllBp();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int xyPointIndex, yzPointIndex, xzPointIndex;
	int xyLineIndex, yzLineIndex, xzLineIndex;
};

#ifndef _DEBUG  // debug version in 3D_view_FPbody_modelView.cpp
inline CMy3D_view_FPbody_modelDoc* CMy3D_view_FPbody_modelView::GetDocument()
   { return (CMy3D_view_FPbody_modelDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3D_VIEW_FPBODY_MODELVIEW_H__68DE8BB9_D47C_47FE_8C6B_27F70938B5A6__INCLUDED_)
