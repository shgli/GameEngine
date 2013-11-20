#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "Common/Common.h"
#include "Graphic/Bitmap.h"
typedef Int32 TextureId;
typedef Fix28 TextFix;
typedef Int32 TextureMode;

struct TextCoord
    :boost::additive1<TextCoord
    ,boost::multipliable<TextCoord,Double> >
{
    Double t,s;
public:
    TextCoord(Double tt,Double ss)
	:t(tt),s(ss)
    {}

    TextCoord& operator *= (Double f)
    {
	t *= f;
	s *= f;
	return *this;
    }

    TextCoord& operator -= (const TextCoord& o)
    {
	t -= o.t;
	s -= o.s;
	return *this;
    }

    TextCoord& operator += (const TextCoord& o)
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

class TextureMgr
{
public:
    static TextureMgr& Instance( void );

    Texture* GetTexture(TextureId textId);
private:
    TextureMgr(const TextureMgr&) = delete;
    TextureMgr( void ) = default;
};

#endif

