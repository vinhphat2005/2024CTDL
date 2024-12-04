#include "HeaderFiles/Customer.h"
#include "HeaderFiles/Utilities.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
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

bool Customer::removeCustomerFromQueue(const string & customerID, const string & customerName, const string & fileName)
{
    ifstream inFile(fileName);
    if (!inFile.is_open()) 
    {
        cerr << "Khong the mo file " << fileName << " de doc.\n";
        return false;
    }

    vector<string> lines;
    string line;
    int customerIndex = -1;

    // Doc du lieu va tim vi tri cua khach hang
    while (getline(inFile, line)) {
        stringstream ss(line);
        int number;
        string id, name;
        ss >> number >> id;
        getline(ss, name);

        if (id == customerID && name.find(customerName) != string::npos) {
            customerIndex = number;
            continue; // Bo qua khach hang nay (tuc la xoa)
        }
        lines.push_back(line);
    }
    inFile.close();

    // Neu khong tim thay, bao loi
    if (customerIndex == -1) {
        cerr << "Khong tim thay khach hang trong danh sach.\n";
        return false;
    }

    // Cap nhat thu tu cua cac khach hang lai
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Khong the mo file " << fileName << " de ghi.\n";
        return false;
    }

    int newIndex = 1;
    for (const auto& l : lines) {
        stringstream ss(l);
        int number;
        string id, name;
        ss >> number >> id;
        getline(ss, name);
        outFile << newIndex << " " << id << name << endl;
        newIndex++;
    }
    outFile.close();

    return true;
}
