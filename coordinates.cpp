#include "coordinates.h"

Coordinates::Coordinates(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Coordinates::getX() {
    return x;
}

int Coordinates::getY() {
    return y;
}

