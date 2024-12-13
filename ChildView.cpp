#include "pch.h"
#include "framework.h"
#include "ChildView.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_KEYDOWN()
    ON_WM_TIMER()
    ON_WM_CREATE()
END_MESSAGE_MAP()

CChildView::CChildView() : size(50), gameOver(false), gameWon(false) {
    enemies.push_back(Enemy(13, 1));
    enemies.push_back(Enemy(13, 13));  
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    SetTimer(1, 1000, NULL);
    SetTimer(2, 50, NULL);
    SetTimer(3, 1000, NULL);
    return 0;
}

CChildView::~CChildView() {}

void CChildView::OnGameOver(bool win) {
    if (gameOver) return;  
    CString message = win ? _T("You win!") : _T("You lose!");
    MessageBox(message);
    gameOver = true;
    if (win)
        gameWon = true;
    Sleep(1000);
    PostQuitMessage(0);

}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) {
    if (!CWnd::PreCreateWindow(cs)) return FALSE;
    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);
    return TRUE;
    
}

void CChildView::OnPaint() {
    CPaintDC dc(this);
    maze.draw(&dc);    
    player.Draw(&dc); 
    for (auto& enemy : enemies) {
        enemy.Draw(&dc);
    }
    activeBomb.Draw(&dc);
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    CRect oldCell(player.getX() * size, player.getY() * size,(player.getX() + 1) * size, (player.getY() + 1) * size);
    switch (nChar) {
        case 'W': player.MoveUp(maze); break;  
        case 'A': player.MoveLeft(maze); break; 
        case 'S': player.MoveDown(maze); break; 
        case 'D': player.MoveRight(maze); break; 
        case VK_SPACE:
            if (!activeBomb.IsExploded()) {
                PlaySound(_T("res/activebomb.wav"), NULL, SND_FILENAME | SND_ASYNC);
                activeBomb.SetPosition(player.getX(), player.getY());
                activeBomb.SetRange(1);
                activeBomb.Activate();
                SetTimer(1, 1000, NULL);
            } break;
    }       
    CRect newCell(player.getX() * size, player.getY() * size,(player.getX() + 1) * size, (player.getY() + 1) * size);
    InvalidateRect(oldCell, TRUE);
    InvalidateRect(newCell, TRUE);
}

void CChildView::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent == 1) { 
        activeBomb.Update(maze);
        if (activeBomb.IsExploded()) {
            maze.Explosion(activeBomb.GetX(), activeBomb.GetY(), activeBomb.GetRange());
            maze.SetCell(activeBomb.GetX(), activeBomb.GetY(), 0); 
            PlaySound(_T("res/bomb.wav"), NULL, SND_FILENAME | SND_ASYNC); 
            SetTimer(2,50,NULL);
            activeBomb.Reset();
            KillTimer(1);
            Invalidate();
            // Kiểm tra địch
            for (auto it = enemies.begin(); it != enemies.end();) {
                if ((it->GetX() == activeBomb.GetX() && abs(it->GetY() - activeBomb.GetY()) <= activeBomb.GetRange()) ||(it->GetY() == activeBomb.GetY() && abs(it->GetX() - activeBomb.GetX()) <= activeBomb.GetRange())) {
                    maze.SetCell(it->GetX(), it->GetY(), 0);
                    it = enemies.erase(it); 
                } else { it++; }
            }
            // Kiểm tra người chơi
            if ((player.getX() == activeBomb.GetX() && abs(player.getY() - activeBomb.GetY()) <= activeBomb.GetRange()) || (player.getY() == activeBomb.GetY() && abs(player.getX() - activeBomb.GetX()) <= activeBomb.GetRange())) {
                maze.SetCell(player.getX(), player.getY(), 0); 
                OnGameOver(false); return;
            }

            if (enemies.empty() && !gameOver) {
                OnGameOver(true); return;
            }
            Invalidate();
        }
    } else if (nIDEvent == 2) {
        // hieu ung bom
        KillTimer(2); 
        maze.ClearExplosion();
        Invalidate(); 
    } else if (nIDEvent == 3) { 
        for (auto& enemy : enemies) {
            CRect oldCell(enemy.GetX() * size, enemy.GetY() * size,(enemy.GetX() + 1) * size, (enemy.GetY() + 1) * size);
            enemy.Move(maze.GetMaze(), maze.GetRows(), maze.GetCols()); 
            CRect newCell(enemy.GetX() * size, enemy.GetY() * size,(enemy.GetX() + 1) * size, (enemy.GetY() + 1) * size);
            InvalidateRect(&oldCell, FALSE);
            InvalidateRect(&newCell, FALSE);
        }
        for (const auto& enemy : enemies) {
            if (enemy.GetX() == player.getX() && enemy.GetY() == player.getY()) {
                OnGameOver(false); return;
            }
        }
    }
    CWnd::OnTimer(nIDEvent);
}
