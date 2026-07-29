#include "entities/actor.h"

// -----------------------------------------------------------------------------
void update_actor(Actor* actor, Vector2 dx, float dt) {
    actor->pos = VADD(actor->pos, VMUL(dx, dt));
}

// -----------------------------------------------------------------------------
