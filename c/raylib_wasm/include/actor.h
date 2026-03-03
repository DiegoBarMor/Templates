#ifndef ACTOR_H
#define ACTOR_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#include "constants.h"

typedef struct Actor {
    Vector2 pos;
    float radius;
    Texture2D* tex;
} Actor;

#define INIT_ACTOR (Actor) { {0.0f, 0.0f}, 50.0f, NULL }
#define FOR_EACH_ACTOR(B, FIRST, LAST) for (Actor *B = (FIRST); B < (LAST); ++B)

void update_pos(Actor *actor, Vector2 dx, float dt);

#endif
