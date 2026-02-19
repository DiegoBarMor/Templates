#include "actor.h"

// -----------------------------------------------------------------------------
void update_pos(Actor* actor, float dt) {
    actor->pos.x += actor->vel.x * dt;
    actor->pos.y += actor->vel.y * dt;
}

// -----------------------------------------------------------------------------
void update_vel(Actor* actor, Vector2 acc, float dt) {
    actor->vel.x += acc.x * dt;
    actor->vel.y += acc.y * dt;
}

// -----------------------------------------------------------------------------
