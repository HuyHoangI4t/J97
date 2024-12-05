#include "pch.h"
#include "Maze.h"


int full[13][15] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 2, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 2, 2, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};



const int(*Maze::GetMaze() const)[15]
{
    return maze;
}

Maze::Maze() : size(40)  {
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
    int dx[] = { -1, 1, 0, 0 };  // Di chuyển theo các hướng (lên, xuống, trái, phải)
    int dy[] = { 0, 0, -1, 1 };

    // Xử lý vụ nổ theo từng hướng
    for (int dir = 0; dir < 4; ++dir) {
        for (int step = 1; step <= range; ++step) {
            int x = bombX + dx[dir] * step;
            int y = bombY + dy[dir] * step;

            // Kiểm tra nếu ô nằm trong phạm vi bản đồ
            if (x < 0 || x >= rows || y < 0 || y >= cols)
                break;

            int cellValue = maze[x][y];
            
            // Nếu gặp tường, dừng vụ nổ tại đó
            if (cellValue == 1) 
                break;

            // Nếu gặp chướng ngại vật, phá hủy nó và dừng vụ nổ
            if (cellValue == 2) {
                maze[x][y] = 0;  // Thay chướng ngại vật thành đường đi
                break;
            }
        }
    }
}

