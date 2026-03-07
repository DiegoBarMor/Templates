#include "graphics/render.h"

// -----------------------------------------------------------------------------
void draw_actor(Actor* actor) {
    DrawCircleV(actor->pos, actor->radius, actor->color);
}

// -----------------------------------------------------------------------------
