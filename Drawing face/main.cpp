#include <Windows.h>
#include <cmath>

void Draw8Points(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc+a, yc-b, color);
    SetPixel(hdc, xc+b, yc+a, color);
    SetPixel(hdc, xc-b, yc+a, color);
    SetPixel(hdc, xc-b, yc-a, color);
    SetPixel(hdc, xc+b, yc-a, color);
}

int roundToInt(double x)
{
    return (int)(x+0.5);
}

void DrawCircle(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {

            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}

double calcRadius(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void DrawFace(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color){
    double temp = calcRadius(x1, y1, x2, y2);
    int radius = roundToInt(temp);
    double halfRadius = radius / 2;
    DrawCircle(hdc, x1, y1, radius, color);
    DrawCircle(hdc, roundToInt(x1 + halfRadius), roundToInt(y1 - halfRadius), roundToInt(radius / 8), color);
    DrawCircle(hdc, roundToInt(x1 - halfRadius), roundToInt(y1 - halfRadius), roundToInt(radius / 8), color);
    DrawCircle(hdc, x1, roundToInt(y1 + halfRadius), roundToInt(radius / 4), color);


}



LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    static POINT points[2]; // Array to store two points
    static int pointCount = 0; // Counter to keep track of how many points have been received

    switch (m)
    {
        case WM_LBUTTONDOWN:
            if (pointCount < 2) {
                points[pointCount].x = LOWORD(lp);
                points[pointCount].y = HIWORD(lp);
                ++pointCount;

                if (pointCount == 2) {
                    HDC hdc = GetDC(hwnd);
                    DrawFace(hdc, points[0].x, points[0].y, points[1].x, points[1].y, RGB(0,0,255));
                    ReleaseDC(hwnd, hdc);
                    pointCount = 0;
                }
            }
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

int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR c, int ns)
{
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hInstance = hi;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = "MyClass";
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("MyClass", "Hello World", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hi, 0);
    ShowWindow(hwnd, ns);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
