#include "Math/Math.h"
#include "Graphic/Object.h"
#include "Graphic/Triangle.h"
Object::Object(const std::string& strName,const ObjectModelPtr& pModel,ObjectAttribute attri)
    :m_attribute(attri)
    ,m_state(0)
    ,m_strName(strName)
    ,m_bufTransVertex(SelectBuffer(pModel->GetVertexBuffer()->GetAccessor().GetAttributes()),pModel->GetVertexBuffer()->GetSize())
    ,m_pObjectModel(pModel)
{
}

Object::~Object( void )
{
}

void Object::Update(const Matrix& mat)
{
    m_transform.Translate(m_worldPos.x,m_worldPos.y,m_worldPos.z);
    Matrix mTrans = mat * m_transform;
    m_pObjectModel->TransformVertices(m_bufTransVertex,mTrans);

    for(auto tri : m_vTriangles)
    {
	delete tri;
    }

    m_vTriangles.clear();
    auto& vTris = m_pObjectModel->GetTriangles();
    //auto vTris = m_pObjectModel->GetTriangles();

    Triangle* pTriangle = nullptr;
    for(Int32 nIdx = 0; nIdx < vTris.size(); ++nIdx)
    {
	pTriangle = new Triangle(*vTris[nIdx]);
        pTriangle->AddAttribute(GetStyle());
	m_vTriangles.push_back(pTriangle);
    }
}

void Object::Update( void )
{
    m_transform.Translate(m_worldPos.x,m_worldPos.y,m_worldPos.z);
    m_pObjectModel->TransformVertices(m_bufTransVertex,m_transform);
}

void Object::Accept(Pass* visitor)
{
    visitor->Visit(*this);
}

void Object::CalculateBound( void )
{
    if(0 == m_bufTransVertex.GetSize())
    {
	m_bound = Sphere();
    }

    Vector sum = Vector::Zero;
    for(int i = 0; i < m_bufTransVertex.GetSize(); ++i)
    {
	sum += m_bufTransVertex.GetPosition(i);
    }

    m_bound.center = sum / m_bufTransVertex.GetSize();

    m_bound.radius = 0.0;
    for(int i = 0; i < m_bufTransVertex.GetSize(); ++i)
    {
	Vector diff = m_bufTransVertex.GetPosition(i) - m_bound.center;
	Real tmp = diff.NormSqure();
	if(tmp > m_bound.radius)
	{
	    m_bound.radius = tmp;
	}
    }

    m_bound.radius = Sqrt(m_bound.radius);

}

std::ostream& operator<< (std::ostream& os,const Object& obj)
{
//    SAVE_INDENT(cindent);
//    os<<"Object "<<obj.GetName()<<std::endl;
//    os<<cindent.Shift(1)<<"# of triangles: "<<obj.GetTriangleCount()<<std::endl;
//
//    cindent.Shift(1);
//    Triangle tri;
//    for(Int32 nTri = 0; nTri < obj.GetTriangleCount(); ++nTri)
//    {
//	obj.GetTriangle(nTri,tri);
//        os<<cindent.Shift(0)<<nTri<<" "<<tri<<std::endl;
//    }
//
//    os<<cindent.Shift(-1)<<"Bound: "<<std::endl;
//    os<<cindent.Shift(1)<<obj.GetBound()<<std::endl;
//
//    os<<cindent.Shift(-1)<<"Transform: "<<obj.m_transform<<std::endl;
//
//    os<<cindent.Shift(-1)<<"status: ";
//    if(obj.IsActive())
//    {
//	os<< "actived : ";
//    }
//    else
//    {
//	os<< "not actived :";
//    }
//
//    if(obj.IsCulled())
//    {
//	os << "been culled .";
//    }
//    else
//    {
//	os << "not culled .";
//    }
//
    return os;
}

Object* Object::Clone( void )
{
    return new Object(GetName(),m_pObjectModel);
}

//Attributes Object::SelectBuffer()
//{
//
//}
