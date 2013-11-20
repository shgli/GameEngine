#ifndef _GRAPHICTYPES_H
#define _GRAPHICTYPES_H
#include "Common/Common.h"
#include "Graphic/Color.h"
#include "Graphic/Texture.h"
static const int INVALID_VALUE = -1024;
struct Point2D
{
    Int32 x,y;

    Point2D(Int32 xx = INVALID_VALUE,Int32 yy = INVALID_VALUE)
	:x(xx),y(yy)
    {}

    static bool IsAntiClockwise(const Point2D& p0,const Point2D& p1,const  Point2D& p2)
    {
        return ((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y)) > 0;
    }
};

struct Rect2D
{
    Int32 x,y,dx,dy; 
    Rect2D(int xx = INVALID_VALUE,int yy = INVALID_VALUE,int dxx = INVALID_VALUE,int dyy = INVALID_VALUE)
	:x(xx),y(yy),dx(dxx),dy(dyy)
    {}

    bool Test(int xx,int yy)
    {
	return xx >=x && xx < (x + dx) && yy >= y && yy < (y + dy);
    }

    bool Test(const Point2D& pt)
    {
	return Test(pt.x,pt.y);
    }
};

#ifdef _USE_BRESHAM_
struct ScreenVertex
{
    Int32 x,y;
    Fix28 z;
    Color clr;
    Fix16 t,s;
    Fix16 t1,s1;

    ScreenVertex()
	:x(0),y(0),z(0)
    {
    }
};
#else
struct ScreenVertex
{
    Fix16 x,y;
    Fix28 z;
    Fix16 r,g,b;
    TextFix t,s;

    inline Int32 GetX( void ) const { return x.ToInt(); }
    inline Int32 GetY( void ) const { return y.ToInt(); }
    inline Color GetColor( void ) const { return Color(r.ToInt(),g.ToInt(),b.ToInt());}
    inline Int32 GetT( void ) const { return t.ToInt(); }
    inline Int32 GetS( void ) const { return s.ToInt(); }

    inline ScreenVertex& operator+= (const ScreenVertex& o)
    {
	x += o.x;
	z += o.z;
	t += o.t;
	s += o.s;
	r += o.r;
	g += o.g;
	b += o.b;

	return *this;
    }

    inline ScreenVertex& operator-= (const ScreenVertex& o)
    {
	x -= o.x;
	z -= o.z;
	t -= o.t;
	s -= o.s;
	r -= o.r;
	g -= o.g;
	b -= o.b;

	return *this;
    }

    inline ScreenVertex& operator/= (Int32 f)
    {
	x /= f;
	z /= f;
	t /= f;
	s /= f;
	r /= f;
	g /= f;
	b /= f;
	return *this;
    }
};
#endif

static const UInt32 MAX_VERTEX_PEROBJECT = 1024;

class Texture;
class VertexArray;
class Triangle;
struct RenderItem
{
    Texture* m_pTexture;
    VertexArray* m_pBuffer;
    std::vector<Triangle*>* m_vTriangles;

    RenderItem(Texture* pText,VertexArray* buf,std::vector<Triangle*> *vTriangles)
	:m_pTexture(pText)
	,m_pBuffer(buf)
	,m_vTriangles(vTriangles)
    {}
};

typedef std::vector<RenderItem> RenderList;

#endif

 
