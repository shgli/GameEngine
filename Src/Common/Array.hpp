#include <type_traits>
template<typename T>
Array<T>& Array<T>::operator= (const std::initializer_list<T>& l)
{
    if(l.size() > m_nCapacity)
    {
	Extend(l.size() - m_nCapacity);
    }

    m_nSize = 0;
    for(auto v : l)
    {
	m_pData[m_nSize++] = v;
    }
}

template<typename T>
void Array<T>::Copy2(Array<T>& outArray) const
{
    outArray.EnsureSize(m_nSize);

    if(std::is_pod<T>::value)
    {
        std::memcpy(outArray.m_pData,m_pData,m_nSize * sizeof(T));
    }
    else
    {
	for(Int32 iV = 0; iV < GetSize(); ++iV)
	{
	    outArray[iV] = m_pData[iV];
	}
    }
}

