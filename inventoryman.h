#ifndef _H3_INVENTORYMAN_H_
#define _H3_INVENTORYMAN_H_

#include <h3.h>

#define INVENTORYMAN_TYPEID 0x000067812

H3_CAPI_BEGIN_BLOCK
void INVENTORYMAN_Terminate(void* properties);
void INVENTORYMAN_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void INVENTORYMAN_Collide(H3Handle object, SH3Collision collide);
void* INVENTORYMAN_CreateProperties(H3Handle scene, H3Handle cam);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(INVENTORYMAN, bool, isinv);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(INVENTORYMAN, bool, isinv);

H3_CAPI_END_BLOCK

#define INVENTORYMAN_CREATE(SCENE, CAM)											\
	(SH3Component) {																			\
		.Terminate          = INVENTORYMAN_Terminate,												\
		.Update             = INVENTORYMAN_Update,													\
		.isInitialized      = false,															\
		.componentType      = INVENTORYMAN_TYPEID,													\
		.properties         = INVENTORYMAN_CreateProperties(SCENE, CAM)			\
}

#endif /* _H3_COMPONENTS_INVENTORYMAN_H_ */