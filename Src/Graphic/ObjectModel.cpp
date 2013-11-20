#include "Common/Common.h"
#include "Graphic/ObjectModel.h"
#include "Graphic/VertexArray.h"
#include "Graphic/IndexBuffer.h"
#include "Graphic/Triangle.h"
ObjectModel::ObjectModel(VertexArray&& aVertices,Array<Triangle>&& aTriangles)
    :m_aVertices(std::move(aVertices))
    ,m_aTriangles(std::move(aTriangles))
{
    CalculateBound();
}

void ObjectModel::Copy2(VertexArray& outVertices,Array<Triangle*>& outTriangles) const
{
    m_aVertices.Copy2(outVertices,VA_ALL);
    for(Int32 iTriangle = 0; iTriangle < m_aTriangles.GetSize(); ++iTriangle)
    {
	outTriangles[iTriangle] = &NonConst(m_aTriangles[iTriangle]);
    }
}

void ObjectModel::CalculateBound( void )
{
    auto& aModelPosition = m_aVertices.GetPositions();
    if(0 == aModelPosition.GetSize())
    {
	m_bound = Sphere();
    }

    Vector sum = Vector::Zero;
    for(int i = 0; i < aModelPosition.GetSize(); ++i)
    {
	sum += aModelPosition[i];
    }

    m_bound.center = sum / aModelPosition.GetSize();

    m_bound.radius = 0.0;
    for(int i = 0; i < aModelPosition.GetSize(); ++i)
    {
	Vector diff = aModelPosition[i] - m_bound.center;
	Real tmp = diff.NormSqure();
	if(tmp > m_bound.radius)
	{
	    m_bound.radius = tmp;
	}
    }

    m_bound.radius = Sqrt(m_bound.radius);
}

