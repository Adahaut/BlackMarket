#include "controls.h"
#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include "malette.h"
#include "player.h"

typedef struct {
    H3Handle player;
    H3Handle texte;
    H3Handle cam;
    bool a;
    int take;
    int slots;
}controls_Properties;


void CONTROLS_Terminate(void* properties)
{
    free(properties);
}
void CONTROLS_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    controls_Properties* props = (controls_Properties*)properties;

    float px, py; // X and Y of the player
    static int x = 1500, y = 100; // Spawn X and Y of the object
    float delta_x, delta_y;
    static int compteur = 0;
    float x_cam, y_cam, w, h, vpw, vph; // X and Y from the camera
    H3_GetView(h3, &x_cam, &y_cam, &w, &h, &vpw, &vph);
    if (props->slots == 0) {
        if (props->a == false) { // Check if there's contact between object and player
            H3_Object_SetRenderOrder(props->texte, 0);
            if (props->take == 0) { // Check if the object is take
                H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
                H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &px, &py);
                H3_Object_SetTranslation(object, x, y);
                delta_x = px - x;
                delta_y = py - y;
                if (delta_x < 0 && delta_y < 0) { // Verify is player is next to the object to take it
                    if (delta_x < 0 && delta_x > -20 && delta_y < 0 && delta_y > -20) {
                        H3_Object_SetRenderOrder(object, 0);
                        H3_Object_SetTranslation(props->texte, x + 100, y - 20); // Write the name of the object next to him
                        H3_Object_SetRenderOrder(props->texte, 10);
                    }

                }
                else if (delta_x > 0 && delta_y < 0) { // Verify is player is next to the object to take it
                    if (delta_x > 0 && delta_x < 20 && delta_y < 0 && delta_y > -20) {
                        H3_Object_SetRenderOrder(object, 0);
                        H3_Object_SetTranslation(props->texte, x - 30, y - 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                    }
                }
                else if (delta_x < 0 && delta_y > 0) { // Verify is player is next to the object to take it
                    if (delta_x < 0 && delta_x > -20 && delta_y > 0 && delta_y < 20) {
                        H3_Object_SetRenderOrder(object, 0);
                        H3_Object_SetTranslation(props->texte, x + 100, y + 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                    }
                }
                else if (delta_x > 0 && delta_y > 0) { // Verify is player is next to the object to take it
                    if (delta_x > 0 && delta_x < 20 && delta_y > 0 && delta_y < 20) {
                        H3_Object_SetRenderOrder(object, 0);
                        H3_Object_SetTranslation(props->texte, x - 30, y + 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                    }
                }
            }
        }
    }
}



void CONTROLS_Collide(H3Handle object, SH3Collision collide)
{
    controls_Properties* props = (controls_Properties*)H3_Object_GetComponent(object, CONTROLS_TYPEID)->properties;
    if (collide.other)
        props->a = false;

}

void CONTROLS_NoCollide(H3Handle object, H3Handle other)
{
    controls_Properties* props = (controls_Properties*)H3_Object_GetComponent(object, CONTROLS_TYPEID)->properties;
    if (other == NULL)
        props->a = true;

}

void* CONTROLS_CreateProperties(H3Handle player, H3Handle texte)
{
    controls_Properties* properties = malloc(sizeof(controls_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
    properties->player = player;
    properties->a = true;
    properties->texte = texte;
    properties->cam = PLAYER_GetcamEx(properties->player);
    properties->slots = 0;
    properties->take = 0;
    return properties;
}
