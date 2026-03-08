#pragma once
#include "raylib.h"
#include "raymath.h"

#include "globals.h"

typedef struct Actor {
    Vector2 pos;
    float radius;
    Color color;
} Actor;

#define INIT_ACTOR (Actor) { {0.0f, 0.0f}, 50.0f, RED }
#define FOR_EACH_ACTOR(B, FIRST, LAST) for (Actor *B = (FIRST); B < (LAST); ++B)

void update_pos(Actor *actor, Vector2 dx, float dt);
