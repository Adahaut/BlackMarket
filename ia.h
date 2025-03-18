#ifndef _H3_COMPONENTS_IACOMPONENT_H_
#define _H3_COMPONENTS_IACOMPONENT_H_

#include <h3.h>

#define IACOMPONENT_TYPEID 0x10008703

H3_CAPI_BEGIN_BLOCK
void IaComponent_Terminate(void* properties);
void IaComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void IaComponent_ColliderON(H3Handle object, SH3Collision collide);
void* IaComponent_CreateProperties(H3Handle scene, H3Handle player);

H3_CAPI_END_BLOCK

#define IACOMPONENT_CREATE(SCENE, PLAYER)                                 \
    (SH3Component) {                                                 \
        .Terminate          = IaComponent_Terminate,             \
        .Update             = IaComponent_Update,                \
        .OnCollisionEnter   = IaComponent_ColliderON,        \
        .isInitialized      = false,                                 \
        .componentType      = IACOMPONENT_TYPEID,                \
        .properties         = IaComponent_CreateProperties(SCENE, PLAYER) \
    }

#endif /* _H3_COMPONENTS_IaCOMPONENT_H_ */