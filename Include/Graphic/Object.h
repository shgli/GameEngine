#ifndef _OBJECT_H
#define _OBJECT_H
#include "Graphic/ObjectVisitor.h"
#include "Graphic/Culler.h"
#include "Graphic/BackFaceCuller.h"
#include "Graphic/Transform.h"
#include "Graphic/ObjectState.h"
#include "Graphic/ObjectModel.h"
#include "Graphic/VertexBuffer.h"
#include "Math/Math.h"

class Texture;
class Triangle;
class Object
{
    ObjectAttribute m_attribute;
    ObjectState m_state;

    std::string m_strName;
    VertexBuffer m_bufTransVertex;
    ObjectModelPtr m_pObjectModel;

    Transform m_transform;

    Sphere m_bound;
    Point m_worldPos;

    std::vector<Triangle*>  m_vTriangles;
    Int32 m_nStartIdxInGlobalBuf;
public:
    //constructor/destructor
    Object(const std::string& strName,const ObjectModelPtr& pModel,ObjectAttribute attri = EOS_SOLID | CM_ALL | BFC_BACK | SM_CONST);

    Object* Clone( void );

    virtual ~Object( void );

    inline void SetName(const std::string& strName) { m_strName = strName; }
    inline const std::string& GetName( void ) const { return m_strName; }

    inline void AddAttribute(ObjectAttribute attr);

    inline void RemoveAttribute(ObjectAttribute attr);

    inline bool HasAttribute(ObjectAttribute attr) const;

    inline void AddState(ObjectState state);

    inline void RemoveState(ObjectState state);

    inline bool HasState(ObjectState state) const;

    inline bool IsVisible( void ) const;

    //cull mode + cull state
    inline CullMode GetCullMode( void ) const;

    inline void SetCullMode(CullMode eM);

    inline bool IsCulled( void ) const;

    //backface culling mode
    inline void SetBaceFaceMode(BackFaceCullerMode bcf);

    inline BackFaceCullerMode GetBackFaceMode( void ) const;

    //shading mode
    inline void SetShadingMode(ShadingMode sm);
    inline ShadingMode GetShadingMode( void );
    inline bool NeedShading( void );

    //style
    inline void SetStyle(ObjectStyle style);
    inline ObjectStyle GetStyle( void ) const;

    inline void SetStartIndex(Int32 nStartIdx) { m_nStartIdxInGlobalBuf = nStartIdx; }
    inline Int32 GetStartIndex( void ) const { return m_nStartIdxInGlobalBuf; }

    inline const Sphere& GetBound( void ) const { return m_bound; }

    Transform* operator-> ( void ) { return &m_transform; }

    void CalculateBound( void );

    void Accept(Pass* visitor);

    void Update(const Matrix& mat);

    void Update( void );

    inline Texture* GetTexture( void ) { m_pObjectModel->GetTexture(); }
    inline VertexBuffer& GetVertexBuffer( void ) { return m_bufTransVertex; }
    inline const VertexBuffer& GetVertexBuffer( void ) const { return m_bufTransVertex; }

    inline std::vector<Triangle*>& GetTriangles( void ) { return m_vTriangles; }
    inline const std::vector<Triangle*>& GetTriangles( void ) const { return m_vTriangles; }

    const Point& GetWorldPosition( void ) const { return m_worldPos; }

    void SetWorldPosition(const Point& pos) 
    {
        m_worldPos = pos;
    }

    void SetWorldPosition(Real x,Real y,Real z) ;

    friend std::ostream& operator<< (std::ostream& os,const Object& obj);

private:
    inline Attributes SelectBuffer(Attributes attris);
};

typedef std::vector<Object*> ObjectList;
#include "Src/Graphic/Object.hpp"
#endif

