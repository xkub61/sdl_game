#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Screen.hpp"
#include "Vector2d.hpp"
#include "Level.hpp"


using namespace std;


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
    //termino da inicialização

    //cria a janela
    Screen display("Plataforma",WINDOW_WIDTH,WINDOW_HEIGHT); 
    display.getErrors();
    //termino da criação da janela
    

    Level level(&display);


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

        level.run();     

        
        //atualiza o renderer
        display.update();

        //calculo do tempo do frame
        dt = SDL_GetTicks() - dt;
        if(dt < (1000/FPS)){
            SDL_Delay((1000/FPS) - dt);
        }
        
        //calculo para a escrita do fps
        dt2 = SDL_GetTicks() - dt2;
        int fps = 1000/dt2;
        
        fps_counter += 1;
        if (fps_counter >= 30)//escreve o valor do fps a cada 30 frames
        {
            fps_counter = 0;
            fps_s = "FPS  ";
            fps_s += to_string(fps);
            cout << fps_s << endl;
        }
        
    }

    //libera a memória alocada pelos objetos
    level.clear();
    display.destroy();
    
    //encerra as apis
    IMG_Quit();
    SDL_Quit();
    return 0;
}