#include "HeaderFiles/Screen.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <vector>
using namespace std;
vector<Airplane> danhSachMayBay;
vector<Flight> danhSachChuyenBay;
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
   
    for (int i = 0; i < verticalPadding; i++) 
    {
        cout << endl;
    }
    printTitle(screenWidth);
    for (int i = 0; i < menuSize; i++) 
    {
        if (i == currentOption) 
        {
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
void MenuAdmin(int currentOption)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    system("cls");
    const int menuSize = 7;
    string menu[] = { "Xu ly dat ve", "Xu ly tra ve", "Thong ke", "Them thong tin may bay", "Them thong tin chuyen bay", "Quay ve Menu thuong", "Thoat" };
    int verticalPadding = (screenHeight - menuSize) / 2;
   
    for (int i = 0; i < verticalPadding; i++) 
    {
        cout << endl;
    }
    printAdminTitle(screenWidth);
    for (int i = 0; i < menuSize; i++) 
    {
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
    setWindowSize();
    disableResizeWindow();
    hideCursor();
    int currentOption = 0;
    char key;
    while (true) 
    {
       
        Menu(currentOption);
        key = _getch(); 
        if (key == -32) 
        {
            key = _getch();
            if (key == 72) { 
                currentOption--;
                if (currentOption < 0) 
                {
                    currentOption = 5;
                }
            }
            else if (key == 80) 
            { 
                currentOption++;
                if (currentOption > 5) 
                {
                    currentOption = 0; 
                }
            }
        }
        else if (key == 13) 
        {
            system("cls");
            switch (currentOption)
            {
            case 0:
                Flight::loadFlightFromFile(danhSachChuyenBay);     
                if (danhSachChuyenBay.empty())
                {
                    setTextColor(14);
                    cout << "Hien tai khong co chuyen bay nao." << endl;
                    setTextColor(7);
                    return;
                }
                setTextColor(14);
                cout << "Hien thi danh sach cac chuyen bay:" << endl;
                setTextColor(7);
                for (const auto& flight : danhSachChuyenBay)
                {
                    flight.displayflight();
                }
                break;
            case 1:
                Ticket::saveTicketToFile();
                break;
            case 2:
                /*ScreenAdmin();*/
                if (Admin::loginAdmin())
                {
                    ScreenAdmin();
                }
                return;
            case 3:
               
                break;
            case 4:
                cout << "ban da chon chuc nang 5" << endl;
                break;
            case 5:
                cout << "Thoat thanh cong" << endl;
                return;
            }

            system("pause");
        }
    }
}
void ScreenAdmin()
{
    int currentOption = 0;
    char key;
    while (true) {
      
        MenuAdmin(currentOption);
        key = _getch(); 
        if (key == -32) 
        {
            key = _getch();
            if (key == 72) 
            { 
                currentOption--;
                if (currentOption < 0) 
                {
                    currentOption = 6; 
                }
            }
            else if (key == 80) 
            { 
                currentOption++;
                if (currentOption > 6) 
                {
                    currentOption = 0; 
                }
            }
        }
        else if (key == 13) 
        {
            system("cls");
            switch (currentOption)
            {
            case 0:
                Flight::bookTicket
                break;
            case 1:
                cout << "xu ly tra ve" << endl;
                break;
            case 2:
                cout << "Thong ke thanh cong" << endl;
                break;
            case 3:
                setTextColor(14);
                cout << "Moi ban them may bay: " << endl;
                setTextColor(7);
                Airplane::saveAirplanesToFile(danhSachMayBay);
                break;
            case 4:
                setTextColor(14);
                cout << "Moi ban them chuyen bay: " << endl;
                setTextColor(7);
                Flight::saveFlightsToFile(danhSachMayBay, danhSachChuyenBay);
                break;
            case 5:
                Screen();
                return;
            case 6:
                cout << "Thoat chuong trinh thanh cong." << endl;
                return;
            }

            system("pause");
        }
    }
}

void ScreenLogin()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    system("cls");
    const int menuSize = 6;
    int verticalPadding = (screenHeight - menuSize) / 2;
    for (int i = 0; i < verticalPadding; i++)
    {
        cout << endl;
    }
    // menu hien thi
    setTextColor(14);
    centerText("****************************************", screenWidth);
    int textWidth = 40;
    int padding = (screenWidth - textWidth) / 2;
    cout << string(padding, ' ');
    setTextColor(14);
    cout << "*";
    setTextColor(2);
    cout << "          DANG NHAP HE THONG          ";

    setTextColor(14);
    cout << "*" << endl;
    centerText("****************************************", screenWidth);
}
