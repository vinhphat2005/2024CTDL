#include "Utilities.h"
#include "Airplane.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
using namespace std;
void setTextColor(int color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void setWindowSize()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Lấy thông tin bộ đệm của màn hình console
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    short scrBufferWidth = scrBufferInfo.dwSize.X;
    // xoá thanh cuộn (chiều cao buffer = window)
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;
    SetConsoleScreenBufferSize(hOut, newSize);
    // Đặt cửa sổ console ở chế độ toàn màn hình
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}
void disableResizeWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG_PTR style = GetWindowLongPtr(consoleWindow, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX; // Tắt nút "Maximize"
    style &= ~WS_SIZEBOX;     // Vô hiệu hóa thay đổi kích thước
    SetWindowLongPtr(consoleWindow, GWL_STYLE, style);
}
void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // bỏ settings của cursor hiện tại vào cursorinfo
    cursorInfo.bVisible = false; // hide cursor đi
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void centerText(const string& text, int width)
{
    int pad = (width - (int)text.length()) / 2;
    cout << setw(pad + text.length()) << text << endl;
}
void printTitle(int screenWidth)
{
    setTextColor(14);
    centerText("________                         .__              _____                  __________               ", screenWidth);
    centerText("\\_____  \\  __ _______    ____    |  | ___.__.    /     \\ _____  ___.__.  \\______   \\_____  ___.__.", screenWidth);
    centerText(" /  / \\  \\|  |  \\__  \\  /    \\   |  |<   |  |   /  \\ /  \\\\__  \\<   |  |   |    |  _/\\__  \\<   |  |", screenWidth);
    centerText("/   \\_/.  \\  |  // __ \\|   |  \\  |  |_\\___  |  /    Y    \\/ __ \\\\___  |   |    |   \\ / __ \\\\___  |", screenWidth);
    centerText("\\_____\\ \\_/____/(____  /___|  /  |____/ ____|  \\____|__  (____  / ____|   |______  /(____  / ____|", screenWidth);
    centerText("      \\__>          \\/     \\/        \\/               \\/     \\/\\/               \\/      \\/\\/     ", screenWidth);
    setTextColor(7);
}
void printAdminTitle(int screenWidth) 
{
    setTextColor(14);

    centerText("  ____  ___    ___ ___  ____  ____  ", screenWidth);
    centerText(" /    ||   \\  |   |   ||    ||    \\ ", screenWidth);
    centerText("|  o  ||    \\ | _   _ | |  | |  _  |", screenWidth);
    centerText("|     ||  D  ||  \\_/  | |  | |  |  |", screenWidth);
    centerText("|  _  ||     ||   |   | |  | |  |  |", screenWidth);
    centerText("|  |  ||     ||   |   | |  | |  |  |", screenWidth);
    centerText("|__|__||_____||___|___||____||__|__|", screenWidth);
    cout << endl;
    setTextColor(7);
}
