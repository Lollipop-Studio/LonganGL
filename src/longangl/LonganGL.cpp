#include <windows.h>
#include <windowsx.h>

#include<iostream>
using namespace std;




//全局变量声明

LPCSTR szTitle = "LonganGL-test";   // 标题栏文本
LPCSTR szWindowClass = "WindowClass";  // 主窗口类名

#define WINDOW_WIDTH	800							//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define WINDOW_HEIGHT	600							//为窗口高度定义的宏，以方便在此处修改窗口高度

HINSTANCE hInst;
HBITMAP hbmp;

HDC		mdc;
HDC     hdc;

int a = 0;

static LRESULT CALLBACK wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps; // 定义一个PAINTSTRUCT结构体来记录一些绘制信息



    switch (message)
    {
        case WM_PAINT:          // 窗口重绘消息
        {
            a++;
            cout << a << ":Hello, world!" << endl;
            hdc = BeginPaint(hWnd, &ps);        //开始绘制
            BitBlt(hdc, 0, 0, 800, 600, mdc, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);			//EndPaint函数标记指定窗口的绘画过程结束
            // ValidateRect(hWnd, NULL);		// 更新客户区的显示
        }
            break;
        case WM_DESTROY:        // 窗口结束消息
            DeleteDC(mdc);
            DeleteObject(hbmp);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


//
//  函数: register_classA()
//
//  目的: 注册窗口类。
//

static ATOM register_classA(HINSTANCE hInstance)
{
    WNDCLASSEXA wcex    = { 0 };
    wcex.cbSize         = sizeof(wcex);
    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = wndproc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = NULL;
    return RegisterClassExA(&wcex);
}



static BOOL init_instance(HINSTANCE hInstance, int nCmdShow)
{

    static DWORD dwExStyle      = WS_EX_OVERLAPPEDWINDOW;
    static DWORD dwStyle        = WS_OVERLAPPEDWINDOW;
    RECT rect                   = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };


    AdjustWindowRectEx(&rect, dwStyle, false, dwExStyle);


    HWND hWnd = CreateWindowExA(
            dwExStyle,
            szWindowClass,
            szTitle,
            dwStyle,
            50,
            50,
            rect.right - rect.left,
            rect.bottom - rect.top,
            NULL,
            NULL,
            hInstance,
            NULL
    );

    if (!hWnd)
    {
        return FALSE;
    }



    MoveWindow(hWnd, 10, 10, 800, 600, true);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    hdc = GetDC(hWnd);
    mdc = CreateCompatibleDC(hdc);

    hbmp = (HBITMAP)LoadImage(NULL, "LonganGLlogo.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    SelectObject(mdc, hbmp);

    BitBlt(hdc, 0, 0, 800, 600, mdc, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hdc);



    //ShowWindow(hWnd, SW_SHOW);    //调用ShowWindow函数来显示窗口
    // UpdateWindow(hWnd);

    return TRUE;
}




int main()
{
    MSG msg                     = { 0 };				//定义并初始化msg
    HINSTANCE hInstance         = GetModuleHandle(NULL);
    register_classA(hInstance);


    // 执行应用程序初始化:
    if (!init_instance(hInstance, SW_SHOW))
    {
        return FALSE;
    }




    // 消息循环
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);     // 将虚拟键消息转换为字符消息
        DispatchMessage(&msg);
    }

    return msg.wParam;
}



























