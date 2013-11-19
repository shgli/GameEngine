#ifndef _VERTEXBUFFER_H
#define _VERTEXBUFFER_H
#include "Common/Common.h"
#include "Math/Math.h"
#include "Graphic/Texture.h"
class Point;
class Vector;
struct Color;
class TextureCoord;

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
class VertexAttrAccessor
{
public:
    typedef Int32 AttrOffsetT[VA_COUNT];

    VertexAttrAccessor(Attributes attris);

    Point& GetPosition(const char* pData) { return INVOKE_CONSTFUNC(GetPosition(pData));}
    const Point& GetPosition(const char* pData)const;

    Vector& GetNormal(const char* pData) { return INVOKE_CONSTFUNC(GetNormal(pData));}
    const Vector& GetNormal(const char* pData)const;

    Color& GetColor(const char* pData) { return INVOKE_CONSTFUNC(GetColor(pData));}
    const Color& GetColor(const char* pData)const;

    TextureCoord& GetTextureCoord(const char* pData) { return INVOKE_CONSTFUNC(GetTextureCoord(pData)); }
    const TextureCoord& GetTextureCoord(const char* pData) const;

    TextureCoord& GetTextureCoord1(const char* pData) { return INVOKE_CONSTFUNC(GetTextureCoord1(pData)); }
    const TextureCoord& GetTextureCoord1(const char* pData) const;

    const Fix28 GetFixZ(const char* pData) const { return *(const Fix28*)(&GetPosition(pData).z); }

    const TextFix GetFixT(const char* pData) const { return *(const TextFix*)(&GetTextureCoord(pData).t); }

    const TextFix GetFixS(const char* pData) const { return *(const TextFix*)(&GetTextureCoord(pData).s); }

    const TextFix GetFixT1(const char* pData) const { return *(TextFix*)(&GetTextureCoord1(pData).t); }

    const TextFix GetFixS1(const char* pData) const { return *(TextFix*)(&GetTextureCoord1(pData).s); }

    inline Int32 Size( void ) const { return m_nSize ; }

    void Consume(const std::initializer_list<Real>& l,const char* pData) ;

    inline bool HasAttribute(VertexAttribute attr) const { return (m_attris & attr); }

    static VertexAttrAccessor& GetAttrbuteAccessor(Attributes attris);

    inline Attributes GetAttributes( void ) const { return m_attris; }
private:
    static Int32 GetAttributeSize( VertexAttribute attri );

    void InitOffset(Attributes attris);

    enum VAttrIdex
    {
        VAI_POSITION = 0 
        ,VAI_NORMAL
        ,VAI_COLOR
        ,VAI_TEXTCOOR
        ,VAI_TEXTCOOR1
    };

    Attributes  m_attris;
    AttrOffsetT m_aOffset;
    Int32 m_nSize;
};

class VertexBuffer
{
public:
    VertexBuffer(Attributes attris,Int32 nLen);

    VertexBuffer(Attributes attris,char* pData,Int32 nLen);

    VertexBuffer(const VertexBuffer& oBuf);

    VertexBuffer(const VertexAttrAccessor& accessor,Int32 nLen);

    ~VertexBuffer( void );

    void Copy2(VertexBuffer& out) const;

    VertexBuffer& operator= (const std::initializer_list<Real>& l);
    VertexBuffer& operator= (const std::initializer_list<std::initializer_list<Real> >& l);

    Point& GetPosition(Int32 nIdx);

    const Point& GetPosition(Int32 nIdx) const;

    Vector& GetNormal(Int32 nIdx);

    const Vector& GetNormal(Int32 nIdx) const;

    Color& GetColor(Int32 nIdx);

    const Color& GetColor(Int32 nIdx) const;

    TextureCoord& GetTextureCoord(Int32 nIdx);

    const TextureCoord& GetTextureCoord(Int32 nIdx) const;

    TextureCoord& GetTextureCoord1(Int32 nIdx);

    inline const Fix28 GetFixZ(Int32 nIdx) const { return r_attrAccessor.GetFixZ(GetStartAddress(nIdx)); }

    inline const TextFix GetFixT(Int32 nIdx) const { return r_attrAccessor.GetFixT(GetStartAddress(nIdx)); }

    inline const TextFix GetFixS(Int32 nIdx) const { return r_attrAccessor.GetFixS(GetStartAddress(nIdx)); }

    inline const TextFix GetFixT1(Int32 nIdx) const { return r_attrAccessor.GetFixT1(GetStartAddress(nIdx)); }

    inline const TextFix GetFixS1(Int32 nIdx) const { return r_attrAccessor.GetFixS1(GetStartAddress(nIdx)); }


    const TextureCoord& GetTextureCoord1(Int32 nIdx) const;

    inline Int32 GetSize( void ) const { return m_nSize;}

    inline const Int32 GetItemSize( void ) const { return r_attrAccessor.Size(); }

    inline const VertexAttrAccessor& GetAccessor( void ) const { return r_attrAccessor; }

    inline bool HasAttribute(VertexAttribute attr) const { return r_attrAccessor.HasAttribute(attr);}

    const char* GetStartAddress(Int32 nIdx) const;

    static VertexBuffer& GetGlobalBuffer( void );
    static inline VertexBuffer&  SelectBuffer(VertexBuffer& buf,Int32 nIdx) { return nIdx < 0 ? GetGlobalBuffer() : buf ;}

private:
    char* m_pData;
    Int32 m_nSize;
    const VertexAttrAccessor& r_attrAccessor;

    static VertexBuffer* g_pGlobalBuffer;
};

class Vertex
{
public:
    Vertex(VertexBuffer& buf,Int32 idx);

    inline Point& GetPosition( void ) { return r_accessor.GetPosition(m_pData);}
    inline const Point& GetPosition( void )const{ return r_accessor.GetPosition(m_pData);}

    inline Vector& GetNormal( void ) { return r_accessor.GetNormal(m_pData);}
    inline const Vector& GetNormal( void )const { return r_accessor.GetNormal(m_pData);}

    inline Color& GetColor( void ) { return r_accessor.GetColor(m_pData);}
    inline const Color& GetColor( void )const { return r_accessor.GetColor(m_pData);}

    inline TextureCoord& GetTextureCoord( void ) { return r_accessor.GetTextureCoord(m_pData); }
    inline const TextureCoord& GetTextureCoord( void ) const { return r_accessor.GetTextureCoord(m_pData);}

    inline TextureCoord& GetTextureCoord1( void ) { return r_accessor.GetTextureCoord1(m_pData);} 
    inline const TextureCoord& GetTextureCoord1(Int32 nIdx) const { return r_accessor.GetTextureCoord1(m_pData);}

    inline bool HasAttribute(VertexAttribute attr) const { return r_accessor.HasAttribute(attr);}

    inline const Fix28 GetFixZ( void ) const { return r_accessor.GetFixZ(m_pData); }

    inline const TextFix GetFixT( void ) const { return r_accessor.GetFixT(m_pData); }

    inline const TextFix GetFixS( void ) const { return r_accessor.GetFixS(m_pData); }

    inline const TextFix GetFixT1( void ) const { return r_accessor.GetFixT1(m_pData); }

    inline const TextFix GetFixS1( void ) const { return r_accessor.GetFixS1(m_pData); }

private:
    const char* m_pData;
    VertexAttrAccessor& r_accessor;
};
#endif

