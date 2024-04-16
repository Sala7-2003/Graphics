#include <Windows.h>
#include <math.h>

// The circle drawn in red color is for the iterative polar algorithm
// function prototype
void DrawCircleUsingPolarForm(HDC hdc, int xc, int yc, int R, COLORREF c);
void DrawCircleUsingIterativePolarForm(HDC hdc, int xc, int yc, int R, COLORREF c);


LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp) {
    HDC hdc;
    int x, y;
    switch (m) {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            x = LOWORD(lp);
            y = HIWORD(lp);

            DrawCircleUsingPolarForm(hdc, 500, 200, 70, 000);
            DrawCircleUsingIterativePolarForm( hdc, 600, 500, 100, 111);

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
void  DrawCircleUsingPolarForm(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    int x=R,y=0;
    double theta=0,dtheta=1.0/R;
    drawEightPoints(hdc,xc,yc,x,y,c);
    while(x>y)
    {
        theta+=dtheta;
        x=round(R*cos(theta));
        y=round(R*sin(theta));
        drawEightPoints(hdc,xc,yc,x,y,c);
    }
}
void  DrawCircleUsingIterativePolarForm(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    double x=R,y=0;
    double dtheta=1.0/R;
    double cdtheta=cos(dtheta),sdtheta=sin(dtheta);
    drawEightPoints(hdc,xc,yc,R,0,c);
    while(x>y)
    {
        double x1=x*cdtheta-y*sdtheta;
        y=x*sdtheta+y*cdtheta;
        x=x1;
        drawEightPoints(hdc,xc,yc,round(x),round(y),c);
    }
}