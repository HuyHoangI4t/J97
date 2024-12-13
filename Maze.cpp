#include "pch.h"
#include "Maze.h"


int full[15][15] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 2, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1},
    {1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
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

int Maze::GetRows() const {
    return rows;
}
int Maze::GetCols() const {
    return cols;
}

void Maze::draw(CDC* dc) const {
    CImage roadImage, blockImage, wallImage, exImage;
    HRESULT hr = roadImage.Load(_T("res/road.png"));
    HRESULT hr1 = blockImage.Load(_T("res/block.png"));
    HRESULT hr2 = wallImage.Load(_T("res/wall.png"));
    HRESULT ex = exImage.Load(_T("res/explosion.png"));
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
            else if (maze[i][j] == -1) {
                exImage.Draw(dc->GetSafeHdc(), cellRect);
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
    SetCell(bombY, bombX, -1);
    int directions[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
    for (auto& dir : directions) {
        for (int r = 1; r <= range; r++) {
            int newY = bombY + dir[0] * r;
            int newX = bombX + dir[1] * r;
            if (newY < 0 || newY >= rows || newX < 0 || newX >= cols)   break;
            int cell = GetCell(newY, newX);
            if (cell == 1)  break;
            else if (cell == 2) {
                SetCell(newY, newX, -1); break;  
            } else {
                SetCell(newY, newX, -1); 
            }
        }
    }
}

void Maze::ClearExplosion() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == -1) {
                maze[i][j] = 0; 
            }
        }
    }
}

