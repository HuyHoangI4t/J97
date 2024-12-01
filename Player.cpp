#include "pch.h"
#include "Player.h"

Player::Player() : x(1), y(1) {
    if (FAILED(playerImage.Load(_T("res/player.png")))) {
        AfxMessageBox(_T("Failed to load player image!"));
    }
}

Player::~Player() {
  
}

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
