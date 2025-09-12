#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Functions for Input with validation checks

void getNumInput(int &num)
{
    while (!(cin >> num) || (num < 0)) // while extraction fails and number is negative
    {
        cout << "Invalid input. Please enter a positive integer: ";
        cin.clear();                                         // clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void getFloatInput(float &num)
{
    while (!(cin >> num) || (num < 0)) // while extraction fails and number is negative
    {
        cout << "Invalid input. Please enter a positive amount: ";
        cin.clear();                                         // clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void getName(string &name)
{
    bool valid = false;

    while (!valid)
    {
        getline(cin, name);

        // Check if name is empty or only contains spaces
        if (name.empty() || name.find_first_not_of(' ') == string::npos)
        {
            cout << "Invalid name! Name cannot be empty." << endl;
            cout << "Please input the name again: ";
            valid = false;
            continue;
        }

        valid = true;

        // learned about this form of for loop while learning python, not plagiarism
        for (char c : name)
        {
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' '))
            {
                cout << "Invalid name! Only alphabets and spaces are allowed." << endl;
                cout << "Please input the name again: ";
                valid = false;
                break;
            }
        }
    }
}

void getAddress(string &add)
{
    bool valid = false;

    while (!valid)
    {
        getline(cin, add);

        // Check if address is empty or only contains spaces
        if (add.empty() || add.find_first_not_of(' ') == string::npos)
        {
            cout << "Invalid address! Address cannot be empty." << endl;
            cout << "Please input the address again: ";
            valid = false;
            continue;
        }
        valid = true;
    }
}

class Date
{
  private:
    int date;
    int month;
    int year;
    int hours;
    int minutes;

  public:
    Date(int d = 0, int m = 0, int y = 0, int h = 0, int mnts = 0)
    {
        date = d;
        month = m;
        year = y;
        hours = h;
        minutes = mnts;
    }

    bool operator<(Date &other)
    {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        if (date != other.date)
            return date < other.date;
        if (hours != other.hours)
            return hours < other.hours;
        return minutes < other.minutes;
    }

    bool operator>(Date &other)
    {
        return (other < *this);
    }

    void display()
    {
        cout << "Date (DD-MM-YYYY): " << date << " - " << month << " - " << year << endl;
        cout << "Time: (HH:MM): " << hours << " : " << minutes << endl;
    }
};

// Helper functions for Date Validation

bool isValidYear(int year)
{
    if (year < 1 || year > 2025)
    {
        cout << "Invalid year. Please enter a year between 1 and 2025: ";
        return false;
    }
    return true;
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidMonth(int month)
{
    if (month < 1 || month > 12)
    {
        cout << "Invalid month. Please enter a month between 1 and 12: ";
        return false;
    }
    return true;
}

int getDaysInMonth(int month, int year)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year)) // February in a leap year
    {
        return 29;
    }
    return daysInMonth[month - 1]; // array is starting from 0 index
}

bool isValidDate(int date, int month, int year)
{
    int maxDays = getDaysInMonth(month, year);
    if (date < 1 || date > maxDays)
    {
        cout << "Invalid date. Please enter a date between 1 and " << maxDays << ": ";
        return false;
    }
    return true;
}

bool isValidHour(int hour)
{
    if (hour < 0 || hour > 23)
    {
        cout << "Invalid hour. Please enter an hour between 0 and 23: ";
        return false;
    }
    return true;
}

bool isValidMinute(int minute)
{
    if (minute < 0 || minute > 59)
    {
        cout << "Invalid minute. Please enter a minute between 0 and 59: ";
        return false;
    }
    return true;
}

void inputDate(int &year, int &month, int &date, int &hour, int &minute)
{
    cout << "Enter the Year: ";
    do
    {
        getNumInput(year);
    } while (!isValidYear(year));

    cout << "Enter the Month: ";
    do
    {
        getNumInput(month);
    } while (!isValidMonth(month));

    cout << "Enter the date: ";
    do
    {
        getNumInput(date);
    } while (!isValidDate(date, month, year));

    cout << "Enter the Time (Hours): ";
    do
    {
        getNumInput(hour);
    } while (!isValidHour(hour));

    cout << "Enter the Time (Minutes): ";
    do
    {
        getNumInput(minute);
    } while (!isValidMinute(minute));
}

// Node structure for Ride Requests
struct RideRequest
{
    int requestID;
    string customerName;
    string pickup;
    string dropoff;
    float fare;
    RideRequest *next;

    RideRequest(int id, string name, string p, string d, float f)
    {
        requestID = id;
        customerName = name;
        pickup = p;
        dropoff = d;
        fare = f;
        next = nullptr;
    }

    void display()
    {
        cout << "Request ID: \t" << requestID << endl;
        cout << "Customer Name: \t" << customerName << endl;
        cout << "Pickup: \t" << pickup << endl;
        cout << "Dropoff: \t" << dropoff << endl;
        cout << "Fare: \t" << fare << endl;
    }
};

// Node structure for Active Rides
struct ActiveRide
{
    int rideID;
    string customerName;
    string driverName;
    string pickup;
    string dropoff;
    float fare;
    ActiveRide *next;

    ActiveRide(int id, string cname, string dname, string p, string d, float f)
    {
        rideID = id;
        customerName = cname;
        driverName = dname;
        pickup = p;
        dropoff = d;
        fare = f;
        next = nullptr;
    }

    void display()
    {
        cout << "Ride ID: \t" << rideID << endl;
        cout << "Customer Name: \t" << customerName << endl;
        cout << "Driver Name: \t" << driverName << endl;
        cout << "Pickup: \t" << pickup << endl;
        cout << "Dropoff: \t" << dropoff << endl;
        cout << "Fare: \t" << fare << endl;
    }
};

// Node structure for Ride History
struct RideHistory
{
    int rideID;
    string customerName;
    string driverName;
    string pickup;
    string dropoff;
    float fare;
    string status; // Completed or Canceled
    Date date;
    RideHistory *next;

    RideHistory(int id, string cname, string dname, string p, string drp, float f, string s, int d, int m, int y, int h,
                int mnts)
        : date(d, m, y, h, mnts)
    {
        rideID = id;
        customerName = cname;
        driverName = dname;
        pickup = p;
        dropoff = drp;
        fare = f;
        status = s;
        next = nullptr;
    }

    void display()
    {
        cout << "Ride ID: \t" << rideID << endl;
        cout << "Customer Name: \t" << customerName << endl;
        cout << "Driver Name: \t" << driverName << endl;
        cout << "Pickup: \t" << pickup << endl;
        cout << "Dropoff: \t" << dropoff << endl;
        cout << "Fare: \t" << fare << endl;
        cout << "Status: \t" << status << endl;
        date.display();
    }
};

class RideNowSystem
{
  private:
    RideRequest *requestHead, *requestTail;
    ActiveRide *activeHead, *activeTail;
    RideHistory *historyHead, *historyTail;

  public:
    RideNowSystem()
    {
        requestHead = requestTail = nullptr;
        activeHead = activeTail = nullptr;
        historyHead = historyTail = nullptr;
    }

    // ========== Ride Request Functions ==========
    void addRideRequest(int id, string cname, string pickup, string drop, float fare)
    {
        if (requestIdExists(id))
        {
            cout << "The entered ID already exists. Please enter another ID" << endl;
            return;
        }

        RideRequest *temp = new RideRequest(id, cname, pickup, drop, fare);

        // If List is Empty
        if (!requestHead)
        {
            requestHead = requestTail = temp;
            return;
        }

        requestTail->next = temp;
        requestTail = temp;
    }

    void displayRideRequests()
    {
        cout << endl << "======= Ride Requests: =======" << endl;

        RideRequest *temp = requestHead;

        if (!temp)
        {
            cout << "\nNO RIDE REQUESTS\n";
        }

        int i = 1;

        while (temp)
        {
            cout << endl << " --- Ride Number " << i++ << " ---" << endl;
            temp->display();
            temp = temp->next;
        }

        cout << endl << "===================================" << endl;
    }

    // ========== Active Ride Functions ==========
    void assignRideToDriver(int id, string driverName)
    {
        if (!requestIdExists(id))
        {
            cout << "The entered ID does not exist in the requests list. Try Again!" << endl;
            return;
        }

        RideRequest *temp = requestHead;
        RideRequest *prev = requestHead;

        int i = 0;
        bool found = false;

        while (temp)
        {
            if (temp->requestID == id)
            {
                ActiveRide *activeRideToAdd =
                    new ActiveRide(id, temp->customerName, driverName, temp->pickup, temp->dropoff, temp->fare);

                if (i)
                {
                    if (!activeHead)
                    {
                        activeHead = activeTail = activeRideToAdd;
                    }
                    else
                    {
                        activeTail->next = activeRideToAdd;
                        activeTail = activeRideToAdd;
                    }

                    requestHead = temp->next;
                    delete temp;
                }
                else
                {
                    if (!activeHead)
                    {
                        activeHead = activeTail = activeRideToAdd;
                    }
                    else
                    {
                        activeTail->next = activeRideToAdd;
                        activeTail = activeRideToAdd;
                    }

                    prev->next = temp->next;
                    delete temp;
                }

                break;
            }

            temp = temp->next;

            if (i++)
            {
                prev = prev->next;
            }
        }

        if (!prev->next)
        {
            requestTail = prev;
        }

        if (!found)
        {
            cout << endl << "The entered ID was not found. No changes made!";
        }
    }

    void displayActiveRides()
    {
        cout << endl << "======= Active Rides: =======" << endl;

        ActiveRide *temp = activeHead;

        if (!temp)
        {
            cout << "\nNO ACTIVE REQUESTS\n";
        }

        int i = 1;

        while (temp)
        {
            cout << endl << " --- Ride Number " << i++ << " ---" << endl;
            temp->display();
            temp = temp->next;
        }

        cout << endl << "=====================" << endl;
    }

    // ========== Ride History Functions ==========

    bool requestIdExists(int id)
    {
        RideRequest *temp = requestHead;

        if (!temp)
        {
            return false;
        }

        while (temp)
        {
            if (temp->requestID == id)
            {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    bool activeIdExists(int id)
    {
        ActiveRide *temp = activeHead;

        if (!temp)
        {
            return false;
        }

        while (temp)
        {
            if (temp->rideID == id)
            {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    void completeRide(int id, bool completed)
    {

        if (completed)
        {
            if (!activeIdExists(id))
            {
                cout << "The entered ID does not exist in the active rides list. Try Again!" << endl;
                return;
            }

            ActiveRide *temp = activeHead;
            ActiveRide *prev = activeHead;

            // copying the contents of active ride before deleting it, to store it in ride history
            string cname = "";
            string dname = "";
            string pickup = "";
            string dropoff = "";
            float fare = 0;

            int i = 0;

            while (temp)
            {
                if (temp->rideID == id)
                {
                    // copying the contents of active ride before deleting it, to store it in ride history
                    cname = temp->customerName;
                    dname = temp->driverName;
                    pickup = temp->pickup;
                    dropoff = temp->dropoff;
                    fare = temp->fare;

                    if (i)
                    {
                        prev->next = temp->next;
                        delete temp;
                    }
                    else
                    {
                        activeHead = temp->next;
                        delete temp;
                    }

                    break;
                }

                temp = temp->next;

                if (i++)
                {
                    prev = prev->next;
                }
            }

            if (!prev->next)
            {
                activeTail = prev;
            }

            cout << "Enter the date and time when the ride is completed." << endl;
            int y, m, d, h, mn;
            inputDate(y, m, d, h, mn);

            RideHistory *temp_2 = new RideHistory(id, cname, dname, pickup, dropoff, fare, "Completed", d, m, y, h, mn);
            if (!historyHead)
            {
                historyHead = historyTail = temp_2;
                return;
            }

            historyTail->next = temp_2;
            historyTail = temp_2;
        }
        else
        {
            if (!requestIdExists(id))
            {
                cout << "The entered ID does not exist in the requests list. Try Again!" << endl;
                return;
            }

            RideRequest *temp = requestHead;
            RideRequest *prev = requestHead;

            // copying the contents of ride request before deleting it, to store it in ride history
            string cname = "";
            string pickup = "";
            string dropoff = "";
            float fare = 0;

            int i = 0;

            while (temp)
            {
                if (temp->requestID == id)
                {
                    // copying the contents of ride request before deleting it, to store it in ride history
                    cname = temp->customerName;
                    pickup = temp->pickup;
                    dropoff = temp->dropoff;
                    fare = temp->fare;

                    if (i)
                    {
                        prev->next = temp->next;
                        delete temp;
                    }
                    else
                    {
                        requestHead = temp->next;
                        delete temp;
                    }

                    break;
                }

                temp = temp->next;

                if (i++)
                {
                    prev = prev->next;
                }
            }

            if (!prev->next)
            {
                requestTail = prev;
            }

            cout << "Enter the date and time when the ride is cancelled." << endl;
            int y, m, d, h, mn;
            inputDate(y, m, d, h, mn);
            string dname = "None"; // as cancelled ride will not have any driver

            RideHistory *temp_2 = new RideHistory(id, cname, dname, pickup, dropoff, fare, "Cancelled", d, m, y, h, mn);
            if (!historyHead)
            {
                historyHead = historyTail = temp_2;
                return;
            }

            historyTail->next = temp_2;
            historyTail = temp_2;
        }
    }

    void displayRideHistory()
    {
        cout << endl << "======= Ride History: =======" << endl;

        RideHistory *temp = historyHead;

        if (!temp)
        {
            cout << "\nNO RIDES HISTORY\n";
        }

        int i = 1;

        while (temp)
        {
            cout << endl << " --- Ride Number " << i++ << " ---" << endl;
            temp->display();
            temp = temp->next;
        }

        cout << endl << "=====================" << endl;
    }

    void searchRideByCustomer(string cname)
    {
        cout << endl << "======= Rides taken by " << cname << ": =======" << endl;

        RideHistory *temp = historyHead;

        if (!temp)
        {
            cout << "\nRIDE HISTORY IS EMPTY\n";
        }

        int i = 1;

        while (temp)
        {
            if (temp->customerName == cname)
            {
                cout << endl << " --- Ride Number " << i++ << " ---" << endl;
                temp->display();
            }
            temp = temp->next;
        }

        if (!i)
        {
            cout << "\nNO RIDES TAKEN BY THIS CUSTOMER\n";
        }

        cout << endl << "=====================" << endl;
    }

    void calculateTotalRevenue()
    {
        cout << endl << "======= Total Revenue: =======" << endl;

        RideHistory *temp = historyHead;

        if (!temp)
        {
            cout << "\nNO REVENUE AS NO RIDES COMPLETED\n";
        }

        int sum = 0;

        while (temp)
        {
            // cancelled rides arent counted in revenue
            if (temp->status == "Completed")
            {
                sum += temp->fare;
            }
            temp = temp->next;
        }

        cout << endl << "Total: " << sum << endl;
        cout << endl << "=====================" << endl;
    }

    // ========== Advanced Functionalities ==========
    void sortRideHistoryByFare()
    {
        if (!historyHead || !historyHead->next)
        {
            return; // Empty list or single ride
        }

        bool swapped = 0;
        RideHistory *current = historyHead;
        RideHistory *last = nullptr;

        do
        {
            swapped = 0;
            RideHistory *prev = nullptr;
            current = historyHead;

            while (current->next != last)
            {
                if (current->fare < current->next->fare)
                {
                    // Swap the nodes
                    RideHistory *next = current->next;

                    if (!prev)
                    {
                        historyHead = next;
                    }
                    else
                    {
                        prev->next = next;
                    }

                    current->next = next->next;
                    next->next = current;

                    prev = next;
                    swapped = 1;
                }
                else
                {
                    prev = current;
                    current = current->next;
                }
            }
            last = current;
        } while (swapped);

        // Update tail pointer
        historyTail = last;

        cout << endl << "Ride History is sorted. Display Ride History to check the results." << endl;
    }

    void reversePrintHistory(RideHistory *temp, int i)
    {
        if (!temp)
        {
            return;
        }
        reversePrintHistory(temp->next, ++i);
        cout << endl << " --- Ride Number " << i << " ---" << endl;
        temp->display();
    }

    void reverseRideHistory()
    {
        cout << endl << "======= Ride History (Recent First): =======" << endl;

        RideHistory *temp = historyHead;

        if (!temp)
        {
            cout << "\nNO RIDES HISTORY\n";
        }

        int i = 0;

        reversePrintHistory(temp, i);

        cout << endl << "=====================" << endl;
    }

    void detectAndMergeDuplicateRequests()
    {
        if (!requestHead || !requestHead->next)
        {
            return;
        }

        RideRequest *main = requestHead;

        while (main)
        {
            RideRequest *move = main;

            while (move->next)
            {
                if ((main->customerName == move->next->customerName) && (main->pickup == move->next->pickup) &&
                    (main->dropoff == move->next->dropoff))
                {
                    RideRequest *nodeToDelete = move->next;
                    move->next = nodeToDelete->next;
                    delete nodeToDelete;
                }
                else
                {
                    move = move->next;
                }
            }
            main = main->next;
        }

        RideRequest *temp = requestHead;
        while (temp && temp->next)
        {
            temp = temp->next;
        }
        requestTail = temp;

        cout << endl << "Duplicate Rides deleted. Display Ride History to check the results." << endl;
    }

    void deleteOldRidesByDate(Date date)
    {
        RideHistory *temp = historyHead;
        RideHistory *prev = historyHead;

        while (temp)
        {
            if (temp->date < date)
            {
                if (temp != historyHead)
                {
                    prev->next = temp->next;
                    delete temp;
                }
                else
                {
                    historyHead = temp->next;
                    delete temp;
                }

                break;
            }

            prev = temp;
            temp = temp->next;
        }

        if (!prev->next)
        {
            historyTail = prev;
        }

        cout << endl << "Old Rides deleted. Display Ride History to check the results." << endl;
    }

    void findLongestRide()
    {
        RideHistory *temp = historyHead;
        int longest_length = 0;
        RideHistory *longest = nullptr;

        cout << endl << "======= Longest Ride =======" << endl;

        if (!temp)
        {
            cout << "\nRIDE HISTORY IS EMPTY\n";
            return;
        }

        bool found = 0;

        while (temp)
        {
            if (temp->status == "Completed")
            {
                found = 1;

                if ((temp->pickup.length() + temp->dropoff.length()) > longest_length)
                {
                    longest_length = temp->pickup.length() + temp->dropoff.length();
                    longest = temp;
                }
            }
            temp = temp->next;
        }

        if (found)
        {
            longest->next = nullptr;
            longest->display();
        }
        else
        {
            cout << endl << "NO COMPLETED RIDE IN THE HISTORY" << endl;
        }
        cout << endl << "=====================" << endl;
    }

    ~RideNowSystem()
    {
        while (requestHead)
        {
            RideRequest *temp = requestHead;
            requestHead = requestHead->next;
            delete temp;
        }

        while (activeHead)
        {
            ActiveRide *temp = activeHead;
            activeHead = activeHead->next;
            delete temp;
        }

        while (historyHead)
        {
            RideHistory *temp = historyHead;
            historyHead = historyHead->next;
            delete temp;
        }
    }
};

int main()
{
    RideNowSystem system;
    int choice;

    do
    {
        cout << "\n\t\t\t======= RideNow System Menu =======\n\n";
        cout << "1. Add Ride Request\n";
        cout << "2. Cancel Ride Request\n";
        cout << "3. Assign Ride to Driver\n";
        cout << "4. Complete Ride\n";
        cout << "5. Display Current Ride Requests\n";
        cout << "6. Display Active Rides\n";
        cout << "7. Display Ride History\n";
        cout << "8. Search Rides by Customer\n";
        cout << "9. Calculate Total Revenue\n";
        cout << "10. Sort Ride History by Fare\n";
        cout << "11. Reverse Ride History\n";
        cout << "12. Detect & Merge Duplicate Ride Requests\n";
        cout << "13. Delete Old Rides by Date\n";
        cout << "14. Find Longest Ride\n";
        cout << "15. Exit\n\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: {
            int id;
            string cname, pickup, drop;
            float fare;
            cout << "Enter Request ID: ";
            getNumInput(id);
            cout << "Enter the Customer's Name: ";
            getName(cname);
            cout << "Enter the Pickup Address: ";
            getAddress(pickup);
            cout << "Enter the Dropoff Address: ";
            getAddress(drop);
            cout << "Enter the Fare: ";
            getFloatInput(fare);
            system.addRideRequest(id, cname, pickup, drop, fare);
            break;
        }
        case 2: {
            int id;
            cout << "Enter Ride ID to cancel: ";
            getNumInput(id);
            system.completeRide(id, 0);
            break;
        }
        case 3: {
            int id;
            string dname;
            cout << "Enter Request ID: ";
            getNumInput(id);
            cout << "Enter the Driver's Name: ";
            getName(dname);
            system.assignRideToDriver(id, dname);
            break;
        }
        case 4: {
            int id;
            cout << "Enter Ride ID to complete: ";
            getNumInput(id);
            system.completeRide(id, 1);
            break;
        }
        case 5:
            system.displayRideRequests();
            break;
        case 6:
            system.displayActiveRides();
            break;
        case 7:
            system.displayRideHistory();
            break;
        case 8: {
            string cname;
            cout << "Enter Customer Name: ";
            getName(cname);
            system.searchRideByCustomer(cname);
            break;
        }
        case 9:
            system.calculateTotalRevenue();
            break;
        case 10:
            system.sortRideHistoryByFare();
            break;
        case 11:
            system.reverseRideHistory();
            break;
        case 12:
            system.detectAndMergeDuplicateRequests();
            break;
        case 13: {
            cout << "Input the Date and Time: " << endl;
            int y, m, d, h, mnt;
            inputDate(y, m, d, h, mnt);
            Date date(d, m, y, h, mnt);
            system.deleteOldRidesByDate(date);
            break;
        }
        case 14:
            system.findLongestRide();
            break;
        case 15:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid input. Please enter an integer: " << endl << endl;
            cin.clear();                                         // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        }
        cout << "\n\n";
    } while (choice != 15);

    return 0;
}