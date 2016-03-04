// GraphicsAlgorithmView.cpp : implementation of the CGraphicsAlgorithmView class
//

#include "stdafx.h"
#include "GraphicsAlgorithm.h"

#include "GraphicsAlgorithmDoc.h"
#include "GraphicsAlgorithmView.h"
#include "LWidth.h"
#include "SelPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmView

IMPLEMENT_DYNCREATE(CGraphicsAlgorithmView, CView)

BEGIN_MESSAGE_MAP(CGraphicsAlgorithmView, CView)
	//{{AFX_MSG_MAP(CGraphicsAlgorithmView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(idCurColor, OnidCurColor)
	ON_COMMAND(idClear, OnidClear)
	ON_COMMAND(idPolygon, OnidPolygon)
	ON_COMMAND(idSetPolygon, OnidSetPolygon)
	ON_COMMAND(IDCLOSE, OnClose)
	ON_COMMAND(idFillColor, OnidFillColor)
	ON_COMMAND(idLineWidth, OnidLineWidth)
	ON_COMMAND(idabout, Onidabout)
	ON_COMMAND(sqx, Onsqx)
	ON_COMMAND(first, Onfirst)
	ON_COMMAND(last, Onlast)
	ON_COMMAND(notnext, Onnotnext)
	ON_COMMAND(next, Onnext)
	ON_COMMAND(id_SelPoint, OnSelPoint)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ch, Onch)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmView construction/destruction

CGraphicsAlgorithmView::CGraphicsAlgorithmView()
{
	// TODO: add construction code here
//	tBreLine=0;
//	tDDALine=1;

}

CGraphicsAlgorithmView::~CGraphicsAlgorithmView()
{
}

BOOL CGraphicsAlgorithmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmView drawing

void CGraphicsAlgorithmView::OnDraw(CDC* Gra)
{
	CGraphicsAlgorithmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	
	cls();


}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmView printing

BOOL CGraphicsAlgorithmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicsAlgorithmView::OnBeginPrinting(CDC* /*Gra*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicsAlgorithmView::OnEndPrinting(CDC* /*Gra*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmView diagnostics

#ifdef _DEBUG
void CGraphicsAlgorithmView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsAlgorithmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsAlgorithmDoc* CGraphicsAlgorithmView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsAlgorithmDoc)));
	return (CGraphicsAlgorithmDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsAlgorithmView message handlers



void CGraphicsAlgorithmView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	Gra=new CClientDC(this);
	Gra->SetBkColor(RGB(0,0,0));
	Curcolor=RGB(255,0,255);
	FillColor=RGB(255,0,255);
	CurPen.CreatePen(PS_SOLID,3,Curcolor);

	CurPen1.CreatePen(PS_SOLID,5,RGB(0,0,0));
	OrgPen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	MouDown=false;
	FunSel=-1;
}



void CGraphicsAlgorithmView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	MouDown=true;
	switch(FunSel)
	{
	case 0:
			break;
	case 1:
	BegP=point;
	if(PNum==0)
	{
		ContP[PNum++]=point;
	}else{
		BegP=ContP[PNum-1];
	}
	PreP=BegP;
//	pen1.CreatePen(PS_SOLID,1,RGB(255,0,0));
	Gra->SetROP2(R2_XORPEN);
	Gra->SelectObject(&OrgPen);  
	Gra->MoveTo(BegP.x-10,BegP.y);
	Gra->LineTo(BegP.x+10,BegP.y);
	Gra->MoveTo(BegP.x,BegP.y-10);
	Gra->LineTo(BegP.x,BegP.y+10);
	Gra->MoveTo(BegP);
	Gra->LineTo(PreP);
			break;
	case 2:
			break;
	case 3:
		//	pen1.CreatePen(PS_SOLID,1,RGB(255,0,0));
			Gra->SetROP2(R2_XORPEN);
			Gra->SelectObject(&CurPen);  
			BegP=point;PreP=point;
			Gra->MoveTo(BegP.x-10,BegP.y);
			Gra->LineTo(BegP.x+10,BegP.y);
			Gra->MoveTo(BegP.x,BegP.y-10);
			Gra->LineTo(BegP.x,BegP.y+10);
			Gra->MoveTo(BegP);
			Gra->LineTo(PreP);
			break;

    case 4:
	      Gra->SetROP2(R2_XORPEN);
          Gra->SelectObject(&OrgPen); 
		  BegP= ContP[GDS+1];
	      PreP=BegP;
          break;
    case 5:Gra->SetROP2(R2_XORPEN);
           Gra->SelectObject(&OrgPen);
	       BegP= ContP[GDS-1];
           PreP=BegP;
           break;
    case 6:
		   Gra->SetROP2(R2_XORPEN);
           Gra->SelectObject(&OrgPen);
           BegP= ContP[GDS-1];
           PreP=BegP;
           BegP1= ContP[GDS+1];
	       PreP1=BegP1;
           break;



	}
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicsAlgorithmView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	MouDown=false;
	switch(FunSel)
	{
	case 0:
			break;
	case 1:
		Gra->SetROP2(R2_XORPEN);
		Gra->MoveTo(BegP.x-10,BegP.y);
		Gra->LineTo(BegP.x+10,BegP.y);
		Gra->MoveTo(BegP.x,BegP.y-10);
		Gra->LineTo(BegP.x,BegP.y+10);
		Gra->MoveTo(BegP);
		Gra->LineTo(point);
		//	pen1.CreatePen(PS_SOLID,1,RGB(255,0,0));
		Gra->SetROP2(R2_COPYPEN);
		Gra->SelectObject(&CurPen);  
		Gra->MoveTo(BegP);
		Gra->LineTo(point);
	 	ContP[PNum++]=point;
		//	Gra->Ellipse(point.x-10,point.y-10,point.x+10,point.y+10);
			break;
	case 2:
			FloodFill4(point,FillColor,Curcolor);
			break;
	case 3:
			Gra->SetROP2(R2_XORPEN);
			Gra->MoveTo(BegP.x-10,BegP.y);
			Gra->LineTo(BegP.x+10,BegP.y);
			Gra->MoveTo(BegP.x,BegP.y-10);
			Gra->LineTo(BegP.x,BegP.y+10);
			Gra->MoveTo(BegP);
			Gra->LineTo(PreP);
		//	pen1.CreatePen(PS_SOLID,1,RGB(255,0,0));
			Gra->SetROP2(R2_COPYPEN);
			Gra->SelectObject(&OrgPen);  
			Gra->MoveTo(BegP);
			Gra->LineTo(point);
			break;
	case 4:
	      Gra->SetROP2(R2_XORPEN);
          Gra->SelectObject(&CurPen);
		  ContP[GDS]=Contp1[GDS];
          Gra->MoveTo(ContP[GDS]);
		  Gra->LineTo(ContP[GDS+1]);
          Gra->SetROP2(R2_COPYPEN);
Gra->SelectObject(&CurPen1);
Onsqx();
	     Gra->SelectObject(&CurPen);
		   Gra->MoveTo(BegP);
		   Gra->LineTo(point);
           ContP[GDS]=point;
           Contp1[GDS]=point;
		   Onsqx();
	       break;
    case 5:Gra->SetROP2(R2_XORPEN); 
           Gra->SelectObject(&CurPen); 
           ContP[GDS]=Contp1[GDS];
           Gra->MoveTo(ContP[GDS]);
		   Gra->LineTo(ContP[GDS-1]);
           Gra->SetROP2(R2_COPYPEN);
Gra->SelectObject(&CurPen1);
Onsqx();
        Gra->SelectObject(&CurPen);
        Gra->MoveTo(BegP);
		Gra->LineTo(point);
	    ContP[GDS]=point;
        Contp1[GDS]=point;
		Onsqx(); 
		break;
    case 6: Gra->SetROP2(R2_XORPEN); 
            Gra->SelectObject(&CurPen); 
            ContP[GDS]=Contp1[GDS];
            Gra->MoveTo(ContP[GDS]);
		    Gra->LineTo(ContP[GDS-1]); 
            Gra->MoveTo(ContP[GDS]);
		    Gra->LineTo(ContP[GDS+1]);
          Gra->SetROP2(R2_COPYPEN);
Gra->SelectObject(&CurPen1);
Onsqx();
         Gra->SelectObject(&CurPen);   
         Gra->MoveTo(BegP);
		 Gra->LineTo(point);
		 Gra->MoveTo(BegP1);
		 Gra->LineTo(point);
	     ContP[GDS]=point;
         Contp1[GDS]=point;
         Onsqx();
		 break;

}
	CView::OnLButtonUp(nFlags, point);
}

void CGraphicsAlgorithmView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(MouDown){
	switch(FunSel)
	{
	case 0:
			break;
	case 1:
		Gra->MoveTo(BegP);
		Gra->LineTo(PreP);
		PreP=point;		
		Gra->MoveTo(BegP);
	//	Gra->Ellipse(point.x ,point.y,point.x+10,point.y+10);
		Gra->LineTo(PreP);
			break;
	case 2:
			break;
	case 3:
			break;
    case 4:	
	case 5:	
		   Gra->MoveTo(BegP);
		   Gra->LineTo(PreP);
           Onsqx();
	       PreP=point;		
		   Gra->MoveTo(BegP);
           Gra->LineTo(PreP);
           ContP[GDS]=point;
		   Onsqx();
       	   break;
	case 6:
           Gra->MoveTo(BegP);
		   Gra->LineTo(PreP);
           Gra->MoveTo(BegP1);
		   Gra->LineTo(PreP1);
           Onsqx();
	       PreP=point;	
		   PreP1=point;
		   Gra->MoveTo(BegP);
           Gra->LineTo(PreP);
           Gra->MoveTo(BegP1);
           Gra->LineTo(PreP1);
           ContP[GDS]=point;
		   Onsqx();
			break;

	}
	}
	
	CView::OnMouseMove(nFlags, point);
}




void CGraphicsAlgorithmView::FloodFill4(CPoint SeedP, COLORREF FillColor, COLORREF BdColor)
{
	if((Gra->GetPixel(SeedP)!=FillColor)&&(Gra->GetPixel(SeedP)!=BdColor))
	{
		Gra->SetPixel(SeedP,FillColor);
		FloodFill4(SeedP+CPoint(1,0),  FillColor, BdColor);
	 	FloodFill4(SeedP-CPoint(1,0),  FillColor, BdColor);
		FloodFill4(SeedP+CPoint(0,1),  FillColor, BdColor);
		FloodFill4(SeedP-CPoint(0,1),  FillColor, BdColor);
	}
}

void CGraphicsAlgorithmView::OnidCurColor() 
{
	// TODO: Add your command handler code here
	CColorDialog cdlg;
	if(cdlg.DoModal()==IDOK)
	{
		Curcolor=cdlg.GetColor();
		CurPen.DeleteObject();
		CurPen.CreatePen(PS_SOLID,3,Curcolor);
	}
	
}

void CGraphicsAlgorithmView::OnidClear() 
{
	// TODO: Add your command handler code here
	FunSel=0;
	CRect rc;
	GetClientRect(rc);
	Gra->FillSolidRect(rc,Gra->GetBkColor());
}

void CGraphicsAlgorithmView::OnidPolygon() 
{
	// TODO: Add your command handler code here
	FunSel=1;PNum=0;
}

void CGraphicsAlgorithmView::OnidSetPolygon() 
{
	// TODO: Add your command handler code here
	FunSel=2;
	static bool First=1;
	if(First)
	{
		First=0;
		MessageBox("提示: 这个直接递归调用的填充程序在填充稍大的区域时容易出现意外,终止运行!");
	}

}

void CGraphicsAlgorithmView::OnClose() 
{
	// TODO: Add your command handler code here
	FunSel=5;
	Gra->MoveTo(ContP[PNum-1]);
 	Gra->LineTo(ContP[0]);
	
}

void CGraphicsAlgorithmView::OnidFillColor() 
{
	// TODO: Add your command handler code here
		CColorDialog cdlg;
	if(cdlg.DoModal()==IDOK)
	{
		FillColor=cdlg.GetColor();

	}

}

void CGraphicsAlgorithmView::OnidLineWidth() 
{
	// TODO: Add your command handler code here
		LWidth ldlg;
		ldlg.DoModal();
		CurPen.DeleteObject();
		CurPen.CreatePen(PS_SOLID,ldlg.m_LWidth,Curcolor);

}

void CGraphicsAlgorithmView::Onidabout() 
{
	// TODO: Add your command handler code here
	MessageBox(" 关于Bezier曲线的生成!");

}



void CGraphicsAlgorithmView::Onsqx() 
{
	// TODO: Add your command handler code here
	int i;

	Gra->MoveTo(ContP[0]);
	for(i=1;i<=1000;i++)
	{
//		BB(float(i/100.0));
		Gra->LineTo(Bezier(float(i/1000.0)));
	}

}






CPoint CGraphicsAlgorithmView::Bezier(float t)
{
		int m,i;
		double CP[2][1000];
	for(i=0;i<PNum;i++)
	{
		CP[0][i]=ContP[i].x;
		CP[1][i]=ContP[i].y;
	}
	for(i=1;i<PNum;i++)
	for(m=0;m<PNum-i;m++)
	{
		CP[0][m]=CP[0][m]+t*(CP[0][m+1]-CP[0][m]);
		CP[1][m]=CP[1][m]+t*(CP[1][m+1]-CP[1][m]);
	}
	return(CPoint(CP[0][0],CP[1][0]));

}

void CGraphicsAlgorithmView::cls()
{
	CRect rc;
	GetClientRect(rc);
	Gra->FillSolidRect(rc,Gra->GetBkColor());

}

void CGraphicsAlgorithmView::Onfirst() 
{
	// TODO: Add your command handler code here
	
	GDS=0;TT();FunSel=4;Contp1[GDS]=ContP[GDS];
	
	
}

void CGraphicsAlgorithmView::TT()
{	

   Gra->SetROP2(R2_XORPEN);
	Gra->SelectObject(&OrgPen);  
	Gra->MoveTo(ContP[GDS].x-10,ContP[GDS].y);
	Gra->LineTo(ContP[GDS].x+10,ContP[GDS].y);
	Gra->MoveTo(ContP[GDS].x,ContP[GDS].y-10);
	Gra->LineTo(ContP[GDS].x,ContP[GDS].y+10);
	Gra->MoveTo(ContP[GDS]);
	Gra->LineTo(ContP[GDS]);





}

void CGraphicsAlgorithmView::Onlast() 
{
	// TODO: Add your command handler code here
	GDS=PNum-1;TT();FunSel=5;Contp1[GDS]=ContP[GDS];
	
}

void CGraphicsAlgorithmView::Onnotnext() 
{
	// TODO: Add your command handler code here
	GDS--; 
	if(GDS==0) {TT();FunSel=4;Contp1[GDS]=ContP[GDS];}
   else	if(GDS<0){GDS=PNum-1;TT();FunSel=5;Contp1[GDS]=ContP[GDS];}
   else {TT();FunSel=6;Contp1[GDS]=ContP[GDS];}
}

void CGraphicsAlgorithmView::Onnext() 
{
	// TODO: Add your command handler code here
	GDS++; 
	if(GDS==PNum-1) {TT(); FunSel=5;Contp1[GDS]=ContP[GDS];}
	else if(GDS>=PNum){GDS=0;TT(); FunSel=4;Contp1[GDS]=ContP[GDS];}
	else {TT(); FunSel=6;Contp1[GDS]=ContP[GDS];}
}

/*void CGraphicsAlgorithmView::OnSelPoint() 
{
}
*/

void CGraphicsAlgorithmView::OnSelPoint() 
{
	// TODO: Add your command handler code here
	SelPoint PInd;
	PInd.SelNum=PNum;
	PInd.DoModal();
	GDS=PInd.SelNum;
	if(GDS==0){TT();FunSel=4;Contp1[GDS]=ContP[GDS];}
   else	if(GDS==PNum-1){TT(); FunSel=5;Contp1[GDS]=ContP[GDS];}
   else {TT(); FunSel=6;Contp1[GDS]=ContP[GDS];}
	

}	

void CGraphicsAlgorithmView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

			
	CView::OnLButtonDblClk(nFlags, point);
}

void CGraphicsAlgorithmView::Onch() 
{
	// TODO: Add your command handler code here
    int i;
	FunSel=0;
	CRect rc;
	GetClientRect(rc);
	Gra->FillSolidRect(rc,Gra->GetBkColor());

	Gra->SetROP2(R2_XORPEN);
	Gra->SelectObject(&OrgPen); 
	for(i=0;i<PNum-1;i++)
	{Gra->MoveTo(ContP[i]);
	Gra->LineTo(ContP[i+1]);}
    Gra->SetROP2(R2_COPYPEN);
	Gra->SelectObject(&CurPen);  
    Onsqx();
}
