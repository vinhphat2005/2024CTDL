#pragma once
#include <string>
#include <vector>
using namespace std;
class Airplane // luu o file MayBay.txt
{
private:
    string airplaneID;
    int seatCount;
public:
    Airplane();
    Airplane(string aID, int seat);
    int getSeatCount() const;
    string getAirplaneID() const;
    void inputAirplane();
    void displayAirplane() const;
    static void saveAirplanesToFile(vector<Airplane>& danhSachMayBay);
    static void loadAirplanesFromFile(vector<Airplane>& danhSachMayBay);
};
