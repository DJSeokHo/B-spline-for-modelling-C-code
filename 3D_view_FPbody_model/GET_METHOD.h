// GET_METHOD.h: interface for the GET_METHOD class.
//
//////////////////////////////////////////////////////////////////////
#include "math.h"

#if !defined(AFX_GET_METHOD_H__79EC43FE_6891_4288_8E6A_419D0474675B__INCLUDED_)
#define AFX_GET_METHOD_H__79EC43FE_6891_4288_8E6A_419D0474675B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GET_METHOD  
{
public:
	int FindSpan(int n, int p, double u, double *U);
	void create_Uni_Knot_Ver(int *u_num, int n, int p, double *knot, int verarr);
	void matrix_inversion_using_elementary_operation(double **original, double **inverse, int dim);
	double cacu_kslope(double xu, double yu, double xuu, double yuu);
	double cacu_ny(double xu, double yu);
	double cacu_nx(double xu, double yu);
	double cacu_Nki_dev(int tk, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1);
	double cacu_Nki(double u, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1);
	double cacu_BP_un(double sNv_1, double sn, int od, int bp);
	double cacu_BP_sn(double sn_1, double xn, double xn_1, double yn, double yn_1);
	double ang_to_rad(double ANG);
	GET_METHOD();
	virtual ~GET_METHOD();

};

#endif // !defined(AFX_GET_METHOD_H__79EC43FE_6891_4288_8E6A_419D0474675B__INCLUDED_)
