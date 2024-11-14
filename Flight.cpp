#include "Flight.h"

Flight::Flight(string fID, string date, string aID, string des, int sta)
    : flightID(fID), departureDate(date), airplaneID(aID), destination(des), status(sta) {}

void Flight::inputFlight() { /* ... */ }
