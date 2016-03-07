// m_coordinate.h: interface for the m_coordinate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_M_COORDINATE_H__2B4DD744_3D53_491A_B9DA_970A228C1E8C__INCLUDED_)
#define AFX_M_COORDINATE_H__2B4DD744_3D53_491A_B9DA_970A228C1E8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class m_coordinate  
{
public:
	double get_xWindow();
	double get_yWindow();
	void set_yViewOrg(double temp_yvo);
	void set_xViewOrg(double temp_xvo);
	void set_yWinExt(double temp_ywe);
	void set_xWinExt(double temp_xwe);
	void set_yViewExt(double temp_yve);
	void set_xViewExt(double temp_xve);
	void set_yWinOrg(double temp_ywo);
	void set_xWinOrg(double temp_xwo);
	void set_yViewPort(double temp_yvp);
	void set_xViewPort(double temp_xvp);
	m_coordinate();
	virtual ~m_coordinate();
	private:
	double xViewPort, yViewPort;
	double xWindow, yWindow;
	double xWinOrg, yWinOrg;
	double xViewExt, yViewExt;
	double xWinExt, yWinExt;
	double xViewOrg, yViewOrg;
};

#endif // !defined(AFX_M_COORDINATE_H__2B4DD744_3D53_491A_B9DA_970A228C1E8C__INCLUDED_)
