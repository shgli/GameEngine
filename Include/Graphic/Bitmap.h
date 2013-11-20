/**
* @file Bitmap.h
* @brief 
* @author Li Shugan
* @date 2011-10-15 12:10:18
* @version 1.0
* copyright:fenge.com
* email: li_shugan@126.com
* company: fenge
* All rights reserved.
* modification:
* Write modifications here.
*/
#ifndef _BITMAP_H
#define _BITMAP_H
#include <string>
#include "Common/Common.h"
#include "Graphic/Color.h"
class Bitmap
{
public:
	enum FORMAT
	{
		RGB = 24,
		RGBA = 32
	};
	struct BITMAPFILEHEADER
	{
		WORD     bfType;
		DWORD    bfSize; 
		WORD     bfReserved1; 
		WORD     bfReserved2; 
		DWORD    bfOffBits;

		static UInt8 Size(){return 14;}
        void SwitchEndians(void);
	};
	struct BITMAPINFOHEADER
	{
		DWORD     biSize; 
		Int32     biWidth; 
		Int32     biHeight; 
		WORD      biPlanes; 
		WORD      biBitCount; 
		DWORD     biCompression; 
		DWORD     biSizeImage; 
		Int32     biXPelsPerMeter; 
		Int32     biYPelsPerMeter; 
		DWORD     biClrUsed; 
		DWORD     biClrImportant;
		static UInt8 Size(){return sizeof(BITMAPINFOHEADER);}
		void SwitchEndians(void);
	};

	Bitmap(const std::string& strPath);
	Bitmap(UInt32 nWidth,UInt32 nHeight,FORMAT format = RGB);
        ~Bitmap();

	void Load(const std::string& strPath);
	void Save(const std::string& strPath);

	void SetPixel(int nX,int nY,Color color);
	void DrawHLine(int nX,int nX1,int nY,Color color);
	Color GetPixel(int nX,int nY) const;
	void SetRowPixel(int nX,int nY,Color clr,bool isNewRow = true);

	Int32 GetWidth( void )const {return nullptr == m_pInfoHeader ? Int32(0) : m_pInfoHeader->biWidth;}

	Int32 GetHeight(void)const{return nullptr == m_pInfoHeader ? Int32(0) : m_pInfoHeader->biHeight;}

	const UInt8* GetData(void)const{return m_pData;}

	void Clear(Color clr);
private:

	void CalculateStoreWidth( void );

	BITMAPFILEHEADER *m_pFileHeader;
	BITMAPINFOHEADER *m_pInfoHeader;

	UInt8 *m_pColorTable;
	UInt8 *m_pData;

	FORMAT m_eFormat;
	UInt32 m_nStoreWidth;
};
#endif 
