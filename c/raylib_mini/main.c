#include "raylib.h"
#include "raymath.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define VLEN(v) Vector2Length(v)
#define VADD(a, b) Vector2Add(a, b)
#define VSUB(a, b) Vector2Subtract(a, b)
#define VMUL(v, s) Vector2Scale(v, s)

const char *APP_TITLE = "Raylib Project";

#define VIEWPORT_W 1600.0f
#define VIEWPORT_H 1200.0f
const unsigned int WINDOW_WMIN = 400;
const unsigned int WINDOW_HMIN = 400;
const unsigned int WINDOW_WINIT = 400;
const unsigned int WINDOW_HINIT = 400;

const int TARGET_FPS = 60;

// -----------------------------------------------------------------------------
typedef struct Actor {
    Vector2 pos;
    float radius;
    Color color;
} Actor;

#define INIT_ACTOR (Actor) { {0.0f, 0.0f}, 50.0f, RED }
#define FOR_EACH_ACTOR(B, FIRST, LAST) for (Actor *B = (FIRST); B < (LAST); ++B)


// -----------------------------------------------------------------------------
void draw_actor(Actor* actor) {
    DrawCircleV(actor->pos, actor->radius, actor->color);
}

// -----------------------------------------------------------------------------
int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    ////////////////////////////// INITIALIZATION //////////////////////////////
    InitWindow(WINDOW_WINIT, WINDOW_HINIT, APP_TITLE);
    #ifndef DO_DEBUG
        ToggleFullscreen();
    #endif
    SetWindowMinSize(WINDOW_WMIN, WINDOW_HMIN);

    RenderTexture2D target = LoadRenderTexture(VIEWPORT_W, VIEWPORT_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(TARGET_FPS);

    Actor player = INIT_ACTOR;

    ///////////////////////////////// MAIN LOOP ////////////////////////////////
    while (!WindowShouldClose()) {
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

        player.pos = virtual_mouse;

    /////////////////////////////////// DRAW ///////////////////////////////////
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

    ///////////////////////////// DE-INITIALIZATION ////////////////////////////
    CloseWindow();
    return 0;
}
