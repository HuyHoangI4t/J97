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
void Enemy::RandomTarget(const int maze[15][15], int rows, int cols) {
    std::mt19937 gen(static_cast<unsigned int>(time(0))); 
    std::uniform_int_distribution<> distribX(1, cols - 2); 
    std::uniform_int_distribution<> distribY(1, rows - 2); 

    do {
        targetX = distribX(gen);  
        targetY = distribY(gen);
    } while (maze[targetY][targetX] != 0);  
}

void Enemy::Move(const int maze[15][15], int rows, int cols) {
    if (x == targetX && y == targetY) {
        RandomTarget(maze, rows, cols);
    }
    if (x < targetX && maze[y][x + 1] == 0) {                                    
        x++;
    } else if (x > targetX && maze[y][x - 1] == 0) {                                 
        x--;
    } else if (y < targetY && maze[y + 1][x] == 0) {                               
        y++;
    } else if (y > targetY && maze[y - 1][x] == 0) {                                 
        y--;
    } else {
        RandomTarget(maze, rows, cols); 
    }
}

void Enemy::Draw(CDC* dc) const {
    CImage enemyImage; 
    HRESULT hr = enemyImage.Load(_T("res/enemy2.png"));                             
    CRect enemyRect(x * size, y * size, (x + 1) * size, (y + 1) * size);            
    enemyImage.Draw(dc->GetSafeHdc(), enemyRect);                                 
}

