#include "HeaderFiles/Customer.h"
#include <fstream>
#include <iostream>
#include <sstream>

Customer::Customer(int num, string cmnd, string n) : number(num = 0), customerID(cmnd), customerName(n) {}

void Customer::saveCustomerToFiles(const string& customerID, const string& customerName)
{
    // Mo file de doc khach hang
    ifstream fileIn("TextFiles/KhachHang.txt");
    int number = 0;
    string line;

    // Doc tung dong de dem so khach hang hien co
    while (getline(fileIn, line)) {
        ++number;
    }
    fileIn.close();

    // Tang so thu tu cho khach hang moi
    number++;

    // Mo file de them thong tin khach hang moi
    ofstream fileOut("TextFiles/KhachHang.txt", ios::app);
    if (!fileOut.is_open()) 
    {
        cerr << "Khong mo duoc file KhachHang.txt de ghi!" << endl;
        return;
    }

    // Ghi thong tin vao file
    fileOut << number << " " << customerID << " " << customerName << endl;

    fileOut.close();
}