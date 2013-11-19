inline void Object::AddAttribute(ObjectAttribute attr)
{
    m_attribute |= attr;
}

inline void Object::RemoveAttribute(ObjectAttribute attr)
{
    m_attribute &= ~attr;
}

inline bool Object::HasAttribute(ObjectAttribute attr) const
{
    return (m_attribute & attr);
}

inline void Object::AddState(ObjectState state)
{
    m_state |= state;
}

inline void Object::RemoveState(ObjectState state)
{
    m_state &= ~state;
}

inline bool Object::HasState(ObjectState state) const
{
    return (m_state & state);
}

inline bool Object::IsVisible( void ) const
{
    return HasState(OS_ACTIVE) && !HasState(OS_CULLED);
}

inline CullMode Object::GetCullMode( void ) const 
{
    return static_cast<CullMode>(m_attribute & CM_MASK);
}

inline void Object::SetCullMode(CullMode eM)
{ 
    RemoveAttribute(CM_MASK);
    AddAttribute(eM);
}

inline BackFaceCullerMode Object::GetBackFaceMode( void ) const 
{ 
    return static_cast<BackFaceCullerMode>(m_attribute & BFC_MASK); 
}

inline void Object::SetBaceFaceMode(BackFaceCullerMode bcf)
{ 
    RemoveAttribute(BFC_MASK);
    AddAttribute(bcf);
}


inline void Object::SetWorldPosition(Real x,Real y,Real z) 
{
    m_worldPos.x = x;
    m_worldPos.y = y;
    m_worldPos.z = z;
}

bool Object::IsCulled( void ) const
{
    return HasState(OS_CULLED);
}

void Object::SetShadingMode(ShadingMode sm)
{
    RemoveAttribute(SM_MASK);
    AddAttribute(sm);
}

ShadingMode Object::GetShadingMode( void )
{
    return static_cast<ShadingMode>(m_attribute & SM_MASK);
}

void Object::SetStyle(ObjectStyle style)
{
    RemoveAttribute(EOS_MASK);
    AddAttribute(style);
}

ObjectStyle Object::GetStyle( void ) const
{
    return static_cast<ObjectStyle>(m_attribute & EOS_MASK);
}

bool Object::NeedShading( void )
{
    return HasAttribute(SM_CONST); 
}

Attributes Object::SelectBuffer(Attributes attris)
{
    if(NeedShading())
    {
	attris |= VA_NORMAL;
    }

    return attris;
}
