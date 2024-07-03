#include "DataSetUp.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <climits>

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
