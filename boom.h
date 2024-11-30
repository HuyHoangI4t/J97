#pragma once
#include "pch.h"

class boom {
public:
    int x, y;                   // Tọa độ của bom trong ma trận
    int range;                  // Phạm vi nổ của bom
    DWORDLONG activationTime;       // Thời gian bom được kích hoạt
    bool isActive;              // Trạng thái của bom (đã kích hoạt hay chưa)
    bool isExploded;            // Trạng thái bom đã nổ hay chưa

    boom(int x = 0, int y = 0, int range = 1);

    void SetPosition(int x, int y);  // Đặt vị trí bom
    void SetRange(int range);        // Đặt phạm vi nổ
    void Activate();                 // Kích hoạt bom
    void Update();                   // Cập nhật trạng thái bom (kiểm tra thời gian nổ)
    bool IsExploded() const;         // Kiểm tra xem bom đã nổ hay chưa
    bool GetActiveState() const;     // Trả về trạng thái bom
    void Draw(CDC* dc) const;        // Vẽ bom trên màn hình
    int GetX() const;                // Lấy tọa độ X
    int GetY() const;                // Lấy tọa độ Y
    int GetRange() const;            // Lấy phạm vi nổ
};
