#ifndef SDLTYPES_H
#define SDLTYPES_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>

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

#endif // !SDLTYPES_H
