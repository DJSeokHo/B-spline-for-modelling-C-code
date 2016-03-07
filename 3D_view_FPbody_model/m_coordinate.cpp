// m_coordinate.cpp: implementation of the m_coordinate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3D_view_FPbody_model.h"
#include "m_coordinate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

m_coordinate::m_coordinate()
{

}

m_coordinate::~m_coordinate()
{

}

void m_coordinate::set_xViewPort(double temp_xvp)
{
	xViewPort = temp_xvp;
}

void m_coordinate::set_yViewPort(double temp_yvp)
{
	yViewPort = temp_yvp;
}

void m_coordinate::set_xWinOrg(double temp_xwo)
{
	xWinOrg = temp_xwo;
}

void m_coordinate::set_yWinOrg(double temp_ywo)
{
	yWinOrg = temp_ywo;
}

void m_coordinate::set_xViewExt(double temp_xve)
{
	xViewExt = temp_xve;
}

void m_coordinate::set_yViewExt(double temp_yve)
{
	yViewExt = temp_yve;
}

void m_coordinate::set_xWinExt(double temp_xwe)
{
	xWinExt = temp_xwe;
}

void m_coordinate::set_yWinExt(double temp_ywe)
{
	yWinExt = temp_ywe;
}

void m_coordinate::set_xViewOrg(double temp_xvo)
{
	xViewOrg = temp_xvo;
}

void m_coordinate::set_yViewOrg(double temp_yvo)
{
	yViewOrg = temp_yvo;
}

double m_coordinate::get_yWindow()
{
	yWindow = (yViewPort - yViewOrg) * yWinExt/yViewExt + yWinOrg;
	return yWindow;
}

double m_coordinate::get_xWindow()
{
	xWindow = (xViewPort - xViewOrg) * xWinExt/xViewExt + xWinOrg;
	return xWindow;
}
