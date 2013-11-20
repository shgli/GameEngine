#ifndef _MATERIAL_HPP
#define _MATERIAL_HPP
#include <map>
#include "Common/Common.h"
#include "Graphic/Color.h"
#include "Graphic/ObjectState.h"
#include "Graphic/Texture.h"
typedef Int32 MaterialId;
static const Int32 InvalidMaterialId = -1;

class Material
{
private:
    MaterialId m_id;
    Int32 m_nShiness;
    Color m_clrEmission;
    Color m_clrAmbient;
    Color m_clrDiffuse;
    Color m_clrSpecular;
    ShadingMode m_modeShading;

    TextureId m_idTexture;
    TextureMode m_modeTexture;
public:
    Material(MaterialId id);

    inline void SetShadingMode(ShadingMode sm) { m_modeShading = sm; }
    inline void SetShiness(Int32 nShiness) { m_nShiness = nShiness; }
    inline void SetTexture(TextureId id,TextureMode tm) { m_idTexture = id; m_modeTexture = tm; }
    
    inline void SetEmission(Color emission) { m_clrEmission = emission; }
    inline void SetAmbient(Color ambient) { m_clrAmbient = ambient; } 
    inline void SetDiffuse(Color diffuse) { m_clrDiffuse = diffuse; }
    inline void SetSpecular(Color specular) { m_clrSpecular = specular; }

    inline void SetEmission(UInt8 r,UInt8 g,UInt8 b) { SetEmission(Color(r,g,b)); }
    inline void SetAmbient(UInt8 r,UInt8 g,UInt8 b) { SetAmbient(Color(r,g,b)); } 
    inline void SetDiffuse(UInt8 r,UInt8 g,UInt8 b) { SetDiffuse(Color(r,g,b)); }
    inline void SetSpecular(UInt8 r,UInt8 g,UInt8 b) { SetSpecular(Color(r,g,b)); }

    inline const Int32 GetShiness( void ) const { return m_nShiness; }
    inline const Color& GetAmbient( void )const { return m_clrAmbient; }
    inline const Color& GetDiffuse( void )const { return m_clrDiffuse; }
    inline const Color& GetSpecular( void )const { return m_clrSpecular; }

    inline TextureId GetTextureId( void ) const { return m_idTexture; }
    inline TextureMode GetTextMode( void ) const { return m_modeTexture; }
};


class MaterialMgr
{
public:
    Material* GetMaterial(MaterialId id);

    Material* GetMaterialByName(std::string& name);

    Material* GenMaterial(std::string& name);

    Material* TryGenMaterial(MaterialId id,std::string& name);

    MaterialMgr& Instance( void );
private:
    MaterialMgr( void );
    MaterialMgr(const MaterialMgr&);
    MaterialMgr& operator= (const MaterialMgr&);

    Material* NewMaterial(MaterialId id,std::string& name);

    Array<Material> m_aMaterial;
    std::map<std::string,Material*> m_mapNameMapping;

    static const Int32 g_nDefaultIncrement;
    static const Int32 g_nDefaultMaterialSize;
};
#endif

