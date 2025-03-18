#ifndef _H3_PLAYER_H_
#define _H3_PLAYER_H_

#include <h3.h>

#define PLAYER_TYPEID 0x000067212

H3_CAPI_BEGIN_BLOCK
void PLAYER_Terminate(void* properties);
void PLAYER_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void PLAYER_Collide(H3Handle object, SH3Collision collide);
void* PLAYER_CreateProperties(H3Handle scene, H3Handle menu);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(PLAYER, float, speed);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PLAYER, float, speed);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PLAYER, H3Handle, cam);

H3_CAPI_END_BLOCK

#define PLAYER_CREATE(SCENE, MENU)											\
	(SH3Component) {																			\
		.Terminate          = PLAYER_Terminate,												\
		.Update             = PLAYER_Update,													\
		.isInitialized    = false,															\
		.componentType      = PLAYER_TYPEID,													\
		.properties         = PLAYER_CreateProperties(SCENE, MENU)			\
}

#endif /* _H3_COMPONENTS_PLAYER_H_ */