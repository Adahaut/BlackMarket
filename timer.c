#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <components/audiosourcecomponent.h>

typedef struct {
	H3Handle scene;
	H3Handle player;
	H3Handle cam;
	H3Handle light;
	H3Handle clock;
	H3Handle bar;
	int tiredness;
	int buff;
	bool drink;
}TIMER_Properties;


void TIMER_Terminate(void* properties)
{
	free(properties);
}
void TIMER_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	TIMER_Properties* props = (TIMER_Properties*)properties;

	static int sec = 0;

	float px, py;
	int mx, my;
	H3_Input_GetMousePos(h3, &mx, &my);

	H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &px, &py);
	float x, y, w, h, vpw, vph;
	H3_GetView(h3, &x, &y, &w, &h, &vpw, &vph);
	float x0 = x - w / 2;
	float x1 = x + w / 2;
	float y0 = y - h / 2;
	float y1 = y + h / 2;
	float mx01 = mx / vpw;
	float my01 = my / vph;
	float mxScene = x0 + (x1 - x0) * mx01;
	float myScene = y0 + (y1 - y0) * my01;

	float dx = mxScene - px;
	float dy = myScene - py;
	float angle = atan2(dy, dx);
	float dist = sqrtf(dx * dx + dy * dy);


	//Set the darkness with the time 
	if (sec == 0)
	{
		H3Handle light = H3_Object_Create2(props->scene, "light", NULL, 9);

		H3_Object_AddComponent(light, SPRITECOMPONENT_CREATE("assets/light.png", A_Middle | A_Center));
		props->light = light;


		//clock UI
		H3Handle clock1 = H3_Object_Create2(props->scene, "clock1", props->cam, 10);
		H3_Object_AddComponent(clock1, SPRITECOMPONENT_CREATE("assets/clock/clock1.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock1, -243, -131);
		props->clock = clock1;

		sec++;
	}
	else if (sec == 14400)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light2 = H3_Object_Create2(props->scene, "light2", NULL, 9);

		H3_Object_AddComponent(light2, SPRITECOMPONENT_CREATE("assets/light2.png", A_Middle | A_Center));
		props->light = light2;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock2 = H3_Object_Create2(props->scene, "clock2", props->cam, 10);
		H3_Object_AddComponent(clock2, SPRITECOMPONENT_CREATE("assets/clock/clock2.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock2, -243, -131);
		props->clock = clock2;

		sec++;
	}
	else if (sec == 21600)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light3 = H3_Object_Create2(props->scene, "light3", NULL, 9);

		H3_Object_AddComponent(light3, SPRITECOMPONENT_CREATE("assets/light3.png", A_Middle | A_Center));
		props->light = light3;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock3 = H3_Object_Create2(props->scene, "clock3", props->cam, 10);
		H3_Object_AddComponent(clock3, SPRITECOMPONENT_CREATE("assets/clock/clock3.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock3, -243, -131);
		props->clock = clock3;



		sec++;
	}
	else if (sec == 28800)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light4 = H3_Object_Create2(props->scene, "light4", NULL, 9);

		H3_Object_AddComponent(light4, SPRITECOMPONENT_CREATE("assets/light4.png", A_Middle | A_Center));
		props->light = light4;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock4 = H3_Object_Create2(props->scene, "clock4", props->cam, 10);
		H3_Object_AddComponent(clock4, SPRITECOMPONENT_CREATE("assets/clock/clock4.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock4, -243, -131);
		props->clock = clock4;


		sec++;
	}
	else if (sec == 36000)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light5 = H3_Object_Create2(props->scene, "light5", NULL, 9);

		H3_Object_AddComponent(light5, SPRITECOMPONENT_CREATE("assets/light5.png", A_Middle | A_Center));
		props->light = light5;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock5 = H3_Object_Create2(props->scene, "clock5", props->cam, 10);
		H3_Object_AddComponent(clock5, SPRITECOMPONENT_CREATE("assets/clock/clock5.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock5, -243, -131);
		props->clock = clock5;


		sec++;
	}
	else if (sec == 43200)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light6 = H3_Object_Create2(props->scene, "light6", NULL, 9);

		H3_Object_AddComponent(light6, SPRITECOMPONENT_CREATE("assets/light6.png", A_Middle | A_Center));
		props->light = light6;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock6 = H3_Object_Create2(props->scene, "clock6", props->cam, 10);
		H3_Object_AddComponent(clock6, SPRITECOMPONENT_CREATE("assets/clock/clock6.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock6, -243, -131);
		props->clock = clock6;


		sec++;
	}
	else if (sec == 50400)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light7 = H3_Object_Create2(props->scene, "light7", NULL, 9);

		H3_Object_AddComponent(light7, SPRITECOMPONENT_CREATE("assets/light7.png", A_Middle | A_Center));
		props->light = light7;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock7 = H3_Object_Create2(props->scene, "clock7", props->cam, 10);
		H3_Object_AddComponent(clock7, SPRITECOMPONENT_CREATE("assets/clock/clock7.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock7, -243, -131);
		props->clock = clock7;


		sec++;
	}
	else if (sec == 57200)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light8 = H3_Object_Create2(props->scene, "light8", NULL, 9);

		H3_Object_AddComponent(light8, SPRITECOMPONENT_CREATE("assets/light8.png", A_Middle | A_Center));
		props->light = light8;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock8 = H3_Object_Create2(props->scene, "clock8", props->cam, 10);
		H3_Object_AddComponent(clock8, SPRITECOMPONENT_CREATE("assets/clock/clock8.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock8, -243, -131);
		props->clock = clock8;


		sec++;
	}
	else if (sec == 64400)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light9 = H3_Object_Create2(props->scene, "light9", NULL, 9);

		H3_Object_AddComponent(light9, SPRITECOMPONENT_CREATE("assets/light9.png", A_Middle | A_Center));
		props->light = light9;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock9 = H3_Object_Create2(props->scene, "clock9", props->cam, 10);
		H3_Object_AddComponent(clock9, SPRITECOMPONENT_CREATE("assets/clock/clock9.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock9, -243, -131);
		props->clock = clock9;


		sec++;
	}
	else if (sec == 71600)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light10 = H3_Object_Create2(props->scene, "light10", NULL, 9);

		H3_Object_AddComponent(light10, SPRITECOMPONENT_CREATE("assets/light10.png", A_Middle | A_Center));
		props->light = light10;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock10 = H3_Object_Create2(props->scene, "clock10", props->cam, 10);
		H3_Object_AddComponent(clock10, SPRITECOMPONENT_CREATE("assets/clock/clock10.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock10, -243, -131);
		props->clock = clock10;


		sec++;
	}
	else if (sec == 78800)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light11 = H3_Object_Create2(props->scene, "light11", NULL, 9);

		H3_Object_AddComponent(light11, SPRITECOMPONENT_CREATE("assets/light11.png", A_Middle | A_Center));
		props->light = light11;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock11 = H3_Object_Create2(props->scene, "clock11", props->cam, 10);
		H3_Object_AddComponent(clock11, SPRITECOMPONENT_CREATE("assets/clock/clock11.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock11, -243, -131);
		props->clock = clock11;


		sec++;
	}
	else if (sec == 86000)
	{
		H3_Object_Destroy(props->light, false);
		H3Handle bong = H3_Sound_Load("assets/bong.wav");
		H3_Sound_Play(bong, 1.0f, false);
		H3Handle light12 = H3_Object_Create2(props->scene, "light12", NULL, 9);

		H3_Object_AddComponent(light12, SPRITECOMPONENT_CREATE("assets/light12.png", A_Middle | A_Center));
		props->light = light12;

		props->tiredness += 50;

		//clock UI
		H3_Object_Destroy(props->clock, false);
		H3Handle clock12 = H3_Object_Create2(props->scene, "clock12", props->cam, 10);
		H3_Object_AddComponent(clock12, SPRITECOMPONENT_CREATE("assets/clock/clock12.png", A_Top | A_Left));
		H3_Object_SetTranslation(clock12, -243, -131);
		props->clock = clock12;


		sec++;
	}
	H3_Object_SetRotation(props->light, angle * H3_RAD2DEG + 90);
	H3_Object_SetTranslation(props->light, px, py);
	sec++;




	//Set the tiredness bar and show it
	if (props->tiredness == 0 && (props->buff == 0 || props->drink == true)) {


		H3Handle tirednessbar = H3_Object_Create2(props->scene, "tiredness", props->cam, 32);
		H3_Object_AddComponent(tirednessbar, SPRITECOMPONENT_CREATE("assets/tired1.png", A_Middle | A_Center));
		props->bar = tirednessbar;
		props->buff = 1;
		props->drink = false;
	}
	else if (props->tiredness == 50 && (props->buff == 1 || props->drink == true)) {

		H3_Object_Destroy(props->bar, false);
		H3Handle tirednessbar2 = H3_Object_Create2(props->scene, "tiredness2", props->cam, 32);
		H3_Object_AddComponent(tirednessbar2, SPRITECOMPONENT_CREATE("assets/tired2.png", A_Middle | A_Center));
		props->bar = tirednessbar2;
		props->buff = 2;
		props->drink = false;

	}

	else if (props->tiredness == 100 && (props->buff == 2 || props->drink == true)) {

		H3_Object_Destroy(props->bar, false);
		H3Handle tirednessbar3 = H3_Object_Create2(props->scene, "tiredness3", props->cam, 32);
		H3_Object_AddComponent(tirednessbar3, SPRITECOMPONENT_CREATE("assets/tired3.png", A_Middle | A_Center));
		props->bar = tirednessbar3;
		props->buff = 3;
		props->drink = false;
	}

	else if (props->tiredness == 150 && (props->buff == 3 || props->drink == true)) {

		H3_Object_Destroy(props->bar, false);
		H3Handle tirednessbar4 = H3_Object_Create2(props->scene, "tiredness4", props->cam, 32);
		H3_Object_AddComponent(tirednessbar4, SPRITECOMPONENT_CREATE("assets/tired4.png", A_Middle | A_Center));
		props->bar = tirednessbar4;
		props->buff = 4;
		props->drink = false;

	}
	else if (props->tiredness == 200 && (props->buff == 4 || props->drink == true)) {

		H3_Object_Destroy(props->bar, false);
		H3Handle tirednessbar5 = H3_Object_Create2(props->scene, "tiredness5", props->cam, 32);
		H3_Object_AddComponent(tirednessbar5, SPRITECOMPONENT_CREATE("assets/tired5.png", A_Middle | A_Center));
		props->bar = tirednessbar5;
		props->buff = 5;
		props->drink = false;

	}
	else if (props->tiredness == 250 && (props->buff == 5 || props->drink == true)) {

		H3_Object_Destroy(props->bar, false);
		H3Handle tirednessbar6 = H3_Object_Create2(props->scene, "tiredness6", props->cam, 32);
		H3_Object_AddComponent(tirednessbar6, SPRITECOMPONENT_CREATE("assets/tired6.png", A_Middle | A_Center));
		props->bar = tirednessbar6;
		props->buff = 6;
		props->drink = false;
	}

	H3_Object_SetRotation(props->bar, -90);
	H3_Object_SetTranslation(props->bar, 225, 70);
}



void* TIMER_CreateProperties(H3Handle scene, H3Handle cam, H3Handle player)
{
	TIMER_Properties* properties = malloc(sizeof(TIMER_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->player = player;
	properties->scene = scene;
	properties->cam = cam;
	properties->tiredness = 0;
	properties->buff = 0;

	return properties;
}