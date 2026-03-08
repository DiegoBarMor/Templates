#include "graphics/render.h"

// -----------------------------------------------------------------------------
void draw_actor(Actor* actor) {
    DrawTexture(*actor->tex, (int)(actor->pos.x - actor->radius*0.5f), (int)(actor->pos.y - actor->radius*0.5f), WHITE);
}

// -----------------------------------------------------------------------------
