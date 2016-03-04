// GraphicsAlgorithmDoc.h : interface of the CGraphicsAlgorithmDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSALGORITHMDOC_H__58CBEE2B_854F_11D8_B394_00E04C391319__INCLUDED_)
#define AFX_GRAPHICSALGORITHMDOC_H__58CBEE2B_854F_11D8_B394_00E04C391319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphicsAlgorithmDoc : public CDocument
{
protected: // create from serialization only
	CGraphicsAlgorithmDoc();
	DECLARE_DYNCREATE(CGraphicsAlgorithmDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsAlgorithmDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicsAlgorithmDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsAlgorithmDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSALGORITHMDOC_H__58CBEE2B_854F_11D8_B394_00E04C391319__INCLUDED_)
