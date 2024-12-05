#pragma once
#include <atlimage.h>

class Maze {
private:
    static const int rows = 13;
    static const int cols = 15;
    int maze[rows][cols];
    int size;  // Kích thước mỗi ô


public:
 const int(*GetMaze() const)[15]; // Khai báo hàm trả về con trỏ ma trận
    Maze();
    void draw(CDC* dc) const;
    int GetCell(int row, int col) const;
    void SetCell(int row, int col, int value);
    int GetRows() const { return rows; }
    int GetCols() const { return cols; }
    void Explosion(int bombX, int bombY, int range);
};
