#include "pch.h"
#include "framework.h"
#include "Boom.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_KEYDOWN()
    ON_WM_TIMER()
END_MESSAGE_MAP()

CChildView::CChildView() : size(40), gameOver(false) {
    // Initialize enemies
    enemies.push_back(Enemy(3, 3));  // Thêm 1 kẻ địch vào vị trí (3,3)
    enemies.push_back(Enemy(7, 7));  // Thêm 1 kẻ địch vào vị trí (7,7)
}

CChildView::~CChildView() {
}

void CChildView::OnGameOver(bool win) {
    CString message = win ? _T("You win!") : _T("You lose!");
    AfxMessageBox(message);

    gameOver = true;
    PostQuitMessage(0);  // Thoát trò chơi sau thông báo
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) {
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        ::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

    return TRUE;
}

void CChildView::OnPaint() {
    CPaintDC dc(this); // device context for painting
    maze.draw(&dc);    // Vẽ bản đồ
    player.Draw(&dc);  // Vẽ nhân vật

    // Vẽ các kẻ địch
    for (auto& enemy : enemies) {
        enemy.Draw(&dc);
    }

    // Vẽ bom
    activeBomb.Draw(&dc);  // Vẽ bom nếu có
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    CRect oldCell(player.getX() * size, player.getY() * size,
        (player.getX() + 1) * size, (player.getY() + 1) * size);

    switch (nChar) {
    case 'W':
        if (player.getY() > 0 && maze.GetCell(player.getY() - 1, player.getX()) == 0)
            player.setY(player.getY() - 1);
        break;
    case 'A':
        if (player.getX() > 0 && maze.GetCell(player.getY(), player.getX() - 1) == 0)
            player.setX(player.getX() - 1);
        break;
    case 'S':
        if (player.getY() < maze.GetRows() - 1 && maze.GetCell(player.getY() + 1, player.getX()) == 0)
            player.setY(player.getY() + 1);
        break;
    case 'D':
        if (player.getX() < maze.GetCols() - 1 && maze.GetCell(player.getY(), player.getX() + 1) == 0)
            player.setX(player.getX() + 1);
        break;
    case VK_SPACE:
        // Đặt bom
        if (!activeBomb.GetActiveState()) {
            activeBomb.SetPosition(player.getX(), player.getY());
            activeBomb.SetRange(2);  // Phạm vi nổ
            activeBomb.Activate();   // Kích hoạt bom
            SetTimer(1, 1500, NULL); // 2 giây để bom nổ
        }
        break;
    }

    CRect newCell(player.getX() * size, player.getY() * size,
        (player.getX() + 1) * size, (player.getY() + 1) * size);

    InvalidateRect(oldCell, TRUE);
    InvalidateRect(newCell, TRUE);
}

void CChildView::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent == 1) {
        activeBomb.Update();

        if (activeBomb.IsExploded()) {
            maze.ExplosionAndItem(activeBomb.GetX(), activeBomb.GetY(), activeBomb.GetRange());
            activeBomb.Reset();
        }

        // Di chuyển các kẻ địch
        for (int i = 0; i < enemies.size(); ++i) {
            CRect oldCell(enemies[i].GetX() * size, enemies[i].GetY() * size,
                (enemies[i].GetX() + 1) * size, (enemies[i].GetY() + 1) * size);

            enemies[i].Move( maze.GetRows(), maze.GetCols());

            CRect newCell(enemies[i].GetX() * size, enemies[i].GetY() * size,
                (enemies[i].GetX() + 1) * size, (enemies[i].GetY() + 1) * size);

            InvalidateRect(oldCell, false);
            InvalidateRect(newCell, false);
        }

        // Kiểm tra nếu kẻ địch bị tiêu diệt
        for (int i = 0; i < enemies.size(); ++i) {
            if (enemies[i].IsDestroyed(activeBomb.GetX(), activeBomb.GetY(), activeBomb.GetRange())) {
                // Đánh dấu kẻ địch đã bị tiêu diệt
                enemies[i].SetPosition(-1, -1); // Cách này chỉ để tránh crash, bạn có thể thay bằng phương thức xóa kẻ địch
            }
        }

        // Kiểm tra nếu kẻ địch chạm vào nhân vật
        for (int i = 0; i < enemies.size(); ++i) {
            if (enemies[i].GetX() == player.getX() && enemies[i].GetY() == player.getY()) {
                if (!gameOver) {
                    OnGameOver(false);  // Người chơi thua
                    break;
                }
            }
        }

        // Kiểm tra nếu thắng
        bool allEnemiesDestroyed = true;
        for (const auto& enemy : enemies) {
            if (enemy.GetX() != -1) {
                allEnemiesDestroyed = false;
                break;
            }
        }

        if (allEnemiesDestroyed && !gameOver) {
            OnGameOver(true);  // Người chơi thắng
        }

        Invalidate();
    }

    CWnd::OnTimer(nIDEvent);
}
