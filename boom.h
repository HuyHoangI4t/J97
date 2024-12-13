#pragma once
#include "Maze.h"

class Boom {
private:
    int x, y;
    int range;       // Phạm vi nổ của quả bom
    bool isActive;   // Trạng thái của quả bom có hoạt động hay không
    bool isExploded; // Trạng thái của quả bom đã nổ hay chưa
    int size;
public:
    Maze maze;

    Boom();
  
    void SetPosition(int newX, int newY);
    void SetRange(int newRange);
    int GetX() const;
    int GetY() const;
    int GetRange() const;
    void Activate();
    void Reset();                           // Đặt lại trạng thái của quả bom (khôi phục về trạng thái ban đầu)
    bool IsExploded() const;                // Kiểm tra xem quả bom đã nổ hay chưa
    void Update(Maze& maze);                // Cập nhật bom mỗi khi thời gian trôi qua
    void Explode(Maze& maze);               // Xử lý vụ nổ
    void Draw(CDC* dc) const;
    void DrawBomb(CDC* dc, const CImage& bombImage) const;
    void DrawExplosion(CDC* dc, const CImage& explosionImage) const;
};