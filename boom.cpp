#include "pch.h"
#include "Boom.h"
#include "Maze.h"

Boom::Boom() : x(0), y(0), range(1), isActive(false), isExploded(false), activationTime(0) {

}

Boom::~Boom() {
   
}

void Boom::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Boom::SetRange(int range) {
    this->range = range;
}

int Boom::GetX() const {
    return x;
}

int Boom::GetY() const {
    return y;
}

int Boom::GetRange() const {
    return range;
}

void Boom::Activate() {
    isActive = true;
    isExploded = false;
    activationTime = std::time(nullptr);
}

void Boom::Update()  {
    if (isActive && !isExploded) {
        if (std::difftime(std::time(nullptr), activationTime) >= 2) {
            isExploded = true;
        }
    }
}

void Boom::Draw(CDC* dc) const {
    CImage bombImage, explosionImage;
    HRESULT hr = bombImage.Load(_T("res/bomb.png"));
    HRESULT hr1 = explosionImage.Load(_T("res/explosion.png"));
    int size = 40;
    if (isActive && !isExploded) {
        CRect bombRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
        if (!bombImage.IsNull()) {
            bombImage.Draw(dc->GetSafeHdc(), bombRect);
        }
    }
    else if (isExploded) {
        for (int dx = -range; dx <= range; ++dx) {
            for (int dy = -range; dy <= range; ++dy) {
                int nx = x + dx;
                int ny = y + dy;

                // Kiểm tra nếu ô nằm trong phạm vi bản đồ
                if (nx >= 0 && nx < 13 && ny >= 0 && ny < 15) {
                    
                        CRect explosionRect(nx * size, ny * size,
                            (nx + 1) * size, (ny + 1) * size);
                        if (!explosionImage.IsNull()) {
                            explosionImage.Draw(dc->GetSafeHdc(), explosionRect);
                        }
                    
                }
            }
        }
    }

    
}

bool Boom::IsExploded() const {
    return isExploded;
}

bool Boom::GetActiveState() const {
    return isActive;
}

void Boom::Reset() {
    isActive = false;
    isExploded = false;
}
