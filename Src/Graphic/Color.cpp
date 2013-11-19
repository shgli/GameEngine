#include <string.h>
#include "Graphic/Color.h"
#include "Graphic/Material.h"
const Color Color::Red = Color(1.0,0.0,0.0);
const Color Color::Green = Color(0.0,1.0,0.0);
const Color Color::Blue = Color(0.0,0.0,1.0);
const Color Color::Black = Color(0.0,0.0,0.0);
const Color Color::White = Color(1.0,1.0,1.0);


Color::Color(double red,double green,double blue,double alpha)
    :r(red * 255),g(green * 255),b(blue * 255),a(alpha * 255)
{}

Color::Color(int red,int green,int blue,int alpha)
    :r(red)
    ,g(green)
    ,b(blue)
    ,a(alpha)
{}

Color::Color(IntColor clr)
{
    AsInt32() = clr;
}

Color& Color::operator ^= (Color o)
{
    AsInt32() ^= o.AsInt32();
    return *this;
}

Color& Color::operator |= (Color o)
{
    AsInt32() |= o.AsInt32();
    return *this;
}

Color& Color::operator &= (Color o)
{
    AsInt32() &= o.AsInt32();
    return *this;
}

Color& Color::operator += (Color o)
{
    r += o.r;
    g += o.g;
    b += o.b; 
    return *this;
}

Color& Color::operator -= (Color o)
{
    r -= o.r;
    g -= o.g;
    b -= o.b; 
    return *this;
}

Color& Color::operator *= (Real f)
{
    r *= f;
    g *= f;
    b *= f; 
    return *this;

}

Color& Color::operator /= (Real f)
{
    r /= f;
    g /= f;
    b /= f; 
    return *this;
}

Color& Color::operator *= (MaterialValue& mater)
{
    r /= mater.m_red;
    g /= mater.m_green;
    b /= mater.m_blue; 
    return *this;

}

Color& Color::operator *= (Color o)
{
    r = (r * o.r) / 256;
    g = (g * o.g) / 256;
    b = (b * o.b) / 256;
    return *this;
}


