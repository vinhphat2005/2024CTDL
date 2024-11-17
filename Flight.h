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
    string flightID; // unique
    string departureDate;
    string airplaneID;
    string destination;
    int status; // 0 -> cancel, 1 -> con cho, 2 -> full, 3 -> hoan tat
    vector<int> availableSeats;
    vector<Ticket> TicketList;
public:
    Flight();
    Flight(const string& flightID, const string& departureDate, const string& airplaneID, const string& destination);
    void inputFlight(const vector<Airplane>& danhSachMayBay);
    void displayflight() const;

    static void saveFlightsToFile(vector<Flight>& danhSachChuyenBay, const vector<Airplane>& danhSachMayBay);
};