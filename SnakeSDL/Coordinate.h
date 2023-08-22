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
        if (x < 0) x = xMax;
        else if (x > xMax) x = 0;
        if (y < 0) y = yMax;
        else if (y > yMax) y = 0;
    }

    int getX() const { return x; }
    int getY() const { return y; }

};

