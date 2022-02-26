#pragma once
#include<iostream>
#include"Screen.hpp"
#include"TtfFont.hpp"

using namespace std;

class Text
{
private:
    /* data */
public:
    Text(/* args */);
    ~Text();
};



/*class Text // refazer
{
private:
    TTF_Font * font;
    Screen * display;
    string text,errors;
    Vector2d pos;
    Vector2d scale;
    SDL_Surface * surf;
    SDL_Texture * texture;
    SDL_Rect rect;
    SDL_Color color;
    
    
public:
    Text(TTF_Font * text_font,string text, Vector2d text_pos,SDL_Color text_color, Screen *display);
    void setPosition(Vector2d text_pos);
    void setScale(Vector2d text_size);
    void render();
    void  getErrors();
    void clear();
};*/
