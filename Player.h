#pragma once
#include "atlimage.h"

class Player {
private:
    int x, y;                 // Tọa độ nhân vật
    CImage playerImage;       // Hình ảnh nhân vật

public:
    Player();
    ~Player();

    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    void Draw(CDC* dc) const; // Vẽ nhân vật
};
