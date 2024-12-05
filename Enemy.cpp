#include "pch.h"
#include "Enemy.h"
#include <random>
#include <ctime>

Enemy::Enemy(int startX, int startY) : x(startX), y(startY), size(40), targetX(startX), targetY(startY) {}

int Enemy::GetX() const {
    return x;
}

int Enemy::GetY() const {
    return y;
}

void Enemy::SetPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

// Hàm chọn mục tiêu mới ngẫu nhiên
void Enemy::RandomTarget(const int maze[13][15], int rows, int cols) {
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<> distribX(1, cols - 2);  // Chỉ chọn trong phạm vi không đụng tường
    std::uniform_int_distribution<> distribY(1, rows - 2);

    do {
        targetX = distribX(gen);
        targetY = distribY(gen);
    } while (maze[targetY][targetX] != 0);  // Chỉ chọn ô trống (giá trị 0)
}

// Hàm di chuyển đơn giản
void Enemy::Move(const int maze[13][15], int rows, int cols) {
    // Nếu đã đến mục tiêu, chọn mục tiêu mới
    if (x == targetX && y == targetY) {
        RandomTarget(maze, rows, cols);
    }

    // Thử di chuyển về phía mục tiêu
    if (x < targetX && maze[y][x + 1] == 0) {  // Nếu mục tiêu ở bên phải
        x++;
    }
    else if (x > targetX && maze[y][x - 1] == 0) {  // Nếu mục tiêu ở bên trái
        x--;
    }
    else if (y < targetY && maze[y + 1][x] == 0) {  // Nếu mục tiêu ở phía dưới
        y++;
    }
    else if (y > targetY && maze[y - 1][x] == 0) {  // Nếu mục tiêu ở phía trên
        y--;
    }
    else {
        // Nếu không thể di chuyển (bị chặn bởi tường), chọn lại mục tiêu
        RandomTarget(maze, rows, cols);
    }
}

void Enemy::Draw(CDC* dc) const {
    CImage enemyImage;
    HRESULT hr = enemyImage.Load(_T("res/enemy.png"));
    /*HRESULT hr2 = enemyImage.Load(_T("res/enemy2.png"));*/
    CRect enemyRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
    enemyImage.Draw(dc->GetSafeHdc(), enemyRect);
}

bool Enemy::IsDestroyed(int bombX, int bombY, int range) const {
    return abs(x - bombX) <= range && abs(y - bombY) <= range;
}
