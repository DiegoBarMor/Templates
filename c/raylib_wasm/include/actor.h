#ifndef ACTOR_H
#define ACTOR_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#include "params.h"

typedef struct Actor {
    Vector2 pos; // position
    Vector2 vel; // velocity
    float radius;
    Texture2D* tex;
    bool active;
} Actor;


#define INIT_ACTOR \
    (Actor) { {0.0f, 0.0f}, {0.0f, 0.0f}, 50.0f, NULL, false }
#define FOR_EACH_ACTIVE(B, FIRST, LAST)      \
    for (Actor *B = (FIRST); B < (LAST); ++B) \
        if ((B)->active)
#define FOR_EACH_INACTIVE(B, FIRST, LAST)    \
    for (Actor *B = (FIRST); B < (LAST); ++B) \
        if (!(B)->active)

void update_pos(Actor *actor, float dt);
void update_vel(Actor *actor, Vector2 acc, float dt);

#endif
