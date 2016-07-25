#pragma once
#include "xrEngine/Engine_impexp.h"
#include "xrSound/Sound.h"

// fwd. decl.
class IGameObject;
template <class T> struct _vector3; typedef _vector3<float> Fvector;

namespace Feel
{
class ENGINE_API Sound
{
public:
    virtual void feel_sound_new(IGameObject* who, int type, CSound_UserDataPtr user_data, const Fvector& Position, float power) {};
};
};
