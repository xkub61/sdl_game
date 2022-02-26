#pragma once
#include"SDL2/SDL.h"

typedef struct Color
{
    int r,g,b,a;
    Color(int r_, int g_, int b_, int a_)
    {   this->r = r_;
        this->g = g_;
        this->b = b_;
        this->a = a_;
    }

    SDL_Color toSDL_Color(){
        SDL_Color color_sdl;
        color_sdl.r = this->r;
        color_sdl.g = this->g;
        color_sdl.b = this->b;
        color_sdl.a = this->a;
        return color_sdl;
    }

}Color;
