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
    vector<Ticket> TicketList;
public:
    Flight();
    Flight(const string& flightID, const string& departureDate, const string& airplaneID, const string& destination, int status, int seatCount);
    vector<Ticket> getTicketList() const;
    string getFlightID() const;
    void inputFlight(vector<Airplane>& danhSachMayBay, const vector<Flight>& danhsachChuyenBay);
    void displayflight() const;
    static void saveFlightsToFile(vector<Airplane>& danhSachMayBay, const vector<Flight>& danhSachChuyenBay);
    static void loadFlightFromFile(vector<Flight>& danhSachChuyenBay);
    static bool checkStatus(const string& _flightID);
    static void saveSeatsToFile(const string& flightID, const vector<int>& seats);
    static vector<int> loadSeatsFromFile(const string& flightID);
    static bool bookSeat(int seat, const string& _flightID);
    static void addTicketToTicketList(const Ticket& newTicket, const string& fileName);
    static void removeTicket(const string& flightID, const string& ticketID, const string& fileName);
    void removeTicketAndFile(const string& flightID, const string& ticketID, const string& fileName);
    static void getTicketList(vector<string>& TicketList, const string& fileName);
    static void processTickets(vector<Flight>& danhSachChuyenBay, const string& fileName, const string& customerFile);
    static void processReturnTicket(vector<Flight>& danhSachChuyenBay, const string& ticketsFile, const string& seatsFile);
};