#ifndef DATASETUP_H
#define DATASETUP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <queue>

using namespace std;

// Class to store each row of the CSV file
class Node {
public:
    int id;
    string name;
    string type;
};

class Edge {
public:
    Node start;
    Node end;
    string type;
    bool car = true;
    bool bike = true;
    bool walk = true;
    int distance = 0;

    Edge(Node s, Node e, string typeOfRoad, int Distance)
        : start(s), end(e), type(typeOfRoad), distance(Distance) {
        if (typeOfRoad == "Intersections") {
            car = false;
        }
    }
};

// Global variables
set<string> UniqueType;
unordered_map<string, int> CountOfPlace;
vector<Node> records;
const int l = 364;
vector<vector<Edge>> edges(l);
vector<vector<pair<int,int>>> adjList(l);

void DataExtract() {
    ifstream file("C:\\Users\\nikhil deshmukh\\Desktop\\SmartMap\\SmartMap.csv");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "Failed to read header line." << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Node record;

        if (!getline(ss, token, ',')) {
            continue;
        }
        record.id = stoi(token);

        if (!getline(ss, token, ',')) {
            continue;
        }
        record.name = token;

        if (!getline(ss, token, ',')) {
            continue;
        }
        record.type = token;
        UniqueType.insert(token);
        CountOfPlace[token]++;

        records.push_back(record);
    }

    file.close();
}

void addEdge() {
    ifstream file("C:\\Users\\nikhil deshmukh\\Desktop\\SmartMap\\SmartMapEdge.csv");
    if (!file.is_open()) {
        cerr << "Failed to open edge file." << endl;
        return;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "Failed to read edge header line." << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int startID, endID;
        string type;
        int distance;

        if (!getline(ss, token, ',')) {
            continue;
        }
        startID = stoi(token);

        if (!getline(ss, token, ',')) {
            continue;
        }
        endID = stoi(token);

        if (!getline(ss, token, ',')) {
            continue;
        }
        type = token;

        if (!getline(ss, token, ',')) {
            continue;
        }
        distance = stoi(token);

        Edge record1(records[startID], records[endID], type, distance);
        Edge record2(records[endID], records[startID], type, distance);
        edges[startID].push_back(record1);
        edges[endID].push_back(record2);
        adjList[startID].push_back({endID,distance});
        adjList[endID].push_back({startID,distance});
    }

    file.close();
}

void printALL_WAY() {
    for (auto i : UniqueType) {
        cout << i << "      ";
    }
    cout << endl;
}

void printAdjList() {
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << " :";
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j].first<< " "<<adjList[i][j].second << " ,";
        }
        cout << endl;
    }
}

#endif // DATASETUP_H
