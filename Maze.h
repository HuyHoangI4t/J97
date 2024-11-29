#pragma once
#include "vector"
class Maze
{
public:
    int rows;
    int cols;
    int size;
    int maze[13][15];  // Ma trận maze
    //std::vector<Item> items;  
    Maze();
    void draw(CDC* dc) const;
    int GetCell(int row, int col) const;
    void SetCell(int row, int col, int value);  // Thêm phương thức SetCell
    int GetRows() const;
    int GetCols() const;
    void AddItem(int x, int y);  // Thêm item vào maze
    void RemoveItem(int x, int y);  // Xóa item từ maze
};

