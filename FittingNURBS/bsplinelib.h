#include <fstream.h>

extern
int FindSpan
    (
        int               n, 
        int               p,
        double            u,
        CVector <double> &U
    );

extern
void BasisFuns
     (
         int           iSpan, 
         double            u,
         int               p, 
         CVector <double> &U, 
         CVector <double> &N
     );

extern
int ComputeUniformKnotVector
    (
       const    int         n,
       const    int         p,
       CVector <double> &knot
    );

extern
int ComputeKnotVectorWithMultiplicity
    (
        const    int              n, 
        const    int              p, 
        const    int  internalKnots, 
        CVector <int> &multiplicity,
        CVector <double>      &knot
    );

extern
int GenerateUniformKnotVector
    (
       const    int          n, 
       const    int          p,
       CVector <double> &knot
    );

extern
void PolynomialMultiplication
     (
          int               N, 
          CVector <double> &a,
          int               M,
          CVector <double> &b, 
          CVector <double> &c
     );

extern
void PolynomialAddition
     (
                 int      N, 
        CVector <double> &a, 
        CVector <double> &b,
        CVector <double> &c
     );

extern
void PolynomialScaling
     (
        int               N, 
        CVector <double> &a, 
        double       factor,
        CVector <double> &c
     );

extern
void BasisFunPolynomialCoeffs
     (
         int                 iSpan,
         int                     p, 
         CVector  <double>      &U,
         CArray2d <double> &NCoeff,
         int           u_c_given, 
         double              u_c
     );

extern
void CurvePoint
     (
        int                n, 
        int                p, 
        CVector  <double> &U, 
        CArray2d <double> &P, 
        double             u, 
        int          index_u, 
        CArray2d <double> &C
     );

extern
void DersBasisFuns
     (
        int              iSpan,
        double               u,
        int                  p, 
        int                  n, 
        CVector  <double> &  U,
        CArray2d <double> &ders
     );

extern
void CurveDerivs
     (
        int                 n, 
        int                 p,
        CVector  <double>  &U,
        CArray2d <double>  &P,
        double              u, 
        int           index_u, 
        int                 d, 
        CArray3d <double> &CK
     );

extern
void SurfacePoint
     (
         int                n, 
         int                p,
         CVector  <double> &U, 
         int                m, 
         int                q, 
         CVector  <double> &V,
         CArray3d <double> &P, 
         double             u,
         int          index_u, 
         double             v,
         int          index_v,
         CArray3d <double> &S
     );

extern
void SurfacePoint1P
     (
        int                n,
        int                p, 
        CVector  <double> &U, 
        int                m,
        int                q,
        CVector  <double> &V,
        CArray3d <double> &P, 
        double             u,
        double             v,
        //double             S[]
        CVector  <double> & S
     );

extern
void SurfaceDerivs
     (
        int                n,
        int                p, 
        CVector  <double> &U,
        int                m, 
        int                q, 
        CVector  <double> &V,
        CArray3d <double> &P, 
        double             u, 
        double             v, 
        int                d, 
        CArray3d <double> &SKL
     );

extern
void GlobalCurveInterp
     (
        const int          n,
        CArray2d <double> &Q, 
        const int          r,
        const int          p, 
        int               &m, 
        CVector  <double> &U, 
        CArray2d <double> &P
     );

extern
int SurfMeshParams
    (
       const int          n,
       const int          m,
       CArray3d <double> &Q, 
       CVector  <double> &uk, 
       CVector  <double> &vl
    );

extern
void GlobalSurfInterp
     (
        const int          n, 
        const int          m,
        const int          r, //... added arguments
        CArray3d <double> &Q,
        const int          p,
        const int          q,
        CVector  <double> &U,
        CVector  <double> &V,
        CArray3d <double> &P
     );

extern
double Distance3D
       (
          double a[],
          double b[]
       );

extern
void MatrixInverse
     (
        CArray2d <double> &M,
        int mrows,
        CArray2d <double> &MI
     );

extern
void MatrixTranspose
     (
        CArray2d <double> &M, 
        int            mrows, 
        int            mcols,
        CArray2d <double> &T
     );

extern
void MatrixAddition
     (
        int            mrows,
        int            mcols, 
        CArray2d <double> &M,
        CArray2d <double> &N,
        CArray2d <double> &W
     );

extern
void MatrixSubstraction
    (
        int            mrows,
        int            mcols,
        CArray2d <double> &M, 
        CArray2d <double> &N, 
        CArray2d <double> &W
    );

extern
int MatrixMultiplication
    (
       CArray2d <double> &M, 
       int            mrows,
       int            mcols,
       CArray2d <double> &N, 
       int            nrows, 
       int            ncols,
       CArray2d <double> &W
    );

void SpDoubleCosine
     (
        int         nPoints, 
        CVector <double> &s
     );

extern
void SpCosine
     (
        int         nPoints, 
        CVector <double> &s
     );

extern
void SpUniform
     (
        int         nPoints,
        double         uMax,
        CVector <double> &u
     );

extern
void CurveKnotIns
     (
        int               np, 
        int                p,
        CVector <double> &UP,
        CVector <double> &Pw, 
        double             u, 
        int                k, 
        int                s, 
        int                r, 
        int              &nq,
        CVector <double> &UQ,
        CVector <double> &Qw
     );

extern
void RatCurveDerivs
     (
        int                 n, 
        int                 p, 
        CVector  <double>  &U,
        CArray2d <double> &Pw, 
        int    nMaxDerivative, 
        CVector  <double>  &u,
        int           index_u,
        CArray3d <double> &CK
     );

extern
void DersOneBasisFun
     (
        int                  p,
        int                  m,
        CVector <double>    &U, 
        int                  i,
        double               u, 
        int                  n,
        CVector <double> &ders
     );

extern
void RatCurvePoint
     (
        int                 n, 
        int                 p,
        CVector  <double>  &U,
        CArray2d <double> &Pw,
        CVector  <double>  &u, 
        int           index_u,
        CArray2d <double>  &C
     );

extern
void  ComputeKnotVectorUsingCosine
      (
         const int         p,
         const int         n,
         CVector <double> &U
      );

extern
void  ComputeKnotVectorUsingDoubleCosine
      (
         const int         p, 
         const int         n,
         CVector <double> &U
      );

extern
void ComputeKnotVectorUsingEq_9_69
     (
        const int          r,
        const int          p, 
        const int          n, 
        CVector <double> &ub,
        CVector <double>  &U
     );

extern
void GlobalSurfApproxFixednm
     (
        const int          r,
        const int          s,
        CArray3d <double> &Q, 
        const int          p,
        const int          q,
        const int          n,
        const int          m,
        CVector  <double> &U, 
        CVector  <double> &V, 
        CArray3d <double> &P
     );

extern
void GlobalSurfApproxFixednm
     (
       const     int	     r,
       const     int	     s,
       CArray3d <double> & Q,
       const     int	     p,
       const     int	     q,
       const     int	     n,
       const     int	     m,
       CVector  <double> & U,
       CVector  <double> & V,
       CArray3d <double> & P,
       const     int       nDimenOff
     );

extern
int WCLeastSquaresCurve
    (
       CArray2d <double>  &Q,
       int                 r, 
       CVector  <double> &Wq,
       CArray2d <double>  &D,
       int                 s,
       CVector  <int>     &I, 
       CVector  <double> &Wd, 
       int                 n,
       int                 p,
       CVector  <double>  &U, 
       CArray2d <double>  &P, 
       int            spacing, 
       int chordwiseparameter,
       double  exponent
    );

extern
int B4FitForFoilCWForCamber
    (
       CArray2d <double>  &Q,
       int                 r,
       CVector  <double> &Wq,
       CArray2d <double>  &D,
       int                 s, 
       CVector  <int>     &I,
       CVector  <double> &Wd, 
       int                 n,
       int                 p,
       CVector  <double>  &U,
       CArray2d <double>  &P,
       CVector  <double> &ub
    );

extern
int B4FitForFoilCW
    (
       CArray2d <double>  &Q,
       int                 r, 
       CVector  <double> &Wq,
       CArray2d <double>  &D, 
       int                 s,
       CVector  <int>     &I,
       CVector  <double> &Wd, 
       int                 n,
       int                 p,
       CVector  <double>  &U, 
       CArray2d <double>  &P,
       CVector  <double> &ub, 
       int dimen
    );

extern
int LookForLELocation
    (
      int                 nGCVerticesM1,
      int                 nDegree,
      CVector  <double> & uKnot,
      CArray2d <double> & xGCVertex,
      double            & xLE,
      double            & uLE,
      double            & chordLETE
    );

extern
void CurvePoint1P
     (
       int                 n,
       int                 p,
       CVector  <double> & U,
       CArray2d <double> & P,
       double              u,
       CVector  <double> & S,
       int                 nDimenOff = 3
     );
