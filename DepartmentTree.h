//DepartmentTree.h
//Author: SHREYAS MANANDHAR
//Header file for tree functions

#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include<vector>
#include<string>

//for an individual department
struct DepartmentNode{
    std::string name;       //department's name
    DepartmentNode* parent;     //pointer to parent department
    std::vector<DepartmentNode*> children;       //vector of pointer to children

    DepartmentNode(const std::string& deptName, DepartmentNode* parentNode){
        name = deptName;
        parent = parentNode;
    }
};

//for the whole hierarchy of departments
class DepartmentTree{
    public:
        DepartmentTree();       //constructor
        ~DepartmentTree();      //destructor to free each node

        DepartmentTree(const DepartmentTree&) = delete;
        DepartmentTree& operator=(const DepartmentTree&) = delete;

        //loading the departments.txt file
        void loadDepartments(const std::string& path);

        //if tree has no departments
        bool isEmpty() const;

        //adding department, root has no parent, and returns error if input is rejected
        bool addDepartment(const std::string& name, const std::string& parentName, std::string& error);

        //displaying department, parent, child count, and depth
        void displayDepartment(const std::string& name) const;

        //displaying in hierarchy
        void displayHierarchy() const;

        //displaying in preorder traversal
        void displayPreorder() const;

    private:
        DepartmentNode* root;

        //finding department by name, case does not matter
        DepartmentNode* findNode(DepartmentNode* node, const std::string& name) const;
        
        //number of edges from root to the specific node
        int getDepth(const DepartmentNode* node) const;
        
        //clearing a node and its descendants
        void deleteTree(DepartmentNode* node);

        //to support displayHierarchy from public
        void printHierarchy(const DepartmentNode* node, int depth) const;
        
        //to support displayPreorder from public
        void collectPreorder(const DepartmentNode* node, std::vector<std::string>& result) const;
};

#endif