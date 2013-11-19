#include "Graphic/IndexBuffer.h"
IndexBuffer::IndexBuffer(Int32 nSize)
    :m_pIndices(nullptr)
    ,m_nSize(nSize)
{
    assert(nSize > 0);
    m_pIndices = new Int32[nSize];
}

IndexBuffer::IndexBuffer(const std::initializer_list<int>& indices)
    :m_pIndices(nullptr)
    ,m_nSize(indices.size())
{
    m_pIndices = new Int32[m_nSize];
    std::copy(indices.begin(),indices.end(),m_pIndices);
}

IndexBuffer& IndexBuffer::operator= (const std::initializer_list<int>& indices)
{
    auto itEnd = m_nSize < indices.size() ? indices.begin() + m_nSize : indices.end();
    std::copy(indices.begin(),itEnd,m_pIndices);
    return *this;
}

IndexBuffer::~IndexBuffer( void )
{
    delete []m_pIndices;
}

