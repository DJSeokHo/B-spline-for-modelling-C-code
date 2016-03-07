// 3D_view_FPbody_modelDoc.h : interface of the CMy3D_view_FPbody_modelDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include "BP.h"
#include "VP.h"
#include "GET_METHOD.h"
#include "ALTCP_XY.h"
#include "ALTCP_YZ.h"
#include "ALTCP_XZ.h"
#include "ALTBSPLINE_XY.h"
#include "ALTBSPLINE_YZ.h"
#include "ALTBSPLINE_XZ.h"
#include "BSPLINE_XY.h"
#include "BSPLINE_YZ.h"
#include "BSPLINE_XZ.h"
#include "NumForIndex.h"

#if !defined(AFX_3D_VIEW_FPBODY_MODELDOC_H__C34A022B_621B_4316_93A2_24FE2B3F0B80__INCLUDED_)
#define AFX_3D_VIEW_FPBODY_MODELDOC_H__C34A022B_621B_4316_93A2_24FE2B3F0B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy3D_view_FPbody_modelDoc : public CDocument
{
protected: // create from serialization only
	CMy3D_view_FPbody_modelDoc();
	DECLARE_DYNCREATE(CMy3D_view_FPbody_modelDoc)

// Attributes
public:
	NumForIndex *XYLINE, *YZLINE, *XZLINE;
	int XYLNum, YZLNum, XZLNum; 
	//...Out Put X-Y, Y-Z, X-Z
	int cacl_KV;
	
	//...Init X-Y, Y-Z, X-Z malloc
	BP **BP_xy, **BP_yz, **BP_xz;
	VP **CP_xy, **CP_yz, **CP_xz;
	
	CALTCP_XY *caltCP_XY;
	CALTCP_YZ *caltCP_YZ;
	CALTCP_XZ *caltCP_XZ;
	
	CALTBSPLINE_XY *caltBSP_XY;
	CALTBSPLINE_YZ *caltBSP_YZ;
	CALTBSPLINE_XZ *caltBSP_XZ;
	
	BSPLINE_XY *BSPL_xy;
	BSPLINE_YZ *BSPL_yz;
	BSPLINE_XZ *BSPL_xz;

// Operations
	GET_METHOD *GetMethod;
	BOOL PCUPI_XY, PCUPI_YZ, PCUPI_XZ, PCUPI_CHANGE; 
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3D_view_FPbody_modelDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int BPLIndex;
	void CALT_BSPLINE_XZ();
	void CALT_BSPLINE_YZ();
	void CALT_BSPLINE_XY();
	void CALT_VP_XZ();
	void CALT_VP_YZ();
	void CALT_VP_XY();
	void Init_BP_XZ();
	void Init_BP_YZ();
	void Init_BP_XY();
	void Init_Num_Ord();
	virtual ~CMy3D_view_FPbody_modelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy3D_view_FPbody_modelDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3D_VIEW_FPBODY_MODELDOC_H__C34A022B_621B_4316_93A2_24FE2B3F0B80__INCLUDED_)
