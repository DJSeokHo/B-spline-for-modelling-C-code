/*
    Limit checking template classes for CVector, CArray2d~3d 

    '98. 9. 25, 9.26, 9.27

    written by Hwang, Ui Sang
*/

#ifndef __cplusplus
#error Must use C++ for Limit checking template classes
#endif

#ifndef __LIMITCHECK_H__
#define __LIMITCHECK_H__

#include "lexcept.h"

template <class Type>
class _Col2d {
private:
   CArray2d <Type> *m_lpCArray2d;

public:
 ~_Col2d(                   );
  _Col2d( CArray2d <Type> * );

public:
   inline Type & operator[] (int);
};

//////////////////////////////////////////////////

template <class Type>
class _Row3d {
private:
   int              m_rowIndex;
   CArray3d <Type> *m_lpCArray3d;

public:
   _Row3d( CArray3d <Type> * );
  ~_Row3d(                   );

friend _Col3d <Type>;

public:
   inline _Col3d <Type> operator[] (int);
};

template <class Type>
class _Col3d {
private:
   _Row3d <Type> *m_lpRow3d;

public:
   _Col3d( _Row3d <Type> * );
  ~_Col3d(                 );

public:
   inline Type & operator[] (int);
};

//////////////////////////////////////////////////


template <class Type>
class _Layer {
private:
   int              m_layerIndex;
   CArray4d <Type> *m_lpCArray4d;

public:
   _Layer( CArray4d <Type> * );
  ~_Layer(                   );

   friend _Row4d <Type>;
   friend _Col4d <Type>;

public:
   inline _Row4d <Type> operator[] (int);
};

template <class Type>
class _Row4d {
private:
   int            m_rowIndex;
   _Layer <Type> *m_lpLayer;

public:
   _Row4d( _Layer <Type> * );
  ~_Row4d(                 );

   friend _Col4d <Type>;

public:
   inline _Col4d <Type> operator[] (int);
};

template <class Type>
class _Col4d {
private:
   _Row4d <Type> *m_lpRow4d;

public:
   _Col4d( _Row4d <Type> *);
  ~_Col4d(                );

public:
   inline Type & operator[] (int);
};

//////////////////////////////////////////////////

template <class Type>
class _Space {
private:
   int m_spaceIndex;
   CArray5d <Type> *m_lpCArray5d;

public:
   _Space( CArray5d <Type> * );
  ~_Space(                   );

   friend _Lay5d <Type>;
   friend _Row5d <Type>;
   friend _Col5d <Type>;

public:
   inline _Lay5d <Type> operator [] (int);
};

template <class Type>
class _Lay5d {
private:
   int            m_layerIndex;
   _Space <Type> *m_lpSpace;

public:
   _Lay5d ( _Space <Type> *);
  ~_Lay5d (                );

   friend _Row5d <Type>;
   friend _Col5d <Type>;

public:
   inline _Row5d <Type> operator[] (int);
};

template <class Type>
class _Row5d {
private:
   int            m_rowIndex;
   _Lay5d <Type> *m_lpLayer;

public:
   _Row5d( _Lay5d <Type> * );
  ~_Row5d(                 );

   friend _Col5d <Type>;

public:
   inline _Col5d <Type> operator[] (int);
};

template <class Type>
class _Col5d {
private:
   _Row5d <Type> *m_lpRow5d;

public:
  ~_Col5d(                );
   _Col5d( _Row5d <Type> *);

public:
   inline Type & operator[] (int);
};

//////////////////////////////////////////////////
///           class _Col2d <Type>              ///  
///     Member functions of _Col2d <Type>      ///
//////////////////////////////////////////////////

template <class Type>
_Col2d<Type>::_Col2d( CArray2d <Type> *v) {

   m_lpCArray2d = v;
}

template <class Type>
_Col2d<Type>::~_Col2d( ) {

}

template <class Type>
Type & _Col2d<Type>::operator [ ] ( int v) {

   if( v >= m_lpCArray2d->m_col ) {
       CException <Type> col2d(this,  COLUMN_LIMIT_EXCEED );
       col2d.exceptionmessage();
   }
   return m_lpCArray2d->location(m_lpCArray2d->m_elem, v);
}

//////////////////////////////////////////////////
///            class _Row3d <Type>             ///
///     Member functions of _Row3d <Type>      ///
//////////////////////////////////////////////////

 template <class Type>
_Row3d<Type>::_Row3d( CArray3d <Type> *v ) {

   m_lpCArray3d = v;
}

 template <class Type>
_Row3d<Type>::~_Row3d() {   

}

 template <class Type>
_Col3d<Type> _Row3d<Type>::operator [] ( int n ) {

   if( n >= m_lpCArray3d->m_row || n < 0 ) {
       CException <Type> col3d( this, ROW_LIMIT_EXCEED );
       col3d.exceptionmessage();
   }
   m_rowIndex = n;

   _Col3d <Type> col3d (this);

   return col3d;
}

//////////////////////////////////////////////////
///            class _Col3d <Type>             ///
///     Member functions of _Col3d <Type>      ///
//////////////////////////////////////////////////

 template <class Type>
_Col3d<Type>::_Col3d( _Row3d <Type> *v ) {

   m_lpRow3d = v;
}

 template <class Type>
_Col3d<Type>::~_Col3d() {   

}

template <class Type>
Type & _Col3d<Type>::operator [] ( int v ) {

   if( v >= m_lpRow3d->m_lpCArray3d->m_col || v < 0 ) {
       CException <Type> col3d(this, COLUMN_LIMIT_EXCEED );
       col3d.exceptionmessage();
   }
   return m_lpRow3d->m_lpCArray3d->location(
          m_lpRow3d->m_lpCArray3d->m_elem, 
          m_lpRow3d->m_rowIndex, v);
} 

//////////////////////////////////////////////////
///            class _Layer <Type>             ///
///     Member functions of _Layer <Type>      ///
//////////////////////////////////////////////////

 template <class Type>
_Layer<Type>::_Layer( CArray4d <Type> *v) {

   m_lpCArray4d = v;
}

 template <class Type>
_Layer<Type>:: ~_Layer( ) {

}

 template <class Type>
_Row4d<Type> _Layer<Type>::operator [] ( int n ) {

   if( n >= m_lpCArray4d->m_layer || n < 0 ) {
       CException <Type> layer(this, LAYER_LIMIT_EXCEED );
       layer.exceptionmessage();
   }
   m_layerIndex = n;

   _Row4d <Type> row4d( this );

   return row4d;
}

//////////////////////////////////////////////////
///            class _Row4d <Type>             ///
///     Member functions of _Row4d <Type>      ///
//////////////////////////////////////////////////

 template <class Type>
_Row4d<Type>::_Row4d( _Layer <Type> *v ) {

   m_lpLayer = v;
}

 template <class Type>
_Row4d<Type>::~_Row4d() {   

}

 template <class Type>
_Col4d<Type> _Row4d<Type>::operator [] ( int n ) {

   if( n >= m_lpLayer->m_lpCArray4d->m_row || n < 0 ) {
       CException <Type> row4d( this, ROW_LIMIT_EXCEED );
       row4d.exceptionmessage();
   }
   m_rowIndex = n;

   _Col4d <Type> col4d(this);

   return col4d;
}

//////////////////////////////////////////////////
///            class _Col4d <Type>             ///
///     Member functions of _Col4d <Type>      ///
//////////////////////////////////////////////////

template <class Type>
_Col4d<Type>::_Col4d( _Row4d <Type> *v ) {

   m_lpRow4d = v;
}

template <class Type>
_Col4d<Type>::~_Col4d (  ) {

}

template <class Type>
Type & _Col4d<Type>::operator [] ( int v ) {

   if( v >= m_lpRow4d->m_lpLayer->m_lpCArray4d->m_col || v < 0) {
       CException <Type> col4d( this, COLUMN_LIMIT_EXCEED );
       col4d.exceptionmessage();
   }
   return m_lpRow4d->m_lpLayer->m_lpCArray4d->location(
          m_lpRow4d->m_lpLayer->m_lpCArray4d->m_elem, 
          m_lpRow4d->m_lpLayer->m_layerIndex,
          m_lpRow4d->m_rowIndex, v);
} 

//////////////////////////////////////////////////
///            class _Space <Type>             ///
///     Member functions of _Space <Type>      ///
//////////////////////////////////////////////////

 template <class Type>
_Space<Type>::_Space( CArray5d <Type> *v) {

   m_lpCArray5d = v;
}

 template <class Type>
_Space<Type>:: ~_Space( ) {

}

 template <class Type>
_Lay5d<Type> _Space<Type>::operator [] ( int n ) {

   if( n >= m_lpCArray5d->m_jspace || n < 0 ) {
       CException <Type> space( this, J_SPACE_LIMIT_EXCEED );
       space.exceptionmessage();
   }
   m_spaceIndex = n;

   _Lay5d <Type> lay5d( this );

   return lay5d;
}

//////////////////////////////////////////////////
///            class _Lay5d <Type>             ///
///     Member functions of _Lay5d <Type>      ///
//////////////////////////////////////////////////

 template <class Type>
_Lay5d<Type>::_Lay5d( _Space <Type> *v) {

   m_lpSpace = v;
}

 template <class Type>
_Lay5d<Type>::~_Lay5d( ) {

}

 template <class Type>
_Row5d<Type> _Lay5d<Type>::operator [] ( int n ) {

   if( n >= m_lpSpace->m_lpCArray5d->m_layer || n < 0 ) {
       CException <Type> lay5d( this, LAYER_LIMIT_EXCEED );
       lay5d.exceptionmessage();
   }
   m_layerIndex = n;

   _Row5d <Type> row5d( this );

   return row5d;
}

//////////////////////////////////////////////////
///            class _Row5d <Type>             ///
///     Member functions of _Row5d <Type>      ///
//////////////////////////////////////////////////

 template <class Type>
_Row5d<Type>::_Row5d( _Lay5d <Type> *v ) {

   m_lpLayer = v;
}

 template <class Type>
_Row5d<Type>::~_Row5d() {   

}

 template <class Type>
_Col5d<Type> _Row5d<Type>::operator [] ( int n ) {

   if( n >= m_lpLayer->m_lpSpace->m_lpCArray5d->m_row || n < 0 ) {
       CException <Type> row5d( this, ROW_LIMIT_EXCEED );
       row5d.exceptionmessage();
   }
   m_rowIndex = n;

   _Col5d <Type> col5d(this);

   return col5d;
}

//////////////////////////////////////////////////
///            class _Col5d <Type>             ///
///     Member functions of _Col5d <Type>      ///
//////////////////////////////////////////////////

 template <class Type>
_Col5d<Type>::_Col5d( _Row5d <Type> *v ) {

   m_lpRow5d = v;
}

 template <class Type>
_Col5d<Type>::~_Col5d(  ) {

}

template <class Type>
Type& _Col5d<Type>::operator [] ( int v ) {

   if( v >= m_lpRow5d->m_lpLayer->m_lpSpace->m_lpCArray5d->m_col || v < 0 ) {
       CException <Type> col5d( this, COLUMN_LIMIT_EXCEED );
       col5d.exceptionmessage();
   }
   return m_lpRow5d->m_lpLayer->m_lpSpace->m_lpCArray5d->location(
          m_lpRow5d->m_lpLayer->m_lpSpace->m_lpCArray5d->m_elem, 
          m_lpRow5d->m_lpLayer->m_lpSpace->m_spaceIndex,
          m_lpRow5d->m_lpLayer->m_layerIndex,
          m_lpRow5d->m_rowIndex, v);
} 

#endif

/*... End of LCheck.h ...*/