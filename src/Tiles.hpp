#pragma once
#include "SDL2/SDL.h"
#include "Screen.hpp"
#include "Vector2d.hpp"


class Tile
{
private:
    Screen* display;
    SDL_Texture * texture;
    SDL_Rect rect;
public:
    Tile(SDL_Texture * texture_ptr,SDL_Rect tile_rect,Screen *display_ptr);
    SDL_Rect getRect();
    void setPos(Vector2d pos);
    void render();
};

Tile::Tile(SDL_Texture * texture_ptr,SDL_Rect tile_rect,Screen *display_ptr)
:display(display_ptr),texture(texture_ptr),rect(tile_rect)
{}


SDL_Rect Tile::getRect(){
    return this->rect;
}

void Tile::setPos(Vector2d pos){
    this->rect.x = pos.x;
    this->rect.y = pos.y;
    return;
}

void Tile::render(){//Precisa ser refeita
    if(this->texture == nullptr){
        cout << "Sem textura in tile" << endl;
        exit(1);
    }
    this->display->render(this->texture,nullptr,&this->rect);
    return;
}
