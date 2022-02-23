#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Screen.hpp"
#include "TtfFont.hpp"
#include "Entity.hpp"
#include "Vector2d.hpp"

using namespace std;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define FPS 60

int main(int argc,char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erro ao inicializar SDL! ERRO :"<< SDL_GetError() << endl;
        return 1;
    }
    if(IMG_Init(IMG_INIT_PNG) == 0){
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
    //termino da criação da janela
    
    
    //cria uma entidade
    Entity ghost("assets/ghost.png",&display);
    ghost.setSize(Vector2d(128,128));
    Vector2d ghost_pos((WINDOW_WIDTH - ghost.getSize().x)/2  , (WINDOW_HEIGHT - ghost.getSize().y)/2);
    ghost.setPosition(ghost_pos);




    //criação da fonte
    TtfFont text = TtfFont("assets/minecraft.ttf", 16, &display);
    text.setFontColor(0, 0, 0, 255);
    text.setTextPosition(20,20);
    text.getErrors();
    //termino da criação da fonte



    //escrita e calculo da duração do frame
    string fps_s = "FPS  0";
    int fps_counter = 0;
    uint32_t dt = SDL_GetTicks();
    


    //eventos
    SDL_Event events;
    bool game_run = true;
   


    //game loop
    while(game_run){
        
        //para calculo do tempo de frame
        dt = SDL_GetTicks();
        uint32_t dt2 = dt;

        //preenche o fundo com a cor 82, 217, 118 e limpa o render
        display.fill(82, 217, 118,255);
        display.clear();


        //lida com eventos
        while(SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
            {
                game_run = false;
            }
        }

        //renderiza o fantasma na tela
        //display.render(texture,nullptr,&dst_rect);
        ghost.render();

        //escrita do fps na tela
        text.renderText(fps_s);
        //fim escrita da fonte do fps

        //atualiza o renderer
        display.update();

        //limpeza da textura da fonte   
        text.clear();

        //calculo do tempo do frame
        dt = SDL_GetTicks() - dt;
        if(dt < (1000/FPS)){
            SDL_Delay((1000/FPS) - dt);
        }
        
        //calculo para a escrita do fps na tela
        dt2 = SDL_GetTicks() - dt2;
        int fps = 1000/dt2;
        
        fps_counter += 1;
        if (fps_counter >= 30)//escreve o valor do fps a cada 30 frames
        {
            fps_counter = 0;
            fps_s = "FPS  ";
            fps_s += to_string(fps);
        }
        
    }

    //libera a memória alocada pelos objetos
    ghost.close();
    text.close();
    display.destroy();
    
    //encerra as apis
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}