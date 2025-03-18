#include <iamove.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	H3Handle scene;
	H3Handle player;

} Iamovecomponent_Properties;

void Iamovecomponent_Terminate(void* properties)
{
	free(properties);
}

void Iamovecomponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	Iamovecomponent_Properties* props = (Iamovecomponent_Properties*)properties;


	// Ia movement

	float gspeed = 30;
	float vx, vy;

	H3_Object_GetVelocity(object, &vx, &vy);
	// poursuite de l'Ia

	float px, py, zx, zy;


	H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &px, &py);
	H3_Transform_GetPosition(H3_Object_GetTransform(object), &zx, &zy); // Get guard's pos

	float dx = zx - px;
	float dy = zy - py;

	float dist = sqrtf(dx * dx + dy * dy); // Get distance between both

	if (dist <= 200) { // chase

		H3_Object_SetVelocity(object, -dx / dist * 70, -dy / dist * 70);

	}
	else
	{
		static int time = 0;
		time++;
		if (time == 600) { // random move each 10 sec
			int d = rand() % 3;

			if (d == 0) {
				H3_Object_SetVelocity(object, vx, -1 * gspeed);
			}
			if (d == 1) {
				H3_Object_SetVelocity(object, -1 * gspeed, vy);
			}
			if (d == 2) {
				H3_Object_SetVelocity(object, vx, 1 * gspeed);
			}
			if (d == 3) {
				H3_Object_SetVelocity(object, 1 * gspeed, vy);
			}
			time = 0;
		}
	}

}


void Iamovecomponent_ColliderON(H3Handle object, SH3Collision collide)
{
	Iamovecomponent_Properties* props = (Iamovecomponent_Properties*)H3_Object_GetComponent(object, IAMOVECOMPONENT_TYPEID)->properties;
}

void* Iamovecomponent_CreateProperties(H3Handle scene, H3Handle player)
{
	Iamovecomponent_Properties* properties = malloc(sizeof(Iamovecomponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
	properties->player = player;

	return properties;
}