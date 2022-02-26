#pragma once
#include "Player.hpp"
#include "Tiles.hpp"
#include "Screen.hpp"
#include <vector>
#include <fstream>

#define TILE_SIZE  64

class Level
{
private:
    Screen * display;
    Player player;
    vector<Tile>  tiles;
    vector<SDL_Texture *> textures;
    int player_initial_x_speed;
    int world_shift;

    
    void loadLevelTextures();
    void setupLevel();
    void scrollX();
    void horizontalMovementCollision();
    void verticalMovementCollision();
    void renderTiles();
public:
    Level(Screen *display_ptr);

    void run();
    void clear();
};



Level::Level(Screen *display_ptr)
:display(display_ptr),player(Player(display_ptr)),world_shift(0)
{
    this->setupLevel();
    this->player_initial_x_speed = this->player.speed_x;

}



void Level::loadLevelTextures(){
    SDL_Texture *tex = this->display->LoadTextureFromFile("assets/rock_tile.png");//textures[0]
    //textures[1]
    //e assim por diante ...
    this->textures.push_back(tex);
}



void Level::setupLevel(){
    
    this->loadLevelTextures();
    
    //lê o arquivo de texto e do map.txt e transforma em cordenada para as tiles e para o player
    
    //teste
    ifstream map_file;
    map_file.open("assets/map.txt");
    vector<string> map_info;
    string line;
    
    while(map_file)
    {
        getline(map_file,line);
        map_info.push_back(line);
    }
    
    map_file.close();


    for (size_t i = 0; i < map_info.size(); i++)
    {   
        for (size_t j = 0; j < map_info[i].size(); j++)
        {
            if(map_info[i][j] == 'X')
            {
                SDL_Rect tile_rect;
                tile_rect.w = TILE_SIZE;
                tile_rect.h = TILE_SIZE;
                tile_rect.x = j * TILE_SIZE;
                tile_rect.y = i * TILE_SIZE;
                this->tiles.push_back(Tile(this->textures[0],tile_rect,this->display));
            }
            if(map_info[i][j] == 'P')
            {
                this->player.rect.x = (j * TILE_SIZE);
                this->player.rect.y = (i * TILE_SIZE);
            }
        }
    }
    

    return;
}



void Level::scrollX(){
    int player_center_pos = (this->player.rect.w/2) + this->player.rect.x;
    int player_direction_x = this->player.direction.x;
    if(player_direction_x > 0 && player_center_pos > (3*this->display->getWindowRect().w/5)){
        this->world_shift = - this->player_initial_x_speed;
        this->player.speed_x = 0;
    }
    else if(player_direction_x < 0 && player_center_pos < (2*this->display->getWindowRect().w/5))
    {
        this->world_shift = this->player_initial_x_speed;
        this->player.speed_x = 0;
    }
    else{
        this->world_shift = 0;
        this->player.speed_x = this->player_initial_x_speed;
    }

    if(this->world_shift != 0)//move todas as tiles
    {    for (size_t i = 0; i < this->tiles.size(); i++)
        {
            Vector2d new_pos(this->tiles[i].getRect().x + this->world_shift,this->tiles[i].getRect().y);
            this->tiles[i].setPos(new_pos);
        }
    }
    
    
    return;
}



void Level::horizontalMovementCollision(){
    
    int x_dir = this->player.direction.x;
    this->player.rect.x = (this->player.speed_x * x_dir + this->player.rect.x);

    for(size_t i = 0; i < tiles.size(); i++){

        SDL_Rect rect_a = this->player.rect;
        SDL_Rect rect_b = tiles[i].getRect();

        if (SDL_HasIntersection(&rect_a,&rect_b)){

            if(x_dir > 0){
                this->player.rect.x = (rect_b.x - rect_a.w);
            }
            if(x_dir < 0){
                this->player.rect.x = (rect_b.x + rect_b.w);
            }
        }//fim do if
    }//fim do for
    return;
}



void Level::verticalMovementCollision(){

    this->player.applyGravity();
    
    
    for(size_t i = 0; i < tiles.size(); i++){

        SDL_Rect rect_a = this->player.rect;
        SDL_Rect rect_b = tiles[i].getRect();

        if (SDL_HasIntersection(&rect_a,&rect_b)){

            if(this->player.direction.y >= 1){
                this->player.rect.y = (rect_b.y - rect_a.h);
                this->player.direction.y = 0;
                
                this->player.on_ground = true;
            }
            if(this->player.direction.y < 0){
                this->player.rect.y = (rect_b.y + rect_b.h);
                this->player.direction.y = 0;
                
            }
        }//fim do if
    }//fim do for
    if((this->player.on_ground && this->player.direction.y < 0) || (this->player.direction.y > this->player.gravity))
    {
        this->player.on_ground = false;
    }
    return;
}



void Level::renderTiles(){

    SDL_Rect window_rect = this->display->getWindowRect();
    
    for (size_t i = 0; i < this->tiles.size(); i++)
    {
        SDL_Rect tile_rect = tiles[i].getRect();
        if(SDL_HasIntersection(&window_rect,&tile_rect))
        {
            this->tiles[i].render();
        }
    }
}



void Level::run(){
    
    this->scrollX();
    this->renderTiles();

    //player
    this->player.update();
    this->horizontalMovementCollision();
    this->verticalMovementCollision();
    this->player.render();
    
}



void Level::clear(){
    for (size_t i = 0; i < this->textures.size(); i++)//clear na texturas
    {
        SDL_DestroyTexture(textures[i]);
    }
    this->player.clear();//clear nas texturas do player
    return;

    
}