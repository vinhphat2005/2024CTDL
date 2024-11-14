#include "Airplane.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
string Airplane::filename = "MayBay.txt";
Airplane::Airplane() : airplaneID(""), seatCount(0) {}

Airplane::Airplane(string aID, int seat) : airplaneID(aID), seatCount(seat) {}


void Airplane::inputAirplane() 
{
    cout << "Nhap ma may bay: ";
    cin >> airplaneID;
    cout << "Nhap so luong ghe: ";
    cin >> seatCount;
}

void Airplane::displayAirplane() const 
{
    cout << "-------------------\n";
    cout << "Ma may bay: " << airplaneID << "\n";
    cout << "So luong ghe: " << seatCount << "\n";
}


void Airplane::saveAirplanesToFile(vector<Airplane>& danhSachMayBay)
{
    ofstream fileOut(Airplane::filename, ios::app);
    if (!fileOut.is_open())
    {
        cout << "Khong mo duoc file: " << Airplane::filename << endl;
        perror("File mo da bi loi ");
        return;
    }
    int soluongmaybay;
    do
    {
        cout << "Hay nhap so luong may bay ma ban muon them (Phai lon hon 0): ";
        cin >> soluongmaybay;
        if (soluongmaybay <= 0)
        {
            cout << "So luong nhap khong hop le. Vui long nhap lai!" << endl;
        }
    } while (soluongmaybay <= 0);
    for (int i = 0; i < soluongmaybay; i++)
    {
        Airplane newAirplane;
        newAirplane.inputAirplane();
        danhSachMayBay.emplace_back(newAirplane);
    }
    for (const auto& airplane : danhSachMayBay)
    {
        fileOut << airplane.airplaneID << " " << airplane.seatCount << endl;
    }
    fileOut.close();
    setTextColor(14);
    cout << "Da them may bay thanh cong!" << endl;
    setTextColor(7);
}


void Airplane::loadAirplanesFromFile(vector<Airplane>& danhSachMayBay) 
{
    ifstream fileIn(Airplane::filename);
    if (!fileIn.is_open()) {
        cerr << "Khong mo duoc file: " << Airplane::filename << endl;
        perror("File mo da bi loi ");
        return;
    }
    danhSachMayBay.clear();
    string id;
    int seats;
    while (fileIn >> id >> seats) {
        danhSachMayBay.emplace_back(id, seats);
    }
    if (danhSachMayBay.empty())
    {
        cout << "Hien tai khong co may bay nao." << endl;
        return;
    }
    setTextColor(14);
    cout << "Hien thi danh sach cac chuyen bay: " << endl;
    setTextColor(7);
    for (const auto& airplane : danhSachMayBay)
    {
        airplane.displayAirplane();
    }
    fileIn.close();
}