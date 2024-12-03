#pragma once
#include "Maze.h"
#include "atlimage.h"

class Enemy {
private:
    int x, y;              // Tọa độ của kẻ địch
    Maze* maze;            // Con trỏ tới bản đồ để kiểm tra di chuyển hợp lệ
    CImage enemyImage;     // Hình ảnh kẻ địch
   

public:
     Enemy(int startX = 1, int startY = 1);  // Khởi tạo vị trí ban đầu
    ~Enemy();

    void SetPosition(int x, int y);
    int GetX() const;
    int GetY() const;
    void Move(const int map[13][15], int rows, int cols);  // Di chuyển kẻ địch
    void Draw(CDC* dc) const;
    bool IsDestroyed(int bombX, int bombY, int range) const; // Bị tiêu diệt nếu trong phạm vi bom
};
