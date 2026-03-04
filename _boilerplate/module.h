#pragma once
#include <stdlib.h>

typedef struct Object {
    float data[42];
    Object* next;
} Object;

#define INIT_OBJECT (Object) { {0.0f}, NULL }
#define FOR_EACH_OBJECT(X, FIRST, LAST) for (Object *X = (FIRST); X < (LAST); ++X)

void update_object(Object *object);
