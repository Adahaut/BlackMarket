#include "INVENTORYWOMAN.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <components/cameracomponent.h>
#include "movements.h"
#include "inventorywoman.h"


typedef struct {
	H3Handle scene;
	H3Handle cam;
	H3Handle inv;
	bool isinvcreate;
	bool isinv;
	int ix;
	int iy;
	H3Handle slot1;
	H3Handle slot2;
	H3Handle slot3;
}INVENTORYWOMAN_Properties;


void INVENTORYWOMAN_Terminate(void* properties)
{
	free(properties);
}


void INVENTORYWOMAN_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	INVENTORYWOMAN_Properties* props = (INVENTORYWOMAN_Properties*)properties;

	if (props->isinvcreate == false) {
		//Create inventory object
		H3Handle inventory = H3_Object_Create(props->scene, "inventory", props->cam);
		H3_Object_AddComponent(inventory, SPRITECOMPONENT_CREATE("assets/WomanInventory.png", A_Middle | A_Center));
		H3_Object_Scale(inventory, 0.34);
		//Create inventory's slots
		H3Handle slot1 = H3_Object_Create2(props->scene, "slot1", props->cam, 32);
		H3Handle slot2 = H3_Object_Create2(props->scene, "slot2", props->cam, 32);
		H3Handle slot3 = H3_Object_Create2(props->scene, "slot3", props->cam, 32);
		H3_Object_AddComponent(slot1, SPRITECOMPONENT_CREATE("assets/Slot.png", A_Middle | A_Center));
		H3_Object_AddComponent(slot2, SPRITECOMPONENT_CREATE("assets/Slot.png", A_Middle | A_Center));
		H3_Object_AddComponent(slot3, SPRITECOMPONENT_CREATE("assets/Slot.png", A_Middle | A_Center));
		H3_Object_Translate(slot1, 140, 110);
		H3_Object_Translate(slot2, 170, 110);
		H3_Object_Translate(slot3, 200, 110);
		props->slot1 = slot1;
		props->slot2 = slot2;
		props->slot3 = slot3;
		props->inv = inventory;
		props->isinvcreate = true;

	}

	float px, py;
	H3_Transform_GetPosition(H3_Object_GetTransform(object), &px, &py);

	if (H3_Input_IsKeyPressed(K_Tab)) {
		props->isinv = !props->isinv;
		//Put a sound when opening inventory
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
		//H3_Object_SetRenderOrder(props->slot1, 30);
		//H3_Object_SetRenderOrder(props->slot2, 30);
		//H3_Object_SetRenderOrder(props->slot3, 30);
	}

	//H3_Object_SetTranslation(props->slot1, 140, 110);
	//H3_Object_SetTranslation(props->slot2, 170, 110);
	//H3_Object_SetTranslation(props->slot3, 200, 110);

}

void* INVENTORYWOMAN_CreateProperties(H3Handle scene, H3Handle cam, H3Handle s1, H3Handle s2, H3Handle s3)
{
	INVENTORYWOMAN_Properties* properties = malloc(sizeof(INVENTORYWOMAN_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
	properties->cam = cam;
	properties->isinvcreate = false;
	properties->isinv = false;
	properties->ix = -1000;
	properties->iy = -1000;
	properties->slot1 = s1;
	properties->slot2 = s2;
	properties->slot3 = s3;

	return properties;
}


H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(INVENTORYWOMAN, bool, isinv);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(INVENTORYWOMAN, INVENTORYWOMAN_TYPEID, bool, isinv);