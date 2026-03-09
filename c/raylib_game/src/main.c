#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "game/app.h"
#include "graphics/render.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//////////////////////////////// CORE VARIABLES ////////////////////////////////
static RenderTexture2D target;
static App app;

void update_draw_frame();


// -----------------------------------------------------------------------------
int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    ////////////////////////////// INITIALIZATION //////////////////////////////
    InitWindow(WINDOW_WINIT, WINDOW_HINIT, APP_TITLE);
    #ifndef DO_DEBUG
        ToggleFullscreen();
    #endif
    SetWindowMinSize(WINDOW_WMIN, WINDOW_HMIN);

    target = LoadRenderTexture(VIEWPORT_W, VIEWPORT_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(TARGET_FPS);

    init_app(&app);

    ///////////////////////////////// MAIN LOOP ////////////////////////////////
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(update_draw_frame, 0, 1);
    #else
        while (!WindowShouldClose()) update_draw_frame();
    #endif

    ///////////////////////////// DE-INITIALIZATION ////////////////////////////
    destroy_app(&app);
    CloseWindow();
    return 0;
}


// -----------------------------------------------------------------------------
void update_draw_frame() {
    ////////////////////////////////// UPDATE //////////////////////////////////
    float framebuffer_scale = MIN(
        (float)GetScreenWidth()  / VIEWPORT_W,
        (float)GetScreenHeight() / VIEWPORT_H
    );
    Vector2 mouse = GetMousePosition();
    Vector2 virtual_mouse = Vector2Clamp(
        (Vector2){
            (mouse.x - (GetScreenWidth()  - (VIEWPORT_W*framebuffer_scale)) * 0.5f) / framebuffer_scale,
            (mouse.y - (GetScreenHeight() - (VIEWPORT_H*framebuffer_scale)) * 0.5f) / framebuffer_scale
        },
        (Vector2){ 0.0f, 0.0f },
        (Vector2){ VIEWPORT_W, VIEWPORT_H }
    );

    update_app(&app, virtual_mouse);

    /////////////////////////////////// DRAW ///////////////////////////////////
    BeginTextureMode(target);
        draw_app(&app);
    EndTextureMode();

    BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(
            target.texture,
            (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
            (Rectangle){
                (GetScreenWidth()  - (VIEWPORT_W * framebuffer_scale))*0.5f,
                (GetScreenHeight() - (VIEWPORT_H * framebuffer_scale))*0.5f,
                VIEWPORT_W * framebuffer_scale,
                VIEWPORT_H * framebuffer_scale
            },
            (Vector2){ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    EndDrawing();
}


// -----------------------------------------------------------------------------
