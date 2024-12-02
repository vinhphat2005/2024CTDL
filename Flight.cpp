#include "HeaderFiles/Flight.h"
#include "HeaderFiles/Utilities.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;
//constructor
Flight::Flight() : flightID(""), departureDate(""), airplaneID(""), destination(""), status(1) {}
Flight::Flight(const string& flightID, const string& departureDate, const string& airplaneID, const string& destination, int status, int seatCount) {
    this->flightID = flightID;
    this->departureDate = departureDate;
    this->airplaneID = airplaneID;
    this->destination = destination;
    this->status = status;
    if (seatCount != 0) 
    {
        availableSeats.resize(seatCount, 1);
    }

}

//input
void Flight::inputFlight(vector<Airplane>& danhSachMayBay, const vector<Flight>& danhSachChuyenBay)
{
    while (true)
    {
        cout << "Nhap ma chuyen bay (khong vuot 10 ki tu): ";
        getline(cin, flightID);

        if (flightID.empty() || all_of(flightID.begin(), flightID.end(), isspace))
        {
            setTextColor(12);
            cout << "Ma chuyen bay khong duoc de trong, vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }
        else if (flightID.length() > 10)
        {
            setTextColor(12);
            cout << "Ma chuyen bay khong duoc vuot qua 10 ky tu, vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }
        // Kiem tra xem flightId co ton tai ch
        bool isDuplicate = false;
        for (const auto& flight : danhSachChuyenBay)
        {
            if (flight.flightID == flightID)
            {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate)
        {
            setTextColor(12);
            cout << "Ma chuyen bay da ton tai. Vui long nhap ma khac!" << endl;
            setTextColor(7);
        }
        else
        {
            break;
        }
        // lam sach lai bo dem nhap
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Nhap Date
    int day, month, year;
    while (true)
    {
        cout << "Nhap ngay xuat phat (dd mm yyyy): ";
        string dateInput;
        getline(cin, dateInput);

        if (dateInput.empty() || all_of(dateInput.begin(), dateInput.end(), isspace)) {
            setTextColor(12);
            cout << "Ngay thang nam khong duoc de trong, vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        stringstream ss(dateInput);
        if (ss >> day >> month >> year && isValidDate(day, month, year))
        {
            ostringstream formattedDate;
            formattedDate << setw(2) << setfill('0') << day << "/" << setw(2) << setfill('0') << month << "/" << year;
            departureDate = formattedDate.str();
            break;
        }
        else
        {
            setTextColor(12);
            cout << "Ngay thang nam khong hop le, vui long nhap lai!" << endl;
            setTextColor(7);
        }
    }

    // Nhap airplaneID
    while (true)
    {
        cout << "Nhap ma may bay: ";
        getline(cin, airplaneID);

        if (airplaneID.empty() || all_of(airplaneID.begin(), airplaneID.end(), isspace)) {
            setTextColor(12);
            cout << "Ma may bay khong duoc de trong, vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        // Kiem tra airplaneID co ton tai khong
        bool found = false;
        Airplane::loadAirplanesFromFile(danhSachMayBay);
        for (const auto& airplane : danhSachMayBay)
        {
            if (airplane.getAirplaneID() == airplaneID)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            break;
        }
        else
        {
            setTextColor(12);
            cout << "Ma may bay khong ton tai trong danh sach, vui long nhap lai!" << endl;
            setTextColor(7);
        }
    }

    // Nhap Destination
    while (true)
    {
        cout << "Nhap san bay den (khong vuot 20 ki tu): ";
        getline(cin, destination);

        if (destination.empty() || all_of(destination.begin(), destination.end(), isspace))
        {
            setTextColor(12);
            cout << "San bay den khong duoc de trong, vui long nhap lai!" << endl;
            setTextColor(7);
        }
        else if (destination.length() > 20)
        {
            setTextColor(12);
            cout << "San bay den khong duoc vuot qua 20 ky tu, vui long nhap lai!" << endl;
            setTextColor(7);
        }
        else {
            break;
        }
    }

    // Nhap status
    do
    {
        cout << "Nhap trang thai cua chuyen bay (0 la huy chuyen, 1 la con ve, 2 la het ve, 3 la hoan tat): ";
        string statusInput;
        getline(cin, statusInput);

        if (statusInput.empty() || all_of(statusInput.begin(), statusInput.end(), isspace))
        {
            setTextColor(12);
            cout << "Trang thai khong duoc de trong, vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        stringstream ss(statusInput);
        if (ss >> status && status >= 0 && status <= 3)
        {
            break;
        }
        else
        {
            setTextColor(12);
            cout << "Status khong hop le, vui long nhap lai." << endl;
            setTextColor(7);
        }
    } while (true);
}
//Xuat ra cac chuyen bay
void Flight::displayflight() const
{
    cout << "----------------------\n";
    cout << "ma chuyen bay: " << flightID << "\n";
    cout << "ngay xuat phat: " << departureDate << "\n";
    cout << "ma may bay: " << airplaneID << "\n";
    cout << "San bay toi: " << destination << "\n";
    cout << "trang thai: ";
    switch (status) {
    case 0: cout << "huy chuyen"; break;
    case 1: cout << "con ve"; break;
    case 2: cout << "het ve"; break;
    case 3: cout << "hoan tat"; break;
    default: cout << "khong xac dinh"; break;
    }
    cout << "\nSo ghe: " << availableSeats.size() << "\n";
    cout << "Danh sach ve: \n";
    for (const auto& v : TicketList)
    {
        cout << v.getTicketID() << endl;
    }
}

//doc du lieu tu danh sach chuyen bay do nguoi dung` nhap thong qua inputflight va bo vao file ChuyenBay.txt
void Flight::saveFlightsToFile(vector<Airplane>& danhSachMayBay, const vector<Flight>& danhSachChuyenBay)
{
    ofstream outFile("TextFiles/ChuyenBay.txt", ios::app);
    if (!outFile.is_open()) {
        cerr << "Error: Khong mo duoc file ChuyenBay.txt" << endl;
        return;
    }
    int soluongchuyenbay;
    string input;
    do 
    {
        setTextColor(11);
        cout << "Hay nhap so luong chuyen bay ma ban muon them (phai lon hon 0): ";
        setTextColor(7);

    
        getline(cin, input);

        // Kiem tra co de trong khong
        if (input.empty()) 
        {
            setTextColor(12);
            cout << "So luong khong duoc de trong. Vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        // Kiem tra co phai so nguyen khong
        stringstream ss(input);
        if (!(ss >> soluongchuyenbay) || soluongchuyenbay <= 0) {
            setTextColor(12);
            cout << "So luong nhap khong hop le. Vui long nhap lai!" << endl;
            setTextColor(7);
            continue;
        }

        break; // thoat khoi neu hop le
    } while (true);

    //Su dung input de moi` nguoi dung nhap va dua vao file
    for (int i = 0; i < soluongchuyenbay; i++)
    {
        Flight newFlight;
        setTextColor(14);
        cout << "Nhap chuyen bay thu " << i + 1 << ": \n";
        setTextColor(7);
        newFlight.inputFlight(danhSachMayBay, danhSachChuyenBay);
        int tempSeatCount = findSeatCount(newFlight.airplaneID);
        outFile << newFlight.flightID << "," << newFlight.departureDate << "," << newFlight.airplaneID << "," << newFlight.destination << "," 
            << newFlight.status << "," << tempSeatCount << endl;
        vector<int> availableSeats(tempSeatCount, 1);
        saveSeatsToFile(newFlight.flightID, availableSeats);
    }

    outFile.close();
    setTextColor(15);
    cout << "da luu chuyen bay thanh cong." << endl;
    setTextColor(7);
}


//doc file tu file ChuyenBay.txt 
//void Flight::loadFlightFromFile(vector<Flight>& danhSachChuyenBay)
//{
//    ifstream fileIn("TextFiles/ChuyenBay.txt");
//    if (!fileIn.is_open())
//    {
//        cerr << "Khong mo duoc file ChuyenBay.txt" << endl;
//        return;
//    }
//
//    danhSachChuyenBay.clear();
//    string line;
//    while (getline(fileIn, line)) {
//        stringstream ss(line);
//        string fID, date, aID, des;
//        int sta = 0, seatCount = 0;
//
//        //doc tung dong
//        getline(ss, fID, ',');  
//        getline(ss, date, ',');  
//        getline(ss, aID, ',');  
//        getline(ss, des, ',');  
//        ss >> sta;  
//        ss.ignore(1, ',');  
//        ss >> seatCount;  
//        ss.ignore(1, ','); 
//
//        //doc tickets
//        string ticketListStr;
//        vector<string> ticketList;
//        if (getline(ss, ticketListStr)) {
//            stringstream ticketStream(ticketListStr);
//            string ticket;
//            while (getline(ticketStream, ticket, ',')) {
//                ticketList.push_back(ticket);
//            }
//        }
//
//        
//        vector<int> availableSeats = loadSeatsFromFile(fID);
//        if (availableSeats.empty()) {
//            availableSeats = vector<int>(seatCount, 1);  
//        }
//
//        //da doc thanh cong, bo vao danhSachChuyenBay
//        Flight flight(fID, date, aID, des, sta, seatCount);
//        flight.availableSeats = availableSeats;
//        
//
//        danhSachChuyenBay.emplace_back(flight);
//    }
//
//    fileIn.close();
//}


void Flight::loadFlightFromFile(vector<Flight>& danhSachChuyenBay)
{
    ifstream fileIn("TextFiles/ChuyenBay.txt");
    if (!fileIn.is_open())
    {
        cerr << "Khong mo duoc file ChuyenBay.txt" << endl;
        return;
    }

    danhSachChuyenBay.clear();
    string line;

    while (getline(fileIn, line))
    {
        stringstream ss(line);
        string fID, date, aID, des;
        int sta = 0, seatCount = 0;
        //doc thong tin flight
        getline(ss, fID, ',');
        getline(ss, date, ',');
        getline(ss, aID, ',');
        getline(ss, des, ',');
        ss >> sta;
        ss.ignore(1, ',');
        ss >> seatCount;
        ss.ignore(1, ',');

        Flight flight(fID, date, aID, des, sta, seatCount);

        flight.availableSeats = loadSeatsFromFile(fID);
        if (flight.availableSeats.empty())
        {
            flight.availableSeats = vector<int>(seatCount, 1);
        }
        //doc toan bo ve lquan den FLightID
        vector<Ticket> ticketList;
        while (ss.peek() != EOF) // neu con du lieu thi cu tiep tuc doc
        {
            string ticketID, ticketFlightID, customerID, customerName;
            int seatNumber = 0;

            getline(ss, ticketID, ',');
            getline(ss, ticketFlightID, ',');
            getline(ss, customerID, ',');
            getline(ss, customerName, ',');
            ss >> seatNumber;
            ss.ignore(1, ','); // doc so ghe xong bo qua dau phay
            //kiem tra khop ID 
            if (ticketFlightID != fID)
            {
                setTextColor(12);
                cerr << "Flight ID cua ve khong giong: " << ticketFlightID << endl;
                setTextColor(7);
                continue;  
            }

            Ticket ticket(ticketFlightID, customerID, customerName, seatNumber);
            ticketList.push_back(ticket);
        }
        //Bo ticket vao flight
        flight.TicketList = ticketList;
        //day vo danhsachchuyenbay
        danhSachChuyenBay.push_back(flight);
    }

    fileIn.close();
}

// su dung de check status may bay co ok khong khi dat ve
bool Flight::checkStatus(const string& _flightID)
{
    vector<Flight> tempFlights;
    Flight::loadFlightFromFile(tempFlights);

    for (const auto& flight : tempFlights)
    {
        if (flight.flightID == _flightID)
        {
            switch (flight.status)
            {
            case 0: 
                setTextColor(12);
                cout << "Chuyen bay da bi huy, khong the dat ve\n";
                setTextColor(7);
                return false;

            case 2: 
                setTextColor(12);
                cout << "Chuyen bay da het ve, khong the dat ve\n";
                setTextColor(7);
                return false;

            case 3: 
                setTextColor(12);
                cout << "Chuyen bay da hoan tat, khong the dat ve\n";
                setTextColor(7);
                return false;

            default: 
                return true;
            }
        }
    }
    setTextColor(12);
    cout << "Khong co ma chuyen bay nay, xin moi nhap lai\n";
    setTextColor(7);
    return false;
}
// luu seats vao file DanhSachGheTrong
void Flight::saveSeatsToFile(const string& flightID, const vector<int>& availableSeats) 
{
    //doc file
    ifstream inFile("TextFiles/DanhSachGheTrong.txt");
    if (!inFile.is_open()) {
        cerr << "Error: Khong mo duoc file DanhSachGheTrong.txt" << endl;
        return;
    }
    
    vector<string> fileContent;
    string line;
    bool found = false;

    while (getline(inFile, line)) 
    {
        stringstream ss(line);
        string currentFlightID;
        ss >> currentFlightID;
        //Tim xem neu trung -> da co -> thay the
        if (currentFlightID == flightID) 
        {
           
            stringstream updatedSeatsStream;
            for (size_t i = 0; i < availableSeats.size(); ++i) 
            {
                updatedSeatsStream << availableSeats[i];
                if (i != availableSeats.size() - 1) {
                    updatedSeatsStream << ",";
                }
            }
            fileContent.push_back(flightID + " " + updatedSeatsStream.str());
            found = true;
        }
        else {
        
            fileContent.push_back(line);
        }
    }
    inFile.close();
    //neu khong tim thay -> flightID moi -> tao ra mot cai moi
    if (!found) {
        stringstream newSeatsStream;
        for (size_t i = 0; i < availableSeats.size(); ++i) {
            newSeatsStream << availableSeats[i];
            if (i != availableSeats.size() - 1) {
                newSeatsStream << ",";
            }
        }
        fileContent.push_back(flightID + " " + newSeatsStream.str());
    }

    //check loi
    ofstream outFile("TextFiles/DanhSachGheTrong.txt");
    if (!outFile.is_open()) 
    {
        cerr << "Error: Khong mo duoc file DanhSachGheTrong.txt" << endl;
        return;
    }

    for (const auto& contentLine : fileContent) {
        outFile << contentLine << endl;
    }
    outFile.close();
}

// doc availableSeats tu file danhsachghetrong
vector<int> Flight::loadSeatsFromFile(const string& flightID) 
{
    ifstream fileIn("TextFiles/DanhSachGheTrong.txt");
    if (!fileIn.is_open()) 
    {
        cerr << "Khong mo duoc file DanhSachGheTrong.txt" << endl;
        return {};
    }

    string line;
    while (getline(fileIn, line)) 
    {
        stringstream ss(line);
        string fID, seatsStr;

        ss >> fID;
        if (fID == flightID) {
            getline(ss >> ws, seatsStr);
            vector<int> availableSeats;
            stringstream seatsStream(seatsStr);
            string seat;


            while (getline(seatsStream, seat, ',')) 
            {
                availableSeats.push_back(stoi(seat));
            }
            fileIn.close();
            return availableSeats;
        }
    }
    fileIn.close();
    return {};
}

//su dung de check coi viec dat ve co hop le khong (check thu tu ghe) 
bool Flight::bookSeat(int seat, const string& _flightID)
{
    vector<Flight> tempFlight;
    loadFlightFromFile(tempFlight);

    for (auto& flight : tempFlight)
    {
        if (flight.flightID == _flightID)
        {
            //su dung ham loadSeats de lay seats tu trong file danhsachghetrong
            vector<int> availableSeats = loadSeatsFromFile(_flightID);
            if (availableSeats.empty())
            {
                setTextColor(12);
                cout << "Thu tu ghe khong hop le. Vui long nhap lai!\n";
                setTextColor(7);
                return false;
            }

            if (static_cast<size_t>(seat) > availableSeats.size())
            {
                setTextColor(12);
                cout << "Thu tu ghe vuot qua so luong ghe hien tai. Vui long nhap lai!\n";
                setTextColor(7);
                return false;
            }
            size_t seatIndex = static_cast<size_t>(seat - 1); 
            if (availableSeats[seatIndex] == 0)
            {
                setTextColor(11);
                cout << "Da co nguoi dat ghe, vui long chon ghe khac.\n";
                setTextColor(7);
                return false;
            }
            //danh dau = 0
            availableSeats[seatIndex] = 0;
            cout << flight.availableSeats.size() << endl;
            for (auto& s : flight.availableSeats)
            {
                cout << s << " ";
            }
            cout << endl;
            //kiem tra xem tat ca ghe da duoc dat hay chua
            bool allSeatsBooked = true;
            for (const auto& s : flight.availableSeats)
            {
                if (s != 0)
                {
                    allSeatsBooked = false;
                    break;
                }
            }
            flight.status = allSeatsBooked ? 2 : 1; // chua sua de luu status
            saveSeatsToFile(_flightID, availableSeats);
            return true;
        }
    }
    cout << "Ma chuyen bay co van de\n";
    return false;
}


//Them ve' sau khi da duoc dat hoan thanh vao danhsachve o flight
void Flight::addTicketToTicketList(const Ticket& newTicket, const string& fileName) {
    vector<string> lines;
    ifstream inFile(fileName);
    string line;
    bool flightFound = false;

    while (getline(inFile, line)) 
    {
        stringstream ss(line);
        string tempFlightID;

        // tach flightid khoi dau phay
        getline(ss, tempFlightID, ',');
        //neu tim thay flightID thi bat dau thuc hien bo cac thong tin cua ticket vao line
        if (tempFlightID == newTicket.getFlightID()) 
        {
            flightFound = true;
            line += "," + newTicket.getTicketID() + "," + newTicket.getFlightID() + "," +
                newTicket.getCustomerID() + "," + newTicket.getCustomerName() + "," +
                to_string(newTicket.getSeatNumber());
        }

        lines.push_back(line);
    }
    inFile.close();
    //Can than neu khong tim thay thi se thong bao
    if (!flightFound) 
    {
        setTextColor(12);
        cerr << "Error: Khong tim thay FlightID: " << newTicket.getFlightID() << " trong file!" << endl;
        setTextColor(7);
        return;
    }
    //bat dau add vo file ChuyenBay.txt
    ofstream outFile(fileName);
    for (const string& l : lines) {
        outFile << l << endl;
    }
    outFile.close();
}

//Lay ra ticket tu ticketList cua mot Flight -> dang bao tri lat test sau, cai nay co ve nhu khong can thiet
void Flight::getTicketList(vector<string>& TicketList, const string& fileName) 
{
    ifstream inFile(fileName);
    string line;
    TicketList.clear();
    while (getline(inFile, line))
    {
     
        size_t pos = 0;
        int commaCount = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == ',') {
                ++commaCount;
                if (commaCount == 6) {
                    pos = i + 1; 
                    break;
                }
            }
        }

        // Neu co phan ve thi xu ly
        if (pos < line.size()) {
            string tickets = line.substr(pos); 

       
            stringstream ticketStream(tickets);
            string ticket;
            while (getline(ticketStream, ticket, ',')) {
                if (!ticket.empty()) { 
                    TicketList.push_back(ticket);
                }
            }
        }
    }
    inFile.close();
}

