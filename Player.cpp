#include "pch.h"
#include "Player.h"

Player::Player() :x(1),y(1)
{
}

void Player::setX(int x) {
	this->x = x;
}
void Player::setY(int y) {
	this->y = y;
}

int Player::getX() const
{
	return x;
}

int Player::getY() const
{
	return y;
}

void Player::Draw(CDC* dc)
{
	CImage playerImage;
	playerImage.Load(_T("res/player.png"));
	int size = 50; 
	CRect playerRect(x * size, y * size, (x + 1) * size, (y + 1) * size);

	// Vẽ hình ảnh người chơi
	playerImage.Draw(dc->GetSafeHdc(), playerRect);


}
