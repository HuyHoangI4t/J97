#pragma once
#include "Maze.h"
#include "Player.h"
#include "Boom.h"
#include "Enemy.h"
#include "vector"

class CChildView : public CWnd {
private:
    bool gameOver;               // Trạng thái kết thúc game
    int size;                    // Kích thước ô vuông
    Maze maze;                   // Bản đồ
    Player player;               // Nhân vật
    Boom activeBomb;             // Bom hiện tại
    std::vector<Enemy> enemies;  // Danh sách kẻ địch
    bool gameWon;
public:
    CChildView();
    virtual ~CChildView();
    void OnGameOver(bool win);
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    afx_msg void OnPaint();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()
};
