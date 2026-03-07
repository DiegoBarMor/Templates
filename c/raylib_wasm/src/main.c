#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"

#include "constants.h"
#include "entities/actor.h"
#include "graphics/render.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// -----------------------------------------------------------------------------
static Actor player = INIT_ACTOR;
static RenderTexture2D target;

#if defined(PLATFORM_WEB)
    static char message[50];
    EM_JS(bool, consume_dirty_textinput_flag, (), {
        if (!window.dirty_textinput) return false;
        window.dirty_textinput = false; // consume the flag
        return true;
    });
    EM_JS(char*, get_textinput_str, (), {
        var input = document.getElementById('msg-input');
        return stringToNewUTF8(input.value);
    });
#endif

void UpdateDrawFrame();

// -----------------------------------------------------------------------------
int main() {
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
        while (!WindowShouldClose()) UpdateDrawFrame();
    #endif

    //-------------------------------------------------------------------------- DE-INITIALIZATION
    CloseWindow();
    return 0;
}


// -----------------------------------------------------------------------------
void UpdateDrawFrame() {
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
        (Vector2){ APP_SCREEN_W, APP_SCREEN_H }
    );

    player.pos = virtual_mouse;

    #if defined(PLATFORM_WEB)
        if (consume_dirty_textinput_flag()) {
            char* str = get_textinput_str();
            printf("Updated message: %s\n", str);
            strncpy(message, str, sizeof(message) - 1);
            message[sizeof(message) - 1] = '\0';
            free(str); // _malloc() was called, so avoid memory leak
        }
    #endif

    //-------------------------------------------------------------------------- DRAW
    BeginTextureMode(target);
        ClearBackground(BLACK);
        draw_actor(&player);
        #if defined(PLATFORM_WEB)
            DrawText(message, 10, 10, 100, WHITE);
        #endif
    EndTextureMode();

    BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(
            target.texture,
            (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
            (Rectangle){
                (GetScreenWidth()  - (APP_SCREEN_W * framebuffer_scale))*0.5f,
                (GetScreenHeight() - (APP_SCREEN_H * framebuffer_scale))*0.5f,
                APP_SCREEN_W * framebuffer_scale,
                APP_SCREEN_H * framebuffer_scale
            },
            (Vector2){ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    EndDrawing();
}


// -----------------------------------------------------------------------------
