#include "HeaderFiles/Airplane.h"
#include "HeaderFiles/Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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

//cho nguoi dung nhap
void Airplane::inputAirplane(vector<Airplane>& danhSachMayBay)
{
    //nhap ma may bay
    while (true)
    {
        cout << "Nhap ma may bay: ";
        getline(cin, airplaneID);

        // Kiem tra neu trong
        if (airplaneID.empty() || all_of(airplaneID.begin(), airplaneID.end(), isspace))
        {
            setTextColor(12);
            cout << "Ma may bay khong duoc de trong, vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        // Kiem tra xem co trung k
        bool isDuplicate = false;
        Airplane::loadAirplanesFromFile(danhSachMayBay); // Lay du lieu tu file MayBay.txt
        for (const auto& airplane : danhSachMayBay)
        {
            if (airplane.getAirplaneID() == airplaneID)
            {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate)
        {
            setTextColor(12);
            cout << "Ma may bay da ton tai trong file MayBay.txt, vui long nhap lai!" << endl;
            setTextColor(7);
        }
        else
        {
            break;
        }
    }

    // Nhap so luong ghe
    while (true)
    {
        cout << "Nhap so luong ghe (khong qua 500): ";
        string seatInput;
        getline(cin, seatInput);

        // Kiem tra neu de trong hoac chi co khoang trang
        if (seatInput.empty() || all_of(seatInput.begin(), seatInput.end(), isspace))
        {
            setTextColor(12);
            cout << "So luong ghe khong duoc de trong, vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        // Chuyen chuoi nhap thanh so nguyen
        stringstream ss(seatInput);
        if (ss >> seatCount && seatCount > 0 && seatCount <= 500)
        {
            break;
        }
        else
        {
            setTextColor(12);
            cout << "So luong ghe phai la so nguyen va khong lon hon 500, vui long nhap lai!" << endl;
            setTextColor(7);
        }
    }
}


void Airplane::displayAirplane() const 
{
    cout << "-------------------\n";
    cout << "Ma may bay: " << airplaneID << "\n";
    cout << "So luong ghe: " << seatCount << "\n";
}

//Luu vao file MayBay.txt (su dung inputAirplane de cho nguoi dung nhap)
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
    string input;
    do {
        setTextColor(11);
        cout << "Hay nhap so luong may bay ma ban muon them (phai lon hon 0): ";
        setTextColor(7);

        getline(cin, input);

        // Kiem tra xem so luong may bay co de trong khong
        if (input.empty()) 
        {
            setTextColor(12);
            cout << "So luong khong duoc de trong. Vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        // Kiem tra co phai nguyen khong
        stringstream ss(input);
        if (!(ss >> soluongmaybay) || soluongmaybay <= 0) {
            setTextColor(12);
            cout << "So luong nhap khong hop le. Vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        break; // Thoat neu hop le
    } while (true);
    // thuc hien su dung input va bo vao file
    for (int i = 0; i < soluongmaybay; i++)
    {
        Airplane newAirplane;
        setTextColor(14);
        cout << "Hay nhap may bay thu " << i + 1 << ": \n";
        setTextColor(7);
        newAirplane.inputAirplane(danhSachMayBay);
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

//Load lai may bay tu file MayBay.txt
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
