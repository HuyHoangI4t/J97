#include "pch.h"
#include "Enemy.h"
#include "random"

Enemy::Enemy(int startX, int startY) : x(startX), y(startY) ,size(40){

  
}

Enemy::~Enemy() {
    /*if (!enemyImage.IsNull()) {
        enemyImage.Destroy();
    }*/
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
    int steps = 3;
    for (int step = 0; step < steps; ++step) {
        int direction = rand() % 4;  // Chọn một hướng ngẫu nhiên

        // Xử lý di chuyển theo hướng
        switch (direction) {
        case 0:  // Di chuyển lên
            if (y > 0 && map[y - 1][x] == 0) {  // Kiểm tra không chạm tường
                y--;  // Di chuyển lên
            }
            break;

        case 1:  // Di chuyển xuống
            if (y < rows - 1 && map[y + 1][x] == 0) {  // Kiểm tra không chạm tường
                y++;  // Di chuyển xuống
            }
            break;

        case 2:  // Di chuyển trái
            if (x > 0 && map[y][x - 1] == 0) {  // Kiểm tra không chạm tường
                x--;  // Di chuyển trái
            }
            break;

        case 3:  // Di chuyển phải
            if (x < cols - 1 && map[y][x + 1] == 0) {  // Kiểm tra không chạm tường
                x++;  // Di chuyển phải
            }
            break;
        }
    }
}

void Enemy::Draw(CDC* dc) const {
   
    CImage enemyImage;
    HRESULT hr = enemyImage.Load(_T("res/enemy.png"));
    CRect enemyRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
    enemyImage.Draw(dc->GetSafeHdc(), enemyRect);
}

bool Enemy::IsDestroyed(int bombX, int bombY, int range) const {
    return abs(x - bombX) <= range && abs(y - bombY) <= range;
}
