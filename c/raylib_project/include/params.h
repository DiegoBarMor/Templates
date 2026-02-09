#ifndef params_H
#define params_H

#include "raylib.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

extern const char *APP_TITLE;
extern const int APP_SCREEN_W;
extern const int APP_SCREEN_H;

extern const int SCREEN_MIN_W;
extern const int SCREEN_MIN_H;

extern int SCREEN_INIT_W;
extern int SCREEN_INIT_H;

extern const int TARGET_FPS;

#endif
