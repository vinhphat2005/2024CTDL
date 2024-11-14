#ifndef TICKET_H
#define TICKET_H
#include <string>
using namespace std;

class Ticket // Moi ve duoc luu tru ra file txt, MaVeTuongUng.txt
{
private:
    string ticketID;
    string airplaneID;
    string CMND;
    string name;
    int seatNumber;
public:
    Ticket(string tID, string aID, string cmnd, string n, int seat);
};

#endif
