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
    enemies.push_back(Enemy(13, 1));  // Thêm 1 kẻ địch vào vị trí (3,3)
    enemies.push_back(Enemy(13, 11));  // Thêm 1 kẻ địch vào vị trí (7,7)

    // Khởi tạo timer cho bom nổ và di chuyển của kẻ địch
   
}

CChildView::~CChildView() {}

void CChildView::OnGameOver(bool win) {
    if (gameOver) return;

    // Hiển thị thông báo win/lose
    CString message = win ? _T("You win!") : _T("You lose!");
    AfxMessageBox(message);

    // Đặt gameOver là true để không hiển thị thông báo lần nữa
    gameOver = true;

    // Thoát trò chơi
    PostQuitMessage(0);
}
void CChildView::StartTimers() {
    
   
    SetTimer(2, 1000, NULL); // 1 giây
}

void CChildView::StopTimers() {
    KillTimer(1);
    KillTimer(2);
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
    SetTimer(2, 500, NULL); // 2 giây
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
        if (!activeBomb.IsExploded()) {
            activeBomb.SetPosition(player.getX(), player.getY());
            activeBomb.SetRange(1.5);  // Phạm vi nổ
            activeBomb.Activate();   // Kích hoạt bom
            SetTimer(1, 2000, NULL); // 2 giây
        }
        break; 
    }

    CRect newCell(player.getX() * size, player.getY() * size,
        (player.getX() + 1) * size, (player.getY() + 1) * size);

    InvalidateRect(oldCell, TRUE);
    InvalidateRect(newCell, TRUE);
    
}

void CChildView::OnTimer(UINT_PTR nIDEvent) {
    
    if (nIDEvent == 1) { // Bom nổ sau 2 giây
        activeBomb.Update(maze);

        if (activeBomb.IsExploded()) {
            // Xử lý vụ nổ (ví dụ: vẽ hiệu ứng nổ)
            
            maze.Explosion(activeBomb.GetX(), activeBomb.GetY(), activeBomb.GetRange());

            // Kiểm tra nếu bom tiêu diệt kẻ địch
            for (auto it = enemies.begin(); it != enemies.end();) {
                if (abs(it->GetX() - activeBomb.GetX()) <= activeBomb.GetRange() &&
                    abs(it->GetY() - activeBomb.GetY()) <= activeBomb.GetRange()) {
                    it = enemies.erase(it);  // Xóa kẻ địch khỏi danh sách
                }
                else {
                    ++it;  // Tiếp tục với kẻ địch tiếp theo
                }
            }
            maze.SetCell(activeBomb.GetX(), activeBomb.GetY(), 0);  // Xóa bom khỏi bản đồ
            activeBomb.Reset();
            Invalidate();  // Vẽ lại màn hình để hiển thị vụ nổ
        }

        // Kiểm tra nếu người chơi nằm trong phạm vi nổ của bom
        if (abs(player.getX() - activeBomb.GetX()) <= activeBomb.GetRange() && abs(player.getY() - activeBomb.GetY()) <= activeBomb.GetRange()) {
            OnGameOver(false);  // Người chơi thua nếu trong phạm vi nổ của bom
            player.setX(-1);
            player.setY(-1);
        }
    }
    else if (nIDEvent == 2) { // Di chuyển các kẻ địch
        for (auto& enemy : enemies) {
            CRect oldCell(enemy.GetX() * size, enemy.GetY() * size,
                (enemy.GetX() + 1) * size, (enemy.GetY() + 1) * size);

            enemy.Move(maze.GetMaze(), maze.GetRows(), maze.GetCols());

            CRect newCell(enemy.GetX() * size, enemy.GetY() * size,
                (enemy.GetX() + 1) * size, (enemy.GetY() + 1) * size);

            InvalidateRect(oldCell, TRUE);
            InvalidateRect(newCell, TRUE);
        }

        // Kiểm tra nếu kẻ địch chạm vào nhân vật
        for (const auto& enemy : enemies) {
            if (enemy.GetX() == player.getX() && enemy.GetY() == player.getY()) {
                if (!gameOver) {
                    OnGameOver(false);  // Người chơi thua
                }
                return;
            }
        }
    }

    // Kiểm tra nếu tất cả kẻ địch đã bị tiêu diệt
    bool allEnemiesDestroyed = true;
    for (const auto& enemy : enemies) {
        if (enemy.GetX() != NULL) {  // Kẻ địch còn tồn tại
            allEnemiesDestroyed = false;
            break;
        }
    }

    if (allEnemiesDestroyed && !gameOver) {
        OnGameOver(true);  // Người chơi thắng
    }

    CWnd::OnTimer(nIDEvent);
}
