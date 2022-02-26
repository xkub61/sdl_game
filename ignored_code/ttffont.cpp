#include"TtfFont.hpp"

TtfFont::TtfFont(const char* file_path, int ptsize)
:font(nullptr),errors("")
{
    font = TTF_OpenFont(file_path,ptsize);
    if (font == nullptr){
        errors.append(TTF_GetError());
    }
}

TTF_Font * TtfFont::getFontptr()
{
    return this->font;
}

void TtfFont::getErrors(){
    cout << this->errors << endl;
}

void TtfFont::close(){
    TTF_CloseFont(this->font);
    return;
}