#include "Utilities.h"
#include "Airplane.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
using namespace std;
void setTextColor(int color) {
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
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX; // Tắt nút "Maximize"
    style &= ~WS_SIZEBOX;     // Vô hiệu hóa thay đổi kích thước
    SetWindowLong(consoleWindow, GWL_STYLE, style);
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

void Menu(int currentOption)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    system("cls");
    const int menuSize = 6;
    string menu[] = { "Hien thi danh sach cac chuyen bay", "Dat ve", "Quan ly", "chuc nang 4", "chuc nang 5", "Thoat" };
    int verticalPadding = (screenHeight - menuSize) / 2;
    // In ra các dòng trống để đưa menu xuống giữa màn hình theo chiều dọc
    for (int i = 0; i < verticalPadding; i++) {
        cout << endl;
    }
    printTitle(screenWidth);
    for (int i = 0; i < menuSize; i++) {
        if (i == currentOption) {
            setTextColor(12);
            centerText("> " + menu[i] + " <", screenWidth);
        }
        else {
            setTextColor(11);
            centerText(menu[i], screenWidth);
        }
    }
    setTextColor(7);
}

void Screen()
{
    vector<Airplane> danhSachMayBay;
    string filename = "MayBay.txt";
    setWindowSize();
    disableResizeWindow();
    hideCursor();
    int currentOption = 0;
    char key;
    while (true) {
        //In ra menu với con trỏ ở vị trí hiện tại
        Menu(currentOption);
        key = _getch();  // Đọc phím nhấn đầu tiên
        if (key == -32) {
            key = _getch();
            if (key == 72) { // Nhận mũi tên (lên)
                currentOption--;
                if (currentOption < 0) {
                    currentOption = 5; // Quay về cuối menu
                }
            }
            else if (key == 80) { // Nhận mũi tên xuống
                currentOption++;
                if (currentOption > 5) {
                    currentOption = 0; // Quay về đầu menu
                }
            }
        }
        else if (key == 13) {
            system("cls");
            switch (currentOption)
            {
            case 0:
                cout << "Hien thi danh sach cac chuyen bay" << endl;
                Airplane::loadAirplanesFromFile(danhSachMayBay, filename);
                for (const auto& airplane : danhSachMayBay)
                {
                    airplane.displayAirplane();
                }
                break;
            case 1:
                cout << "Chuan bi dat ve" << endl;
                break;
            case 2:
                cout << "Ban da chon chuc nang 3" << endl;
                break;
            case 3:
                cout << "Ban da chon chuc nang 4" << endl;
                break;
            case 4:
                cout << "ban da chon chuc nang 5" << endl;
                break;
            case 5:
                cout << "Thoat thanh cong" << endl;
                return;
                break;
            }

            system("pause");
        }
    }
}
