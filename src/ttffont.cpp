#include"TtfFont.hpp"

TtfFont::TtfFont(const char* file_path, int ptsize, Screen *display_ptr)
:font(nullptr),text_surf(nullptr),display(display_ptr),text_texture(nullptr),errors("")
{
    this->font_color.r = 255;
    this->font_color.g = 255;
    this->font_color.b = 255;
    this->font_color.a = 255;

    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.h = 1;
    this->rect.w = 1;

    font = TTF_OpenFont(file_path,ptsize);
    if (font == nullptr){
        errors.append(TTF_GetError());
    }
}

void TtfFont::setFontColor(int r,int g,int b,int a){
    this->font_color.r = r;
    this->font_color.g = g;
    this->font_color.b = b;
    this->font_color.a = a;
    return;
}

void TtfFont::setTextPosition(int x, int y){
    this->rect.x = x;
    this->rect.y = y;
    return;
}

void TtfFont::setScale(int x, int y){
    this->rect.w *= x;
    this->rect.h *= y;
    return;
}

void TtfFont::renderText(std::string text){
    text_surf = TTF_RenderText_Solid(this->font,text.c_str(),this->font_color);
    if(text_surf == nullptr){
        errors.append(TTF_GetError());
    }
    this->rect.h = this->text_surf->h;
    this->rect.w = this->text_surf->w;
    
    this->text_texture = this->display->CreateTextureFromSurface(text_surf);
    SDL_FreeSurface(this->text_surf);
        
    this->display->render(text_texture,nullptr,&this->rect);
    return;
}

void TtfFont::getErrors(){
    cout << this->errors << endl;
    return;
}

void TtfFont::clear(){
    SDL_DestroyTexture(this->text_texture);
    return;
}

void TtfFont::close(){
    TTF_CloseFont(this->font);
    return;
}