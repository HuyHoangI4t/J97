#include "pch.h"
#include "boom.h"

boom::boom(int x, int y, int range) : x(x), y(y), range(range), isActive(false), activationTime(0), isExploded(false) {}

void boom::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void boom::SetRange(int range) {
    this->range = range;
}

void boom::Activate() {
    isActive = true;                // Kích hoạt bom
    isExploded = false;             // Đảm bảo bom chưa nổ
    activationTime = GetTickCount64(); // Ghi lại thời gian khi bom được đặt
}

void boom::Update() {
    if (isActive && !isExploded) {
        DWORDLONG currentTime = GetTickCount64();
        // Nếu đã qua 2 giây (2000ms), bom sẽ nổ
        if (currentTime - activationTime >= 2000) {
            isExploded = true; // Đánh dấu bom đã nổ
        }
    }
}

bool boom::IsExploded() const {
    return isExploded;
}

bool boom::GetActiveState() const {
    return isActive;
}

void boom::Draw(CDC* dc) const {
    if (isActive) {
        CImage bombImage;
        bombImage.Load(_T("res/bomb.png")); // Đường dẫn đến hình ảnh của bom
        CRect bombRect(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
        bombImage.Draw(dc->GetSafeHdc(), bombRect);
    }
}

int boom::GetX() const {
    return x;
}

int boom::GetY() const {
    return y;
}

int boom::GetRange() const {
    return range;
}
