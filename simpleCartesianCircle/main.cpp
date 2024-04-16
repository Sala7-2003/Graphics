#include <Windows.h>
#include <math.h>

// function prototype
void DrawCircleUsingCartesianEquation(HDC hdc, int xc, int yc, int R, COLORREF c);

LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp) {
    HDC hdc;
    int x, y;
    switch (m) {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            x = LOWORD(lp);
            y = HIWORD(lp);

            DrawCircleUsingCartesianEquation(hdc, 500, 200, 70, 000);
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
void drawEightPoints (HDC hdc , int xc , int yc , int a , int b , COLORREF color){
    SetPixel(hdc, xc+a, yc+b, color);
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc+a, yc-b, color);
    SetPixel(hdc, xc+b, yc+a, color);
    SetPixel(hdc, xc-b, yc+a, color);
    SetPixel(hdc, xc-b, yc-a, color);
    SetPixel(hdc, xc+b, yc-a, color);

}
void DrawCircleUsingCartesianEquation(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    // we could draw a square from the same code by making y1 = round(sqrt(RPow2))
    int x1 = 0 , y1 = R;
    int RPow2 = y1*y1;
    drawEightPoints(hdc , xc , yc , x1 , y1 , 000);
    while (x1 < y1 ){
        x1++;
        y1= round(sqrt(RPow2-(x1*x1)));
        drawEightPoints(hdc , xc , yc , x1 , y1 , 000);


    }
}

