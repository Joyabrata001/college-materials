#include <iostream>
#include <cstring>
using namespace std;

const int NAME_SIZE = 10;

struct person_node
{
    char *name;
    person_node *next;
};

//initialises circular linked list
person_node *initialise_circular_list()
{
    person_node *tail = new person_node;
    tail->next = tail;
    return tail;
}

//adds name to the circular linked list
person_node *add_data(person_node *&tail, char *person_name)
{
    person_node *temp = new person_node;
    temp->name = new char[NAME_SIZE];
    strcpy(temp->name, person_name);
    temp->next = tail->next;
    tail->next = temp;
    return tail;
}

//displays the circular linked list
void display(person_node *tail)
{
    person_node *temp = tail->next;

    while (temp != tail)
    {
        cout << temp->name << " -> ";
        temp = temp->next;
    }
    cout << "CYCLE" << endl;
}

//deletes element with person_name, if present, otherwise return false
bool delete_data(person_node *&tail, char *person_name)
{
    person_node *curr = tail->next;
    person_node *prev = tail;

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

// int main()
// {
//     person_node *tail = initialise_circular_list();

//     char *a = "Abhiroop";
//     add_data(tail, a);

//     char *b = "B";
//     add_data(tail, b);

//     char *c = "c";
//     add_data(tail, c);

//     display(tail);
//     delete_data(tail,a);
//     display(tail);


// }