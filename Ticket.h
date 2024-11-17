#pragma once
#include <string>
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
    void inputTicket(const string& flightID, int seatNumber);
    static bool isValidInput(const string& input);
    void saveTicketToFile() const;
    void displayTicket() const;
};

