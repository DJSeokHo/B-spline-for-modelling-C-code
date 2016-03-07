// NumForIndex.h: interface for the NumForIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NUMFORINDEX_H__64B79A27_C38A_4B13_9A27_9B514BE6B6A2__INCLUDED_)
#define AFX_NUMFORINDEX_H__64B79A27_C38A_4B13_9A27_9B514BE6B6A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class NumForIndex  
{
public:
	int Get_NUM();
	int Get_VERARR();
	int Get_BPARR();
	int Get_ORD();
	int Get_VER();
	int Get_BP(void);
	void Set_NUM(int snum);
	void Set_VERARR(int sverarr);
	void Set_BPARR(int sbparr);
	void Set_ORD(int sord);
	void Set_VER(int sver);
	void Set_BP(int sbp);
	NumForIndex();
	virtual ~NumForIndex();
	
private:
	int BP;
	int VER;
	int ORD;
	int BPARR;
	int VERARR;
	int NUM;

};

#endif // !defined(AFX_NUMFORINDEX_H__64B79A27_C38A_4B13_9A27_9B514BE6B6A2__INCLUDED_)
