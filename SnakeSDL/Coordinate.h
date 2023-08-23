#pragma once
class Coordinate 
{
private:
    int x;
    int y;

public:
    Coordinate() { x = 0; y = 0; }
    Coordinate(int xVal, int yVal, int xMax, int yMax) : x(xVal), y(yVal)
    {
        if (x < 0) x = xMax - 1;
        else if (x > xMax - 1) x = 0;
        if (y < 0) y = yMax - 1;
        else if (y > yMax - 1) y = 0;
    }

    int getX() const { return x; }
    int getY() const { return y; }

};

