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

    VertexIndex(Int32 nIdxPos,Int32 nIdxClr,Int32 nIdxText,Int32 nIdxNorm,Int32 nIdxText1 = InvalidId)
    {
	SetIndices(nIdxPos,nIdxClr,nIdxText,nIdxNorm,nIdxText1);
    }

    VertexIndex& operator= (const std::initializer_list<Int32>& idx);

    inline void SetIndices(Int32 nIdxPos,Int32 nIdxClr,Int32 nIdxText,Int32 nIdxNorm,Int32 nIdxText1)
    {
        m_nIdxPos = nIdxPos;
        m_nIdxText = nIdxText;
	m_nIdxText1 = nIdxText1;
        m_nIdxNormal = nIdxNorm;
	m_nIdxColor = nIdxClr;
    }


    inline Int32 GetPositionIndex( void ) const { return m_nIdxPos; }
    inline Int32 GetTextCoordIndex( void ) const { return m_nIdxText; }
    inline Int32 GetTextCoord1Index( void ) const { return m_nIdxText1; }
    inline Int32 GetNormalIndex( void ) const { return m_nIdxNormal; }
    inline Int32 GetColorIndex( void ) const { return m_nIdxColor; }

    inline void SetPositionIndex(Int32 nIdxPos) { m_nIdxPos = nIdxPos;}
    inline void SetTextCoordIndex(Int32 nIdxText) { m_nIdxText = nIdxText;}
    inline void SetTextCoord1Index(Int32 nIdxText) { m_nIdxText1 = nIdxText;}
    inline void SetNormalIndex(Int32 nIdxNormal) { m_nIdxNormal = nIdxNormal;}
    inline void SetColorIndex(Int32 nIdxClr) { m_nIdxColor= nIdxClr; }

private:
    Int32 m_nIdxPos;
    Int32 m_nIdxText;
    Int32 m_nIdxText1;
    Int32 m_nIdxNormal;

    Int32 m_nIdxColor;

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
    inline TextCoord& GetTextCoord1( void ) { return *r_pTextCoord1; }
    inline Color& GetColor( void ) { return *r_pColor; }

    inline const Point& GetPosition( void ) const { return *r_pPosition; }
    inline const Vector& GetNormal( void ) const { return *r_pNormal; }
    inline const TextCoord& GetTextCoord( void ) const { return *r_pTextCoord; }
    inline const TextCoord& GetTextCoord1( void ) const { return *r_pTextCoord1; }

    inline const Color GetColor( void ) const { return *r_pColor; }

    bool HasAttribute(VertexAttribute attri) const;

private:
    Point* r_pPosition;
    Vector* r_pNormal;
    TextCoord* r_pTextCoord;
    TextCoord* r_pTextCoord1;
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
	SetTextCoords(vertexArray.m_aTextCoord1);
	SetNormals(vertexArray.m_aNormal);
	SetColors(vertexArray.m_aColor);
    }
    //modifier
    inline void SetPositions(Array<Point>& posArray) { m_aPosition.Swap(posArray);}
    inline void SetTextCoords(Array<TextCoord>& txtArray) { m_aTextCoord.Swap(txtArray); }
    inline void SetTextCoords1(Array<TextCoord>& txtArray) { m_aTextCoord1.Swap(txtArray); }
    inline void SetNormals(Array<Vector>& normalArray) { m_aNormal.Swap(normalArray); }
    inline void SetColors(Array<Color>& clrArray) { m_aColor.Swap(clrArray); }

    inline void SetPositions(Array<Point>&& posArray) { m_aPosition.Swap(posArray);}
    inline void SetTextCoords(Array<TextCoord>&& txtArray) { m_aTextCoord.Swap(txtArray); }
    inline void SetTextCoords1(Array<TextCoord>&& txtArray) { m_aTextCoord1.Swap(txtArray); }
    inline void SetNormals(Array<Vector>&& normalArray) { m_aNormal.Swap(normalArray); }
    inline void SetColors(Array<Color>&& clrArray) { m_aColor.Swap(clrArray); }

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
    inline Vertex GetVertex(VertexIndex& index) { return Vertex(*this,index); }
    inline const Vertex GetVertex(VertexIndex& index) const { return Vertex(*this,index); }

    inline Point& GetPosition(Int32 nIdx) { return m_aPosition[nIdx]; }
    inline TextCoord& GetTextCoord(Int32 nIdx) { return m_aTextCoord[nIdx]; }
    inline TextCoord& GetTextCoord1(Int32 nIdx) { return m_aTextCoord1[nIdx]; }
    inline Vector& GetNormal(Int32 nIdx) { return m_aNormal[nIdx]; }
    inline Color& GetColor(Int32 nIdx){ return m_aColor[nIdx]; }

    inline const Point& GetPosition(Int32 nIdx) const { return m_aPosition[nIdx]; }
    inline const TextCoord& GetTextCoord(Int32 nIdx) const { return m_aTextCoord[nIdx]; }
    inline const TextCoord& GetTextCoord1(Int32 nIdx) const { return m_aTextCoord1[nIdx]; }
    inline const Vector& GetNormal(Int32 nIdx) const { return m_aNormal[nIdx]; }
    inline Color GetColor(Int32 nIdx) const { return m_aColor[nIdx]; }

    inline Int32 GetPositionSize( void ) const { return m_aPosition.GetSize(); }
    inline Int32 GetTextCoordSize( void ) const { return m_aTextCoord.GetSize(); }
    inline Int32 GetTextCoord1Size( void ) const { return m_aTextCoord1.GetSize(); }
    inline Int32 GetNormalSize( void ) const { return m_aNormal.GetSize(); }
    inline Int32 GetColorSize( void ) const { return m_aColor.GetSize();}

    inline bool HasAttribute(VertexAttribute attri) const { return m_attris & attri; }

    inline Array<Point>& GetPositions( void ) { return m_aPosition; }
    inline Array<TextCoord>& GetTextCoords( void ) { return m_aTextCoord; }
    inline Array<TextCoord>& GetTextCoord1s( void ) { return m_aTextCoord1; }
    inline Array<Vector>& GetNormals( void ) { return m_aNormal; }
    inline Array<Color>& GetColors( void ) { return m_aColor; }

    inline const Array<Point>& GetPositions( void ) const { return m_aPosition; }
    inline const Array<TextCoord>& GetTextCoords( void ) const { return m_aTextCoord; }
    inline const Array<TextCoord>& GetTextCoord1s( void ) const { return m_aTextCoord1; }
    inline const Array<Vector>& GetNormals( void ) const { return m_aNormal; }
    inline const Array<Color>& GetColors( void ) const { return m_aColor; }

    static VertexArray& SelectBuffer(VertexArray& buf,const VertexIndex& idx) { return buf;}
private:
    Attributes m_attris;
    Array<Point> m_aPosition;
    Array<TextCoord> m_aTextCoord;
    Array<TextCoord> m_aTextCoord1;
    Array<Vector> m_aNormal;
    Array<Color> m_aColor;
};



#endif

