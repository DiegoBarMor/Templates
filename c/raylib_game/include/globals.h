#pragma once
#include "raylib.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define VLEN(v) Vector2Length(v)
#define VADD(a, b) Vector2Add(a, b)
#define VSUB(a, b) Vector2Subtract(a, b)
#define VMUL(v, s) Vector2Scale(v, s)

extern const char *APP_TITLE;

#define VIEWPORT_W 1600.0f
#define VIEWPORT_H 1200.0f
extern const unsigned int WINDOW_WMIN;
extern const unsigned int WINDOW_HMIN;
extern const unsigned int WINDOW_WINIT;
extern const unsigned int WINDOW_HINIT;

extern const int TARGET_FPS;
