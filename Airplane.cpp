#include "Airplane.h"
#include <iostream>
#include <fstream>
#include <vector>
Airplane::Airplane(string aID, int seat) : airplaneID(aID), seatCount(seat) {}
string Airplane::getaID() { return this->airplaneID; }
void Airplane::setaID(string airplaneID) { this->airplaneID = airplaneID; }
void Airplane::inputAirplane() {
    cout << "Nhap ma may bay: ";
    cin >> airplaneID;
    cout << "Nhap so luong ghe: ";
    cin >> seatCount;
}
void Airplane::displayAirplane() const {
    cout << "-------------------\n";
    cout << "Ma may bay: " << airplaneID << "\n";
    cout << "So luong ghe: " << seatCount << "\n";
}
void Airplane::loadAirplanesFromFile(vector<Airplane>& danhSachMayBay, const string& filename) {
    ifstream fileIn(filename);
    if (!fileIn.is_open()) {
        cerr << "Khong mo duoc file: " << filename << endl;
        perror("File mo da bi loi ");
        return;
    }

    danhSachMayBay.clear();
    string id;
    int seats;
    while (fileIn >> id >> seats) {
        danhSachMayBay.emplace_back(id, seats);
    }
    fileIn.close();
}