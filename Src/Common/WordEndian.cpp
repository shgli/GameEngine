/**
 * @file WordEndian.cpp
 * @brief 
 * @author Li Shugan
 * @date 2011-10-15 19:19:55
 * @version 1.0
 * copyright:fenge.com
 * email: li_shugan@126.com
 * company: fenge
 * All rights reserved.
 * modification:
 * Write modifications here.
 */
#include "Common/Utils/WordEndian.h"

bool WordEndian::IsLittleEndian( void )
{
    static int32_t i = 1;
    static bool is_le = 1 == (*(char*)&i);

    return is_le;
}

bool WordEndian::IsBigEndian( void )
{
    return !IsLittleEndian();
}

void WordEndian::SwitchEndian(WORD& word)
{
    word = ((word & 0xFF00) >> 8) | ((word & 0x00FF) << 8);
}

void WordEndian::SwitchEndian(DWORD& dword)
{
    dword = ((dword & 0xFF000000) >> 24) | ((dword & 0x00FF0000) >> 16)
	| ((dword & 0x0000FF00) << 16) | ((dword & 0x0000000FF) << 24);
}

void WordEndian::SwitchEndian(long& dword)
{
    dword = ((dword & 0xFF000000) >> 24) | ((dword & 0x00FF0000) >> 16)
	| ((dword & 0x0000FF00) << 16) | ((dword & 0x0000000FF) << 24);
}
