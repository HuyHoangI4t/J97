#include "pch.h"
#include "Boom.h"

Boom::Boom() : x(0), y(0), range(1), isActive(false), isExploded(false), activationTime(0) {

}

Boom::~Boom() {
    if (!bombImage.IsNull()) {
        bombImage.Destroy();
    }
    if (!explosionImage.IsNull()) {
        explosionImage.Destroy();
    }
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

void Boom::Update() const {
    if (isActive && !isExploded) {
        if (std::difftime(std::time(nullptr), activationTime) >= 2) {
           /* isExploded = true;*/
        }
    }
}

void Boom::Draw(CDC* dc) const {
    CImage bombImage, explosionImage;
    HRESULT hr = bombImage.Load(_T("res/bomb.png"));
    HRESULT hr1 = explosionImage.Load(_T("res/explosion.png"));
    int size = 50;
    if (isActive && !isExploded) {
        CRect bombRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
        bombImage.Draw(dc->GetSafeHdc(), bombRect);
    }
    else if (isExploded) {
        for (int dx = -range; dx <= range; ++dx) {
            for (int dy = -range; dy <= range; ++dy) {
                CRect explosionRect((x + dx) * size, (y + dy) * size,
                    (x + dx + 1) * size, (y + dy + 1) * size);
                /*explosionImage.Draw(dc->GetSafeHdc(), explosionRect);*/
                dc->Ellipse(explosionRect);
            }
        }
    }
  
        //int size = 50;  // Kích thước ô

        //if (isActive && !isExploded) {
        //    // Vẽ bom dưới dạng elip tại vị trí (x, y)
        //    CRect bombRect(x * size, y * size, (x + 1) * size, (y + 1) * size);
        //    dc->SelectStockObject(DC_PEN);  // Chọn bút vẽ
        //    dc->SetDCPenColor(RGB(255, 0, 0));  // Đặt màu bom là đỏ (RGB)
        //    dc->Ellipse(bombRect);  // Vẽ elip tại vị trí của bom
        //}
        //else if (isExploded) {
        //    // Vẽ hiệu ứng nổ dưới dạng elip, sử dụng màu khác cho nổ
        //    dc->SetDCPenColor(RGB(255, 165, 0));  // Màu cam cho hiệu ứng nổ
        //    for (int i = -range; i <= range; ++i) {
        //        for (int j = -range; j <= range; ++j) {
        //            int newX = x + j;
        //            int newY = y + i;
        //            CRect explosionRect(newX * size, newY * size, (newX + 1) * size, (newY + 1) * size);
        //            dc->Ellipse(explosionRect);  // Vẽ hiệu ứng nổ dưới dạng elip
        //        }
        //    }
        //}
    
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
