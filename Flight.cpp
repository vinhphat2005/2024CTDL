#include "HeaderFiles/Flight.h"
#include "HeaderFiles/Utilities.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;
//constructor
Flight::Flight() : flightID(""), departureDate(""), airplaneID(""), destination(""), status(1) {}
Flight::Flight(const string& flightID, const string& departureDate, const string& airplaneID, const string& destination, int status, int seatCount) {
    this->flightID = flightID;
    this->departureDate = departureDate;
    this->airplaneID = airplaneID;
    this->destination = destination;
    this->status = status;
    if (seatCount != 0) 
    {
        for (int i = 0; i < seatCount; i++)
        {
            availableSeats.push_back(i);
        }
    }
}

//input
void Flight::inputFlight(vector<Airplane>& danhSachMayBay)
{
    //Nhap Flight ID
    cout << "Nhap ma chuyen bay: ";
    cin >> flightID;
    cin.ignore();
    
    //Nhap Date
    int day, month, year;
    while (true)
    {
        cout << "Nhap ngay xuat phat (dd mm yyyy): ";
        string dateInput;
        getline(cin, dateInput);
        stringstream ss(dateInput);
        if (ss >> day >> month >> year && isValidDate(day, month, year))
        {
            ostringstream formattedDate;
            formattedDate << setw(2) << setfill('0') << day << "/" << setw(2) << setfill('0') << month << "/" << year;
            departureDate = formattedDate.str();
            break;
        }
        else
        {
            cout << "Ngay thang nam khong hop le, vui long nhap lai!" << endl;
        }
    }

    //Nhap airplaneID
    while (true)
    {
        cout << "Nhap ma may bay: ";
        cin >> airplaneID;
        cin.ignore();

        // Kiem tra airplaneID co ton tai khong
        bool found = false;
        Airplane::loadAirplanesFromFile(danhSachMayBay);
        for (const auto& airplane : danhSachMayBay)
        {
            if (airplane.getAirplaneID() == airplaneID) 
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            break;
        }
        else
        {
            cout << "Ma may bay khong ton tai trong danh sach, vui long nhap lai!" << endl;
        }
    }
    //Nhap Destination
    cout << "Nhap san bay den: ";
    getline(cin, destination);
    
    //Nhap status
    do
    {
        cout << "Nhap trang thai cua chuyen bay (0 la huy chuyen, 1 la con ve, 2 la het ve, 3 la hoan tat): ";
        cin >> status;
        if (cin.fail() || status < 0 || status > 3)
        {
            cout << "Status khong hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    } while (true);
    
}
//Xuat ra cac chuyen bay
void Flight::displayflight() const
{
    cout << "----------------------\n";
    cout << "ma chuyen bay: " << flightID << "\n";
    cout << "ngay xuat phat: " << departureDate << "\n";
    cout << "ma may bay: " << airplaneID << "\n";
    cout << "San bay toi: " << destination << "\n";
    cout << "trang thai: ";
    switch (status) {
    case 0: cout << "huy chuyen"; break;
    case 1: cout << "con ve"; break;
    case 2: cout << "het ve"; break;
    case 3: cout << "hoan tat"; break;
    default: cout << "khong xac dinh"; break;
    }
    cout << "\nSo ghe: " << availableSeats.size() << "\n";
}

//doc du lieu tu danh sach chuyen bay do nguoi dung` nhap thong qua inputflight va bo vao file ChuyenBay.txt
void Flight::saveFlightsToFile(vector<Airplane>& danhSachMayBay)
{
    ofstream outFile("TextFiles/ChuyenBay.txt", ios::app);
    if (!outFile.is_open()) {
        cerr << "Error: Khong mo duoc file ChuyenBay.txt" << endl;
        return;
    }
    int soluongchuyenbay;
    do
    {
        cout << "hay nhap so luong chuyen bay ma ban muon them (phai lon hon 0): ";
        cin >> soluongchuyenbay;
        if (soluongchuyenbay <= 0)
        {
            cout << "so luong nhap khong hop le. vui long nhap lai!" << endl;
        }
    } while (soluongchuyenbay <= 0);
    //Su dung input de moi` nguoi dung nhap va dua vao file
    for (int i = 0; i < soluongchuyenbay; i++)
    {
        Flight newFlight;
        setTextColor(14);
        cout << "Nhap chuyen bay thu " << i + 1 << ": \n";
        setTextColor(7);
        newFlight.inputFlight(danhSachMayBay);
        int tempSeatCount = findSeatCount(newFlight.airplaneID);
        outFile << newFlight.flightID << " " << newFlight.departureDate << " " << newFlight.airplaneID << " " << newFlight.destination << " " 
            << newFlight.status << " " << tempSeatCount << endl;
    }
    outFile.close();
    cout << "da luu chuyen bay thanh cong." << endl;
}

//doc file tu file ChuyenBay.txt 
void Flight::loadFlightFromFile(vector<Flight>& danhSachChuyenBay)
{
    ifstream fileIn("TextFiles/ChuyenBay.txt");
    if (!fileIn.is_open())
    {
        cerr << "Khong mo duoc file ChuyenBay.txt" << endl;
        return;
    }
    danhSachChuyenBay.clear();
    string line;
    while (getline(fileIn, line)) {
        stringstream ss(line);
        string fID, date, aID, des;
        int sta;
        int seatCount;
        ss >> fID >> date >> aID;
        //Luu san bay toi
        getline(ss >> ws, des); 
        //Vi san bay duoc quyen co khoang cach nen getline da lay het tu san bay -> seatCount
        // => tim 2 vi tri ' ' o cuoi de xac dinh status va seatCount -> chuyen chung tu string -> int
        size_t lastSpace = des.find_last_of(' '); 
        if (lastSpace != string::npos) {
            string seatStr = des.substr(lastSpace + 1); 
            des = des.substr(0, lastSpace); 
            // vi tri thu 2 bi rong~
            size_t secondLastSpace = des.find_last_of(' '); 
            if (secondLastSpace != string::npos) {
                string staStr = des.substr(secondLastSpace + 1); 
                des = des.substr(0, secondLastSpace); 

                stringstream seatStream(seatStr), staStream(staStr);
                seatStream >> seatCount;
                staStream >> sta;       
            }
        }
        danhSachChuyenBay.emplace_back(fID, date, aID, des, sta, seatCount); // su dung emplace_back de khoi tao bien tam thoi` -> su dung constructor ap' thang? vao cuoi vector
    }
    fileIn.close();
}
