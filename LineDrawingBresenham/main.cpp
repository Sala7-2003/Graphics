#include <Windows.h>

// function prototype
void DrawLine(HDC hdc, int x1,  int y1 , int x2, int y2, COLORREF c);

LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp) {
    HDC hdc;
    int x, y;
    switch (m) {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            x = LOWORD(lp);
            y = HIWORD(lp);

            //void DrawLine(HDC hdc ,int x1, int x2 , int y1 , int y2, COLORREF c)
            DrawLine(hdc, 8, 2, 700, 250, 000);
            ReleaseDC(hwnd, hdc);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, m, wp, lp);
    }
    return 0;
}

// swapping by calling by refrence
void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

// the entry point of the program
int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR c, int ns) {
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hInstance = hi;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = TEXT("MyClass");
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow(TEXT("MyClass"), TEXT("Hello World"), WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hi,
                             0);
    ShowWindow(hwnd, ns);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}


void DrawLine(HDC hdc, int X1, int Y1, int X2, int Y2, COLORREF c)
{
    // calculate dx & dy
    int dx = X2 - X1;
    int dy = Y2 - Y1;

    // determine the direction of drawing
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;

    // make dx and dy positive
    dx = abs(dx);
    dy = abs(dy);

    // initialize decision parameters
    int d;
    int x = X1, y = Y1;

    // plot the first point
    SetPixel(hdc, x, y, c);

    if (dx >= dy) // slope < 1
    {
        d = 2 * dy - dx;
        while (x != X2)
        {
            if (d >= 0)
            {
                y += stepY;
                d -= 2 * dx;
            }
            x += stepX;
            d += 2 * dy;
            SetPixel(hdc, x, y, c);
        }
    }
    else // slope >= 1
    {
        d = 2 * dx - dy;
        while (y != Y2)
        {
            if (d >= 0)
            {
                x += stepX;
                d -= 2 * dy;
            }
            y += stepY;
            d += 2 * dx;
            SetPixel(hdc, x, y, c);
        }
    }
}
