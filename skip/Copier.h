#ifndef _COPIER_H_
#define _COPIER_H_

#include <windows.h>
#include "graphics.h"

struct Copier final{
    HDC wndDC,drawDC;
    HBITMAP hBmp;
    GL::rgba *gsBuff;
    int w, h;
public:
             Copier ();
             Copier (HDC wndDC);
    int      Create (HDC wndDC);
    int      set    (GL::rgba *gsBuff, int w, int h);

    void     Update () const;
    void     Copy   (int x, int y, int x1, int y1) const;
    void     Copy   (int wDest, int hDest, int xDest, int yDest, int xSrc, int ySrc) const;
            ~Copier ();
};
#endif // _COPIER_H_
