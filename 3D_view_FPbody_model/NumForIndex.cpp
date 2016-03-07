// NumForIndex.cpp: implementation of the NumForIndex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3D_view_FPbody_model.h"
#include "NumForIndex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NumForIndex::NumForIndex()
{
	
}

NumForIndex::~NumForIndex()
{

}

void NumForIndex::Set_BP(int sbp)
{
	BP = sbp;
}

void NumForIndex::Set_VER(int sver)
{
	VER = sver;
}

void NumForIndex::Set_ORD(int sord)
{
	ORD = sord;
}

void NumForIndex::Set_BPARR(int sbparr)
{
	BPARR = sbparr;
}

void NumForIndex::Set_VERARR(int sverarr)
{
	VERARR = sverarr;
}

void NumForIndex::Set_NUM(int snum)
{
	NUM = snum;
}

int NumForIndex::Get_BP()
{
	return BP;
}

int NumForIndex::Get_VER()
{
	return VER;
}

int NumForIndex::Get_ORD()
{	
	return ORD;
}

int NumForIndex::Get_BPARR()
{
	return BPARR;
}

int NumForIndex::Get_VERARR()
{
	return VERARR;
}

int NumForIndex::Get_NUM()
{
	return NUM;
}
