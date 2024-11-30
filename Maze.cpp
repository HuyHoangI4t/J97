#include "pch.h"
#include "Maze.h"

int full[13][15] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 0, 1, 0, 1},
    {1, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

Maze::Maze() {
    size = 50;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            maze[i][j] = full[i][j];
}

void Maze::draw(CDC* dc) const {
    CImage roadImage, blockImage, wallImage, itemImage;
    roadImage.Load(_T("res/road.png"));   // Hình ảnh ô đi được
    blockImage.Load(_T("res/block.png")); // Hình ảnh ô bị chặn
    wallImage.Load(_T("res/wall.png"));   // Hình ảnh ô tường
    itemImage.Load(_T("res/item.png"));   // Hình ảnh item

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Xác định vị trí của ô
            CRect cellRect(j * size, i * size, (j + 1) * size, (i + 1) * size);

            // Vẽ viền ô (nếu cần)
            dc->Rectangle(&cellRect);

            // Vẽ hình ảnh tùy theo loại ô
            if (maze[i][j] == 0) {
                roadImage.Draw(dc->GetSafeHdc(), cellRect);  // Ô đi được
            }
            else if (maze[i][j] == 2) {
                blockImage.Draw(dc->GetSafeHdc(), cellRect); // Ô bị chặn
            }
            else if (maze[i][j] == 1) {
                wallImage.Draw(dc->GetSafeHdc(), cellRect);  // Ô tường
            }
            else if (maze[i][j] == 3) {
                itemImage.Draw(dc->GetSafeHdc(), cellRect);  // Vẽ item
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

int Maze::GetRows() const {
    return rows;
}

int Maze::GetCols() const {
    return cols;
}

// Thêm item vào vị trí (x, y)
void Maze::AddItem(int x, int y) {
    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        maze[x][y] = 3;  // Giả sử mã item là 3
    }
}

// Xóa item tại vị trí (x, y)
void Maze::RemoveItem(int x, int y) {
    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        maze[x][y] = 0;  // Xóa item (chuyển về ô đường đi)
    }
}

// Xử lý nổ bom và sinh item
void Maze::ExplosionAndItem(int bombX, int bombY, int range) {
    // Duyệt qua các ô xung quanh bom trong phạm vi nổ
    for (int i = -range; i <= range; ++i) {
        for (int j = -range; j <= range; ++j) {
            int x = bombX + i;
            int y = bombY + j;
            if (x >= 0 && x < rows && y >= 0 && y < cols) {
                // Kiểm tra xem ô có phải là chướng ngại vật (value = 2)
                if (maze[x][y] == 2) {
                    // Chuyển chướng ngại vật thành đường đi (value = 0)
                    maze[x][y] = 0;

                    // Sinh item ngẫu nhiên với xác suất nhất định
                    if (rand() % 2 == 0) { // 50% xác suất sinh item
                        maze[x][y] = 3;  // Ví dụ: 3 là mã item
                    }
                }
            }
        }
    }
}


