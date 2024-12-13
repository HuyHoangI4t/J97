#pragma once
#include "atlimage.h"
#include "Maze.h"

class Player {
private:
    int x, y;                 
public:
    Player();
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    void Draw(CDC* dc) const; 
    void MoveUp(const Maze& maze);
    void MoveDown(const Maze& maze);
    void MoveLeft(const Maze& maze);
    void MoveRight(const Maze& maze);
};
