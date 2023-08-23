#pragma once
#include "Coordinate.h"
#include "DirEnum.h"
#include "TurnEnum.h"

class SnakeCoordinate :
    public Coordinate
{
private:
    Dir orientation;
    Turn turn;

public:

    SnakeCoordinate(int xVal, int yVal, int xMax, int yMax, Dir orientation, Turn turn = Turn::straight) :
        Coordinate(xVal, yVal, xMax, yMax), orientation(orientation), turn(turn) {}

    Dir getOrientation() const
    {
        return orientation;
    }

    Turn getTurn() const
    {
        return turn;
    }

    void setOrientation(Dir orientationVal)
    {
        orientation = orientationVal;
    }

    void setTurn(Turn turnVal)
    {
        turn = turnVal;
    }
};

