#include "pch.h"
#include "Boom.h"
#include "Maze.h"


Boom::Boom() : x(-1), y(-1), range(0), isActive(false), isExploded(false) {}

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
        Explode(maze);  // Gọi hàm Explode để xử lý vụ nổ
    }
}

void Boom::Explode(Maze& maze) {
    isExploded = true;  // Đánh dấu bom đã nổ
    maze.Explosion(x, y, range);  // Cập nhật maze với vụ nổ
}

void Boom::Draw(CDC* dc) const {
    CImage bombImage, explosionImage;
    bombImage.Load(_T("res/bomb.png"));
    explosionImage.Load(_T("res/explosion.png"));
    int size = 50;

    // Vẽ bom nếu nó còn hoạt động
    if (isActive && !isExploded) {
        CRect bombRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
        bombImage.Draw(dc->GetSafeHdc(), bombRect);
    }
    // Vẽ vụ nổ nếu bom đã phát nổ
    else if (isExploded) {
        // Vẽ hình ảnh vụ nổ tại vị trí trung tâm
        explosionImage.Draw(dc->GetSafeHdc(),
            x * size, y * size,
            size, size);

        // Vẽ các vùng nổ xung quanh (hình chữ thập)
        for (int r = 1; r <= range; ++r) {
            // Vẽ hướng trên
            if (y - r >= 0) {
                explosionImage.Draw(dc->GetSafeHdc(),
                    x * size, (y - r) * size,
                    size, size);
            }
            // Vẽ hướng dưới
            if (y + r < 13) {
                explosionImage.Draw(dc->GetSafeHdc(),
                    x * size, (y + r) * size,
                    size, size);
            }
            // Vẽ hướng trái
            if (x - r >= 0) {
                explosionImage.Draw(dc->GetSafeHdc(),
                    (x - r) * size, y * size,
                    size, size);
            }
            // Vẽ hướng phải
            if (x + r < 15) {
                explosionImage.Draw(dc->GetSafeHdc(),
                    (x + r) * size, y * size,
                    size, size);
            }
        }
    }
}


