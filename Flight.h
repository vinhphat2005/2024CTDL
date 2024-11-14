
#ifndef FLIGHT_H
#define FLIGHT_H
#include <string>
using namespace std;
class Flight // luu o file ChuyenBay.txt
{
private:
    string flightID; // unique
    string departureDate;
    string airplaneID;
    string destination;
    int status; // 0 -> cancel, 1 -> con cho, 2 -> full, 3 -> hoan tat
public:
    Flight(string fID, string date, string aID, string des, int sta);
    void inputFlight();
};

#endif  