#include<iostream>
#include"SDL2/SDL.h"
#include"SDL2/SDL_ttf.h"
#include "Screen.hpp"
using namespace std;

class TtfFont
{
private:
    Screen * display;
    TTF_Font * font;
    SDL_Surface * text_surf;
    SDL_Texture * text_texture;
    SDL_Color font_color;
    SDL_Rect rect;
    string errors;
public:
    TtfFont(const char* file_path, int ptsize, Screen *display_ptr);
    TtfFont();

    void setFontColor(int r,int g,int b,int a);
    void setTextPosition(int x, int y);
    void setScale(int x, int y);
    void renderText(std::string text);
    void getErrors();
    void clear();
    void close();
};