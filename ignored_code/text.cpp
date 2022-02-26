#include"Text.hpp"

Text::Text(TTF_Font * text_font,string text_, Vector2d text_pos,SDL_Color text_color, Screen *display)
:font(text_font),text(text_),errors(""),pos(text_pos),color(text_color),scale(Vector2d(1,1)),
surf(nullptr),texture(nullptr),rect({0,0,1,1})
{
    if(font == nullptr){
        errors.append(TTF_GetError());
        cout << errors << endl;
    }
}

void Text::setPosition(Vector2d text_pos){
    this->rect.x = text_pos.x;
    this->rect.y = text_pos.y;
    return;
}

void Text::setScale(Vector2d text_size){
    this->rect.w *= text_size.x;
    this->rect.h *= text_size.y;
    return;
}

void Text::render(){
    this->surf = TTF_RenderText_Solid(this->font,this->text.c_str(),this->color);
    
    if(this->surf == nullptr){
        this->errors.append(TTF_GetError());
        cout << this->errors << endl;
        return;
    }
    
    this->rect.h = this->surf->h;
    this->rect.w = this->surf->w;
    
    this->texture = this->display->CreateTextureFromSurface(this->surf);
    cout <<"aqui" << endl;
    SDL_FreeSurface(this->surf);
        
    this->display->render(this->texture,nullptr,&this->rect);
    return;
}

void Text::getErrors(){
    cout << this->errors << endl;
    return;
}

void Text::clear(){
    SDL_DestroyTexture(this->texture);
    return;
}