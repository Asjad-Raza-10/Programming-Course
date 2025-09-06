#include <iostream>
#include <string>
using namespace std;

// Node structure for Ride Requests
struct RideRequest {
    int requestID;
    string customerName;
    string pickup;
    string dropoff;
    float fare;
    RideRequest* next;
};

// Node structure for Active Rides
struct ActiveRide {
    int rideID;
    string customerName;
    string driverName;
    string pickup;
    string dropoff;
    float fare;
    ActiveRide* next;
};

// Node structure for Ride History
struct RideHistory {
    int rideID;
    string customerName;
    string driverName;
    string pickup;
    string dropoff;
    float fare;
    string status; // Completed or Canceled
    RideHistory* next;
};

class RideNowSystem {
private:
    RideRequest* requestHead;
    ActiveRide* activeHead;
    RideHistory* historyHead;

public:
    RideNowSystem() {
        requestHead = nullptr;
        activeHead = nullptr;
        historyHead = nullptr;
    }

    // ========== Ride Request Functions ==========
    void addRideRequest(int id, string cname, string pickup, string drop, float fare);
    void cancelRideRequest(int id);
    void displayRideRequests();

    // ========== Active Ride Functions ==========
    void assignRideToDriver(int id, string driverName);
    void displayActiveRides();

    // ========== Ride History Functions ==========
    void completeRide(int id, bool completed);
    void displayRideHistory();
    void searchRideByCustomer(string cname);
    void calculateTotalRevenue();

    // ========== Advanced Functionalities ==========
    void sortRideHistoryByFare();
    void reverseRideHistory();
    void detectAndMergeDuplicateRequests();
    void deleteOldRidesByDate(string date); // Extra challenge
    void findLongestRide();
};

int main() {
    RideNowSystem system;
    int choice;

    do {
        cout << "\n====== RideNow System Menu ======\n";
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

        switch(choice) {
            case 1: {
                int id; string cname, pickup, drop; float fare;
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
                int id; string dname;
                cout << "Enter Ride ID and Driver Name: ";
                cin >> id >> dname;
                system.assignRideToDriver(id, dname);
                break;
            }
            case 4: {
                int id; bool completed;
                cout << "Enter Ride ID and (1 for Completed, 0 for Canceled): ";
                cin >> id >> completed;
                system.completeRide(id, completed);
                break;
            }
            case 5: system.displayRideRequests(); break;
            case 6: system.displayActiveRides(); break;
            case 7: system.displayRideHistory(); break;
            case 8: {
                string cname;
                cout << "Enter Customer Name: ";
                cin >> cname;
                system.searchRideByCustomer(cname);
                break;
            }
            case 9: system.calculateTotalRevenue(); break;
            case 10: system.sortRideHistoryByFare(); break;
            case 11: system.reverseRideHistory(); break;
            case 12: system.detectAndMergeDuplicateRequests(); break;
            case 13: {
                string date;
                cout << "Enter Date (DD/MM/YYYY): ";
                cin >> date;
                system.deleteOldRidesByDate(date);
                break;
            }
            case 14: system.findLongestRide(); break;
            case 15: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 15);

    return 0;
