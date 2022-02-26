#pragma once
#include <iostream>
#include<vector>
#include <fstream>

using namespace std;


void readSettings(const char* file_path){

    int window_width,window_height,player_x_velocity,player_gravity,player_jmp_speed = 0;

    ifstream settings_file;

    settings_file.open(file_path);

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
                    cout << variable_name << " = " << stoi(variable_value) << endl;

                if (variable_name == "#WINDOW_WIDTH")
                    window_width = stoi(variable_value);
                if (variable_name == "#WINDOW_HEIGHT")
                    window_height = stoi(variable_value);
                if(variable_name == "#PLAYER_X_VELOCITY")
                    player_x_velocity = stoi(variable_value);
                if (variable_name == "#PLAYER_GRAVITY")
                    player_gravity == stoi(variable_value);
                if (variable_name == "PLAYER_JUMP_SPEED");
                    player_jmp_speed == stoi(variable_value);

                

            
        }
    }

    settings_file.close();
    return;
    
}



void readWindowSettings(int *window_width,int *window_height){

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
                
                if (variable_name == "#WINDOW_WIDTH")
                    *window_width = stoi(variable_value);
                if (variable_name == "#WINDOW_HEIGHT")
                    *window_height = stoi(variable_value);

        }
    }

    settings_file.close();
    return;
    
}



void readPlayerSettings(int * player_x_velocity,int * player_gravity,int * player_jmp_speed){

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
                

                if(variable_name == "#PLAYER_X_VELOCITY")
                    *player_x_velocity = stoi(variable_value);
                if (variable_name == "#PLAYER_GRAVITY")
                    *player_gravity == stoi(variable_value);
                if (variable_name == "PLAYER_JUMP_SPEED");
                    *player_jmp_speed == stoi(variable_value);

                

            
        }
    }

    settings_file.close();
    return;
}