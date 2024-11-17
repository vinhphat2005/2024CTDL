#include "Ticket.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <iomanip>
using namespace std;
Ticket::Ticket() : ticketID(""), flightID(""), customerID(""), customerName(""), seatNumber(0) {}
Ticket::Ticket(const string& fID, const string& cID, const string& cName, int seat)
    : flightID(fID), customerID(cID), customerName(cName), seatNumber(seat) {
    ticketID = generateTicketID();
}
string Ticket::generateTicketID() const {
    ostringstream oss;
    oss << flightID << "_" << setw(3) << setfill('0') << seatNumber; // Example: FL123_005
    return oss.str();
}
void Ticket::inputTicket(const string& flightID, int seatNumber)
{
    this->flightID = flightID;
    this->seatNumber = seatNumber;
    this->ticketID = generateTicketID();
    do
    {
        cout << "Nhap CMND cho khach hang: ";
        getline(cin, customerID);
        if (!isValidInput(customerID))
        {
            cout << "CMND khong hop le. Vui long chi nhap ky tu va so!" << endl;
        }
    } while (customerID.empty() || isValidInput(customerID) == false);
    do
    {
        cout << "Nhap ho ten khach hang: ";
        getline(cin, customerName);
        if (customerName.empty() || customerName.find_first_not_of(" \t") == string::npos) {
            cout << "Ho ten khong duoc de trong hoac chi chua khoang trang!" << endl;
        }
    } while (customerName.empty() || customerName.find_first_not_of(" \t") == string::npos);
}
bool Ticket::isValidInput(const string& input) {
    regex pattern("^[a-zA-Z0-9]+$"); 
    return regex_match(input, pattern);
}

void Ticket::saveTicketToFile() const {
    string filename = ticketID + ".txt";
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Khong the mo file " << filename << " de ghi du lieu!\n";
        return;
    }
    outFile << "Ma ve: " << ticketID << endl;
    outFile << "Ma chuyen bay: " << flightID << endl;
    outFile << "CMND: " << customerID << endl;
    outFile << "Ho ten: " << customerName << endl;
    outFile << "So ghe: " << seatNumber << endl;
    outFile.close();
    cout << "Da luu ve vao file " << filename << " thanh cong.\n";
}
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