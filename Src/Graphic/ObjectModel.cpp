#include "Graphic/ObjectModel.h"
#include "Graphic/VertexBuffer.h"
#include "Graphic/IndexBuffer.h"
ObjectModel::ObjectModel(VertexBuffer* vertexBuf,PrimitiveType pt)
    :m_vertexBuf(vertexBuf)
     ,m_ePrimType(pt)
     ,m_pTexture(nullptr)
{
    CalculateBound();
}

void ObjectModel::TransformVertices(VertexBuffer& outVertexBuf,const Matrix& m) const
{
    m_vertexBuf->Copy2(outVertexBuf);
    for(int i = 0; i < m_vertexBuf->GetSize(); ++i)
    {
	outVertexBuf.GetPosition(i) = m * m_vertexBuf->GetPosition(i);
    }
}

void ObjectModel::AddTriangle(Triangle* tri)
{
    m_vTriangles.push_back(tri);
}

void ObjectModel::CalculateBound( void )
{
    if(0 == m_vertexBuf->GetSize())
    {
	m_bound = Sphere();
    }

    Vector sum = Vector::Zero;
    for(int i = 0; i < m_vertexBuf->GetSize(); ++i)
    {
	sum += m_vertexBuf->GetPosition(i);
    }

    m_bound.center = sum / m_vertexBuf->GetSize();

    m_bound.radius = 0.0;
    for(int i = 0; i < m_vertexBuf->GetSize(); ++i)
    {
	Vector diff = m_vertexBuf->GetPosition(i) - m_bound.center;
	Real tmp = diff.NormSqure();
	if(tmp > m_bound.radius)
	{
	    m_bound.radius = tmp;
	}
    }

    m_bound.radius = Sqrt(m_bound.radius);
}

//Int32 ObjectModel::GetTriangleCount( void ) const
//{
//    switch(m_ePrimType)
//    {
//	case PT_TRIANGLES:
//	    return m_indexBuf->GetSize() / 3;
//	case PT_TRIANGLE_STRIP:
//	    return m_indexBuf->GetSize() - 2;
//	case PT_TRIANGLE_FAN:
//	   return m_indexBuf->GetSize() - 2; 
//        default:
//	   assert(false);
//	   return 0;
//    }
//}

void ObjectModel::GetTriangleIndex(Int32 nIdx,Int32& p1,Int32& p2,Int32& p3) const
{
    IndexBuffer& buf = *m_indexBuf;
    switch(m_ePrimType)
    {
	case PT_TRIANGLES:
	    {
		Int32 nRIndex = 3 * nIdx;
		p1 = buf[nRIndex];
		p2 = buf[nRIndex + 1];
		p3 = buf[nRIndex + 2];
	    }
	    break;
	case PT_TRIANGLE_STRIP:
	    {
		if(0 == (nIdx % 2))
		{
		    p1 = buf[nIdx];
		    p2 = buf[nIdx + 1];
		}
		else
		{
		    p2 = buf[nIdx];
		    p1 = buf[nIdx + 1];
		}
		p3 = buf[nIdx + 2];
	    }
	    break;
	case PT_TRIANGLE_FAN:
	    {
		p1 = 0;
		p2 = nIdx + 1;
		p3 = nIdx + 2;
	    }
	    break;
    }
}

