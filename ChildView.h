#pragma once
#include "Maze.h"
#include "Player.h"
#include "boom.h"

class CChildView : public CWnd
{
private:
    DWORD startTime;      // Thời điểm bắt đầu trò chơi
    CString timeDisplay;

public:
    int size;
    Maze maze;
    Player player;
    boom Bom;

    CChildView();
    virtual ~CChildView();

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    afx_msg void OnPaint();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    DECLARE_MESSAGE_MAP()
};
