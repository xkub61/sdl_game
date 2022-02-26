#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Screen.hpp"
#include "Vector2d.hpp"
#include "Text.hpp"
#include <vector>
using namespace std;

/*
-inicie o objeto            TtfFont()
-verifique erros            getErrors()
-por fim, feche a fonte     close()

*/

class TtfFont
{
private:
    TTF_Font * font;
    string errors;
public:
    TtfFont(const char* file_path, int ptsize);

    TTF_Font * getFontptr();
    void getErrors();
    void close();
};