// 3D_view_FPbody_modelDoc.cpp : implementation of the CMy3D_view_FPbody_modelDoc class
//

#include "stdafx.h"
#include "3D_view_FPbody_model.h"

#include "3D_view_FPbody_modelDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelDoc

IMPLEMENT_DYNCREATE(CMy3D_view_FPbody_modelDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3D_view_FPbody_modelDoc, CDocument)
	//{{AFX_MSG_MAP(CMy3D_view_FPbody_modelDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelDoc construction/destruction

CMy3D_view_FPbody_modelDoc::CMy3D_view_FPbody_modelDoc()
{
	// TODO: add one-time construction code here
	GetMethod = (GET_METHOD*)malloc(sizeof(GET_METHOD));

	PCUPI_XY = FALSE;
	PCUPI_YZ = FALSE;
	PCUPI_XZ = FALSE;
	PCUPI_CHANGE = FALSE;
	
	XYLNum = 1;
	YZLNum = 16; 
	XZLNum = 1; 
	
	Init_Num_Ord();
	Init_BP_XY();
	Init_BP_YZ();
	Init_BP_XZ();
//	CALT_VP_XY();
//	CALT_VP_YZ();
//	CALT_VP_XZ();

	for(BPLIndex=0; BPLIndex<XYLNum; BPLIndex++)
	{
//		CALT_BSPLINE_XY();
	}

	for(BPLIndex=0; BPLIndex<YZLNum; BPLIndex++)
	{
//		CALT_BSPLINE_YZ();
	}

	for(BPLIndex=0; BPLIndex<XZLNum; BPLIndex++)
	{
//		CALT_BSPLINE_XZ();
	}	
}

CMy3D_view_FPbody_modelDoc::~CMy3D_view_FPbody_modelDoc()
{
}

BOOL CMy3D_view_FPbody_modelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelDoc serialization

void CMy3D_view_FPbody_modelDoc::Serialize(CArchive& ar)
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
// CMy3D_view_FPbody_modelDoc diagnostics

#ifdef _DEBUG
void CMy3D_view_FPbody_modelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3D_view_FPbody_modelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3D_view_FPbody_modelDoc commands

void CMy3D_view_FPbody_modelDoc::Init_Num_Ord()
{
	//...Init Num Ord
	XYLINE = new NumForIndex[XYLNum];
	YZLINE = new NumForIndex[YZLNum];
	XZLINE = new NumForIndex[XZLNum];
	
	int index;
	index = 0;
	XYLINE[index].Set_BP(31);
	XYLINE[index].Set_VER(XYLINE[index].Get_BP());
	XYLINE[index].Set_ORD(3);
	XYLINE[index].Set_BPARR(XYLINE[index].Get_BP()+XYLINE[index].Get_ORD());
	XYLINE[index].Set_VERARR(XYLINE[index].Get_VER()+XYLINE[index].Get_ORD());
	XYLINE[index].Set_NUM(141);

	index = 0;	//st 10
	YZLINE[index].Set_BP(6);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(16);
	
	index = 1;	//st 11
	YZLINE[index].Set_BP(7);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(21);

	index = 2;	//st 12
	YZLINE[index].Set_BP(8);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(26);
	
	index = 3;	//st 13
	YZLINE[index].Set_BP(10);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(36);

	index = 4;	//st 14
	YZLINE[index].Set_BP(13);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(51);
	
	index = 5;	//st 15
	YZLINE[index].Set_BP(17);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(71);

	index = 6;	//st 16
	YZLINE[index].Set_BP(19);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(81);
	
	index = 7;	//st 17
	YZLINE[index].Set_BP(21);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(91);

	index = 8;	//st 18
	YZLINE[index].Set_BP(20);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(86);
	
	index = 9;	//st 18.5
	YZLINE[index].Set_BP(20);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(86);

	index = 10;	//st 19
	YZLINE[index].Set_BP(20);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(86);
	
	index = 11;	//st 19.5
	YZLINE[index].Set_BP(20);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(86);
	
	index = 12;	//st 19.5~
	YZLINE[index].Set_BP(20);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(86);

	index = 13;	//st 20
	YZLINE[index].Set_BP(20);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(86);
	
	index = 14;	//st 20.23
	YZLINE[index].Set_BP(19);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(81);

	index = 15;	//st 20.45
	YZLINE[index].Set_BP(15);
	YZLINE[index].Set_VER(YZLINE[index].Get_BP());
	YZLINE[index].Set_ORD(3);
	YZLINE[index].Set_BPARR(YZLINE[index].Get_BP()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_VERARR(YZLINE[index].Get_VER()+YZLINE[index].Get_ORD());
	YZLINE[index].Set_NUM(61);

	index = 0;
	XZLINE[index].Set_BP(8);
	XZLINE[index].Set_VER(XZLINE[index].Get_BP());
	XZLINE[index].Set_ORD(4);
	XZLINE[index].Set_BPARR(XZLINE[index].Get_BP()+XZLINE[index].Get_ORD());
	XZLINE[index].Set_VERARR(XZLINE[index].Get_VER()+XZLINE[index].Get_ORD());
	XZLINE[index].Set_NUM(21);

	BP_xy = new BP*[XYLNum];
	for(index=0;index<XYLNum;index++)
	{
		BP_xy[index] = new BP[XYLINE[index].Get_BP()];
	}
	CP_xy = new VP*[XYLNum];
	for(index=0;index<XYLNum;index++)
	{
		CP_xy[index] = new VP[XYLINE[index].Get_VER()];
	}
	BSPL_xy = new BSPLINE_XY[XYLNum];

	
	BP_yz = new BP*[YZLNum];
	for(index=0;index<YZLNum;index++)
	{
		BP_yz[index] = new BP[YZLINE[index].Get_BP()];
	}
	CP_yz = new VP*[YZLNum];
	for(index=0;index<YZLNum;index++)
	{
		CP_yz[index] = new VP[YZLINE[index].Get_VER()];
	}
	BSPL_yz = new BSPLINE_YZ[YZLNum];

		
	BP_xz = new BP*[XZLNum];
	for(index=0;index<XZLNum;index++)
	{
		BP_xz[index] = new BP[XZLINE[index].Get_BP()];
	}
	CP_xz = new VP*[XZLNum];
	for(index=0;index<XZLNum;index++)
	{
		CP_xz[index] = new VP[XZLINE[index].Get_BP()];
	}
	BSPL_xz = new BSPLINE_XZ[XZLNum];
}

void CMy3D_view_FPbody_modelDoc::Init_BP_XY()
{
/*	int i;
	int index;
	index = 0;
	double *anglexy = new double;
	*anglexy = 0.0;
	for(i=0;i<XYLINE[index].Get_BP();i++)								//init the cycle							
	{																	
		BP_xy[index][i].Set_x(1.0*cos(GetMethod->ang_to_rad(*anglexy)));									
		BP_xy[index][i].Set_y(1.0*sin(GetMethod->ang_to_rad(*anglexy)));
		BP_xy[index][i].Set_z(0);
		BP_xy[index][i].Catch = FALSE;
		BP_xy[index][i].LineStatus = 1;
		*anglexy += 360.0 / (XYLINE[index].Get_BP()-1);
	}		
	delete anglexy;
*/	
	int index;
	int i;

	for(index=0;index<XYLNum;index++)
	{
		for(i=0;i<XYLINE[index].Get_BP();i++)								//init the cycle							
		{
			BP_xy[index][i].Catch = FALSE;
			BP_xy[index][i].Set_z(0.0);
		}
	}

	index = 0;
	BP_xy[index][0].Set_x(-132.025);
	BP_xy[index][1].Set_x(-118.823);
	BP_xy[index][2].Set_x(-105.620);
	BP_xy[index][3].Set_x(-92.418);
	BP_xy[index][4].Set_x(-79.215);
	BP_xy[index][5].Set_x(-66.013);
	BP_xy[index][6].Set_x(-52.810);
	BP_xy[index][7].Set_x(-39.608);
	BP_xy[index][8].Set_x(-26.405);
	BP_xy[index][9].Set_x(-19.804);
	BP_xy[index][10].Set_x(-13.203);
	BP_xy[index][11].Set_x(-6.601);
	BP_xy[index][12].Set_x(-4.000);
	BP_xy[index][13].Set_x(0.000);
	BP_xy[index][14].Set_x(3.037);
	BP_xy[index][15].Set_x(5.941);
	BP_xy[index][16].Set_x(7.769);
	BP_xy[index][17].Set_x(8.406);
	BP_xy[index][18].Set_x(8.948);
	BP_xy[index][19].Set_x(9.075);
	BP_xy[index][20].Set_x(8.789);
	BP_xy[index][21].Set_x(7.705);
	BP_xy[index][22].Set_x(5.941);
	BP_xy[index][23].Set_x(3.037);
	BP_xy[index][24].Set_x(0.000);
	BP_xy[index][25].Set_x(0.000);
	BP_xy[index][26].Set_x(0.034);
	BP_xy[index][27].Set_x(0.524);
	BP_xy[index][28].Set_x(1.267);
	BP_xy[index][29].Set_x(3.037);
	BP_xy[index][30].Set_x(5.941);
	
	BP_xy[index][0].Set_y(0.0);
	BP_xy[index][1].Set_y(0.0);
	BP_xy[index][2].Set_y(0.0);
	BP_xy[index][3].Set_y(0.0);
	BP_xy[index][4].Set_y(0.0);
	BP_xy[index][5].Set_y(0.0);
	BP_xy[index][6].Set_y(0.0);
	BP_xy[index][7].Set_y(0.0);
	BP_xy[index][8].Set_y(0.0);
	BP_xy[index][9].Set_y(0.0);
	BP_xy[index][10].Set_y(0.0);
	BP_xy[index][11].Set_y(0.0);
	BP_xy[index][12].Set_y(0.0);
	BP_xy[index][13].Set_y(1.252);
	BP_xy[index][14].Set_y(2.340);
	BP_xy[index][15].Set_y(4.206);
	BP_xy[index][16].Set_y(6);
	BP_xy[index][17].Set_y(7);
	BP_xy[index][18].Set_y(8);
	BP_xy[index][19].Set_y(9);
	BP_xy[index][20].Set_y(10);
	BP_xy[index][21].Set_y(11);
	BP_xy[index][22].Set_y(11.198);
	BP_xy[index][23].Set_y(11.516);
	BP_xy[index][24].Set_y(11.947);
	BP_xy[index][25].Set_y(12.3);
	BP_xy[index][26].Set_y(13);
	BP_xy[index][27].Set_y(14.5);
	BP_xy[index][28].Set_y(16);
	BP_xy[index][29].Set_y(18.640);
	BP_xy[index][30].Set_y(23.013);
}

void CMy3D_view_FPbody_modelDoc::Init_BP_YZ()
{
/*	int i;
	int index;
	index = 0;
	double *angleyz = new double;
	*angleyz = 0.0;
	for(i=0;i<YZLINE[index].Get_BP();i++)								//init the cycle							
	{																	
		BP_yz[index][i].Set_x(0);									
		BP_yz[index][i].Set_y(1.0*cos(GetMethod->ang_to_rad(*angleyz)));
		BP_yz[index][i].Set_z(1.0*sin(GetMethod->ang_to_rad(*angleyz)));
		BP_yz[index][i].Catch = FALSE;
		BP_yz[index][i].LineStatus = 1;
		*angleyz += 360.0 / (YZLINE[index].Get_BP()-1);
	}		
	delete angleyz;
*/
	int i;
	int index;
	
	for(index=0;index<YZLNum;index++)
	{
		for(i=0;i<YZLINE[index].Get_BP();i++)								//init the cycle							
		{																	
			BP_yz[index][i].Catch = FALSE;
	//		BP_yz[index][i].Set_x(BP_xy[0][index].Get_x());
		}
	}
	
	index = 0;	//st 10
	BP_yz[index][0].Set_x(-132.025);
	BP_yz[index][1].Set_x(-132.025);
	BP_yz[index][2].Set_x(-132.025);
	BP_yz[index][3].Set_x(-132.025);
	BP_yz[index][4].Set_x(-132.025);
	BP_yz[index][5].Set_x(-132.025);

	BP_yz[index][0].Set_z(13.517);
	BP_yz[index][1].Set_z(17.469);
	BP_yz[index][2].Set_z(18.718);
	BP_yz[index][3].Set_z(19.466);
	BP_yz[index][4].Set_z(20.000);
	BP_yz[index][5].Set_z(20.000);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(3.910);
	BP_yz[index][5].Set_y(24.200);

	index = 1;	//st 11
	BP_yz[index][0].Set_x(-118.823);
	BP_yz[index][1].Set_x(-118.823);
	BP_yz[index][2].Set_x(-118.823);
	BP_yz[index][3].Set_x(-118.823);
	BP_yz[index][4].Set_x(-118.823);
	BP_yz[index][5].Set_x(-118.823);
	BP_yz[index][6].Set_x(-118.823);

	BP_yz[index][0].Set_z(12.406);
	BP_yz[index][1].Set_z(16.799);
	BP_yz[index][2].Set_z(18.306);
	BP_yz[index][3].Set_z(19.265);
	BP_yz[index][4].Set_z(19.873);
	BP_yz[index][5].Set_z(20.000);
	BP_yz[index][6].Set_z(20.000);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(4.100);
	BP_yz[index][6].Set_y(24.200);

	index = 2;	//st 12
	BP_yz[index][0].Set_x(-105.620);
	BP_yz[index][1].Set_x(-105.620);
	BP_yz[index][2].Set_x(-105.620);
	BP_yz[index][3].Set_x(-105.620);
	BP_yz[index][4].Set_x(-105.620);
	BP_yz[index][5].Set_x(-105.620);
	BP_yz[index][6].Set_x(-105.620);
	BP_yz[index][7].Set_x(-105.620);

	BP_yz[index][0].Set_z(11.001);
	BP_yz[index][1].Set_z(15.632);
	BP_yz[index][2].Set_z(17.338);
	BP_yz[index][3].Set_z(18.464);
	BP_yz[index][4].Set_z(19.316);
	BP_yz[index][5].Set_z(19.887);
	BP_yz[index][6].Set_z(20.000);
	BP_yz[index][7].Set_z(20.000);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.100);
	BP_yz[index][6].Set_y(5.275);
	BP_yz[index][7].Set_y(24.200);

	index = 3;	//st 13
	BP_yz[index][0].Set_x(-92.418);
	BP_yz[index][1].Set_x(-92.418);
	BP_yz[index][2].Set_x(-92.418);
	BP_yz[index][3].Set_x(-92.418);
	BP_yz[index][4].Set_x(-92.418);
	BP_yz[index][5].Set_x(-92.418);
	BP_yz[index][6].Set_x(-92.418);
	BP_yz[index][7].Set_x(-92.418);
	BP_yz[index][8].Set_x(-92.418);
	BP_yz[index][9].Set_x(-92.418);

	BP_yz[index][0].Set_z(9.018);
	BP_yz[index][1].Set_z(14.029);
	BP_yz[index][2].Set_z(15.875);
	BP_yz[index][3].Set_z(17.152);
	BP_yz[index][4].Set_z(18.138);
	BP_yz[index][5].Set_z(18.941);
	BP_yz[index][6].Set_z(19.528);
	BP_yz[index][7].Set_z(19.922);
	BP_yz[index][8].Set_z(20.000);
	BP_yz[index][9].Set_z(20.000);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(7.394);
	BP_yz[index][9].Set_y(24.200);

	index = 4;	//st 14
	BP_yz[index][0].Set_x(-79.215);
	BP_yz[index][1].Set_x(-79.215);
	BP_yz[index][2].Set_x(-79.215);
	BP_yz[index][3].Set_x(-79.215);
	BP_yz[index][4].Set_x(-79.215);
	BP_yz[index][5].Set_x(-79.215);
	BP_yz[index][6].Set_x(-79.215);
	BP_yz[index][7].Set_x(-79.215);
	BP_yz[index][8].Set_x(-79.215);
	BP_yz[index][9].Set_x(-79.215);
	BP_yz[index][10].Set_x(-79.215);
	BP_yz[index][11].Set_x(-79.215);
	BP_yz[index][12].Set_x(-79.215);

	BP_yz[index][0].Set_z(6.196);
	BP_yz[index][1].Set_z(11.304);
	BP_yz[index][2].Set_z(13.404);
	BP_yz[index][3].Set_z(14.934);
	BP_yz[index][4].Set_z(16.146);
	BP_yz[index][5].Set_z(17.141);
	BP_yz[index][6].Set_z(17.974);
	BP_yz[index][7].Set_z(18.650);
	BP_yz[index][8].Set_z(19.199);
	BP_yz[index][9].Set_z(19.622);
	BP_yz[index][10].Set_z(19.886);
	BP_yz[index][11].Set_z(20.000);
	BP_yz[index][12].Set_z(20.000);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(10.592);
	BP_yz[index][12].Set_y(24.200);

	index = 5;	//st 15
	BP_yz[index][0].Set_x(-66.013);
	BP_yz[index][1].Set_x(-66.013);
	BP_yz[index][2].Set_x(-66.013);
	BP_yz[index][3].Set_x(-66.013);
	BP_yz[index][4].Set_x(-66.013);
	BP_yz[index][5].Set_x(-66.013);
	BP_yz[index][6].Set_x(-66.013);
	BP_yz[index][7].Set_x(-66.013);
	BP_yz[index][8].Set_x(-66.013);
	BP_yz[index][9].Set_x(-66.013);
	BP_yz[index][10].Set_x(-66.013);
	BP_yz[index][11].Set_x(-66.013);
	BP_yz[index][12].Set_x(-66.013);
	BP_yz[index][13].Set_x(-66.013);
	BP_yz[index][14].Set_x(-66.013);
	BP_yz[index][15].Set_x(-66.013);
	BP_yz[index][16].Set_x(-66.013);

	BP_yz[index][0].Set_z(2.003);
	BP_yz[index][1].Set_z(7.980);
	BP_yz[index][2].Set_z(10.216);
	BP_yz[index][3].Set_z(11.870);
	BP_yz[index][4].Set_z(13.217);
	BP_yz[index][5].Set_z(14.356);
	BP_yz[index][6].Set_z(15.353);
	BP_yz[index][7].Set_z(16.246);
	BP_yz[index][8].Set_z(17.038);
	BP_yz[index][9].Set_z(17.740);
	BP_yz[index][10].Set_z(18.354);
	BP_yz[index][11].Set_z(18.882);
	BP_yz[index][12].Set_z(19.312);
	BP_yz[index][13].Set_z(19.633);
	BP_yz[index][14].Set_z(19.929);
	BP_yz[index][15].Set_z(20.000);
	BP_yz[index][16].Set_z(20.000);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(14.751);
	BP_yz[index][16].Set_y(24.200);

	index = 6;	//st 16
	BP_yz[index][0].Set_x(-52.810);
	BP_yz[index][1].Set_x(-52.810);
	BP_yz[index][2].Set_x(-52.810);
	BP_yz[index][3].Set_x(-52.810);
	BP_yz[index][4].Set_x(-52.810);
	BP_yz[index][5].Set_x(-52.810);
	BP_yz[index][6].Set_x(-52.810);
	BP_yz[index][7].Set_x(-52.810);
	BP_yz[index][8].Set_x(-52.810);
	BP_yz[index][9].Set_x(-52.810);
	BP_yz[index][10].Set_x(-52.810);
	BP_yz[index][11].Set_x(-52.810);
	BP_yz[index][12].Set_x(-52.810);
	BP_yz[index][13].Set_x(-52.810);
	BP_yz[index][14].Set_x(-52.810);
	BP_yz[index][15].Set_x(-52.810);
	BP_yz[index][16].Set_x(-52.810);
	BP_yz[index][17].Set_x(-52.810);
	BP_yz[index][18].Set_x(-52.810);

	BP_yz[index][0].Set_z(0.583);
	BP_yz[index][1].Set_z(5.356);
	BP_yz[index][2].Set_z(7.103);
	BP_yz[index][3].Set_z(8.420);
	BP_yz[index][4].Set_z(9.598);
	BP_yz[index][5].Set_z(10.677);
	BP_yz[index][6].Set_z(11.684);
	BP_yz[index][7].Set_z(12.651);
	BP_yz[index][8].Set_z(13.581);
	BP_yz[index][9].Set_z(14.471);
	BP_yz[index][10].Set_z(15.328);
	BP_yz[index][11].Set_z(16.159);
	BP_yz[index][12].Set_z(16.935);
	BP_yz[index][13].Set_z(17.624);
	BP_yz[index][14].Set_z(18.572);
	BP_yz[index][15].Set_z(19.322);
	BP_yz[index][16].Set_z(19.877);
	BP_yz[index][17].Set_z(20.000);
	BP_yz[index][18].Set_z(20.000);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(16.000);
	BP_yz[index][16].Set_y(18.000);
	BP_yz[index][17].Set_y(18.601);
	BP_yz[index][18].Set_y(24.200);

	index = 7;	//st 17
	BP_yz[index][0].Set_x(-39.608);
	BP_yz[index][1].Set_x(-39.608);
	BP_yz[index][2].Set_x(-39.608);
	BP_yz[index][3].Set_x(-39.608);
	BP_yz[index][4].Set_x(-39.608);
	BP_yz[index][5].Set_x(-39.608);
	BP_yz[index][6].Set_x(-39.608);
	BP_yz[index][7].Set_x(-39.608);
	BP_yz[index][8].Set_x(-39.608);
	BP_yz[index][9].Set_x(-39.608);
	BP_yz[index][10].Set_x(-39.608);
	BP_yz[index][11].Set_x(-39.608);
	BP_yz[index][12].Set_x(-39.608);
	BP_yz[index][13].Set_x(-39.608);
	BP_yz[index][14].Set_x(-39.608);
	BP_yz[index][15].Set_x(-39.608);
	BP_yz[index][16].Set_x(-39.608);
	BP_yz[index][17].Set_x(-39.608);
	BP_yz[index][18].Set_x(-39.608);
	BP_yz[index][19].Set_x(-39.608);
	BP_yz[index][20].Set_x(-39.608);

	BP_yz[index][0].Set_z(0.124);
	BP_yz[index][1].Set_z(3.602);
	BP_yz[index][2].Set_z(4.805);
	BP_yz[index][3].Set_z(5.656);
	BP_yz[index][4].Set_z(6.434);
	BP_yz[index][5].Set_z(7.181);
	BP_yz[index][6].Set_z(7.919);
	BP_yz[index][7].Set_z(8.674);
	BP_yz[index][8].Set_z(9.438);
	BP_yz[index][9].Set_z(10.248);
	BP_yz[index][10].Set_z(11.052);
	BP_yz[index][11].Set_z(11.859);
	BP_yz[index][12].Set_z(12.734);
	BP_yz[index][13].Set_z(13.663);
	BP_yz[index][14].Set_z(15.032);
	BP_yz[index][15].Set_z(16.321);
	BP_yz[index][16].Set_z(17.837);
	BP_yz[index][17].Set_z(19.014);
	BP_yz[index][18].Set_z(19.797);
	BP_yz[index][19].Set_z(20.000);
	BP_yz[index][20].Set_z(20.000);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(16.000);
	BP_yz[index][16].Set_y(18.000);
	BP_yz[index][17].Set_y(20.000);
	BP_yz[index][18].Set_y(22.000);
	BP_yz[index][19].Set_y(22.924);
	BP_yz[index][20].Set_y(24.200);
	
	index = 8;	//st 18
	BP_yz[index][0].Set_x(-26.405);
	BP_yz[index][1].Set_x(-26.405);
	BP_yz[index][2].Set_x(-26.405);
	BP_yz[index][3].Set_x(-26.405);
	BP_yz[index][4].Set_x(-26.405);
	BP_yz[index][5].Set_x(-26.405);
	BP_yz[index][6].Set_x(-26.405);
	BP_yz[index][7].Set_x(-26.405);
	BP_yz[index][8].Set_x(-26.405);
	BP_yz[index][9].Set_x(-26.405);
	BP_yz[index][10].Set_x(-26.405);
	BP_yz[index][11].Set_x(-26.405);
	BP_yz[index][12].Set_x(-26.405);
	BP_yz[index][13].Set_x(-26.405);
	BP_yz[index][14].Set_x(-26.405);
	BP_yz[index][15].Set_x(-26.405);
	BP_yz[index][16].Set_x(-26.405);
	BP_yz[index][17].Set_x(-26.405);
	BP_yz[index][18].Set_x(-26.405);
	BP_yz[index][19].Set_x(-26.405);

	BP_yz[index][0].Set_z(0.100);
	BP_yz[index][1].Set_z(2.577);
	BP_yz[index][2].Set_z(3.442);
	BP_yz[index][3].Set_z(3.967);
	BP_yz[index][4].Set_z(4.341);
	BP_yz[index][5].Set_z(4.643);
	BP_yz[index][6].Set_z(4.932);
	BP_yz[index][7].Set_z(5.224);
	BP_yz[index][8].Set_z(5.554);
	BP_yz[index][9].Set_z(5.931);
	BP_yz[index][10].Set_z(6.346);
	BP_yz[index][11].Set_z(6.845);
	BP_yz[index][12].Set_z(7.479);
	BP_yz[index][13].Set_z(8.235);
	BP_yz[index][14].Set_z(9.516);
	BP_yz[index][15].Set_z(10.921);
	BP_yz[index][16].Set_z(13.033);
	BP_yz[index][17].Set_z(15.277);
	BP_yz[index][18].Set_z(17.449);
	BP_yz[index][19].Set_z(19.250);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(16.000);
	BP_yz[index][16].Set_y(18.000);
	BP_yz[index][17].Set_y(20.000);
	BP_yz[index][18].Set_y(22.000);
	BP_yz[index][19].Set_y(24.200);

	index = 9;	//st 18.5
	BP_yz[index][0].Set_x(-19.804);
	BP_yz[index][1].Set_x(-19.804);
	BP_yz[index][2].Set_x(-19.804);
	BP_yz[index][3].Set_x(-19.804);
	BP_yz[index][4].Set_x(-19.804);
	BP_yz[index][5].Set_x(-19.804);
	BP_yz[index][6].Set_x(-19.804);
	BP_yz[index][7].Set_x(-19.804);
	BP_yz[index][8].Set_x(-19.804);
	BP_yz[index][9].Set_x(-19.804);
	BP_yz[index][10].Set_x(-19.804);
	BP_yz[index][11].Set_x(-19.804);
	BP_yz[index][12].Set_x(-19.804);
	BP_yz[index][13].Set_x(-19.804);
	BP_yz[index][14].Set_x(-19.804);
	BP_yz[index][15].Set_x(-19.804);
	BP_yz[index][16].Set_x(-19.804);
	BP_yz[index][17].Set_x(-19.804);
	BP_yz[index][18].Set_x(-19.804);
	BP_yz[index][19].Set_x(-19.804);

	BP_yz[index][0].Set_z(0.110);
	BP_yz[index][1].Set_z(2.286);
	BP_yz[index][2].Set_z(2.979);
	BP_yz[index][3].Set_z(3.414);
	BP_yz[index][4].Set_z(3.673);
	BP_yz[index][5].Set_z(3.815);
	BP_yz[index][6].Set_z(3.893);
	BP_yz[index][7].Set_z(3.951);
	BP_yz[index][8].Set_z(4.012);
	BP_yz[index][9].Set_z(4.115);
	BP_yz[index][10].Set_z(4.320);
	BP_yz[index][11].Set_z(4.603);
	BP_yz[index][12].Set_z(4.959);
	BP_yz[index][13].Set_z(5.458);
	BP_yz[index][14].Set_z(6.511);
	BP_yz[index][15].Set_z(7.872);
	BP_yz[index][16].Set_z(10.049);
	BP_yz[index][17].Set_z(12.543);
	BP_yz[index][18].Set_z(15.057);
	BP_yz[index][19].Set_z(17.488);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(16.000);
	BP_yz[index][16].Set_y(18.000);
	BP_yz[index][17].Set_y(20.000);
	BP_yz[index][18].Set_y(22.000);
	BP_yz[index][19].Set_y(24.200);

	index = 10;	//st 19
	BP_yz[index][0].Set_x(-13.203);
	BP_yz[index][1].Set_x(-13.203);
	BP_yz[index][2].Set_x(-13.203);
	BP_yz[index][3].Set_x(-13.203);
	BP_yz[index][4].Set_x(-13.203);
	BP_yz[index][5].Set_x(-13.203);
	BP_yz[index][6].Set_x(-13.203);
	BP_yz[index][7].Set_x(-13.203);
	BP_yz[index][8].Set_x(-13.203);
	BP_yz[index][9].Set_x(-13.203);
	BP_yz[index][10].Set_x(-13.203);
	BP_yz[index][11].Set_x(-13.203);
	BP_yz[index][12].Set_x(-13.203);
	BP_yz[index][13].Set_x(-13.203);
	BP_yz[index][14].Set_x(-13.203);
	BP_yz[index][15].Set_x(-13.203);
	BP_yz[index][16].Set_x(-13.203);
	BP_yz[index][17].Set_x(-13.203);
	BP_yz[index][18].Set_x(-13.203);
	BP_yz[index][19].Set_x(-13.203);

	BP_yz[index][0].Set_z(0.112);
	BP_yz[index][1].Set_z(1.982);
	BP_yz[index][2].Set_z(2.596);
	BP_yz[index][3].Set_z(2.988);
	BP_yz[index][4].Set_z(3.195);
	BP_yz[index][5].Set_z(3.258);
	BP_yz[index][6].Set_z(3.215);
	BP_yz[index][7].Set_z(3.104);
	BP_yz[index][8].Set_z(2.954);
	BP_yz[index][9].Set_z(2.804);
	BP_yz[index][10].Set_z(2.723);
	BP_yz[index][11].Set_z(2.710);
	BP_yz[index][12].Set_z(2.780);
	BP_yz[index][13].Set_z(3.087);
	BP_yz[index][14].Set_z(3.833);
	BP_yz[index][15].Set_z(4.987);
	BP_yz[index][16].Set_z(7.036);
	BP_yz[index][17].Set_z(9.433);
	BP_yz[index][18].Set_z(11.867);
	BP_yz[index][19].Set_z(14.527);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(16.000);
	BP_yz[index][16].Set_y(18.000);
	BP_yz[index][17].Set_y(20.000);
	BP_yz[index][18].Set_y(22.000);
	BP_yz[index][19].Set_y(24.200);

	index = 11;	//st 19.5
	BP_yz[index][0].Set_x(-6.601);
	BP_yz[index][1].Set_x(-6.601);
	BP_yz[index][2].Set_x(-6.601);
	BP_yz[index][3].Set_x(-6.601);
	BP_yz[index][4].Set_x(-6.601);
	BP_yz[index][5].Set_x(-6.601);
	BP_yz[index][6].Set_x(-6.601);
	BP_yz[index][7].Set_x(-6.601);
	BP_yz[index][8].Set_x(-6.601);
	BP_yz[index][9].Set_x(-6.601);
	BP_yz[index][10].Set_x(-6.601);
	BP_yz[index][11].Set_x(-6.601);
	BP_yz[index][12].Set_x(-6.601);
	BP_yz[index][13].Set_x(-6.601);
	BP_yz[index][14].Set_x(-6.601);
	BP_yz[index][15].Set_x(-6.601);
	BP_yz[index][16].Set_x(-6.601);
	BP_yz[index][17].Set_x(-6.601);
	BP_yz[index][18].Set_x(-6.601);
	BP_yz[index][19].Set_x(-6.601);

	BP_yz[index][0].Set_z(0.000);
	BP_yz[index][1].Set_z(1.538);
	BP_yz[index][2].Set_z(2.160);
	BP_yz[index][3].Set_z(2.550);
	BP_yz[index][4].Set_z(2.778);
	BP_yz[index][5].Set_z(2.891);
	BP_yz[index][6].Set_z(2.894);
	BP_yz[index][7].Set_z(2.784);
	BP_yz[index][8].Set_z(2.569);
	BP_yz[index][9].Set_z(2.231);
	BP_yz[index][10].Set_z(1.760);
	BP_yz[index][11].Set_z(1.385);
	BP_yz[index][12].Set_z(1.247);
	BP_yz[index][13].Set_z(1.279);
	BP_yz[index][14].Set_z(1.685);
	BP_yz[index][15].Set_z(2.532);
	BP_yz[index][16].Set_z(4.262);
	BP_yz[index][17].Set_z(6.237);
	BP_yz[index][18].Set_z(8.428);
	BP_yz[index][19].Set_z(10.884);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(16.000);
	BP_yz[index][16].Set_y(18.000);
	BP_yz[index][17].Set_y(20.000);
	BP_yz[index][18].Set_y(22.000);
	BP_yz[index][19].Set_y(24.200);

	index = 12;	//st 19.5~
	BP_yz[index][0].Set_x(-4.000);
	BP_yz[index][1].Set_x(-4.000);
	BP_yz[index][2].Set_x(-4.000);
	BP_yz[index][3].Set_x(-4.000);
	BP_yz[index][4].Set_x(-4.000);
	BP_yz[index][5].Set_x(-4.000);
	BP_yz[index][6].Set_x(-4.000);
	BP_yz[index][7].Set_x(-4.000);
	BP_yz[index][8].Set_x(-4.000);
	BP_yz[index][9].Set_x(-4.000);
	BP_yz[index][10].Set_x(-4.000);
	BP_yz[index][11].Set_x(-4.000);
	BP_yz[index][12].Set_x(-4.000);
	BP_yz[index][13].Set_x(-4.000);
	BP_yz[index][14].Set_x(-4.000);
	BP_yz[index][15].Set_x(-4.000);
	BP_yz[index][16].Set_x(-4.000);
	BP_yz[index][17].Set_x(-4.000);
	BP_yz[index][18].Set_x(-4.000);
	BP_yz[index][19].Set_x(-4.000);

	BP_yz[index][0].Set_z(0.000);
	BP_yz[index][1].Set_z(1.538);
	BP_yz[index][2].Set_z(2.160);
	BP_yz[index][3].Set_z(2.550);
	BP_yz[index][4].Set_z(2.778);
	BP_yz[index][5].Set_z(2.891);
	BP_yz[index][6].Set_z(2.894);
	BP_yz[index][7].Set_z(2.784);
	BP_yz[index][8].Set_z(2.569);
	BP_yz[index][9].Set_z(2.231);
	BP_yz[index][10].Set_z(1.760);
	BP_yz[index][11].Set_z(1.385);
	BP_yz[index][12].Set_z(1.247);
	BP_yz[index][13].Set_z(1.279);
	BP_yz[index][14].Set_z(1.685);
	BP_yz[index][15].Set_z(2.532);
	BP_yz[index][16].Set_z(4.262);
	BP_yz[index][17].Set_z(6.237);
	BP_yz[index][18].Set_z(8.428);
	BP_yz[index][19].Set_z(10.884);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(16.000);
	BP_yz[index][16].Set_y(18.000);
	BP_yz[index][17].Set_y(20.000);
	BP_yz[index][18].Set_y(22.000);
	BP_yz[index][19].Set_y(24.200);

	index = 13;	//st 20
	BP_yz[index][0].Set_x(0.000);
	BP_yz[index][1].Set_x(0.000);
	BP_yz[index][2].Set_x(0.000);
	BP_yz[index][3].Set_x(0.000);
	BP_yz[index][4].Set_x(0.000);
	BP_yz[index][5].Set_x(0.000);
	BP_yz[index][6].Set_x(0.000);
	BP_yz[index][7].Set_x(0.000);
	BP_yz[index][8].Set_x(0.000);
	BP_yz[index][9].Set_x(0.000);
	BP_yz[index][10].Set_x(0.000);
	BP_yz[index][11].Set_x(0.000);
	BP_yz[index][12].Set_x(0.000);
	BP_yz[index][13].Set_x(0.000);
	BP_yz[index][14].Set_x(0.000);
	BP_yz[index][15].Set_x(0.000);
	BP_yz[index][16].Set_x(0.000);
	BP_yz[index][17].Set_x(0.000);
	BP_yz[index][18].Set_x(0.000);
	BP_yz[index][19].Set_x(0.000);

	BP_yz[index][0].Set_z(0.000);
	BP_yz[index][1].Set_z(0.000);
	BP_yz[index][2].Set_z(1.195);
	BP_yz[index][3].Set_z(1.825);
	BP_yz[index][4].Set_z(2.310);
	BP_yz[index][5].Set_z(2.652);
	BP_yz[index][6].Set_z(2.901);
	BP_yz[index][7].Set_z(2.768);
	BP_yz[index][8].Set_z(2.497);
	BP_yz[index][9].Set_z(2.060);
	BP_yz[index][10].Set_z(1.301);
	BP_yz[index][11].Set_z(0.000);
	BP_yz[index][12].Set_z(0.000);
	BP_yz[index][13].Set_z(0.029);
	BP_yz[index][14].Set_z(0.148);
	BP_yz[index][15].Set_z(0.603);
	BP_yz[index][16].Set_z(1.551);
	BP_yz[index][17].Set_z(2.981);
	BP_yz[index][18].Set_z(4.700);
	BP_yz[index][19].Set_z(6.815);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(1.000);
	BP_yz[index][2].Set_y(2.000);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(12.000);
	BP_yz[index][13].Set_y(13.000);
	BP_yz[index][14].Set_y(14.500);
	BP_yz[index][15].Set_y(16.000);
	BP_yz[index][16].Set_y(18.000);
	BP_yz[index][17].Set_y(20.000);
	BP_yz[index][18].Set_y(22.000);
	BP_yz[index][19].Set_y(24.200);

	index = 14;	//st 20.23
	BP_yz[index][0].Set_x(3.037);
	BP_yz[index][1].Set_x(3.037);
	BP_yz[index][2].Set_x(3.037);
	BP_yz[index][3].Set_x(3.037);
	BP_yz[index][4].Set_x(3.037);
	BP_yz[index][5].Set_x(3.037);
	BP_yz[index][6].Set_x(3.037);
	BP_yz[index][7].Set_x(3.037);
	BP_yz[index][8].Set_x(3.037);
	BP_yz[index][9].Set_x(3.037);
	BP_yz[index][10].Set_x(3.037);
	BP_yz[index][11].Set_x(3.037);
	BP_yz[index][12].Set_x(3.037);
	BP_yz[index][13].Set_x(3.037);
	BP_yz[index][14].Set_x(3.037);
	BP_yz[index][15].Set_x(3.037);
	BP_yz[index][16].Set_x(3.037);
	BP_yz[index][17].Set_x(3.037);
	BP_yz[index][18].Set_x(3.037);
	BP_yz[index][19].Set_x(3.037);

	BP_yz[index][0].Set_z(0.000);
	BP_yz[index][1].Set_z(0.000);
	BP_yz[index][2].Set_z(0.000);
	BP_yz[index][3].Set_z(1.353);
	BP_yz[index][4].Set_z(2.045);
	BP_yz[index][5].Set_z(2.481);
	BP_yz[index][6].Set_z(2.753);
	BP_yz[index][7].Set_z(2.893);
	BP_yz[index][8].Set_z(2.890);
	BP_yz[index][9].Set_z(2.686);
	BP_yz[index][10].Set_z(2.125);
	BP_yz[index][11].Set_z(0.697);
	BP_yz[index][12].Set_z(0.000);
	BP_yz[index][13].Set_z(0.000);
	BP_yz[index][14].Set_z(0.000);
	BP_yz[index][15].Set_z(0.000);
	BP_yz[index][16].Set_z(1.590);
	BP_yz[index][17].Set_z(3.135);
	BP_yz[index][18].Set_z(5.042);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(2.000);
	BP_yz[index][2].Set_y(2.340);
	BP_yz[index][3].Set_y(3.000);
	BP_yz[index][4].Set_y(4.000);
	BP_yz[index][5].Set_y(5.000);
	BP_yz[index][6].Set_y(6.000);
	BP_yz[index][7].Set_y(7.000);
	BP_yz[index][8].Set_y(8.000);
	BP_yz[index][9].Set_y(9.000);
	BP_yz[index][10].Set_y(10.000);
	BP_yz[index][11].Set_y(11.000);
	BP_yz[index][12].Set_y(11.516);
	BP_yz[index][13].Set_y(12.000);
	BP_yz[index][14].Set_y(18.000);
	BP_yz[index][15].Set_y(18.640);
	BP_yz[index][16].Set_y(20.000);
	BP_yz[index][17].Set_y(22.000);
	BP_yz[index][18].Set_y(24.200);
	
	index = 15;	//st 20.45
	BP_yz[index][0].Set_x(5.941);
	BP_yz[index][1].Set_x(5.941);
	BP_yz[index][2].Set_x(5.941);
	BP_yz[index][3].Set_x(5.941);
	BP_yz[index][4].Set_x(5.941);
	BP_yz[index][5].Set_x(5.941);
	BP_yz[index][6].Set_x(5.941);
	BP_yz[index][7].Set_x(5.941);
	BP_yz[index][8].Set_x(5.941);
	BP_yz[index][9].Set_x(5.941);
	BP_yz[index][10].Set_x(5.941);
	BP_yz[index][11].Set_x(5.941);
	BP_yz[index][12].Set_x(5.941);
	BP_yz[index][13].Set_x(5.941);
	BP_yz[index][14].Set_x(5.941);

	BP_yz[index][0].Set_z(0.000);
	BP_yz[index][1].Set_z(0.000);
	BP_yz[index][2].Set_z(0.000);
	BP_yz[index][3].Set_z(1.300);
	BP_yz[index][4].Set_z(1.910);
	BP_yz[index][5].Set_z(2.258);
	BP_yz[index][6].Set_z(2.420);
	BP_yz[index][7].Set_z(2.400);
	BP_yz[index][8].Set_z(2.110);
	BP_yz[index][9].Set_z(1.320);
	BP_yz[index][10].Set_z(0.000);
	BP_yz[index][11].Set_z(0.000);
	BP_yz[index][12].Set_z(0.000);
	BP_yz[index][13].Set_z(0.000);
	BP_yz[index][14].Set_z(2.343);

	BP_yz[index][0].Set_y(0.000);
	BP_yz[index][1].Set_y(4.000);
	BP_yz[index][2].Set_y(4.206);
	BP_yz[index][3].Set_y(5.000);
	BP_yz[index][4].Set_y(6.000);
	BP_yz[index][5].Set_y(7.000);
	BP_yz[index][6].Set_y(8.000);
	BP_yz[index][7].Set_y(9.000);
	BP_yz[index][8].Set_y(10.000);
	BP_yz[index][9].Set_y(11.000);
	BP_yz[index][10].Set_y(11.198);
	BP_yz[index][11].Set_y(12.000);
	BP_yz[index][12].Set_y(22.000);
	BP_yz[index][13].Set_y(23.013);
	BP_yz[index][14].Set_y(24.200);
}

void CMy3D_view_FPbody_modelDoc::Init_BP_XZ()
{
/*	int i;
	int index;
	index = 0;
	double *anglexz = new double;
	*anglexz = 0.0;
	for(i=0;i<XZLINE[index].Get_BP();i++)								//init the cycle							
	{																	
		BP_xz[index][i].Set_x(1.0*cos(GetMethod->ang_to_rad(*anglexz)));									
		BP_xz[index][i].Set_y(0);
		BP_xz[index][i].Set_z(1.0*sin(GetMethod->ang_to_rad(*anglexz)));
		BP_xz[index][i].Catch = FALSE;
		BP_xz[index][i].LineStatus = 1;
		*anglexz += 360.0 / (XZLINE[index].Get_BP()-1);
	}		
	delete anglexz;*/
}

void CMy3D_view_FPbody_modelDoc::CALT_VP_XY()
{
	int i, index;

	index = 0;
	
	caltCP_XY = new CALTCP_XY;
	caltCP_XY->Init_N(XYLINE[index].Get_ORD(), XYLINE[index].Get_BP());
	caltCP_XY->Init_U(XYLINE[index].Get_VERARR()); 

	for(i=0;i<XYLINE[index].Get_BP();i++)
	{
		if(i==0)
		{
			BP_xy[index][i].Set_BP_sn(0.0);
		}
		else
		{
			BP_xy[index][i].Set_BP_sn(GetMethod->cacu_BP_sn(BP_xy[index][i-1].Get_BP_sn(), BP_xy[index][i].Get_x(), BP_xy[index][i-1].Get_x(), BP_xy[index][i].Get_y(), BP_xy[index][i-1].Get_y()));
		}
	}
	for(i=0;i<XYLINE[index].Get_BP();i++)
	{
		BP_xy[index][i].Set_BP_un(GetMethod->cacu_BP_un(BP_xy[index][XYLINE[index].Get_BP()-1].Get_BP_sn(), BP_xy[index][i].Get_BP_sn(),XYLINE[index].Get_ORD(),XYLINE[index].Get_BP()));
	}

	GetMethod->create_Uni_Knot_Ver(&cacl_KV, XYLINE[index].Get_BP(), XYLINE[index].Get_ORD(), caltCP_XY->U_xy, XYLINE[index].Get_BPARR());


	//...Calculate Basic Function N and Control Point

	int cout, n, j, k;

	for(cout=0;cout<XYLINE[index].Get_BP();cout++)
	{
		for(n=0;n<XYLINE[index].Get_BP();n++)
		{
			for(k=0;k<=XYLINE[index].Get_ORD();k++)
			{	
				for(i=0;i<XYLINE[index].Get_BP();i++)
				{	
					if(k==0)
					{
						if(BP_xy[index][n].Get_BP_un()>=caltCP_XY->U_xy[i] && BP_xy[index][n].Get_BP_un()<caltCP_XY->U_xy[i+1])
						{
							caltCP_XY->BP_N_xy[k][i] = 1.0;
						}
						else
						{
							caltCP_XY->BP_N_xy[k][i] = 0.0;
						}
					}
					else if(k==XYLINE[index].Get_ORD()&&n==XYLINE[index].Get_BP()-1&&i==XYLINE[index].Get_BP()-1)
					{
						caltCP_XY->BP_N_xy[k][i] = 1.0;				
					}
					else
					{
						caltCP_XY->BP_N_xy[k][i] = GetMethod->cacu_Nki(BP_xy[index][n].Get_BP_un(), caltCP_XY->U_xy[i], caltCP_XY->BP_N_xy[k-1][i], caltCP_XY->U_xy[i+k], caltCP_XY->BP_N_xy[k-1][i+1], caltCP_XY->U_xy[i+k+1], caltCP_XY->U_xy[i+1]);
					}
				}
				if(k==XYLINE[index].Get_ORD())
				{				
					caltCP_XY->temp_BP_N_xy[n][cout] = caltCP_XY->BP_N_xy[XYLINE[index].Get_ORD()][cout];
				}
			}
		}
	}
	
	GetMethod->matrix_inversion_using_elementary_operation(caltCP_XY->temp_BP_N_xy,caltCP_XY->inv_temp_BP_N_xy,XYLINE[index].Get_BP());
	
	for(i=0;i<XYLINE[index].Get_BP();i++)
	{
		double *temp_x = new double;
		double *temp_y = new double;
		double *temp_z = new double;
		*temp_x=0.0; *temp_y=0.0; *temp_z=0.0;
		for(j=0;j<XYLINE[index].Get_BP();j++)
		{
			*temp_x += caltCP_XY->inv_temp_BP_N_xy[i][j] * BP_xy[index][j].Get_x();
			*temp_y += caltCP_XY->inv_temp_BP_N_xy[i][j] * BP_xy[index][j].Get_y();
			*temp_z += caltCP_XY->inv_temp_BP_N_xy[i][j] * BP_xy[index][j].Get_z();
		}
		CP_xy[index][i].Set_ksi(*temp_x);
		CP_xy[index][i].Set_eta(*temp_y);
		CP_xy[index][i].Set_zeta(*temp_z);
		delete temp_x; delete temp_y; delete temp_z;
	}
}

void CMy3D_view_FPbody_modelDoc::CALT_VP_YZ()
{
	int index, i;

	index = 0;

	caltCP_YZ = new CALTCP_YZ;
	caltCP_YZ->Init_N(YZLINE[index].Get_ORD(), YZLINE[index].Get_BP());
	caltCP_YZ->Init_U(YZLINE[index].Get_VERARR()); 

	for(i=0;i<YZLINE[index].Get_BP();i++)
	{
		if(i==0)
		{
			BP_yz[index][i].Set_BP_sn(0.0);
		}
		else
		{
			BP_yz[index][i].Set_BP_sn(GetMethod->cacu_BP_sn(BP_yz[index][i-1].Get_BP_sn(), BP_yz[index][i].Get_y(), BP_yz[index][i-1].Get_y(), BP_yz[index][i].Get_z(), BP_yz[index][i-1].Get_z()));
		}
	}
	for(i=0;i<YZLINE[index].Get_BP();i++)
	{
		BP_yz[index][i].Set_BP_un(GetMethod->cacu_BP_un(BP_yz[index][YZLINE[index].Get_BP()-1].Get_BP_sn(), BP_yz[index][i].Get_BP_sn(),YZLINE[index].Get_ORD(),YZLINE[index].Get_BP()));
	}

	GetMethod->create_Uni_Knot_Ver(&cacl_KV, YZLINE[index].Get_BP(), YZLINE[index].Get_ORD(), caltCP_YZ->U_yz, YZLINE[index].Get_BPARR());
	

	//...Calculate Basic Function N and Control Point

	int cout, n, j, k;

	for(cout=0;cout<YZLINE[index].Get_BP();cout++)
	{
		for(n=0;n<YZLINE[index].Get_BP();n++)
		{
			for(k=0;k<=YZLINE[index].Get_ORD();k++)
			{	
				for(i=0;i<YZLINE[index].Get_BP();i++)
				{	
					if(k==0)
					{
						if(BP_yz[index][n].Get_BP_un()>=caltCP_YZ->U_yz[i] && BP_yz[index][n].Get_BP_un()<caltCP_YZ->U_yz[i+1])
						{
							caltCP_YZ->BP_N_yz[k][i] = 1.0;
						}
						else
						{
							caltCP_YZ->BP_N_yz[k][i] = 0.0;
						}
					}
					else if(k==YZLINE[index].Get_ORD()&&n==YZLINE[index].Get_BP()-1&&i==YZLINE[index].Get_BP()-1)
					{
						caltCP_YZ->BP_N_yz[k][i] = 1.0;				
					}
					else
					{
						caltCP_YZ->BP_N_yz[k][i] = GetMethod->cacu_Nki(BP_yz[index][n].Get_BP_un(), caltCP_YZ->U_yz[i], caltCP_YZ->BP_N_yz[k-1][i], caltCP_YZ->U_yz[i+k], caltCP_YZ->BP_N_yz[k-1][i+1], caltCP_YZ->U_yz[i+k+1], caltCP_YZ->U_yz[i+1]);
					}
				}
				if(k==YZLINE[index].Get_ORD())
				{				
					caltCP_YZ->temp_BP_N_yz[n][cout] = caltCP_YZ->BP_N_yz[YZLINE[index].Get_ORD()][cout];
				}
			}
		}
	}
	
	GetMethod->matrix_inversion_using_elementary_operation(caltCP_YZ->temp_BP_N_yz,caltCP_YZ->inv_temp_BP_N_yz,YZLINE[index].Get_BP());
	
	for(i=0;i<YZLINE[index].Get_BP();i++)
	{
		double *temp_x = new double;
		double *temp_y = new double;
		double *temp_z = new double;
		*temp_x=0.0; *temp_y=0.0; *temp_z=0.0;
		for(j=0;j<YZLINE[index].Get_BP();j++)
		{
			*temp_x += caltCP_YZ->inv_temp_BP_N_yz[i][j] * BP_yz[index][j].Get_x();
			*temp_y += caltCP_YZ->inv_temp_BP_N_yz[i][j] * BP_yz[index][j].Get_y();
			*temp_z += caltCP_YZ->inv_temp_BP_N_yz[i][j] * BP_yz[index][j].Get_z();
		}
		CP_yz[index][i].Set_ksi(*temp_x);
		CP_yz[index][i].Set_eta(*temp_y);
		CP_yz[index][i].Set_zeta(*temp_z);
		delete temp_x; delete temp_y; delete temp_z;
	}
}

void CMy3D_view_FPbody_modelDoc::CALT_VP_XZ()
{
	int index, i;

	index = 0;

	caltCP_XZ = new CALTCP_XZ;
	caltCP_XZ->Init_N(XZLINE[index].Get_ORD(), XZLINE[index].Get_BP());
	caltCP_XZ->Init_U(XZLINE[index].Get_VERARR()); 

	for(i=0;i<XZLINE[index].Get_BP();i++)
	{
		if(i==0)
		{
			BP_xz[index][i].Set_BP_sn(0.0);
		}
		else
		{
			BP_xz[index][i].Set_BP_sn(GetMethod->cacu_BP_sn(BP_xz[index][i-1].Get_BP_sn(), BP_xz[index][i].Get_x(), BP_xz[index][i-1].Get_x(), BP_xz[index][i].Get_z(), BP_xz[index][i-1].Get_z()));
		}
	}
	for(i=0;i<XZLINE[index].Get_BP();i++)
	{
		BP_xz[index][i].Set_BP_un(GetMethod->cacu_BP_un(BP_xz[index][XZLINE[index].Get_BP()-1].Get_BP_sn(), BP_xz[index][i].Get_BP_sn(),XZLINE[index].Get_ORD(),XZLINE[index].Get_BP()));
	}

	GetMethod->create_Uni_Knot_Ver(&cacl_KV, XZLINE[index].Get_BP(), XZLINE[index].Get_ORD(), caltCP_XZ->U_xz, XZLINE[index].Get_BPARR());


	//...Calculate Basic Function N and Control Point

	int cout, n, j, k;	

	for(cout=0;cout<XZLINE[index].Get_BP();cout++)
	{
		for(n=0;n<XZLINE[index].Get_BP();n++)
		{
			for(k=0;k<=XZLINE[index].Get_ORD();k++)
			{	
				for(i=0;i<XZLINE[index].Get_BP();i++)
				{	
					if(k==0)
					{
						if(BP_xz[index][n].Get_BP_un()>=caltCP_XZ->U_xz[i] && BP_xz[index][n].Get_BP_un()<caltCP_XZ->U_xz[i+1])
						{
							caltCP_XZ->BP_N_xz[k][i] = 1.0;
						}
						else
						{
							caltCP_XZ->BP_N_xz[k][i] = 0.0;
						}
					}
					else if(k==XZLINE[index].Get_ORD()&&n==XZLINE[index].Get_BP()-1&&i==XZLINE[index].Get_BP()-1)
					{
						caltCP_XZ->BP_N_xz[k][i] = 1.0;				
					}
					else
					{
						caltCP_XZ->BP_N_xz[k][i] = GetMethod->cacu_Nki(BP_xz[index][n].Get_BP_un(), caltCP_XZ->U_xz[i], caltCP_XZ->BP_N_xz[k-1][i], caltCP_XZ->U_xz[i+k], caltCP_XZ->BP_N_xz[k-1][i+1], caltCP_XZ->U_xz[i+k+1], caltCP_XZ->U_xz[i+1]);
					}
				}
				if(k==XZLINE[index].Get_ORD())
				{				
					caltCP_XZ->temp_BP_N_xz[n][cout] = caltCP_XZ->BP_N_xz[XZLINE[index].Get_ORD()][cout];
				}
			}
		}
	}
	
	GetMethod->matrix_inversion_using_elementary_operation(caltCP_XZ->temp_BP_N_xz,caltCP_XZ->inv_temp_BP_N_xz,XZLINE[index].Get_BP());
	
	for(i=0;i<XZLINE[index].Get_BP();i++)
	{
		double *temp_x = new double;
		double *temp_y = new double;
		double *temp_z = new double;
		*temp_x=0.0; *temp_y=0.0; *temp_z=0.0;
		for(j=0;j<XZLINE[index].Get_BP();j++)
		{
			*temp_x += caltCP_XZ->inv_temp_BP_N_xz[i][j] * BP_xz[index][j].Get_x();
			*temp_y += caltCP_XZ->inv_temp_BP_N_xz[i][j] * BP_xz[index][j].Get_y();
			*temp_z += caltCP_XZ->inv_temp_BP_N_xz[i][j] * BP_xz[index][j].Get_z();
		}
		CP_xz[index][i].Set_ksi(*temp_x);
		CP_xz[index][i].Set_eta(*temp_y);
		CP_xz[index][i].Set_zeta(*temp_z);
		delete temp_x; delete temp_y; delete temp_z;
	}
}

void CMy3D_view_FPbody_modelDoc::CALT_BSPLINE_XY()
{
//...Calculate basic function N Ndev1 Ndev2
	int index, i, cout, n, k, uNt, cot;
	index = BPLIndex;

	caltBSP_XY = new CALTBSPLINE_XY;
	BSPL_xy[index].Catch=FALSE;

	BSPL_xy[index].Init(XYLINE[index].Get_NUM());
	caltBSP_XY->Init_U(XYLINE[index].Get_VERARR());
	caltBSP_XY->Init_N(XYLINE[index].Get_ORD(), XYLINE[index].Get_VER(), XYLINE[index].Get_NUM());
	
	if(PCUPI_XY==TRUE)
	{
		caltBSP_XY->Init_U_dev(XYLINE[index].Get_VERARR()-2);
	}

	GetMethod->create_Uni_Knot_Ver(&cacl_KV, XYLINE[index].Get_VER(), XYLINE[index].Get_ORD(), caltBSP_XY->U_xy, XYLINE[index].Get_VERARR());

	double *temp_x, *temp_y, *temp_z;
	double *temp_x_dev1, *temp_y_dev1, *temp_z_dev1;
	double *temp_x_dev2, *temp_y_dev2, *temp_z_dev2;

	//...XYZ... u spn U
	for(i=0;i<XYLINE[index].Get_NUM();i++)
	{
		caltBSP_XY->u_xy[i] = (double)i/5.0;
	}

////////////////////////////////////////////////////////////////////////////////

	//...XY...N
	for(cout=0;cout<XYLINE[index].Get_VER();cout++)
	{
		for(n=0;n<XYLINE[index].Get_NUM();n++)
		{
			for(k=0;k<=XYLINE[index].Get_ORD();k++)
			{	
				for(i=0;i<XYLINE[index].Get_VER();i++)
				{	
					if(k==0)
					{
						if(caltBSP_XY->u_xy[n]>=caltBSP_XY->U_xy[i] && caltBSP_XY->u_xy[n]<caltBSP_XY->U_xy[i+1])
						{
							caltBSP_XY->N_xy[k][i] = 1.0;
						}
						else
						{
							caltBSP_XY->N_xy[k][i] = 0.0;
						}
					}
					else if(k==XYLINE[index].Get_ORD()&&n==XYLINE[index].Get_NUM()-1&&i==XYLINE[index].Get_VER()-1)
					{
						caltBSP_XY->N_xy[k][i] = 1.0;				
					}
					else
					{
						caltBSP_XY->N_xy[k][i]	= GetMethod->cacu_Nki(caltBSP_XY->u_xy[n], caltBSP_XY->U_xy[i], caltBSP_XY->N_xy[k-1][i], caltBSP_XY->U_xy[i+k], caltBSP_XY->N_xy[k-1][i+1], caltBSP_XY->U_xy[i+k+1], caltBSP_XY->U_xy[i+1]);
						if(PCUPI_XY==TRUE)
						{
							caltBSP_XY->N_dev1_xy[k][i] = GetMethod->cacu_Nki_dev(k, caltBSP_XY->U_xy[i], caltBSP_XY->N_xy[k-1][i], caltBSP_XY->U_xy[i+k], caltBSP_XY->N_xy[k-1][i+1], caltBSP_XY->U_xy[i+k+1], caltBSP_XY->U_xy[i+1]);
							caltBSP_XY->N_dev2_xy[k][i] = GetMethod->cacu_Nki_dev(k, caltBSP_XY->U_xy[i], caltBSP_XY->N_dev1_xy[k-1][i], caltBSP_XY->U_xy[i+k], caltBSP_XY->N_dev1_xy[k-1][i+1], caltBSP_XY->U_xy[i+k+1], caltBSP_XY->U_xy[i+1]);
						}
					}
				}
				if(k==XYLINE[index].Get_ORD())
				{		
					if(PCUPI_XY==TRUE)
					{
						if(n==0 && cout==0)
						{
							for(uNt=0;uNt<2;uNt++)
							{
								caltBSP_XY->uN_temp_dev1[uNt] = caltBSP_XY->N_dev1_xy[XYLINE[index].Get_ORD()][uNt];
							}
						}
						for(uNt=0;uNt<2;uNt++)
						{
							if(n==XYLINE[index].Get_NUM()-1 && cout == XYLINE[index].Get_VER() - (uNt + 1))
							{
								caltBSP_XY->N_dev1_xy[XYLINE[index].Get_ORD()][XYLINE[index].Get_VER() - (uNt + 1)] = caltBSP_XY->uN_temp_dev1[1 - uNt];
							}
						}

						if(n==0 && cout==0)
						{
							for(uNt=0;uNt<3;uNt++)
							{
								caltBSP_XY->uN_temp_dev2[uNt] = caltBSP_XY->N_dev2_xy[XYLINE[index].Get_ORD()][uNt];
							}
						}
						for(uNt=0;uNt<3;uNt++)
						{
							if(n==XYLINE[index].Get_NUM()-1 && cout == XYLINE[index].Get_VER() - (uNt + 1))
							{
								caltBSP_XY->N_dev2_xy[XYLINE[index].Get_ORD()][XYLINE[index].Get_VER() - (uNt + 1)] = caltBSP_XY->uN_temp_dev2[uNt];
							}
						}
						caltBSP_XY->N_sig_dev_1_xy[n][cout] = caltBSP_XY->N_xy[XYLINE[index].Get_ORD()-1][cout+1];		//dev 1 importent,this is right
						caltBSP_XY->N_sig_dev_2_xy[n][cout] = caltBSP_XY->N_xy[XYLINE[index].Get_ORD()-2][cout+2];		//dev 2 importent,this is right
					}

					caltBSP_XY->N_sig_xy[n][cout] = caltBSP_XY->N_xy[XYLINE[index].Get_ORD()][cout];	
				}
			}
		}
	}
	
	if(PCUPI_XY==TRUE)
	{
		//...XY...CP...dev
		for(i=0;i<XYLINE[index].Get_VER()-1;i++)
		{		
			CP_xy[index][i].Set_ksi_dev1(((XYLINE[index].Get_ORD())/(caltBSP_XY->U_xy[i+XYLINE[index].Get_ORD()+1]-caltBSP_XY->U_xy[i+1]))*(CP_xy[index][i+1].Get_ksi()-CP_xy[index][i].Get_ksi()));
			CP_xy[index][i].Set_eta_dev1(((XYLINE[index].Get_ORD())/(caltBSP_XY->U_xy[i+XYLINE[index].Get_ORD()+1]-caltBSP_XY->U_xy[i+1]))*(CP_xy[index][i+1].Get_eta()-CP_xy[index][i].Get_eta()));		
			CP_xy[index][i].Set_zeta_dev1(((XYLINE[index].Get_ORD())/(caltBSP_XY->U_xy[i+XYLINE[index].Get_ORD()+1]-caltBSP_XY->U_xy[i+1]))*(CP_xy[index][i+1].Get_zeta()-CP_xy[index][i].Get_zeta()));				
		}
		GetMethod->create_Uni_Knot_Ver(&cacl_KV, XYLINE[index].Get_VER()-1, XYLINE[index].Get_ORD()-1, caltBSP_XY->U_xy_dev, XYLINE[index].Get_VERARR()-2);

		for(i=0;i<XYLINE[index].Get_VER()-2;i++)
		{
			CP_xy[index][i].Set_ksi_dev2(((XYLINE[index].Get_ORD()-1)/(caltBSP_XY->U_xy_dev[i+XYLINE[index].Get_ORD()-1+1]-caltBSP_XY->U_xy_dev[i+1]))*(CP_xy[index][i+1].Get_ksi_dev1()-CP_xy[index][i].Get_ksi_dev1()));
			CP_xy[index][i].Set_eta_dev2(((XYLINE[index].Get_ORD()-1)/(caltBSP_XY->U_xy_dev[i+XYLINE[index].Get_ORD()-1+1]-caltBSP_XY->U_xy_dev[i+1]))*(CP_xy[index][i+1].Get_eta_dev1()-CP_xy[index][i].Get_eta_dev1()));		
			CP_xy[index][i].Set_zeta_dev2(((XYLINE[index].Get_ORD()-1)/(caltBSP_XY->U_xy_dev[i+XYLINE[index].Get_ORD()-1+1]-caltBSP_XY->U_xy_dev[i+1]))*(CP_xy[index][i+1].Get_zeta_dev1()-CP_xy[index][i].Get_zeta_dev1()));		
		}	
		temp_x_dev1 = new double;
		temp_y_dev1 = new double;
		temp_z_dev1 = new double;
			
		temp_x_dev2 = new double;
		temp_y_dev2 = new double;
		temp_z_dev2 = new double;
	}

	temp_x = new double;
	temp_y = new double;
	temp_z = new double;
	
	
	//...XY...Bspline...normal vector...kslope
	for(n=0;n<XYLINE[index].Get_NUM();n++)
	{	
		*temp_x = 0.0;
		*temp_y = 0.0;
		*temp_z = 0.0;
		if(PCUPI_XY==TRUE)
		{
			*temp_x_dev1 = 0.0;
			*temp_y_dev1 = 0.0;
			*temp_z_dev1 = 0.0;
			
			*temp_x_dev2 = 0.0;
			*temp_y_dev2 = 0.0;
			*temp_z_dev2 = 0.0;
		}

		for(cot=0;cot<XYLINE[index].Get_VER();cot++)
		{
			*temp_x += CP_xy[index][cot].Get_ksi() * caltBSP_XY->N_sig_xy[n][cot];
			*temp_y += CP_xy[index][cot].Get_eta() * caltBSP_XY->N_sig_xy[n][cot];
			*temp_z += CP_xy[index][cot].Get_zeta() * caltBSP_XY->N_sig_xy[n][cot];
		}
		
		if(PCUPI_XY==TRUE)
		{
			for(cot=0;cot<XYLINE[index].Get_VER()-1;cot++)
			{
				if(n==XYLINE[index].Get_NUM()-1)
				{
					*temp_x_dev1 = CP_xy[index][XYLINE[index].Get_VER()-2].Get_ksi_dev1();
					*temp_y_dev1 = CP_xy[index][XYLINE[index].Get_VER()-2].Get_eta_dev1();
					*temp_z_dev1 = CP_xy[index][XYLINE[index].Get_VER()-2].Get_zeta_dev1();
				}
				else if(n==0)
				{
					*temp_x_dev1 = CP_xy[index][0].Get_ksi_dev1();
					*temp_y_dev1 = CP_xy[index][0].Get_eta_dev1();
					*temp_z_dev1 = CP_xy[index][0].Get_zeta_dev1();
				}
				else
				{
					*temp_x_dev1 += CP_xy[index][cot].Get_ksi_dev1() * caltBSP_XY->N_sig_dev_1_xy[n][cot];
					*temp_y_dev1 += CP_xy[index][cot].Get_eta_dev1() * caltBSP_XY->N_sig_dev_1_xy[n][cot];
					*temp_z_dev1 += CP_xy[index][cot].Get_zeta_dev1() * caltBSP_XY->N_sig_dev_1_xy[n][cot];
				}
			}
		
			for(cot=0;cot<XYLINE[index].Get_VER()-2;cot++)
			{
				if(n==XYLINE[index].Get_NUM()-1)
				{
					*temp_x_dev2 = CP_xy[index][XYLINE[index].Get_VER()-3].Get_ksi_dev2();
					*temp_y_dev2 = CP_xy[index][XYLINE[index].Get_VER()-3].Get_eta_dev2();
					*temp_z_dev2 = CP_xy[index][XYLINE[index].Get_VER()-3].Get_zeta_dev2();
				}
				else if(n==0)
				{
					*temp_x_dev2 = CP_xy[index][0].Get_ksi_dev2();
					*temp_y_dev2 = CP_xy[index][0].Get_eta_dev2();
					*temp_z_dev2 = CP_xy[index][0].Get_zeta_dev2();
				}
				else
				{
					*temp_x_dev2 += CP_xy[index][cot].Get_ksi_dev2() * caltBSP_XY->N_sig_dev_2_xy[n][cot];
					*temp_y_dev2 += CP_xy[index][cot].Get_eta_dev2() * caltBSP_XY->N_sig_dev_2_xy[n][cot];
					*temp_z_dev2 += CP_xy[index][cot].Get_zeta_dev2() * caltBSP_XY->N_sig_dev_2_xy[n][cot];
				}
			}
		}

		BSPL_xy[index].x[n] = *temp_x;
		BSPL_xy[index].y[n] = *temp_y;
		BSPL_xy[index].z[n] = *temp_z;
		
		if(PCUPI_XY==TRUE)
		{
			BSPL_xy[index].x_dev1[n] = *temp_x_dev1;
			BSPL_xy[index].y_dev1[n] = *temp_y_dev1;
			BSPL_xy[index].z_dev1[n] = *temp_z_dev1;

			BSPL_xy[index].x_dev2[n] = *temp_x_dev2;
			BSPL_xy[index].y_dev2[n] = *temp_y_dev2;
			BSPL_xy[index].z_dev2[n] = *temp_z_dev2;
		
			BSPL_xy[index].nx_xy[n] = GetMethod->cacu_nx(BSPL_xy[index].x_dev1[n], BSPL_xy[index].y_dev1[n]);
			BSPL_xy[index].ny_xy[n] = GetMethod->cacu_ny(BSPL_xy[index].x_dev1[n], BSPL_xy[index].y_dev1[n]);
			BSPL_xy[index].kslope_xy[n] = GetMethod->cacu_kslope(BSPL_xy[index].x_dev1[n], BSPL_xy[index].y_dev1[n], BSPL_xy[index].x_dev2[n], BSPL_xy[index].y_dev2[n]);
		}
	}
	
	delete temp_x; delete temp_y; delete temp_z;
	if(PCUPI_XY==TRUE)
	{
		delete temp_x_dev1; delete temp_y_dev1; delete temp_z_dev1;
		delete temp_x_dev2; delete temp_y_dev2; delete temp_z_dev2;
	}
}

void CMy3D_view_FPbody_modelDoc::CALT_BSPLINE_YZ()
{
	//...Calculate basic function N Ndev1 Ndev2
	int index, i, cout, n, k, uNt, cot;
	index = BPLIndex;
		
	caltBSP_YZ = new CALTBSPLINE_YZ;

	BSPL_yz[index].Catch=FALSE;
	BSPL_yz[index].Init(YZLINE[index].Get_NUM());

	caltBSP_YZ->Init_U(YZLINE[index].Get_VERARR());
	caltBSP_YZ->Init_N(YZLINE[index].Get_ORD(), YZLINE[index].Get_VER(), YZLINE[index].Get_NUM());

	if(PCUPI_YZ==TRUE)
	{
		caltBSP_YZ->Init_U_dev(YZLINE[index].Get_VERARR()-2);
	}

	GetMethod->create_Uni_Knot_Ver(&cacl_KV, YZLINE[index].Get_VER(), YZLINE[index].Get_ORD(), caltBSP_YZ->U_yz, YZLINE[index].Get_VERARR());

	double *temp_x, *temp_y, *temp_z;
	double *temp_x_dev1, *temp_y_dev1, *temp_z_dev1;
	double *temp_x_dev2, *temp_y_dev2, *temp_z_dev2;

	//...XYZ... u spn U
	for(i=0;i<YZLINE[index].Get_NUM();i++)
	{
		caltBSP_YZ->u_yz[i] = (double)i/5.0;
	}

////////////////////////////////////////////////////////////////////////////////
	
	//...YZ...N
	for(cout=0;cout<YZLINE[index].Get_VER();cout++)
	{
		for(n=0;n<YZLINE[index].Get_NUM();n++)
		{
			for(k=0;k<=YZLINE[index].Get_ORD();k++)
			{	
				for(i=0;i<YZLINE[index].Get_VER();i++)
				{	
					if(k==0)
					{
						if(caltBSP_YZ->u_yz[n]>=caltBSP_YZ->U_yz[i] && caltBSP_YZ->u_yz[n]<caltBSP_YZ->U_yz[i+1])
						{
							caltBSP_YZ->N_yz[k][i] = 1.0;
						}
						else
						{
							caltBSP_YZ->N_yz[k][i] = 0.0;
						}
					}
					else if(k==YZLINE[index].Get_ORD()&&n==YZLINE[index].Get_NUM()-1&&i==YZLINE[index].Get_VER()-1)
					{
						caltBSP_YZ->N_yz[k][i] = 1.0;				
					}
					else
					{
						caltBSP_YZ->N_yz[k][i]	= GetMethod->cacu_Nki(caltBSP_YZ->u_yz[n], caltBSP_YZ->U_yz[i], caltBSP_YZ->N_yz[k-1][i], caltBSP_YZ->U_yz[i+k], caltBSP_YZ->N_yz[k-1][i+1], caltBSP_YZ->U_yz[i+k+1], caltBSP_YZ->U_yz[i+1]);
						if(PCUPI_YZ==TRUE)
						{
							caltBSP_YZ->N_dev1_yz[k][i] = GetMethod->cacu_Nki_dev(k, caltBSP_YZ->U_yz[i], caltBSP_YZ->N_yz[k-1][i], caltBSP_YZ->U_yz[i+k], caltBSP_YZ->N_yz[k-1][i+1], caltBSP_YZ->U_yz[i+k+1], caltBSP_YZ->U_yz[i+1]);
							caltBSP_YZ->N_dev2_yz[k][i] = GetMethod->cacu_Nki_dev(k, caltBSP_YZ->U_yz[i], caltBSP_YZ->N_dev1_yz[k-1][i], caltBSP_YZ->U_yz[i+k], caltBSP_YZ->N_dev1_yz[k-1][i+1], caltBSP_YZ->U_yz[i+k+1], caltBSP_YZ->U_yz[i+1]);
						}
					}
				}
				if(k==YZLINE[index].Get_ORD())
				{	
					if(PCUPI_YZ==TRUE)
					{
						if(n==0 && cout==0)
						{
							for(uNt=0;uNt<2;uNt++)
							{
								caltBSP_YZ->uN_temp_dev1[uNt] = caltBSP_YZ->N_dev1_yz[YZLINE[index].Get_ORD()][uNt];
							}
						}
						for(uNt=0;uNt<2;uNt++)
						{
							if(n==YZLINE[index].Get_NUM()-1 && cout == YZLINE[index].Get_VER() - (uNt + 1))
							{
								caltBSP_YZ->N_dev1_yz[YZLINE[index].Get_ORD()][YZLINE[index].Get_VER() - (uNt + 1)] = caltBSP_YZ->uN_temp_dev1[1 - uNt];
							}
						}

						if(n==0 && cout==0)
						{
							for(uNt=0;uNt<3;uNt++)
							{
								caltBSP_YZ->uN_temp_dev2[uNt] = caltBSP_YZ->N_dev2_yz[YZLINE[index].Get_ORD()][uNt];
							}
						}
						for(uNt=0;uNt<3;uNt++)
						{
							if(n==YZLINE[index].Get_NUM()-1 && cout == YZLINE[index].Get_VER() - (uNt + 1))
							{
								caltBSP_YZ->N_dev2_yz[YZLINE[index].Get_ORD()][YZLINE[index].Get_VER() - (uNt + 1)] = caltBSP_YZ->uN_temp_dev2[uNt];
							}
						}
						caltBSP_YZ->N_sig_dev_1_yz[n][cout] = caltBSP_YZ->N_yz[YZLINE[index].Get_ORD()-1][cout+1];		//dev 1 importent,this is right
						caltBSP_YZ->N_sig_dev_2_yz[n][cout] = caltBSP_YZ->N_yz[YZLINE[index].Get_ORD()-2][cout+2];		//dev 2 importent,this is right
					}
					caltBSP_YZ->N_sig_yz[n][cout] = caltBSP_YZ->N_yz[YZLINE[index].Get_ORD()][cout];
				}
			}
		}
	}
	
	if(PCUPI_YZ==TRUE)
	{
		//...YZ...CP...dev
		for(i=0;i<YZLINE[index].Get_VER()-1;i++)
		{		
			CP_yz[index][i].Set_ksi_dev1(((YZLINE[index].Get_ORD())/(caltBSP_YZ->U_yz[i+YZLINE[index].Get_ORD()+1]-caltBSP_YZ->U_yz[i+1]))*(CP_yz[index][i+1].Get_ksi()-CP_yz[index][i].Get_ksi()));
			CP_yz[index][i].Set_eta_dev1(((YZLINE[index].Get_ORD())/(caltBSP_YZ->U_yz[i+YZLINE[index].Get_ORD()+1]-caltBSP_YZ->U_yz[i+1]))*(CP_yz[index][i+1].Get_eta()-CP_yz[index][i].Get_eta()));		
			CP_yz[index][i].Set_zeta_dev1(((YZLINE[index].Get_ORD())/(caltBSP_YZ->U_yz[i+YZLINE[index].Get_ORD()+1]-caltBSP_YZ->U_yz[i+1]))*(CP_yz[index][i+1].Get_zeta()-CP_yz[index][i].Get_zeta()));		
		}
		GetMethod->create_Uni_Knot_Ver(&cacl_KV, YZLINE[index].Get_VER()-1, YZLINE[index].Get_ORD()-1, caltBSP_YZ->U_yz_dev, YZLINE[index].Get_VERARR()-2);

		for(i=0;i<YZLINE[index].Get_VER()-2;i++)
		{
			CP_yz[index][i].Set_ksi_dev2(((YZLINE[index].Get_ORD()-1)/(caltBSP_YZ->U_yz_dev[i+YZLINE[index].Get_ORD()-1+1]-caltBSP_YZ->U_yz_dev[i+1]))*(CP_yz[index][i+1].Get_ksi_dev1()-CP_yz[index][i].Get_ksi_dev1()));
			CP_yz[index][i].Set_eta_dev2(((YZLINE[index].Get_ORD()-1)/(caltBSP_YZ->U_yz_dev[i+YZLINE[index].Get_ORD()-1+1]-caltBSP_YZ->U_yz_dev[i+1]))*(CP_yz[index][i+1].Get_eta_dev1()-CP_yz[index][i].Get_eta_dev1()));		
			CP_yz[index][i].Set_zeta_dev2(((YZLINE[index].Get_ORD()-1)/(caltBSP_YZ->U_yz_dev[i+YZLINE[index].Get_ORD()-1+1]-caltBSP_YZ->U_yz_dev[i+1]))*(CP_yz[index][i+1].Get_zeta_dev1()-CP_yz[index][i].Get_zeta_dev1()));		
		}
		temp_x_dev1 = new double;
		temp_y_dev1 = new double;
		temp_z_dev1 = new double;
			
		temp_x_dev2 = new double;
		temp_y_dev2 = new double;
		temp_z_dev2 = new double;
	}
	temp_x = new double;
	temp_y = new double;
	temp_z = new double;
	
	//...YZ...Bspline...normal vector...kslope
	for(n=0;n<YZLINE[index].Get_NUM();n++)
	{	
		*temp_x = 0.0;
		*temp_y = 0.0;
		*temp_z = 0.0;
		
		if(PCUPI_YZ==TRUE)
		{
			*temp_x_dev1 = 0.0;
			*temp_y_dev1 = 0.0;
			*temp_z_dev1 = 0.0;
			
			*temp_x_dev2 = 0.0;
			*temp_y_dev2 = 0.0;
			*temp_z_dev2 = 0.0;
		}

		for(cot=0;cot<YZLINE[index].Get_VER();cot++)
		{
			*temp_x += CP_yz[index][cot].Get_ksi() * caltBSP_YZ->N_sig_yz[n][cot];
			*temp_y += CP_yz[index][cot].Get_eta() * caltBSP_YZ->N_sig_yz[n][cot];
			*temp_z += CP_yz[index][cot].Get_zeta() * caltBSP_YZ->N_sig_yz[n][cot];
		}
		
		if(PCUPI_YZ==TRUE)
		{
			for(cot=0;cot<YZLINE[index].Get_VER()-1;cot++)
			{
				if(n==YZLINE[index].Get_NUM()-1)
				{
					*temp_x_dev1 = CP_yz[index][YZLINE[index].Get_VER()-2].Get_ksi_dev1();
					*temp_y_dev1 = CP_yz[index][YZLINE[index].Get_VER()-2].Get_eta_dev1();
					*temp_z_dev1 = CP_yz[index][YZLINE[index].Get_VER()-2].Get_zeta_dev1();
				}
				else if(n==0)
				{
					*temp_x_dev1 = CP_yz[index][0].Get_ksi_dev1();
					*temp_y_dev1 = CP_yz[index][0].Get_eta_dev1();
					*temp_z_dev1 = CP_yz[index][0].Get_zeta_dev1();
				}
				else
				{
					*temp_x_dev1 += CP_yz[index][cot].Get_ksi_dev1() * caltBSP_YZ->N_sig_dev_1_yz[n][cot];
					*temp_y_dev1 += CP_yz[index][cot].Get_eta_dev1() * caltBSP_YZ->N_sig_dev_1_yz[n][cot];
					*temp_z_dev1 += CP_yz[index][cot].Get_zeta_dev1() * caltBSP_YZ->N_sig_dev_1_yz[n][cot];
				}
			}
		
			for(cot=0;cot<YZLINE[index].Get_VER()-2;cot++)
			{
				if(n==YZLINE[index].Get_NUM()-1)
				{
					*temp_x_dev2 = CP_yz[index][YZLINE[index].Get_VER()-3].Get_ksi_dev2();
					*temp_y_dev2 = CP_yz[index][YZLINE[index].Get_VER()-3].Get_eta_dev2();
					*temp_z_dev2 = CP_yz[index][YZLINE[index].Get_VER()-3].Get_zeta_dev2();
				}
				else if(n==0)
				{
					*temp_x_dev2 = CP_yz[index][0].Get_ksi_dev2();
					*temp_y_dev2 = CP_yz[index][0].Get_eta_dev2();
					*temp_z_dev2 = CP_yz[index][0].Get_zeta_dev2();
				}
				else
				{
					*temp_x_dev2 += CP_yz[index][cot].Get_ksi_dev2() * caltBSP_YZ->N_sig_dev_2_yz[n][cot];
					*temp_y_dev2 += CP_yz[index][cot].Get_eta_dev2() * caltBSP_YZ->N_sig_dev_2_yz[n][cot];
					*temp_z_dev2 += CP_yz[index][cot].Get_zeta_dev2() * caltBSP_YZ->N_sig_dev_2_yz[n][cot];
				}
			}
		}
		BSPL_yz[index].x[n] = *temp_x;
		BSPL_yz[index].y[n] = *temp_y;
		BSPL_yz[index].z[n] = *temp_z;

		if(PCUPI_YZ==TRUE)
		{
			BSPL_yz[index].x_dev1[n] = *temp_x_dev1;
			BSPL_yz[index].y_dev1[n] = *temp_y_dev1;
			BSPL_yz[index].z_dev1[n] = *temp_z_dev1;

			BSPL_yz[index].x_dev2[n] = *temp_x_dev2;
			BSPL_yz[index].y_dev2[n] = *temp_y_dev2;
			BSPL_yz[index].z_dev2[n] = *temp_z_dev2;
		
			BSPL_yz[index].nx_yz[n] = GetMethod->cacu_nx(BSPL_yz[index].y_dev1[n], BSPL_yz[index].z_dev1[n]);
			BSPL_yz[index].ny_yz[n] = GetMethod->cacu_ny(BSPL_yz[index].y_dev1[n], BSPL_yz[index].z_dev1[n]);

			BSPL_yz[index].kslope_yz[n] = GetMethod->cacu_kslope(BSPL_yz[index].y_dev1[n], BSPL_yz[index].z_dev1[n], BSPL_yz[index].y_dev2[n], BSPL_yz[index].z_dev2[n]);
		}
	}
	
	delete temp_x; delete temp_y; delete temp_z;
	if(PCUPI_YZ==TRUE)
	{
		delete temp_x_dev1; delete temp_y_dev1; delete temp_z_dev1;
		delete temp_x_dev2; delete temp_y_dev2; delete temp_z_dev2;
	}
}

void CMy3D_view_FPbody_modelDoc::CALT_BSPLINE_XZ()
{
	//...Calculate basic function N Ndev1 Ndev2
	int index, i, cout, n, k, uNt, cot;
	index = BPLIndex;
		
	caltBSP_XZ = new CALTBSPLINE_XZ;

	BSPL_xz[index].Catch=FALSE;
	BSPL_xz[index].Init(XZLINE[index].Get_NUM());

	caltBSP_XZ->Init_U(XZLINE[index].Get_VERARR());
	caltBSP_XZ->Init_N(XZLINE[index].Get_ORD(), XZLINE[index].Get_VER(), XZLINE[index].Get_NUM());

	if(PCUPI_XZ==TRUE)
	{
		caltBSP_XZ->Init_U_dev(XZLINE[index].Get_VERARR()-2);
	}

	GetMethod->create_Uni_Knot_Ver(&cacl_KV, XZLINE[index].Get_VER(), XZLINE[index].Get_ORD(), caltBSP_XZ->U_xz, XZLINE[index].Get_VERARR());

	double *temp_x, *temp_y, *temp_z;
	double *temp_x_dev1, *temp_y_dev1, *temp_z_dev1;
	double *temp_x_dev2, *temp_y_dev2, *temp_z_dev2;

	//...XYZ... u spn U
	for(i=0;i<XZLINE[index].Get_NUM();i++)
	{
		caltBSP_XZ->u_xz[i] = (double)i/5.0;
	}

////////////////////////////////////////////////////////////////////////////////
	
	//...XZ...N
	for(cout=0;cout<XZLINE[index].Get_VER();cout++)
	{
		for(n=0;n<XZLINE[index].Get_NUM();n++)
		{
			for(k=0;k<=XZLINE[index].Get_ORD();k++)
			{	
				for(i=0;i<XZLINE[index].Get_VER();i++)
				{	
					if(k==0)
					{
						if(caltBSP_XZ->u_xz[n]>=caltBSP_XZ->U_xz[i] && caltBSP_XZ->u_xz[n]<caltBSP_XZ->U_xz[i+1])
						{
							caltBSP_XZ->N_xz[k][i] = 1.0;
						}
						else
						{
							caltBSP_XZ->N_xz[k][i] = 0.0;
						}
					}
					else if(k==XZLINE[index].Get_ORD()&&n==XZLINE[index].Get_NUM()-1&&i==XZLINE[index].Get_VER()-1)
					{
						caltBSP_XZ->N_xz[k][i] = 1.0;				
					}
					else
					{
						caltBSP_XZ->N_xz[k][i]	= GetMethod->cacu_Nki(caltBSP_XZ->u_xz[n], caltBSP_XZ->U_xz[i], caltBSP_XZ->N_xz[k-1][i], caltBSP_XZ->U_xz[i+k], caltBSP_XZ->N_xz[k-1][i+1], caltBSP_XZ->U_xz[i+k+1], caltBSP_XZ->U_xz[i+1]);
						if(PCUPI_XZ==TRUE)
						{
							caltBSP_XZ->N_dev1_xz[k][i] = GetMethod->cacu_Nki_dev(k, caltBSP_XZ->U_xz[i], caltBSP_XZ->N_xz[k-1][i], caltBSP_XZ->U_xz[i+k], caltBSP_XZ->N_xz[k-1][i+1], caltBSP_XZ->U_xz[i+k+1], caltBSP_XZ->U_xz[i+1]);
							caltBSP_XZ->N_dev2_xz[k][i] = GetMethod->cacu_Nki_dev(k, caltBSP_XZ->U_xz[i], caltBSP_XZ->N_dev1_xz[k-1][i], caltBSP_XZ->U_xz[i+k], caltBSP_XZ->N_dev1_xz[k-1][i+1], caltBSP_XZ->U_xz[i+k+1], caltBSP_XZ->U_xz[i+1]);
						}
					}
				}
				if(k==XZLINE[index].Get_ORD())
				{	
					if(PCUPI_XZ==TRUE)
					{
						if(n==0 && cout==0)
						{
							for(uNt=0;uNt<2;uNt++)
							{
								caltBSP_XZ->uN_temp_dev1[uNt] = caltBSP_XZ->N_dev1_xz[XZLINE[index].Get_ORD()][uNt];
							}
						}
						for(uNt=0;uNt<2;uNt++)
						{
							if(n==XZLINE[index].Get_NUM()-1 && cout == XZLINE[index].Get_VER() - (uNt + 1))
							{
								caltBSP_XZ->N_dev1_xz[XZLINE[index].Get_ORD()][XZLINE[index].Get_VER() - (uNt + 1)] = caltBSP_XZ->uN_temp_dev1[1 - uNt];
							}
						}

						if(n==0 && cout==0)
						{
							for(uNt=0;uNt<3;uNt++)
							{
								caltBSP_XZ->uN_temp_dev2[uNt] = caltBSP_XZ->N_dev2_xz[XZLINE[index].Get_ORD()][uNt];
							}
						}
						for(uNt=0;uNt<3;uNt++)
						{
							if(n==XZLINE[index].Get_NUM()-1 && cout == XZLINE[index].Get_VER() - (uNt + 1))
							{
								caltBSP_XZ->N_dev2_xz[XZLINE[index].Get_ORD()][XZLINE[index].Get_VER() - (uNt + 1)] = caltBSP_XZ->uN_temp_dev2[uNt];
							}
						}
						caltBSP_XZ->N_sig_dev_1_xz[n][cout] = caltBSP_XZ->N_xz[XZLINE[index].Get_ORD()-1][cout+1];		//dev 1 importent,this is right
						caltBSP_XZ->N_sig_dev_2_xz[n][cout] = caltBSP_XZ->N_xz[XZLINE[index].Get_ORD()-2][cout+2];		//dev 2 importent,this is right	
					}
					caltBSP_XZ->N_sig_xz[n][cout] = caltBSP_XZ->N_xz[XZLINE[index].Get_ORD()][cout];
				}
			}
		}
	}
	
	if(PCUPI_XZ==TRUE)
	{
		//...XZ...CP...dev
		for(i=0;i<XZLINE[index].Get_VER()-1;i++)
		{		
			CP_xz[index][i].Set_ksi_dev1(((XZLINE[index].Get_ORD())/(caltBSP_XZ->U_xz[i+XZLINE[index].Get_ORD()+1]-caltBSP_XZ->U_xz[i+1]))*(CP_xz[index][i+1].Get_ksi()-CP_xz[index][i].Get_ksi()));
			CP_xz[index][i].Set_eta_dev1(((XZLINE[index].Get_ORD())/(caltBSP_XZ->U_xz[i+XZLINE[index].Get_ORD()+1]-caltBSP_XZ->U_xz[i+1]))*(CP_xz[index][i+1].Get_eta()-CP_xz[index][i].Get_eta()));		
			CP_xz[index][i].Set_zeta_dev1(((XZLINE[index].Get_ORD())/(caltBSP_XZ->U_xz[i+XZLINE[index].Get_ORD()+1]-caltBSP_XZ->U_xz[i+1]))*(CP_xz[index][i+1].Get_zeta()-CP_xz[index][i].Get_zeta()));		
		}
		GetMethod->create_Uni_Knot_Ver(&cacl_KV, XZLINE[index].Get_VER()-1, XZLINE[index].Get_ORD()-1, caltBSP_XZ->U_xz_dev, XZLINE[index].Get_VERARR()-2);

		for(i=0;i<XZLINE[index].Get_VER()-2;i++)
		{
			CP_xz[index][i].Set_ksi_dev2(((XZLINE[index].Get_ORD()-1)/(caltBSP_XZ->U_xz_dev[i+XZLINE[index].Get_ORD()-1+1]-caltBSP_XZ->U_xz_dev[i+1]))*(CP_xz[index][i+1].Get_ksi_dev1()-CP_xz[index][i].Get_ksi_dev1()));
			CP_xz[index][i].Set_eta_dev2(((XZLINE[index].Get_ORD()-1)/(caltBSP_XZ->U_xz_dev[i+XZLINE[index].Get_ORD()-1+1]-caltBSP_XZ->U_xz_dev[i+1]))*(CP_xz[index][i+1].Get_eta_dev1()-CP_xz[index][i].Get_eta_dev1()));		
			CP_xz[index][i].Set_zeta_dev2(((XZLINE[index].Get_ORD()-1)/(caltBSP_XZ->U_xz_dev[i+XZLINE[index].Get_ORD()-1+1]-caltBSP_XZ->U_xz_dev[i+1]))*(CP_xz[index][i+1].Get_zeta_dev1()-CP_xz[index][i].Get_zeta_dev1()));				
		}
		temp_x_dev1 = new double;
		temp_y_dev1 = new double;
		temp_z_dev1 = new double;
			
		temp_x_dev2 = new double;
		temp_y_dev2 = new double;
		temp_z_dev2 = new double;	
	}
	temp_x = new double;
	temp_y = new double;
	temp_z = new double;
	
	
	
	//...XZ...Bspline...normal vector...kslope
	for(n=0;n<XZLINE[index].Get_NUM();n++)
	{	
		*temp_x = 0.0;
		*temp_y = 0.0;
		*temp_z = 0.0;
		if(PCUPI_XZ==TRUE)
		{
			*temp_x_dev1 = 0.0;
			*temp_y_dev1 = 0.0;
			*temp_z_dev1 = 0.0;
			
			*temp_x_dev2 = 0.0;
			*temp_y_dev2 = 0.0;
			*temp_z_dev2 = 0.0;
		}

		for(cot=0;cot<XZLINE[index].Get_VER();cot++)
		{
			*temp_x += CP_xz[index][cot].Get_ksi() * caltBSP_XZ->N_sig_xz[n][cot];
			*temp_y += CP_xz[index][cot].Get_eta() * caltBSP_XZ->N_sig_xz[n][cot];
			*temp_z += CP_xz[index][cot].Get_zeta() * caltBSP_XZ->N_sig_xz[n][cot];
		}
		
		if(PCUPI_XZ==TRUE)
		{
			for(cot=0;cot<XZLINE[index].Get_VER()-1;cot++)
			{
				if(n==XZLINE[index].Get_NUM()-1)
				{
					*temp_x_dev1 = CP_xz[index][XZLINE[index].Get_VER()-2].Get_ksi_dev1();
					*temp_y_dev1 = CP_xz[index][XZLINE[index].Get_VER()-2].Get_eta_dev1();
					*temp_z_dev1 = CP_xz[index][XZLINE[index].Get_VER()-2].Get_zeta_dev1();
				}
				else if(n==0)
				{
					*temp_x_dev1 = CP_xz[index][0].Get_ksi_dev1();
					*temp_y_dev1 = CP_xz[index][0].Get_eta_dev1();
					*temp_z_dev1 = CP_xz[index][0].Get_zeta_dev1();
				}
				else
				{
					*temp_x_dev1 += CP_xz[index][cot].Get_ksi_dev1() * caltBSP_XZ->N_sig_dev_1_xz[n][cot];
					*temp_y_dev1 += CP_xz[index][cot].Get_eta_dev1() * caltBSP_XZ->N_sig_dev_1_xz[n][cot];
					*temp_z_dev1 += CP_xz[index][cot].Get_zeta_dev1() * caltBSP_XZ->N_sig_dev_1_xz[n][cot];
				}
			}
		
			for(cot=0;cot<XZLINE[index].Get_VER()-2;cot++)
			{
				if(n==XZLINE[index].Get_NUM()-1)
				{
					*temp_x_dev2 = CP_xz[index][XZLINE[index].Get_VER()-3].Get_ksi_dev2();
					*temp_y_dev2 = CP_xz[index][XZLINE[index].Get_VER()-3].Get_eta_dev2();
					*temp_z_dev2 = CP_xz[index][XZLINE[index].Get_VER()-3].Get_zeta_dev2();
				}
				else if(n==0)
				{
					*temp_x_dev2 = CP_xz[index][0].Get_ksi_dev2();
					*temp_y_dev2 = CP_xz[index][0].Get_eta_dev2();
					*temp_z_dev2 = CP_xz[index][0].Get_zeta_dev2();
				}
				else
				{
					*temp_x_dev2 += CP_xz[index][cot].Get_ksi_dev2() * caltBSP_XZ->N_sig_dev_2_xz[n][cot];
					*temp_y_dev2 += CP_xz[index][cot].Get_eta_dev2() * caltBSP_XZ->N_sig_dev_2_xz[n][cot];
					*temp_z_dev2 += CP_xz[index][cot].Get_zeta_dev2() * caltBSP_XZ->N_sig_dev_2_xz[n][cot];
				}
			}
		}

		BSPL_xz[index].x[n] = *temp_x;
		BSPL_xz[index].y[n] = *temp_y;
		BSPL_xz[index].z[n] = *temp_z;
	
		if(PCUPI_XZ==TRUE)
		{
			BSPL_xz[index].x_dev1[n] = *temp_x_dev1;
			BSPL_xz[index].y_dev1[n] = *temp_y_dev1;
			BSPL_xz[index].z_dev1[n] = *temp_z_dev1;

			BSPL_xz[index].x_dev2[n] = *temp_x_dev2;
			BSPL_xz[index].y_dev2[n] = *temp_y_dev2;
			BSPL_xz[index].z_dev2[n] = *temp_z_dev2;
		
			BSPL_xz[index].nx_xz[n] = GetMethod->cacu_nx(BSPL_xz[index].x_dev1[n], BSPL_xz[index].z_dev1[n]);
			BSPL_xz[index].ny_xz[n] = GetMethod->cacu_ny(BSPL_xz[index].x_dev1[n], BSPL_xz[index].z_dev1[n]);

			BSPL_xz[index].kslope_xz[n] = GetMethod->cacu_kslope(BSPL_xz[index].x_dev1[n], BSPL_xz[index].z_dev1[n], BSPL_xz[index].x_dev2[n], BSPL_xz[index].z_dev2[n]);
		}
	}
	
	delete temp_x; delete temp_y; delete temp_z;
	if(PCUPI_XZ==TRUE)
	{
		delete temp_x_dev1; delete temp_y_dev1; delete temp_z_dev1;
		delete temp_x_dev2; delete temp_y_dev2; delete temp_z_dev2;
	}
}
