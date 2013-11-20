#include <cstring>
#include "Graphic/RenderTri.h"
#include "Graphic/Interpolator.h"
#include "Graphic/Canvas.h"
#include "Graphic/VertexArray.h"
#include "Graphic/Material.h"
RenderTri::RenderTri( void )
{
}

void RenderTri::SetVertices(const Vertex& v0,const Vertex& v1,const Vertex& v2)
{
    std::memset(m_fragment,0,sizeof(m_fragment));
    SetVertex(v0,0);
    SetVertex(v1,1);
    SetVertex(v2,2);

    m_iP0 = 0;
    m_iP1 = 1;
    m_iP2 = 2;
}

void RenderTri::SetVertex(const Vertex& v,Int32 nIdx)
{
    m_fragment[nIdx].x = Fix16(v.GetPosition().x);
    m_fragment[nIdx].y = Fix16(v.GetPosition().y);
    //m_fragment[nIdx].z = v.GetFixZ();

    Color clr = v.GetColor();
    m_fragment[nIdx].r = Fix16(clr.r);
    m_fragment[nIdx].g = Fix16(clr.g);
    m_fragment[nIdx].b = Fix16(clr.b);

    if(v.HasAttribute(VA_TEXTCOOR))
    {
	const TextCoord &coor = v.GetTextCoord();
        //m_fragment[nIdx].t = v.GetFixT();
        //m_fragment[nIdx].s = v.GetFixS();
    }

    //if(v.HasAttribute(VA_TEXTCOOR1))
    //{
    //    m_fragment[nIdx].t1 = v.GetFixT1();
    //    m_fragment[nIdx].s1 = v.GetFixS1();
    //}
}

bool RenderTri::Sort( void )
{
    if(VertexLessThan(m_iP1,m_iP0))
    {
	Swap(m_iP0,m_iP1);
    }

    if(VertexLessThan(m_iP2,m_iP0))
    {
	Swap(m_iP1,m_iP2);
	Swap(m_iP0,m_iP1);
    }
    else if(VertexLessThan(m_iP2,m_iP1))
    {
	Swap(m_iP1,m_iP2);
    }

    if(m_fragment[m_iP0].y == m_fragment[m_iP2].y)
    {
	return false;
    }

    return true;
}

void RenderTri::Render(Canvas& canvas)
{
    if(!Sort())
    {
	return;
    }

    Point2D p0(m_fragment[m_iP0].GetX(),m_fragment[m_iP0].GetY());
    Point2D p1(m_fragment[m_iP1].GetX(),m_fragment[m_iP1].GetY());
    Point2D p2(m_fragment[m_iP2].GetX(),m_fragment[m_iP2].GetY());

    //compute interplators
    m_interpolator[P02P2].SetScreenVertex(p0.y,p2.y
	    ,m_fragment[m_iP0],m_fragment[m_iP2]);

    if(m_fragment[m_iP0].y < m_fragment[m_iP1].y)
    {
	m_interpolator[P02P1].SetScreenVertex(p0.y,p1.y
		,m_fragment[m_iP0],m_fragment[m_iP1]);
    }

    if(m_fragment[m_iP1].y < m_fragment[m_iP2].y)
    {
	m_interpolator[P12P2].SetScreenVertex(p1.y,p2.y
	    ,m_fragment[m_iP1],m_fragment[m_iP2]);
    }

    //deternimate the start/end interplator
    bool bAntiClockwise = Point2D::IsAntiClockwise(p0,p1,p2);
    int startIt = P02P1,endIt = P02P2;
    if(bAntiClockwise)
    {
        startIt = P02P2,endIt = P02P1;
    }

    //render loop
    for(int y =  p0.y + 1; y <= p1.y; ++y)
    {
	RenderLine(canvas,m_interpolator[startIt].Next(),m_interpolator[endIt].Next(),y);
    }

    if(bAntiClockwise)
    {
        startIt = P02P2, endIt = P12P2;
    }
    else
    {
        startIt = P12P2, endIt = P02P2;
    }
    for(int y = p1.y + 1; y <= p2.y; ++y)
    {
	RenderLine(canvas,m_interpolator[startIt].Next(),m_interpolator[endIt].Next(),y);
    }
}

void RenderTri::RenderLine(Canvas& canvas,const ScreenVertex& start,const ScreenVertex& end,int nY)
{
    if( (SM_PURE == m_shaderMode) || (SM_FLAT == m_shaderMode) )
    {
        canvas.DrawHLine(start.GetX(),end.GetX(),nY,start.GetColor());	
    }
    else
    {
	Int32 nStartX = start.GetX();
	Int32 nEndX = end.GetX();
	if(!canvas.PrepareDraw(nStartX,nY,r_pTexture))
	{
	    return;
	}

        if(nStartX == nEndX)
        {
            canvas.DrawPixel(nStartX,nY,start,r_pTexture);
        }
        else
        {
            m_lineInter.SetScreenVertex(nStartX,nEndX,start,end);
            for(int x = nStartX; x < nEndX; ++x)
            {
                canvas.DrawPixel(x,nY,m_lineInter.Next(),r_pTexture);
            }
        }
    }
}

