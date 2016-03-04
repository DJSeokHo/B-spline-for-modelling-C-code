// GraphicsAlgorithmView.h : interface of the CGraphicsAlgorithmView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSALGORITHMVIEW_H__58CBEE2D_854F_11D8_B394_00E04C391319__INCLUDED_)
#define AFX_GRAPHICSALGORITHMVIEW_H__58CBEE2D_854F_11D8_B394_00E04C391319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphicsAlgorithmView : public CView
{
protected: // create from serialization only
	CGraphicsAlgorithmView();
	DECLARE_DYNCREATE(CGraphicsAlgorithmView)

// Attributes
public:
	CGraphicsAlgorithmDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsAlgorithmView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CPen CurPen1;
	CPoint PreP1;
	CPoint BegP1;
	void TT();
	int GDS;
	void cls();
	CPoint Bezier(float t);
	CPoint Contp1[100];
	COLORREF FillColor;
	int PNum;
	CPoint ContP[1000];
	COLORREF Curcolor;
	void FloodFill4(CPoint SeedP, COLORREF FillColor, COLORREF BdColor);
	int FunSel;
	CPen OrgPen;
	CPen CurPen;
	CClientDC *Gra;
	bool MouDown;
	CPoint PreP;
	CPoint BegP;
	virtual ~CGraphicsAlgorithmView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsAlgorithmView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnidCurColor();
	afx_msg void OnidClear();
	afx_msg void OnidPolygon();
	afx_msg void OnidSetPolygon();
	afx_msg void OnClose();
	afx_msg void OnidFillColor();
	afx_msg void OnidLineWidth();
	afx_msg void Onidabout();
	afx_msg void Onsqx();
	afx_msg void Onfirst();
	afx_msg void Onlast();
	afx_msg void Onnotnext();
	afx_msg void Onnext();
	afx_msg void OnSelPoint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void Onch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GraphicsAlgorithmView.cpp
inline CGraphicsAlgorithmDoc* CGraphicsAlgorithmView::GetDocument()
   { return (CGraphicsAlgorithmDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSALGORITHMVIEW_H__58CBEE2D_854F_11D8_B394_00E04C391319__INCLUDED_)
