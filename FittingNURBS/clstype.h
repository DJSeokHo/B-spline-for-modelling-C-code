/*
    Class types & Enumerations

    '98. 9. 27

     written by Hwang, Ui Sang
*/

#ifndef __cplusplus
#error Must use C++ for template classes
#endif

#ifndef __TEMPLATECLASSTYPE_H__
#define __TEMPLATECLASSTYPE_H__

template <class Type> class  CVector ;
template <class Type> class  CArray2d;
template <class Type> class  CArray3d;
template <class Type> class  CArray4d;
template <class Type> class  CArray5d;

template <class Type> class _Col2d;
template <class Type> class _Row3d;
template <class Type> class _Col3d;
template <class Type> class _Layer;
template <class Type> class _Row4d;
template <class Type> class _Col4d;
template <class Type> class _Space;
template <class Type> class _Lay5d;
template <class Type> class _Row5d;
template <class Type> class _Col5d;


typedef 			  enum	  {
    INSUFFICIENT_MEMORY 	       =	  0x0001,  // [ 0  ]
   I_SPACE_LIMIT_EXCEED 	       =	  0x0002,  // [ 1  ]
   J_SPACE_LIMIT_EXCEED 	       =	  0x0003,  // [ 2  ]
     SPACE_LIMIT_EXCEED 	       =	  0x0004,  // [ 3  ]
     LAYER_LIMIT_EXCEED 	       =	  0x0005,  // [ 4  ]
       ROW_LIMIT_EXCEED 	       =	  0x0006,  // [ 5  ]
    COLUMN_LIMIT_EXCEED 	       =	  0x0007,  // [ 6  ]

   CARRAY2D_CVECTOR_MULTIPLICATION  =	  0x0008,  // [ 7  ]
   CVECTOR_CARRAY2D_MULTIPLICATION  =	  0x0009,  // [ 8  ]
   CVECTOR_CVECTOR_MULTIPLICATION   =	  0x000A,  // [ 9  ]
   CVECTOR_CVECTOR_ADDITION	        =     0x000B,  // [ 10 ]
   CVECTOR_CVECTOR_SUBTRACTION	    =	  0x000C,  // [ 11 ]

   CVECTOR_CVECTOR_ASSIGNMENT	    =	  0x000D,  // [ 12 ]
   CARRAY2D_CARRAY2D_ASSIGNMENT     =	  0x000E,  // [ 13 ]
   CARRAY3D_CARRAY3D_ASSIGNMENT     =	  0x000F,  // [ 14 ]
   CARRAY4D_CARRAY4D_ASSIGNMENT     =	  0x0010,  // [ 15 ]
   CARRAY5D_CARRAY5D_ASSIGNMENT     =	  0x0011,  // [ 16 ]
   NO_ASSIGNED_MEMORY               =     0x0012,  // [ 17 ]
   VECTOR_LIMIT_EXCEED              =     0x0013 
                               }  exceptiontype_t;

typedef 			  enum	  {
    TEMPLATE_CLASS_CVECTOR_TYPE     =	  0x1000,
    TEMPLATE_CLASS_CARRAY2D_TYPE    =	  0x1001,
    TEMPLATE_CLASS_CARRAY3D_TYPE    =	  0x1002,
    TEMPLATE_CLASS_CARRAY4D_TYPE    =	  0x1003,
    TEMPLATE_CLASS_CARRAY5D_TYPE    =	  0x1004,

    TEMPLATE_CLASS_COL2D_TYPE	    =	  0x1005,
    TEMPLATE_CLASS_ROW3D_TYPE	    =	  0x1006,
    TEMPLATE_CLASS_COL3D_TYPE	    =	  0x1007,
    TEMPLATE_CLASS_LAYER_TYPE	    =	  0x1008,
    TEMPLATE_CLASS_ROW4D_TYPE	    =	  0x1009,
    TEMPLATE_CLASS_COL4D_TYPE	    =	  0x100A,
    TEMPLATE_CLASS_SPACE_TYPE	    =	  0x100B,
    TEMPLATE_CLASS_LAY5D_TYPE	    =	  0x100C,
    TEMPLATE_CLASS_ROW5D_TYPE	    =	  0x100D,
    TEMPLATE_CLASS_COL5D_TYPE	    =	  0x100E
                                    } classtype_t;

#endif

/* ... End of clstype.h ...*/
