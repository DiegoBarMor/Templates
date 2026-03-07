#include "graphics/render.h"

// -----------------------------------------------------------------------------
Texture2D load_texture_resize(const char* filename, int width, int height) {
    Image img = LoadImage(filename);
    ImageResize(&img, width, height);
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

// -----------------------------------------------------------------------------
void draw_actor(Actor* actor) {
    DrawTexture(*actor->tex, (int)(actor->pos.x - actor->radius*0.5f), (int)(actor->pos.y - actor->radius*0.5f), WHITE);
}

// -----------------------------------------------------------------------------
