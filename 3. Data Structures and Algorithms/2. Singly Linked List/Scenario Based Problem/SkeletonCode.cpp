#include <iostream>
#include <string>
using namespace std;

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
    RideHistory *next;

    RideHistory(int id, string cname, string dname, string p, string d, float f, string s)
    {
        rideID = id;
        customerName = cname;
        driverName = dname;
        pickup = p;
        dropoff = d;
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

    void cancelRideRequest(int id)
    {
        RideRequest *temp = requestHead;
        RideRequest *prev = requestHead;

        int i = 0;

        while (temp)
        {
            if (temp->requestID == id)
            {
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

        completeRide(id, 0); // saving it in rides history as 0 = cancelled
    }

    void displayRideRequests()
    {
        cout << endl << "======= Ride Requests: =======" << endl;

        RideRequest *temp = requestHead;

        int i = 1;

        while (temp)
        {
            cout << endl << " --- Ride Number " << i++ << " ---" << endl;
            temp->display();
            temp = temp->next;
        }

        cout << endl << "=====================" << endl;
    }

    // ========== Active Ride Functions ==========
    void assignRideToDriver(int id, string driverName)
    {
        RideRequest *temp = requestHead;
        RideRequest *prev = requestHead;

        int i = 0;

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

                    prev->next = temp->next;
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
    }

    void displayActiveRides()
    {
        cout << endl << "======= Active Rides: =======" << endl;

        ActiveRide *temp = activeHead;

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
    void completeRide(int id, bool completed);
    void displayRideHistory()
    {
        cout << endl << "======= Ride History: =======" << endl;

        RideHistory *temp = historyHead;

        int i = 1;

        while (temp)
        {
            cout << endl << " --- Ride Number " << i++ << " ---" << endl;
            temp->display();
            temp = temp->next;
        }

        cout << endl << "=====================" << endl;
    }
    void searchRideByCustomer(string cname);
    void calculateTotalRevenue();

    // ========== Advanced Functionalities ==========
    void sortRideHistoryByFare();
    void reverseRideHistory();
    void detectAndMergeDuplicateRequests();
    void deleteOldRidesByDate(string date); // Extra challenge
    void findLongestRide();
};

int main()
{
    RideNowSystem system;
    int choice;

    do
    {
        cout << "\n======= RideNow System Menu =======\n";
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
        cout << "15. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: {
            int id;
            string cname, pickup, drop;
            float fare;
            cout << "Enter ID, Customer Name, Pickup, Drop, Fare: ";
            cin >> id >> cname >> pickup >> drop >> fare;
            system.addRideRequest(id, cname, pickup, drop, fare);
            break;
        }
        case 2: {
            int id;
            cout << "Enter Ride ID to cancel: ";
            cin >> id;
            system.cancelRideRequest(id);
            break;
        }
        case 3: {
            int id;
            string dname;
            cout << "Enter Ride ID and Driver Name: ";
            cin >> id >> dname;
            system.assignRideToDriver(id, dname);
            break;
        }
        case 4: {
            int id;
            bool completed;
            cout << "Enter Ride ID and (1 for Completed, 0 for Canceled): ";
            cin >> id >> completed;
            system.completeRide(id, completed);
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
            cin >> cname;
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
            string date;
            cout << "Enter Date (DD/MM/YYYY): ";
            cin >> date;
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
            cout << "Invalid choice!\n";
        }
    } while (choice != 15);

    return 0;
}