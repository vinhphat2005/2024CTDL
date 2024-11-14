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
    static string filename;
public:
    Airplane();
    Airplane(string aID, int seat);
    void inputAirplane();
    void displayAirplane() const;
    static void saveAirplanesToFile(vector<Airplane>& danhSachMayBay);
    static void loadAirplanesFromFile(vector<Airplane>& danhSachMayBay);
};

#endif