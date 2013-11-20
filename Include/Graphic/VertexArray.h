#ifndef _VERTEXBUFFER_H
#define _VERTEXBUFFER_H
#include "Common/Common.h"
#include "Math/Math.h"
#include "Graphic/Texture.h"
class Point;
class Vector;
struct Color;
class TextCoord;

enum VertexAttribute
{
     VA_NONE = 0x0000 
    ,VA_POSITION = 0x0001
    ,VA_NORMAL = 0x0002
    ,VA_COLOR = 0x0004
    ,VA_TEXTCOOR = 0x0008
    ,VA_TEXTCOOR1 = 0x0010
    ,VA_ALL = 0x001f
    ,VA_COUNT = 5 
};

typedef UInt32 Attributes;
static const Int32 InvalidId = -1;

class VertexIndex
{
public:
    VertexIndex( void );

    VertexIndex(Int32 nIdxPos,Int32 nIdxText,Int32 nIdxNorm,Color clr = Color::Black)
    {
	SetIndices(nIdxPos,nIdxText,nIdxNorm);
	SetColor(clr);
    }

    VertexIndex& operator= (const std::initializer_list<Int32>& idx);

    inline void SetIndices(Int32 nIdxPos,Int32 nIdxText,Int32 nIdxNorm)
    {
        m_nIdxPos = nIdxPos;
        m_nIdxText = nIdxText;
        m_nIdxNormal = nIdxNorm;
    }

    inline void SetColor(Color clr) { m_clr = clr; }

    inline Int32 GetPositionIndex( void ) const { return m_nIdxPos; }
    inline Int32 GetTextCoordIndex( void ) const { return m_nIdxText; }
    inline Int32 GetNormalIndex( void ) const { return m_nIdxNormal; }

    inline void SetPositionIndex(Int32 nIdxPos) { m_nIdxPos = nIdxPos;}
    inline void SetTextCoordIndex(Int32 nIdxText) { m_nIdxText = nIdxText;}
    inline void SetNormalIndex(Int32 nIdxNormal) { m_nIdxNormal = nIdxNormal;}

    inline Color GetColor( void ) { return m_clr ;}
private:
    Int32 m_nIdxPos;
    Int32 m_nIdxText;
    Int32 m_nIdxNormal;

    Color m_clr;

    friend class VertexArray;
};


class VertexArray;
class Vertex
{
public:
    Vertex(VertexArray& array,const VertexIndex& indices);
    Vertex(const VertexArray& array,const VertexIndex& indices);


    inline Point& GetPosition( void ) { return *r_pPosition; }
    inline Vector& GetNormal( void ) { return *r_pNormal; }
    inline TextCoord& GetTextCoord( void ) { return *r_pTextCoord; }
    inline Color& GetColor( void ) { return *r_pColor; }

    inline const Point& GetPosition( void ) const { return *r_pPosition; }
    inline const Vector& GetNormal( void ) const { return *r_pNormal; }
    inline const TextCoord& GetTextCoord( void ) const { return *r_pTextCoord; }
    inline const Color GetColor( void ) const { return *r_pColor; }

    bool HasAttribute(VertexAttribute attri) const;

private:
    Point* r_pPosition;
    Vector* r_pNormal;
    TextCoord* r_pTextCoord;
    Color* r_pColor;
};

class VertexArray
{
public:
    VertexArray(Attributes attri = VA_ALL)
        :m_attris(attri)
    {
    }


    VertexArray(VertexArray&& other)
	:m_attris(VA_ALL)
    {
	Swap(other);
    }

    void Enable(Attributes attris)
    {
        m_attris = attris;
    }

    void Copy2(VertexArray& array,Attributes copAttri = VA_ALL) const;

    inline VertexArray& operator= (VertexArray&& vertexArray)
    {
	Swap(vertexArray);
    }

    void Swap(VertexArray& vertexArray)
    {
	::Swap(m_attris,vertexArray.m_attris);
    	SetPositions(vertexArray.m_aPosition);
	SetTextCoords(vertexArray.m_aTextCoord);
	SetNormals(vertexArray.m_aNormal);
    }
    //modifier
    inline void SetPositions(Array<Point>& posArray) { m_aPosition.Swap(posArray);}
    inline void SetTextCoords(Array<TextCoord>& txtArray) { m_aTextCoord.Swap(txtArray); }
    inline void SetNormals(Array<Vector>& normalArray) { m_aNormal.Swap(normalArray); }

    inline void SetPositions(Array<Point>&& posArray) { m_aPosition = std::move(posArray);}
    inline void SetTextCoords(Array<TextCoord>&& txtArray) { m_aTextCoord = std::move(txtArray); }
    inline void SetNormals(Array<Vector>&& normalArray) { m_aNormal = std::move(normalArray); }

    void Append(const Point& pos,const TextCoord& textCoord,const Vector& normal,VertexIndex& index)
    {
        m_aPosition.Append(pos);
        index.m_nIdxPos = m_aPosition.LastIndex();
        if(HasAttribute(VA_TEXTCOOR))
        {
            m_aTextCoord.Append(textCoord);
            index.m_nIdxText = m_aTextCoord.LastIndex();
        }

        if(HasAttribute(VA_NORMAL))
        {
            m_aNormal.Append(normal);
            index.m_nIdxNormal = m_aTextCoord.LastIndex();
        }
    }

    //getter
    Vertex GetVertex(VertexIndex& index) { return Vertex(*this,index); }
    const Vertex GetVertex(VertexIndex& index) const { return Vertex(*this,index); }

    Point& GetPosition(Int32 nIdx) { return m_aPosition[nIdx]; }
    TextCoord& GetTextCoord(Int32 nIdx) { return m_aTextCoord[nIdx]; }
    Vector& GetNormal(Int32 nIdx) { return m_aNormal[nIdx]; }

    const Point& GetPosition(Int32 nIdx) const { return m_aPosition[nIdx]; }
    const TextCoord& GetTextCoord(Int32 nIdx) const { return m_aTextCoord[nIdx]; }
    const Vector& GetNormal(Int32 nIdx) const { return m_aNormal[nIdx]; }

    Int32 GetPositionSize( void ) const { return m_aPosition.GetSize(); }
    Int32 GetTextCoordSize( void ) const { return m_aTextCoord.GetSize(); }
    Int32 GetNormalSize( void ) const { return m_aNormal.GetSize(); }

    bool HasAttribute(VertexAttribute attri) const { return m_attris & attri; }

    inline Array<Point>& GetPositions( void ) { return m_aPosition; }
    inline Array<TextCoord>& GetTextCoords( void ) { return m_aTextCoord; }
    inline Array<Vector>& GetNormals( void ) { return m_aNormal; }

    inline const Array<Point>& GetPositions( void ) const { return m_aPosition; }
    inline const Array<TextCoord>& GetTextCoords( void ) const { return m_aTextCoord; }
    inline const Array<Vector>& GetNormals( void ) const { return m_aNormal; }

    static VertexArray& SelectBuffer(VertexArray& buf,const VertexIndex& idx) { return buf;}
private:
    Attributes m_attris;
    Array<Point> m_aPosition;
    Array<TextCoord> m_aTextCoord;
    Array<Vector> m_aNormal;
};



#endif

