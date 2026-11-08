// main.cpp
// Purpose: load data files and run the Milestone 1 menu.
// Author: Member B (shared)

#include <iostream>
#include <string>
#include "CampusGraph.h"
#include "Utils.h"
// Member A --- #include facility / hash table headers here
#include "DepartmentTree.h"

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
         << "10. Exit\n"
         << "Choice: ";
}

// read choice 1-10; -1 invalid, -2 EOF
static int readChoice() {
    string line;
    if (!getline(cin, line)) return -2;
    line = trim(line);
    if (line.empty() || line.size() > 2) return -1;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] < '0' || line[i] > '9') return -1;
    }
    int n = stoi(line);
    return (n >= 1 && n <= 10) ? n : -1;
}

// prompt for a name; false + error if blank
// Member A --- use for ID prompt
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
    DepartmentTree tree;

    // load order: buildings, connections, facilities, departments
    graph.loadBuildings(dir + "buildings.txt");
    graph.loadConnections(dir + "connections.txt");
    // Member A --- load dir + "facilities.txt" here (pass graph for building checks)
    tree.loadDepartments(dir + "departments.txt");

    while (true) {
        printMenu();
        int choice = readChoice();
        if (choice == -2) {  // EOF
            cout << "\nGoodbye.\n";
            break;
        }

        string name;
        switch (choice) {
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
                if (readName("Enter department name: ", name)) {
                    string parent, error;
                    bool isRoot = tree.isEmpty();
                    // empty tree, new department becomes the root, parent is not prompted
                    if (isRoot || readName("Enter parent department: ", parent)) {
                        if (tree.addDepartment(name, parent, error))
                            cout << "Added department \"" << name
                                 << (isRoot ? "\" as the root.\n" : "\" under \"" + parent + "\".\n");
                        else
                            cout << "Error: " << error << "\n";
                    }
                }
                break;
            case 7:
                if (readName("Enter department name: ", name)){
                    tree.displayDepartment(name);
                }
                break;
            case 8:
                tree.displayHierarchy();
                break;
            case 9:
                tree.displayPreorder();
                break;
            case 10:
                cout << "Goodbye.\n";
                return 0;
            default:
                cout << "Error: invalid choice. Enter a number from 1 to 10.\n";
                break;
        }
    }
    return 0;
}