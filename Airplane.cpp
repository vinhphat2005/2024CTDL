#include "HeaderFiles/Airplane.h"
#include "HeaderFiles/Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
Airplane::Airplane() : airplaneID(""), seatCount(0) {}

Airplane::Airplane(string aID, int seat) : airplaneID(aID), seatCount(seat) {}

int Airplane::getSeatCount() const
{
    return seatCount;
}

string Airplane::getAirplaneID() const
{
    return airplaneID;
}

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
    ofstream fileOut("TextFiles/MayBay.txt", ios::app);
    if (!fileOut.is_open())
    {
        cout << "Khong mo duoc file: TextFiles/MayBay.txt" << endl;
        perror("File mo da bi loi ");
        return;
    }
    int soluongmaybay;
    do
    {
        setTextColor(11);
        cout << "Hay nhap so luong may bay ma ban muon them (phai lon hon 0): ";
        setTextColor(7);
        cin >> soluongmaybay;
        if (soluongmaybay <= 0)
        {
            setTextColor(12);
            cout << "So luong nhap khong hop le. Vui long nhap lai!" << endl;
            setTextColor(7);
        }
    } while (soluongmaybay <= 0);
    for (int i = 0; i < soluongmaybay; i++)
    {
        Airplane newAirplane;
        setTextColor(14);
        cout << "Hay nhap may bay thu " << i + 1 << ": \n";
        setTextColor(7);
        newAirplane.inputAirplane();
        danhSachMayBay.emplace_back(newAirplane);
    }
    for (const auto& airplane : danhSachMayBay)
    {
        fileOut << airplane.airplaneID << " " << airplane.seatCount << endl;
    }
    fileOut.close();
    setTextColor(15);
    cout << "Da them may bay thanh cong!" << endl;
    setTextColor(7);
}


void Airplane::loadAirplanesFromFile(vector<Airplane>& danhSachMayBay) 
{
    ifstream fileIn("TextFiles/MayBay.txt");
    if (!fileIn.is_open()) 
    {
        cerr << "Khong mo duoc file: TextFiles/MayBay.txt" << endl;
        return;
    }
    danhSachMayBay.clear();
    string id;
    int seats;
    while (fileIn >> id >> seats) 
    {
        danhSachMayBay.emplace_back(id, seats);
    }
    if (danhSachMayBay.empty())
    {
        setTextColor(14);
        cout << "Hien tai khong co may bay nao." << endl;
        setTextColor(7);
        return;
    }
    fileIn.close();
}
