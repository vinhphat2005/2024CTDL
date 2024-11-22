#pragma once
#include <string>
using namespace std;
void setTextColor(int color);
bool isLeapYear(int year);
bool isValidDate(int day, int month, int year);
void setWindowSize();
void disableResizeWindow();
void hideCursor();
void centerText(const string& text, int width);
void printTitle(int screenWidth);
void printAdminTitle(int screenWidth);
int findSeatCount(const string& airplaneIDToFind);
void useVerticalPadding(int VerticalPadding);