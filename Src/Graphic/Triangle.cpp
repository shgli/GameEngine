#include "Graphic/Triangle.h"

void Triangle::CalculateNormal(const VertexBuffer& buf)
{
    Vector v1 = buf.GetPosition(m_idxP1) - buf.GetPosition(m_idxP0);
    Vector v2 = buf.GetPosition(m_idxP2) - buf.GetPosition(m_idxP0);

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

