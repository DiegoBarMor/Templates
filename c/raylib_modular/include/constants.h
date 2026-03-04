#pragma once
#include "raylib.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define VLEN(v) Vector2Length(v)
#define VADD(a, b) Vector2Add(a, b)
#define VSUB(a, b) Vector2Subtract(a, b)
#define VMUL(v, s) Vector2Scale(v, s)

extern const char *APP_TITLE;

#define APP_SCREEN_W 1600.0f
#define APP_SCREEN_H 1200.0f
extern const unsigned int SCREEN_MIN_W;
extern const unsigned int SCREEN_MIN_H;
extern const unsigned int SCREEN_INIT_W;
extern const unsigned int SCREEN_INIT_H;

extern const int TARGET_FPS;
