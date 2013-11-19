#include <fstream>
#include <sstream>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include "Common/Common.h"
#include "Math/Math.h"
#include "Graphic/PLGLoader.h"
#include "Graphic/Triangle.h"
#include "Graphic/VertexBuffer.h"
#include "Graphic/Object.h"
#include "Graphic/GraphicException.h"
#define PLX_RGB_MASK    0x8000
#define PLX_SHADE_MODE_MASK 0x6000
#define PLX_2SIDED_MASK 0x1000
#define PLX_COLOR_MASK 0x0fff

#define PLX_COLOR_MODE_RGB_FLAG 0x8000
#define PLX_COLOR_MODE_INDEXED_FLAG 0x0000

#define PLX_2SIDE_FLAG 0x1000
#define PLX_1SIDE_FLAG 0x0000

#define PLX_SHADE_MODE_PURE_FLAG 0x0000
#define PLX_SHADE_MODE_FLAT_FLAG 0x2000
#define PLX_SHADE_MODE_GOURAUD_FLAG 0x4000
#define PLX_SHADE_MODE_PHONG_FLAG 0x6000
void PLGLoader::GetLine(std::ifstream& objFile,std::stringstream& strStream) const
{
    std::string strLine;
    while(getline(objFile,strLine))
    {
        boost::trim(strLine);
	if((0 == strLine.length()) || ('#' == strLine[0]))
	{
	    continue;
	}
	else
	{
	    strStream.clear();
	    strStream << strLine;
	    return ;
	}
    }
    
    throw FileException("File may be damaged!");
}

Object* PLGLoader::Load(const std::string & strFile,CoordinateSystem cs)
{
    std::ifstream objFile(strFile);
    if(!objFile.is_open())
    {
	throw FileException("Can not open file " + strFile);
    }

    std::stringstream strStream; 
    //1.物体描述符
    GetLine(objFile,strStream);

    //物体名称
    std::string strName;
    strStream >> strName;

    //顶点数目
    Int32 nVertices,nTriangles;
    strStream >> nVertices >> nTriangles;
#ifdef _DEBUG
    std::cout<<"----------Load Object-------------------"<<std::endl;
    std::cout<<nVertices<<" Vertexs: "<<std::endl;
#endif

    //加载顶点列表
    Attributes attris = VA_POSITION|VA_COLOR;
    VertexBuffer *buf = new VertexBuffer(attris,nVertices);

    for(Int32 nVertex = 0; nVertex < nVertices; ++nVertex)
    {
	//读取一个顶点
	GetLine(objFile,strStream);
	Point& pt = buf->GetPosition(nVertex);
        strStream >> pt.x >> pt.y >> pt.z;       	
	pt.w = 1.0;

        Color& clr = buf->GetColor(nVertex);
        clr.r = 255;
        clr.g = 255;
	clr.b = 0;
#ifdef _DEBUG
	std::cout<<cindent.Reset(1)<<pt<<std::endl;
#endif
    }

    //加载三角形列表
    std::string strDescriptor;
    Int32 nCnt,p1,p2,p3,surfaceDes;
#ifdef _DEBUG
    std::cout<<nTriangles<<" Triangles: "<<std::endl;
#endif

    ObjectModelPtr pModel(new ObjectModel(buf));
    for(Int32 nTri = 0; nTri < nTriangles; ++nTri)
    {
        //读取一个三角形
	GetLine(objFile,strStream);

	if(RightHanded == cs)
	{
	    strStream >> strDescriptor >> nCnt >> p1 >> p2 >> p3;
	}
	else
	{
            strStream >> strDescriptor >> nCnt >> p3 >> p2 >> p1;
	}
#ifdef _DEBUG
	std::cout<<cindent.Reset(1)<<strDescriptor<<" "<<nCnt<<" "<<p1 <<" "<<p2<<" "<<p3<<std::endl;
#endif

	assert(3 == nCnt);
        if('0' == strDescriptor[0] && 'x' == strDescriptor[1])
	{
           strStream << strDescriptor;
	   strStream >> std::hex >> surfaceDes >> std::dec; 
	}
	else
	{
	    strStream << strDescriptor;
	    strStream >> surfaceDes;
	}

	FaceType faceType = FT_SINGLE;
	if(surfaceDes & PLX_2SIDE_FLAG)
	{
	    faceType = FT_2SIDE;
	}

	ShadingMode shadeMode;
	int sm    = surfaceDes & PLX_SHADE_MODE_MASK;
	switch(sm)
	{
	    case PLX_SHADE_MODE_PURE_FLAG:
		shadeMode = SM_PURE;
	        break;
	    case PLX_SHADE_MODE_FLAT_FLAG:
		shadeMode = SM_FLAT;
		break;
	    case PLX_SHADE_MODE_GOURAUD_FLAG:
		shadeMode = SM_GOURAUD;
		break;
	    case PLX_SHADE_MODE_PHONG_FLAG:
		shadeMode = SM_PHONG;
		break;
	    default:
		break;
	}

	ColorMode clrMode = COLOR_RGB;
	int red = 0,green = 0,blue = 0;
	if(surfaceDes & PLX_COLOR_MODE_RGB_FLAG)
	{
	    red = ((surfaceDes & 0x0f00) >> 8);
	    green = ((surfaceDes & 0x00f0) >> 4);
	    blue = ((surfaceDes & 0x000f));
	}
	else
	{
	    int clrIdx = ((surfaceDes & 0x00ff));
            static int i = 0;
            switch(i)
            {
                case 0:
                case 1:
                    red = 255;
                    break;
                case 2:
                case 3:
                    green = 255;
                    break;
                case 4:
                case 5:
                    blue = 255;
                    break;
                case 6:
                case 7:
                    red = 255;
                    green = 255;
                    break;
                case 8:
                case 9:
                    red = 255;
                    blue = 255;
                    break;
                case 10:
                case 11:
                    blue = 255;
                    green = 255;
                    break;
            }
            ++i;
	}


	Triangle *tri = new Triangle(p1,p2,p3);
	tri->SetColor(Color(red,green,blue));
	tri->AddAttribute(shadeMode);
	pModel->AddTriangle(tri);
    }//for

    Object* pObject = new Object(strName,pModel);
    return pObject;
}


