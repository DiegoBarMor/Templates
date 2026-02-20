#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

#include "params.h"
#include "actor.h"
#include "render.h"

//// uncomment to compile for PLATFORM_WEB
// #define PLATFORM_WEB

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// -----------------------------------------------------------------------------
static Actor player = INIT_ACTOR;
static RenderTexture2D target;
static char message[100];

void UpdateDrawFrame(void) {
    //-------------------------------------------------------------------------- UPDATE
    float framebuffer_scale = MIN(
        (float)GetScreenWidth()  / APP_SCREEN_W,
        (float)GetScreenHeight() / APP_SCREEN_H
    );
    Vector2 mouse = GetMousePosition();
    Vector2 virtual_mouse = Vector2Clamp(
        (Vector2){
            (mouse.x - (GetScreenWidth()  - (APP_SCREEN_W*framebuffer_scale)) * 0.5f) / framebuffer_scale,
            (mouse.y - (GetScreenHeight() - (APP_SCREEN_H*framebuffer_scale)) * 0.5f) / framebuffer_scale
        },
        (Vector2){ 0.0f, 0.0f },
        (Vector2){ (float)APP_SCREEN_W, (float)APP_SCREEN_H }
    );

    player.pos = virtual_mouse;

    //-------------------------------------------------------------------------- DRAW
    BeginTextureMode(target);
        ClearBackground(BLACK);
        draw_actor(&player);
        DrawText(message, 0, 0, 16, WHITE);
    EndTextureMode();

    BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(
            target.texture,
            (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
            (Rectangle){
                (GetScreenWidth()  - ((float)APP_SCREEN_W * framebuffer_scale))*0.5f,
                (GetScreenHeight() - ((float)APP_SCREEN_H * framebuffer_scale))*0.5f,
                (float)APP_SCREEN_W * framebuffer_scale,
                (float)APP_SCREEN_H * framebuffer_scale
            },
            (Vector2){ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    EndDrawing();
}

// -----------------------------------------------------------------------------
int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    //-------------------------------------------------------------------------- INITIALIZATION
    InitWindow(SCREEN_INIT_W, SCREEN_INIT_H, APP_TITLE);
    #ifndef DO_DEBUG
        ToggleFullscreen();
    #endif
    SetWindowMinSize(SCREEN_MIN_W, SCREEN_MIN_H);

    target = LoadRenderTexture(APP_SCREEN_W, APP_SCREEN_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(TARGET_FPS);

    player = INIT_ACTOR;
    Texture2D tex_player = load_texture_resize("assets/circle.png", player.radius, player.radius);
    player.tex = &tex_player;

    #if defined(PLATFORM_WEB)
        printf("This text was written by the WASM binary!\n"); // the '\n' at the end is important
    #endif

    //-------------------------------------------------------------------------- MAIN LOOP
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else
        while (!WindowShouldClose()) {
            UpdateDrawFrame();
        }
    #endif

    //-------------------------------------------------------------------------- DE-INITIALIZATION
    CloseWindow();
    return 0;
}
