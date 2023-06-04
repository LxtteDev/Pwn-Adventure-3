#include <memory>
#include <iostream>
#include <dlfcn.h>
#include <X11/Xlib.h>
#include "libGameLogic.h"

/*
Default Walk Speed: 200
Default Jump Speed: 420
*/

/* By chikadance on StackOverflow
   https://stackoverflow.com/questions/18281412/check-keypress-in-c-on-linux */
bool isKeyPressed(KeySym ks) { // Key codes can be found at https://fossies.org/linux/tk/xlib/X11/keysymdef.h
    Display *dpy = XOpenDisplay(":0");
    char keys_return[32];
    XQueryKeymap(dpy, keys_return);
    KeyCode kc2 = XKeysymToKeycode(dpy, ks);
    bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    XCloseDisplay(dpy);
    return isPressed;
}

void World::Tick(float t) { // Run every frame
    ClientWorld* w = *(ClientWorld**)dlsym(RTLD_NEXT, "GameWorld"); // Cast void* to ClientWorld*

    IPlayer* iplayer = w->m_activePlayer.m_object; // Get active player
    Player* player = ((Player*)(iplayer)); // Convert IPlayer to Player

    // Speed/Jump hack [Left Control]
    if (isKeyPressed(0xffe3)) { player->m_walkingSpeed = 20000; player->m_jumpSpeed = 4200; }
    else                      { player->m_walkingSpeed = 200;   player->m_jumpSpeed = 420;  }
}