#include "raylib.h"
#include "raymath.h"

//// uncomment to compile for PLATFORM_WEB
// #define PLATFORM_WEB

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// -----------------------------------------------------------------------------
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

const char *APP_TITLE = "Raylib Project";
const int APP_SCREEN_W = 1600;
const int APP_SCREEN_H = 1200;

const int SCREEN_MIN_W = 400;
const int SCREEN_MIN_H = 400;

int SCREEN_INIT_W = 400;
int SCREEN_INIT_H = 400;

const int TARGET_FPS = 60;

// -----------------------------------------------------------------------------
typedef struct Actor {
    Vector2 pos;
} Actor;

#define INIT_ACTOR \
    (Actor) { {0.0f, 0.0f} }
#define FOR_EACH_ACTIVE(B, FIRST, LAST)      \
    for (Actor *B = (FIRST); B < (LAST); ++B) \
        if ((B)->active)
#define FOR_EACH_INACTIVE(B, FIRST, LAST)    \
    for (Actor *B = (FIRST); B < (LAST); ++B) \
        if (!(B)->active)


// -----------------------------------------------------------------------------
static Actor player = INIT_ACTOR;
static RenderTexture2D target;

void draw_actor(Actor* actor) {
    DrawCircle((int)actor->pos.x, (int)actor->pos.y, 20, RED);
}

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
