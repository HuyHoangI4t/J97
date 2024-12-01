#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(int startX, int startY) : x(startX), y(startY) {

  
}

Enemy::~Enemy() {
    
}

void Enemy::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Enemy::GetX() const {
    return x;
}

int Enemy::GetY() const {
    return y;
}

void Enemy::Move( int rows, int cols) {
    int maze[13][15];
    // Di chuyển kẻ địch ngẫu nhiên (trái, phải, lên, xuống)
    int direction = rand() % 4;  // Chọn một hướng ngẫu nhiên
    switch (direction) {
    case 0:  // Di chuyển lên
        if (y > 0 && maze[y - 1][x] ==0) {  // Kiểm tra không chạm tường
            y--;
        }
        break;
    case 1:  // Di chuyển xuống
        if (y < rows - 1 && maze[y + 1][x] == 0) {  // Kiểm tra không chạm tường
            y++;
        }
        break;
    case 2:  // Di chuyển trái
        if (x > 0 && maze[y][x - 1] == 0) {  // Kiểm tra không chạm tường
            x--;
        }
        break;
    case 3:  // Di chuyển phải
        if (x < cols - 1 && maze[y][x + 1] == 0) {  // Kiểm tra không chạm tường
            x++;
        }
        break;
    }
}

void Enemy::Draw(CDC* dc) const {
    int size = 50;
    CImage enemyImage;
    HRESULT hr = enemyImage.Load(_T("res/enemy.png"));
    CRect enemyRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
    enemyImage.Draw(dc->GetSafeHdc(), enemyRect);
}

bool Enemy::IsDestroyed(int bombX, int bombY, int range) const {
    return abs(x - bombX) <= range && abs(y - bombY) <= range;
}
