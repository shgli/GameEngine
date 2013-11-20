#ifndef _ACTIVE_TRIANGLE_ARRAY_H
#define _ACTIVE_TRIANGLE_ARRAY_H
#include "Graphic/VertexArray.h"
#include "Graphic/Material.h"
#include "Graphic/Triangle.h"

class ActiveTriangleArray
{
public:
    ActiveTriangleArray( void )
	:m_nFirstIndex(0)
    {}

    inline VertexArray& GetVertices( void ) { return m_aVertices; }
    inline const VertexArray& GetVertices( void ) const { return m_aVertices; }

    inline Array<Triangle*>& GetTriangles( void ) { return m_aTriangles; }
    inline const Array<Triangle*>& GetTriangles( void ) const { return m_aTriangles; }

    inline Triangle& operator[] (Int32 nIdx) { return *m_aTriangles[nIdx]; }
    inline const Triangle& operator[] (Int32 nIdx) const { return *m_aTriangles[nIdx]; }

    Int32 GetSize() const { return m_aTriangles.GetSize(); }

    inline Triangle* Dequeue( void )
    {
	if(m_nFirstIndex < m_aTriangles.GetSize())
	{
	    return m_aTriangles[m_nFirstIndex++];
	}
	else
	{
	    return nullptr;
	}
    }

    inline void Enqueue(Triangle* pTriangle)
    {
	m_aOutTriangles.Append(pTriangle);
    }

    inline void Enqueue(const VertexIndex& iV0,const VertexIndex& iv1,const VertexIndex& iv2,MaterialId matId)
    {
	m_aGeneratedTriangles.Append(Triangle(iV0,iv1,iv2,matId));
	m_aOutTriangles.Append(&m_aGeneratedTriangles.Last());
    }

    inline void SwapTriangles( void )
    {
	m_aTriangles.Swap(m_aOutTriangles);
	m_nFirstIndex = 0;
    }
private:
    VertexArray m_aVertices;
    Array<Triangle*> m_aTriangles;
    Array<Triangle*> m_aOutTriangles;
    Array<Triangle> m_aGeneratedTriangles;
    Int32 m_nFirstIndex;
};
#endif

