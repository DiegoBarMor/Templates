#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "entities/actor.h"
#include "graphics/render.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    //-------------------------------------------------------------------------- INITIALIZATION
    InitWindow(WINDOW_WINIT, WINDOW_HINIT, APP_TITLE);
    #ifndef DO_DEBUG
        ToggleFullscreen();
    #endif
    SetWindowMinSize(WINDOW_WMIN, WINDOW_HMIN);

    RenderTexture2D target = LoadRenderTexture(VIEWPORT_W, VIEWPORT_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(TARGET_FPS);

    Actor player = INIT_ACTOR;


    //-------------------------------------------------------------------------- MAIN LOOP
    while (!WindowShouldClose()) {
        //---------------------------------------------------------------------- UPDATE
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

        player.pos = virtual_mouse;

        //---------------------------------------------------------------------- DRAW
        BeginTextureMode(target);
            ClearBackground(BLACK);
            draw_actor(&player);
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

    //-------------------------------------------------------------------------- DE-INITIALIZATION
    CloseWindow();
    return 0;
}
