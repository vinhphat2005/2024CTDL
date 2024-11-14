#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
using namespace std;

class Customer // luu KhachHang.txt
{
private:
    int customerID;
    string CMND;
    string name;
public:
    Customer(int id, string cmnd, string n);
};
#endif
