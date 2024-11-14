#include "Admin.h"

void Admin::inputAdmin() { /* ... */ }
void Admin::displayAdmin() { /* ... */ }
void Admin::saveAdmin(ofstream& file) const
{
    file << username << " " << password << endl;
}
