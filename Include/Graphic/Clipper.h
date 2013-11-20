#ifndef _CLIPPER_HPP
#define _CLIPPER_HPP
#include "Common/Common.h"
#include "Graphic/ObjectVisitor.h"

class Vertex;
class Clipper
    :public Step
{
public:
    virtual void Visit(Object& obj);
    void Reset( void ) { m_nCurSize = 1; }
private:
    void AdjustSequence(Vertex*& pp0,Vertex*& pp1,Vertex*& pp2
	,VertexIndex*& i0,VertexIndex*& i1,VertexIndex*& i2,Int32 nFirstIdx);

    Int32 DeterminateStatus(Vertex& v);
    VertexIndex IntersectAndInterpolateAttr(Vertex* p0,Vertex* p1,VertexArray& aVertices);

    Int32 m_nCurSize;
};
#endif
 
