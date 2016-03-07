// 3D_view_FPbody_modelView.cpp : implementation of the CMy3D_view_FPbody_modelView class
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
// CMy3D_view_FPbody_modelView
extern CMy3D_view_FPbody_modelView *p3D, *pBODY, *pHALF, *pSHEER, *StatusString;

IMPLEMENT_DYNCREATE(CMy3D_view_FPbody_modelView, CView)

BEGIN_MESSAGE_MAP(CMy3D_view_FPbody_modelView, CView)
	//{{AFX_MSG_MAP(CMy3D_view_FPbody_modelView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(SHOW_KSLOPE_YES, OnKslopeYes)
	ON_COMMAND(SHOW_KSLOPE_NO, OnKslopeNo)
	ON_COMMAND(KSLOPE_STARTCHANGE, OnStartchange)
	ON_COMMAND(KSLOPE_ENDCHANGE, OnEndchange)
	ON_COMMAND(INIT_ALL_BP, OnAllBp)
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelView construction/destruction

CMy3D_view_FPbody_modelView::CMy3D_view_FPbody_modelView()
{
	// TODO: add construction code here
	Real_Ortho_ViewPort_Ratio = 0.0;
	mcoordinate = (m_coordinate*)malloc(sizeof(m_coordinate));

	DrawSpaceSize = 100.0;

	OPRT = (Operat*)malloc(sizeof(Operat));
	
	rad = -0.5 * DrawSpaceSize;
	
	xyLineIndex = 0;
	yzLineIndex = 0;
	xzLineIndex = 0;

	xyPointIndex = 0;
	yzPointIndex = 0;
	xzPointIndex = 0;


	OPRT->Set_xRot(0.0);
	OPRT->Set_yRot(0.0);
	OPRT->Set_xMove(0.0);
	OPRT->Set_yMove(0.0);
	OPRT->Set_RBD(FALSE);
	OPRT->Set_LBD(FALSE);
	OPRT->Set_MMS(30.0);
	OPRT->Set_Scale(1.0);
	OPRT->Set_SHIFT(FALSE);
	OPRT->Set_CTRL(FALSE);
}

CMy3D_view_FPbody_modelView::~CMy3D_view_FPbody_modelView()
{
	free(mcoordinate);
}

BOOL CMy3D_view_FPbody_modelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelView drawing

void CMy3D_view_FPbody_modelView::OnDraw(CDC* pDC)
{
	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC); 
	// TODO: add draw code for native data here
	// Clear out the color & depth buffers
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glMatrixMode(GL_MODELVIEW);

	if(p3D == this)   
    {  
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		DrawCoordinate();
		OPRT->Set_MMS(100.0/DrawSpaceSize);
		glTranslatef(OPRT->Get_xMove()-DrawSpaceSize/2, OPRT->Get_yMove()-DrawSpaceSize/2, 0.0f);	
		glScalef(OPRT->Get_Scale(), OPRT->Get_Scale(), OPRT->Get_Scale());	
		glRotatef(-45+OPRT->Get_xRot(), 0.0f, 1.0f, 0.0f);
		glRotatef(-45+OPRT->Get_yRot(), 1.0f, 0.0f, 0.0f);

		RenderScene();
    }
    if(pBODY == this)  
    {  
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();

	//	glTranslatef(0.0f, OPRT->Get_yMove(), 0.0f);	
		glScalef(OPRT->Get_Scale()+DrawSpaceSize/20, OPRT->Get_Scale()+DrawSpaceSize/20, OPRT->Get_Scale()+DrawSpaceSize/20);
		
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		
		RenderScene();
		
		glLoadIdentity();
		glTranslatef(-DrawSpaceSize + 0.5f, -DrawSpaceSize + 0.8f, 0.0f);

		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(2.5);
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(DrawSpaceSize*0.2f,0.0f,0.0f);
		glEnd();
		
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,DrawSpaceSize*0.2,0.0f);	
		glEnd();

		glRasterPos2f(DrawSpaceSize*0.2f+0.2, 0.0f-0.3f);
		glListBase(m_2DTextList);
		glCallLists(1, GL_UNSIGNED_BYTE ,"z");

		glRasterPos2f(0.0f-0.2f, DrawSpaceSize*0.2f+0.2);
		glListBase(m_2DTextList);
		glCallLists(1, GL_UNSIGNED_BYTE ,"y");

		glPopMatrix();
		glLoadIdentity();
    }
    if(pHALF == this)  
    {  
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		sheerYESNO = FALSE;
//		glTranslatef(OPRT->Get_xMove()+DrawSpaceSize/2, OPRT->Get_yMove()-DrawSpaceSize/2, 0.0);		
		glScalef(OPRT->Get_Scale()+DrawSpaceSize/20, OPRT->Get_Scale()+DrawSpaceSize/20, OPRT->Get_Scale()+DrawSpaceSize/20);
//		glScalef(OPRT->Get_Scale(), OPRT->Get_Scale(), OPRT->Get_Scale());
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		
		RenderScene();
		
		glLoadIdentity();
		glTranslatef(-DrawSpaceSize + 0.5f, -DrawSpaceSize + 0.8f, 0.0f);

		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(2.5);
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(DrawSpaceSize*0.2f,0.0f,0.0f);
		glEnd();
		
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,DrawSpaceSize*0.2,0.0f);
			
		glEnd();

		glRasterPos2f(DrawSpaceSize*0.2f+0.2, 0.0f-0.3f);
		glListBase(m_2DTextList);
		glCallLists(1, GL_UNSIGNED_BYTE ,"x");

		glRasterPos2f(0.0f-0.1, DrawSpaceSize*0.2f+0.3f);
		glListBase(m_2DTextList);
		glCallLists(1, GL_UNSIGNED_BYTE ,"z");

		glPopMatrix();
		glLoadIdentity();
	}
    if(pSHEER == this)  
    {  
		sheerYESNO = TRUE;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		
//		glTranslatef(OPRT->Get_xMove()-DrawSpaceSize/2, OPRT->Get_yMove()-DrawSpaceSize/2, 0.0f);	
		glScalef(OPRT->Get_Scale()+DrawSpaceSize/20, OPRT->Get_Scale()+DrawSpaceSize/20, OPRT->Get_Scale()+DrawSpaceSize/20);
//		glScalef(OPRT->Get_Scale(), OPRT->Get_Scale(), OPRT->Get_Scale());
		RenderScene();
		
		glLoadIdentity();
		glTranslatef(-DrawSpaceSize + 0.5f, -DrawSpaceSize + 0.8f, 0.0f);
		
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(2.5);
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(DrawSpaceSize*0.2f,0.0f,0.0f);
		glEnd();
		
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,DrawSpaceSize*0.2,0.0f);
		glEnd();

		glRasterPos2f(DrawSpaceSize*0.2f+0.2, 0.0f-0.3f);
		glListBase(m_2DTextList);
		glCallLists(1, GL_UNSIGNED_BYTE ,"x");

		glRasterPos2f(0.0f-0.2, DrawSpaceSize*0.2f+0.3f);
		glListBase(m_2DTextList);
		glCallLists(1, GL_UNSIGNED_BYTE ,"y");

		glPopMatrix();
		glLoadIdentity();
	}
	if(StatusString == this)
	{
	}

    // Tell OpenGL to flush its pipeline
	::glFinish();
    // Now Swap the buffers
	::SwapBuffers(m_pDC->GetSafeHdc());
	
	wglMakeCurrent(pDC->GetSafeHdc(), NULL); 
}

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelView printing

BOOL CMy3D_view_FPbody_modelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy3D_view_FPbody_modelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy3D_view_FPbody_modelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelView diagnostics

#ifdef _DEBUG
void CMy3D_view_FPbody_modelView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3D_view_FPbody_modelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3D_view_FPbody_modelDoc* CMy3D_view_FPbody_modelView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3D_view_FPbody_modelDoc)));
	return (CMy3D_view_FPbody_modelDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelView message handlers

int CMy3D_view_FPbody_modelView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	InitializeOpenGL();
	return 0;
}

void CMy3D_view_FPbody_modelView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CMy3D_view_FPbody_modelView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}

void CMy3D_view_FPbody_modelView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	// TODO: Add your message handler code here
	GLdouble aspectRatio; // width/height ratio
	GLdouble nRange;
	
	nRange = DrawSpaceSize;
	mcoordinate->set_xViewOrg(cx/2);
	mcoordinate->set_yViewOrg(cy/2);
	mcoordinate->set_xViewExt(cx);
	mcoordinate->set_yViewExt(-cy);
	mcoordinate->set_xWinExt(cx);
	mcoordinate->set_yWinExt(cy);
	mcoordinate->set_xWinOrg(0.0);		//Here same as down but +/-
	mcoordinate->set_yWinOrg(0.0);		//Here same as down but +/-
										///////////
    if ( 0 >= cx || 0 >= cy )			//   ||
    {									//   ||
        return;							//   ||
    }									//   ||
    // select the full client area		//   VV
    ::glViewport(0.0, 0.0, cx, cy);	//!!!!!!!!!
    // compute the aspect ratio
    // this will keep all dimension scales equal
    aspectRatio = (GLdouble)cx/(GLdouble)cy;
    // select the projection matrix and clear it
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();
    // select the viewing volume
 //   ::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);
	if(cx <= cy) 
	{
		glOrtho(-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, nRange*50, -nRange*50);
		Real_Ortho_ViewPort_Ratio = nRange * 2.0 / (double)cx; 
	}
    else 
	{
		glOrtho(-nRange * aspectRatio, nRange * aspectRatio, -nRange, nRange, nRange*50, -nRange*50);
		Real_Ortho_ViewPort_Ratio = nRange * 2.0 / (double)cy; 
	}
    // switch back to the modelview matrix and clear it

	
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
}

BOOL CMy3D_view_FPbody_modelView::InitializeOpenGL()
{
	//Get a DC for the Client Area
    m_pDC = new CClientDC(this);
    //Failure to Get DC
    if(m_pDC == NULL)
    {
        MessageBox("Error Obtaining DC");
        return FALSE;
    }
    //Failure to set the pixel format
    if(!SetupPixelFormat())
    {
        return FALSE;
    }
    //Create Rendering Context
    m_hRC = ::wglCreateContext (m_pDC->GetSafeHdc ());
    //Failure to Create Rendering Context
    if(m_hRC == 0)
    {
        MessageBox("Error Creating RC");
        return FALSE;
    }
    //Make the RC Current
    if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE)
    {
        MessageBox("Error making RC Current");
        return FALSE;
    }
    //Specify Black as the clear color
    ::glClearColor(1.0f,1.0f,1.0f,0.0f);
    //Specify the back of the buffer as clear depth
    ::glClearDepth(1.0f);
    //Enable Depth Testing
    ::glEnable(GL_DEPTH_TEST);
	Create2DTextLists();
    return TRUE;
}

BOOL CMy3D_view_FPbody_modelView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = 
    {
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
        PFD_SUPPORT_OPENGL |            // support OpenGL
        PFD_DOUBLEBUFFER,                // double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        16,                             // 16-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
    if ( m_nPixelFormat == 0 )
    {
       return FALSE;
    }
    if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
    {
       return FALSE;
    }
    return TRUE;
}

void CMy3D_view_FPbody_modelView::RenderScene()
{
	int index, i, n;

	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	glLineWidth(1.0);
	for(index=0;index<pDoc->XYLNum;index++)
	{	
		for(i=0;i<pDoc->XYLINE[index].Get_BP();i++)								//init the cycle							
		{	
			if(OPRT->Get_LBD()==TRUE && pDoc->BP_xy[index][i].Catch==TRUE)
			{
				glColor3f(1.0, 0.0, 0.0);
				glPointSize(6.0f);
			}
			else
			{
				glColor3f(0.0, 0.0, 0.0);
				glPointSize(3.0f);
			}
			glBegin(GL_POINTS);
				glVertex3f(pDoc->BP_xy[index][i].Get_x(), pDoc->BP_xy[index][i].Get_y(), pDoc->BP_xy[index][i].Get_z());
			glEnd();
		}
	}
	for(index=0;index<pDoc->XYLNum;index++)
	{	
		glBegin(GL_LINE_STRIP);
		for(i=0;i<pDoc->XYLINE[index].Get_BP();i++)								//init the cycle							
		{
			glVertex3f(pDoc->BP_xy[index][i].Get_x(), pDoc->BP_xy[index][i].Get_y(), pDoc->BP_xy[index][i].Get_z());
		}
		glEnd();
	}

	for(index=0;index<pDoc->YZLNum;index++)
	{	
		for(i=0;i<pDoc->YZLINE[index].Get_BP();i++)								//init the cycle							
		{	
			if(OPRT->Get_LBD()==TRUE && pDoc->BP_yz[index][i].Catch==TRUE)
			{
				glColor3f(0.0, 1.0, 0.0);
				glPointSize(6.0f);
			}
			else
			{
				glColor3f(0.0, 0.0, 0.0);
				glPointSize(3.0f);
			}
			glBegin(GL_POINTS);
				glVertex3f(pDoc->BP_yz[index][i].Get_x(), pDoc->BP_yz[index][i].Get_y(), pDoc->BP_yz[index][i].Get_z());
			glEnd();			
		}
	}
	for(index=0;index<pDoc->YZLNum;index++)
	{	
		glBegin(GL_LINE_STRIP);
		for(i=0;i<pDoc->YZLINE[index].Get_BP();i++)								//init the cycle							
		{
			glVertex3f(pDoc->BP_yz[index][i].Get_x(), pDoc->BP_yz[index][i].Get_y(), pDoc->BP_yz[index][i].Get_z());
		}
		glEnd();
	}

	for(index=0;index<pDoc->XZLNum;index++)
	{	
		for(i=0;i<pDoc->XZLINE[index].Get_BP();i++)								//init the cycle							
		{	
			if(OPRT->Get_LBD()==TRUE && pDoc->BP_xz[index][i].Catch==TRUE)
			{
				glColor3f(0.0, 0.0, 1.0);
				glPointSize(6.0f);
			}
			else
			{
				glColor3f(0.0, 0.0, 0.0);
				glPointSize(3.0f);
			}
			glBegin(GL_POINTS);
				glVertex3f(pDoc->BP_xz[index][i].Get_x(), pDoc->BP_xz[index][i].Get_y(), pDoc->BP_xz[index][i].Get_z());
			glEnd();
		}
	}


/*
	glPointSize(6.0f);			
	glBegin(GL_POINTS);
		glColor3f(1.0, 0.0, 0.0);
		for(index=0;index<pDoc->XYLNum;index++)
		{	
			for(i=0;i<pDoc->XYLINE[0].Get_VER();i++)								//init the cycle							
			{	
				glVertex3f(pDoc->CP_xy[index][i].Get_ksi(), pDoc->CP_xy[index][i].Get_eta(), pDoc->CP_xy[index][i].Get_zeta());
			}
		}
	glEnd();

	glPointSize(6.0f);			
	glBegin(GL_POINTS);
		glColor3f(0.0, 1.0, 0.0);
		for(index=0;index<pDoc->YZLNum;index++)
		{	
			for(i=0;i<pDoc->YZLINE[0].Get_VER();i++)								//init the cycle							
			{	
				glVertex3f(pDoc->CP_yz[index][i].Get_ksi(), pDoc->CP_yz[index][i].Get_eta(), pDoc->CP_yz[index][i].Get_zeta());
			}
		}
	glEnd();

	glPointSize(6.0f);			
	glBegin(GL_POINTS);
		glColor3f(0.0, 0.0, 1.0);
		for(index=0;index<pDoc->XZLNum;index++)
		{	
			for(i=0;i<pDoc->XZLINE[0].Get_VER();i++)								//init the cycle							
			{	
				glVertex3f(pDoc->CP_xz[index][i].Get_ksi(), pDoc->CP_xz[index][i].Get_eta(), pDoc->CP_xz[index][i].Get_zeta());
			}
		}
	glEnd();



	glLineWidth(1.0);
	if(pDoc->BSPL_xy->Catch==TRUE)
	{
		glLineWidth(2.5);
	}

	
	glLineWidth(1.0);
	for(index=0;index<pDoc->XYLNum;index++)
	{
		glBegin(GL_LINE_STRIP);
			glColor3f(1.0, 0.0, 0.0);
			for(n=0;n<pDoc->XYLINE[index].Get_NUM();n++)								//init the cycle							
			{	
				glVertex3f(pDoc->BSPL_xy[index].x[n], pDoc->BSPL_xy[index].y[n], pDoc->BSPL_xy[index].z[n]);
			}
		glEnd();
	}

	glLineWidth(1.0);

	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		for(index=0;index<pDoc->XYLNum;index++)
		{	
			for(n=0;n<pDoc->XYLINE[index].Get_NUM();n++)								//init the cycle							
			{	
				glVertex3f(pDoc->BSPL_xy[index].x[n], pDoc->BSPL_xy[index].y[n], pDoc->BSPL_xy[index].z[n]);
				glVertex3f(pDoc->BSPL_xy[index].x[n]+pDoc->BSPL_xy[index].nx_xy[n]*pDoc->BSPL_xy[index].kslope_xy[n]*rad, pDoc->BSPL_xy[index].y[n]+pDoc->BSPL_xy[index].ny_xy[n]*pDoc->BSPL_xy[index].kslope_xy[n]*rad, pDoc->BSPL_xy[index].z[n]);
			}
		}
	glEnd();

	
	for(index=0;index<pDoc->YZLNum;index++)
	{
		glBegin(GL_LINE_STRIP);
			glColor3f(0.0, 1.0, 0.0);	
			for(n=0;n<pDoc->YZLINE[index].Get_NUM();n++)								//init the cycle							
			{	
				glVertex3f(pDoc->BSPL_yz[index].x[n], pDoc->BSPL_yz[index].y[n], pDoc->BSPL_yz[index].z[n]);
			}
		glEnd();
	}
	
	glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);
		for(index=0;index<pDoc->YZLNum;index++)
		{	
			for(n=0;n<pDoc->YZLINE[index].Get_NUM();n++)								//init the cycle							
			{	
				glVertex3f(pDoc->BSPL_yz[index].x[n], pDoc->BSPL_yz[index].y[n], pDoc->BSPL_yz[index].z[n]);
				glVertex3f(pDoc->BSPL_yz[index].x[n], pDoc->BSPL_yz[index].y[n]+pDoc->BSPL_yz[index].nx_yz[n]*pDoc->BSPL_yz[index].kslope_yz[n]*rad, pDoc->BSPL_yz[index].z[n]+pDoc->BSPL_yz[index].ny_yz[n]*pDoc->BSPL_yz[index].kslope_yz[n]*rad);
			}
		}
	glEnd();

	
	for(index=0;index<pDoc->XZLNum;index++)
	{
		glBegin(GL_LINE_STRIP);
			glColor3f(0.0, 0.0, 1.0);
			for(n=0;n<pDoc->XZLINE[index].Get_NUM();n++)								//init the cycle							
			{	
				glVertex3f(pDoc->BSPL_xz[index].x[n], pDoc->BSPL_xz[index].y[n], pDoc->BSPL_xz[index].z[n]);
			}
		glEnd();
	}

	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0);
		for(index=0;index<pDoc->XZLNum;index++)
		{	
			for(n=0;n<pDoc->XZLINE[index].Get_NUM();n++)								//init the cycle							
			{	
				glVertex3f(pDoc->BSPL_xz[index].x[n], pDoc->BSPL_xz[index].y[n], pDoc->BSPL_xz[index].z[n]);
				glVertex3f(pDoc->BSPL_xz[index].x[n]+pDoc->BSPL_xz[index].nx_xz[n]*pDoc->BSPL_xz[index].kslope_xz[n]*rad, pDoc->BSPL_xz[index].y[n], pDoc->BSPL_xz[index].z[n]+pDoc->BSPL_xz[index].ny_xz[n]*pDoc->BSPL_xz[index].kslope_xz[n]*rad);
			}
		}
	glEnd();
	glLineWidth(1.0);*/
//	glPopMatrix();
//	glLoadIdentity();

}

void CMy3D_view_FPbody_modelView::DrawCoordinate()
{
	// Clear the window with current clearing color

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(-DrawSpaceSize + 0.5f, -DrawSpaceSize + 0.8f, 0.0f);
	
	glRotatef(-45+OPRT->Get_xRot(), 0.0f, 1.0f, 0.0f);
	glRotatef(-45+OPRT->Get_yRot(), 1.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);	
	// Set current drawing color to red
	//		   R	 G	   B
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.5);
	glBegin(GL_LINES);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(DrawSpaceSize*0.2f,0.0f,0.0f);
	glEnd();
	
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,DrawSpaceSize*0.2,0.0f);
		
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,DrawSpaceSize*0.2f);
	glEnd();

	glLineWidth(1.0);
	glTranslatef(0.30f, 0.30f, 0.30f);
	glutWireCube(0.6); 

	glRasterPos3f(DrawSpaceSize*0.2f, 0.0f-0.3f, 0.0f-0.3f);
	glListBase(m_2DTextList);
	glCallLists(1, GL_UNSIGNED_BYTE ,"x");

	glRasterPos3f(0.0f-0.3, DrawSpaceSize*0.2f-0.2f, 0.0f-0.3f);
	glListBase(m_2DTextList);
	glCallLists(1, GL_UNSIGNED_BYTE ,"y");

	glRasterPos3f(0.0f-0.3, 0.0f-0.3f, DrawSpaceSize*0.2f);
	glListBase(m_2DTextList);
	glCallLists(1, GL_UNSIGNED_BYTE ,"z");

	glPopMatrix();
	glLoadIdentity();
}

void CMy3D_view_FPbody_modelView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	OPRT->Set_RBD(TRUE);

	InvalidateRect(NULL,FALSE);
	CView::OnRButtonDown(nFlags, point);
}

void CMy3D_view_FPbody_modelView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	OPRT->p_new = point;
	double real_pnewx, real_pnewy;

	mcoordinate->set_xViewPort(OPRT->p_new.x);
	mcoordinate->set_yViewPort(OPRT->p_new.y);
	OPRT->p_new.x = mcoordinate->get_xWindow();
	OPRT->p_new.y = mcoordinate->get_yWindow();

	real_pnewx = OPRT->p_new.x * Real_Ortho_ViewPort_Ratio;
	real_pnewy = OPRT->p_new.y * Real_Ortho_ViewPort_Ratio;
	
	if(OPRT->Get_RBD()==TRUE)
	{
		OPRT->Set_xRot((real_pnewx) * -OPRT->Get_MMS());	
		OPRT->Set_yRot((real_pnewy) * OPRT->Get_MMS());
		InvalidateRect(NULL,FALSE);
	}

	if(OPRT->Get_SHIFT()==TRUE)
	{
//		OPRT->Set_xMove(real_pnewx);
//		OPRT->Set_yMove(real_pnewy);
		InvalidateRect(NULL,FALSE);
	}

	real_pnewx /= OPRT->Get_Scale()+DrawSpaceSize/20;
	real_pnewy /= OPRT->Get_Scale()+DrawSpaceSize/20;

//	real_pnewx -= OPRT->Get_xMove();
//	real_pnewy -= OPRT->Get_yMove();

	if(OPRT->Get_LBD()==TRUE)
	{
		if(pDoc->BP_xy[xyLineIndex][xyPointIndex].Catch==TRUE)
		{
			pDoc->BP_xy[xyLineIndex][xyPointIndex].Set_x(real_pnewx);
			pDoc->BP_xy[xyLineIndex][xyPointIndex].Set_y(real_pnewy);
			pDoc->BP_xy[xyLineIndex][xyPointIndex].Set_z(0.0);
		}
//		pDoc->BPLIndex = xyLineIndex;
//		pDoc->CALT_VP_XY();
//		pDoc->CALT_BSPLINE_XY();	
		InvalidateRect(NULL,FALSE);
		pDoc->UpdateAllViews(this);
	}
	if(OPRT->Get_LBD()==TRUE)
	{
		if(pDoc->BP_yz[yzLineIndex][yzPointIndex].Catch==TRUE)
		{
		/*	if(yzLineIndex==0)
			{
				pDoc->BP_yz[yzLineIndex][yzPointIndex].Set_x(-132.025);
			}
			else if(yzLineIndex==1)
			{
				pDoc->BP_yz[yzLineIndex][yzPointIndex].Set_x(-118.823);
			}*/
			pDoc->BP_yz[yzLineIndex][yzPointIndex].Set_x(pDoc->BP_xy[0][yzLineIndex].Get_x());
			pDoc->BP_yz[yzLineIndex][yzPointIndex].Set_y(real_pnewy);
			pDoc->BP_yz[yzLineIndex][yzPointIndex].Set_z(real_pnewx);

		}
//		pDoc->BPLIndex = yzLineIndex;
//		pDoc->CALT_VP_YZ();
//		pDoc->CALT_BSPLINE_YZ();	
		InvalidateRect(NULL,FALSE);
		pDoc->UpdateAllViews(this);
	}

	if(OPRT->Get_LBD()==TRUE)
	{
		if(pDoc->BP_xz[xzLineIndex][xzPointIndex].Catch==TRUE)
		{
			pDoc->BP_xz[xzLineIndex][xzPointIndex].Set_x(real_pnewx);
			pDoc->BP_xz[xzLineIndex][xzPointIndex].Set_y(0.0);
			pDoc->BP_xz[xzLineIndex][xzPointIndex].Set_z(real_pnewy);

		}
//		pDoc->BPLIndex = xzLineIndex;
//		pDoc->CALT_VP_XZ();
//		pDoc->CALT_BSPLINE_XZ();
		InvalidateRect(NULL,FALSE);
		pDoc->UpdateAllViews(this);
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CMy3D_view_FPbody_modelView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OPRT->Set_RBD(FALSE);
	InvalidateRect(NULL,FALSE);

	CView::OnRButtonUp(nFlags, point);
}

BOOL CMy3D_view_FPbody_modelView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	GLdouble zin, zout;
	zin = 2.5 * DrawSpaceSize;
	zout = 0.5 / DrawSpaceSize;

	if(zDelta>0&&OPRT->Get_Scale()<=zin && OPRT->Get_CTRL()==FALSE)
	{
		OPRT->Set_Scale(OPRT->Get_Scale() + 0.1*zDelta/120);
	}
	if(zDelta<0&&OPRT->Get_Scale()>=zout && OPRT->Get_CTRL()==FALSE)
	{
		OPRT->Set_Scale(OPRT->Get_Scale() + 0.1*zDelta/120);
	}
	
	if(zDelta>0&&OPRT->Get_Scale()<=zin && OPRT->Get_CTRL()==TRUE)
	{
		rad -= 0.1 * zDelta/120;
	}
	if(zDelta<0&&OPRT->Get_Scale()>=zout && OPRT->Get_CTRL()==TRUE)
	{
		rad -= 0.1 * zDelta/120;
	}

	InvalidateRect(NULL,FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMy3D_view_FPbody_modelView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC); 

	OPRT->Set_LBD(TRUE);
	OPRT->p_old = point;
	
	int i, index;
	double real_poldx, real_poldy;

	mcoordinate->set_xViewPort(OPRT->p_old.x);
	mcoordinate->set_yViewPort(OPRT->p_old.y);
	OPRT->p_old.x = mcoordinate->get_xWindow();
	OPRT->p_old.y = mcoordinate->get_yWindow();
	
	real_poldx = OPRT->p_old.x * Real_Ortho_ViewPort_Ratio;
	real_poldy = OPRT->p_old.y * Real_Ortho_ViewPort_Ratio;

	real_poldx /= OPRT->Get_Scale()+DrawSpaceSize/20;
	real_poldy /= OPRT->Get_Scale()+DrawSpaceSize/20;

	real_poldx -= OPRT->Get_xMove();
	real_poldy -= OPRT->Get_yMove();

	for(index=0;index<pDoc->XYLNum;index++)
	{	
		for(i=0;i<pDoc->XYLINE[index].Get_BP();i++)
		{																	
			if(real_poldx<=(pDoc->BP_xy[index][i].Get_x()+0.01*DrawSpaceSize) && real_poldx>=(pDoc->BP_xy[index][i].Get_x()-0.01*DrawSpaceSize) &&
				real_poldy<=(pDoc->BP_xy[index][i].Get_y()+0.01*DrawSpaceSize) && real_poldy>=(pDoc->BP_xy[index][i].Get_y()-0.01*DrawSpaceSize) &&
				 sheerYESNO == TRUE)
			{	
				pDoc->BP_xy[index][i].Catch=TRUE;
				xyLineIndex = index;
				xyPointIndex = i;
				InvalidateRect(NULL,FALSE);
				break;
			}
		}
	}	

	for(index=0;index<pDoc->YZLNum;index++)
	{	
		for(i=0;i<pDoc->YZLINE[index].Get_BP();i++)
		{																	
			if(real_poldx<=(pDoc->BP_yz[index][i].Get_z()+0.01*DrawSpaceSize) && real_poldx>=(pDoc->BP_yz[index][i].Get_z()-0.01*DrawSpaceSize) &&
				real_poldy<=(pDoc->BP_yz[index][i].Get_y()+0.01*DrawSpaceSize) && real_poldy>=(pDoc->BP_yz[index][i].Get_y()-0.01*DrawSpaceSize))
			{	
				pDoc->BP_yz[index][i].Catch=TRUE;
				yzLineIndex = index;
				yzPointIndex = i;
				InvalidateRect(NULL,FALSE);
				break;
			}
		}
	}
	
	for(index=0;index<pDoc->XZLNum;index++)
	{	
		for(i=0;i<pDoc->XZLINE[index].Get_BP();i++)
		{																	
			if(real_poldx<=(pDoc->BP_xz[index][i].Get_x()+0.01*DrawSpaceSize) && real_poldx>=(pDoc->BP_xz[index][i].Get_x()-0.01*DrawSpaceSize) &&
				real_poldy<=(pDoc->BP_xz[index][i].Get_z()+0.01*DrawSpaceSize) && real_poldy>=(pDoc->BP_xz[index][i].Get_z()-0.01*DrawSpaceSize) &&
				 sheerYESNO == FALSE)
			{	
				pDoc->BP_xz[index][i].Catch=TRUE;
				xzLineIndex = index;
				xzPointIndex = i;
				InvalidateRect(NULL,FALSE);
				break;
			}
		}
	}
	
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}

void CMy3D_view_FPbody_modelView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL); 
	
	OPRT->Set_LBD(FALSE);
	if(pDoc->BP_xy[xyLineIndex][xyPointIndex].Catch==TRUE)
	{
		pDoc->BP_xy[xyLineIndex][xyPointIndex].Catch=FALSE;
	}

	if(pDoc->BP_yz[yzLineIndex][yzPointIndex].Catch==TRUE)
	{
		pDoc->BP_yz[yzLineIndex][yzPointIndex].Catch=FALSE;
	}

	if(pDoc->BP_xz[xzLineIndex][xzPointIndex].Catch==TRUE)
	{
		pDoc->BP_xz[xzLineIndex][xzPointIndex].Catch=FALSE;
	}
/*	int i, index;
	for(index=0;index<pDoc->XYLNum;index++)
	{	
		for(i=0;i<pDoc->XYLINE[index].Get_BP();i++)
		{																	
			if(pDoc->BP_xy[index][i].Catch==TRUE)
			{	
				pDoc->BP_xy[index][i].Catch=FALSE;
				break;
			}
		}
	}
	for(index=0;index<pDoc->YZLNum;index++)
	{	
		for(i=0;i<pDoc->YZLINE[index].Get_BP();i++)
		{																	
			if(pDoc->BP_yz[index][i].Catch==TRUE)
			{	
				pDoc->BP_yz[index][i].Catch=FALSE;
				break;
			}
		}
	}
	for(index=0;index<pDoc->XZLNum;index++)
	{	
		for(i=0;i<pDoc->XZLINE[index].Get_BP();i++)
		{																	
			if(pDoc->BP_xz[index][i].Catch==TRUE)
			{	
				pDoc->BP_xz[index][i].Catch=FALSE;
				break;
			}
		}
	}*/
	InvalidateRect(NULL,FALSE);
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}

void CMy3D_view_FPbody_modelView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
    if(nChar==VK_CONTROL)
		OPRT->Set_CTRL(TRUE);

	InvalidateRect(NULL,FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMy3D_view_FPbody_modelView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	OPRT->Set_CTRL(FALSE);

	InvalidateRect(NULL,FALSE);
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMy3D_view_FPbody_modelView::OnKslopeYes() 
{
	// TODO: Add your command handler code here
	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
/*	
	int index;

	pDoc->PCUPI_XY = TRUE;
	pDoc->PCUPI_YZ = TRUE;
	pDoc->PCUPI_XZ = TRUE;

	
	for(index=0;index<pDoc->XYLNum;index++)
	{
		pDoc->CALT_BSPLINE_XY();
		InvalidateRect(NULL,FALSE);
	}

	for(index=0;index<pDoc->YZLNum;index++)
	{
		pDoc->CALT_BSPLINE_YZ();
		InvalidateRect(NULL,FALSE);
	}

	for(index=0;index<pDoc->XZLNum;index++)
	{
		pDoc->CALT_BSPLINE_XZ();
		InvalidateRect(NULL,FALSE);
	}
	pDoc->UpdateAllViews(this);	*/
}

void CMy3D_view_FPbody_modelView::OnKslopeNo() 
{
	// TODO: Add your command handler code here
	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
/*
	int index;

	pDoc->PCUPI_XY = FALSE;
	pDoc->PCUPI_YZ = FALSE;
	pDoc->PCUPI_XZ = FALSE;

	for(index=0;index<pDoc->XYLNum;index++)
	{
		pDoc->CALT_BSPLINE_XY();
		InvalidateRect(NULL,FALSE);
	}

	for(index=0;index<pDoc->YZLNum;index++)
	{
		pDoc->CALT_BSPLINE_YZ();
		InvalidateRect(NULL,FALSE);
	}

	for(index=0;index<pDoc->XZLNum;index++)
	{
		pDoc->CALT_BSPLINE_XZ();
		InvalidateRect(NULL,FALSE);
	}
	pDoc->UpdateAllViews(this);*/
}

void CMy3D_view_FPbody_modelView::OnStartchange() 
{
	// TODO: Add your command handler code here
//	PCUPI_CHANGE = TRUE;
/*	
	PCUPI_XY = FALSE;
	PCUPI_YZ = FALSE;
	PCUPI_XZ = FALSE;
	for(OPRT->index=0;OPRT->index<*XYLINE;OPRT->index++)
	{
		CALT_BSPLINE_XY();
	}

	for(OPRT->index=0;OPRT->index<*YZLINE;OPRT->index++)
	{
		CALT_BSPLINE_YZ();
	}

	for(OPRT->index=0;OPRT->index<*XZLINE;OPRT->index++)
	{
		CALT_BSPLINE_XZ();
	}
	*/
//	InvalidateRect(NULL,FALSE);
}

void CMy3D_view_FPbody_modelView::OnEndchange() 
{
	// TODO: Add your command handler code here
//	PCUPI_CHANGE = FALSE;
//	InvalidateRect(NULL,FALSE);
}

void CMy3D_view_FPbody_modelView::OnAllBp() 
{
	// TODO: Add your command handler code here
	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
/*
	pDoc->PCUPI_XY = FALSE;
	pDoc->PCUPI_YZ = FALSE;
	pDoc->PCUPI_XZ = FALSE;

	int index;
	
	OPRT->Set_xRot(0.0);
	OPRT->Set_yRot(0.0);
	OPRT->Set_xMove(0.0);
	OPRT->Set_yMove(0.0);
	OPRT->Set_RBD(FALSE);
	OPRT->Set_LBD(FALSE);
	OPRT->Set_Scale(1.0);
	OPRT->Set_SHIFT(FALSE);
	OPRT->Set_CTRL(FALSE);

	pDoc->Init_Num_Ord();

	for(index=0;index<pDoc->XYLNum;index++)
	{
		pDoc->Init_BP_XY();
		pDoc->CALT_VP_XY();
		pDoc->CALT_BSPLINE_XY();
		InvalidateRect(NULL,FALSE);
	}

	for(index=0;index<pDoc->YZLNum;index++)
	{
		pDoc->Init_BP_YZ();
		pDoc->CALT_VP_YZ();
		pDoc->CALT_BSPLINE_YZ();
		InvalidateRect(NULL,FALSE);
	}

	for(index=0;index<pDoc->XZLNum;index++)
	{
		pDoc->Init_BP_XZ();
		pDoc->CALT_VP_XZ();
		pDoc->CALT_BSPLINE_XZ();
		InvalidateRect(NULL,FALSE);
	}
	pDoc->UpdateAllViews(this);*/
}

void CMy3D_view_FPbody_modelView::OnMButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnMButtonDown(nFlags, point);
	OPRT->Set_SHIFT(TRUE);
	InvalidateRect(NULL,FALSE);
}

void CMy3D_view_FPbody_modelView::OnMButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnMButtonUp(nFlags, point);
	OPRT->Set_SHIFT(FALSE);
	InvalidateRect(NULL,FALSE);
}

void CMy3D_view_FPbody_modelView::Create2DTextLists()
{
	CFont m_font;
    m_font.CreateFont(    -15,                            // Height Of Font
                        8,                                // Width Of Font
                        0,                                // Angle Of Escapement
                        0,                                // Orientation Angle
                        FW_NORMAL,                        // Font Weight
                        FALSE,                            // Italic
                        FALSE,                            // Underline
                        FALSE,                            // Strikeout
                        ANSI_CHARSET,                     // Character Set Identifier
                        OUT_TT_PRECIS,                    // Output Precision
                        CLIP_DEFAULT_PRECIS,			  // Clipping Precision
                        DEFAULT_QUALITY,                  // Output Quality
                        FF_DONTCARE|DEFAULT_PITCH,        // Family And Pitch
                        "Algerian");
    CFont* m_pOldFont = m_pDC->SelectObject(&m_font);
     // create display lists for glyphs 0 through 255 with 0.1 extrusion 
    // and default deviation. The display list numbering starts at 1000 
    // (it could be any number) 
    m_2DTextList = glGenLists(256);
    wglUseFontBitmaps(m_pDC->GetSafeHdc(), 0, 255, m_2DTextList); 
    m_pDC->SelectObject(m_pOldFont);
}
