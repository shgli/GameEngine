#include "Graphic/Triangle.h"

Triangle& Triangle::operator= (std::initializer_list<std::initializer_list<Int32> >& ids)
{
    assert(ids.size() <= 3);
    Int32 nIdx = 0;
    for(auto itVertexIndex = ids.begin(); itVertexIndex < ids.end(); ++itVertexIndex)
    {
	m_vertices[nIdx++] = *itVertexIndex;
    }
}

void Triangle::CalculateNormal(const VertexArray& buf)
{
    Vector v1 = buf.GetPosition(m_vertices[1].GetPositionIndex()) - buf.GetPosition(m_vertices[0].GetPositionIndex());
    Vector v2 = buf.GetPosition(m_vertices[2].GetPositionIndex()) - buf.GetPosition(m_vertices[0].GetPositionIndex());

    m_normal = v1.Cross(v2);
}

std::ostream& operator<< (std::ostream& os,const Triangle& tri)
{
    SAVE_INDENT(cindent);
    os<<"Triangle "<<&tri<<": "<<std::endl;
    //os<<cindent.Shift(1)<<"Position 0: "<<tri.GetPosition0()<<std::endl;
    //os<<cindent.Shift(0)<<"Position 1: "<<tri.GetPosition1()<<std::endl;
    //os<<cindent.Shift(0)<<"Position 2: "<<tri.GetPosition2()<<std::endl;
    
    return os;
}

