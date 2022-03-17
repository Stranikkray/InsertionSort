#include <windows.h>
#include <iostream>
#include <cmath>
#include <dos.h>

#define Width 5
#define Pass 2
#define Size 100

using namespace std;

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);

void Draw(int mass[], int nowNumber, int lastNumber)
{
    system("cls");
    
    COLORREF color;

    for (int i = 0; i < Size; i++)
    {
        if (nowNumber == i) 
            color = RGB(255, 0, 0);
        else if (lastNumber == i)
            color = RGB(0, 255, 0);
        else 
            color = RGB(255, 255, 255);

        HBRUSH temp_brush = CreateSolidBrush(color);
        RECT temp_rectangle = { i * (Width + Pass)+50, (Size - mass[i])*3+50, i * (Width + Pass) + Width+50,  Size * 3 +50};
        FillRect(hdc, &temp_rectangle,  temp_brush);
    }

    //Sleep(500);
}

BOOL ShowConsoleCursor(BOOL bShow)
{
    CONSOLE_CURSOR_INFO cci;
    HANDLE hStdOut;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return FALSE;
    if (!GetConsoleCursorInfo(hStdOut, &cci))
        return FALSE;
    cci.bVisible = bShow;
    if (!SetConsoleCursorInfo(hStdOut, &cci))
        return FALSE;
    return TRUE;
}

int main()
{   
    int mas[Size];

    for (size_t i = 0; i < Size; i++)
    {
        mas[i] = i + 1;
    }
    for (size_t i = 0; i < Size; i++)
    {
        int i1 = rand() % Size;
        int i2 = rand() % Size;
        int t = mas[i1];
        mas[i1] = mas[i2];
        mas[i2] = t;
    }


   ShowConsoleCursor(FALSE);
   

   int last = -1;
   for (size_t i = 1; i < Size; i++)
   {
       Draw(mas,i,last);

       int x = mas[i];       
       
       for (size_t n = i-1; n >= 0; n--)
       {
           if (x>=mas[n])
           {
               last = n + 1;
               mas[n + 1] = x;
               break;
           }
           mas[n + 1] = mas[n];
       }

      
   }
   Draw(mas,-1,-1);
   ReleaseDC(hwnd, hdc);
   cin.get();
}
