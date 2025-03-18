#include "movements.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <components/spritecomponent.h>
#include <components/audiosourcecomponent.h>
#include "player.h"
#include "inventorywoman.h"

typedef struct
{
    H3Handle scene;
    H3Handle cam;
    H3Handle light;
    float vx;
    float vy;
} movement_Properties;

void movement_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    movement_Properties* props = (movement_Properties*)properties;

    int mx;
    int my;
    float px;
    float py;
    static int _time = 0;

    H3_Input_GetMousePos(h3, &mx, &my);
    H3_Transform_GetPosition(H3_Object_GetTransform(object), &px, &py);

    float speed = PLAYER_GetspeedEx(object);
    bool isinv = INVENTORYWOMAN_GetisinvEx(object);

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
    H3_Object_SetRotation(object, angle * H3_RAD2DEG + 90);

    //Camera's movements
    float finalCamX = min(max(px, w / 2), 3008 - (w / 2));
    float finalCamY = min(max(py, h / 2), 3008 - (h / 2));
    H3_Object_SetTranslation(props->cam, finalCamX, finalCamY);


    //Player's movements
    if (H3_Input_IsKeyDown(K_Q))
    {
        props->vx = -speed;
        props->vy = 0;
    }
    else if (H3_Input_IsKeyDown(K_Z))
    {
        props->vx = 0;
        props->vy = -speed;
    }
    else if (H3_Input_IsKeyDown(K_D))
    {
        props->vx = speed;
        props->vy = 0;
    }
    else if (H3_Input_IsKeyDown(K_S))
    {
        props->vx = 0;
        props->vy = speed;
    }
    else 
    {
        props->vx = 0;
        props->vy = 0;
    }
    //Sprint
    if (H3_Input_IsKeyDown(K_Shift)) {
        props->vx *= 1.5;
        props->vy *= 1.5;
    }
    //Stop the player when inventory is open
    if (isinv == true)
    {
        props->vx = 0;
        props->vy = 0;
    }
        H3_Object_SetVelocity(object, props->vx, props->vy);


}



void movement_Terminate(void* properties)
{
    free(properties);
}

void* movement_CreateProperties(H3Handle scene, H3Handle cam, H3Handle light)
{
    movement_Properties* properties = malloc(sizeof(movement_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

    properties->scene = scene;
    properties->cam = cam;
    properties->light = light;

    return properties;
}
