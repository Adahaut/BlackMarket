#ifndef _H3_COMPONENTS_IAMOVECOMPONENT_H_
#define _H3_COMPONENTS_IAMOVECOMPONENT_H_

#include <h3.h>

#define IAMOVECOMPONENT_TYPEID 0x10008747

H3_CAPI_BEGIN_BLOCK
void Iamovecomponent_Terminate(void* properties);
void Iamovecomponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void Iamovecomponent_ColliderON(H3Handle object, SH3Collision collide);
void* Iamovecomponent_CreateProperties(H3Handle scene, H3Handle player);

H3_CAPI_END_BLOCK

#define IAMOVECOMPONENT_CREATE(SCENE, PLAYER)                                 \
    (SH3Component) {                                                 \
        .Terminate          = Iamovecomponent_Terminate,             \
        .Update             = Iamovecomponent_Update,                \
        .OnCollisionEnter   = Iamovecomponent_ColliderON,        \
        .isInitialized      = false,                                 \
        .componentType      = IAMOVECOMPONENT_TYPEID,                \
        .properties         = Iamovecomponent_CreateProperties(SCENE, PLAYER) \
    }

#endif /* _H3_COMPONENTS_IAMOVECOMPONENT_H_ */