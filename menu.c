#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <math.h>


typedef struct {
	H3Handle scene;
	H3Handle texture1;
	H3Handle texture2;
	H3Handle snd;
	H3Handle cache;
	int choice;
	H3Handle man;
	H3Handle woman;
	H3Handle a1;
	H3Handle a2;
	H3Handle a3;
	H3Handle a4;
	H3Handle a5;
	int posx;
	int posy;
	int language;
	bool iscache;
}MENU_Properties;


void MENU_Terminate(void* properties)
{
	free(properties);
}


void MENU_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	MENU_Properties* props = (MENU_Properties*)properties;

	int mx, my;
	H3_Input_GetMousePos(h3, &mx, &my);
	static int destcache = 0;
	if (props->iscache == true) {
		//Mask gender buttons when no language is selected
		printf("c");
		H3Handle cache = H3_Object_Create2(props->scene, "cache", NULL, 30);
		H3_Object_AddComponent(cache, SPRITECOMPONENT_CREATE("assets/cache.png", A_Middle | A_Center));
		H3_Object_Translate(cache, 570, 525);
		props->cache = cache;
		props->iscache = false;
	}

	if (props->language != NULL && destcache == 0) {
		//Unmask gender
		H3_Object_Destroy(props->cache, false);
		destcache = 1;
	}

	if (mx > 382 && mx < 763 && my > 390 && my < 525 && props->language != NULL) {
		//Show man's skills
		H3_Object_SetTranslation(props->man, 1100, 550);
		//An animation 
		H3_Object_SetTranslation(props->a1, 575, 460);
		if (H3_Input_IsMouseBtnPressed(MB_Left) && props->language != NULL) {
			//The choice is the man
			props->choice = 1;
			H3_Object_Destroy(object, false);
			H3_Object_Destroy(props->man, false);
			H3_Object_Destroy(props->woman, false);
			H3_Object_Destroy(props->a1, false);
			H3_Object_Destroy(props->a5, false);
			H3_Sound_Stop(props->snd);
		}
	}
	else if (mx > 382 && mx < 763 && my > 560 && my < 696 && props->language != NULL) {
		//Show woman's skills
		H3_Object_SetTranslation(props->woman, 1100, 550);
		//An animation
		H3_Object_SetTranslation(props->a1, 575, 625);

		if (H3_Input_IsMouseBtnPressed(MB_Left) && props->language != NULL) {
			//The choice is the woman
			props->choice = 2;
			H3_Object_Destroy(object, false);
			H3_Object_Destroy(props->woman, false);
			H3_Object_Destroy(props->man, false);
			H3_Object_Destroy(props->a1, false);
			H3_Object_Destroy(props->a5, false);
			H3_Sound_Stop(props->snd);
		}
	}
	else if (mx > 187 && mx < 569 && my > 710 && my < 845) {
		//An animation
		H3_Object_SetTranslation(props->a5, 380, 775);
		if (H3_Input_IsMouseBtnPressed(MB_Left)) {
			//The choice is french
			props->posx = 380;
			props->posy = 775;
			props->language = 1;
		}
	}
	else if (mx > 587 && mx < 956 && my > 710 && my < 845) {
		//An animation
		H3_Object_SetTranslation(props->a5, 773, 775);
		if (H3_Input_IsMouseBtnPressed(MB_Left)) {
			//The choice is english
			props->posx = 773;
			props->posy = 775;
			props->language = 2;
		}
	}
	else if (mx > 464 && mx < 678 && my > 895 && my < 991) {
		//Exit
		if (H3_Input_IsMouseBtnPressed(MB_Left))
			H3_Terminate(&h3);
	}
	else {
		//Hide animations and skills
		H3_Object_SetTranslation(props->woman, -400, -550);
		H3_Object_SetTranslation(props->man, -400, -400);
		H3_Object_SetTranslation(props->a1, -960, -540);
		H3_Object_SetTranslation(props->a5, props->posx, props->posy);
	}
	

}

void* MENU_CreateProperties(H3Handle snd, H3Handle scene, H3Handle man, H3Handle woman, H3Handle a1, H3Handle a5)
{
	MENU_Properties* properties = malloc(sizeof(MENU_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->snd = snd;
	properties->scene = scene;
	properties->man = man;
	properties->woman = woman;
	properties->choice = 0;
	properties->a1 = a1;
	properties->a5 = a5;
	properties->posx = -1000;
	properties->posy = -1000;
	properties->language = NULL;
	properties->iscache = true;

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(MENU, int, choice);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MENU, MENU_TYPEID, int, choice);
