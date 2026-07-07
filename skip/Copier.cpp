#include "Copier.h"
#include <windows.h>
#include <math.h>
#include <stdio.h>

Copier::Copier () : wndDC(NULL), drawDC(NULL), hBmp(NULL), gsBuff(NULL){}
Copier::Copier (HDC wndDC){
    drawDC = CreateCompatibleDC(wndDC);
    this->wndDC = wndDC;
    hBmp = NULL;
    gsBuff = NULL;
}
int Copier::Create (HDC wndDC){
    if(drawDC != NULL) DeleteDC(drawDC);
    drawDC = CreateCompatibleDC(wndDC);
    if(drawDC == NULL) return -1;
    this->wndDC = wndDC;
    hBmp = NULL;
    gsBuff = NULL;
    return 0;
}
int Copier::set (GL::rgba *gsBuff, int w, int h){
    HBITMAP hBmp;
    if(this->hBmp != NULL)
        hBmp = CreateCompatibleBitmap(drawDC,w,h);
    else
        hBmp = CreateBitmap(w,h,1,32,gsBuff);
    if(hBmp == NULL) return -1;

    this->hBmp = (HBITMAP)SelectObject(drawDC,hBmp);
    if(this->hBmp == HGDI_ERROR || this->hBmp == NULL){
        DeleteObject(hBmp);
        return -1;
    }
    DeleteObject(this->hBmp);
    this->hBmp = hBmp;
    this->gsBuff = gsBuff;
    this->w = w;
    this->h = h;
    return 0;
}
void Copier::Update() const{
    SetBitmapBits(hBmp, sizeof(GL::rgba) * w * h, gsBuff);
}
void Copier::Copy (int xDest, int yDest, int xSrc, int ySrc) const{
    BitBlt(wndDC, xDest, yDest, w, h, drawDC, xSrc, ySrc, SRCCOPY);
}
void Copier::Copy (int wDest, int hDest, int xDest, int yDest, int xSrc, int ySrc) const{
    StretchBlt(wndDC, xDest, yDest, wDest, hDest, drawDC, xSrc, ySrc, w, h,SRCCOPY);
}
Copier::~Copier(){
    DeleteObject(hBmp);
    DeleteDC(drawDC);
    gsBuff = NULL;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const char CLASS_NAME[]  = "Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    
    Copier cp(GetDC(hwnd));
    GL::field fd(200, 100, 1079, 619);
    GL::dim3::render rndr(1280, 720, new GL::rgba[1280*720], new GL::dim3::vector[1280 * 720]);
    cp.set(rndr.gsBuff, 1280, 720);
    
    GL::dim3::camera cam;
    cam.multViewPt = 2000.0f;
    
    cam.move(GL::dim3::vector(0, 1, -1), 20);
    cam.spin(GL::dim3::vector(1, 0, 0), cam.pos, 45 * 3.14f / 180);
    //printf(
    GL::dim3::vector vt;

    MSG msg = { };
    float t = 0.01f;
    
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        vt = 10000000*cam.horz^cam.vert;
        for(int i = 0; i != 720; i++)
            for(int j = 0; j != 1280; j++){
                rndr.gsBuff[rndr.w*i + j].set(GL::rgba::HEX::BLACK, 255);
                rndr.ptBuff[rndr.w*i + j] = vt;
                }
        
        for(int i = 0; i <= 1000; i+= 1){
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::RED, 255), GL::dim3::vector(0, i, 0));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::RED, 255), GL::dim3::vector(0, -i, 0));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::GREEN, 255), GL::dim3::vector(i, 0, 0));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::GREEN, 255), GL::dim3::vector(-i, 0, 0));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::BLUE, 255), GL::dim3::vector(0, 0, i));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::BLUE, 255), GL::dim3::vector(0, 0, -i));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::BLUE, 255), GL::dim3::vector(1, 0, i));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::BLUE, 255), GL::dim3::vector(1, 0, -i));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::BLUE, 255), GL::dim3::vector(-1, 0, i));
            rndr(cam, fd, GL::rgba(GL::rgba::HEX::BLUE, 255), GL::dim3::vector(-1, 0, -i));
        }
        
        cp.Update();
        cp.Copy(0,0,0,0);
        cam.spin(GL::dim3::vector(0, 1, 0), GL::dim3::vector(0, 0, 0), 1 * 3.14f / 180);
        //cam.pos = GL::dim3::vector(pos.x() + 10*cos(t * 3.14f / 180), pos.y() + 10*sin(t * 3.14f / 180), pos.z());
        cam.move(cam.horz^cam.vert, -1);
        //t+= 0.01f;
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}