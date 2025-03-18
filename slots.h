#ifndef _H3_SLOTS_H_
#define _H3_SLOTS_H_

#include <h3.h>

#define SLOTS_TYPEID 0x00000009

H3_CAPI_BEGIN_BLOCK
void SLOTS_Terminate(void* properties);
void SLOTS_Update(H3Handle h3, H3Handle SLOTS, SH3Transform* transform, float t, float dt, void* properties);
void* SLOTS_CreateProperties(H3Handle monster, H3Handle badge, H3Handle cle, H3Handle malette);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(SLOTS, int, slots);

H3_CAPI_END_BLOCK

#define SLOTS_CREATE(MONSTER,BADGE,CLE,MALETTE)                                            \
    (SH3Component) {                                                                            \
        .Terminate          = SLOTS_Terminate,                                                \
        .Update             = SLOTS_Update,                                                    \
        .isInitialized      = false,                                                            \
        .componentType      = SLOTS_TYPEID,                                                    \
        .properties         = SLOTS_CreateProperties(MONSTER,BADGE,CLE,MALETTE)            \
}

#endif /* _H3_COMPONENTS_SLOTS_H_ */