#include "HeaderFiles/Screen.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;
Admin::Admin() {}
Admin::Admin(string user, string pass) : username(user), password(pass) {}
bool Admin::loginAdmin()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    string userInput, passInput;
    const int maxAttempts = 3; 
    int attempt = 0;
    const int menuSize = 6;
    int verticalPadding = (screenHeight - menuSize) / 2;
    while (attempt < maxAttempts)
    {
        ScreenLogin();
        setTextColor(2);
        cout << string((screenWidth - 6) / 2, ' ') << "User: ";
        setTextColor(7);

        userInput = "";
        char ch;
        while ((ch = _getch()) != '\r') // nhan enter de ket thuc user
        {
            if (ch == 27) // Esc
            {
                setTextColor(12);
                system("cls");
                useVerticalPadding(verticalPadding);
                centerText("Co ve ban muon tro ve menu thuong.", screenWidth);
                centerText("An 1 de tro ve, hoac an 2 de tiep tuc nhap:", screenWidth);
                setTextColor(7);

                char choice = _getch(); // doc lua chon
                if (choice == '1')
                {
                    Screen();
                }
                else if (choice == '2')
                {
                    // cho nhap lai user
                    ScreenLogin();
                    setTextColor(2);
                    cout << string((screenWidth - 6) / 2, ' ') << "User: ";
                    setTextColor(7);
                    userInput = ""; // xoa input trc
                    continue;
                }
            }
            else if (ch == '\b') // Backspace
            {
                if (!userInput.empty())
                {
                    userInput.pop_back(); // xoa ki tu cuoi trong chuoi
                    cout << "\b \b";      // di chuyen con tro ve phia truoc -> de khoang trang ghi lai
                }
            }
            else
            {
                userInput += ch; // them ky tu vao chuoi
                cout << ch;
            }
        }
        cout << endl;

        setTextColor(2);
        cout << string((screenWidth - 6) / 2, ' ') << "Password: ";
        setTextColor(7);
        passInput = "";
        while ((ch = _getch()) != '\r')
        {
            if (ch == 27) // Esc
            {
                system("cls");
                useVerticalPadding(verticalPadding);
                setTextColor(12);
                centerText("Co ve ban muon tro ve menu thuong.", screenWidth);
                centerText("An 1 de tro ve, hoac an 2 de tiep tuc nhap:", screenWidth);
                setTextColor(7);

                char choice = _getch(); // doc lua chon
                if (choice == '1')
                {
                    Screen();
                }
                else if (choice == '2')
                {
                    // cho nhap lai pass
                    ScreenLogin();
                    setTextColor(2);
                    cout << string((screenWidth - 6) / 2, ' ') << "Password: ";
                    setTextColor(7);
                    passInput = ""; // xoa input trc do
                    continue;
                }
            }
            else if (ch == '\b')
            {
                if (!passInput.empty())
                {
                    passInput.pop_back(); 
                    cout << "\b \b";    
                }
            }
            else
            {
                passInput += ch; 
                cout << '*';     
            }
        }
        cout << endl;

        // kiem tra co the truy cap file va xem co dung username voi pass k
        ifstream file("TextFiles/Admin.txt");
        if (!file.is_open())
        {
            cout << "Khong the mo file Admin.txt!\n";
            return false;
        }

        string userFile, passFile;
        bool isAuthenticated = false;

        while (file >> userFile >> passFile)
        {
            if (userFile == userInput && passFile == passInput)
            {
                isAuthenticated = true;
                break;
            }
        }
        file.close();

        if (isAuthenticated)
        {
            system("cls");
            setTextColor(11);
            useVerticalPadding(verticalPadding);
            centerText("Dang nhap thanh cong!", screenWidth);
            setTextColor(7);
            Sleep(1000);
            return true;
        }
        else
        {
            int remainingAttempts = maxAttempts - attempt - 1; 
            setTextColor(12); 
            string errorMessage = "Khong dung password hoac username. Con ";
            errorMessage += to_string(remainingAttempts);
            errorMessage += " lan thu.";
            centerText(errorMessage, screenWidth);
            setTextColor(7); 

            attempt++;
            Sleep(1500); 
        }
    }
    system("cls");
    setTextColor(12);
    cout << "Nhap sai qua 3 lan, he thong xin duoc phep tam dung." << endl;
    setTextColor(7);
    return false;
}
