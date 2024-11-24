#include "HeaderFiles/Ticket.h"
#include "HeaderFiles/Flight.h"
#include "HeaderFiles/Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <vector>
using namespace std;
//constructor
Ticket::Ticket() : ticketID(""), flightID(""), customerID(""), customerName(""), seatNumber(0) {}
Ticket::Ticket(const string& fID, const string& cID, const string& cName, int seat)
    : flightID(fID), customerID(cID), customerName(cName), seatNumber(seat) {
    ticketID = generateTicketID();
}

//ham` de tao ra TicketID
string Ticket::generateTicketID() const {
    ostringstream oss;
    oss << flightID << "_" << setw(3) << setfill('0') << seatNumber; // Example: FLVN123_005
    return oss.str();
}

//ham` input
void Ticket::inputTicket()
{
    do
    {
        cout << "Nhap ma chuyen bay: ";
        getline(cin, flightID);

        if (flightID.empty() || flightID.find_first_not_of(" \t") == string::npos)
        {
            setTextColor(12);
            cout << "Ma chuyen bay khong duoc de trong hoac chi chua khoang trang!" << endl;
            setTextColor(7);
            continue; 
        }
        //kiem tra ma chuyen bay
        if (!Flight::checkStatus(flightID))
        {
            continue;
        }
        break;
    } while (true);


    string seatNumberInput;
    do
    {
        cout << "Nhap thu tu ghe: ";
        getline(cin, seatNumberInput);
        if (seatNumberInput.empty() || seatNumberInput.find_first_not_of("0123456789") != string::npos)
        {
            setTextColor(12);
            cout << "Thu tu ghe khong hop le. Vui long nhap mot so nguyen duong khong co khoang trang!" << endl;
            setTextColor(7);
            continue; 
        }
        seatNumber = stoi(seatNumberInput);
        if (!Flight::bookSeat(seatNumber, flightID))
        {
            continue; 
        }
        break;
    } while (true);

    this->ticketID = generateTicketID();
    do
    {
        cout << "Nhap CMND cho khach hang: ";
        getline(cin, customerID);
        if (!isValidInput(customerID))
        {
            setTextColor(12);
            cout << "CMND khong hop le. Vui long chi nhap ky tu va so!" << endl;
            setTextColor(7);
        }
    } while (customerID.empty() || isValidInput(customerID) == false);
    do
    {
        cout << "Nhap ho ten khach hang: ";
        getline(cin, customerName);
        if (customerName.empty() || customerName.find_first_not_of(" \t") == string::npos) {
            setTextColor(12);
            cout << "Ho ten khong duoc de trong hoac chi chua khoang trang!" << endl;
            setTextColor(7);
        }
    } while (customerName.empty() || customerName.find_first_not_of(" \t") == string::npos);
    Flight::addTicketToTicketList(flightID, ticketID, "TextFiles/ChuyenBay.txt");
}


//ham` xuat ra ticket
void Ticket::displayTicket() const
{
    cout << "----------------------\n";
    cout << "Ma ve: " << ticketID << endl;
    cout << "Ma chuyen bay: " << flightID << endl;
    cout << "CMND: " << customerID << endl;
    cout << "Ho ten: " << customerName << endl;
    cout << "So ghe: " << seatNumber << endl;
    cout << "----------------------\n";
}
//ham` check tim ky tu dac biet va khoach cach cho input VD: abc @ 123 = false 
bool Ticket::isValidInput(const string& input) {
    regex pattern("^[a-zA-Z0-9]+$"); 
    return regex_match(input, pattern);
}

//ham` su dung input de cho nguoi dung nhap va luu vao file
void Ticket::saveTicketToFile()
{ 
    int soluongve;
    do
    {
        setTextColor(11);
        cout << "hay nhap so luong ve muon dat (phai lon hon 0): ";
        setTextColor(7);
        cin >> soluongve;
        cin.ignore();
        if (soluongve <= 0)
        {
            setTextColor(12);
            cout << "so luong nhap khong hop le. vui long nhap lai!" << endl;
            setTextColor(7);
        }
    } while (soluongve <= 0);
    for (int i = 0; i < soluongve; i++)
    {
        Ticket newTicket;
        setTextColor(14);
        cout << "Hay nhap ve thu " << i + 1 << ": \n";
        setTextColor(7);
        newTicket.inputTicket();
        string filename = "TextFiles/" + newTicket.ticketID + ".txt";
        ofstream outFile(filename);

        if (!outFile)
        {
            cerr << "Khong the mo file " << filename << " de ghi du lieu!\n";
            continue;
        }
        outFile << newTicket.ticketID << " "
            << newTicket.customerID << " "
            << "\"" << newTicket.customerName << "\" "
            << newTicket.flightID << " "
            << newTicket.seatNumber << "\n";
        outFile.close();
        setTextColor(15);
        cout << "Da luu ve vao file " << filename << " thanh cong.\n";
        setTextColor(7);
    }
}
