/**
* @file WordEndian.h
* @brief 
* @author Li Shugan
* @date 2011-10-15 19:17:58
* @version 1.0
* copyright:fenge.com
* email: li_shugan@126.com
* company: fenge
* All rights reserved.
* modification:
* Write modifications here.
*/
#ifndef _WORDENDIAN_H
#define _WORDENDIAN_H
#include "Common/Numeric/CIntypes.h"
typedef  uint8_t   BYTE;
typedef  uint16_t  WORD;
typedef  uint32_t   DWORD;

class WordEndian
{
public:
	static bool IsLittleEndian( void );
	static bool IsBigEndian( void );

	static void SwitchEndian(WORD& word);
	static void SwitchEndian(DWORD& dword);

	static void SwitchEndian(long& word);
};
#endif 
