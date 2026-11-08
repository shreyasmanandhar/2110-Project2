// main.cpp
// Purpose: load data files and run the Milestone 1 menu.
// Author: Member B (shared)

#include <iostream>
#include <string>
#include "CampusGraph.h"
#include "Utils.h"
// Member A --- #include facility / hash table headers here
// Member C --- #include department tree header here

using namespace std;

// print M1 menu
static void printMenu() {
    cout << "\n===== Campus Menu =====\n"
         << "1. View all facilities\n"
         << "2. Search facility by ID\n"
         << "3. View campus graph\n"
         << "4. Display graph counts and degrees\n"
         << "5. Find reachable buildings (BFS)\n"
         << "6. Add department\n"
         << "7. Search department\n"
         << "8. Display department hierarchy\n"
         << "9. Run preorder traversal\n"
         << "0. Exit\n"
         << "Choice: ";
}

// read choice 0-9; -1 invalid, -2 EOF
static int readChoice() {
    string line;
    if (!getline(cin, line)) return -2;
    line = trim(line);
    if (line.empty() || line.size() > 2) return -1;
    for (size_t i = 0; i < line.size(); ++i)
        if (line[i] < '0' || line[i] > '9') return -1;
    int n = stoi(line);
    return (n >= 0 && n <= 9) ? n : -1;
}

// prompt for a name; false + error if blank
// Member A --- use for ID prompt
// Member C --- use for department/parent prompts
static bool readName(const string& prompt, string& out) {
    cout << prompt;
    if (!getline(cin, out)) {
        out.clear();
        return false;
    }
    out = trim(out);
    if (out.empty()) {
        cout << "Error: name cannot be blank.\n";
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    // NFR-10: optional data dir
    string dir = (argc > 1) ? argv[1] : "data";
    if (dir.empty()) dir = "data";
    char last = dir[dir.size() - 1];
    if (last != '/' && last != '\\') dir += '/';

    CampusGraph graph;
    // Member A --- declare facility list + HashTable here
    // Member C --- declare DepartmentTree here

    // load order: buildings, connections, facilities, departments
    graph.loadBuildings(dir + "buildings.txt");
    graph.loadConnections(dir + "connections.txt");
    // Member A --- load dir + "facilities.txt" here (pass graph for building checks)
    // Member C --- load dir + "departments.txt" here

    while (true) {
        printMenu();
        int choice = readChoice();
        if (choice == -2) {  // EOF
            cout << "\nGoodbye.\n";
            break;
        }

        string name;
        switch (choice) {
            case 0:
                cout << "Goodbye.\n";
                return 0;
            case 1:
                // Member A --- view all facilities
                cout << "Not implemented yet.\n";
                break;
            case 2:
                // Member A --- search facility by ID
                cout << "Not implemented yet.\n";
                break;
            case 3:
                graph.displayGraph();
                break;
            case 4:
                graph.displayCounts();
                break;
            case 5:
                if (readName("Enter starting building: ", name))
                    graph.displayReachable(name);
                break;
            case 6:
                // Member C --- add department (no parent prompt if tree empty)
                cout << "Not implemented yet.\n";
                break;
            case 7:
                // Member C --- search department
                cout << "Not implemented yet.\n";
                break;
            case 8:
                // Member C --- display hierarchy (4 spaces per depth)
                cout << "Not implemented yet.\n";
                break;
            case 9:
                // Member C --- preorder traversal
                cout << "Not implemented yet.\n";
                break;
            default:
                cout << "Error: invalid choice. Enter a number from 0 to 9.\n";
                break;
        }
    }
    return 0;
}
