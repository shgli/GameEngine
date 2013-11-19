#include "Graphic/Object.h"
#include "Graphic/Clipper.h"
#include "Graphic/Camera.h"
#include "Graphic/Triangle.h"
void Clipper::Visit(Object& obj)
{
    Int32 nStatus0,nStatus1,nStatus2;
    std::vector<Triangle*>& vTriangles = obj.GetTriangles();
    Int32 nSize = vTriangles.size();
    obj.SetStartIndex(m_nCurSize);
    for(Int32 nTri = 0; nTri < nSize; ++nTri)
    {
	Triangle* tri = vTriangles[nTri];
	//判断三点相对于视景体的位置
	Int32 i0 = tri->GetIndexOfP0();
	Int32 i1 = tri->GetIndexOfP1();
	Int32 i2 = tri->GetIndexOfP2();

        Vertex v0(obj.GetVertexBuffer(),i0);	
        Vertex v1(obj.GetVertexBuffer(),i1);	
        Vertex v2(obj.GetVertexBuffer(),i2);	

	nStatus0 = DeterminateStatus(v0);
	nStatus1 = DeterminateStatus(v1);
	nStatus2 = DeterminateStatus(v2);

	//根据不同的状态作不同的操作:
	//1. 若nStatus0,nStatus1,nStatus2都为0x00 则clip掉
	//2. 若三个顶点的状态是除了0x01外的两种状态，则通过了clipper
	//3. 若三个顶点的状态是除了0x02外的两种状态，则被clip掉了
	//否则需要进行裁剪
	switch(nStatus0 | nStatus1 | nStatus2)
	{
	    case 0:
	    case 1:
		//clipped
		tri->AddState(TS_CLIPPED);
		break;
	    case 2:
		//pass
		break;
	    case 3:
		{
		    tri->AddState(TS_CLIPPED);
		    Vertex* ppos0(&v0),*ppos1(&v1),*ppos2(&v2);
		    //可分为三种情况
		    //1. 只有一个点在near平面上
		    //2. 只有一个点在near后面
		    //3. 只有一个点在near前面
		    if(0 == nStatus0 || 0 == nStatus1 || 0 == nStatus2)
		    {
			//情况1: 只有一个点在near平面上 处理步骤:
			//1. 将在near平面上的点变为第0个点
			if(0 == nStatus1)
			{
			    AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,1);
			}
			else if(0 == nStatus2)
			{
			    AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,2);
			}

			//2. 求线段ppos1->ppos2与平面near的交点
			Int32 nNewIdx = IntersectAndInterpolateAttr(ppos1,ppos2);

			if(ppos1->GetPosition().z < r_pCamera->GetNear())
			{
                            vTriangles.push_back(new Triangle(i0,nNewIdx,i2));
			}
			else
			{
			    vTriangles.push_back(new Triangle(i0,i1,nNewIdx));
			}
		    }
		    else if(5 == (nStatus0 + nStatus1 + nStatus2)) //1 2 2
		    {
			//情况2:只有一个在near后面 处理步骤:
			//1. 将在near后的点变为第0个点
			if(0x01 == nStatus1)
			{
			    AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,1);
			}
			else if(0x01 == nStatus2)
			{
                            AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,2);
			}

			//求出p0->p1以及p0->p2与near的交点
			Int32 nIntersect1 = IntersectAndInterpolateAttr(ppos0,ppos1);
			Int32 nIntersect2 = IntersectAndInterpolateAttr(ppos0,ppos2);
			
			//将新生成的三角形加入到三角形列表中
			vTriangles.push_back(new Triangle(nIntersect1,i1,i2));
			vTriangles.push_back(new Triangle(nIntersect2,nIntersect1,i2));
		    }
		    else
		    {
			//情况2:只有一个在near前面 处理步骤:
			//1. 将在near前的点变为第0个点
			if(0x02 == nStatus1)
			{
			    AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,1);
			}
			else if(0x02 == nStatus2)
			{
                            AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,2);
			}
			//求出p0->p1以及p0->p2与near的交点
			Int32 nIntersect1 = IntersectAndInterpolateAttr(ppos0,ppos1);
			Int32 nIntersect2 = IntersectAndInterpolateAttr(ppos0,ppos2);
			
			//将新生成的三角形加入到三角形列表中
                        vTriangles.push_back(new Triangle(i0,nIntersect1,nIntersect2));
		    }
		}
		break;
	    default:
		assert(false);
	}
    }
}

Int32 Clipper::IntersectAndInterpolateAttr(Vertex* p0,Vertex* p1)
{
    Double t = (r_pCamera->GetNear() - p0->GetPosition().z) / (p1->GetPosition().z - p0->GetPosition().z);

    //插值属性
    Vertex v(VertexBuffer::GetGlobalBuffer(),m_nCurSize++);
    v.GetPosition() = p0->GetPosition() + t * (p1->GetPosition() - p0->GetPosition());

    if(p0->HasAttribute(VA_COLOR))
    {
	v.GetColor() = p0->GetColor() + t * (p1->GetColor() - p0->GetColor());
    }

    if(p0->HasAttribute(VA_TEXTCOOR))
    {
	v.GetTextureCoord() = p0->GetTextureCoord() + t * (p1->GetTextureCoord() - p0->GetTextureCoord());
    }

    if(p0->HasAttribute(VA_TEXTCOOR1))
    {
        v.GetTextureCoord1() = p0->GetTextureCoord1() + t * (p1->GetTextureCoord1() - p0->GetTextureCoord1());
    }

    return (1 - m_nCurSize);
}

Int32 Clipper::DeterminateStatus(Vertex& v)
{
    if(v.GetPosition().z < r_pCamera->GetNear())
    {
	return 0x01; //在near后面
    }
    else if(v.GetPosition().z > r_pCamera->GetNear())
    {
	return 0x02; //在near前面
    }
    else
    {
	return 0x00; //在平面之上
    }
}

void Clipper::AdjustSequence(Vertex*& pp0,Vertex*& pp1,Vertex*& pp2,Int32& i0,Int32& i1,Int32& i2,Int32 nFirstIdx)
{
    if(1 == nFirstIdx)
    {
	Swap(pp0,pp1);
	Swap(pp1,pp2);
	Swap(i0,i1);
	Swap(i1,i2);
    }
    else if(2 == nFirstIdx)
    {
	Swap(pp0,pp1);
	Swap(pp0,pp2);
	Swap(i0,i1);
	Swap(i0,i2);
    }
}

