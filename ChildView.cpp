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

CChildView::CChildView() : size(50), startTime(0) {}

CChildView::~CChildView() {}

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

    maze.draw(&dc);
    player.Draw(&dc);
    Bom.Draw(&dc); // Vẽ bom
    
    // Vẽ chuỗi thời gian tại vị trí (10, 10)
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    CRect oldCell(player.getX() * size, player.getY() * size, (player.getX() + 1) * size, (player.getY() + 1) * size);

    switch (nChar)
    {
    case 'W':
        if (player.getY() > 0 && maze.GetCell(player.getY() - 1, player.getX()) != 1 && maze.GetCell(player.getY() - 1, player.getX()) != 2)
            player.setY(player.getY() - 1);
        break;
    case 'A':
        if (player.getX() > 0 && maze.GetCell(player.getY(), player.getX() - 1) != 1 && maze.GetCell(player.getY(), player.getX() - 1) != 2)
            player.setX(player.getX() - 1);
        break;
    case 'S':
        if (player.getY() < maze.GetRows() - 1 && maze.GetCell(player.getY() + 1, player.getX()) != 1 && maze.GetCell(player.getY() + 1, player.getX()) != 2)
            player.setY(player.getY() + 1);
        break;
    case 'D':
        if (player.getX() < maze.GetCols() - 1 && maze.GetCell(player.getY(), player.getX() + 1) != 1 && maze.GetCell(player.getY(), player.getX() + 1) != 2)
            player.setX(player.getX() + 1);
        break;

    case VK_SPACE:
        if (!Bom.GetActiveState()) {
            Bom.SetPosition(player.getX(), player.getY());
            Bom.SetRange(3); // Phạm vi bom có thể điều chỉnh
            Bom.Activate(); // Kích hoạt bom
            SetTimer(1, 2000, NULL); // 2 giây để bom nổ
        }
        break;
    }
    
    CRect newCell(player.getX() * size, player.getY() * size,
        (player.getX() + 1) * size, (player.getY() + 1) * size);
    InvalidateRect(oldCell | newCell,  1 );
    
}

void CChildView::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent == 1) { // Bom đã đến thời gian nổ
        Bom.Update();
        if (Bom.IsExploded()) {
            maze.ExplosionAndItem(Bom.GetX(), Bom.GetY(), Bom.GetRange());
            KillTimer(1); // Dừng bộ đếm thời gian của bom sau khi nó nổ
        }
    }

    CWnd::OnTimer(nIDEvent);
}
