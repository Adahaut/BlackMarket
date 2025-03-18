#ifndef _H3_MALETTE_H_
#define _H3_MALETTE_H_

#include <h3.h>

#define MALETTE_TYPEID 0x00000009

H3_CAPI_BEGIN_BLOCK
void MALETTE_Terminate(void* properties);
void MALETTE_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void MALETTE_Collide(H3Handle object, SH3Collision collide);
void* MALETTE_CreateProperties(H3Handle player, H3Handle texte);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(malette, int, slots);

H3_CAPI_END_BLOCK

#define MALETTE_CREATE(PLAYER,TEXTE)                                            \
    (SH3Component) {                                                                            \
        .Terminate          = MALETTE_Terminate,                                                \
        .Update             = MALETTE_Update,                                                    \
        .isInitialized      = false,                                                            \
        .OnCollisionEnter   = MALETTE_Collide,                                                    \
        .componentType      = MALETTE_TYPEID,                                                    \
        .properties         = MALETTE_CreateProperties(PLAYER, TEXTE)            \
}

#endif /* _H3_COMPONENTS_MALETTE_H_ */