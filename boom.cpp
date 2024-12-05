#include "pch.h"
#include "Boom.h"
#include "Maze.h" 

Boom::Boom() : x(-1), y(-1), range(1), isActive(false), isExploded(false) {
  
}



void Boom::SetPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Boom::SetRange(int newRange) {
    range = newRange;
}

int Boom::GetX() const
{
    return x;
}

int Boom::GetY() const
{
    return y;
}

int Boom::GetRange() const
{
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

void Boom::Update(Maze& maze) {
    // Kiểm tra bom có nổ chưa
    if (isActive && !isExploded) {
        Explode(maze);  // Gọi hàm Explode để xử lý vụ nổ
    }
}

void Boom::Explode(Maze& maze) {
    isExploded = true;  // Đánh dấu bom đã nổ
    maze.Explosion(x, y, range);  // Cập nhật maze với vụ nổ
}

bool Boom::IsExploded() const
{
    return false;
}

void Boom::Draw(CDC* dc) const {
    CImage bombImage, explosionImage;
    HRESULT b = bombImage.Load(_T("res/bomb.png"));
    HRESULT ex = explosionImage.Load(_T("res/explosion.png"));

    int size = 40;
    if (isActive && !isExploded) {
        CRect bombRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
        bombImage.Draw(dc->GetSafeHdc(), bombRect);  // Vẽ bom nếu nó còn hoạt động
    }
    else if (isExploded) {
        for (int dx = -range; dx <= range; ++dx) {
            for (int dy = -range; dy <= range; ++dy) {
                int nx = x + dx;
                int ny = y + dy;

                // Kiểm tra ô nằm trong phạm vi bản đồ
                if (nx >= 0 && nx < 13 && ny >= 0 && ny < 15) {
                    CRect explosionRect(nx * size, ny * size, (nx + 1) * size, (ny + 1) * size);
                    explosionImage.Draw(dc->GetSafeHdc(), explosionRect);  // Vẽ hiệu ứng vụ nổ
                }
            }
        }
    }
}
