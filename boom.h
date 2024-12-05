#pragma once
#include "Maze.h"
#include <atlimage.h>
#include <ctime>


class Boom {
private:
    int x, y;                // Tọa độ bom
    int range;               // Phạm vi nổ
    bool isActive;           // Trạng thái bom
    bool isExploded;         // Trạng thái đã nổ
    std::time_t activationTime; // Thời gian kích hoạt

public:
    Boom();
  
    
    void SetPosition(int x, int y);
    void SetRange(int range);
    int GetX() const;
    int GetY() const;
    int GetRange() const;
    void Activate();
    void Update(Maze& maze);
    void Draw(CDC* dc) const;               // vẽ
    void Explode(Maze& maze);
    bool IsExploded() const;                // bom nổ
    void Reset();
};
