#pragma once

class Maze {
private:
    static const int rows = 15;
    static const int cols = 15;
    int maze[rows][cols];
    int size;  
public:
    const int(*GetMaze() const)[15];                            // Hàm trả về con trỏ ma trận mê cung , dùng cho enemy
    Maze();  
    int GetRows() const;
    int GetCols() const;
    void draw(CDC* dc) const;
    int GetCell(int row, int col) const;
    void SetCell(int row, int col, int value);
    void Explosion(int bombX, int bombY, int range);            
    void ClearExplosion();
};
