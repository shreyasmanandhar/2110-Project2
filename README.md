# Overview
**Foundations of Data Structures CSCE 2110 - Project 1 [Smart Campus Navigation and Facility Analytics System] - <ins>Milestone 1</ins>**

This project is intended to design a program that models a university campus. It loads buildings, building connections, facilities, and academic departments from text files, then lets the user explore them through a menu-driven command-line interface.

The project applies data structures and algorithms: a hash table with separate chaining (facilities), an undirected graph with an adjacency list and breadth-first search (buildings), and a general tree with preorder traversal (departments).

## Functionality Description

* main.cpp: It loads all data files at startup, then runs a menu loop until the user shooses to exits.

* Facilities: Facilities, HashTable, and Chain (SeparateChaining) store facilities in a hash table of 11 buckets. Collisions are handled with separate chaining, where each bucket is a linked list. Facility IDs are stored in uppercase, so searches are not case-sensitive. A facility is accepted only if its building exists in the campus graph and its ID is not already in the table.

* Campus Graph: CampusGraph stores buildings as vertices and connections as undirected edges in an adjacency list. It can print each building with its neighbors, a degree table with totals, and a breadth-first search (BFS) that lists every building reachable from a chosen building along with its distance.

* Department Tree: DepartmentTree stores departments as a general tree. Each department has one parent and any number of children, and the first department added becomes the root. It supports adding a department, looking one up (parent, number of direct children, depth), printing the indented hierarchy, and a preorder traversal. Department names are not case-sensitive and must be unique.

* Utilities: This is an additional feature implemented through Utils which we planned to create for the ease of teh team. Utils provides shared helpers for trimming text, case-insensitive comparison, splitting fields, skipping blank and comment lines, and printing load warnings.

* Input Handling: Invalid lines in a data file are skipped with a warning that names the file and line number. A missing file is reported and treated as empty. Menu input is validated, and invalid choices return to the menu.

## Project Structure (Primary files only)

* include/ : All header (.h)
* source/ : (.cpp) files, including main.cpp
* data/ : buildings.txt, connections.txt, facilities.txt, departments.txt

The project also includes additional files such as documentations and folder of test data.

## Requirements & Dependencies
* Linux environment with a terminal
* C++ compiler (g++ was used during development and testing)
* Note: This program was tested on the UNT CELL machines and is best run there.

## Setup and Execution

### Compiling the Program
* Navigate to the main project directory and execute the following command (not required but preferred for efficiency, and the user may rename the output file based on their preference): `g++ -std=c++11 -Wall -Wextra -Iinclude src/*.cpp -o test_output`
* If the compilation is successful, an executable file named `text_output` will be created in the prohect directory.

### Running the Program
* After successful compilation, to execute the program, run the following command in the terminal: `./test_output`

## Menu Options
1. View all facilities
3. Search facility by ID
4. View campus graph
5. Display graph counts and degrees
6. Find reachable buildings (BFS)
7. Add department
8. Search department
9. Display department hierarchy
10. Run preorder traversal
11. Exit

## Data File Format

Each record is on its own line, with fields separated by a vertical bar (|). Blank lines and lines starting with # are ignored. Spaces around fields are trimmed.
* buildings.txt:    BuildingName
* connections.txt:  BuildingName1 | BuildingName2
* facilities.txt:   FacilityID | FacilityName | BuildingName | Category
* departments.txt:  DepartmentName | ParentName

Files are loaded in this order: buildings, connections, facilities, departments.
Building names are matched ignoring case, and facility buildings and connections must refer to buildings listed in buildings.txt. The root department comes first and its parent must be NONE.

## Help

Common problems
* Having the header files or code files in an inaccessible repository or folder.
   - if you are in the cell machine run the command ls and make sure all the files are listed
   - if you are in an editor like Visual Studio make sure you can view all files in the explorer
* Not being in a UNT CELL machine with proper access.
   - UNT CELL machines have a firewall that has geographical access so make sure you are logged into a computer on the engineering campus or have logged into the CELL with two factor authentification on the DOU mobile app.

## Authors

* Member: Shreyas Manadhar
* Email: ShreyasManandhar@my.unt.edu
----------
* Member: Tucker Williamson
* Email: JakeWilliamson@my.unt.edu
----------
* Member: Samuel Smethers
* Email: SamuelSmethers@my.unt.edu

## Version History

* 0.1 – Milestone 1
    * This version is the Initial Release and is the core functionality of the full system.

## THANK YOU
