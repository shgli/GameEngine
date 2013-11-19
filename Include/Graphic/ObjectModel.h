#ifndef _OBJECTMODEL_H
#define _OBJECTMODEL_H
#include <boost/shared_ptr.hpp>
#include "Math/Math.h"
enum PrimitiveType
{
    PT_TRIANGLES,
    PT_TRIANGLE_STRIP,
    PT_TRIANGLE_FAN
};

//==========================ObjectModel========================================
class VertexBuffer;
class IndexBuffer;
class Texture;
class Triangle;
class ObjectModel
{
    VertexBuffer *m_vertexBuf;
    IndexBuffer *m_indexBuf;
    Sphere m_bound;
    PrimitiveType m_ePrimType;
    Texture* m_pTexture;
    std::vector<Triangle*> m_vTriangles;
public:
    ObjectModel(VertexBuffer* vertexBuf,PrimitiveType pt = PT_TRIANGLES);

    void CalculateBound( void );
    
    void TransformVertices(VertexBuffer& outVertexBuf,const Matrix& m) const;

    void AddTriangle(Triangle* tri);

    inline const Sphere& GetBound( void ) const { return m_bound; }

    inline Int32 GetTriangleCount( void ) const { return m_vTriangles.size(); }

    inline std::vector<Triangle*>& GetTriangles( void ) { return m_vTriangles; } 

    inline const VertexBuffer* GetVertexBuffer( void ) const { return m_vertexBuf; }

    inline Texture* GetTexture( void ) { return m_pTexture; }

    inline void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }
private:

    void GetTriangleIndex(Int32 nIdx,Int32& p1,Int32& p2,Int32& p3) const;
};

typedef std::shared_ptr<ObjectModel> ObjectModelPtr;
#endif
 
