#include <ia.h>
#include <iamove.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	H3Handle scene;
	H3Handle player;

} IaComponent_Properties;

void IaComponent_Terminate(void* properties)
{
	free(properties);
}

void IaComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	IaComponent_Properties* props = (IaComponent_Properties*)properties;


	// AI spawn
    static float stime = 0;
    stime++;
    // Wave time
    if (stime == 0 || stime == 1 || stime == 7200 || stime == 7201 || stime == 14400 || stime == 14401 || stime == 21600 || stime == 21601 || stime == 28800 || stime == 28801 || stime == 36000 || stime == 36001 || stime == 43200 || stime == 43201 || stime == 50400 || stime == 50401 || stime == 57600 || stime == 57601 || stime == 64800 || stime == 64801 || stime == 72000 || stime == 72001 || stime == 79200 || stime == 79201) {

        static int numZ = 0;
        char buff[256];
        snprintf(buff, 256, "guard%d", ++numZ);


        int zax = rand() % 100; // random coordinate x
        int zay = rand() % 100; // random coordinate y

        H3Handle zomb = H3_Object_Create2(props->scene, buff, NULL, 8);
        H3_Object_EnablePhysics(zomb, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
        H3_Object_AddComponent(zomb, SPRITECOMPONENT_CREATE("assets/guard.png", 0x22));
        H3_Object_AddComponent(zomb, IAMOVECOMPONENT_CREATE(props->scene, props->player));
        H3_Object_SetTranslation(zomb, zax, zay);

    };
    
}

void IaComponent_ColliderON(H3Handle object, SH3Collision collide)
{
	IaComponent_Properties* props = (IaComponent_Properties*)H3_Object_GetComponent(object, IACOMPONENT_TYPEID)->properties;

}

void* IaComponent_CreateProperties(H3Handle scene, H3Handle player)
{
	IaComponent_Properties* properties = malloc(sizeof(IaComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
	properties->player = player;

	return properties;
}
