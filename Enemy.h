#pragma once

class Enemy {
private:
    int x, y; 
    int targetX, targetY;  
    int size;  
    void RandomTarget(const int maze[13][15], int rows, int cols);          // Hàm chọn mục tiêu ngẫu nhiên trong mê cung

public:
 
    Enemy(int startX, int startY);                                          // Hàm khởi tạo, nhận vị trí bắt đầu của kẻ địch
    int GetX() const;
    int GetY() const;
    void Move(const int maze[13][15], int rows, int cols);                  // Hàm di chuyển kẻ địch trong mê cung
    void Draw(CDC* dc) const;
};
