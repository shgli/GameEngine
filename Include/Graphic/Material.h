#ifndef _MATERIAL_HPP
#define _MATERIAL_HPP
#include "Common/Common.h"
struct MaterialValue
{
public:
    Real m_red;
    Real m_green;
    Real m_blue;
};

class Material
{
private:
    Int32 m_nShiness;
    MaterialValue m_Ambient;
    MaterialValue m_Diffuse;
    MaterialValue m_Specular;

public:
    Material( void );
    Material(Int32 shiness
	    ,const MaterialValue& amb
	    ,const MaterialValue& diff
	    ,const MaterialValue& spec);

    void SetShiness(Int32 nShiness) { m_nShiness = nShiness; }
    void SetAmbient(Real r,Real g,Real b);
    void SetDiffuse(Real r,Real g,Real b);
    void SetSpecular(Real r,Real g,Real b);

    const Int32 GetShiness( void ) const { return m_nShiness; }
    const MaterialValue& GetAmbient( void )const { return m_Ambient; }
    const MaterialValue& GetDiffuse( void )const { return m_Diffuse; }
    const MaterialValue& GetSpecular( void )const { return m_Specular; }

    MaterialValue& GetAmbient( void ) { return m_Ambient; }
    MaterialValue& GetDiffuse( void ) { return m_Diffuse; }
    MaterialValue& GetSpecular( void ) { return m_Specular; }
};

typedef Material* MaterialId;
#endif

