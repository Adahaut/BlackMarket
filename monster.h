#ifndef _H3_MONSTER_H_
#define _H3_MONSTER_H_

#include <h3.h>

#define MONSTER_TYPEID 0x00000009

H3_CAPI_BEGIN_BLOCK
void MONSTER_Terminate(void* properties);
void MONSTER_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void MONSTER_Collide(H3Handle object, SH3Collision collide);
void* MONSTER_CreateProperties(H3Handle player, H3Handle texte);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(monster, int, slots);

H3_CAPI_END_BLOCK

#define MONSTER_CREATE(PLAYER,TEXTE)                                            \
    (SH3Component) {                                                                            \
        .Terminate          = MONSTER_Terminate,                                                \
        .Update             = MONSTER_Update,                                                    \
        .isInitialized      = false,                                                            \
        .OnCollisionEnter   = MONSTER_Collide,                                                    \
        .componentType      = MONSTER_TYPEID,                                                    \
        .properties         = MONSTER_CreateProperties(PLAYER, TEXTE)            \
}

#endif /* _H3_COMPONENTS_MONSTER_H_ */