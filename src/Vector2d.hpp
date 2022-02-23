#pragma once

#include<iostream>

typedef struct Vector2d
{
    int x;
    int y;
    Vector2d(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
}Vector2d;
