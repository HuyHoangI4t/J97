#pragma once

class Enemy {
private:
    int x, y;  // Vị trí của kẻ địch
    int targetX, targetY;  // Vị trí mục tiêu
    int size;  // Kích thước mỗi ô

    // Chọn mục tiêu mới
    void RandomTarget(const int maze[13][15], int rows, int cols);

public:
    Enemy(int startX, int startY);

    int GetX() const;
    int GetY() const;

    void SetPosition(int newX, int newY);

    // Hàm di chuyển đơn giản
    void Move(const int maze[13][15], int rows, int cols);

    void Draw(CDC* dc) const;

    bool IsDestroyed(int bombX, int bombY, int range) const;
};
