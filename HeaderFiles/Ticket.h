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
    string generateTicketID() const;
public:
    Ticket();
    Ticket(const string& fID, const string& cID, const string& cName, int seat);
    string getTicketID() const;
    string getFlightID() const;
    string getCustomerID() const;
    string getCustomerName() const;
    int getSeatNumber() const;

    // Setter neu du thi xoa sau
    void setTicketID(const string& tID);
    void setFlightID(const string& fID);
    void setCustomerID(const string& cID);
    void setCustomerName(const string& cName);
    void setSeatNumber(int sNum);
    void inputTicket();
    void displayTicket() const;
    static bool isValidInput(const string& input);
    static void saveTicketToFile();
};

