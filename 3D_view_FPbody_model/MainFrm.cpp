// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "3D_view_FPbody_model.h"
#include "3D_view_FPbody_modelDoc.h"
#include "3D_view_FPbody_modelView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame


CMy3D_view_FPbody_modelView *p3D, *pBODY, *pHALF, *pSHEER, *StatusString;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	IsOnCreate = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!m_wndSplitterString.CreateStatic(this,3,1))
	{
		return FALSE;
	}
	m_wndSplitter.CreateStatic(&m_wndSplitterString,1,2,WS_CHILD|WS_VISIBLE|WS_BORDER, 
		m_wndSplitterString.IdFromRowCol(0,0));

	IsOnCreate = TRUE;
	CRect rect;
	GetClientRect(&rect);

	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CMy3D_view_FPbody_modelView),
        CSize(rect.Width()/10*6,rect.Height()),pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CMy3D_view_FPbody_modelView),
        CSize(rect.Width()/10*4,rect.Height()),pContext);

	m_wndSplitterString.CreateView(1,0,RUNTIME_CLASS(CMy3D_view_FPbody_modelView),
        CSize(rect.Width(),rect.Height()/10 * 3),pContext);
	m_wndSplitterString.CreateView(2,0,RUNTIME_CLASS(CMy3D_view_FPbody_modelView),
        CSize(rect.Width(),rect.Height()/10 * 3),pContext);

	p3D = (CMy3D_view_FPbody_modelView*)m_wndSplitter.GetPane(0, 0);  
    pBODY = (CMy3D_view_FPbody_modelView*)m_wndSplitter.GetPane(0, 1);  
    pHALF = (CMy3D_view_FPbody_modelView*)m_wndSplitterString.GetPane(1, 0);  
    pSHEER = (CMy3D_view_FPbody_modelView*)m_wndSplitterString.GetPane(2, 0);  
//	StatusString = (CMy3D_view_FPbody_modelView*)m_wndSplitterString.GetPane(0, 0);  

	return TRUE;
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect;  
    GetClientRect(&rect);  

	if(IsOnCreate==TRUE)
	{
		m_wndSplitter.SetRowInfo(0, rect.Height()/10*4, 0);
		m_wndSplitter.SetColumnInfo(0, rect.Width()/10*6, 0); 
		m_wndSplitter.SetColumnInfo(1, rect.Width()/10*4, 0); 

		m_wndSplitterString.SetRowInfo(0, rect.Height()/10*4.5, 0);
		m_wndSplitterString.SetRowInfo(1, rect.Height()/10*2.5, 0);
		m_wndSplitterString.SetRowInfo(2, rect.Height()/10*3, 0);
		m_wndSplitterString.RecalcLayout();  
		m_wndSplitter.RecalcLayout();
	}
}	

