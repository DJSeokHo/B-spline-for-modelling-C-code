/*

  PROPLIBD.H

  1999. 6. 10

  revised by H.U.S

  Proplibd.h was developed from proplib.h (C-Version).
  
*/

#ifndef __PROPLIBDOUBLE_H__
#define __PROPLIBDOUBLE_H__

#ifndef __DMEMCLS_H__
#include "dmemcls.h"
#endif

extern void  drivdk(
                           int                         nin,
                           int                        nout,
                           CVector   < double >   &    Xin, 
                           CVector   < double >   &   Xout, 
                           CVector   < double >   &   dydx,
                           CVector   < double >   &  d2ydx,
                           CVector   < double >   &      A  
                    ); 
                                                                    

extern void  evaldk (
                           int                        nin,
                           int                       nout,
                           CVector   < double >   &   Xin,
                           CVector   < double >   &  Xout, 
                           CVector   < double >   &  Yout,
                           CVector   < double >   &     A
                    );

                       
extern double fillin (
                           double                      x,
                           CVector   < double >   &   ab,
                           CVector   < double >   &  ord,
                           int                        no 
                     );
                       
 
extern void  intedk  (
                           int                         nin, 
                           CVector   < double >   &   Xout,
                           double                       x1,
                           double                       xu, 
                           double                 &    ydx,
                           double                 &   xydx, 
                           double                 &  xxydx,
                           CVector   < double >   &      A
                     );
                    
extern void  uglydk  (
                           int                       nin,
                           int                       ncl,
                           int                       ncr,
                           CVector   < double >   &  Xin, 
                           CVector   < double >   &  Yin,
                           double                    esl,
                           double                    esr,
                           CVector   < double >   &   Ae
                     );
                        
extern void  simq    (
                           CVector   < double >   &   A,
                           CVector   < double >   &   B,
                           int                        n,
                           int                    &  ks
                     );
                      
extern void  iterlu ( 
                           CArray2d  < double >   &      a,
                           CArray2d  < double >   &   alud,
                           int                           n, 
                           CVector   <   int  >   &   indx,
                           CVector   < double >   &      b, 
                           CVector   < double >   &      x,
                           int                       itmax,
                           double                     tolx
                    );
                                                 
extern void  linsol (
                           CArray2d  < double >   &       a, 
                           CArray2d  < double >   &    alud,
                           int                            n, 
                           CVector   <   int  >   &    indx,
                           CVector   < double >   &       b,
	                          CVector   < double >   &       x,
                           int                         kase,
                           int                       inital,
                           int                        itmax,
                           double                      tolx
                    );
                                                          
extern void  lubksb (
                          CArray2d   < double >   &  alud,
                          int                           n,
                          CVector    <   int  >   &  indx, 
                          CVector    < double >   &     b
                    );
                   
extern void  ludcmp (
                          CArray2d   < double >   &     a,
                          CArray2d   < double >   &  alud,
                          int                           n,
                          CVector    <  int   >   &  indx, 
                          double                  &     d
                    );
                                                                               
extern void  vorseg (
                          double                     xp,
                          double                     yp,
                          double                     zp,
                          double                     x1,
                          double                     y1, 
                          double                     z1, 
                          double                     x2, 
                          double                     y2, 
                          double                     z2, 
                          double                  &  vx, 
                          double                  &  vy,
                          double                  &  fz, 
                          double                  &  sx, 
                          double                  &  sy, 
                          double                  &  sz, 
                          int                         k
                    );

extern void  prcros (
                      double    a[], 
                      double    b[], 
                      double    c[]
                    );
                  
extern double prdot ( 
                      double     a[],
                      double     b[]
                    );
                   
                        
extern double potder (
                       double    xp,
                       double    xin[],
                       double    yin[]
                     );

/*--Exponential spline--*/

extern void    spl (
                           int                       npt,
                           CVector   < double >  &   Xin, 
                           CVector   < double >  &   Yin, 
                           double                &  slpl,
                           double                &  slpr,
                           double                  relax,
                           int                     itmax, 
                           int                      ispl, 
                           CVector   < double >  &     R, 
                           CVector   < double >  &     P,
                           int                   &  iter
                   );

                                                                        
extern void   espl (       int                       npt,
                           CVector   < double >  &   Xin, 
                           CVector   < double >  &   Yin,
                           int                      ispl,
                           CVector   < double >  &    F2,
                           CVector   < double >  &     P,
                           int                      nout,  
                           CVector   < double >  &  Xout,
                           CVector   < double >  &  Yout
                   );
                   
                                                
extern void   dspl (
                           int                        npt,
                           CVector   < double >   &   Xin, 
                           CVector   < double >   &   Yin,
                           int                       ispl,
                           CVector   < double >   &    F2,
                           CVector   < double >   &     P,
                           int                       nout, 
                           CVector   < double >   &  Xout,
                           CVector   < double >   & Y1out,
                           CVector   < double >   &  Y2out
                   );

extern void intspl ( 
                           int                      npt,
                           CVector   < double >   & Xin, 
                           CVector   < double >   & Yin,
                           int                     ispl, 
                           CVector   < double >   &  F2,
                           CVector   < double >   &   P,
                           double                    xa,
                           double                    xb,
                           double                 & yint
                   );
                                               
extern void tridag (
                           int                       il,
                           int                       iu,
                           CVector   < double >     & A, 
                           CVector   < double >     & B, 
                           CVector   < double >     & C, 
                           CVector   < double >     & R
                   );
                                                       

extern double powi (
                           double                     x,
                           int                        n
                   );


extern double powr (
                           double                     x,
                           double                apower
                   );

extern void nrerror (
                           char            error_text[]
                    );

#endif