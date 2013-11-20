#ifndef _TRIANGLE_H
#define _TRIANGLE_H
#include "Graphic/IndexBuffer.h"
#include "Graphic/VertexArray.h"
#include "Graphic/Color.h"
#include "Math/Math.h"
#include "Graphic/Material.h"
//===========attribute=============//
enum FaceType
{
    FT_SINGLE = 0x0001,
    FT_2SIDE  = 0x0002,
    FT_MASK   = 0x0007
};

enum ColorMode
{
    COLOR_RGB = 0x0010,
    COLOR_INDEX = 0x0020,
    COLOR_MASK = 0x0070
};

//=============state=================//
enum FaceState
{
    FS_BACKFACE  = 0x0001,
    FS_FRONTFACE = 0x0002,
    FS_2SIDE     = 0x0004,
    FS_MASK      = 0x0007
};

enum TriState
{
    TS_CULLED  = 0x0010,
    TS_CLIPPED = 0x0020,
    TS_MASK    = 0x0070
};

class Triangle
{
#ifdef _DEBUG
    UInt32 m_state;
#endif
    
    MaterialId m_idMaterial;
    VertexIndex m_vertices[3];
    Vector m_normal;

public:
    Triangle(const VertexIndex& id0,const VertexIndex& id1,const VertexIndex& id2,MaterialId matId)
	:m_idMaterial(matId)
    {
	m_vertices[0] = id0;
	m_vertices[1] = id1;
	m_vertices[2] = id2;
    }

    Triangle& operator= (std::initializer_list<std::initializer_list<Int32> >& ids);
    void CalculateNormal(const VertexArray& buf);

    //getter
    inline Vector& GetNormal( void ) { return m_normal; }
    inline const Vector& GetNormal( void )const { return m_normal; }

    inline const Vertex GetVertex0(VertexArray& vertexArray) const { return Vertex(vertexArray,m_vertices[0]); }
    inline const Vertex Getvertex1(VertexArray& vertexArray) const { return Vertex(vertexArray,m_vertices[1]); }
    inline const Vertex Getvertex2(VertexArray& vertexArray) const { return Vertex(vertexArray,m_vertices[2]); }

    inline Vertex GetVertex0(VertexArray& vertexArray) { return Vertex(vertexArray,m_vertices[0]); }
    inline Vertex Getvertex1(VertexArray& vertexArray) { return Vertex(vertexArray,m_vertices[1]); }
    inline Vertex Getvertex2(VertexArray& vertexArray) { return Vertex(vertexArray,m_vertices[2]); }

    inline VertexIndex& GetIndex0( void ) { return m_vertices[0]; }
    inline VertexIndex& GetIndex1( void ) { return m_vertices[1]; }
    inline VertexIndex& GetIndex2( void ) { return m_vertices[2]; }

    inline MaterialId GetMaterialID( void ) const { return m_idMaterial; }

    inline Int32 GetPositionIndex(Int32 idx) const { return m_vertices[idx].GetPositionIndex();}
    inline Int32 GetTextCoordIndex(Int32 idx) const { return m_vertices[idx].GetTextCoordIndex();}
    inline Int32 GetNormalIndex(Int32 idx)const { return m_vertices[idx].GetNormalIndex();}

#ifdef _DEBUG
    inline void AddState(UInt32 state) { m_state |= state; }
    inline void RemoveState(UInt32 state) { (m_state & ~state); }
    inline bool HasState(UInt32 state) const { return (m_state & state); }
    inline bool IsVisible( void ) const { return !HasState(TS_CULLED) && !HasState(TS_CLIPPED);}
#endif

    friend std::ostream& operator<< (std::ostream& os,const Triangle& tri);
};

#endif

