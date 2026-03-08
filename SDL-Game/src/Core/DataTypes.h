#ifndef DATATYPES_H
#define DATATYPES_H

#include <SDL2/SDL.h>
#include <box2d/box2d.h>

#ifdef _WIN_64

// PRIMATIVES_BEGIN
#define NULL 0

#define FALSE 0
#define TRUE 1

typedef unsigned long long SIZE_T;

typedef void* P_VOID;

typedef char CHAR8;
typedef char* P_CHAR8;
typedef const char* C_STRING;

typedef signed char INT8;
typedef unsigned char UINT8;

typedef short INT16;
typedef unsigned short UINT16;

typedef int INT32;
typedef unsigned int UINT32;

typedef long long INT64;
typedef unsigned long long UINT64;

typedef float FLOAT32;

typedef double FLOAT64;
// PRIMATIVES_END

// SDL_TYPES_START
typedef SDL_Window WINDOW;
typedef SDL_Window* P_WINDOW;

typedef SDL_Renderer RENDERER;
typedef SDL_Renderer* P_RENDERER;

typedef SDL_Event EVENT;
typedef SDL_Event* P_EVENT;

typedef SDL_Texture TEX2D;
typedef SDL_Texture* P_TEX2D;

typedef SDL_Rect RECT2D;
typedef SDL_Rect* P_RECT2D;

typedef SDL_FRect F_RECT2D;
typedef SDL_FRect* P_F_RECT2D;
// SDL_TYPES_END

// BOX2D_TYPES_START
typedef b2Vec2 VEC2D;

typedef b2WorldDef WORLD_DEF;

typedef b2WorldId WORLD_ID;

typedef b2BodyDef BODY_DEF;

typedef b2BodyId BODY_ID;

typedef b2Polygon POLY2D;

typedef b2ShapeDef SHAPE_DEF;
// BOX2D_TYPES_END

#endif // _WIN_64

#endif // !DATATYPES_H
