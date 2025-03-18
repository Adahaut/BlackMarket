#ifndef _H3_CLE_H_
#define _H3_CLE_H_

#include <h3.h>

#define CLE_TYPEID 0x00000009

H3_CAPI_BEGIN_BLOCK
void CLE_Terminate(void* properties);
void CLE_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void CLE_Collide(H3Handle object, SH3Collision collide);
void* CLE_CreateProperties(H3Handle player, H3Handle scene);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(cle, int, slots);

H3_CAPI_END_BLOCK

#define CLE_CREATE(PLAYER,TEXTE)                                            \
    (SH3Component) {                                                                            \
        .Terminate          = CLE_Terminate,                                                \
        .Update             = CLE_Update,                                                    \
        .isInitialized      = false,                                                            \
        .OnCollisionEnter   = CLE_Collide,                                                    \
        .componentType      = CLE_TYPEID,                                                    \
        .properties         = CLE_CreateProperties(PLAYER, TEXTE)            \
}

#endif /* _H3_COMPONENTS_CLE_H_ */