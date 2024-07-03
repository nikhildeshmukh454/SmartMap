#include "DataSetUp.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

// Function to find the nearest place of a given type from the start location using the specified mode of transportation
void pathFromA_ByMode(int start, const string &end, const string &mode) {
    // Determine the mode of transportation
    bool bikeMode = (mode == "bike");
    bool carMode = (mode == "car");
    bool walkMode = (mode == "walk");

    // Initialize visited vector and priority queue for Dijkstra's algorithm
    vector<bool> visited(edges.size(), false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    // Initialize parent map and distance vector
    unordered_map<int, int> parent;
    vector<int> dis(edges.size(), INT_MAX);
    dis[start] = 0;

    int result = -1;

    while (!pq.empty()) {
        auto p = pq.top();
        int place = p.second;
        int l = p.first;
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
                parent[placeN] = place;
                pq.push({dis[placeN], placeN});
            }

            // Update distance for car mode
            if (carMode && C && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                parent[placeN] = place;
                pq.push({dis[placeN], placeN});
            }

            // Update distance for walk mode
            if (walkMode && W && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                parent[placeN] = place;
                pq.push({dis[placeN], placeN});
            }
        }
    }

    // Output results
    if (result == -1) {
        cout << "NO PATH FOUND FROM " << records[start].name << " TO " << end << " BY THE MODE OF " << mode << endl;
    } else {
        vector<string> path;
        int current = result;
        while (current != start) {
            path.push_back(records[current].name);
            current = parent[current];
        }
        path.push_back(records[start].name);

        cout << "Nearest " << end << " from your location by the mode of " << mode << " is " << records[result].name 
             << " at a distance of " << dis[result] << "m. The path is:" << endl;

        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }
}

// Function to find the nearest service from home based on user input
void NearServiceFromHomeBYmode() {
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

    cout << "Enter the Type of  place you want to visit   ";
    
    cout<<endl;
    cin >> place;

    // Validate place

    while (!UniqueType.count(place)) {
        cout << "The place you entered is not recognized. Please try again." << endl;
        cout << "Enter the place you want to visit: ";
        cin >> place;
    }

    string mode;
    cout << "Tell me the mode you want to travel (bike, car, walk): ";
    cin >> mode;

    // Validate mode
    while (mode != "bike" && mode != "car" && mode != "walk") {
        cout << "The mode you entered is not recognized. Please try again." << endl;
        cout << "Tell me the mode you want to travel (bike, car, walk): ";
        cin >> mode;
    }

    pathFromA_ByMode(HomeId, place, mode);
}
