#include "Common/Common.h"
#include "Graphic/ProjectPass.h"
#include "Graphic/Object.h"
#include "Graphic/Camera.h"
#include "Graphic/Triangle.h"

void ProjectPass::Process(VertexBuffer& localBuf,VertexBuffer& globalBuf,Int32 p)
{
    VertexBuffer& buf = p < 0 ? globalBuf : localBuf;
    p = p >= 0 ? p : -p;
    Point& pt = buf.GetPosition(p);
    pt = r_pCamera->GetProjectMatrix() * pt;
    pt.ProjectDiv();
    pt = r_pCamera->GetScreenMatrix() * pt;

    if(localBuf.HasAttribute(VA_TEXTCOOR))
    {
	TextureCoord& coor = buf.GetTextureCoord(p);
	coor.t *= pt.z;
	coor.s *= pt.z;
        Int32 nT = TextFix::Double2Fix(coor.t);
        Int32 nS = TextFix::Double2Fix(coor.s);
	++nS;
    }

    if(localBuf.HasAttribute(VA_TEXTCOOR1))
    {
	TextureCoord& coor1 = buf.GetTextureCoord1(p);
	coor1.t *= pt.z;
	coor1.s *= pt.z;
        TextFix::Double2Fix(coor1.t);
        TextFix::Double2Fix(coor1.s);
    }
    Fix28::Double2Fix(pt.z);
}

void ProjectPass::Visit(Object& obj)
{
    static StatusArray IsProcessed(MAX_VERTEX_PEROBJECT,MAX_VERTEX_PEROBJECT / 4);
    IsProcessed.Reset();
    VertexBuffer& bufLocal = obj.GetVertexBuffer();
    VertexBuffer& bufGlobal = VertexBuffer::GetGlobalBuffer();
    for(auto tri : obj.GetTriangles())
    {
        if(tri->IsVisible())
	{
	    Int32 p0 = tri->GetIndexOfP0();
	    Int32 p1 = tri->GetIndexOfP1();
	    Int32 p2 = tri->GetIndexOfP2();

	    if(!IsProcessed.TestAndSet(p0,obj.GetStartIndex()))
	    {
		Process(bufLocal,bufGlobal,p0);
	    }

	    if(!IsProcessed.TestAndSet(p1,obj.GetStartIndex()))
	    {
		Process(bufLocal,bufGlobal,p1);
	    }

	    if(!IsProcessed.TestAndSet(p2,obj.GetStartIndex()))
	    {
		Process(bufLocal,bufGlobal,p2);
	    }
	}
    } 

    m_vRendLists.push_back(RenderItem(obj.GetTexture(),&obj.GetVertexBuffer(),&obj.GetTriangles()));
}

