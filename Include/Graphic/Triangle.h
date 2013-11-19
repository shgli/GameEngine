#ifndef _TRIANGLE_H
#define _TRIANGLE_H
#include "Graphic/IndexBuffer.h"
#include "Graphic/VertexBuffer.h"
#include "Graphic/Color.h"
#include "Math/Math.h"
class IndexBuffer;
class VertexBuffer;

//===========attribute=============//
enum FaceType
{
    FT_SINGLE = 0x0001,
    FT_2SIDE  = 0x0002,
    FT_MASK   = 0x0007
};

enum ColorMode
{
    COLOR_RGB = 0x0010,
    COLOR_INDEX = 0x0020,
    COLOR_MASK = 0x0070
};

//=============state=================//
enum FaceState
{
    FS_BACKFACE  = 0x0001,
    FS_FRONTFACE = 0x0002,
    FS_2SIDE     = 0x0004,
    FS_MASK      = 0x0007
};

enum TriState
{
    TS_CULLED  = 0x0010,
    TS_CLIPPED = 0x0020,
    TS_MASK    = 0x0070
};

class Triangle
{
    UInt32 m_attribute;
    UInt32 m_state;

    Int32 m_idxP0,m_idxP1,m_idxP2;
    Color m_clr;
    Vector m_normal;

public:
    Triangle(Int32 i0 = 0,Int32 i1 = 1,Int32 i2 = 2,UInt32 nAttr = FT_SINGLE | COLOR_RGB)
        :m_attribute(nAttr)
        ,m_state(0)
	,m_idxP0(i0),m_idxP1(i1),m_idxP2(i2)
    {}

    void CalculateNormal(const VertexBuffer& buf);
    inline Vector& GetNormal( void ) { return m_normal; }
    inline const Vector& GetNormal( void )const { return m_normal; }

    inline const Color& GetColor( void )const { return m_clr; }
    inline Color& GetColor( void ) { return m_clr; }
    inline void SetColor(const Color& clr) { m_clr = clr; }

    inline Int32 GetIndexOfP0( void ) const { return m_idxP0; }
    inline Int32 GetIndexOfP1( void ) const { return m_idxP1; }
    inline Int32 GetIndexOfP2( void ) const { return m_idxP2; }

    inline void AddState(UInt32 state) { m_state |= state; }
    inline void RemoveState(UInt32 state) { (m_state & ~state); }
    inline bool HasState(UInt32 state) const { return (m_state & state); }
    inline bool IsVisible( void ) const { return !HasState(TS_CULLED) && !HasState(TS_CLIPPED);}

    inline void AddAttribute(UInt32 attr) { m_attribute |= attr; }
    inline void RemoveAttribute(UInt32 attr) { m_attribute &= ~attr; }
    inline bool HasAttribute(UInt32 attr) const { return (m_attribute & attr); }

    friend std::ostream& operator<< (std::ostream& os,const Triangle& tri);
};

#endif

