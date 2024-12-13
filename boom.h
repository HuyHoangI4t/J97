#pragma once
#include "Maze.h"

class Boom {
private:
    int x, y;
    int range;       
    bool isActive;   
    bool isExploded; 
    int size;
public:
    Maze maze;
    Boom();
    void SetPosition(int newX, int newY);
    void SetRange(int newRange);
    int GetX() const;
    int GetY() const;
    int GetRange() const;
    void Activate();
    void Reset();                           
    bool IsExploded() const;                
    void Update(Maze& maze);                
    void Explode(Maze& maze);              
    void Draw(CDC* dc) const;
    void DrawBomb(CDC* dc, const CImage& bombImage) const;
  
};