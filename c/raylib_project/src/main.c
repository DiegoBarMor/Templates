#include "raylib.h"
#include "raymath.h"

#include "parameters.h"
#include "actor.h"
#include "render.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    //-------------------------------------------------------------------------- INITIALIZATION
    InitWindow(SCREEN_INIT_W, SCREEN_INIT_H, GAME_TITLE);
    #ifndef DO_DEBUG
        ToggleFullscreen();
    #endif
    SetWindowMinSize(SCREEN_MIN_W, SCREEN_MIN_H);

    RenderTexture2D target = LoadRenderTexture(GAME_SCREEN_W, GAME_SCREEN_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(TARGET_FPS);

    Actor player = INIT_ACTOR;


    //-------------------------------------------------------------------------- GAME LOOP
    while (!WindowShouldClose()) {
        //---------------------------------------------------------------------- UPDATE
        float framebuffer_scale = MIN(
            (float)GetScreenWidth()  / GAME_SCREEN_W,
            (float)GetScreenHeight() / GAME_SCREEN_H
        );
        Vector2 mouse = GetMousePosition();
        Vector2 virtual_mouse = Vector2Clamp(
            (Vector2){
                (mouse.x - (GetScreenWidth()  - (GAME_SCREEN_W*framebuffer_scale)) * 0.5f) / framebuffer_scale,
                (mouse.y - (GetScreenHeight() - (GAME_SCREEN_H*framebuffer_scale)) * 0.5f) / framebuffer_scale
            },
            (Vector2){ 0.0f, 0.0f },
            (Vector2){ (float)GAME_SCREEN_W, (float)GAME_SCREEN_H }
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
                    (GetScreenWidth()  - ((float)GAME_SCREEN_W * framebuffer_scale))*0.5f,
                    (GetScreenHeight() - ((float)GAME_SCREEN_H * framebuffer_scale))*0.5f,
                    (float)GAME_SCREEN_W * framebuffer_scale,
                    (float)GAME_SCREEN_H * framebuffer_scale
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
