#include "actor.h"

// -----------------------------------------------------------------------------
void update_pos(Actor* actor, Vector2 dx, float dt) {
    actor->pos = VADD(actor->pos, VMUL(dx, dt));
}

// -----------------------------------------------------------------------------
