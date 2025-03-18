#include "player.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <components/cameracomponent.h>
#include "movements.h"
#include "timer.h"
#include "inventorywoman.h"
#include "inventoryman.h"
#include "shoot.h"

typedef struct {
	H3Handle scene;
	H3Handle texture1;
	H3Handle texture2;
	H3Handle snd;
	H3Handle cam;
	float speed;
	int choice;
	H3Handle menu;
	bool game;
}PLAYER_Properties;


void PLAYER_Terminate(void* properties)
{
	free(properties);
}


void PLAYER_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	PLAYER_Properties* props = (PLAYER_Properties*)properties;

	int mx, my;
	H3_Input_GetMousePos(h3, &mx, &my);
	if (props->game == false) {
		int choice = MENU_GetchoiceEx(props->menu);
		if (choice == 1)
		{
			//Man properties
			props->speed = 100;
			H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/man.png", A_Middle | A_Center));
			H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(CDT_Dynamic, 28, 15, 0x22, false));
			H3Handle cam = H3_Object_Create(props->scene, "camera", NULL);
			H3_Object_AddComponent(cam, CAMERACOMPONENT_CREATE(480, 256));
			H3Handle timer = H3_Object_Create(props->scene, "timer", NULL);
			H3_Object_AddComponent(timer, TIMER_CREATE(props->scene, cam, object));
			H3_Object_AddComponent(object, MOVEMENT_CREATE(props->scene, cam));
			H3_Object_AddComponent(object, SHOOT_CREATE(props->scene, choice));
			H3_Object_AddComponent(object, INVENTORYMAN_CREATE(props->scene, cam));
			H3_Object_Translate(object, 1500, 100);
			props->cam = cam;
			props->game = true;
		}
		else if (choice == 2)
		{
			//Woman properties
			props->speed = 75;
			H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/man.png", A_Middle | A_Center));
			H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(CDT_Dynamic, 15, 25, 0x22, false));
			H3Handle cam = H3_Object_Create(props->scene, "camera", NULL);
			H3_Object_AddComponent(cam, CAMERACOMPONENT_CREATE(480, 256));
			H3Handle timer = H3_Object_Create(props->scene, "timer", NULL);
			H3_Object_AddComponent(timer, TIMER_CREATE(props->scene, cam, object));
			H3_Object_AddComponent(object, MOVEMENT_CREATE(props->scene, cam));
			H3_Object_AddComponent(object, SHOOT_CREATE(props->scene, choice));
			H3_Object_AddComponent(object, INVENTORYWOMAN_CREATE(props->scene, cam));
			H3_Object_Translate(object, 1500, 100);
			props->cam = cam;
			props->game = true;
		}
	}


}

void* PLAYER_CreateProperties(H3Handle scene, H3Handle menu)
{
	PLAYER_Properties* properties = malloc(sizeof(PLAYER_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
	properties->speed = 0;
	properties->menu = menu;
	properties->game = false;

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(PLAYER, float, speed);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PLAYER, MENU_TYPEID, float, speed);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(PLAYER, MENU_TYPEID, H3Handle, cam);


