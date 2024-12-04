#pragma once
#include <string>
#include <vector>
using namespace std;

class Ticket // Moi ve duoc luu tru ra file txt, MaVeTuongUng.txt
{
private:
    string ticketID;
    string flightID;
    string customerID;
    string customerName;
    int seatNumber;
    bool checkReady;
public:
    Ticket();
    Ticket(const string& fID, const string& cID, const string& cName, int seat);
    string generateTicketID() const;
    string getTicketID() const;
    string getFlightID() const;
    string getCustomerID() const;
    string getCustomerName() const;
    int getSeatNumber() const;
    void setTicketID(const string& tID);
    void setFlightID(const string& fID);
    void setCustomerID(const string& cID);
    void setCustomerName(const string& cName);
    void setSeatNumber(int sNum);
    void setCheckReady(bool status);
    bool isCheckReady() const;
    void inputTicket();
    void displayTicket() const;
    static bool isValidInput(const string& input);
    static void saveTicketToFile();
    static bool getIsBooked(const string& flightID, int seatNumber, const string& fileName);
};

