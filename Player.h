#pragma once

class Player
{
public:
	int x, y;
	int Bom;
	bool die;
    Player();
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    void Draw(CDC* dc);
};

