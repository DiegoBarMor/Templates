#include "graphics/textures.h"

// -----------------------------------------------------------------------------
Texture2D load_texture_resize(const char* filename, float width, float height) {
    Image img = LoadImage(filename);
    ImageResize(&img, (int)width, (int)height);
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

// -----------------------------------------------------------------------------
