//Samuel Smethers
//Linked list to use in hash table to chain in separate bins
#include "SeparateChaining.h"

Chain::Chain(){
    front = nullptr;
    rear = nullptr;
    count = 0;
}

void Chain::RemoveChain()
{
    Node* current = front;
    while (current !=nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
}


void Chain::addFacility(const Facilities& tempFac)
{
    Node* newNode = new Node(tempFac);
    if (rear == nullptr){
        front = newNode;
        rear = newNode;
    }
    else{
        rear->next = newNode;
        rear = newNode;
    }
    count = count+1;
}

bool Chain::isEmpty() const{
    return front == nullptr;
}

Facilities* Chain::searchID(string inputID)
{
    for (Node* current = front; current!= nullptr; current = current->next){
        if (current->data.getID() == inputID){
            return &current->data;
        }
    }
    return nullptr;
}

bool Chain::isDuplicate(string tempID)
{
    for (Node* current = front; current!= nullptr; current = current->next){
        if (tempID == current->data.getID()){
            return true;
        }
    }
    return false;
}