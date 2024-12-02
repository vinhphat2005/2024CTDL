#include "HeaderFiles/Ticket.h"
#include "HeaderFiles/Flight.h"
#include "HeaderFiles/Utilities.h"
#include "HeaderFiles/Customer.h"
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
// Getter
string Ticket::getTicketID() const { return ticketID; }
string Ticket::getFlightID() const { return flightID; }
string Ticket::getCustomerID() const { return customerID; }
string Ticket::getCustomerName() const { return customerName; }
int Ticket::getSeatNumber() const { return seatNumber; }

// Setter
void Ticket::setTicketID(const string& tID) { ticketID = tID; }
void Ticket::setFlightID(const string& fID) { flightID = fID; }
void Ticket::setCustomerID(const string& cID) { customerID = cID; }
void Ticket::setCustomerName(const string& cName) { customerName = cName; }
void Ticket::setSeatNumber(int sNum) { seatNumber = sNum; }
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
        //kiem tra status chuyen bay coi co ok khong (Phai con ve)
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
        //Nhap cmnd
    {
        cout << "Nhap CMND cho khach hang (11 ky tu): ";
        getline(cin, customerID);
        if (customerID.length() != 11 || customerID.find_first_not_of("0123456789") != string::npos)
        {
            setTextColor(12);
            cout << "CMND phai co dung 11 ky tu va chi bao gom so!" << endl;
            setTextColor(7);
        }
    } while (customerID.length() != 11 || customerID.find_first_not_of("0123456789") != string::npos);

    do
        //Nhap ho ten
    {
        cout << "Nhap ho ten khach hang (toi da 20 ky tu): ";
        getline(cin, customerName);
        if (customerName.empty() || customerName.find_first_not_of(" \t") == string::npos || customerName.length() > 20)
        {
            setTextColor(12);
            cout << "Ho ten khong duoc de trong, chi chua khoang trang, va phai nho hon 20 ky tu!" << endl;
            setTextColor(7);
        }
    } while (customerName.empty() || customerName.find_first_not_of(" \t") == string::npos || customerName.length() > 20);
    Customer::saveCustomerToFiles(customerID, customerName);
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
    string input;

    // Nhap so luong ve
    do
    {
        setTextColor(11);
        cout << "Hay nhap so luong ve muon dat (phai lon hon 0): ";
        setTextColor(7);

        getline(cin, input);

        // Kiem tra neu de trong
        if (input.empty() || input.find_first_not_of(' ') == string::npos) {
            setTextColor(12);
            cout << "So luong khong duoc de trong. Vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        // Kiem tra co nguyen
        stringstream ss(input);
        if (!(ss >> soluongve) || soluongve <= 0) {
            setTextColor(12);
            cout << "So luong nhap khong hop le. Vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        break; // Thoat neu ok
    } while (true);

    for (int i = 0; i < soluongve; i++)
    {
        Ticket newTicket;
        setTextColor(14);
        cout << "Hay nhap ve thu " << i + 1 << ": \n";
        setTextColor(7);
        newTicket.inputTicket();
        Flight::addTicketToTicketList(newTicket, "TextFiles/ChuyenBay.txt");
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
