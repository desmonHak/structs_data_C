#ifndef __MATRIZ_LIST_H__
#define __MATRIZ_LIST_H__

#include "./DebugLibC/debug_c.h"
#include "array-list.h"
#include <stdarg.h>
#include <math.h>

typedef struct Matriz {
    ArrayList *list;
    ArrayList *dimensiones_matriz;
} Matriz;

typedef position dimensiones;

Matriz* createMatriz(dimensiones dimensionesMatriz, ...);
Matriz* newMatriz();
Matriz* freeMatriz(Matriz* matriz);
void createColumns(Matriz* matriz, position columns);
void createRow(Matriz* matriz, position row);
dimensiones get_size_va_list(dimensiones dimensionesMatriz, va_list args);
dimensiones get_size_size_total(dimensiones dimensionesMatriz, ...);
ArrayList* dimensiones_matriz(dimensiones dimensionesMatriz, ...);
ArrayList* dimensiones_matriz_va_list(dimensiones dimensionesMatriz, va_list args);

#ifdef INCLUDE_COLORS_C
#include "matriz-list.c"
#endif
#endif