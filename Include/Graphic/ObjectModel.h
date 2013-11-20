#ifndef _OBJECTMODEL_H
#define _OBJECTMODEL_H
#include <boost/shared_ptr.hpp>
#include "Math/Math.h"
#include "VertexArray.h"
enum PrimitiveType
{
    PT_TRIANGLES,
    PT_TRIANGLE_STRIP,
    PT_TRIANGLE_FAN
};

//==========================ObjectModel========================================
class VertexArray;
class IndexBuffer;
class Texture;
class Triangle;
class ObjectModel
{
    VertexArray m_aVertices;
    Array<Triangle> m_aTriangles;
    Sphere m_bound;
public:
    ObjectModel(VertexArray&& aVertices,Array<Triangle>&& aTriangles);

    void CalculateBound( void );
    
    inline const Sphere& GetBound( void ) const { return m_bound; }

    //setter
    inline void SetVertices(VertexArray&& aVertices)
    {
	m_aVertices = std::move(aVertices);
    }

    inline void SetTriangles(Array<Triangle>&& aTriangles)
    {
	m_aTriangles = std::move(aTriangles);
    }

    //getter
    inline VertexArray& GetVertices( void ) { return m_aVertices; }
    inline Array<Triangle>& GetTriangles( void ) { return m_aTriangles; }

    inline const VertexArray& GetVertices( void ) const { return m_aVertices; }
    inline const Array<Triangle>& GetTriangles( void ) const { return m_aTriangles; }

    void Copy2(VertexArray& aVertices,Array<Triangle*>& aTriangles) const;
private:

    void GetTriangleIndex(Int32 nIdx,Int32& p1,Int32& p2,Int32& p3) const;
};

typedef std::shared_ptr<ObjectModel> ObjectModelPtr;
#endif
 
