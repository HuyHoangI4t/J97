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
    // Đặt vị trí bom thành -1 (bom phát nổ tại vị trí này)
    SetCell(bombY, bombX, -1);

    // Các hướng (trên, dưới, trái, phải)
    int directions[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

    for (auto& dir : directions) {
        bool canExplode = true;  // Biến kiểm tra xem có thể nổ tiếp hay không
        for (int r = 1; r <= range; r++) {
            int newY = bombY + dir[0] * r;
            int newX = bombX + dir[1] * r;

            // Kiểm tra phạm vi hợp lệ (tránh ra ngoài biên)
            if (newY < 0 || newY >= rows || newX < 0 || newX >= cols) {
                break;
            }

            int cell = GetCell(newY, newX);

            // Nếu gặp tường (ô có giá trị 1), set giá trị thành -1 và dừng nổ
            if (cell == 1) {
                break; // Dừng nổ ở tường
            }
            // Nếu gặp block (ô có giá trị 2), set giá trị thành -1 nhưng không tạo hiệu ứng nổ
            else if (cell == 2) {
                SetCell(newY, newX, -1);

                break;  // Ngừng nổ tại đây, không lan sang các ô khác
            }
            
            else {
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

