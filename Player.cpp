#include "pch.h"
#include "Player.h"


Player::Player() : x(1), y(11) {}

void Player::setX(int x) {
    this->x = x;
}

void Player::setY(int y) {
    this->y = y;
}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

void Player::Draw(CDC* dc) const {
    int size = 50;
    CImage playerImage;
    HRESULT hr = playerImage.Load(_T("res/player.png"));
    CRect playerRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
    playerImage.Draw(dc->GetSafeHdc(), playerRect);
}

void Player::MoveUp(const Maze& maze) {
    if (maze.GetCell(y - 1, x) == 0) { 
        y--;
    }
}

void Player::MoveDown(const Maze& maze) {
    if (maze.GetCell(y + 1, x) == 0) {  
        y++;
    }
}

void Player::MoveLeft(const Maze& maze) {
    if (maze.GetCell(y, x - 1) == 0) {  
        x--;
    }
}

void Player::MoveRight(const Maze& maze) {
    if (maze.GetCell(y, x + 1) == 0) { 
        x++;
    }
}