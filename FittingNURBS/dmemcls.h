/*

  Template Classes For 1D ~ 5D Array

  1998. 9.25, 1999. 8.11

  written by Eui-Sang Hwang

  Dept.  : Chungnam National Univ.
	          Naval Architecture & Ocean Engineering

  E-mail : s_usang@hanbat.chungnam.ac.kr(x)
	          hus90@hanmail.net
	          hus90@yahoo.com(x)
*/

#ifndef __cplusplus
#error Must use C++ for CVector and CArray2d ~ 5d
#endif

#ifndef __DMEMCLS_H__
#define __DMEMCLS_H__

#ifdef	__DMEMCLSDEBUG__

	#include "dmcdebug.h"

#else

	#include "dmcreles.h"

#endif

 typedef CVector <double> cvecd;
 typedef CVector <   int> cveci;
 typedef CArray2d<double> car2d;
 typedef CArray2d<   int> car2i;
 typedef CArray3d<double> car3d;
 typedef CArray4d<double> car4d;
 typedef CArray5d<double> car5d;

 #define CVEC(T) CVector<T >

#endif

/*... end of dmemcls.h...*/
