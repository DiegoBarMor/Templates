#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"

#include "params.h"
#include "actor.h"

Texture2D load_texture_resize(const char* filename, int width, int height);
void draw_actor(Actor* actor);

#endif
