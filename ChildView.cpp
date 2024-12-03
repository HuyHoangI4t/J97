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
    enemies[0] = Enemy(3, 3);  // Thêm 1 kẻ địch vào vị trí (3,3)
    enemies[1] = Enemy(7, 7);  // Thêm 1 kẻ địch vào vị trí (7,7)
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

  
    for (int i = 0; i < 2; ++i) {
        enemies[i].Draw(&dc);
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

        for (int i = 0; i < 2; ++i) {
            enemies[i].Move(maze.GetMap(), maze.GetRows(), maze.GetCols());  // Di chuyển kẻ địch
        }

        // Kiểm tra nếu kẻ địch bị tiêu diệt
        for (int i = 0; i < 2; ++i) {
            if (enemies[i].IsDestroyed(activeBomb.GetX(), activeBomb.GetY(), activeBomb.GetRange())) {
                // Xóa kẻ địch nếu bị nổ
                enemies[i].SetPosition(-1, -1);  // Cách này chỉ để tránh crash, bạn có thể thay bằng phương thức xóa kẻ địch
            }
        }

        // Kiểm tra nếu kẻ địch chạm vào nhân vật, thì thua
        for (int i = 0; i < 2; ++i) {
            if (enemies[i].GetX() == player.getX() && enemies[i].GetY() == player.getY()) {
                if (!gameOver) {  // Nếu chưa hiển thị thông báo
                    OnGameOver(false);  // Người chơi thua
                }
                return;  // Không tiếp tục kiểm tra sau khi game over
            }
        }

        // Kiểm tra nếu thắng
        if (enemies[0].GetX() == -1 && enemies[1].GetX() == -1 && !gameOver) {  // Nếu không còn kẻ địch
            OnGameOver(true);  // Người chơi thắng
        }

        CWnd::OnTimer(nIDEvent);
    }
}