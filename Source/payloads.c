/*
Quick Question(s): Why I don't close handles and Windows Direct Object?
	As, Clxcq uses while loop without a specific time (just he want to destroy it, I've just clear up mess not really recode it.
				It's saying memory error, why?
	Memory leak, as it've alloc the mem, but never clean it.
*/

#include <windows.h>
#include <math.h>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

DWORD WINAPI Payload_1()
{
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    while (1)
    {
		switch (rand() % 4)
		{
			case 0:
			    BitBlt(hdc, rand() % w, 1, 10, h, hdc, rand() % w, 0, SRCPAINT);
			break;
			
			case 1:
				BitBlt(hdc, rand() % w, -1, -10, h, hdc, rand() % w, 0, SRCPAINT);
        	break;
			
			case 2:
				BitBlt(hdc, 1, rand() % h, w, 66, hdc, 0, rand() % h, SRCPAINT);
        	break;
			
			case 3:
				BitBlt(hdc, -1, rand() % h, w, -66, hdc, 0, rand() % h, SRCPAINT);
			break;
		}
    }
}

DWORD WINAPI Payload_2()
{
	HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    HRGN rgn;
    RECT rect;
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	
	while (1)
    {
        SetStretchBltMode(hdc, STRETCH_HALFTONE);
        if (rand() % 2 == 0)
        {
            for (int i = 5; i < 16; ++i)
            {
                rgn = CreateEllipticRgn(w - w / i, h + h / i, w + rand() % 2000 / i, h - 950 / i);
                SelectClipRgn(hdc, rgn);
                StretchBlt(hdc, 1, 1, w - 2, h - 2, hdc, 0, 0, w, h, SRCCOPY);
            }
        }
        else if (rand() % 2 == 1)
        {
            for (int i = 5; i < 16; ++i)
            {
                rgn = CreateEllipticRgn(w - w / i, h + h / i, w + rand() % 2000 / i, h - 950 / i);
                SelectClipRgn(hdc, rgn);
                StretchBlt(hdc, -1, -1, w + 2, h + 2, hdc, 0, 0, w, h, SRCCOPY);
            }
        }
    }
}

DWORD WINAPI Payload_3()
{
	HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    HRGN rgn;
    RECT rect;
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	
    while (1)
    {
        GetWindowRect(hwnd, &rect);
        
        for (int e = 0;; e++)
        {
            int _xval = rand() % (rect.right - rect.top + 500) - 1000 / 2;
            int _yval = rand() % (rect.bottom - rect.top + 500) - 1000 / 2;

            for (int i = 0; i < 1000; i += 100)
            {
                rgn = CreateEllipticRgn(_xval - i / 2, _yval - i / 2, i, i);
                SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
                BitBlt(hdc, _xval, _xval, w, h, hdc, _xval, _yval, 0x2837E28);
                SelectClipRgn(hdc, rgn);
                Sleep(15);
            }
		}
	}
}

DWORD WINAPI Payload_4()
{
	HDC hdc = GetDC(GetDesktopWindow());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    while (1) {
        int a = rand() % w, b = rand() % h;
        BitBlt(hdc, a, b, w, h, hdc, a + cos(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
        BitBlt(hdc, a, b, -w, -h, hdc, a + cos(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
    }
}

DWORD WINAPI Payload_5()
{
	HDC hdc = GetDC(GetDesktopWindow());
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    float radius = 5.0f;
    int moveangle = 0;
    while (1) {
        double x = (cos(moveangle) * radius), y = (sin(moveangle) * radius);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 123, rand() % 431, rand() % 311)));
        BitBlt(hdc, x, y, w, h, hdc, 0, 0, 0x9273ecef);
        BitBlt(hdc, x, y, w, h, hdc, 0, 0, SRCAND);
        Sleep(10);
        moveangle = fmod(moveangle + M_PI / radius, M_PI * radius);
    }
}

DWORD WINAPI Payload_6()
{
	HDC hdc = GetDC(GetDesktopWindow());
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	float radius2 = 500.0f;
    int moveangle = 0;
	
    while (1) {
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 155, rand() % 155, rand() % 155));
        double ax = cos(moveangle) * radius2, ay = sin(moveangle) * radius2;
		
        StretchBlt(hdc, ax, ay, w, h, hdc, 0, 0, w, h, SRCCOPY);
        moveangle = fmod(moveangle + M_PI / radius2, M_PI * radius2);
		
        for (int t = 5; t < w + h; t++, t += 10) {
            int x = abs(100 + t / tan(t + 100 * 10)) + rand() % w,
                y = abs(100 + t / sin(t + 100 * 10)) + rand() % h;
            TextOutW(hdc, x, y, L"Skid Clxcq", wcslen(L"Skid Clxcq"));
        }
        Sleep(10);
        if (rand() % 10 == 4) InvalidateRect(0, 0, 0);
    }
}

DWORD WINAPI Payload_7()
{
	HDC hdc = GetDC(GetDesktopWindow());
	HBRUSH brush;
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    int c = 0;
	
    for (int a = 0;; a++, a %= 9)
    {
        if (!a) RedrawWindow(0, 0, 0, 133);

        for (int t = 0; t < rand() % 3; t++)
        {
            for (int c = 0; c < rand() % 10; c++)
            {
                int y = rand() % w, _h = h - rand() % h - (h / 2 - 58);
                int r = rand() % 3;
                
				switch (r)
				{
					case 0:
						brush = CreateSolidBrush(RGB(rand() % 100 + 155, 0, 0));
						SelectObject(hdc, brush);
					break;
					
					case 1:
						brush = CreateSolidBrush(RGB(0, rand() % 100 + 155, 0));
						SelectObject(hdc, brush);
					break;
					
					case 2:
						brush = CreateSolidBrush(RGB(0, 0, rand() % 100 + 155));
						SelectObject(hdc, brush);
					break;
				}
				
                BitBlt(hdc, 0, y, w, _h, hdc, rand() % 244 - 112, y, SRCCOPY);
                PatBlt(hdc, 0, y, w, _h, PATINVERT);
            }
        }
    }
}

DWORD WINAPI Payload_8()
{
	HDC hdc = GetDC(GetDesktopWindow());
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    int i = cos(0) + sin(1);
	
    while (1) {
		if (i < w, i++)
        BitBlt(hdc, tan(i), 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, -cos(i), 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, 0, sin(i), w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, 0, -tan(i), w, h, hdc, 0, 0, SRCCOPY);
    }
}

DWORD WINAPI Payload_9()
{
	while (1) {
		
        HDC hdc = GetDC(GetDesktopWindow());
		RECT rekt;
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
        GetWindowRect(GetDesktopWindow(), &rekt);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        int xyrng = rand() % w, _h = _h - rand() % w - (w / 2 - 110);

        POINT pt3[3];
        int inc3 = 60;
        inc3++;
        pt3[0].x = rekt.left + inc3;
        pt3[0].y = rekt.top - inc3;
        pt3[1].x = rekt.right + inc3;
        pt3[1].y = rekt.top + inc3;
        pt3[2].x = rekt.left - inc3;
        pt3[2].y = rekt.bottom - inc3;

        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);

        BitBlt(hdc, xyrng, _h, xyrng, _h, hdc, rand() % 100 - 50, xyrng, SRCCOPY);
        PatBlt(hdc, xyrng, h, xyrng, _h, PATINVERT);

        StretchBlt(hdc, -16, -16, w + 32, _h + 32, hdc, 0, 0, w, _h, SRCCOPY);
        StretchBlt(hdc, 16, 16, w - 32, _h - 32, hdc, 0, 0, w, _h, SRCCOPY);
    }
}

DWORD WINAPI Payload_10()
{
	while (1) {
        HDC hdc = GetDC(GetDesktopWindow());
        RECT rekt;
        GetWindowRect(GetDesktopWindow(), &rekt);
        SetStretchBltMode(hdc, STRETCH_HALFTONE);
        BitBlt(hdc, rekt.left + rand() % 1 + 1, rekt.top + rand() % 1 + 1, rekt.right + rand() % 1 + 1, rekt.bottom + rand() % 1 + 1, hdc, rekt.left, rekt.top, SRCPAINT);
        BitBlt(hdc, rekt.left + rand() % 1 - 1, rekt.top + rand() % 1 - 1, rekt.right + rand() % 1 + 1, rekt.bottom + rand() % 1 - 1, hdc, rekt.left, rekt.top, SRCINVERT);
        Sleep(10);
    }
}

DWORD WINAPI Payload_11()
{
	HDC hdc = GetDC(GetDesktopWindow());
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	
	while (1) {
		switch (rand() % 4)
		{
			case 0:
			    BitBlt(hdc, 0, 0, w, h, hdc, -90, 20, SRCCOPY);
			break;
			
			case 1:
				BitBlt(hdc, 0, 0, w, h, hdc, 90, -20, SRCCOPY);
			break;
			
			case 2:
				BitBlt(hdc, 0, 0, w, h, hdc, -90, -20, SRCCOPY);
        	break;
			
			case 3:
				BitBlt(hdc, 0, 0, w, h, hdc, 90, 20, SRCCOPY);
        	break;
		}
	}
}

DWORD WINAPI Payload_12()
{
	HDC hdc = GetDC(GetDesktopWindow());
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	
	while (1) {
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        PatBlt(hdc, 0, 0, w, h, PATINVERT);
        Sleep(150);
    }
}

// My favorite
DWORD WINAPI Payload_13()
{
	HDC hdc = GetDC(GetDesktopWindow());
	POINT pt;
    CURSORINFO ci;
	
    while (1) {
        GetCursorPos(&pt);
        GetCursorInfo(&ci);
        ci.cbSize = sizeof(CURSORINFO);
        DrawIcon(hdc, pt.x, pt.y, ci.hCursor);
    }
}

DWORD WINAPI Payload_14()
{
	HDC hdc = GetDC(GetDesktopWindow());
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	
	while (1) {
        for (int t = 0; t < w + h; t++) 
		{
            int x = abs(10 + t * tan(t + 10 * 3) + rand() % w),
                y = abs(10 + t * cos(t + 10 * 3) + rand() % h);
				
			switch (rand() % 5)
			{
				case 0:
					DrawIcon(hdc, x, y, LoadIcon(0, IDI_ERROR));
				break;
				
				case 1:
					DrawIcon(hdc, x, y, LoadIcon(0, IDI_WARNING));
				break;
				
				case 2:
					DrawIcon(hdc, x, y, LoadIcon(0, IDI_INFORMATION));
				break;
				
				case 3:
					DrawIcon(hdc, x, y, LoadIcon(0, IDI_QUESTION));
				break;
				
				case 4:
					DrawIcon(hdc, x, y, LoadIcon(0, IDI_ASTERISK));
				break;
			}
        }
        InvalidateRect(0, 0, 0);
    }
}

DWORD WINAPI Payload_15()
{
	HDC hdc = GetDC(GetDesktopWindow());
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	
	while (1) {
        SetStretchBltMode(hdc, STRETCH_HALFTONE);
        StretchBlt(hdc, 30, 30, w - 60, h - 60, hdc, w, h, -w, -h, SRCCOPY);
        Sleep(90);
    }
}

DWORD WINAPI Payload_16()
{
	HDC hdc = GetDC(GetDesktopWindow());
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	
	while (1) {
		int _dxy = rand() % w - 400;
        BitBlt(hdc, _dxy, _dxy, rand() % 400, rand() % 400, hdc, _dxy, _dxy, !(rand() % 2) ? SRCERASE : NOTSRCERASE);
        BitBlt(hdc, _dxy, _dxy, rand() % 400, rand() % 400, hdc, _dxy, _dxy, !(rand() % 2) ? NOTSRCCOPY : SRCPAINT);
        BitBlt(hdc, _dxy, _dxy, rand() % 400, rand() % 400, hdc, _dxy, _dxy, !(rand() % 2) ? SRCCOPY : SRCAND);
    }
}

DWORD WINAPI Payload_17()
{
	HDC hdc = GetDC(GetDesktopWindow());
	POINT c;
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
	GetCursorPos(&c);
	
    while (1) {
        BitBlt(hdc, -1, 1, w, h, hdc, 2, 2, NOTSRCCOPY);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        BitBlt(hdc, -rand() % 15, rand() % 15, w, h, hdc, -rand() % 11, rand() % 11, 0x2837e28);
        DrawIcon(hdc, c.x, c.y, LoadIcon(0, IDI_ERROR));
    }
}

// Clxcq copy it from Nikitpad lol

DWORD WINAPI Payload_18()
{
	HDC hdc = GetDC(GetDesktopWindow()), hdcMem = CreateCompatibleDC(hdc); 
	int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
	
    for (int i = 0;; i++, i %= 6) {
        SelectObject(hdcMem, hbm);
        BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); 
		GetBitmapBits(hbm, w * h * 4, data);
		
        for (int i = 0; w * h > i; i++) {
            int x = i * w + i, y = i * h + i, f = (y | y + y + -1 + x + w / h);
            ((BYTE*)(data + i))[2] = (f / 10);
        }
		
        SetBitmapBits(hbm, w * h * 4, data); 
		BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCERASE);
        Sleep(50);
    }
}

