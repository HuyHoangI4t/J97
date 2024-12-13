#include "pch.h"
#include "Boom.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


Boom::Boom() : x(-1), y(-1), range(0), isActive(false), isExploded(false),size(50) {}

void Boom::SetPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Boom::SetRange(int newRange) {
    range = newRange;
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
}

void Boom::Reset() {
    isActive = false;
    isExploded = false;
    
}

bool Boom::IsExploded() const {
    return isExploded;
}

void Boom::Update(Maze& maze) {
    if (isActive && !isExploded) {
        Explode(maze); 
    }
}

void Boom::Explode(Maze& maze) {
    isExploded = true;  
    maze.Explosion(x, y, range); 
}

void Boom::Draw(CDC* dc) const {
   bool imagesLoaded = false;
   CImage bombImage, explosionImage;
   bombImage.Load(_T("res/bomb.png"));
   explosionImage.Load(_T("res/explosion.png"));
    if (isActive && !isExploded) {
        DrawBomb(dc, bombImage);  
    } 
}

void Boom::DrawBomb(CDC* dc, const CImage& bombImage) const {
    // Vẽ bom ở vị trí (x, y)
    CRect bombRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
    bombImage.Draw(dc->GetSafeHdc(), bombRect);
}

