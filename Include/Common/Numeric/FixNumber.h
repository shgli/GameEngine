#ifndef _FIXNUMBER_H
#define _FIXNUMBER_H
#include <boost/operators.hpp>
#include "Common/Numeric/CIntypes.h"

template<Int32 Shift>
class FixNumber
    :public boost::arithmetic<FixNumber<Shift>
    ,boost::totally_ordered<FixNumber<Shift> > >
{
    static const Double ConvertDelta;
    Int32 value;
    template<Int32 Shift1> friend class FixNumber;
public:
    FixNumber(Int32 n = 0)
	:value(n << Shift)
    {}

    FixNumber(Double& d)
        :value(Double2Fix(d))
    {
    }

    inline bool operator == (const FixNumber& o) const
    {
        return value == o.value;
    }

    inline bool operator < (const FixNumber& o) const
    {
        return value < o.value;
    }

    inline FixNumber& operator+= (const FixNumber& o)
    {
        value += o.value;
        return *this;
    }

    inline FixNumber& operator-= (const FixNumber& o)
    {
        value -= o.value;
        return *this;
    }

    inline FixNumber& operator*= (Int32 f)
    {
        value *= f;
        return *this;
    }

    template<Int32 Shift1>
    inline FixNumber& operator*= (const FixNumber<Shift1>& o)
    {
        Int64 mult = ((Int64)value) * o.value;
        value = mult >> Shift1;
        return *this;
    }

    inline FixNumber& operator/= (const FixNumber& o)
    {
        Int64 div = ((Int64)value) << Shift;
        value = div / o.value;
        return *this;
    }

    inline FixNumber& operator /= (Int32 f)
    {
	value /= f;
	return *this;
    }

    inline Int32 Div2Int(const FixNumber o,Int32 nScale) const
    {
	Int64 div = value;
	return Int32((div * nScale)/ o.value);
    }

    template<Int32 Shift1>
    inline Int32 Div2Int(const FixNumber<Shift1> o,Int32 nScale) const
    {
        Int64 div = (((Int64)value) * nScale) << (Shift1 - Shift);
	return Int32(div / o.value);
    }

    inline Int32 ToInt() const { return (value >> Shift); }

    inline static Int32 Double2Fix(Double& d)
    {
        d += ConvertDelta;
        return *(const Int32*)&d;
    }

    static const FixNumber Unit;
};

typedef FixNumber<28>  Fix28;
typedef FixNumber<24>  Fix24;
typedef FixNumber<16>  Fix16;

template<Int32 Shift>
const Double FixNumber<Shift>::ConvertDelta = 6291456.0 * (1 << (30 - Shift)); //1.5 * (1 << (52 - Shift) );

template<Int32 Shift>
const FixNumber<Shift> FixNumber<Shift>::Unit(1);


#endif
 
