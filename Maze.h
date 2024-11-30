#pragma once
#include "pch.h"

class Maze {
public:
    static const int rows = 13;
    static const int cols = 15;
    int maze[rows][cols];
    int size; // Kích thước mỗi ô

    Maze();
    void draw(CDC* dc) const; // Vẽ bản đồ
    int GetCell(int row, int col) const; // Lấy giá trị của ô tại (row, col)
    void SetCell(int row, int col, int value); // Thiết lập giá trị cho ô tại (row, col)
    int GetRows() const; // Lấy số hàng
    int GetCols() const; // Lấy số cột
    void AddItem(int x, int y); // Thêm item vào vị trí (x, y)
    void RemoveItem(int x, int y); // Xóa item tại vị trí (x, y)

    void ExplosionAndItem(int bombX, int bombY, int range); // Xử lý nổ bom và sinh item
};
