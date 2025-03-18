#ifndef _H3_SHOOT_H_
#define _H3_SHOOT_H_

#include <h3.h>

#define SHOOT_TYPEID 0x10670701

H3_CAPI_BEGIN_BLOCK
void Shoot_Terminate(void* properties);
void Shoot_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

void* Shoot_CreateProperties(H3Handle scene, int choice);

H3_CAPI_END_BLOCK

#define SHOOT_CREATE(SCENE, CHOICE)                                 \
    (SH3Component) {                                                 \
        .Terminate          = Shoot_Terminate,             \
        .Update             = Shoot_Update,                \
        .isInitialized      = false,                                 \
        .componentType      = SHOOT_TYPEID,                \
        .properties         = Shoot_CreateProperties(SCENE, CHOICE) \
    }

#endif /* _H3_COMPONENTS_SHOOT_H_ */