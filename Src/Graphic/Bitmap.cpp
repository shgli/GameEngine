/**
 * @file Bitmap.cpp
 * @brief 
 * @author Li Shugan
 * @date 2011-10-15 12:40:17
 * @version 1.0
 * copyright:fenge.com
 * email: li_shugan@126.com
 * company: fenge
 * All rights reserved.
 * modification:
 * Write modifications here.
 */
#include <stdexcept>
#include <cstring>
#include <locale>
#include <fstream>
#include "Graphic/Bitmap.h"
#include "Common/Utils/WordEndian.h"
void Bitmap::BITMAPFILEHEADER::SwitchEndians()
{
//    WordEndian::SwitchEndian(bfType);
//    WordEndian::SwitchEndian(bfSize); 
//    WordEndian::SwitchEndian(bfReserved1); 
//    WordEndian::SwitchEndian(bfReserved2); 
//    WordEndian::SwitchEndian(bfOffBits);
}

void Bitmap::BITMAPINFOHEADER::SwitchEndians()
{
//    WordEndian::SwitchEndian(biSize); 
//    WordEndian::SwitchEndian(biWidth); 
//    WordEndian::SwitchEndian(biHeight); 
//    WordEndian::SwitchEndian(biPlanes); 
//    WordEndian::SwitchEndian(biBitCount); 
//    WordEndian::SwitchEndian(biCompression); 
//    WordEndian::SwitchEndian(biSizeImage); 
//    WordEndian::SwitchEndian(biXPelsPerMeter); 
//    WordEndian::SwitchEndian(biYPelsPerMeter); 
//    WordEndian::SwitchEndian(biClrUsed); 
}

Bitmap::~Bitmap()
{
    delete m_pFileHeader;
    delete m_pInfoHeader;
    delete []m_pColorTable;
    delete []m_pData;
}

Bitmap::Bitmap(const std::string& strPath):
    m_pFileHeader(NULL)
    ,m_pInfoHeader(NULL)
    ,m_pColorTable(NULL)
    ,m_pData(NULL)
    ,m_nStoreWidth(0)
    ,m_eFormat(RGB)
{
    Load(strPath);
}

Bitmap::Bitmap(UInt32 nWidth,UInt32 nHeight,FORMAT format):
    m_pFileHeader(NULL)
    ,m_pInfoHeader(NULL)
    ,m_pColorTable(NULL)
    ,m_pData(NULL)
    ,m_nStoreWidth(0)
    ,m_eFormat(format)
{
    m_pInfoHeader = new BITMAPINFOHEADER();
    if (NULL != m_pInfoHeader)
    {
	m_pInfoHeader->biSize = BITMAPINFOHEADER::Size(); 
	m_pInfoHeader->biWidth = nWidth; 
	m_pInfoHeader->biHeight = nHeight; 
	m_pInfoHeader->biPlanes = 1; 
	m_pInfoHeader->biBitCount = format; 
	m_pInfoHeader->biCompression = 0; 
	m_pInfoHeader->biSizeImage = 0; 
	m_pInfoHeader->biXPelsPerMeter = 0;
	m_pInfoHeader->biYPelsPerMeter = 0;
	m_pInfoHeader->biClrUsed = 0; 
	m_pInfoHeader->biClrImportant = 0;
    }
    CalculateStoreWidth();

    m_pFileHeader = new BITMAPFILEHEADER();
    if (NULL != m_pFileHeader)
    {
	m_pFileHeader->bfType = WordEndian::IsLittleEndian()?0x4d42:0x424d;
	m_pFileHeader->bfSize = BITMAPFILEHEADER::Size() + BITMAPINFOHEADER::Size() + m_nStoreWidth * nHeight ;
	m_pFileHeader->bfReserved1 = m_pFileHeader->bfReserved2 = 0;
	m_pFileHeader->bfOffBits = BITMAPFILEHEADER::Size() + BITMAPINFOHEADER::Size();
    }

    m_pData = new UInt8[GetValue(nHeight * m_nStoreWidth)];
    std::memset(m_pData,0,(nHeight * m_nStoreWidth));

}

void Bitmap::Load(const std::string& strFile)
{
    if (NULL != m_pData)
    {
	throw std::runtime_error("can not load bitmap two times");
    }
    using namespace std;
    locale loc = locale::global(locale(""));
    ifstream  bmpFile(strFile.c_str(),ios::in | ios::binary);
    locale::global(loc);

    if(bmpFile.fail())
    {
	throw std::runtime_error("can not open " + strFile);
    }

    //读取bitmap-file header
    if(nullptr == m_pFileHeader)
    {
	m_pFileHeader = new BITMAPFILEHEADER;
    }
    bmpFile.read((char*)m_pFileHeader,sizeof(WORD));
    bmpFile.read((char*)m_pFileHeader + 4,(BITMAPFILEHEADER::Size() - sizeof(WORD)));

    bool needSwitchEndian = false;
    if(0x4d42 == m_pFileHeader->bfType)//按小端存储
    {
	needSwitchEndian = WordEndian::IsBigEndian();
    }
    else if (0x424d == m_pFileHeader->bfType) //大端存储
    {
	needSwitchEndian = WordEndian::IsLittleEndian();
    }
    else
    {
	throw std::runtime_error(strFile + "is not a bitmap file!");
    }

    //读取bitmap-information header
    if(nullptr == m_pInfoHeader)
    {
	m_pInfoHeader = new BITMAPINFOHEADER;
    }
    bmpFile.read((char*)m_pInfoHeader,BITMAPINFOHEADER::Size());


    //如果有调色板，读取调色板
    long szColorTable = (m_pFileHeader->bfOffBits - m_pInfoHeader->biSize - BITMAPFILEHEADER::Size());
    if(0 != szColorTable)
    {
	m_pColorTable = new UInt8[szColorTable];
	bmpFile.read((char*)m_pColorTable,szColorTable);
    }

    //switch endians;
    if (needSwitchEndian)
    {
	m_pFileHeader->SwitchEndians();
	if (NULL != m_pInfoHeader)
	{
	    m_pInfoHeader->SwitchEndians();
	}
    }

    //读取bmp数据
    CalculateStoreWidth();
    DWORD dwSize = m_pInfoHeader->biSizeImage;
    if(0 == dwSize) //此时m_m_pInfoHeader->biCompression = BI_RGB,所以没有进行压缩
    {
	dwSize = m_pInfoHeader->biHeight * m_nStoreWidth;
    }

    m_pData = new UInt8[dwSize];
    bmpFile.seekg(GetValue(m_pFileHeader->bfOffBits),ios::beg);
    bmpFile.read((char*)m_pData,GetValue(dwSize));
}

void Bitmap::Save(const std::string& strFile)
{
    using namespace std;
    locale loc = locale::global(locale(""));
    ofstream  bmpFile(strFile.c_str(),ios::out | ios::binary | ios::trunc) ;
    locale::global(loc);

    if(bmpFile.fail())
    {
	throw std::runtime_error("can not open " + strFile + " for write!");
    }

    bmpFile.write((const char*)(&m_pFileHeader->bfType),sizeof(WORD));
    bmpFile.write((const char*)m_pFileHeader + sizeof(DWORD),GetValue(BITMAPFILEHEADER::Size() - sizeof(WORD)));
    bmpFile.write((const char*)m_pInfoHeader,GetValue(BITMAPINFOHEADER::Size()));
    if (NULL != m_pColorTable)
    {
	long szColorTable = GetValue(m_pFileHeader->bfOffBits - m_pInfoHeader->biSize - BITMAPFILEHEADER::Size());
	bmpFile.write((const char*)m_pColorTable,szColorTable);
    }

    DWORD dwSize = m_pInfoHeader->biSizeImage;
    if(0 == dwSize) //此时m_m_pInfoHeader->biCompression = BI_RGB,所以没有进行压缩
    {
	dwSize = m_pInfoHeader->biHeight * m_nStoreWidth;
    }
    bmpFile.write((const char*)m_pData,GetValue(dwSize));
}

void Bitmap::CalculateStoreWidth( void )
{
    if (NULL == m_pInfoHeader)
    {
	return;
    }

    m_nStoreWidth = (((m_pInfoHeader->biWidth * m_pInfoHeader->biBitCount + 31) >> 5) << 2);
}

void Bitmap::SetRowPixel(int nX,int nY,Color color,bool isNewRow)
{
    static int nStartIndex = 0;
    if(isNewRow)
    {
        nStartIndex = nY * m_nStoreWidth + nX * (m_pInfoHeader->biBitCount / 8) - 1;
    }
    else
    {
	m_pData[++nStartIndex] = color.r;
	m_pData[++nStartIndex] = color.g;
	m_pData[++nStartIndex] = color.b;
    }
}

void Bitmap::SetPixel(int nX,int nY,Color color)
{
    if (nX < 0 || nY < 0 || nX >= GetWidth() || nY >= GetHeight())
    {
	return;
    }

    int nStartIndex = GetValue(nY * m_nStoreWidth + nX * (m_pInfoHeader->biBitCount / 8));
    m_pData[nStartIndex] = color.r;
    m_pData[nStartIndex + 1] = color.g;
    m_pData[nStartIndex + 2] = color.b;
}

void Bitmap::DrawHLine(int nX,int nX1,int nY,Color color)
{
    if(nX >= GetWidth() || nX1 <=0 || nY > GetHeight()) return;
    if(nX < 0) nX = 0;
    if(nX1 >= GetWidth()) nX1 = GetWidth() - 1;

    //std::cout<<"Draw Line: "<<nY<<"("<<nX<<","<<nX1<<")"<<std::endl;

    int nBits = (m_pInfoHeader->biBitCount / 8);
    long nStartIndex = GetValue(nY * m_nStoreWidth + nX * nBits);
    for(long i = nStartIndex + 3 * (nX1 - nX) + 2; i >= nStartIndex;i -= 3)
    {
        m_pData[i ] = color.r;
        m_pData[i + 1] = color.g;
        m_pData[i + 2] = color.b;
    }
}

Color Bitmap::GetPixel(int nX,int nY) const
{
    if (nX < 0 || nY < 0 || nX >= GetWidth() || nY >= GetHeight())
    {
	return BLACK_COLOR;
    }

    long nStartIndex = GetValue(nY * m_nStoreWidth + nX * (m_pInfoHeader->biBitCount / 8));
    return *((Color*)(&m_pData[nStartIndex]));
}

void Bitmap::Clear(Color clr)
{
    long szColorTable = GetValue(m_pInfoHeader->biHeight * m_nStoreWidth);
    std::memset(m_pData,clr.AsInt32(),szColorTable);
}

