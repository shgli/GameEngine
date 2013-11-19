#ifndef _CLIPPER_HPP
#define _CLIPPER_HPP
#include "Common/Common.h"
#include "Graphic/ObjectVisitor.h"

class Vertex;
class Clipper
    :public Pass
{
public:
    virtual void Visit(Object& obj);
    void Reset( void ) { m_nCurSize = 1; }
private:
    void AdjustSequence(Vertex*& pp0,Vertex*& pp1,Vertex*& pp2,Int32& i0,Int32& i1,Int32& i2,Int32 nFirstIdx);
    Int32 DeterminateStatus(Vertex& v);
    Int32 IntersectAndInterpolateAttr(Vertex* p1,Vertex* p2);

    Int32 m_nCurSize;
};
#endif
 
