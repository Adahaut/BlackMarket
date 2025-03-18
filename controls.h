#ifndef _H3_CONTROLS_H_
#define _H3_CONTROLS_H_

#include <h3.h>

#define CONTROLS_TYPEID 0x00000009

H3_CAPI_BEGIN_BLOCK
void CONTROLS_Terminate(void* properties);
void CONTROLS_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void CONTROLS_Collide(H3Handle object, SH3Collision collide);
void* CONTROLS_CreateProperties(H3Handle player, H3Handle texte);

H3_CAPI_END_BLOCK

#define CONTROLS_CREATE(PLAYER,TEXTE)                                            \
    (SH3Component) {                                                                            \
        .Terminate          = CONTROLS_Terminate,                                                \
        .Update             = CONTROLS_Update,                                                    \
        .isInitialized      = false,                                                            \
        .OnCollisionEnter   = CONTROLS_Collide,                                                    \
        .componentType      = CONTROLS_TYPEID,                                                    \
        .properties         = CONTROLS_CreateProperties(PLAYER, TEXTE)            \
}

#endif /* _H3_COMPONENTS_CONTROLS_H_ */