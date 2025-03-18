#ifndef _H3_BADGE_H_
#define _H3_BADGE_H_

#include <h3.h>

#define BADGE_TYPEID 0x00000009

H3_CAPI_BEGIN_BLOCK
void BADGE_Terminate(void* properties);
void BADGE_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void BADGE_Collide(H3Handle object, SH3Collision collide);
void* BADGE_CreateProperties(H3Handle player, H3Handle scene);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(badge, int, slots);

H3_CAPI_END_BLOCK

#define BADGE_CREATE(PLAYER,TEXTE)                                            \
    (SH3Component) {                                                                            \
        .Terminate          = BADGE_Terminate,                                                \
        .Update             = BADGE_Update,                                                    \
        .isInitialized      = false,                                                            \
        .OnCollisionEnter   = BADGE_Collide,                                                    \
        .componentType      = BADGE_TYPEID,                                                    \
        .properties         = BADGE_CreateProperties(PLAYER, TEXTE)            \
}

#endif /* _H3_COMPONENTS_BADGE_H_ */