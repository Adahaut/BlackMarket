#include <player.h>
#include <shoot.h>
#include <components/spritecomponent.h>
#include <components/cameracomponent.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	H3Handle scene;
	int choice;
	int laserIndex;
} Shoot_Properties;

void Shoot_Terminate(void* properties)
{
	free(properties);
}

void Shoot_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	Shoot_Properties* props = (Shoot_Properties*)properties;

	// Rotation du player
	float px;
	float py;
	H3_Transform_GetPosition(H3_Object_GetTransform(object), &px, &py);	// recuperation of the player's position

	int mouseX;
	int mouseY;
	H3_Input_GetMousePos(h3, &mouseX, &mouseY);	// start of recuperation of the mouse's position
	float vx, vy, vw, vh, vpw, vph;

	H3_GetView(h3, &vx, &vy, &vw, &vh, &vpw, &vph);
	float vt = vy - 0.5f * vh;
	float vb = vy + 0.5f * vh;
	float vl = vx - 0.5f * vw;
	float vr = vx + 0.5f * vw;

	float mx = ((((float)mouseX) / vpw) - 0.5f) * vw + vx;
	float my = ((((float)mouseY) / vph) - 0.5f) * vh + vy;

	float dx = mx - px;
	float dy = my - py;	// end of recuperation of the mouse's position

	float distance = sqrtf(dx * dx + dy * dy);	//calculates distance between the mouse and the player
	float angle = atan2f(dy, dx);	//calculates angle between the mouse and the player



	//Spawn du laser

	static int cd = 600; //initialization of the cooldown
	cd++;
	if (H3_Input_IsKeyPressed(K_Space)) {	// Shoot
		if (cd >= 600)
		{

			float Speed = 150;

			char laser[256];
			float laserX = 0, laserY = 0;
			bool launch = false;

			snprintf(laser, 256, "laser_%d ", props->laserIndex++);
			H3Handle bullet = H3_Object_Create2(props->scene, laser, NULL, 3);
			if (props->choice == 1) { H3_Object_AddComponent(bullet, SPRITECOMPONENT_CREATE("assets/keyboard.png", 0x22));};
			if (props->choice == 2) { H3_Object_AddComponent(bullet, SPRITECOMPONENT_CREATE("assets/krokmou.png", 0x22));};
			H3_Object_EnablePhysics(bullet, H3_BOX_COLLIDER(CDT_Dynamic, 4, 10, A_Center | A_Bottom, false));
			H3_Object_SetTranslation(bullet, px, py);
			H3_Object_SetVelocity(bullet, Speed * dx / distance, Speed * dy / distance);
			H3_Object_Rotate(bullet, angle * H3_RAD2DEG + 90);

			cd = 0;	// 10s of CoolDown
		}



	}

}

void* Shoot_CreateProperties(H3Handle scene, int choice)
{
	Shoot_Properties* properties = malloc(sizeof(Shoot_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
	properties->choice = choice;

	return properties;
}
