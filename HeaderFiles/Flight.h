#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Airplane.h"
#include "Ticket.h"
using namespace std;
class Flight // luu o file ChuyenBay.txt
{
private:
    string flightID; 
    string departureDate;
    string airplaneID;
    string destination;
    int status; // 0 -> cancel, 1 -> con cho, 2 -> full, 3 -> hoan tat
    vector<int> availableSeats;
    vector<string> TicketList;
public:
    Flight();
    Flight(const string& flightID, const string& departureDate, const string& airplaneID, const string& destination, int status, int seatCount);
    void inputFlight(vector<Airplane>& danhSachMayBay, const vector<Flight>& danhsachChuyenBay);
    void displayflight() const;
    static void saveFlightsToFile(vector<Airplane>& danhSachMayBay, const vector<Flight>& danhSachChuyenBay);
    static void loadFlightFromFile(vector<Flight>& danhSachChuyenBay);
    static bool checkStatus(const string& _flightID);
    static void saveSeatsToFile(const string& flightID, const vector<int>& seats);
    static vector<int> loadSeatsFromFile(const string& flightID);
    static bool bookSeat(int seat, const string& _flightID);
    static void addTicketToTicketList(const string& flightID, const string& ticket, const string& fileName);
    static void bookTicket(const string& flightID, const string& customerID, int seatNumber, const string& customerFile, const string& seatListFile);
    static void processBuyTicket();
};