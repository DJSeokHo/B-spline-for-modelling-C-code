// LWidth.cpp : implementation file
//

#include "stdafx.h"
#include "GraphicsAlgorithm.h"
#include "LWidth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LWidth dialog


LWidth::LWidth(CWnd* pParent /*=NULL*/)
	: CDialog(LWidth::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWidth)
	m_LWidth = 3;
	//}}AFX_DATA_INIT
}


void LWidth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWidth)
	DDX_Text(pDX, IDC_EDIT1, m_LWidth);
	DDV_MinMaxInt(pDX, m_LWidth, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWidth, CDialog)
	//{{AFX_MSG_MAP(LWidth)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWidth message handlers
