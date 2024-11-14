#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include <fstream>
using namespace std;

class Admin {
private:
    string username;
    string password;
public:
    Admin() {}
    Admin(string user, string pass);
    void inputAdmin();
    void displayAdmin();
    void saveAdmin(ofstream& file) const;
};
#endif