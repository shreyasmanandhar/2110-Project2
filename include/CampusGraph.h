//CampusGraph.h
//Purpose: undirected campus graph (adjacency list) and BFS.
//Author: Member B

#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

class CampusGraph {
public:
    CampusGraph();

    //load buildings.txt (vertices)
    void loadBuildings(const std::string& path);

    //load connections.txt (edges); call after loadBuildings
    void loadConnections(const std::string& path);

    //index of building (trimmed, case-insensitive), -1 if not found
    //Member A --- validate facility building with this; -1 = reject
    int findBuilding(const std::string& name) const;

    //stored spelling at index (index must be valid)
    //Member A --- store this spelling in Facility, not the file's
    const std::string& getName(int index) const;

    int buildingCount() const;
    int connectionCount() const;
    int degree(int index) const;

    //menu 3: buildings and neighbors
    void displayGraph() const;

    //menu 4: totals and degrees
    void displayCounts() const;

    //menu 5: BFS visit order and distances
    void displayReachable(const std::string& startName) const;

private:
    std::vector<std::string> names;         //vertex spelling, file order
    std::vector<std::vector<int> > adj;     //neighbor indices, insertion order
    int edges;                              //undirected, counted once

    //true if a-b edge exists (either direction)
    bool hasEdge(int a, int b) const;

    //BFS core: returns visit order, fills dist (-1 = unreached)
    std::vector<int> bfs(int start, std::vector<int>& dist) const;
};

#endif
