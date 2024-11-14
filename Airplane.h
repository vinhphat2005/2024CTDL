#ifndef AIRPLANE_H
#define AIRPLANE_H
#include <string>
#include <vector>
using namespace std;
class Airplane // luu o file MayBay.txt
{
private:
    string airplaneID;
    int seatCount;
public:
    Airplane(string aID, int seat);
    string getaID();
    void setaID(string);
    void inputAirplane();
    void displayAirplane() const;
    static void loadAirplanesFromFile(vector<Airplane>& danhSachMayBay, const string& filename);
};

#endif