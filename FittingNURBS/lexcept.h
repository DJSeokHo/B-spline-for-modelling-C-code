/*
    Exception handler for CVector, CArray2d~3d

    1998. 9. 26, 9.27

    written by Hwang, Ui Sang
*/

#ifndef __cplusplus
#error Must use C++ for Limit checking template classes
#endif

#ifndef __LIMITEXCEPTION_H__
#define __LIMITEXCEPTION_H__

#include <stdio.h>
#include <stdlib.h>
#include "clstype.h"

template <class Type>
class CException {
private:
    classtype_t t1;
exceptiontype_t t2;

public:
  ~CException(					  );
   CException( CVector	<Type> *, exceptiontype_t );
   CException( CArray2d <Type> *, exceptiontype_t );
   CException( CArray3d <Type> *, exceptiontype_t );
   CException( CArray4d <Type> *, exceptiontype_t );
   CException( CArray5d <Type> *, exceptiontype_t );
   CException( _Col2d	<Type> *, exceptiontype_t );
   CException( _Row3d	<Type> *, exceptiontype_t );
   CException( _Col3d	<Type> *, exceptiontype_t );
   CException( _Layer	<Type> *, exceptiontype_t );
   CException( _Row4d	<Type> *, exceptiontype_t );
   CException( _Col4d	<Type> *, exceptiontype_t );
   CException( _Space	<Type> *, exceptiontype_t );
   CException( _Lay5d	<Type> *, exceptiontype_t );
   CException( _Row5d	<Type> *, exceptiontype_t );
   CException( _Col5d	<Type> *, exceptiontype_t );
   CException(					  );

   void exceptionmessage( void );
};

template <class Type>
CException<Type>::~CException( ) {  }

template <class Type>
CException<Type>::CException ( ) {

   puts("CException() error...\n");
   exit(0);
}

template <class Type>
CException<Type>::CException( CVector  <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_CVECTOR_TYPE ;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( CArray2d <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_CARRAY2D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( CArray3d <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_CARRAY3D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( CArray4d <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_CARRAY4D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( CArray5d <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_CARRAY5D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Col2d   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_COL2D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Row3d   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_ROW3D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Col3d   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_COL3D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Layer   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_LAYER_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Row4d   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_ROW4D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Col4d   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_COL4D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Space   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_SPACE_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Lay5d   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_LAY5D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Row5d   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_ROW5D_TYPE;
   t2 = v2;
}

template <class Type>
CException<Type>::CException( _Col5d   <Type> *v1, exceptiontype_t v2) {

   t1 = TEMPLATE_CLASS_COL5D_TYPE;
   t2 = v2;
}

template <class Type>
void CException<Type>::exceptionmessage( void ) {

   static char *errstring[] = {
   "Error 0001 : Insufficient memory...\n",
   "Error 0002 : I-Space limit exceeds...\n",
   "Error 0003 : J-Space limit exceeds...\n",
   "Error 0004 : Space limit exceeds...\n",
   "Error 0005 : Layer limit exceeds...\n",
   "Error 0006 : Row limit exceeds...\n",
   "Error 0007 : Column limit exceeds...\n",
   "Error 0008 : CArray2d * Cvector , size does not match...\n",
   "Error 0009 : CVector  * CArray2d, size does not match...\n",
   "Error 000A : CVector  * CVector , size does not match...\n",
   "Error 000B : CVector  + CVector , size does not match...\n",
   "Error 000C : CVector  - CVector , size does not match...\n",
   "Error 000D : CVector  = CVector , size does not match...\n",
   "Error 000E : CArray2d = CArray2d , size does not match...\n",
   "Error 000F : CArray3d = CArray3d , size does not match...\n",
   "Error 0010 : CArray4d = CArray4d , size does not match...\n",
   "Error 0011 : CArray5d = CArray5d , size does not match...\n",
   "Error 0012 : Memory doesn't assigned...\n",
   "Error 0013 : Vector limit exceed...\n"
   };

   static char *typestring[] = {
   "CVector  <Type> : ",  "CArray2d <Type> : ",
   "CArray3d <Type> : ",  "CArray4d <Type> : ",
   "CArray5d <Type> : ",  "_Col2d   <Type> : ",
   "_Row3d   <Type> : ",  "_Col3d   <Type> : ",
   "_Layer   <Type> : ",  "_Row4d   <Type> : ",
   "_Col4d   <Type> : ",  "_Space   <Type> : ",
   "_Lay5d   <Type> : ",  "_Row5d   <Type> : ",
   "_Col5d   <Type> : ",
   };

   char *p1, *p2;

   switch( t1 ) {
     case  TEMPLATE_CLASS_CVECTOR_TYPE	   : p1 = typestring[ 0];  break;
     case  TEMPLATE_CLASS_CARRAY2D_TYPE    : p1 = typestring[ 1];  break;
     case  TEMPLATE_CLASS_CARRAY3D_TYPE    : p1 = typestring[ 2];  break;
     case  TEMPLATE_CLASS_CARRAY4D_TYPE    : p1 = typestring[ 3];  break;
     case  TEMPLATE_CLASS_CARRAY5D_TYPE    : p1 = typestring[ 4];  break;
     case  TEMPLATE_CLASS_COL2D_TYPE	   : p1 = typestring[ 5];  break;
     case  TEMPLATE_CLASS_ROW3D_TYPE	   : p1 = typestring[ 6];  break;
     case  TEMPLATE_CLASS_COL3D_TYPE	   : p1 = typestring[ 7];  break;
     case  TEMPLATE_CLASS_LAYER_TYPE	   : p1 = typestring[ 8];  break;
     case  TEMPLATE_CLASS_ROW4D_TYPE	   : p1 = typestring[ 9];  break;
     case  TEMPLATE_CLASS_COL4D_TYPE	   : p1 = typestring[10];  break;
     case  TEMPLATE_CLASS_SPACE_TYPE	   : p1 = typestring[11];  break;
     case  TEMPLATE_CLASS_LAY5D_TYPE	   : p1 = typestring[12];  break;
     case  TEMPLATE_CLASS_ROW5D_TYPE	   : p1 = typestring[13];  break;
     case  TEMPLATE_CLASS_COL5D_TYPE	   : p1 = typestring[14];  break;
   }

   switch( t2 ) {
     case  INSUFFICIENT_MEMORY             : p2 =  errstring[ 0];  break;
     case  I_SPACE_LIMIT_EXCEED            : p2 =  errstring[ 1];  break;
     case  J_SPACE_LIMIT_EXCEED            : p2 =  errstring[ 2];  break;
     case    SPACE_LIMIT_EXCEED            : p2 =  errstring[ 3];  break;
     case    LAYER_LIMIT_EXCEED            : p2 =  errstring[ 4];  break;
     case      ROW_LIMIT_EXCEED            : p2 =  errstring[ 5];  break;
     case   COLUMN_LIMIT_EXCEED            : p2 =  errstring[ 6];  break;
     case  CARRAY2D_CVECTOR_MULTIPLICATION : p2 =  errstring[ 7];  break;
     case  CVECTOR_CARRAY2D_MULTIPLICATION : p2 =  errstring[ 8];  break;
     case  CVECTOR_CVECTOR_MULTIPLICATION  : p2 =  errstring[ 9];  break;
     case  CVECTOR_CVECTOR_ADDITION	       : p2 =  errstring[10];  break;
     case  CVECTOR_CVECTOR_SUBTRACTION	   : p2 =  errstring[11];  break;
     case  CVECTOR_CVECTOR_ASSIGNMENT	   : p2 =  errstring[12];  break;
     case  CARRAY2D_CARRAY2D_ASSIGNMENT    : p2 =  errstring[13];  break;
     case  CARRAY3D_CARRAY3D_ASSIGNMENT    : p2 =  errstring[14];  break;
     case  CARRAY4D_CARRAY4D_ASSIGNMENT    : p2 =  errstring[15];  break;
     case  CARRAY5D_CARRAY5D_ASSIGNMENT    : p2 =  errstring[16];  break;
     case  NO_ASSIGNED_MEMORY              : p2 =  errstring[17];  break;
     case  VECTOR_LIMIT_EXCEED             : p2 =  errstring[18];  break;
   }
   printf("%s%s", p1, p2);
   exit(0);
}

#endif

/*... End of LExcept.h ...*/
