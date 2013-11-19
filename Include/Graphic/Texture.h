#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "Common/Common.h"
#include "Graphic/Bitmap.h"

struct TextureCoord
    :boost::additive1<TextureCoord
    ,boost::multipliable<TextureCoord,Double> >
{
    Double t,s;
public:
    TextureCoord(Double tt,Double ss)
	:t(tt),s(ss)
    {}

    TextureCoord& operator *= (Double f)
    {
	t *= f;
	s *= f;
	return *this;
    }

    TextureCoord& operator -= (const TextureCoord& o)
    {
	t -= o.t;
	s -= o.s;
	return *this;
    }

    TextureCoord& operator += (const TextureCoord& o)
    {
	t += o.t;
	s += o.s;
	return *this;
    }
};

class Texture
{
public:
    Texture(const std::string& strPath);
    ~Texture( void );

    Int32 GetWidth( void ) const { return m_pBitmap->GetWidth(); }
    Int32 GetHeight( void ) const { return m_pBitmap->GetHeight(); }
    Color GetSample(Int32 nT,Int32 nS);
private:
    Bitmap *m_pBitmap;
    UInt16 m_nShift;
};

typedef Fix28 TextFix;
#endif

