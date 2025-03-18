#ifndef _H3_TIMER_H_
#define _H3_TIMER_H_

#include <h3.h>

#define TIMER_TYPEID 0x00000009

H3_CAPI_BEGIN_BLOCK
void TIMER_Terminate(void* properties);
void TIMER_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* TIMER_CreateProperties(H3Handle scene, H3Handle cam, H3Handle player);

H3_CAPI_END_BLOCK

#define TIMER_CREATE(SCENE, CAM, PLAYER)											\
	(SH3Component) {																			\
		.Terminate          = TIMER_Terminate,												\
		.Update             = TIMER_Update,													\
		.isInitialized      = false,															\
		.componentType      = TIMER_TYPEID,													\
		.properties         = TIMER_CreateProperties(SCENE, CAM, PLAYER)			\
}

#endif /* _H3_COMPONENTS_TIMER_H_ */
