#include "monster.h"
#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>

typedef struct {
    H3Handle player;
    H3Handle texte;
    H3Handle cam;
    int take;
    int slots;
    bool collision;
}monster_Properties;


void MONSTER_Terminate(void* properties)
{
    free(properties);
}
void MONSTER_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    monster_Properties* props = (monster_Properties*)properties;

    float px, py;  // X and Y of the player
    static int x = 100, y = 2900; // Spawn X and Y of the object
    float delta_x, delta_y;
    static int compteur = 0;
    float x_cam, y_cam, w, h, vpw, vph;  // X and Y from the camera
    H3_GetView(h3, &x_cam, &y_cam, &w, &h, &vpw, &vph);
    if (props->slots == 0) {
        if (props->collision == true) {  // Check if there's contact between object and player
            H3_Object_SetRenderOrder(props->texte, 0);
            if (props->take == 0) {  // Check if the object is take
                H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
                H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &px, &py);
                H3_Object_SetTranslation(object, x, y);
                delta_x = px - x;
                delta_y = py - y;
                if (delta_x < 0 && delta_y < 0) {  // Verify is player is next to the object to take it
                    if (delta_x < 0 && delta_x > -20 && delta_y < 0 && delta_y > -20) {
                        H3_Object_SetRenderOrder(object, 10);  
                        H3_Object_SetTranslation(props->texte, x + 30, y - 20); // Write the name of the object next to him
                        H3_Object_SetRenderOrder(props->texte, 10);
                        if (H3_Input_IsMouseBtnPressed(MB_Left)) {  // Take the item
                            props->take = 1;
                        }
                    }
                    else {  // Flash the item
                        compteur = compteur + 1;
                        if (compteur == 100) {
                            H3_Object_SetRenderOrder(object, 10);
                        }
                        if (compteur == 150)
                        {
                            H3_Object_SetRenderOrder(object, 2);
                            compteur = 0;
                        }
                    }
                }
                else if (delta_x > 0 && delta_y < 0) {   // Verify is player is next to the object to take it
                    if (delta_x > 0 && delta_x < 20 && delta_y < 0 && delta_y > -20) {
                        H3_Object_SetRenderOrder(object, 10);
                        H3_Object_SetTranslation(props->texte, x - 30, y - 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                        if (H3_Input_IsMouseBtnPressed(MB_Left)) {
                            props->take = 1;
                        }
                    }
                    else {
                        compteur = compteur + 1;
                        if (compteur == 100) {
                            H3_Object_SetRenderOrder(object, 10);
                        }
                        if (compteur == 150)
                        {
                            H3_Object_SetRenderOrder(object, 2);
                            compteur = 0;
                        }
                    }
                }
                else if (delta_x < 0 && delta_y > 0) {   // Verify is player is next to the object to take it
                    if (delta_x < 0 && delta_x > -20 && delta_y > 0 && delta_y < 20) {
                        H3_Object_SetRenderOrder(object, 10);
                        H3_Object_SetTranslation(props->texte, x + 30, y + 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                        if (H3_Input_IsMouseBtnPressed(MB_Left)) {
                            props->take = 1;
                        }
                    }
                    else {
                        compteur = compteur + 1;
                        if (compteur == 100) {
                            H3_Object_SetRenderOrder(object, 10);
                        }
                        if (compteur == 150)
                        {
                            H3_Object_SetRenderOrder(object, 2);
                            compteur = 0;
                        }
                    }
                }
                else if (delta_x > 0 && delta_y > 0) {   // Verify is player is next to the object to take it
                    if (delta_x > 0 && delta_x < 20 && delta_y > 0 && delta_y < 20) {
                        H3_Object_SetRenderOrder(object, 10);
                        H3_Object_SetTranslation(props->texte, x - 30, y + 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                        if (H3_Input_IsMouseBtnPressed(MB_Left)) {
                            props->take = 1;
                        }
                    }
                    else {
                        compteur = compteur + 1;
                        if (compteur == 100) {
                            H3_Object_SetRenderOrder(object, 10);
                        }
                        if (compteur == 150)
                        {
                            H3_Object_SetRenderOrder(object, 2);
                            compteur = 0;
                        }
                    }
                }
                else {
                    compteur = compteur + 1;
                    if (compteur == 100) {
                        H3_Object_SetRenderOrder(object, 10);
                    }
                    if (compteur == 150)
                    {
                        H3_Object_SetRenderOrder(object, 2);
                        compteur = 0;
                    }
                }
            }
            else if (props->take == 1) {  // If the item is take
                H3_Object_DisablePhysics(object); // Disable collision
                H3_Object_Rotate(object, 90);
                H3_Object_SetTranslation(object, x_cam + 170, y_cam + 110); // place the item on the 1st slot
                H3_Object_SetRenderOrder(object, 40);
                if (H3_Input_IsMouseBtnPressed(MB_Middle)) {  // Drop the item on the player's x,y
                    H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &px, &py);
                    x = px;
                    y = py;
                    H3_Object_SetRenderOrder(object, 2);
                    H3_Object_SetTranslation(object, x, y);
                    H3Handle drop = H3_Sound_Load("assets/drop.wav"); // Play drop sound
                    H3_Sound_Play(drop, 1.0f, false);
                    props->take = 0;
                }
                props->slots = 1;
            }
        }
        else {
            H3_Object_SetRenderOrder(props->texte, 0);
            compteur = compteur + 1;
            if (compteur == 100) {
                H3_Object_SetRenderOrder(object, 10);
            }
            if (compteur == 150)
            {
                H3_Object_SetRenderOrder(object, 2);
                compteur = 0;
            }
        }
    }
    else if (props->slots == 1) {
        if (props->collision == true) {
            H3_Object_SetRenderOrder(props->texte, 0);
            if (props->take == 1) {
                H3_Object_DisablePhysics(object);
                H3_Object_Rotate(object, 90);
                H3_Object_SetTranslation(object, x_cam + 170, y_cam + 110);
                H3_Object_SetRenderOrder(object, 40);
                if (H3_Input_IsMouseBtnPressed(MB_Right)) {
                    H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &px, &py);
                    x = px;
                    y = py;
                    H3_Object_SetRenderOrder(object, 2);
                    H3_Object_SetTranslation(object, x, y);
                    H3Handle drop = H3_Sound_Load("assets/drop.wav");
                    H3_Sound_Play(drop, 1.0f, false);
                    props->take = 0;
                    props->slots = 0;
                }
            }
        }
        else {
            H3_Object_SetRenderOrder(props->texte, 0);
            compteur = compteur + 1;
            if (compteur == 100) {
                H3_Object_SetRenderOrder(object, 10);
            }
            if (compteur == 150)
            {
                H3_Object_SetRenderOrder(object, 2);
                compteur = 0;
            }
        }
    }
    else if (props->slots == 2) {
        if (props->collision == true) {
            H3_Object_SetRenderOrder(props->texte, 0);
            if (props->take == 0) {
                H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
                H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &px, &py);
                H3_Object_SetTranslation(object, x, y);
                delta_x = px - x;
                delta_y = py - y;
                if (delta_x < 0 && delta_y < 0) {
                    if (delta_x < 0 && delta_x > -20 && delta_y < 0 && delta_y > -20) {
                        H3_Object_SetRenderOrder(object, 10);
                        H3_Object_SetTranslation(props->texte, x + 30, y - 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                        if (H3_Input_IsMouseBtnPressed(MB_Left)) {
                            props->take = 1;
                        }
                    }
                    else {
                        compteur = compteur + 1;
                        if (compteur == 100) {
                            H3_Object_SetRenderOrder(object, 10);
                        }
                        if (compteur == 150)
                        {
                            H3_Object_SetRenderOrder(object, 2);
                            compteur = 0;
                        }
                    }
                }
                else if (delta_x > 0 && delta_y < 0) {
                    if (delta_x > 0 && delta_x < 20 && delta_y < 0 && delta_y > -20) {
                        H3_Object_SetRenderOrder(object, 10);
                        H3_Object_SetTranslation(props->texte, x - 30, y - 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                        if (H3_Input_IsMouseBtnPressed(MB_Left)) {
                            props->take = 1;
                        }
                    }
                    else {
                        compteur = compteur + 1;
                        if (compteur == 100) {
                            H3_Object_SetRenderOrder(object, 10);
                        }
                        if (compteur == 150)
                        {
                            H3_Object_SetRenderOrder(object, 2);
                            compteur = 0;
                        }
                    }
                }
                else if (delta_x < 0 && delta_y > 0) {
                    if (delta_x < 0 && delta_x > -20 && delta_y > 0 && delta_y < 20) {
                        H3_Object_SetRenderOrder(object, 10);
                        H3_Object_SetTranslation(props->texte, x + 30, y + 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                        if (H3_Input_IsMouseBtnPressed(MB_Left)) {
                            props->take = 1;
                        }
                    }
                    else {
                        compteur = compteur + 1;
                        if (compteur == 100) {
                            H3_Object_SetRenderOrder(object, 10);
                        }
                        if (compteur == 150)
                        {
                            H3_Object_SetRenderOrder(object, 2);
                            compteur = 0;
                        }
                    }
                }
                else if (delta_x > 0 && delta_y > 0) {
                    if (delta_x > 0 && delta_x < 20 && delta_y > 0 && delta_y < 20) {
                        H3_Object_SetRenderOrder(object, 10);
                        H3_Object_SetTranslation(props->texte, x - 30, y + 20);
                        H3_Object_SetRenderOrder(props->texte, 10);
                        if (H3_Input_IsMouseBtnPressed(MB_Left)) {
                            props->take = 1;
                        }
                    }
                    else {
                        compteur = compteur + 1;
                        if (compteur == 100) {
                            H3_Object_SetRenderOrder(object, 10);
                        }
                        if (compteur == 150)
                        {
                            H3_Object_SetRenderOrder(object, 2);
                            compteur = 0;
                        }
                    }
                }
                else {
                    compteur = compteur + 1;
                    if (compteur == 100) {
                        H3_Object_SetRenderOrder(object, 10);
                    }
                    if (compteur == 150)
                    {
                        H3_Object_SetRenderOrder(object, 2);
                        compteur = 0;
                    }
                }
            }
            else if (props->take == 1) {
                H3_Object_DisablePhysics(object);
                H3_Object_Rotate(object, 90);
                H3_Object_SetTranslation(object, x_cam + 200, y_cam + 110);
                H3_Object_SetRenderOrder(object, 40);
                if (H3_Input_IsMouseBtnPressed(MB_Right)) {
                    H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &px, &py);
                    x = px;
                    y = py;
                    H3_Object_SetRenderOrder(object, 2);
                    H3_Object_SetTranslation(object, x, y);
                    H3Handle drop = H3_Sound_Load("assets/drop.wav");
                    H3_Sound_Play(drop, 1.0f, false);
                    props->take = 0;
                    props->slots = 1;
                }
            }
        }
        else {
            H3_Object_SetRenderOrder(props->texte, 0);
            compteur = compteur + 1;
            if (compteur == 100) {
                H3_Object_SetRenderOrder(object, 10);
            }
            if (compteur == 150)
            {
                H3_Object_SetRenderOrder(object, 2);
                compteur = 0;
            }
        }
    }
}
void MONSTER_Collide(H3Handle object, SH3Collision collide)
{
    monster_Properties* props = (monster_Properties*)H3_Object_GetComponent(object, MONSTER_TYPEID)->properties;
    if (collide.other)
        props->collision = true;

}

void MONSTER_NoCollide(H3Handle object, H3Handle other)
{
    monster_Properties* props = (monster_Properties*)H3_Object_GetComponent(object, MONSTER_TYPEID)->properties;
    if (other == NULL)
        props->collision = false;

}

void* MONSTER_CreateProperties(H3Handle player, H3Handle texte)
{
    monster_Properties* properties = malloc(sizeof(monster_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
    properties->player = player;
    properties->collision = false;
    properties->texte = texte;
    properties->cam = PLAYER_GetcamEx(properties->player);
    properties->slots = 0;
    properties->take = 0;

    return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(monster, MONSTER_TYPEID, int, slots);

