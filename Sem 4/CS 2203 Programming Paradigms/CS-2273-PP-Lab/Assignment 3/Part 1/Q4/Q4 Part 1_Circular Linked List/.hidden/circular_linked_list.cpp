#include <iostream>
#include <cstring>
using namespace std;

const int NAME_SIZE = 10;

class circularLL
{
    struct node
    {
        char *name;
        node *next;
    };

    node *tail;

public:
    circularLL();
    void add_data(char *person_name);
    void display();
    bool delete_data(char *person_name);
};

//initialises circular linked list
circularLL::circularLL()
{
    tail = new node;
    tail->next = tail;
}

//adds name to the circular linked list
void circularLL::add_data(char *person_name)
{
    node *temp = new node;
    temp->name = new char[NAME_SIZE];
    strcpy(temp->name, person_name);
    temp->next = tail->next;
    tail->next = temp;
}

//displays the circular linked list
void circularLL::display()
{
    node *temp = tail->next;

    while (temp != tail)
    {
        cout << temp->name << " -> ";
        temp = temp->next;
    }
    cout << "CYCLE" << endl;
}

//deletes element with person_name, if present, otherwise return false
bool circularLL::delete_data(char *person_name)
{
    node *curr = tail->next;
    node *prev = tail;

    while (curr != tail)
    {
        if (strcmp(curr->name, person_name) == 0)
        {
            prev->next = curr->next;
            delete curr->name;
            delete curr;
            return true;
        }

        prev = curr;
        curr = curr->next;
    }
    return false;
}