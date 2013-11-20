#ifndef _ARRAY_H
#define _ARRAY_H
#include <initializer_list>
#include <cmath>
#include "Common/Utils/HelpFuns.h"
template<typename T>
class Array
{
public:
    Array(Int32 nSize = 0)
        :m_nSize(nSize)
        ,m_nCapacity(0)
        ,m_pData(nullptr)
    {
	if(m_nSize > 0)
	{
            Extend(m_nSize);
	}
    }


    Array(Array<T>&& array)
    {
	Swap(array);
    }

    ~Array( void )
    {
        free(m_pData);
    }

    Array& operator= (const std::initializer_list<T>& l);
    inline Array& operator= (Array<T>&& array)
    {
	Swap(array);
	return *this;
    }

    void Copy2(Array<T>& outArray) const;

    inline Int32 GetSize( void ) const { return m_nSize; }
    inline Int32 Resize(Int32 newSize) { m_nSize = std::max(newSize,m_nCapacity); return m_nSize; }
    inline Int32 GetCapacity( void ) const { return m_nCapacity; }
    inline void Clear( void ) { m_nSize = 0; }

    inline T& operator[] (Int32 nIdx) { return m_pData[nIdx]; }
    inline const T& operator[] (Int32 nIdx) const { return m_pData[nIdx]; }

    inline void EnsureSize(Int32 newSize)
    {
	if(m_nCapacity <= newSize)
	{
	    Extend(newSize - m_nCapacity);
	}
    }

    void Append(const T& value)
    {
        EnsureSize(m_nSize + 1);
	m_pData[m_nSize++] = value;
    }

    inline void Extend(Int32 nIncrement = 16)
    {
        m_pData = (T*)realloc(m_pData,(m_nCapacity + nIncrement) * sizeof(T));
        if(nullptr != m_pData)
        {
            m_nCapacity += nIncrement;
        }
        else
        {
            m_nCapacity = m_nSize = 0;
        }
    }

    inline void Swap(Array<T>& array)
    {
        ::Swap(m_nSize,array.m_nSize);
        ::Swap(m_nCapacity,array.m_nCapacity);
        ::Swap(m_pData,array.m_pData);
    }

    inline T& First( void ) { return m_pData[0]; }
    inline T& Last( void ) { return m_pData[m_nSize - 1]; }
    inline const T& First( void ) const { return m_pData[0]; }
    inline const T& Last( void ) const { return m_pData[m_nSize - 1]; }

    inline Int32 LastIndex( void ) const { return m_nSize - 1; }
private:
    //deleted functions
    Array(const Array& ) = delete;
    Array& operator= (const Array& ) = delete;

    Int32 m_nSize;
    Int32 m_nCapacity;
    T* m_pData;
};

#include "Src/Common/Array.hpp"
#endif

