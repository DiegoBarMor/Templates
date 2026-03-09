#include "game/app.h"

// -----------------------------------------------------------------------------
void init_app(App* app) {
    app->player = INIT_ACTOR;
    app->player.pos = (Vector2){ VIEWPORT_W*0.5f, VIEWPORT_H*0.5f };

    app->tex_player = load_texture_resize("assets/circle.png", app->player.radius, app->player.radius);

    app->player.tex = &app->tex_player;
}


// -----------------------------------------------------------------------------
void update_app(App* app, Vector2 virtual_mouse) {
    _update_state(app, virtual_mouse);
}


// -----------------------------------------------------------------------------
void destroy_app(App* app) {
    UnloadTexture(app->tex_player);
}


// -----------------------------------------------------------------------------
void _update_state(App* app, Vector2 virtual_mouse) {
    float dt = 1.0f / (float)TARGET_FPS;
    // float dt = GetFrameTime();

    app->player.pos = virtual_mouse;
}


// -----------------------------------------------------------------------------
