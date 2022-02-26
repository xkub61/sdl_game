#pragma once
#include "SDL2/SDL.h"
#include "Vector2d.hpp"
#include "Screen.hpp"
#include <fstream>

class Player
{
private:
    Screen * display;//pode ser privada
    const float animation_speed = 0.25;//pode ser privada
    float frame_index;//pode ser privada
    SDL_Texture * texture;//pode ser privada   


    //metodos internos;
    void readPlayerSettings();
    void importCharacterAssets();
    void animate();
    void getInput();
    void jump();


    
    

public:
    //player movement
    SDL_Rect rect;
    Vector2d direction;
    int speed_x ;
    int gravity ;
    int jump_speed;
    
    //player status
    int status;
    bool facing_right;
    bool on_ceiling;
    bool on_ground;
    bool on_left;
    bool on_right;


    Player(Screen *display_ptr);
    void applyGravity();
    void printValues();
    void update();
    void render();
    void clear();

    
    

};

Player::Player(Screen *display_ptr)
:direction(Vector2d(0,0)),display(display_ptr)
{
    this->readPlayerSettings();
    cout << this->speed_x << endl;
    cout << this->gravity << endl;
    cout << this->jump_speed << endl;
    this->status = 0;
    this->facing_right = false;
    this->on_ceiling = false;
    this->on_ground = false;
    this->on_left = false;
    this->on_right = false;

    SDL_Surface * surf = nullptr;
    surf = IMG_Load("assets/ghost.png");
    this->rect = this->display->getRectFromSurface(surf);
    this->rect.h *= 3;
    this->rect.w *= 3;
    this->texture = this->display->CreateTextureFromSurface(surf);

    SDL_FreeSurface(surf);
}


void Player::readPlayerSettings(){

    ifstream settings_file;

    settings_file.open("assets/settings");

    string line;
    while (settings_file)
    {
        getline(settings_file,line);
        if(line[0] == '#'){
         
                string variable_name;
                string variable_value;

                for (int i = 0; line[i] != ' '; i++)
                {
                    variable_name.push_back(line[i]);
                }
                
                int count = 0;
                while ((line[count] < '0' || line[count] > '9') && line[count] != '-' )
                {
                    count++;
                }

                for (int i = count; line[i] >= '0' && line[i] <= '9' || line[i] == '-'; i++)
                {
                    variable_value.push_back(line[i]);
                }
                 cout << stoi(variable_value) << endl;

                if(variable_name == "#PLAYER_X_VELOCITY")
                    this->speed_x = stoi(variable_value);
                if (variable_name == "#PLAYER_GRAVITY")
                    this->gravity = stoi(variable_value);
                if (variable_name == "PLAYER_JUMP_SPEED");
                    this->jump_speed = stoi(variable_value);

            
        }
    }

    settings_file.close();
    return;
}



void Player::importCharacterAssets(){
    return;
}



void Player::animate(){
    return;
}



void Player::getInput(){
    this->direction.x = 0;
    const Uint8 * keys = SDL_GetKeyboardState(nullptr);
        
    if (keys[SDL_SCANCODE_LEFT]){
            this->direction.x = - 1;
        }
    else if (keys[SDL_SCANCODE_RIGHT]){
            this->direction.x = 1;
        }
    else{
        this->direction.x = 0;
    }
        
    if (keys[SDL_SCANCODE_SPACE] and this->on_ground){
            this->jump();
        }
               
    return;
}



void Player::applyGravity(){
    this->direction.y += this->gravity;
    this->rect.y += this->direction.y;
    return;
}



void Player::jump(){
    this->direction.y = this->jump_speed;
    return;
}



void Player::render(){
    this->display->render(this->texture,nullptr,&this->rect);
}



void Player::printValues(){
    cout << "Player gravity: " << this->gravity << endl;
    cout << "Player x direction: " << this->direction.x  << endl;
    cout << "Player y direction: " << this->direction.y << endl;
    cout << "Player jump speed: " << this->jump_speed << endl;
}



void Player::update(){
    this->getInput();
    this->animate();
    return;
}



void Player::clear(){
    SDL_DestroyTexture(this->texture);
    return;
}