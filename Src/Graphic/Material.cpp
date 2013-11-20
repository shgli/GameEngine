#include "Graphic/Material.h"
Material::Material(MaterialId id)
    :m_id(id)
{}

//===================MaterialMgr==========================
const Int32 MaterialMgr::g_nDefaultIncrement = 16;
const Int32 MaterialMgr::g_nDefaultMaterialSize = 16;
MaterialMgr::MaterialMgr( void )
    :m_aMaterial(g_nDefaultMaterialSize)
{}

Material* MaterialMgr::GetMaterial(MaterialId id)
{
    if(id == InvalidMaterialId)
    {
        return nullptr;
    }
    else
    {
        return &m_aMaterial[id];
    }
}

Material* MaterialMgr::GetMaterialByName(std::string& name)
{
    auto itPair = m_mapNameMapping.find(name);
    if(itPair == m_mapNameMapping.end())
    {
        return nullptr;
    }
    else
    {
        return itPair->second;
    }
}

Material* MaterialMgr::GenMaterial(std::string& name)
{
    if(m_aMaterial.GetSize() >= m_aMaterial.GetCapacity())
    {
        m_aMaterial.Extend(g_nDefaultIncrement);
    }

    return NewMaterial(m_aMaterial.GetSize(),name);
}

Material* MaterialMgr::TryGenMaterial(MaterialId id,std::string& name)
{
    if(id < m_aMaterial.GetSize())
    {
        return nullptr;
    }
    else if(id >= m_aMaterial.GetCapacity())
    {
        m_aMaterial.Extend(Max(id - m_aMaterial.GetCapacity() + 1,g_nDefaultIncrement));
    }

    return NewMaterial(id,name);
}

Material* MaterialMgr::NewMaterial(MaterialId id,std::string& name)
{
    m_aMaterial.Resize(id + 1);
    Material *pNewMat = new(GetMaterial(id))Material(id);

    m_mapNameMapping[name] = pNewMat;
    return pNewMat;
}

MaterialMgr& MaterialMgr::Instance( void )
{
    static MaterialMgr materialMgrInstance;
    return materialMgrInstance;
}

