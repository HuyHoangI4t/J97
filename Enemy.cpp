#include "pch.h"
#include "Enemy.h"
#include <random>
#include <ctime>

Enemy::Enemy(int startX, int startY) : x(startX), y(startY), size(50), targetX(startX), targetY(startY) {}

int Enemy::GetX() const {
    return x;
}

int Enemy::GetY() const {
    return y;
}



// Thuật toán của hàm này là chọn vị trí đích ngẫu nhiên trên bản đồ rồi đi tới đó nếu đi đến chọn lại đích
void Enemy::RandomTarget(const int maze[13][15], int rows, int cols) {
    std::mt19937 gen(static_cast<unsigned int>(time(0))); 
    std::uniform_int_distribution<> distribX(1, cols - 2);  // ngẫu nhiên cho tọa độ x (tránh tường)
    std::uniform_int_distribution<> distribY(1, rows - 2);  // ngẫu nhiên cho tọa độ y (tránh tường)

    do {
        targetX = distribX(gen);  // Chọn vị trí mục tiêu ngẫu nhiên
        targetY = distribY(gen);
    } while (maze[targetY][targetX] != 0);  // Lặp lại cho đến khi chọn được ô trống (giá trị 0)
}

// Hàm di chuyển kẻ địch trong mê cung
void Enemy::Move(const int maze[13][15], int rows, int cols) {

    // Nếu kẻ địch đã đến mục tiêu, chọn lại mục tiêu mới
    if (x == targetX && y == targetY) {
        RandomTarget(maze, rows, cols);  
    }

    // Di chuyển kẻ địch về phía mục tiêu nếu ô kế tiếp là ô trống
    if (x < targetX && maze[y][x + 1] == 0) {                                       // Nếu mục tiêu ở bên phải
        x++;
    }
    else if (x > targetX && maze[y][x - 1] == 0) {                                  // Nếu mục tiêu ở bên trái
        x--;
    }
    else if (y < targetY && maze[y + 1][x] == 0) {                                  // Nếu mục tiêu ở phía dưới
        y++;
    }
    else if (y > targetY && maze[y - 1][x] == 0) {                                  // Nếu mục tiêu ở phía trên
        y--;
    }
    else {
        RandomTarget(maze, rows, cols);                                             // Nếu không thể di chuyển (bị chặn bởi tường), chọn lại mục tiêu
    }
}

void Enemy::Draw(CDC* dc) const {
    CImage enemyImage; 
    HRESULT hr = enemyImage.Load(_T("res/enemy.png"));                              // Tải hình ảnh kẻ địch từ file
    /*HRESULT hr2 = enemyImage.Load(_T("res/enemy2.png"));*/  
    CRect enemyRect(x * size, y * size, (x + 1) * size, (y + 1) * size);            // Định nghĩa vị trí vẽ kẻ địch
    enemyImage.Draw(dc->GetSafeHdc(), enemyRect);                                   // Vẽ hình ảnh kẻ địch lên màn hình tại vị trí đã xác định
}

