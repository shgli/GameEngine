#ifndef _ALGORITHM_H
#define _ALGORITHM_H
#include "Common/Common.h"
#define PI_DIV_4  (0.78539816339745)
#define PI_DIV_2  (1.570796326794897)
#define PI3_DIV_4 (2.356194490192345)
#define PI        (3.141592653589793)
#define PI5_DIV_4 (3.926990816987241) 
#define PI3_DIV_2 (4.71238898038469)
#define PI7_DIV_4 (5.497787143782138)
#define PI2       (6.283185307179586)
#define PI_RECIPROCAL (0.318309886)

Real Sqrt(Real v);

Real InvSqrt(Real v);

Real Fabs(Real v);

Real Cos(Real  v);

Real Sin(Real v);

Real Tan(Real x);

Real Cot(Real x);

Real ACos(Real thetha);

Real ASin(Real thetha);

Real ATan(Real thetha);

//Real Acos(Real v);

Int32 Round(Real v);

inline void RoundToInt64 (int &val, double dval)
{
}

Real Pow(Real e,Int32 nPow);

Int32 RandRange(Int32 a,Int32 b);

template<typename T>
inline T Abs(T v) { return v < 0 ? -v : v; }

#endif

