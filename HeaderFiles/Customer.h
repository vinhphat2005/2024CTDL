#pragma once
#include <string>
using namespace std;

class Customer // luu KhachHang.txt
{
private:
    int number;
    string customerID;
    string customerName;
public:
    Customer(int num, string cmnd, string n);
    static void saveCustomerToFiles(const string& customerID, const string& customerName);
};

