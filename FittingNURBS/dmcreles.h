/*

  Template Classes For 1D ~ 5D Array

  written by Hwang, Eui Sang

  '98.3. 6, 3. 7, 3. 9, 3.16,
      3.19, 3.30, 6.10, 9. 3,
      9.26, 9.27, 11.11

  '99.1.25
  
  Dept.  : Chungnam National Univ.
           Naval Architecture & Ocean Engineering
           Propeller LAB.

  E-mail : s_usang@hanbat.chungnam.ac.kr (x)
           hus90@hanmail.net             (o)
           hus90@yahoo.com	              (x)
*/

#ifndef __cplusplus
#error Must use C++ for CVector, CArray2d ~ 5d
#endif

#ifndef __DMEMCLSRELEASE_H__
#define __DMEMCLSRELEASE_H__

#include <iostream.h>
#include <iomanip.h>
#include <string.h>
#include "lexcept.h"

template <class Type>
class CVector {
private:
   int	m_size;
   Type *m_lpType;
   friend void allocdmem( CVector <Type> &v );

public:
   CVector();
   CVector(int s);
   CVector(int s, const Type * const v);
   CVector(const CVector <Type> &v);
  ~CVector();
   friend CArray2d <Type>;

public:
   inline   Type  & operator[](int);
            Type  * operator &();
   CVector <Type> & operator =(CVector <Type> &v);
   CVector <Type> & operator =(const Type * const v);
   friend ostream & operator<<(ostream &v1,CVector<Type>&v2);

   /*------- Binary operator overloading functions -------*/
   friend
   inline CVector<Type>operator+ (CVector <Type> &, CVector <Type> &);
   friend
   inline CVector<Type>operator- (CVector <Type> &, CVector <Type> &);
   friend
   inline CVector<Type>operator* (CVector <Type> &,          Type   );
   friend
   inline CVector<Type>operator* (         Type   , CVector <Type> &);
   friend         Type operator* (CVector <Type> &, CVector <Type> &);
   friend
   inline CVector<Type>operator* (CVector <Type> &, CArray2d<Type> &);
   friend
   inline CVector<Type>operator* (CArray2d<Type> &, CVector <Type> &);

public:
   void setdimsize(int );
   void cleanup   (void);
   inline int getdimsize(void);
   inline CVector <Type> * getthis(void);
};

///////////////////////////////////////////////////////////////////////

template <class Type>
class CArray2d {
private:
   int m_row, m_col;
   Type **m_lpType;
   friend void allocdmem(CArray2d <Type> &v);

public:
   CArray2d();
   CArray2d(int, int);
   CArray2d(const CArray2d <Type> &v );
  ~CArray2d();
   friend class CVector <Type>;

public:
   inline    Type  *  operator[] (int);
             Type  ** operator	& ();
   CArray2d <Type> &  operator	= (CArray2d <Type> &v );
   friend  ostream &  operator<< (ostream &v1, CArray2d <Type> &v2);
   friend
   inline CVector<Type>operator* (CVector <Type> &, CArray2d <Type> &);
   friend
   inline CVector<Type>operator* (CArray2d<Type> &, CVector  <Type> &);

public:
   void setdimsize(int,int);
   void cleanup   (void);
   inline int getrowsize(void);
   inline int getcolsize(void);
   inline CArray2d <Type> * getthis(void);
};

///////////////////////////////////////////////////////////////////////

template <class Type>
class CArray3d {
private:
   int	m_layer, m_row, m_col;
   Type ***m_lpType;
   friend void allocdmem(CArray3d <Type> &v);

public:
   CArray3d();
   CArray3d(int, int, int);
   CArray3d(const CArray3d <Type> &v );
  ~CArray3d();

public:
   inline    Type **  operator[] (int);
             Type *** operator	& ();
   CArray3d <Type> &  operator	= (CArray3d <Type> &v);
   friend  ostream &  operator<< (ostream &v1, CArray3d <Type> &v2);

public:
   void setdimsize(int, int, int);
   void cleanup   (void);
   inline int getlayersize (void);
   inline int getrowsize   (void);
   inline int getcolsize   (void);
   inline CArray3d <Type> * getthis(void);
};

///////////////////////////////////////////////////////////////////////

template <class Type>
class CArray4d {
private:
   int	m_space, m_layer, m_row, m_col;
   Type ****m_lpType;
   friend void allocdmem( CArray4d <Type> &v );

public:
   CArray4d();
   CArray4d(int, int, int, int);
   CArray4d(const CArray4d <Type> &v );
  ~CArray4d();

public:
   inline    Type ***  operator [](int);
             Type **** operator & ();
   CArray4d <Type>  &  operator = (CArray4d <Type> &v );
   friend   ostream &  operator <<(ostream &v1, CArray4d <Type> &v2);

public:
   void setdimsize(int,int,int,int);
   void cleanup   (void);
   inline int getispacesize(void);
   inline int getlayersize (void);
   inline int getrowsize   (void);
   inline int getcolsize   (void);
   inline CArray4d <Type> * getthis(void);
};

///////////////////////////////////////////////////////////////////////

template <class Type>
class CArray5d {
private:
   int	m_ispace, m_jspace, m_layer, m_row, m_col;
   Type *****m_lpType;
   friend void  allocdmem( CArray5d <Type> &v );

public:
   CArray5d();
   CArray5d(int, int, int, int, int);
   CArray5d(const CArray5d <Type> &v );
  ~CArray5d();

public:
   inline Type ****	operator[](int);
          Type *****operator& ();
   CArray5d <Type>  &	operator=(CArray5d <Type> &v );
   friend   ostream &	operator<<(ostream &v1, CArray5d <Type> &v2);

public:
   void setdimsize(int,int,int,int,int);
   void cleanup   (void);
   inline int getispacesize(void);
   inline int getjspacesize(void);
   inline int getlayersize (void);
   inline int getrowsize   (void);
   inline int getcolsize   (void);
   inline CArray5d <Type> * getthis(void);
};

//--------------------------------------------------------------
//  Vector
//--------------------------------------------------------------

template <class Type>
CVector<Type>::CVector() : m_lpType(NULL), m_size(0) {

}

template <class Type>
CVector<Type>::CVector(int s) : m_size(s){

   allocdmem(*this);
}

template <class Type>
CVector <Type>::CVector(int s, const Type * const v) : m_size(s) {

   if( m_lpType != NULL ) {
       allocdmem(*this);
       memcpy((void*)  m_lpType, (void*)v, sizeof(Type)*m_size);
   }
}

template <class Type>
CVector<Type>::CVector(const CVector <Type> &v) {

   m_size = v.m_size;
   allocdmem(*this);

   memcpy((void*)  m_lpType,
          (void*)v.m_lpType, sizeof(Type)*m_size);
}

template <class Type>
CVector<Type>::~CVector() {

   if( m_lpType != NULL ) {
       cleanup();
   }
}

template <class Type>
void CVector<Type>::cleanup(void) {

   if( m_lpType != NULL ) {
       delete [] m_lpType;
       m_size = 0;
       m_lpType = NULL;
   }
}

template <class Type>
inline Type & CVector<Type>::operator [] (int n) {

   return m_lpType[n];
}

template <class Type>
Type * CVector<Type>::operator & () {

   return m_lpType;
}

template <class Type>
CVector <Type>	operator + (CVector <Type> &v1, CVector <Type> &v2) {

   if( v1.m_size != v2.m_size ) {
       CException <Type> plus( v1.getthis(), CVECTOR_CVECTOR_ADDITION );
       plus.exceptionmessage();
   }
   CVector <Type> temp(v1.m_size);

   for(int i = 0; i < v1.m_size; i++) temp.m_lpType[i] = v1.m_lpType[i] + v2.m_lpType[i];

   return temp;
}

template <class Type>
CVector <Type> operator - (CVector <Type> &v1, CVector <Type> &v2) {

   if( v1.m_size != v2.m_size ) {
       CException <Type> sub( v1.getthis(),  CVECTOR_CVECTOR_SUBTRACTION );
       sub.exceptionmessage();
   }
   CVector <Type> temp(v1.m_size);

   for(int i = 0; i < v1.m_size; i++) temp.m_lpType[i] = v1.m_lpType[i] - v2.m_lpType[i];

   return temp;
}

template <class Type>
CVector <Type> operator * (CVector <Type> &v1, Type v2) {

   CVector <Type> temp( v1.m_size );

   for(int i = 0; i < v1.m_size; i++) temp.m_lpType[i] = v1.m_lpType[i] * v2;

   return temp;
}

template <class Type>
CVector <Type> operator * (Type v1, CVector  <Type> &v2) {

   CVector <Type> temp( v2.m_size );

   for(int i = 0; i < v2.m_size; i++) temp.m_lpType[i] = v2.m_lpType[i] * v1;

   return temp;
}

template <class Type>
Type operator * (CVector <Type> &v1, CVector <Type> &v2) {

   if( v1.m_size != v2.m_size ) {
       CException <Type> mul( v1.getthis(), CVECTOR_CVECTOR_MULTIPLICATION );
       mul.exceptionmessage();
   }
   int i;
   Type temp = Type(0);

   for( i = 0; i < v1.m_size ; i++)
   temp += v1.m_lpType[i] * v2.m_lpType[i];

   return temp;
}

template <class Type>
CVector <Type> operator * (CVector <Type> &v1, CArray2d <Type> &v2 )	{

   if( v1.m_size != v2.m_row ) {
       CException <Type> mul( v1.getthis(), CVECTOR_CARRAY2D_MULTIPLICATION );
       mul.exceptionmessage();
   }
   CVector <Type> temp( v2.m_row );
   int i, j;

   for( i = 0; i < v2.m_row ; i++)
   for( j = 0; j < v1.m_size; j++) temp.m_lpType[i] += v1.m_lpType[j] * v2.m_lpType[j][i];

   return temp;
}

template <class Type>
CVector <Type> & CVector<Type>::operator = (CVector <Type> &v) {

   if( m_lpType == NULL ) {
       m_size    =  v.m_size;
       allocdmem(*this);
   }
   else if ( this == v.getthis() || ( m_size != v.m_size )) {
       CException <Type> assign( this, CVECTOR_CVECTOR_ASSIGNMENT );
       assign.exceptionmessage();
   }
   else;
   memcpy((void*)  m_lpType,
          (void*)v.m_lpType, sizeof(Type)*m_size);

   return (CVector<Type>&)*this;
}

template <class Type>
CVector <Type> & CVector<Type>::operator = (const Type * const v) {

   if( m_lpType != NULL ) {
       memcpy((void*)  m_lpType, (void*)v, sizeof(Type)*m_size);
   }
   return (CVector<Type>&)*this;
}

template <class Type>
ostream & operator << ( ostream &v1, CVector <Type> &v2) {

  v1.setf(ios::fixed | ios::showpoint | ios::right | ios::showpos);
  v1.precision(4);
  int i;

  for( i = 0; i < v2.m_size; i++) {
     v1 << '[' << setw( 3) << i << ']'
        << setw( 3) << '=' 
        << setw(10) << setiosflags(ios::left | ios::showpos) << v2.m_lpType[i];
     v1 << resetiosflags(ios::left | ios::showpos);
     if(!((i+1)%4)) v1 << endl;
  }
  return v1;
}

template <class Type>
inline CVector <Type> * CVector<Type>::getthis(void) {

  return this;
}

template <class Type>
void CVector<Type>::setdimsize(int size) {

   if( m_lpType == NULL ) {
       m_size    =  size;
       allocdmem(*this);
   }
}

template <class Type>
inline int CVector<Type>::getdimsize(void) {

   return ( m_size );
}

template <class Type>
void allocdmem(CVector <Type> &v) {

   v.m_lpType = new Type [v.m_size];

   if( v.m_lpType == NULL) {
       CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
       alloc.exceptionmessage();
   }
   memset((void*)v.m_lpType, 0x00, sizeof(Type)*v.m_size);
}

//--------------------------------------------------------------
//   2D ARRAY
//--------------------------------------------------------------

template <class Type>
CArray2d <Type>::CArray2d() {

   m_lpType = NULL;
   m_row = m_col = 0;
}

template <class Type>
CArray2d <Type>::CArray2d(int row, int col) {

   m_col = col;
   m_row = row;
   allocdmem(*this);
}

template <class Type>
CArray2d <Type>::CArray2d(const CArray2d<Type> &v ) {

   m_row = v.m_row;
   m_col = v.m_col;
   allocdmem(*this);

   for( int i = 0; i < m_row; i++)
   memcpy((void*)  m_lpType[i],
          (void*)v.m_lpType[i], sizeof(Type)*m_col);
}

template <class Type>
CArray2d <Type>::~CArray2d() {

   if( m_lpType != NULL ) {
       cleanup();
   }
}

template <class Type>
void CArray2d<Type>::cleanup(void) {

   if( m_lpType != NULL ) {
       for(int i = 0; i < m_row; i++) delete [] m_lpType[i];
       delete [] m_lpType;
       m_lpType = NULL;
       m_row = m_col = 0;
   }
}


template <class Type>
CVector <Type> operator * (CArray2d <Type> &v1, CVector <Type> &v2) {

   if( v1.m_col != v2.m_size ) {
       CException <Type> mul( v1.getthis(), CARRAY2D_CVECTOR_MULTIPLICATION );
       mul.exceptionmessage();
   }
   CVector <Type> temp( v2.m_size );
   int i, j;

   for( i = 0; i < v1.m_row ; i++)
   for( j = 0; j < v2.m_size; j++) temp.m_lpType[i] += v1.m_lpType[i][j] * v2.m_lpType[j];

   return temp;
}

template <class Type>
Type * CArray2d<Type>::operator [] (int n) {

   return m_lpType[n];
}

template <class Type>
Type ** CArray2d<Type>::operator & () {

   return (m_lpType);
}

template <class Type>
CArray2d <Type> & CArray2d<Type>::operator = (CArray2d <Type> &v) {

   if( m_lpType == NULL ) {
       m_row	=  v.m_row;
       m_col	=  v.m_col;
       allocdmem(*this);
   }
   else if ( this == v.getthis() || ( m_row != v.m_row || m_col != v.m_col) ) {
      CException <Type> assign( this, CARRAY2D_CARRAY2D_ASSIGNMENT );
      assign.exceptionmessage();
   }
   else;
   for( int i = 0; i < m_row; i++)
   memcpy((void*)m_lpType[i], (void*)v.m_lpType[i], sizeof(Type)*m_col);

   return (CArray2d<Type>&)*this;
}

template <class Type>
ostream & operator << (ostream &v1, CArray2d <Type> &v2) {

  v1.setf(ios::fixed | ios::right | ios::right);
  v1.precision(4);
  int i, j, m, n;

  m = v2.getrowsize();
  n = v2.getcolsize();

  for(i = 0; i < m; i++) {
    v1 << "i = " << i << endl;
    for(j = 0; j < n; j++) { 
      v1 << setw(10) << v2[i][j];
      if(!((j+1)%5)) v1 << endl;
    }
    v1 << endl;
  }
  return v1;
}

template <class Type>
inline CArray2d <Type> * CArray2d<Type>::getthis(void) {

   return this;
}

template <class Type>
void CArray2d<Type>::setdimsize(int row, int col) {

   if( m_lpType == NULL ) {
       m_row	=  row;
       m_col	=  col;
       allocdmem(*this);
   }
}

template <class Type>
int CArray2d<Type>::getrowsize(void) {

   return (m_row);
}

template <class Type>
int CArray2d<Type>::getcolsize(void) {

   return (m_col);
}

template <class Type>
void allocdmem(CArray2d <Type> &v) {

   v.m_lpType = new Type* [v.m_row];

   if( v.m_lpType == NULL) {
       CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
       alloc.exceptionmessage();
   }
   for(int i = 0; i < v.m_row; i++) {
      v.m_lpType[i] = new Type [v.m_col];
      if( v.m_lpType[i] == NULL) {
          CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
          alloc.exceptionmessage();
      }
      memset((void*)v.m_lpType[i], 0x00, sizeof(Type)*v.m_col);
   }
}

//--------------------------------------------------------------
//   3D ARRAY
//--------------------------------------------------------------

template <class Type>
CArray3d <Type>::CArray3d() {

   m_lpType = NULL;
   m_layer = m_row = m_col = 0;
}

template <class Type>
CArray3d <Type>::CArray3d(int layer, int row, int col) {

   m_layer = layer;
   m_row   = row;
   m_col   = col;
   allocdmem(*this);
}

template <class Type>
CArray3d <Type>::CArray3d(const CArray3d<Type> &v) {

   int i, j;

   m_layer = v.m_layer;
   m_row   = v.m_row;
   m_col   = v.m_col;
   allocdmem(*this);

   for( i = 0; i < m_layer; i++)
   for( j = 0; j < m_row  ; j++)
   memcpy((void*)  m_lpType[i][j],
          (void*)v.m_lpType[i][j], sizeof(Type)*m_col);
}

template <class Type>
CArray3d <Type>::~CArray3d() {

   if( m_lpType != NULL ) {
       cleanup();
   }
}

template <class Type>
void CArray3d<Type>::cleanup(void) {

   if( m_lpType != NULL ) {
   int i, j;

   for( i = 0; i < m_layer; i++) {
     for( j = 0; j < m_row	; j++) {
	      delete [] m_lpType[i][j];
	   }  delete [] m_lpType[i];
   }    delete [] m_lpType;
   m_lpType = NULL;
   m_layer = m_row = m_col = 0;
   }
}

template <class Type>
inline Type ** CArray3d<Type>::operator [] (int n) {

   return m_lpType[n];
}

template <class Type>
Type *** CArray3d<Type>::operator & () {

   return (m_lpType);
}

template <class Type>
CArray3d <Type> & CArray3d<Type>::operator = (CArray3d <Type> &v) {

   int i, j;

   if( m_lpType == NULL ) {
       m_layer	=  v.m_layer;
       m_row	=  v.m_row;
       m_col	=  v.m_col;
       allocdmem(*this);
   }
   else if ( this == v.getthis()  || ( m_layer != v.m_layer ||
             m_row!= v.m_row      ||   m_col   != v.m_col   )) {
       CException <Type> assign( this, CARRAY3D_CARRAY3D_ASSIGNMENT );
       assign.exceptionmessage();
   }
   else;

   for(i = 0; i < m_layer; i++)
   for(j = 0; j < m_row  ; j++)
      memcpy((void*)  m_lpType[i][j],
             (void*)v.m_lpType[i][j], sizeof(Type)*m_col);

   return (CArray3d<Type>&)*this;
}

template <class Type>
ostream & operator << (ostream &v1, CArray3d <Type> &v2) {

  v1.setf(ios::fixed | ios::right | ios::right);
  v1.precision(4);
  int i, j, k, m, n, z;

  m = v2.getlayersize();
  n = v2.getrowsize();
  z = v2.getcolsize();

  for(i = 0; i < m; i++) {
    for(j = 0; j < n; j++) { 
      v1 << "i = " << i  << ", j = " << j 
         << ", k = 0 ~ " << (z-1) << endl;
      for(k = 0; k < z; k++) {
        v1 << setw(10) << v2[i][j][k];
        if(!((k+1)%5)) v1 << endl;
      }
      v1 << endl;
    }
  }
  return v1;
}

template <class Type>
inline CArray3d <Type> * CArray3d<Type>::getthis(void) {

   return this;
}

template <class Type>
inline int CArray3d<Type>::getlayersize(void) {

   return m_layer;
}

template <class Type>
inline int CArray3d<Type>::getrowsize(void) {

   return m_row;
}

template <class Type>
inline int CArray3d<Type>::getcolsize(void) {

   return m_col;
}

template <class Type>
void CArray3d<Type>::setdimsize(int layer, int row, int col) {

   if( m_lpType == NULL ) {
       m_layer	=  layer;
       m_row	=  row;
       m_col	=  col;
       allocdmem(*this);
   }
}

template <class Type>
void  allocdmem(CArray3d <Type> &v) {

   int i, j;

   v.m_lpType = new Type ** [v.m_layer];

   if( v.m_lpType == NULL) {
       CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
       alloc.exceptionmessage();
   }
   for(i = 0; i < v.m_layer; i++) {
      v.m_lpType[i] = new Type * [v.m_row];
      if( v.m_lpType[i] == NULL) {
          CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
          alloc.exceptionmessage();
      }
      for( j = 0; j < v.m_row; j++) {
	       v.m_lpType[i][j] = new Type [v.m_col];
         if( v.m_lpType[i][j] == NULL) {
             CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
             alloc.exceptionmessage();
	       }
	       memset((void*)v.m_lpType[i][j], 0x00, sizeof(Type)*v.m_col);
      }
   }
}

//--------------------------------------------------------------
//   4D ARRAY
//--------------------------------------------------------------

template <class Type>
CArray4d <Type>::CArray4d() {

   m_lpType = NULL;
   m_space = m_layer = m_row = m_col = 1;
}

template <class Type>
CArray4d <Type>::CArray4d(int space, int layer, int row, int col) {

   m_space = space;
   m_layer = layer;
   m_row   = row;
   m_col   = col;
   allocdmem(*this);
}

template <class Type>
CArray4d <Type>::CArray4d(const CArray4d<Type> &v) {

   int i, j, k;

   m_space = v.m_space;
   m_layer = v.m_layer;
   m_row   = v.m_row;
   m_col   = v.m_col;
   allocdmem(*this);

   for( i = 0; i < m_space; i++)
   for( j = 0; j < m_layer ; j++)
   for( k = 0; k < m_row   ; k++)
   memcpy((void*)  m_lpType[i][j][k],
          (void*)v.m_lpType[i][j][k], sizeof(Type)*m_col);
}

template <class Type>
CArray4d <Type>::~CArray4d() {

   if( m_lpType  != NULL ) {
       cleanup();
   }
}

template <class Type>
void CArray4d<Type>::cleanup(void) {

   if( m_lpType != NULL ) {
       int i, j, k;
       for( i = 0; i < m_space; i++) {
         for( j = 0; j < m_layer ; j++) {
           for( k = 0; k < m_row   ; k++)  {
             delete [] m_lpType[i][j][k];
           } delete [] m_lpType[i][j];
         }   delete [] m_lpType[i];
       }     delete [] m_lpType;
       m_lpType = NULL;
       m_space = m_layer = m_row = m_col = 0;
   }
}

template <class Type>
inline Type *** CArray4d<Type>::operator [] (int n) {

   return m_lpType[n];
}

template <class Type>
Type **** CArray4d<Type>::operator & () {

   return (m_lpType);
}

template <class Type>
CArray4d <Type> & CArray4d<Type>::operator = (CArray4d <Type> &v) {

   int i, j, k;

   if( m_lpType == NULL ) {
       m_space  =  v.m_space;
       m_layer  =  v.m_layer;
       m_row    =  v.m_row;
       m_col    =  v.m_col;
       allocdmem(*this);
   }
   else if ( this     == v.getthis()|| ( m_space != v.m_space ||
             m_layer  != v.m_layer	||   m_row   != v.m_row    ||
             m_col	  != v.m_col    )) {
      CException <Type> assign( this, CARRAY4D_CARRAY4D_ASSIGNMENT );
      assign.exceptionmessage();
   }
   else;

   for( i = 0; i < m_space; i++)
   for( j = 0; j < m_layer; j++)
   for( k = 0; k < m_row  ; k++)
      memcpy((void*)  m_lpType[i][j][k],
		     (void*)v.m_lpType[i][j][k], sizeof(Type)*m_col);

   return (CArray4d<Type>&)*this;
}

template <class Type>
inline CArray4d <Type> * CArray4d<Type>::getthis(void) {

  return this;
}

template <class Type>
void CArray4d<Type>::setdimsize(int space, int layer, int row, int col) {

   if( m_lpType == NULL ) {
       m_space  =  space;
       m_layer	=  layer;
       m_row	=  row;
       m_col	=  col;
       allocdmem(*this);
   }
}

template <class Type>
void  allocdmem(CArray4d <Type> &v) {

   int i, j, k;

   v.m_lpType = new Type *** [v.m_space];

   if( v.m_lpType == NULL) {
       CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
       alloc.exceptionmessage();
   }
   for( i = 0; i < v.m_space; i++) {
      v.m_lpType[i] = new Type ** [v.m_layer];
      if( v.m_lpType[i] == NULL) {
          CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
          alloc.exceptionmessage();
      }
      for( j = 0; j < v.m_layer; j++) {
        v.m_lpType[i][j] = new Type * [v.m_row];
        if( v.m_lpType[i][j] == NULL) {
            CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
            alloc.exceptionmessage();
        }
        for( k = 0; k < v.m_row; k++) {
          v.m_lpType[i][j][k] = new Type [v.m_col];
          if( v.m_lpType[i][j][k] == NULL) {
              CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
              alloc.exceptionmessage();
          }
          memset((void*)v.m_lpType[i][j][k], 0x00, sizeof(Type)*v.m_col);
       }
     }
   }
}

//--------------------------------------------------------------
//   5D ARRAY
//--------------------------------------------------------------

template <class Type>
CArray5d <Type>::CArray5d() {

   m_lpType = NULL;
   m_ispace = m_jspace = m_layer = m_row = m_col = 0;
}

template <class Type>
CArray5d <Type>::CArray5d(int ispace, int jspace, int layer, int row, int col) {

   m_ispace = ispace;
   m_jspace = jspace;
   m_layer  = layer;
   m_row    = row;
   m_col    = col;
   allocdmem(*this);
}

template <class Type>
CArray5d <Type>::CArray5d(const CArray5d<Type> &v) {

   int i, j, k, l;

   m_ispace = v.m_ispace;
   m_jspace = v.m_jspace;
   m_layer  = v.m_layer;
   m_row    = v.m_row;
   m_col    = v.m_col;
   allocdmem(*this);

   for( i = 0; i < m_ispace; i++)
   for( j = 0; j < m_jspace; j++)
   for( k = 0; k < m_layer ; k++)
   for( l = 0; l < m_row   ; l++)
      memcpy((void*)  m_lpType[i][j][k][l],
             (void*)v.m_lpType[i][j][k][l], sizeof(Type)*m_col);
}

template <class Type>
CArray5d <Type>::~CArray5d() {

   if( m_lpType != NULL ) {
       cleanup();
   }
}

template <class Type>
void CArray5d<Type>::cleanup(void) {

   if( m_lpType != NULL ) {
       int i, j, k, l;
       for( i = 0; i < m_ispace; i++) {
         for( j = 0; j < m_jspace ; j++) {
           for( k = 0; k < m_layer  ; k++) {
	           for( l = 0; l < m_row	; l++) {
               delete [] m_lpType[i][j][k][l];
             } delete [] m_lpType[i][j][k];
           }   delete [] m_lpType[i][j];
         }     delete [] m_lpType[i];
       }       delete [] m_lpType;
       m_lpType = NULL;
       m_ispace = m_jspace = m_layer = m_row = m_col = 0;
   }
}

template <class Type>
inline Type **** CArray5d<Type>::operator [] (int n) {

   return m_lpType[n];
}

template <class Type>
Type ***** CArray5d<Type>::operator & () {

   return (m_lpType);
}

template <class Type>
CArray5d <Type> & CArray5d<Type>::operator = (CArray5d <Type> &v) {

   int i, j, k, l;

   if( m_lpType == NULL ) {
       m_ispace =  v.m_ispace;
       m_jspace =  v.m_jspace;
       m_layer	=  v.m_layer;
       m_row	=  v.m_row;
       m_col	=  v.m_col;
       allocdmem(*this);
   }
   else if( this     == v.getthis() || ( m_ispace != v.m_ispace ||
           	m_jspace != v.m_jspace	||   m_layer  != v.m_layer  ||
       		m_row	 != v.m_row	    ||   m_col    != v.m_col    ))	{
      CException <Type> assign( this, CARRAY5D_CARRAY5D_ASSIGNMENT );
      assign.exceptionmessage();
   }
   else;

   for( i = 0; i < m_ispace; i++)
   for( j = 0; j < m_jspace; j++)
   for( k = 0; k < m_layer ; k++)
   for( l = 0; l < m_row   ; l++)
      memcpy((void*)  m_lpType[i][j][k][l],
          	 (void*)v.m_lpType[i][j][k][l], sizeof(Type)*m_col);

   return (CArray5d<Type>&)*this;
}

template <class Type>
inline CArray5d <Type> * CArray5d<Type>::getthis(void) {

   return this;
}

template <class Type>
void CArray5d<Type>::setdimsize(int ispace, int jspace, int layer, int row, int col) {

   if( m_lpType == NULL ) {
       m_ispace = ispace;
       m_jspace = jspace;
       m_layer	= layer;
       m_row	= row;
       m_col	= col;
       allocdmem(*this);
   }
}

template <class Type>
void  allocdmem(CArray5d <Type> &v) {

   int i, j, k, l;

   v.m_lpType = new Type **** [v.m_ispace];

   if( v.m_lpType == NULL) {
       CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
       alloc.exceptionmessage();
   }
   for(i = 0; i < v.m_ispace; i++) {
      v.m_lpType[i] = new Type *** [v.m_jspace];
      if( v.m_lpType[i] == NULL) {
      	  CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
      	  alloc.exceptionmessage();
      }
      for(j = 0; j < v.m_jspace; j++) {
        v.m_lpType[i][j] = new Type ** [v.m_layer];
        if( v.m_lpType[i][j] == NULL) {
	          CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
	          alloc.exceptionmessage();
        }
        for(k = 0; k < v.m_layer; k++) {
	         v.m_lpType[i][j][k] = new Type * [v.m_row];
	         if( v.m_lpType[i][j][k] == NULL) {
		           CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
		           alloc.exceptionmessage();
	         }
	         for(l = 0; l < v.m_row; l++) {
	           v.m_lpType[i][j][k][l] = new Type [v.m_col];
	           if( v.m_lpType[i][j][k][l] == NULL) {
		             CException <Type> alloc( v.getthis(), INSUFFICIENT_MEMORY );
		             alloc.exceptionmessage();
	           }
	           memset((void*)v.m_lpType[i][j][k][l], 0x00, sizeof(Type)*v.m_col);
	        }
	      }
      }
   }
}

#endif

/*... End of dmcreles.h...*/
