#include "ChcekTheConnectivityOfPlace.cpp"
#include "DataSetUp.h"
#include "FindingMinmumDistance.cpp"
#include "MultiplePlace.cpp"
#include "PathByMode.cpp"
#include "TimeAsPerMode.cpp"
using namespace std;

int main()
{

    DataExtract();
    addEdge();
   int choice;
    cout << "WELCOME TO SMART_MAP...." << endl;

   
        // Display the menu
        cout << "Please select your need:\n";
        cout << "1. To know What Diffrnet Typeof service are in your area .\n";
        cout << "2. Plan the day with most time-saving and minimum distance path.\n";
        cout << "3. Find the nearest service from home {based on mode of transportation}.\n";
        cout << "4. Find the nearest service from home {considering travel time per mode}.\n";
        cout << "5. Estimate travel time to a place {based on mode of transportation}.\n";
        cout << "6. Determine the overall connectivity of my place.\n";
        cout << "7. Find the nearest service from home.\n";
        cout << "8. Exit.\n";
        cout << "Enter your choice (1-8): ";
        cin >> choice;

        // Call the corresponding function based on user input
        switch (choice)
        {
        case 1:
           printALL_WAY();
            break;
        case 2:
            Multipleinput();
            break;
        case 3:
            NearServiceFromHomeBYmode();
            break;
        case 4:
            NearServiceFromHomeB();
            break;
        case 5:
            PlaceTime();
            break;
        case 6:
            TellMeTheOverallConnectivityOfMyPlace();
            break;
        case 7:
            NearServiceFromHome();

        case 8:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

           cout << "\n";
    

    return 0;
   
}


