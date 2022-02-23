#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "TtfFont.hpp"
using namespace std;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define FPS 60

int main(int argc,char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erro ao inicializar SDL! ERRO :"<< SDL_GetError() << endl;
        return 1;
    }
    int img_flags = IMG_INIT_PNG;
    if(IMG_Init(img_flags) == 0){
        cout << "Erro ao inicializar SDL_image! ERRO :"<< IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    if(TTF_Init() == -1){
        cout << "Erro ao inicializar SDL_ttf! ERRO :"<< TTF_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    //termino da inicialização




    //cria a janela
    string titulo = "Game";
    Screen display(titulo.c_str(),WINDOW_WIDTH,WINDOW_HEIGHT); 
    display.getErrors();
    
    //cria uma textura
    SDL_Texture* texture = display.LoadTextureFromFile("assets/ghost.png");
    if(texture == nullptr){
        cout << "Erro ao criar textura! ERRO :"<< SDL_GetError() << endl;
        display.destroy();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Rect dst_rect;
    dst_rect.w = 128;
    dst_rect.h = 128;
    dst_rect.x = (WINDOW_WIDTH - dst_rect.w) /2;
    dst_rect.y = (WINDOW_HEIGHT - dst_rect.h) /2;




    //inicializa a fonte 
    /*TTF_Font * font = TTF_OpenFont("assets/minecraft.ttf",16);
    if (font == nullptr){
        cout << "Erro ao criar textura! ERRO :"<< SDL_GetError() << endl;
        SDL_DestroyTexture(texture);
        display.destroy();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Surface * text_surf = nullptr;
    SDL_Texture * text_texture = nullptr;
    SDL_Color font_color;
    font_color.r = 255;
    font_color.g = 255;
    font_color.b = 255;
    font_color.a = 255;
    SDL_Rect text_rect;
    text_rect.x = 20;
    text_rect.y = 20;*/
    TtfFont text = TtfFont("assets/minecraft.ttf", 16, &display);
    text.setFontColor(140, 109, 232, 255);
    text.setTextPosition(20,20);
    text.getErrors();

    string fps_s = "FPS  0";
    int fps_counter = 0;

    
    //eventos
    SDL_Event events;
    bool game_run = true;
    uint32_t dt = SDL_GetTicks();



    //game loop
    while(game_run){
        
        //para calculo do tempo de frame
        dt = SDL_GetTicks();
        uint32_t dt2 = dt;

        //preenche o fundo com a cor 82, 217, 118 e limpa o render
        display.fill(82, 217, 118,255);
        display.clear();


        while(SDL_PollEvent(&events))//lida com eventos
        {
            if (events.type == SDL_QUIT)
            {
                game_run = false;
            }
        }

        display.render(texture,nullptr,&dst_rect);

        //escrita da fonte do fps
        /*text_surf = TTF_RenderText_Solid(font,fps_s.c_str(),font_color);
        if(text_surf == nullptr){
            cout << "Erro ao criar surface da fonte! ERRO :"<< SDL_GetError() << endl;
            TTF_CloseFont(font);
            SDL_DestroyTexture(texture);
            display.destroy();
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
        text_rect.h = text_surf->h;
        text_rect.w = text_surf->w;
        text_texture = display.CreateTextureFromSurface(text_surf);
        SDL_FreeSurface(text_surf);
        
        display.render(text_texture,nullptr,&text_rect);//renderiza a fonte na tela*/
        text.renderText(fps_s);
        //fim escrita da fonte do fps

        //atualiza o renderer
        display.update();

        //limpeza da textura da fonte   
        //SDL_DestroyTexture(text_texture);
        text.clear();

        dt = SDL_GetTicks() - dt;
        if(dt < (1000/FPS)){
            SDL_Delay((1000/FPS) - dt);
        }
        dt2 = SDL_GetTicks() - dt2;
        
        int fps = 1000/dt2;
        fps_counter += 1;
        if (fps_counter >= 30)
        {
            fps_counter = 0;
            fps_s = "FPS  ";
            fps_s += to_string(fps);
        }
        
    }
    display.destroy();
    //TTF_CloseFont(font); //fecha a fonte minecraft
    SDL_DestroyTexture(texture);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}