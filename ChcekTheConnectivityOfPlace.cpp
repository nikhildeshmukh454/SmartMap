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
