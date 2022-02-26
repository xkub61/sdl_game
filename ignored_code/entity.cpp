#include "Entity.hpp"

Entity::Entity(const char* img_path, Screen *display_ptr)
:display(display_ptr),texture(nullptr),direction(Vector2d(0,0)),rect({0,0,1,1}),errors("")
{
    
    SDL_Surface * surf = nullptr;
    surf = IMG_Load(img_path);

    if (surf == nullptr)
    {
        this->errors.append(IMG_GetError());
    }
    
    this->rect = this->display->getRectFromSurface(surf);
    this->texture = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);

}

void Entity::setPosition(Vector2d pos){
    this->rect.x = pos.x;
    this->rect.y = pos.y;
    return;
}

Vector2d Entity::getPosition(){
    return Vector2d(this->rect.x,this->rect.y);
}

void Entity::setSize(Vector2d size){
    this->rect.w = size.x;
    this->rect.h = size.y;
    return;
}

Vector2d Entity::getSize(){
    return Vector2d(this->rect.w,this->rect.h);
}

void Entity::render(){
    this->display->render(this->texture,nullptr,&this->rect);
    return;
}

void Entity::close(){
    SDL_DestroyTexture(texture);

}