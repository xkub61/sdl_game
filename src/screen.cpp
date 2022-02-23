#include "Screen.hpp"

Screen::Screen(const char* screen_caption,int screen_width, int screen_height)
:caption(screen_caption),width(screen_width),height(screen_height)
{
    window = SDL_CreateWindow(caption,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width,
                            height,
                            SDL_WINDOW_OPENGL);
    if(window == nullptr){
        erros = SDL_GetError();
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        erros.append("\n");
        erros.append(SDL_GetError());
    }  
}

Screen::~Screen(){
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Screen::fill( int rval,int gval,int bval,int aval){
    SDL_SetRenderDrawColor(this->renderer,rval,gval,bval,aval);
    return;
}

void Screen::clear(){
    SDL_RenderClear(this->renderer);
    return;
}

void Screen::render(SDL_Texture* texture, SDL_Rect * src_rect, SDL_Rect * dst_rect ){
    SDL_RenderCopy(this->renderer,texture,src_rect,dst_rect);
    return;
}

void Screen::update(){
    SDL_RenderPresent(this->renderer);
    return;
}

SDL_Texture* Screen::LoadTextureFromFile(const char* file_path){
    SDL_Texture *texture = IMG_LoadTexture(this->renderer,file_path);
    return texture;
}

SDL_Texture* Screen::CreateTextureFromSurface(SDL_Surface * surface){

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer,surface);
    return texture;
}

void Screen::getErrors(){
    cout<< erros << endl;
    return;
}
void Screen::destroy(){
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}