#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Screen
{
    private:
        const char* caption;
        int width;
        int height;
        SDL_Window * window;
        SDL_Renderer * renderer;
        string erros = "";
    public:
        Screen(const char* screen_caption,int screen_widht, int screen_height);
        ~Screen();
        void fill( int rval,int gval,int bval,int aval);
        void clear();
        void destroy();
        void render(SDL_Texture* texture, SDL_Rect * src_rect, SDL_Rect * dst_rect );
        void update();
        void getErrors();
        SDL_Renderer * getRenderer();
        SDL_Texture* LoadTextureFromFile(const char* file_path);
        
        //transforma uma superficie em texture
        SDL_Texture* CreateTextureFromSurface(SDL_Surface * surface);
};

