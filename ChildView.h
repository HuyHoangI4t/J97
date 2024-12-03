#pragma once
#include "Maze.h"
#include "Player.h"
#include "Boom.h"
#include "Enemy.h"
#include "afxmt.h"


class CChildView : public CWnd {
private:
        // Thời gian bắt đầu trò chơi
    CString timeDisplay;  // Thời gian chơi
    
    bool gameOver;

public:
    int size;
    Maze maze;
    Player player;
    Boom activeBomb;
    Enemy enemies[2];

    CChildView();
    virtual ~CChildView();
    void OnGameOver(bool win);
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    afx_msg void OnPaint();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    DECLARE_MESSAGE_MAP()
};
