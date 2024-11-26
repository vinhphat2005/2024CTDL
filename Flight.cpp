#include "HeaderFiles/Flight.h"
#include "HeaderFiles/Utilities.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
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
        cout << "Nhap ma chuyen bay: ";
        cin >> flightID;
        cin.ignore();
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
    }
    //Nhap Date
    int day, month, year;
    while (true)
    {
        cout << "Nhap ngay xuat phat (dd mm yyyy): ";
        string dateInput;
        getline(cin, dateInput);
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

    //Nhap airplaneID
    while (true)
    {
        cout << "Nhap ma may bay: ";
        cin >> airplaneID;
        cin.ignore();
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
    //Nhap Destination
    cout << "Nhap san bay den: ";
    getline(cin, destination);
    
    //Nhap status
    do
    {
        cout << "Nhap trang thai cua chuyen bay (0 la huy chuyen, 1 la con ve, 2 la het ve, 3 la hoan tat): ";
        cin >> status;
        if (cin.fail() || status < 0 || status > 3)
        {
            setTextColor(12);
            cout << "Status khong hop le, vui long nhap lai." << endl;
            setTextColor(7);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
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
        cout << v << endl;
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
    do
    {
        setTextColor(11);
        cout << "hay nhap so luong chuyen bay ma ban muon them (phai lon hon 0): ";
        setTextColor(7);
        cin >> soluongchuyenbay;
        if (soluongchuyenbay <= 0)
        {
            setTextColor(12);
            cout << "so luong nhap khong hop le. vui long nhap lai!" << endl;
            setTextColor(7);
        }
    } while (soluongchuyenbay <= 0);
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
    while (getline(fileIn, line)) {
        stringstream ss(line);
        string fID, date, aID, des;
        int sta = 0, seatCount = 0;

        
        getline(ss, fID, ',');  
        getline(ss, date, ',');  
        getline(ss, aID, ',');  
        getline(ss, des, ',');  
        ss >> sta;  
        ss.ignore(1, ',');  
        ss >> seatCount;  
        ss.ignore(1, ','); 

      
        string ticketListStr;
        vector<string> ticketList;
        if (getline(ss, ticketListStr)) {
            stringstream ticketStream(ticketListStr);
            string ticket;
            while (getline(ticketStream, ticket, ',')) {
                ticketList.push_back(ticket);
            }
        }

        
        vector<int> availableSeats = loadSeatsFromFile(fID);
        if (availableSeats.empty()) {
            availableSeats = vector<int>(seatCount, 1);  
        }

      
        Flight flight(fID, date, aID, des, sta, seatCount);
        flight.availableSeats = availableSeats;
        flight.TicketList = ticketList;

        danhSachChuyenBay.emplace_back(flight);
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
// luu seats vao file danhsachghetrong
void Flight::saveSeatsToFile(const string& flightID, const vector<int>& availableSeats) {
 
    ifstream inFile("TextFiles/DanhSachGheTrong.txt");
    if (!inFile.is_open()) {
        cerr << "Error: Khong mo duoc file DanhSachGheTrong.txt" << endl;
        return;
    }

    vector<string> fileContent;
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string currentFlightID;
        ss >> currentFlightID;

        if (currentFlightID == flightID) {
           
            stringstream updatedSeatsStream;
            for (size_t i = 0; i < availableSeats.size(); ++i) {
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

 
    ofstream outFile("TextFiles/DanhSachGheTrong.txt");
    if (!outFile.is_open()) {
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
    if (!fileIn.is_open()) {
        cerr << "Khong mo duoc file DanhSachGheTrong.txt" << endl;
        return {};
    }

    string line;
    while (getline(fileIn, line)) {
        stringstream ss(line);
        string fID, seatsStr;

        ss >> fID;
        if (fID == flightID) {
            getline(ss >> ws, seatsStr);
            vector<int> availableSeats;
            stringstream seatsStream(seatsStr);
            string seat;


            while (getline(seatsStream, seat, ',')) {
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
void Flight::addTicketToTicketList(const string& flightID, const string& ticket, const string& fileName) {
    vector<string> lines;
    ifstream inFile(fileName);
    string line;
    bool flightFound = false;

    // doc file vao vector
    while (getline(inFile, line)) {
        stringstream ss(line);
        string tempFlightID;

        // tach flightid khoi dau phay
        getline(ss, tempFlightID, ',');

        if (tempFlightID == flightID) {
            
            flightFound = true;

          // tim vi tri ve
            size_t pos = line.find_last_of(',');
            if (pos == string::npos) 
            {
                line += "," + ticket; // neu khong co ve nao thi them ve moi
            }
            else {
                line += "," + ticket; // co roi thi them moi vao cuoi danh sach
            }
        }

        lines.push_back(line); // luu vao vector
    }
    inFile.close();

    ofstream outFile(fileName);
    for (const string& l : lines) 
    {
        outFile << l << endl;
    }
    outFile.close();
}


void Flight::bookTicket(const string& flightID, const string& customerID, int seatNumber, const string& customerFile, const string& seatListFile) {
    vector<string> customerList;
    string customerInfo;
    bool customerFound = false;

    // doc va xoa khach hang khoi file khachhang.txt
    ifstream inFile(customerFile);
    string line;
    while (getline(inFile, line)) 
    {
        stringstream ss(line);
        int number;
        string tempCustomerID, name;

        ss >> number >> tempCustomerID; // doc so thu tu va cmnd
        getline(ss, name);             // doc ten

        // Loai bo khoang trang dau dong neu co
        if (!name.empty() && name[0] == ' ')
            name = name.substr(1);

        if (tempCustomerID == customerID) 
        {
            customerFound = true;
            customerInfo = tempCustomerID + " " + name; // luu thong tin khach hang
        }
        else {
            customerList.push_back(line); // giu lai khach hang khong lien quan
        }
    }
    inFile.close();

    if (!customerFound) 
    {
        setTextColor(12);
        cout << "Khach hang khong co trong hang` cho`!" << endl;
        setTextColor(7);
        return;
    }

    // Ghi lai file khachhang.txt sau khi xoa khach hang trong hang` cho`
    ofstream outFile(customerFile);
    for (const string& l : customerList) 
    {
        outFile << l << endl;
    }
    outFile.close();

    // Doc danh sach ghe trong tu file DanhSachGheTrong.txt
    vector<string> seatLines;
    inFile.open(seatListFile);
    while (getline(inFile, line)) 
    {
        seatLines.push_back(line);
    }
    inFile.close();

    // cap nhat danh sach ghe trong
    bool seatUpdated = false;
    for (string& seatLine : seatLines) 
    {
        stringstream ss(seatLine);
        string tempFlightID;
        ss >> tempFlightID; // doc flightid trc

        if (tempFlightID == flightID) 
        {
            size_t pos = seatLine.find(' ');
            string seats = seatLine.substr(pos + 1); // bat dau lay danh sach ghe
            vector<int> seatStatus;

            stringstream seatStream(seats);
            string seatToken;
            while (getline(seatStream, seatToken, ',')) 
            {
                seatStatus.push_back(stoi(seatToken)); // dua no vao vector
            }

            if (seatNumber < 1 || seatNumber > seatStatus.size() || seatStatus[seatNumber - 1] == 1) 
            {
                cout << "Ghế đã được đặt hoặc không tồn tại!" << endl;
                return;
            }

            //danh dau ghe' da check tu 0 -> 1
            seatStatus[seatNumber - 1] = 1;

            // Ghi lai danh sach ghe
            seatLine = flightID + " ";
            for (size_t i = 0; i < seatStatus.size(); ++i) {
                seatLine += to_string(seatStatus[i]);
                if (i != seatStatus.size() - 1) {
                    seatLine += ",";
                }
            }
            seatUpdated = true;
            break;
        }
    }

    if (!seatUpdated) {
        // check xem kh co flightid -> bao loi
        setTextColor(12);
        cout << "Flight ID không tồn tại trong danh sách ghế trống!" << endl;
        setTextColor(7);
        return;
    }

    // Ghi lai file ghe trong sau khi cap nhat
    outFile.open(seatListFile);
    for (const string& l : seatLines) {
        outFile << l << endl;
    }
    outFile.close();

    // Tao ve moi va them vao danh sach trong ChuyenBay.txt
    string ticketID = customerID + "_" + to_string(seatNumber); // CMND_SoGhe
    addTicketToTicketList(flightID, ticketID, "TextFiles/ChuyenBay.txt");

    // Luu ve vao file rieng
    outFile.open(ticketID + ".txt");
    outFile << flightID << "," << customerInfo << "," << seatNumber << endl;
    outFile.close();

    //Thong bao cho admin biet da hoan thanh
    system("cls");
    setTextColor(11);
    cout << "Dat ve thanh cong! Ve da duoc luu tai " << ticketID << ".txt" << endl;
    setTextColor(7);
}


void Flight::processBuyTicket()
{
    vector<Flight> danhSachChuyenBay;
    Flight::loadFlightFromFile(danhSachChuyenBay);
    for (auto& f : danhSachChuyenBay)
    {
        if (f.TicketList.empty())
        {
            continue;
        }
        
    }
}

// Hay them trong bien ticket khi dat ve phai check ten trong file KhachHang.txt de dat ve dung nguoi 