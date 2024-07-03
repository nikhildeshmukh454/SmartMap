#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <climits>
#include <string>
#include "DataSetUp.h"
using namespace std;



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
