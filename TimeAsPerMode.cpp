#include "DataSetUp.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

// Define the velocities in meters per hour
const int WalkVelocity = 5120;
const int CarVelocity = 18000;
const int BikeVelocity = 24000;

// Function to find the nearest place of a given type from the start location using the specified mode of transportation
void timeFromA_ByMode(int start, const string &end, const string &mode) {
    // Determine the mode of transportation
    bool bikeMode = (mode == "bike");
    bool carMode = (mode == "car");
    bool walkMode = (mode == "walk");

    // Initialize visited vector and priority queue for Dijkstra's algorithm
    vector<bool> visited(edges.size(), false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    vector<int> dis(edges.size(), INT_MAX);
    dis[start] = 0;

    int result = -1;

    while (!pq.empty()) {
        auto p = pq.top();
        int place = p.second;
        pq.pop();

        if (visited[place])
            continue;

        visited[place] = true;

        // Check if the current place is the destination type
        if (records[place].type == end) {
            result = place;
            break;
        }

        // Explore neighboring nodes
        for (const auto &in : edges[place]) {
            int placeN = in.end.id;
            int dist = in.distance;
            bool B = in.bike, C = in.car, W = in.walk;

            // Update distance for bike mode
            if (bikeMode && B && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                pq.push({dis[placeN], placeN});
            }

            // Update distance for car mode
            if (carMode && C && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                pq.push({dis[placeN], placeN});
            }

            // Update distance for walk mode
            if (walkMode && W && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                pq.push({dis[placeN], placeN});
            }
        }
    }

    // Output results
    if (result == -1) {
        cout << "NO PATH FOUND FROM " << records[start].name << " TO " << end << " BY THE MODE OF " << mode << endl;
    } else {
        double time = 0;
        if (mode == "walk") {
            time = static_cast<double>(dis[result]) / WalkVelocity;
        } else if (mode == "car") {
            time = static_cast<double>(dis[result]) / CarVelocity;
        } else if (mode == "bike") {
            time = static_cast<double>(dis[result]) / BikeVelocity;
        }

        cout << "Nearest " << end << " from your location by the mode of " << mode << " is " << records[result].name 
             << " at a distance of " << dis[result] << " meters, which will take approximately " 
             << time*60 << " minutes." << endl;
    }
}


void timeFromid_ByMode(int start, const int  &end, const string &mode) {
    // Determine the mode of transportation
    bool bikeMode = (mode == "bike");
    bool carMode = (mode == "car");
    bool walkMode = (mode == "walk");

    // Initialize visited vector and priority queue for Dijkstra's algorithm
    vector<bool> visited(edges.size(), false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    vector<int> dis(edges.size(), INT_MAX);
    dis[start] = 0;

    int result = -1;

    while (!pq.empty()) {
        auto p = pq.top();
        int place = p.second;
        pq.pop();

        if (visited[place])
            continue;

        visited[place] = true;

        // Check if the current place is the destination type
        if (place == end) {
            result = place;
            break;
        }

        // Explore neighboring nodes
        for (const auto &in : edges[place]) {
            int placeN = in.end.id;
            int dist = in.distance;
            bool B = in.bike, C = in.car, W = in.walk;

            // Update distance for bike mode
            if (bikeMode && B && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                pq.push({dis[placeN], placeN});
            }

            // Update distance for car mode
            if (carMode && C && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                pq.push({dis[placeN], placeN});
            }

            // Update distance for walk mode
            if (walkMode && W && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                pq.push({dis[placeN], placeN});
            }
        }
    }

    // Output results
    if (result == -1) {
        cout << "NO PATH FOUND FROM " << records[start].name << " TO " << end << " BY THE MODE OF " << mode << endl;
    } else {
        double time = 0;
        if (mode == "walk") {
            time = static_cast<double>(dis[result]) / WalkVelocity;
        } else if (mode == "car") {
            time = static_cast<double>(dis[result]) / CarVelocity;
        } else if (mode == "bike") {
            time = static_cast<double>(dis[result]) / BikeVelocity;
        }

        cout << "Nearest " << records[end].name << " from your location by the mode of " << mode << " is " << records[result].name 
             << " at a distance of " << dis[result] << " meters, which will take approximately " 
             << time*60 << " minutes." << endl;
    }
}



// Function to find the nearest service from home based on user input
void NearServiceFromHomeB() {
    int HomeId;
    cout << "Enter the valid ID of your place: ";
    cin >> HomeId;

    // Validate home ID
    while (HomeId < 0 || HomeId >= 363) {
        cout << "The place you entered is not recognized. Please try again." << endl;
        cout << "Enter the valid ID of your place: ";
        cin >> HomeId;
    }

    string place;
    cout << "Enter the type of place you want to visit: ";
    cin >> place;

    // Validate place
    while (!UniqueType.count(place)) {
        cout << "The place you entered is not recognized. Please try again." << endl;
        cout << "Enter the place you want to visit: ";
        cin >> place;
    }

    timeFromA_ByMode(HomeId, place, "bike");
    timeFromA_ByMode(HomeId, place, "walk");
    timeFromA_ByMode(HomeId, place, "car");
}



void PlaceTime() {
    int HomeId;
    cout << "Enter the valid ID of your place: ";
    cin >> HomeId;

    // Validate home ID
    while (HomeId < 0 || HomeId >= 363) {
        cout << "The place you entered is not recognized. Please try again." << endl;
        cout << "Enter the valid ID of your place: ";
        cin >> HomeId;
    }
int endId;
     cout << "Enter the valid ID of  place you want to visit : ";
    cin >> endId;

    // Validate home ID
    while (endId < 0 || endId >= 363) {
        cout << "The id you entered is not recognized. Please try again." << endl;
        cout << "Enter the valid ID of your place: ";
        cin >> endId;
    }


    timeFromid_ByMode(HomeId, endId, "bike");
    timeFromid_ByMode(HomeId, endId, "walk");
    timeFromid_ByMode(HomeId, endId, "car");
}

