#ifndef _INDEXBUFFER_H
#define _INDEXBUFFER_H
#include "Common/Common.h"
class IndexBuffer
{
public:
    IndexBuffer(Int32 nSize);

    IndexBuffer(const std::initializer_list<int>& indices);

    ~IndexBuffer( void );

    IndexBuffer& operator= (const std::initializer_list<int>& indices);

    inline Int32& operator[] (Int32 nIdx)
    {
        assert(nIdx >= 0 && nIdx < m_nSize);
        return m_pIndices[nIdx];
    }

    inline const Int32& operator[] (Int32 nIdx) const
    {
        assert(nIdx >= 0 && nIdx < m_nSize);
        return m_pIndices[nIdx];
    }

    inline const Int32 GetSize( void ) const { return m_nSize; }

private:
    IndexBuffer(const IndexBuffer& );

    Int32* m_pIndices;
    Int32 m_nSize;
};
#endif

