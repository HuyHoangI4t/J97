#pragma once
#include <atlimage.h>

class Maze {
private:
    static const int rows = 13;
    static const int cols = 15;
    int maze[rows][cols];
    int size;  

public:
    
    const int(*GetMaze() const)[15];                            // Hàm trả về con trỏ ma trận mê cung, kiểu con trỏ là mảng 2 chiều có 15 cột
    Maze();  
    void draw(CDC* dc) const;
    int GetCell(int row, int col) const;
    void SetCell(int row, int col, int value);
    int GetRows() const { 
        return rows;
    }
    int GetCols() const {
        return cols;
    }
    void Explosion(int bombX, int bombY, int range);            // Hàm mô phỏng sự nổ của bom trong phạm vi nhất định
};
