//DepartmentTree.cpp
//SHREYAS MANANDHAR
//function definition file for tree

#include "DepartmentTree.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

using namespace std;

//constructor creating empty tree
DepartmentTree::DepartmentTree(){
    root = nullptr;
}

//destructor clearing all nodes
DepartmentTree::~DepartmentTree(){
    deleteTree(root);
}

//clear a node and its descendants
void DepartmentTree::deleteTree(DepartmentNode* node){
    if (node==nullptr){
        return;
    }
    for (size_t i = 0; i < node->children.size(); i++){
        deleteTree(node->children[i]);
    }
    delete node;
}

//return true if tree is empty
bool DepartmentTree::isEmpty() const{
    return root == nullptr;
}

//find department by name, it is not case-sensitive
DepartmentNode* DepartmentTree::findNode(DepartmentNode* node, const string& name) const{
    if (node == nullptr){
        return nullptr;
    }
    if (equalsIgnoreCase(node->name, name)){
        return node;
    }
    for (size_t i=0; i < node->children.size(); i++){
        DepartmentNode* found = findNode(node->children[i],name);
        if (found != nullptr){
            return found;
        }
    }
    return nullptr;
}

//number of edges from root to the node
int DepartmentTree::getDepth(const DepartmentNode* node) const{
    if (node == nullptr){
        return -1;
    }

    int depth = 0;
    while (node->parent != nullptr){
        node = node->parent;
        depth = depth + 1;
    }
    return depth;
}

//adding a department, the first one becomes root, rejecting if false
bool DepartmentTree::addDepartment(const string& name, const string& parentName, string& error){
    string deptName = trim(name);

    //invalid empty input
    if (deptName.empty()){
        error = "Department name cannot be blank.";
        return false;
    }

    if (equalsIgnoreCase(deptName, "NONE")){
        error = "Department name \"NONE\" is reserved.";
        return false;
    }

    //tree is empty
    if (root == nullptr){
        root = new DepartmentNode(deptName, nullptr);
        return true;
    }

    string parent = trim(parentName);
    DepartmentNode* parentNode = findNode(root, parent);
    if (parentNode == nullptr){
        error = "Parent \"" + parent + "\" is UNKNOWN.";
        return false;
    }

    //duplicate check
    if (findNode(root,deptName) != nullptr){
        error = "Department \"" + deptName + "\" already exists.";
        return false;
    }

    parentNode->children.push_back(new DepartmentNode(deptName, parentNode));
    return true;
}

//loading the departments.txt file
void DepartmentTree::loadDepartments(const string& path){
    ifstream in(path.c_str());
    if (!in){
        printOpenError(path);
        printLoadSummary(path,0,0);
        return;
    }
    string line;
    int lineNum = 0, accepted = 0, rejected = 0;
    while (getline(in, line)){
        lineNum++;
        if(isSkippable(line)){
            continue;
        }

        vector<string> fields = splitFields(line);
        if(fields.size() != 2){
            printWarning(path,lineNum,"expected 2 fields, but found " + to_string(fields.size()));
            rejected++;
            continue;
        }

        if (fields[0].empty() || fields[1].empty()){
            printWarning(path,lineNum,"empty department or parent name");
            rejected++;
            continue;
        }
        bool parentIsNone = equalsIgnoreCase(fields[1],"NONE");
        //root's parent must be NONE
        if (root==nullptr && !parentIsNone){
            printWarning(path,lineNum,"root department's parent must be NONE");
            rejected++;
            continue;
        }

        if (root != nullptr && parentIsNone){
            printWarning(path,lineNum,"only the root department's parent must be NONE");
            rejected++;
            continue;
        }

        string error;
        if (addDepartment(fields[0],fields[1],error)){
            accepted++;
        }
        else{
            printWarning(path,lineNum,error);
            rejected++;
        }
    }
    printLoadSummary(path,accepted,rejected);
}

//displaying parent, child-count, and depth
void DepartmentTree::displayDepartment(const string& name) const{
    if (root == nullptr){
        cout << "No departments are loaded.\n";
        return;
    }
    DepartmentNode* node = findNode(root,name);
    if (node==nullptr){
        cout << "Department \"" << name << "\" not found.\n";
        return;
    }
    string parentName = "None";
    if (node->parent != nullptr) parentName = node->parent->name;
    cout << "Name: " << node->name << endl;
    cout << "Parent: " << parentName << endl;
    cout << "Direct children: " << node->children.size() << endl;
    cout << "Depth: " << getDepth(node) << endl;
}

//to help displayHierarchy recursively
void DepartmentTree::printHierarchy(const DepartmentNode* node, int depth) const{
    for (int i=0; i < depth*4; i++){
        cout << ' ';
    }
    cout << node->name << "\n";
    for (size_t i=0; i < node->children.size(); i++){
        printHierarchy(node->children[i], depth+1);
    }
}

//displaying hierarchy
void DepartmentTree::displayHierarchy() const{
    if (root == nullptr){
        cout << "No departments are loaded." << endl;
        return;
    }
    printHierarchy(root,0);
}

//to help displayPreorder recursively
void DepartmentTree::collectPreorder(const DepartmentNode* node, vector<string>& result) const{
    result.push_back(node->name);
    for (size_t i=0; i < node->children.size(); i++){
        collectPreorder(node->children[i],result);
    }
}

//displaying in preorder
void DepartmentTree::displayPreorder() const{
    if (root == nullptr){
        cout << "No departments are loaded." << endl;
        return;
    }
    vector<string> result;
    collectPreorder(root, result);
    cout << "Preorder: ";
    for(size_t i=0; i < result.size(); i++){
        if (i>0) cout << ", ";
        cout << result[i];
    }
    cout << endl;
}