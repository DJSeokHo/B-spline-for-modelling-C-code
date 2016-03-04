// SelPoint.cpp : implementation file
//

#include "stdafx.h"
#include "GraphicsAlgorithm.h"
#include "SelPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelPoint dialog


SelPoint::SelPoint(CWnd* pParent /*=NULL*/)
	: CDialog(SelPoint::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelPoint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SelPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelPoint)
	DDX_Control(pDX, IDC_LIST1, m_PointNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelPoint, CDialog)
	//{{AFX_MSG_MAP(SelPoint)
	ON_WM_CLOSE()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelPoint message handlers



BOOL SelPoint::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
 	char tt[2];
 	int i;
 	m_PointNumber.ResetContent();
 	for(i=0;i<SelNum;i++)
 		m_PointNumber.AddString(itoa(i,tt,10));//
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SelPoint::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	SelNum=m_PointNumber.GetCurSel();
	CDialog::OnClose();
}

void SelPoint::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
		SelNum=m_PointNumber.GetCurSel();

}
