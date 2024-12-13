#pragma once

class Enemy {
private:
    int x, y; 
    int targetX, targetY;  
    int size;  
public:
    void RandomTarget(const int maze[15][15], int rows, int cols); 
    Enemy(int startX, int startY);                                       
    int GetX() const;
    int GetY() const;
    void Move(const int maze[15][15], int rows, int cols);                  
    void Draw(CDC* dc) const;
};
