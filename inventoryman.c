#include "INVENTORYMAN.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <components/cameracomponent.h>
#include "movements.h"
#include "inventoryman.h"


typedef struct {
	H3Handle scene;
	H3Handle cam;
	H3Handle inv;
	H3Handle slot1;
	H3Handle slot2;
	bool isinvcreate;
	bool isinv;
	int ix;
	int iy;
}INVENTORYMAN_Properties;


void INVENTORYMAN_Terminate(void* properties)
{
	free(properties);
}


void INVENTORYMAN_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	INVENTORYMAN_Properties* props = (INVENTORYMAN_Properties*)properties;

	if (props->isinvcreate == false) {
		//Creating inventory
		H3Handle inventory = H3_Object_Create(props->scene, "inventory", props->cam);
		H3_Object_AddComponent(inventory, SPRITECOMPONENT_CREATE("assets/ManInventory.png", A_Middle | A_Center));
		//Creating hotbar's slots
		H3Handle slot1 = H3_Object_Create2(props->scene, "slot2", props->cam, 30);
		H3Handle slot2 = H3_Object_Create2(props->scene, "slot3", props->cam, 30);
		H3_Object_AddComponent(slot1, SPRITECOMPONENT_CREATE("assets/Slot.png", A_Middle | A_Center));
		H3_Object_AddComponent(slot2, SPRITECOMPONENT_CREATE("assets/Slot.png", A_Middle | A_Center));
		H3_Object_Translate(slot1, 170, 110);
		H3_Object_Translate(slot2, 200, 110);
		props->slot1 = slot1;
		props->slot2 = slot2;
		props->isinvcreate = true;
		props->inv = inventory;
	}

	float px, py;
	H3_Transform_GetPosition(H3_Object_GetTransform(object), &px, &py);

	if (H3_Input_IsKeyPressed(K_Tab)) {
		//Put a sound when opening inventory
		props->isinv = !props->isinv;
		H3Handle sndopen = H3_Sound_Load("assets/invopen.wav");
		H3_Sound_Play(sndopen, 1, false);
	}
	if (props->isinv == true) {
		//Show inventory
		H3_Object_SetRenderOrder(props->inv, 12);
	}

	if (props->isinv == false) {
		//Hide inventory
		H3_Object_SetRenderOrder(props->inv, 0);
	}


}

void* INVENTORYMAN_CreateProperties(H3Handle scene, H3Handle cam)
{
	INVENTORYMAN_Properties* properties = malloc(sizeof(INVENTORYMAN_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
	properties->cam = cam;
	properties->isinvcreate = false;
	properties->isinv = false;
	properties->ix = -1000;
	properties->iy = -1000;

	return properties;
}


H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(INVENTORYMAN, bool, isinv);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(INVENTORYMAN, INVENTORYMAN_TYPEID, bool, isinv);