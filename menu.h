#ifndef _H3_MENU_H_
#define _H3_MENU_H_

#include <h3.h>

#define MENU_TYPEID 0x000067212

H3_CAPI_BEGIN_BLOCK
void MENU_Terminate(void* properties);
void MENU_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void MENU_Collide(H3Handle object, SH3Collision collide);
void* MENU_CreateProperties(H3Handle snd, H3Handle scene, H3Handle man, H3Handle woman, H3Handle a1, H3Handle a5);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(MENU, int, choice);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MENU, int, choice);


H3_CAPI_END_BLOCK

#define MENU_CREATE(SND, SCENE, MAN, WOMAN, A1, A5)											\
	(SH3Component) {																			\
		.Terminate          = MENU_Terminate,												\
		.Update             = MENU_Update,													\
		.isInitialized      = false,															\
		.componentType      = MENU_TYPEID,													\
		.properties         = MENU_CreateProperties(SND, SCENE, MAN, WOMAN, A1, A5)			\
}

#endif /* _H3_COMPONENTS_MENU_H_ */