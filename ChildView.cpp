#include "pch.h"
#include "framework.h"
#include "Bomb.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_KEYDOWN()
    ON_WM_TIMER()
END_MESSAGE_MAP()

CChildView::CChildView() : size(50), gameOver(false) {
    enemies.push_back(Enemy(3, 3));  // Thêm 1 kẻ địch
    enemies.push_back(Enemy(7, 7));  // Thêm 1 kẻ địch
}

CChildView::~CChildView() {

}

void CChildView::OnGameOver(bool win)
{
    if (win) {
        AfxMessageBox(_T("You win!"));
    }
    else {
        AfxMessageBox(_T("You lose!"));
    }

    gameOver = true;  // Đặt cờ gameOver để không hiển thị thông báo nữa

    // Dừng trò chơi, ví dụ:
    PostQuitMessage(0);  // Thoát trò chơi
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
    for (const auto& enemy : enemies) {
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
        if (player.getY() > 0 && maze.GetCell(player.getY() - 1, player.getX()) ==0)
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
            activeBomb.SetRange(3);  // Phạm vi nổ
            activeBomb.Activate();   // Kích hoạt bom
            SetTimer(1, 1000, NULL); // 2 giây để bom nổ
        }
        break;
    }

    CRect newCell(player.getX() * size, player.getY() * size,
        (player.getX() + 1) * size, (player.getY() + 1) * size);

    InvalidateRect(oldCell | newCell, 0);
}

void CChildView::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent == 1) {
        // Cập nhật trạng thái của bom
        activeBomb.Update();

        // Nếu bom nổ, xử lý nổ bom
        if (activeBomb.IsExploded()) {
            maze.ExplosionAndItem(activeBomb.GetX(), activeBomb.GetY(), activeBomb.GetRange());
            activeBomb.Reset();
        }

        // Cập nhật màn hình
        Invalidate();
    }

    // Di chuyển kẻ địch
    for (auto& enemy : enemies) {
        enemy.Move( maze.GetRows(), maze.GetCols());  // Di chuyển kẻ địch
    }

    // Kiểm tra nếu kẻ địch bị tiêu diệt
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (it->IsDestroyed(activeBomb.GetX(), activeBomb.GetY(), activeBomb.GetRange())) {
            it = enemies.erase(it);  // Xóa kẻ địch nếu bị nổ
        }
        else {
            ++it;
        }
    }

    // Kiểm tra nếu kẻ địch chạm vào nhân vật, thì thua
    for (const auto& enemy : enemies) {
        if (enemy.GetX() == player.getX() && enemy.GetY() == player.getY()) {
            if (!gameOver) {  // Nếu chưa hiển thị thông báo
                OnGameOver(false);  // Người chơi thua
            }
            return;  // Không tiếp tục kiểm tra sau khi game over
        }
    }

    // Kiểm tra nếu thắng
    if (enemies.empty() && !gameOver) {  // Nếu chưa hiển thị thông báo
        OnGameOver(true);  // Người chơi thắng
    }

    CWnd::OnTimer(nIDEvent);  // Gọi hàm OnTimer của lớp cha
}