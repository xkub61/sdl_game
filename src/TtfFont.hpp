#pragma once
#include<iostream>
#include"SDL2/SDL.h"
#include"SDL2/SDL_ttf.h"
#include "Screen.hpp"
using namespace std;

/*
-inicie o objeto            TtfFont()
-verifique erros            getErrors()
-sete a cor                 setFontColor()
-sete a posição             setTextPosition()
-sete a escala caso queira  setScale()
-renderize o texto          renderText()
-verifique erros            getErrors()
-libere a textura           clear()
-por fim, feche a fonte     close()

*/

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

    void setFontColor(int r,int g,int b,int a);
    void setTextPosition(int x, int y);
    void setScale(int x, int y);
    void renderText(std::string text);
    void getErrors();
    void clear();
    void close();
};