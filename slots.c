#include "badge.h"
#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include "malette.h"
#include "cle.h"
#include "monster.h"
#include "slots.h"

typedef struct {
    H3Handle monster;
    H3Handle badge;
    H3Handle cle;
    H3Handle malette;
    int slots1;
    int slots2;
    int slots3;
    int slots4;
}slots_Properties;


void SLOTS_Terminate(void* properties)
{
    free(properties);
}

void SLOTS_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    slots_Properties* props = (slots_Properties*)properties;

     // Get the slots of all item

    props->slots1 = malette_GetslotsEx(props->malette);
    props->slots2 = badge_GetslotsEx(props->badge);
    props->slots3 = cle_GetslotsEx(props->cle);
    props->slots4 = monster_GetslotsEx(props->monster);
    if (props->slots1 == 1) {
        malette_SetslotsEx(props->malette, 2);
        badge_SetslotsEx(props->badge, 0);
        cle_SetslotsEx(props->cle, 0);
        monster_SetslotsEx(props->monster, 0);
    }
    else if (props->slots2 == 1) {
        malette_SetslotsEx(props->malette, 0);
        badge_SetslotsEx(props->badge, 2);
        cle_SetslotsEx(props->cle, 0);
        monster_SetslotsEx(props->monster, 0);
    }
    else if (props->slots3 == 1) {
        malette_SetslotsEx(props->malette, 0);
        badge_SetslotsEx(props->badge, 0);
        cle_SetslotsEx(props->cle, 2);
        monster_SetslotsEx(props->monster, 0);
    }
    else if (props->slots4 == 1) {
        malette_SetslotsEx(props->malette, 0);
        badge_SetslotsEx(props->badge, 0);
        cle_SetslotsEx(props->cle, 0);
        monster_SetslotsEx(props->monster, 2);
    }
}


void* SLOTS_CreateProperties(H3Handle monster, H3Handle badge, H3Handle cle, H3Handle malette)
{
    slots_Properties* properties = malloc(sizeof(slots_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
    properties->monster = monster;
    properties->badge = badge;
    properties->cle = cle;
    properties->malette = malette;
}