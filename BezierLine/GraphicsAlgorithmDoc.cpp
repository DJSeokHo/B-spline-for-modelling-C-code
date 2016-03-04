// GraphicsAlgorithmDoc.cpp : implementation of the CGraphicsAlgorithmDoc class
//

#include "stdafx.h"
#include "GraphicsAlgorithm.h"

#include "GraphicsAlgorithmDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmDoc

IMPLEMENT_DYNCREATE(CGraphicsAlgorithmDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicsAlgorithmDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphicsAlgorithmDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmDoc construction/destruction

CGraphicsAlgorithmDoc::CGraphicsAlgorithmDoc()
{
	// TODO: add one-time construction code here

}

CGraphicsAlgorithmDoc::~CGraphicsAlgorithmDoc()
{
}

BOOL CGraphicsAlgorithmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmDoc serialization

void CGraphicsAlgorithmDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmDoc diagnostics

#ifdef _DEBUG
void CGraphicsAlgorithmDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicsAlgorithmDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmDoc commands
