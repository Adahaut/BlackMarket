#ifndef _H3_INVENTORYWOMAN_H_
#define _H3_INVENTORYWOMAN_H_

#include <h3.h>

#define INVENTORYWOMAN_TYPEID 0x000067812

H3_CAPI_BEGIN_BLOCK
void INVENTORYWOMAN_Terminate(void* properties);
void INVENTORYWOMAN_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void INVENTORYWOMAN_Collide(H3Handle object, SH3Collision collide);
void* INVENTORYWOMAN_CreateProperties(H3Handle scene, H3Handle cam);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(INVENTORYWOMAN, bool, isinv);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(INVENTORYWOMAN, bool, isinv);

H3_CAPI_END_BLOCK

#define INVENTORYWOMAN_CREATE(SCENE, CAM)											\
	(SH3Component) {																			\
		.Terminate          = INVENTORYWOMAN_Terminate,												\
		.Update             = INVENTORYWOMAN_Update,													\
		.isInitialized      = false,															\
		.componentType      = INVENTORYWOMAN_TYPEID,													\
		.properties         = INVENTORYWOMAN_CreateProperties(SCENE, CAM)			\
}

#endif /* _H3_COMPONENTS_INVENTORYWOMAN_H_ */