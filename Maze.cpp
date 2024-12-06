#include "pch.h"
#include "Maze.h"


int full[13][15] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 2, 2, 2, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1},
    {1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 0, 1, 0, 1},
    {1, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};



const int(*Maze::GetMaze() const)[15]
{
    return maze;
}

Maze::Maze() : size(50)  {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maze[i][j] = full[i][j];
        }
    }
}

void Maze::draw(CDC* dc) const {
    CImage roadImage, blockImage, wallImage;
    HRESULT hr = roadImage.Load(_T("res/road.png"));
    HRESULT hr1 = blockImage.Load(_T("res/block.png"));
    HRESULT hr2 = wallImage.Load(_T("res/wall1.png"));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            CRect cellRect(j * size, i * size, (j + 1) * size, (i + 1) * size);
            if (maze[i][j] == 0) {
                roadImage.Draw(dc->GetSafeHdc(), cellRect);
            }
            else if (maze[i][j] == 1) {
                wallImage.Draw(dc->GetSafeHdc(), cellRect);
            }
            else if (maze[i][j] == 2) {
                blockImage.Draw(dc->GetSafeHdc(), cellRect);
            }                                             
        }
    }
}

int Maze::GetCell(int row, int col) const {

    return maze[row][col];
}

void Maze::SetCell(int row, int col, int value) {
    maze[row][col] = value;
}

void Maze::Explosion(int bombX, int bombY, int range) {
    for (int r = 1; r <= range; ++r) {
        // Nổ lên (Chỉ nổ lên nếu không gặp tường)
        if (bombY - r >= 0 && maze[bombY - r][bombX] != 1) {  // Nếu không gặp tường và không vượt quá biên giới
            maze[bombY - r][bombX] = 0;  // Xóa vật cản
        }

        // Nổ xuống (Chỉ nổ xuống nếu không gặp tường)
        if (bombY + r < rows && maze[bombY + r][bombX] != 1) {  // Nếu không gặp tường và không vượt quá biên giới
            maze[bombY + r][bombX] = 0;  // Xóa vật cản
        }

        // Nổ trái (Chỉ nổ trái nếu không gặp tường)
        if (bombX - r >= 0 && maze[bombY][bombX - r] != 1) {  // Nếu không gặp tường và không vượt quá biên giới
            maze[bombY][bombX - r] = 0;  // Xóa vật cản
        }

        // Nổ phải (Chỉ nổ phải nếu không gặp tường)
        if (bombX + r < cols && maze[bombY][bombX + r] != 1) {  // Nếu không gặp tường và không vượt quá biên giới
            maze[bombY][bombX + r] = 0;  // Xóa vật cản
        }
    }
}



