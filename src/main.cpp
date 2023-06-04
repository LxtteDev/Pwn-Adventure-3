#include <memory>
#include <iostream>
#include <dlfcn.h>
#include "libGameLogic.h"

/*
Default Walk Speed: 200

*/

void World::Tick(float t) { // Run every frame
    ClientWorld* w = *(ClientWorld**)dlsym(RTLD_NEXT, "GameWorld"); // Cast void* to ClientWorld*

    IPlayer* iplayer = w->m_activePlayer.m_object; // Get active player
    Player* player = ((Player*)(iplayer)); // Convert IPlayer to Player

    // Sprint/Speed hack
}