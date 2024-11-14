#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
using namespace std;
void setTextColor(int color);
void setWindowSize();
void disableResizeWindow();
void hideCursor();
void centerText(const string& text, int width);
void printTitle(int screenWidth);
void printAdminTitle(int screenWidth);
void Menu(int currentOption);
void MenuAdmin(int currentOption);
void Screen();
void ScreenAdmin();
#endif