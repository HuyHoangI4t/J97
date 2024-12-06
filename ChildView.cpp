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
END_MESSAGE_MAP()

CChildView::CChildView() : size(50), gameOver(false), gameWon(false) {
    // Khởi tạo kẻ địch
    enemies.push_back(Enemy(1, 11)); 
    enemies.push_back(Enemy(1, 11)); 
}

CChildView::~CChildView() {}

void CChildView::OnGameOver(bool win) {
    if (gameOver) return;  // Ngăn chặn các thông báo trùng lặp

    CString message = win ? _T("You win!") : _T("You lose!");
    MessageBox(message);
    gameOver = true;
    if (win) gameWon = true;  // Đánh dấu trạng thái thắng
   
    // Thoát trò chơi
    PostQuitMessage(0);
}



void CChildView::StopTimers() {
    KillTimer(1); // Xóa timer bom nổ
    KillTimer(2); // Xóa timer bom nổ
    KillTimer(3); // Xóa timer hiệu ứng nổ
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
    CPaintDC dc(this); // Context để vẽ
    maze.draw(&dc);    // Vẽ bản đồ
    player.Draw(&dc);  // Vẽ người chơi

    // Vẽ kẻ địch
    for (auto& enemy : enemies) {
        enemy.Draw(&dc);
    }

    activeBomb.Draw(&dc);
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
    case VK_UP: 
        if (player.getY() > 0 && maze.GetCell(player.getY() - 1, player.getX()) == 0)
            player.setY(player.getY() - 1);
        break;
    case VK_LEFT: // Trái
        if (player.getX() > 0 && maze.GetCell(player.getY(), player.getX() - 1) == 0)
            player.setX(player.getX() - 1);
        break;
    case VK_DOWN: // Xuống
        if (player.getY() < maze.GetRows() - 1 && maze.GetCell(player.getY() + 1, player.getX()) == 0)
            player.setY(player.getY() + 1);
        break;
    case VK_RIGHT: // Phải 
        if (player.getX() < maze.GetCols() - 1 && maze.GetCell(player.getY(), player.getX() + 1) == 0)
            player.setX(player.getX() + 1);
        break;
    case 'E':
        SetTimer(2, 500, NULL); 
        break;
    case VK_SPACE: // Đặt bom
        if (!activeBomb.IsExploded()) {
            activeBomb.SetPosition(player.getX(), player.getY());
            activeBomb.SetRange(1);  // Phạm vi nổ
            activeBomb.Activate();   // Kích hoạt bom
            SetTimer(1, 1000, NULL); // Hẹn giờ nổ sau 2 giây
         
        }
        break;
        
    }

    CRect newCell(player.getX() * size, player.getY() * size,
        (player.getX() + 1) * size, (player.getY() + 1) * size);

    InvalidateRect(oldCell, TRUE);
    InvalidateRect(newCell, TRUE);
}

void CChildView::OnTimer(UINT_PTR nIDEvent) {
    if (gameOver) return;
    if (nIDEvent == 1) {                                                                                        // Bom nổ
        activeBomb.Update(maze);

        if (activeBomb.IsExploded()) {
            maze.Explosion(activeBomb.GetX(), activeBomb.GetY(), activeBomb.GetRange());
            maze.SetCell(activeBomb.GetX(), activeBomb.GetY(), 0);                                              // Xóa vị trí bom
            PlaySound(_T("res/bomb.wav"), NULL, SND_FILENAME | SND_ASYNC);                                      //Thêm tiếng nổ cho bom
            Invalidate(); 
            activeBomb.Reset();
            
            for (auto it = enemies.begin(); it != enemies.end();) {
                if (abs(it->GetX() - activeBomb.GetX()) <= activeBomb.GetRange() && abs(it->GetY() - activeBomb.GetY()) <= activeBomb.GetRange()) {
                    maze.SetCell(it->GetX(), it->GetY(), 0);                                                    // Xóa vị trí kẻ địch khỏi bản đồ
                    it = enemies.erase(it);                                                                     // Xóa kẻ địch khỏi danh sách
                   
                }
                else {
                    ++it;                                                                                       // Tiếp tục với kẻ địch tiếp theo
                }
            }
            // Kiểm tra nếu người chơi bị ảnh hưởng
            if (abs(player.getX() - activeBomb.GetX()) <= activeBomb.GetRange() && abs(player.getY() - activeBomb.GetY()) <= activeBomb.GetRange())
            {
                maze.SetCell(player.getX(), player.getY(), 0);                                                  // Xóa vị trí người chơi nếu trong phạm vi nổ
                OnGameOver(false);  // Người chơi thua
                return;
            }
            if (enemies.empty() && !gameOver) {
                OnGameOver(true);
                return;
            }
            Invalidate();
        }
      
    }

    else if (nIDEvent == 2) 
    {
        for (auto& enemy : enemies) {
            CRect oldCell(enemy.GetX() * size, enemy.GetY() * size,
                (enemy.GetX() + 1) * size, (enemy.GetY() + 1) * size);

            enemy.Move(maze.GetMaze(), maze.GetRows(), maze.GetCols());                                        // Di chuyển kẻ địch

            CRect newCell(enemy.GetX() * size, enemy.GetY() * size,
                (enemy.GetX() + 1) * size, (enemy.GetY() + 1) * size);

            InvalidateRect(oldCell, TRUE);
            InvalidateRect(newCell, TRUE);

        }

        // Kiểm tra kẻ địch chạm vào người chơi
        for (const auto& enemy : enemies) {
            if (enemy.GetX() == player.getX() && enemy.GetY() == player.getY()) {
                OnGameOver(false);
                return;
            }
        }
        
    }
 

   

    CWnd::OnTimer(nIDEvent);
}
