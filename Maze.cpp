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

Maze::Maze(): rows(13),cols(15), size(50)
{
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j) {
			maze[i][j] = full[i][j];
		}
	}
}

void Maze::draw(CDC* dc) const
{
	CImage roadImage, blockImage, wallImage;
	roadImage.Load(_T("res/road.png"));   // Hình ảnh ô đi được
	blockImage.Load(_T("res/block.png")); // Hình ảnh ô bị chặn
	wallImage.Load(_T("res/wall.png"));   // Hình ảnh ô tường

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
		}
	}
}

int Maze::GetCell(int row, int col) const
{
	return maze[row][col];
}

void Maze::SetCell(int row, int col, int value)
{
	if (row >= 0 && row < rows && col >= 0 && col < cols)
	{
		maze[row][col] = value;
	}
}

int Maze::GetRows() const
{
	return rows;
}

int Maze::GetCols() const
{
	return cols;
}

void Maze::AddItem(int x, int y)
{
}

void Maze::RemoveItem(int x, int y)
{
}
