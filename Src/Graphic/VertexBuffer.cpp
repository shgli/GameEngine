#include <algorithm>
#include <cstring>
#include <map>
#include <utility>
#include "Math/Math.h"
#include "Graphic/Color.h"
#include "Graphic/VertexBuffer.h"
#include "Graphic/GraphicException.h"

//=============================implementation of VertexAttrAccessor========//
VertexAttrAccessor::VertexAttrAccessor(Attributes attris)
{
    m_attris = attris;
    InitOffset(attris);
}

const Point& VertexAttrAccessor::GetPosition(const char* pData) const
{
    if(-1 == m_aOffset[VAI_POSITION])
    {
	throw NoSuchAttribute();
    }

    return *reinterpret_cast<const Point*>(pData + m_aOffset[VAI_POSITION]);
}

const Vector& VertexAttrAccessor::GetNormal(const char* pData) const
{
    if(-1 == m_aOffset[VAI_NORMAL])
    {
	throw NoSuchAttribute();
    }

    return *reinterpret_cast<const Vector*>(pData + m_aOffset[VAI_NORMAL]);

}

const Color& VertexAttrAccessor::GetColor(const char* pData) const
{
    if(-1 == m_aOffset[VAI_COLOR])
    {
	throw NoSuchAttribute();
    }

    return *reinterpret_cast<const Color*>(pData + m_aOffset[VAI_COLOR]);
}

const TextureCoord& VertexAttrAccessor::GetTextureCoord(const char* pData) const
{
    if(-1 == m_aOffset[VAI_TEXTCOOR])
    {
	throw NoSuchAttribute();
    }

    return *reinterpret_cast<const TextureCoord*>(pData + m_aOffset[VAI_TEXTCOOR]);
}

const TextureCoord& VertexAttrAccessor::GetTextureCoord1(const char* pData) const
{
    if(-1 == m_aOffset[VAI_TEXTCOOR1])
    {
	throw NoSuchAttribute();
    }

    return *reinterpret_cast<const TextureCoord*>(pData + m_aOffset[VAI_TEXTCOOR1]);
}

Int32 VertexAttrAccessor::GetAttributeSize(VertexAttribute attri)
{
    Int32 nSize = 0;
    switch(attri)
    {
	case VA_POSITION:
	    nSize = sizeof(Point);
	    break;
	case VA_NORMAL:
	    nSize = sizeof(Vector);
	    break;
	case VA_COLOR:
	    nSize = sizeof(Color);
	    break;
	case VA_TEXTCOOR:
	case VA_TEXTCOOR1:
	    nSize = sizeof(TextureCoord);
	    break;
	default:
	    assert(false);
    } //switch
    
    return nSize;
}

void VertexAttrAccessor::InitOffset(Attributes attris)
{
    m_nSize = 0;
    std::memset(m_aOffset,-1,sizeof(m_aOffset));
    for(int i = 0; i < VA_COUNT; ++i)
    {
	VertexAttribute attri = (VertexAttribute)(1 << i);
        if(-1 == m_aOffset[i] && HasAttribute(attri))
	{
	    m_aOffset[i] = m_nSize;
	    m_nSize += GetAttributeSize(attri);
	} //if

    } //for

}

VertexAttrAccessor& VertexAttrAccessor::GetAttrbuteAccessor(Attributes attris)
{
    static std::map<Int32,VertexAttrAccessor*> accessorMap;
    Int32 id = attris;
    auto it = accessorMap.find(id); 
    if(it == accessorMap.end())
    {
        it = accessorMap.insert(std::make_pair(id,new VertexAttrAccessor(attris))).first;
    }
    return *it->second;
}

void VertexAttrAccessor::Consume(const std::initializer_list<Real>& l,const char* pData) 
{
    auto it = l.begin();
    if(HasAttribute(VA_POSITION))
    {
            GetPosition(pData).x = *it++;
            GetPosition(pData).y = *it++;
            GetPosition(pData).z = *it++;
            GetPosition(pData).w = 1.0;
    }

    if(HasAttribute(VA_NORMAL))
    {
            GetNormal(pData).x = *it++;
            GetNormal(pData).y = *it++;
            GetNormal(pData).z = *it++;
            GetNormal(pData).w = 0.0;
    }

    if(HasAttribute(VA_COLOR))
    {
            GetColor(pData).r = *it++;
            GetColor(pData).g = *it++;
            GetColor(pData).b = *it++;
            if(it != l.end())
            GetColor(pData).a = *it++;
    }

    if(HasAttribute(VA_TEXTCOOR))
    {
	GetTextureCoord(pData).t = *it++;
	GetTextureCoord(pData).s = *it++;
    }

    if(HasAttribute(VA_TEXTCOOR1))
    {
	GetTextureCoord1(pData).t = *it++;
	GetTextureCoord1(pData).s = *it++;
    }
}

//====================Implemenataion fo VertexBuffer================
VertexBuffer* VertexBuffer::g_pGlobalBuffer = nullptr;
VertexBuffer::VertexBuffer(Attributes attris,Int32 nLen)
    :m_pData(nullptr)
    ,m_nSize(nLen)
    ,r_attrAccessor(VertexAttrAccessor::GetAttrbuteAccessor(attris))
{
    assert( nLen > 0);
    m_pData = new char[nLen * r_attrAccessor.Size()];
}

VertexBuffer::VertexBuffer(Attributes attris,char* pData,Int32 nLen)
    :m_pData(nullptr)
    ,m_nSize(nLen)
    ,r_attrAccessor(VertexAttrAccessor::GetAttrbuteAccessor(attris))
{
    assert( nLen > 0);

    if(nullptr != pData && 0 < nLen)
    {
	Int32 nBytes = nLen * r_attrAccessor.Size();
	m_pData = new char[nBytes];
	std::memcpy(m_pData,pData,nBytes);
    }
}

VertexBuffer::VertexBuffer(const VertexAttrAccessor& accessor,Int32 nLen)
    :m_pData(nullptr)
    ,m_nSize(nLen)
    ,r_attrAccessor(accessor)
{
    assert( nLen > 0);
    Int32 nBytes = nLen * r_attrAccessor.Size();
    m_pData = new char[nBytes];
}

VertexBuffer::VertexBuffer(const VertexBuffer& oBuf)
    :m_pData(nullptr)
    ,m_nSize(oBuf.m_nSize)
    ,r_attrAccessor(oBuf.r_attrAccessor)
{
    if(0 < m_nSize)
    {
	Int32 nBytes = m_nSize * r_attrAccessor.Size();
	m_pData = new char[nBytes];
	std::memcpy(m_pData,oBuf.m_pData,nBytes);
    }
}

void VertexBuffer::Copy2(VertexBuffer& out) const
{
    Int32 nSize = m_nSize < out.GetSize() ? m_nSize : out.GetSize();
    for(Int32 nIdx = 0; nIdx < m_nSize; ++nIdx)
    {
	out.GetPosition(nIdx) = GetPosition(nIdx);
	if(HasAttribute(VA_COLOR) && out.HasAttribute(VA_COLOR))
        {
	    out.GetColor(nIdx) = GetColor(nIdx);
	}

	if(HasAttribute(VA_NORMAL) && out.HasAttribute(VA_NORMAL))
	{
	    out.GetNormal(nIdx) = GetNormal(nIdx);
	}

	if(HasAttribute(VA_TEXTCOOR) && out.HasAttribute(VA_TEXTCOOR))
	{
	    out.GetTextureCoord(nIdx) = GetTextureCoord(nIdx);
	}

    	if(HasAttribute(VA_TEXTCOOR1) && out.HasAttribute(VA_TEXTCOOR1))
	{
	    out.GetTextureCoord1(nIdx) = GetTextureCoord1(nIdx);
	}
}
}

VertexBuffer::~VertexBuffer( void )
{
    delete []m_pData;
}

VertexBuffer& VertexBuffer::operator= (const std::initializer_list<Real>& l)
{
    auto itEnd = m_nSize < l.size() ?  l.begin() + m_nSize : l.end();
    std::copy(l.begin(),l.end(),(Real*)m_pData);

    return *this;
}

VertexBuffer& VertexBuffer::operator= (const std::initializer_list<std::initializer_list<Real> >& l)
{
    const char* pData = m_pData;
    for(auto item : l)
    {
        const_cast<VertexAttrAccessor&>(r_attrAccessor).Consume(item,pData);
        pData += r_attrAccessor.Size();
    }
    return *this;
}

Point& VertexBuffer::GetPosition(Int32 nIdx)
{
    return INVOKE_CONSTFUNC(GetPosition(nIdx));
}

const Point& VertexBuffer::GetPosition(Int32 nIdx) const
{
    return r_attrAccessor.GetPosition(GetStartAddress(nIdx));
}

Vector& VertexBuffer::GetNormal(Int32 nIdx)
{
    return INVOKE_CONSTFUNC(GetNormal(nIdx));
}

const Vector& VertexBuffer::GetNormal(Int32 nIdx) const
{
    return r_attrAccessor.GetNormal(GetStartAddress(nIdx));
}

Color& VertexBuffer::GetColor(Int32 nIdx)
{
    return INVOKE_CONSTFUNC(GetColor(nIdx));
}

const Color& VertexBuffer::GetColor(Int32 nIdx) const
{
    return r_attrAccessor.GetColor(GetStartAddress(nIdx));
}

TextureCoord& VertexBuffer::GetTextureCoord(Int32 nIdx)
{
    return INVOKE_CONSTFUNC(GetTextureCoord(nIdx));
}

const TextureCoord& VertexBuffer::GetTextureCoord(Int32 nIdx) const
{
    return r_attrAccessor.GetTextureCoord(GetStartAddress(nIdx));
}

TextureCoord& VertexBuffer::GetTextureCoord1(Int32 nIdx)
{
    return INVOKE_CONSTFUNC(GetTextureCoord1(nIdx));
}

const TextureCoord& VertexBuffer::GetTextureCoord1(Int32 nIdx) const
{
    return r_attrAccessor.GetTextureCoord1(GetStartAddress(nIdx));
}

const char* VertexBuffer::GetStartAddress(Int32 nIdx) const 
{
    if(nIdx < m_nSize)
    {
	return m_pData + nIdx * GetItemSize();
    }

    throw RangeException();
}

VertexBuffer& VertexBuffer::GetGlobalBuffer( void )
{
    if(nullptr == g_pGlobalBuffer)
    {
	Attributes attri = VA_ALL;
	g_pGlobalBuffer = new VertexBuffer(attri,8192);
    }

    return *g_pGlobalBuffer;
}
//====================implementation of Vertex==============
Vertex::Vertex(VertexBuffer& buf,Int32 idx)
    :m_pData(buf.GetStartAddress(idx))
    ,r_accessor(const_cast<VertexAttrAccessor&>(buf.GetAccessor()))
{}

