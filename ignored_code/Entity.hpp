#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Screen.hpp"
#include "Vector2d.hpp"

using namespace std;

class Entity
{
private:
    Screen * display;
    SDL_Texture * texture;
    SDL_Rect rect;
    Vector2d direction;
    string errors;
public:
    Entity(const char* img_path, Screen *display_ptr);

    void setPosition(Vector2d pos);
    Vector2d getPosition();
    void setSize(Vector2d size);
    Vector2d getSize();
    void render();
    void close();
};
