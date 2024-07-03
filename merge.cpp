#include "DataSetUp.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <climits>
#include <iomanip>
void pathFromHomeToPlace(int start, const string &end)
{
    vector<bool> visited(edges.size(), false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    vector<int> dis(edges.size(), INT_MAX);
    dis[start] = 0;

    int result = -1;
    while (!pq.empty())
    {
        auto p = pq.top();
        int place = p.second;
        int l = p.first;
        pq.pop();

        if (visited[place])
            continue;

        visited[place] = true;

        if (records[place].type == end)
        {
            result = place;
            break;
        }

        for (const auto &in : edges[place])
        {
            int placeN = in.end.id;
            int dist = in.distance;

            if (dis[placeN] > dis[place] + dist)
            {
                dis[placeN] = dis[place] + dist;
                pq.push({dis[placeN], placeN});
            }
        }
    }

    if (result == -1)
    {
        cout << "NO PATH FOUND FROM " << records[start].name << " TO " << end << endl;
    }
    else
    {
        // cout  << records[result].name << " At a distance of " << dis[result] <<"meters"<<endl;
        cout << setw(20) << left << end
             << setw(20) << left << dis[result]
             << endl;
    }
}

void pathFromHomeToAllService(int HomeId)
{
    cout << endl
         << "Nearest  Services from Your Location Are  " << endl;

    cout << setw(20) << left << "Name"
         << setw(20) << left << "Distance (meters)"
         << endl;

    for (auto TYPEOFPLCAE : UniqueType)
    {
        pathFromHomeToPlace(HomeId, TYPEOFPLCAE);
    }
}




void TellMeTheOverallConnectivityOfMyPlace()
{
    int HomeId;
    cout << "Enter the Valid id of your  Place : ";
    cin >> HomeId;

    do
    {
        if (HomeId >= 0 && HomeId < 363)
        {
            break;
        }
        else
        {
            cout << "The place you entered is not recognized. Please try again." << endl;
            cout << "Enter the Valid id of your  Place : ";
            cin >> HomeId;
        }
    } while (true);

    pathFromHomeToAllService(HomeId);
}



void pathFromA_B(int start, const string &end)
{
    vector<bool> visited(edges.size(), false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    unordered_map<int, int> parent;
    vector<int> dis(edges.size(), INT_MAX);
    dis[start] = 0;

    int result = -1;
    while (!pq.empty())
    {
        auto p = pq.top();
        int place = p.second;
        int l = p.first;
        pq.pop();

        if (visited[place])
            continue;

        visited[place] = true;

        if (records[place].type == end)
        {
            result = place;
            break;
        }

        for (const auto &in : edges[place])
        {
            int placeN = in.end.id;
            int dist = in.distance;

            if (dis[placeN] > dis[place] + dist)
            {
                dis[placeN] = dis[place] + dist;
                parent[placeN] = place;
                pq.push({dis[placeN], placeN});
            }
        }
    }

    if (result == -1)
    {
        cout << "NO PATH FOUND FROM " << records[start].name << " TO " << end << endl;
    }
    else
    {
        vector<string> cont;
        int ans = result;
        while (result != start)
        {
            cont.push_back(records[result].name);
            result = parent[result];
        }
        cont.push_back(records[start].name);

        cout << "Nearest " << end << " from Your Location is " << records[ans].name << " At a distance of " << dis[ans] << "m .  and the path to this is:" << endl;

        for (int i = cont.size() - 1; i >= 0; i--)
        {
            cout << cont[i];
            if (i > 0)
                cout << " -> ";
        }
        cout << endl;
    }
}

void NearServiceFromHome()
{
    int HomeId;
    cout << "Enter the Valid id of your  Place : ";
    cin >> HomeId;

    do
    {
        if (HomeId >= 0 && HomeId < 363)
        {
            break;
        }
        else
        {
            cout << "The place you entered is not recognized. Please try again." << endl;
            cout << "Enter the Valid id of your  Place : ";
            cin >> HomeId;
        }
    } while (true);

    string place;
    cout << "Enter the place you want to visit: ";
    cin >> place;

    do
    {
        if (UniqueType.count(place))
        {
            break;
        }
        else
        {
            cout << "The place you entered is not recognized. Please try again." << endl;
            cout << "Enter the place you want to visit: ";
            cin >> place;
        }
    } while (true);

    pathFromA_B(HomeId, place);
}



void dijkstra(int startNode, const set<int> &toVisit, unordered_map<int, unordered_map<int, int>> &mp) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distances(adjList.size(), INT_MAX);
    distances[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDistance > distances[currentNode]) continue;

        if (toVisit.count(currentNode)) {
            mp[startNode][currentNode] = currentDistance;
        }

        for (const auto &neighbor : adjList[currentNode]) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;
            int newDistance = currentDistance + weight;

            if (newDistance < distances[nextNode]) {
                distances[nextNode] = newDistance;
                pq.push({newDistance, nextNode});
            }
        }
    }
}

void check(int node, unordered_map<int, bool> &visited, vector<int> &temp, const set<int> &toVisit,
           unordered_map<int, unordered_map<int, int>> &mp, vector<int> &ans, int d, int &D, int c, const vector<int> &FinalSeq) {
    temp.push_back(node);
    if (temp.size() == c) {
        if (d < D) {
            D = d;
            ans = temp;
        }
    } else {
        for (int i : FinalSeq) {
            if (!visited[i] && toVisit.count(i) && mp[node][i] < INT_MAX) {
                visited[i] = true;
                check(i, visited, temp, toVisit, mp, ans, d + mp[node][i], D, c, FinalSeq);
                visited[i] = false;
            }
        }
    }
    temp.pop_back();
}

void MinDist(set<int> &toVisit, int s) {
    unordered_map<int, unordered_map<int, int>> mp;
    unordered_map<int, bool> v;
    vector<int> FinalSeq(toVisit.begin(), toVisit.end());

    for (int i : FinalSeq) {
        v[i] = false;
        for (int j : FinalSeq) {
            mp[i][j] = INT_MAX;
            if (i == j) mp[i][j] = 0;
        }
    }

    for (int startNode : FinalSeq) {
        dijkstra(startNode, toVisit, mp);
    }

    vector<int> temp;
    vector<int> ans;
    int d = 0;
    int D = INT_MAX;
    int c = toVisit.size();
    v[s] = true;


    check(s, v, temp, toVisit, mp, ans, d, D, c, FinalSeq);

    if (D == INT_MAX) {
        cout << "No path found connecting any of these places." << endl;
    } else {
        cout << "From our analysis, if you visit the provided places in this order, you will require a minimum distance of " << D << " meters" << endl;
        for (int i : ans) {
            cout << records[i].name << "->";
        }
        cout << "End" << endl;
    }
}

void Multipleinput()
{
    set<int> temp;
    int startID, endID;

    cout << "Tell me your home ID: ";
    cin >> startID;
    temp.insert(startID);

    while (true)
    {
        int input;
        cout << "Tell me the ID of next place you want to visit, or enter '-1' to stop: ";
        cin >> input;
        if (input == -1)
        {
            cout << "Wait ......." << endl;
            break;
        }

        int place = input;
        if (place >= 0 && place < 365)
        {
            temp.insert(place);
        }
        else
        {
            cout << "The place you entered is not recognized. Please try again." << endl;
        }
    }

    if (temp.empty())
    {
        cout << "No places to visit provided." << endl;
        return;
    }

    vector<int> Temp;
    vector<int> BestWay;
    vector<bool> v(365, false);
    int C = temp.size();
    int minDis = INT_MAX;

    MinDist(temp, startID);
}


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









