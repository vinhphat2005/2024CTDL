#include "Flight.h"
#include "Utilities.h"
#include "Airplane.h"
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
void Flight::inputFlight(const vector<Airplane>& danhSachMayBay)
{
    cout << "Nhap ma chuyen bay: ";
    cin >> flightID;
    cin.ignore();
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
    cout << "Nhap ma may bay: ";
    cin >> airplaneID;
    cin.ignore();
    cout << "Nhap san bay den: ";
    getline(cin, destination);
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
void Flight::saveFlightsToFile(vector<Flight>& danhSachChuyenBay, const vector<Airplane>& danhSachMayBay)
{
    ofstream outFile("ChuyenBay.txt", ios::app);
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
    for (int i = 0; i < soluongchuyenbay; i++)
    {
        Flight newFlight;
        setTextColor(14);
        cout << "Nhap chuyen bay thu " << i + 1 << ": \n";
        setTextColor(7);
        newFlight.inputFlight(danhSachMayBay);
        danhSachChuyenBay.emplace_back(newFlight);
    }
    for (auto& flight : danhSachChuyenBay)
    {
        int tempSeatCount = findSeatCount(flight.airplaneID);
        outFile << flight.flightID << " " << flight.departureDate << " " << flight.airplaneID << " " << flight.destination << " " << flight.status << " " << tempSeatCount << endl;
    }
    outFile.close();
    cout << "da luu chuyen bay thanh cong." << endl;
}

//doc file tu file ChuyenBay.txt va su dung display de xuat ra
void Flight::loadFlightFromFile(vector<Flight>& danhSachChuyenBay)
{
    ifstream fileIn("ChuyenBay.txt");
    if (!fileIn.is_open())
    {
        cerr << "Khong mo duoc file ChuyenBay.txt" << endl;
        return;
    }
    danhSachChuyenBay.clear();
    string fID, date, aID, des;
    int sta;
    int seatCount;
    while (fileIn >> fID >> date >> aID >> des >> sta >> seatCount)
    {
        danhSachChuyenBay.emplace_back(fID, date, aID, des, sta, seatCount);
    }
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
    fileIn.close();
}
//void Flight::updateFlightStatus(const vector<Airplane>& danhSachMayBay, vector<Flight>& danhSachChuyenBay)
//{
//    for (auto& flight : danhSachChuyenBay)
//    {
//        for (const auto& airplane : danhSachMayBay)
//        {
//            if (flight.airplaneID == airplane.getAirplaneID())
//            {
//                if (airplane.getSeatCount() == 0)
//                {
//                    flight.status = 2; 
//                }
//                break; 
//            }
//        }
//    }
//}
//
//void Flight::bookSeat(Flight& tempFlight, int seat) 
//{
//    auto it = find(tempFlight.availableSeats.begin(), tempFlight.availableSeats.end(), seat);
//    if (it != tempFlight.availableSeats.end()) {
//        tempFlight.availableSeats.erase(it);  
//        if (tempFlight.availableSeats.empty()) {
//            tempFlight.status = 2;  
//        }
//    }
//    else {
//        cerr << "Ghe " << seat << " khong co san hoac da duoc dat." << endl;
//    }   
//}
