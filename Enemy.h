#pragma once
#include "atlimage.h"
#include "Maze.h"

class Enemy {
private:
    int x, y;         // Vị trí hiện tại của kẻ địch
    int size;         // Kích thước ô (mặc định là 50)
    CImage enemyImage; // Hình ảnh của kẻ địch
   
public:
    Enemy(int startX = 0, int startY = 0);
    ~Enemy();
    int map[13][15];
    void SetPosition(int x, int y); // Đặt vị trí mới cho kẻ địch
    int GetX() const;              // Lấy vị trí x
    int GetY() const;              // Lấy vị trí y
    void Move( int rows, int cols); // Di chuyển kẻ địch
    void Draw(CDC* dc) const;      // Vẽ kẻ địch
    bool IsDestroyed(int bombX, int bombY, int range) const; // Kiểm tra kẻ địch bị nổ
};
