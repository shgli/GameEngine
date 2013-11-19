#ifndef _COLOR_H_
#define _COLOR_H_
#include "Common/Common.h"
#include "Graphic/Material.h"
#include <boost/operators.hpp>
typedef UInt32 IntColor;
#define MAKE_INT_COLOR(r,g,b,a)  ((r<<24) + (g << 16) + (b << 8) + a)
#define GET_RED(clr) ((clr & 0xff000000) >> 24)
#define GET_GREEN(clr) ((clr & 0x00ff0000) >> 16)
#define GET_BLUE(clr) ((clr & 0x0000ff00) >> 8)
#define GET_ALPHA(clr) (clr & 0x000000ff)

static const IntColor BLACK_COLOR = MAKE_INT_COLOR(0,0,0,255);
static const IntColor RED_COLOR = MAKE_INT_COLOR(255,0,0,255);
static const IntColor GREEN_COLOR = MAKE_INT_COLOR(0,255,0,255);
static const IntColor BLUE_COLOR = MAKE_INT_COLOR(0,0,255,255);

struct Color
    :boost::additive<Color
    ,boost::multiplicative<Color,Real>
    ,boost::multipliable<Color,MaterialValue> >
{
    UInt8 r,g,b,a;

    Color(double red,double green,double blue,double alpha = 1.0);
    Color(int red,int green,int blue,int alpha = 255);
    Color(IntColor clr = 0);

    Color& operator ^= (Color o);
    Color& operator |= (Color o);
    Color& operator &= (Color o);

    UInt32& AsInt32( void ) 
    { 
        return INVOKE_CONSTFUNC(AsInt32());
    }

    const UInt32& AsInt32( void )const 
    { 
	return *(UInt32*)this;
    }

    Color& operator += (Color o);
    Color& operator -= (Color o);
    Color& operator *= (Color o);
    Color& operator *= (Real f);
    Color& operator /= (Real f);

    Color& operator *= (MaterialValue& mater);
public:
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Black;
    static const Color White;
};

struct ColorEx
{
    UInt32 r,g,b;
    ColorEx(Color clr)
	:r(clr.r)
	,g(clr.g)
	,b(clr.b)
    {}
};
#endif

