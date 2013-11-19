#include "Graphic/Material.h"
Material::Material( void )
{}

Material::Material(Int32 nShiness
        ,const MaterialValue& amb
        ,const MaterialValue& diff
        ,const MaterialValue& spec)
    :m_nShiness(nShiness)
    ,m_Ambient(amb)
    ,m_Diffuse(diff)
    ,m_Specular(spec)
{}

