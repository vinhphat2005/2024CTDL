#include "HeaderFiles/Flight.h"
#include "HeaderFiles/Utilities.h"
#include "HeaderFiles/Customer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdio>
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

vector<Ticket> Flight::getTicketList() const 
{
    return TicketList;
}
int Flight::getStatus() const 
{
    return status;
}
string Flight::getFlightID() const 
{
    return flightID;
}
string Flight::getAirplaneID() const
{
    return airplaneID;
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
            bool checkReady = false;

            getline(ss, ticketID, ',');
            getline(ss, ticketFlightID, ',');
            getline(ss, customerID, ',');
            getline(ss, customerName, ',');
            ss >> seatNumber;
            ss.ignore(1, ','); // doc so ghe xong bo qua dau phay
            ss >> checkReady;
            ss.ignore(1, ','); // doc xong checkReady bo qua dau phay
            //kiem tra khop ID 
            if (ticketFlightID != fID)
            {
                setTextColor(12);
                cerr << "Flight ID cua ve khong giong: " << ticketFlightID << endl;
                setTextColor(7);
                continue;  
            }

            Ticket ticket(ticketFlightID, customerID, customerName, seatNumber);
            ticket.setTicketID(ticketID);
            if (checkReady == 0)
            {
                ticket.setCheckReady(false);
            }
            else ticket.setCheckReady(true);
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
void Flight::addTicketToTicketList(const Ticket& newTicket, const string& fileName) 
{
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
            line += "," + newTicket.getTicketID() + "," +
                newTicket.getFlightID() + "," +
                newTicket.getCustomerID() + "," +
                newTicket.getCustomerName() + "," +
                to_string(newTicket.getSeatNumber()) + "," +
                (newTicket.isCheckReady() ? "1" : "0"); 
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
    for (const string& l : lines) 
    {
        outFile << l << endl;
    }
    outFile.close();
}



//xoa file 
static void deleteFile(const std::string& fileName)
{
    if (std::remove(fileName.c_str()) == 0)
    {
        
    }
    else
    {
        std::cerr << "Khong the xoa file: " << fileName
            << ". Kiem tra xem file co ton tai va co quyen truy cap hay khong." << std::endl;
    }
}
//xoa ticket
void Flight::removeTicketAndFile(const string& flightID, const string& ticketID, const string& fileName)
{
    removeTicket(flightID, ticketID, fileName);
    string ticketFile = "TextFiles/" + ticketID + ".txt";
    deleteFile(ticketFile);
}

void Flight::removeTicket(const string& flightID, const string& ticketID, const string& fileName)
{
    vector<string> lines; // Vector để lưu từng dòng của file
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cerr << "Khong mo duoc file " << fileName << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        // Kiểm tra nếu dòng bắt đầu bằng flightID + ","
        if (line.find(flightID + ",") == 0)
        {
            // Tách dòng thành các token
            vector<string> tokens;
            string token;
            stringstream ss(line);
            while (getline(ss, token, ','))
            {
                tokens.push_back(token);
            }

            // Tìm vị trí của ticketID trong tokens
            bool ticketFound = false;
            for (size_t i = 0; i < tokens.size(); ++i)
            {
                if (tokens[i] == ticketID)
                {
                    // Kiểm tra có đủ 5 trường sau ticketID để xóa
                    if (i + 5 < tokens.size())
                    {
                        // Xóa 6 trường: ticketID, customerID, customerName, flightID, seatNumber, checkReady
                        tokens.erase(tokens.begin() + i, tokens.begin() + i + 6);
                        ticketFound = true;
                        break; // Giả sử ticketID là duy nhất, nên dừng lại sau khi tìm thấy
                    }
                    else
                    {
                        setTextColor(12);
                        cerr << "Khong du lieu de xoa cho ticketID: " << ticketID << endl;
                        setTextColor(7);
                    }
                }
            }

            if (!ticketFound)
            {
                setTextColor(12);
                cerr << "Khong tim thay ticketID: " << ticketID << " trong flightID: " << flightID << endl;
                setTextColor(7);
            }

            // Xây dựng lại dòng sau khi đã xóa
            string newLine;
            for (size_t i = 0; i < tokens.size(); ++i)
            {
                newLine += tokens[i];
                if (i != tokens.size() - 1)
                    newLine += ",";
            }
            lines.push_back(newLine);
        }
        else
        {
            lines.push_back(line); // Dòng không thuộc flightID cần xóa thì giữ nguyên
        }
    }
    inFile.close();

    // Ghi lại dữ liệu đã chỉnh sửa vào file
    ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        cerr << "Khong the mo file " << fileName << " de ghi." << endl;
        return;
    }

    for (const string& l : lines)
    {
        outFile << l << endl;
    }
    outFile.close();
}


void Flight::processTickets(vector<Flight>& danhSachChuyenBay, const string& fileName, const string& customerFile)
{
    loadFlightFromFile(danhSachChuyenBay);
    for (size_t i = 0; i < danhSachChuyenBay.size();)
    {
        auto& flight = danhSachChuyenBay[i];
        setTextColor(15);
        cout << "Cac ticket cua chuyen bay " << flight.getFlightID() << " la:\n";
        setTextColor(7);

        vector<Ticket> ticketsToProcess;
        for (auto& ticket : flight.getTicketList())
        {
            if (!ticket.isCheckReady()) // Loại bỏ ticket đã checkReady
            {
                ticketsToProcess.push_back(ticket);
                cout << ticket.getTicketID() << endl;
            }
        }

        if (ticketsToProcess.empty())
        {
            setTextColor(14);
            cout << "Khong co ticket nao can duoc xu ly.\n";
            setTextColor(7);
        }
        else
        {
            while (true)
            {
                string selectedTicketID;
                setTextColor(11);
                cout << "Nhap ID cua ticket muon xu ly: ";
                setTextColor(7);
                cin >> selectedTicketID;

                auto it = find_if(ticketsToProcess.begin(), ticketsToProcess.end(),
                    [&selectedTicketID](const Ticket& t)
                    {
                        return t.getTicketID() == selectedTicketID;
                    });

                if (it == ticketsToProcess.end())
                {
                    setTextColor(12);
                    cout << "Khong tim thay ticket voi ID: " << selectedTicketID << endl;
                    setTextColor(7);
                    continue; // Quay lại yêu cầu nhập Ticket ID
                }

                Ticket& selectedTicket = *it;

                // Đọc thông tin khách hàng
                ifstream inFile(customerFile);
                if (!inFile.is_open())
                {
                    cerr << "Khong the mo file " << customerFile << " de doc.\n";
                    break; // Thoát vòng lặp nếu xảy ra lỗi
                }

                string line;
                int customerIndex = -1;
                stringstream ss;
                while (getline(inFile, line))
                {
                    ss.clear();
                    ss.str(line);
                    int number;
                    string id, name;
                    ss >> number >> id;
                    getline(ss, name);

                    if (id == selectedTicket.getCustomerID() &&
                        name.find(selectedTicket.getCustomerName()) != string::npos)
                    {
                        customerIndex = number;
                        break;
                    }
                }
                inFile.close();

                if (customerIndex == -1)
                {
                    setTextColor(12);
                    cerr << "Khong tim thay khach hang tuong ung voi ticket.\n";
                    setTextColor(7);
                    break; // Thoát vòng lặp nếu xảy ra lỗi
                }
                setTextColor(11);
                cout << "Khach hang " << selectedTicket.getCustomerName() << " co so thu tu " << customerIndex << ".\n";
                setTextColor(7);

                char choice;
                do {
                    setTextColor(14);
                    cout << "Ban co muon xu ly ticket nay? (y/n): ";
                    setTextColor(7);
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
                        break;
                    }
                    setTextColor(12);
                    cout << "Lua chon khong hop le, vui long nhap lai (y/n).\n";
                    setTextColor(7);
                } while (true);

                if (choice == 'n' || choice == 'N')
                {
                    setTextColor(12);
                    cout << "Huy bo xu ly ticket.\n";
                    setTextColor(7);
                    continue; // Quay lại yêu cầu nhập Ticket ID
                }

                // Xử lý ticket
                string ticketFileName = "TextFiles/" + selectedTicketID + ".txt";
                ifstream ticketFile(ticketFileName);
                if (!ticketFile.is_open())
                {
                    cerr << "Khong mo duoc file " << ticketFileName << endl;
                    break; // Thoát vòng lặp nếu xảy ra lỗi
                }

                string ticketData;
                getline(ticketFile, ticketData);
                ticketFile.close();

                ostringstream idStream;
                idStream << selectedTicket.getCustomerID() << selectedTicket.getCustomerName()
                    << "_" << setw(3) << setfill('0') << selectedTicket.getSeatNumber();
                string newTicketID = idStream.str();
                selectedTicket.setTicketID(newTicketID); // Cập nhật lại ID


                size_t ticketPos = ticketData.find(selectedTicketID);
                if (ticketPos != string::npos)
                {
                    ticketData.replace(ticketPos, selectedTicketID.length(), newTicketID);
                }

                // Cập nhật trạng thái checkReady trong đối tượng Ticket
                selectedTicket.setCheckReady(true);

                string processedFileName = "TextFiles/" + newTicketID + ".txt";
                ofstream processedFile(processedFileName);
                processedFile << ticketData << endl;
                processedFile.close();
                
                // xoa file cu
                flight.removeTicketAndFile(selectedTicket.getFlightID(), selectedTicketID, fileName);
                // tao ticket moi
                Ticket newTicket(newTicketID, selectedTicket.getCustomerID(),
                    selectedTicket.getCustomerName(), selectedTicket.getSeatNumber());
                newTicket.setFlightID(flight.getFlightID());
                newTicket.setCheckReady(true);
                //them vao flight
                newTicket.setTicketID(selectedTicket.getCustomerID() + selectedTicket.getCustomerName() +
                    "_" + (ostringstream() << setw(3) << setfill('0') << selectedTicket.getSeatNumber()).str());
                flight.addTicketToTicketList(newTicket, fileName);

                // Xóa khách hàng khỏi danh sách
                if (Customer::removeCustomerFromQueue(selectedTicket.getCustomerID(), selectedTicket.getCustomerName(), customerFile))
                {

                }
                else
                {
                    setTextColor(12);
                    cerr << "Khong the xoa khach hang khoi danh sach.\n";
                    setTextColor(7);
                }

                setTextColor(15);
                cout << "Da cap nhat va luu vao chuyen bay hoan tat.\n";
                setTextColor(7);
                break; 
            }
        }
        char nextChoice;
        do {
            setTextColor(15);
            cout << "Ban co muon chuyen sang chuyen bay tiep theo? (y/n): ";
            setTextColor(7);
            cin >> nextChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (nextChoice == 'y' || nextChoice == 'Y' || nextChoice == 'n' || nextChoice == 'N') {
                loadFlightFromFile(danhSachChuyenBay);
                break;
            }
            setTextColor(12);
            cout << "Lua chon khong hop le, vui long nhap lai (y/n).\n";
            setTextColor(7);
        } while (true);

        if (nextChoice == 'y' || nextChoice == 'Y') {
            ++i; // Chuyển sang chuyến bay kế tiếp
        }
        else {
            setTextColor(14);
            cout << "Tiep tuc xu ly chuyen bay hien tai.\n";
            setTextColor(7);
        }
    }
}

void Flight::processReturnTicket(vector<Flight>& danhSachChuyenBay, const string& seatsFile)
{
    loadFlightFromFile(danhSachChuyenBay);  // Load danh sách chuyến bay từ file

    for (size_t i = 0; i < danhSachChuyenBay.size();)
    {
        auto& flight = danhSachChuyenBay[i];
        setTextColor(15);
        cout << "Cac ticket cua chuyen bay " << flight.getFlightID() << " la:\n";
        setTextColor(7);

        vector<Ticket> ticketsToProcess;

        // Lấy danh sách vé cần xử lý
        for (auto& ticket : flight.getTicketList())
        {
            ticketsToProcess.push_back(ticket);
        }

        if (ticketsToProcess.empty())
        {
            setTextColor(14);
            cout << "Khong co ve nao trong chuyen bay nay.\n";
            setTextColor(7);
        }
        else
        {
            while (true)
            {
                // Hiển thị danh sách vé
                for (size_t j = 0; j < ticketsToProcess.size(); ++j)
                {
                    cout << j + 1 << ". " << ticketsToProcess[j].getTicketID() << endl;
                }

                cout << "Nhap so thu tu cua ve muon tra (hoac 0 de bo qua): ";
                int ticketIndex;
                cin >> ticketIndex;

                if (ticketIndex == 0)
                {
                    break; // Dừng xử lý vé và hỏi có muốn chuyển chuyến bay không
                }

                if (ticketIndex < 1 || ticketIndex > ticketsToProcess.size())
                {
                    setTextColor(12);
                    cout << "Lua chon khong hop le!\n";
                    setTextColor(7);
                    continue;
                }

                Ticket selectedTicket = ticketsToProcess[ticketIndex - 1];

                // Kiểm tra trạng thái chuyến bay
                if (flight.getStatus() == 2)
                {
                    setTextColor(12);
                    cout << "Khong the tra ve, may bay da hoan tat!" << endl;
                    setTextColor(7);
                    continue;
                }

                // Cập nhật file ghế ngồi
                string flightID = selectedTicket.getFlightID();
                int seatNumber = selectedTicket.getSeatNumber();
                if (updateSeatsFile(seatsFile, flightID, seatNumber))
                {
                    // Xóa vé và file liên quan
                    flight.removeTicketAndFile(selectedTicket.getFlightID(), selectedTicket.getTicketID(), "TextFiles/ChuyenBay.txt");
                }
                else
                {
                    setTextColor(12);
                    cout << "Cap nhat that bai ghe\n";
                    setTextColor(7);
                }
            }
        }

        // Hỏi người dùng có muốn chuyển sang chuyến bay tiếp theo không
        char nextChoice;
        do {
            setTextColor(15);
            cout << "Ban co muon chuyen sang chuyen bay tiep theo? (y/n): ";
            setTextColor(7);
            cin >> nextChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (nextChoice == 'y' || nextChoice == 'Y' || nextChoice == 'n' || nextChoice == 'N')
            {
                break;
            }
            setTextColor(12);
            cout << "Lua chon khong hop le, vui long nhap lai (y/n).\n";
            setTextColor(7);
        } while (true);

        if (nextChoice == 'y' || nextChoice == 'Y')
        {
            ++i; // Chuyển sang chuyến bay tiếp theo
        }
        else
        {
            setTextColor(14);
            cout << "Tiep tuc xu ly chuyen bay hien tai.\n";
            setTextColor(7);
        }
    }
}

bool Flight::updateSeatsFile(const string& seatsFile, const string& flightID, int seatNumber) 
{
    
    ifstream inFile(seatsFile);
    if (!inFile.is_open()) {
        cerr << "Khong mo duoc file " << seatsFile << endl;
        return false;
    }

    vector<string> updatedLines;
    string line;
    bool seatUpdated = false;

    while (getline(inFile, line)) 
    {
        stringstream ss(line);
        string id;
        ss >> id;

        // Loại bỏ khoảng trắng hoặc ký tự không mong muốn
        id.erase(remove_if(id.begin(), id.end(), ::isspace), id.end());

        if (id == flightID) {
            string updatedLine = id + " ";
            string seatStatus;
            int currentSeat = 0;

            while (getline(ss, seatStatus, ',')) 
            {
                // Loại bỏ khoảng trắng hoặc ký tự không mong muốn
                seatStatus.erase(remove_if(seatStatus.begin(), seatStatus.end(), ::isspace), seatStatus.end());

                if (++currentSeat == seatNumber) 
                {
                    if (seatStatus == "0") 
                    {
                        updatedLine += "1,"; // Đánh dấu ghế là "trống" bằng 1
                        seatUpdated = true;
                    }
                    else {
                        cerr << "Ghe nay da trong roi, khong can cap nhat." << endl;
                        updatedLine += seatStatus + ",";
                    }
                }
                else {
                    updatedLine += seatStatus + ",";
                }
            }

            // Xóa dấu phẩy cuối cùng
            if (!updatedLine.empty() && updatedLine.back() == ',') 
            {
                updatedLine.pop_back();
            }

            updatedLines.push_back(updatedLine);
        }
        else {
            updatedLines.push_back(line); // Dữ liệu không thay đổi
        }
    }

    inFile.close();

    if (!seatUpdated) 
    {
        cerr << "Khong tim thay ghe can cap nhat hoac ticketID khong khop trong file " << seatsFile << endl;
        return false;
    }

    // Ghi lại dữ liệu cập nhật vào file
    ofstream outFile(seatsFile);
    if (!outFile.is_open()) 
    {
        cerr << "Khong the ghi vao file " << seatsFile << endl;
        return false;
    }

    for (const auto& updatedLine : updatedLines) 
    {
        outFile << updatedLine << endl;
    }

    outFile.close();
    return true;
}
void Flight::displayCustomerList(const Flight& chuyenBay)  
{

    cout << "Danh sach khach hang cua chuyen bay " << chuyenBay.flightID << ":\n";
    
    if (chuyenBay.TicketList.empty()) 
    {
        setTextColor(11);
        cout << "Khong co khach hang nao trong chuyen bay nay.\n";
        setTextColor(7);
        return;
    }

    cout << left << setw(15) << "TicketID"
        << setw(15) << "CustomerID"
        << setw(20) << "CustomerName"
        << setw(10) << "SeatNumber" << endl;

    for (const auto& ticket : chuyenBay.TicketList)
    {
        cout << left << setw(15) << ticket.getTicketID()
            << setw(15) << ticket.getCustomerID()
            << setw(20) << ticket.getCustomerName()
            << setw(10) << ticket.getSeatNumber() << endl;
    }
}
static vector<int> parseSeats(const string& seatData) 
{
    vector<int> seats;
    stringstream ss(seatData);
    string seat;
    while (getline(ss, seat, ',')) 
    {
        seats.push_back(stoi(seat));
    }
    return seats;
}

// Hàm hiển thị vị trí ghế trống
void Flight::displayAvailableSeats(const string& flightID) 
{
    ifstream file("TextFiles/DanhSachGheTrong.txt");
    if (!file) {
        cerr << "Khong mo duoc file danhsachghetrong.txt" << endl;
        return;
    }

    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string id, seatData;

        // Tách flightID và danh sách ghế
        getline(ss, id, ' ');
        getline(ss, seatData);

        if (id == flightID) {
            vector<int> seats = parseSeats(seatData);

            cout << "Ghe trong cho chuyen bay " << flightID << ": ";
            for (size_t i = 0; i < seats.size(); ++i) 
            {
                if (seats[i] == 1) {
                    cout << i + 1 << " "; // Vị trí ghế trống (tính từ 1)
                }
            }
            cout << endl;
            return;
        }
    }
    setTextColor(12);
    cout << "Khong tim thay chuyen bay voi ID: " << flightID << endl;
    setTextColor(7);
}
void Flight::countFlightsByPlane(const vector<Flight>& flights, const string& planeID) 
{
    int count = 0;
    for (const auto& flight : flights) 
    {
        if (flight.getAirplaneID() == planeID) 
        {
            ++count;
        }
    }
    setTextColor(14);
    cout << "May bay " << planeID << " da thuc hien " << count << " chuyen bay.\n";
    setTextColor(7);
}

void Flight::processFlightDetails(const vector<Flight>& flights) 
{
    string flightID, airplaneID;

  
    setTextColor(11);
    cout << "Nhap flightID: ";
    setTextColor(7);
    cin >> flightID;

  
    setTextColor(11);
    cout << "Nhap airplaneID: ";
    setTextColor(7);
    cin >> airplaneID;

  
    for (const auto& flight : flights) 
    {
        if (flight.flightID == flightID && flight.getAirplaneID() == airplaneID) 
        {
            flight.displayCustomerList(flight);
            cout << "------------------\n";

         
            flight.displayAvailableSeats(flightID);
            cout << "------------------\n";

            
            flight.countFlightsByPlane(flights, airplaneID);
            cout << "------------------\n";
            return;
        }
    }
    setTextColor(12);
    cout << "Khong tim thay chuyen bay voi flightID: " << flightID
        << " va airplaneID: " << airplaneID << endl;
    setTextColor(7);
}