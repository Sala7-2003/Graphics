#include <Windows.h>

// function prototype
void DrawLine(HDC hdc, int x1, int x2, int y1, int y2, COLORREF c);

LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp) {
    HDC hdc;
    int x, y;
    switch (m) {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            x = LOWORD(lp);
            y = HIWORD(lp);

            //void DrawLine(HDC hdc ,int x1, int x2 , int y1 , int y2, COLORREF c)
            DrawLine(hdc, 50, 200, 7, 250, 000);
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


void DrawLine(HDC hdc, int x1, int x2, int y1, int y2, COLORREF c) {

    int dy = y2 - y1;
    int dx = x2 - x1;
    // slope is less than one
    if (abs(dx) > abs(dy)) {
        if (dx == 0) {
            SetPixel(hdc, x1, y1, c);
            return;
        }
        // making swap in case x-start is greater than x-end
        if (x2 < x1) {
            swap(x1, x2);
            swap(y1, y2);
        }
        // initializing x and y
        int x = x1;
        double y = y1;
        double m = dy / (double) dx;
        SetPixel(hdc, x1, y1, c);
        while (x < x2) {
            x++;
            y += m;
            SetPixel(hdc, x, y, c);
        }

    // slope is greater than 1
    } else {
        if (dy == 0) {
            SetPixel(hdc, x1, y1, c);
            return;
        }
        if (y2 < y1) {
            swap(x1, x2);
            swap(y1, y2);
        }

        double x = x1;
        int y = y1;
        double m = dy / (double) dx;
        SetPixel(hdc, x1, y1, c);
        while (y < y2) {
            y++;
            x += m;
            SetPixel(hdc, x, y, c);
        }
    }

}


