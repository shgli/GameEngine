#include <algorithm>
#include <cstring>
#include <map>
#include <utility>
#include "Math/Math.h"
#include "Graphic/Color.h"
#include "Graphic/VertexArray.h"
#include "Graphic/GraphicException.h"

void VertexArray::Copy2(VertexArray& array,Attributes copyAttri) const
{
    if(HasAttribute(VA_POSITION) & (copyAttri & VA_POSITION))
    {
	m_aPosition.Copy2(array.m_aPosition);
    }

    if(HasAttribute(VA_TEXTCOOR) & (copyAttri & VA_TEXTCOOR))
    {
	m_aTextCoord.Copy2(array.m_aTextCoord);
    }

    if(HasAttribute(VA_TEXTCOOR1) & (copyAttri & VA_TEXTCOOR1))
    {
	m_aTextCoord1.Copy2(array.m_aTextCoord1);
    }

    if(HasAttribute(VA_NORMAL) & (copyAttri & VA_NORMAL))
    {
	m_aNormal.Copy2(array.m_aNormal);
    }
}


//=================implementation of VertexIndex===========================
VertexIndex::VertexIndex( void )
    :m_nIdxPos(InvalidId)
    ,m_nIdxText(InvalidId)
    ,m_nIdxNormal(InvalidId)
    ,m_nIdxColor(InvalidId)
{}

VertexIndex& VertexIndex::operator= (const std::initializer_list<Int32>& idx)
{
    assert(idx.size() <= 3);
    auto itId = idx.begin();
    if(itId != idx.end())
    {
	m_nIdxPos = *itId;

	if(++itId != idx.end())
	{
	    m_nIdxText = *itId;
	    if(++itId != idx.end())
	    {
		m_nIdxNormal = *itId;
	    } //normal
	} //texture coordinate
    }//pos
}

//=====================implmentation of Vertex ===========================
Vertex::Vertex(VertexArray& array,const VertexIndex& indices)
    :r_pPosition(nullptr)
    ,r_pTextCoord(nullptr)
    ,r_pTextCoord1(nullptr)
    ,r_pNormal(nullptr)
    ,r_pColor(nullptr)
{
    if(array.HasAttribute(VA_POSITION))
    {
	r_pPosition = &array.GetPosition(indices.GetPositionIndex());
    }

    if(array.HasAttribute(VA_TEXTCOOR))
    {
	r_pTextCoord = &array.GetTextCoord(indices.GetTextCoordIndex());
    }

    if(array.HasAttribute(VA_TEXTCOOR1))
    {
	r_pTextCoord1 = &array.GetTextCoord1(indices.GetTextCoord1Index());
    }

    if(array.HasAttribute(VA_NORMAL))
    {
	r_pNormal = &array.GetNormal(indices.GetNormalIndex());
    }

    if(array.HasAttribute(VA_COLOR))
    {
	r_pColor = &array.GetColor(indices.GetColorIndex());
    }
}

bool Vertex::HasAttribute(VertexAttribute attri) const
{
    switch(attri)
    {
	case VA_POSITION:
	    assert(nullptr != r_pPosition);
	    return true;
	case VA_NORMAL:
	    return nullptr != r_pNormal;
	case VA_COLOR:
	    return nullptr != r_pColor;
	case VA_TEXTCOOR:
	    return nullptr != r_pTextCoord;
	case VA_TEXTCOOR1:
	    return nullptr != r_pTextCoord1;
	default:
	    return false;
    }
}
