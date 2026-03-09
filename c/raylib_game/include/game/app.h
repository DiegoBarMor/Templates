#pragma once
#include <stdlib.h>

#include "globals.h"
#include "entities/actor.h"
#include "graphics/textures.h"

typedef struct App {
    Texture2D tex_player;
    Actor player;
} App;

void init_app(App* app);
void update_app(App* app, Vector2 virtual_mouse);
void destroy_app(App* app);

void _update_state(App* app, Vector2 virtual_mouse);
