//CampusGraph.cpp
//Purpose: undirected campus graph (adjacency list) and BFS.
//Author: Member B

#include "CampusGraph.h"
#include "Utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

CampusGraph::CampusGraph() : edges(0) {}

//load vertices
void CampusGraph::loadBuildings(const string& path) {
    ifstream in(path.c_str());
    if (!in) {
        printOpenError(path);
        printLoadSummary(path, 0, 0);
        return;
    }

    string line;
    int lineNum = 0, accepted = 0, rejected = 0;
    while (getline(in, line)) {
        ++lineNum;
        if (isSkippable(line)) continue;

        vector<string> f = splitFields(line);
        if (f.size() != 1) {
            printWarning(path, lineNum, "expected 1 field, found " + to_string(f.size()));
            ++rejected;
            continue;
        }
        if (f[0].empty()) {
            printWarning(path, lineNum, "empty building name");
            ++rejected;
            continue;
        }
        if (findBuilding(f[0]) != -1) {
            printWarning(path, lineNum, "duplicate building \"" + f[0] + "\"");
            ++rejected;
            continue;
        }

        names.push_back(f[0]);
        adj.push_back(vector<int>());
        ++accepted;
    }
    printLoadSummary(path, accepted, rejected);
}

//load edges
void CampusGraph::loadConnections(const string& path) {
    ifstream in(path.c_str());
    if (!in) {
        printOpenError(path);
        printLoadSummary(path, 0, 0);
        return;
    }

    string line;
    int lineNum = 0, accepted = 0, rejected = 0;
    while (getline(in, line)) {
        ++lineNum;
        if (isSkippable(line)) continue;

        vector<string> f = splitFields(line);
        if (f.size() != 2) {
            printWarning(path, lineNum, "expected 2 fields, found " + to_string(f.size()));
            ++rejected;
            continue;
        }
        if (f[0].empty() || f[1].empty()) {
            printWarning(path, lineNum, "empty building name");
            ++rejected;
            continue;
        }

        int a = findBuilding(f[0]);
        int b = findBuilding(f[1]);
        if (a == -1 || b == -1) {
            printWarning(path, lineNum, "unknown building \"" + (a == -1 ? f[0] : f[1]) + "\"");
            ++rejected;
            continue;
        }
        if (a == b) {
            printWarning(path, lineNum, "self-connection \"" + names[a] + "\"");
            ++rejected;
            continue;
        }
        if (hasEdge(a, b)) {
            printWarning(path, lineNum,
                         "duplicate connection \"" + names[a] + "|" + names[b] + "\"");
            ++rejected;
            continue;
        }

        adj[a].push_back(b);
        adj[b].push_back(a);
        ++edges;
        ++accepted;
    }
    printLoadSummary(path, accepted, rejected);
}

//linear scan, case-insensitive
int CampusGraph::findBuilding(const string& name) const {
    string key = trim(name);
    for (size_t i = 0; i < names.size(); ++i)
        if (equalsIgnoreCase(names[i], key)) return static_cast<int>(i);
    return -1;
}

const string& CampusGraph::getName(int index) const { return names[index]; }

int CampusGraph::buildingCount() const { return static_cast<int>(names.size()); }

int CampusGraph::connectionCount() const { return edges; }

int CampusGraph::degree(int index) const { return static_cast<int>(adj[index].size()); }

//symmetric, so one side covers reversed duplicates
bool CampusGraph::hasEdge(int a, int b) const {
    for (size_t i = 0; i < adj[a].size(); ++i)
        if (adj[a][i] == b) return true;
    return false;
}

//print each building + neighbors
void CampusGraph::displayGraph() const {
    if (names.empty()) {
        cout << "No buildings are loaded.\n";
        return;
    }
    cout << "Campus graph (" << names.size() << " buildings):\n";
    for (size_t i = 0; i < names.size(); ++i) {
        cout << names[i] << ": ";
        if (adj[i].empty()) {
            cout << "(no connections)";
        } else {
            for (size_t j = 0; j < adj[i].size(); ++j) {
                if (j > 0) cout << ", ";
                cout << names[adj[i][j]];
            }
        }
        cout << "\n";
    }
}

//print degree table and totals
void CampusGraph::displayCounts() const {
    if (names.empty()) {
        cout << "No buildings are loaded.\n" << "Total buildings: 0\n" << "Total connections: 0\n";
        return;
    }

    size_t width = 8;   //len("Building")
    for (size_t i = 0; i < names.size(); ++i)
        if (names[i].size() > width) width = names[i].size();
    width += 2;

    cout << left << setw(static_cast<int>(width)) << "Building" << "Degree\n";
    for (size_t i = 0; i < names.size(); ++i)
        cout << left << setw(static_cast<int>(width)) << names[i] << adj[i].size() << "\n";
    cout << "Total buildings: " << names.size() << "\n" << "Total connections: " << edges << "\n";
}

//BFS from start; mark visited on enqueue
vector<int> CampusGraph::bfs(int start, vector<int>& dist) const {
    vector<int> order;
    vector<bool> visited(names.size(), false);
    dist.assign(names.size(), -1);

    queue<int> q;
    visited[start] = true;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        order.push_back(cur);
        for (size_t i = 0; i < adj[cur].size(); ++i) {
            int nb = adj[cur][i];
            if (!visited[nb]) {
                visited[nb] = true;
                dist[nb] = dist[cur] + 1;
                q.push(nb);
            }
        }
    }
    return order;
}

//print BFS results
void CampusGraph::displayReachable(const string& startName) const {
    if (names.empty()) {
        cout << "No buildings are loaded.\n";
        return;
    }
    int start = findBuilding(startName);
    if (start == -1) {
        cout << "Error: unknown building \"" << trim(startName) << "\"\n";
        return;
    }

    vector<int> dist;
    vector<int> order = bfs(start, dist);

    cout << "Reachable from " << names[start] << ":\n";
    for (size_t i = 0; i < order.size(); ++i) cout << names[order[i]] << " (distance " << dist[order[i]] << ")\n";
    cout << "Reachable: " << order.size() << " of " << names.size() << " buildings\n";
}
