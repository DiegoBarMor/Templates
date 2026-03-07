#pragma once
#include "raylib.h"

#include "constants.h"
#include "entities/actor.h"

Texture2D load_texture_resize(const char* filename, int width, int height);
void draw_actor(Actor* actor);
