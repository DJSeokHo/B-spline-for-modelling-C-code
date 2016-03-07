// Operat.h: interface for the Operat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPERAT_H__AA411BED_676C_44A6_A2D9_2C34F3750085__INCLUDED_)
#define AFX_OPERAT_H__AA411BED_676C_44A6_A2D9_2C34F3750085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Operat  
{
public:
	double offset;
	int index;
	Operat();
	virtual ~Operat();
	
	void Set_xRot(GLdouble xr)
	{
		xRot = xr;
	}
	void Set_yRot(GLdouble yr)
	{
		yRot = yr;
	}
	void Set_MMS(GLdouble mms)
	{
		MouseMoveSpeed = mms;
	}
	void Set_Scale(GLdouble Scale)
	{
		m_Scale = Scale;
	}
	void Set_xMove(GLdouble xm)
	{
		xMove = xm;
	}
	void Set_yMove(GLdouble ym)
	{
		yMove = ym;
	}

	GLdouble Get_xRot()
	{
		return xRot;
	}
	GLdouble Get_yRot()
	{
		return yRot;
	}
	GLdouble Get_MMS()
	{
		return MouseMoveSpeed;
	}
	GLdouble Get_Scale()
	{
		return m_Scale;
	}
	GLdouble Get_xMove()
	{
		return xMove;
	}
	GLdouble Get_yMove()
	{
		return yMove;
	}

	void Set_RBD(BOOL RBD)
	{
		RButDon = RBD;
	}
	BOOL Get_RBD()
	{
		return RButDon;
	}
	void Set_LBD(BOOL LBD)
	{
		LButDon = LBD;
	}
	BOOL Get_LBD()
	{
		return LButDon;
	}
	void Set_SHIFT(BOOL SHIFT)
	{
		SHIFTDon = SHIFT;
	}
	void Set_CTRL(BOOL CTRL)
	{
		CTRLDon = CTRL;
	}
	BOOL Get_SHIFT()
	{
		return SHIFTDon;
	}
	BOOL Get_CTRL()
	{
		return CTRLDon;
	}
	CPoint p_new, p_old;

private:
	GLdouble xRot, yRot, xMove, yMove;
	BOOL LButDon, RButDon, SHIFTDon, CTRLDon;
	GLdouble MouseMoveSpeed, m_Scale;
};

#endif // !defined(AFX_OPERAT_H__AA411BED_676C_44A6_A2D9_2C34F3750085__INCLUDED_)
