#include <h3.h>
#include <components/cameracomponent.h>
#include <components/maplayercomponent.h>
#include <components/spritecomponent.h>
#include <components/textcomponent.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "movements.h"
#include "monster.h"
#include "timer.h"
#include "menu.h"
#include "player.h"
#include "ia.h"
#include "malette.h"
#include "cle.h"
#include "badge.h"
#include "slots.h"
#include "controls.h"

#ifndef NDEBUG
# pragma comment(lib, "h3-s-d.lib")
#else // !NDEBUG
# pragma comment(lib, "h3-s.lib")
#endif // !NDEBUG

int main(int argc, char** argv)
{
    H3Handle h3 = H3_Init((SH3InitParams) {
        .width = 1920,
            .height = 1080,
            .fullscreen = false,
            .windowTitle = "Black Market"
    });

    srand(time(NULL));

    bool running = true;

    H3Handle scn = H3_Scene_Create(h3, false);
    H3Handle menu = H3_Object_Create2(scn, "menu", NULL, 20);
    H3_Object_AddComponent(menu, SPRITECOMPONENT_CREATE("assets/menu.png", A_Middle | A_Center));
    H3_Object_Translate(menu, 960, 540);
    H3Handle menusound = H3_Sound_Load("assets/menusound.wav");
    H3_Sound_Play(menusound, 1.0f, true);
    H3Handle manskills = H3_Object_Create2(scn, "manskills",NULL, 21);
    H3Handle womanskills = H3_Object_Create2(scn, "womanskills",NULL, 21);
    H3_Object_AddComponent(manskills, SPRITECOMPONENT_CREATE("assets/manskills.png", A_Middle | A_Center));
    H3_Object_AddComponent(womanskills, SPRITECOMPONENT_CREATE("assets/womanskills.png", A_Middle | A_Center));
    H3_Object_Translate(manskills, -960, -540);
    H3_Object_Translate(womanskills, -960, -540);
    H3Handle animbutt1 = H3_Object_Create2(scn, "anim1", NULL, 22);
    H3Handle animbutt5 = H3_Object_Create2(scn, "anim5", NULL, 22);
    H3_Object_AddComponent(animbutt1, SPRITECOMPONENT_CREATE("assets/animbutt.png", A_Middle | A_Center));
    H3_Object_AddComponent(animbutt5, SPRITECOMPONENT_CREATE("assets/animbutt.png", A_Middle | A_Center));
    H3_Object_Translate(animbutt1, -960, -540);
    H3_Object_Translate(animbutt5, -960, -540);
    H3_Object_AddComponent(menu, MENU_CREATE(menusound, scn, manskills, womanskills, animbutt1, animbutt5));


    H3Handle map = H3_Map_Load("assets/map.tmx");
    H3Handle Map = H3_Map_Load("assets/map.tmx");
    H3Handle MapObject = H3_Object_Create(scn, "mapobject", NULL);
    H3_Object_SetRenderOrder(MapObject, 1);
    H3Handle MapBackGround = H3_Object_Create(scn, "mapbackground", NULL);
    H3_Object_SetRenderOrder(MapBackGround, 2);
    H3_Object_AddComponent(MapBackGround, (MAPLAYERCOMPONENT_CREATE(Map, "Terrain")));
    H3_Object_AddComponent(MapObject, (MAPLAYERCOMPONENT_CREATE(Map, "Collisions")));
    H3_Map_RegisterObjectLayerForPhysicsInScene(scn, Map, "Collisions");


    int choice;
    MENU_Getchoice(&choice);

    H3Handle player = H3_Object_Create2(scn, "player", NULL, 8);
    H3_Object_AddComponent(player, PLAYER_CREATE(scn, menu));

    H3Handle texte = H3_Object_Create(scn, "texte", NULL);
    H3_Object_AddComponent(texte, SPRITECOMPONENT_CREATE("assets/monster_txt.png", A_Middle | A_Center));

    H3Handle ia = H3_Object_Create(scn, "ia", NULL);
    H3_Object_AddComponent(ia, IACOMPONENT_CREATE(scn, player));
    H3Handle texte_monster = H3_Object_Create(scn, "texte_monster", NULL);
    H3_Object_AddComponent(texte_monster, SPRITECOMPONENT_CREATE("assets/monster_txt.png", A_Middle | A_Center));

    H3Handle monster = H3_Object_Create(scn, "monster", NULL);
    H3_Object_AddComponent(monster, SPRITECOMPONENT_CREATE("assets/monster_spr.png", A_Middle | A_Center));
    H3_Object_EnablePhysics(monster, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
    H3_Object_AddComponent(monster, MONSTER_CREATE(player, texte_monster));

    H3Handle texte_malette = H3_Object_Create(scn, "texte_malette", NULL);
    H3_Object_AddComponent(texte_malette, SPRITECOMPONENT_CREATE("assets/malette_txt.png", A_Middle | A_Center));

    H3Handle malette = H3_Object_Create(scn, "malette", NULL);
    H3_Object_AddComponent(malette, SPRITECOMPONENT_CREATE("assets/malette.png", A_Middle | A_Center));
    H3_Object_EnablePhysics(malette, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
    H3_Object_AddComponent(malette, MALETTE_CREATE(player, texte_malette));

    H3Handle texte_cle = H3_Object_Create(scn, "texte_cle", NULL);
    H3_Object_AddComponent(texte_cle, SPRITECOMPONENT_CREATE("assets/cle_txt.png", A_Middle | A_Center));

    H3Handle cle = H3_Object_Create(scn, "cle", NULL);
    H3_Object_AddComponent(cle, SPRITECOMPONENT_CREATE("assets/cle.png", A_Middle | A_Center));
    H3_Object_EnablePhysics(cle, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
    H3_Object_AddComponent(cle, CLE_CREATE(player, texte_cle));

    H3Handle texte_badge = H3_Object_Create(scn, "texte_badge", NULL);
    H3_Object_AddComponent(texte_badge, SPRITECOMPONENT_CREATE("assets/badge_txt.png", A_Middle | A_Center));

    H3Handle badge = H3_Object_Create(scn, "badge", NULL);
    H3_Object_AddComponent(badge, SPRITECOMPONENT_CREATE("assets/badge.png", A_Middle | A_Center));
    H3_Object_EnablePhysics(badge, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
    H3_Object_AddComponent(badge, BADGE_CREATE(player, texte_badge));

    H3Handle slots = H3_Object_Create(scn, "slots", NULL);
    H3_Object_AddComponent(slots, SLOTS_CREATE(monster, badge, cle, malette));

    H3Handle texte_controls = H3_Object_Create(scn, "texte_controls", NULL);
    H3_Object_AddComponent(texte_controls, SPRITECOMPONENT_CREATE("assets/controls.png", A_Middle | A_Center));

    H3Handle controls = H3_Object_Create(scn, "controls", NULL);
    H3_Object_AddComponent(controls, SPRITECOMPONENT_CREATE("assets/badge.png", A_Middle | A_Center));
    H3_Object_EnablePhysics(controls, H3_BOX_COLLIDER(CDT_Dynamic, 10, 10, 0x22, false));
    H3_Object_AddComponent(controls, CONTROLS_CREATE(player, texte_controls));



    do {

        running = H3_DoFrame(h3, scn);
    } while (running);


    H3_Object_Destroy(MapObject, true);
    H3_Object_Destroy(MapBackGround, true);

    H3_Scene_Destroy(scn);

    H3_Terminate(&h3);


    return 0;
}
