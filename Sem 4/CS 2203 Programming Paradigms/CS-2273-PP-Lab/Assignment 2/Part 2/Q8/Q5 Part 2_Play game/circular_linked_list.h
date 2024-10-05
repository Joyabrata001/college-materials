#ifndef CIRCULAR_LINKED_LIST
#define CIRCULAR_LINKED_LIST

const int NAME_SIZE = 10;

struct person_node
{
    char *name;
    person_node *next;
};

//initialises circular linked list
person_node *initialise_circular_list();

//adds name to the circular linked list
person_node *add_data(person_node *&tail, char *person_name);

//displays the circular linked list
void display(person_node *tail);

//deletes element with person_name, if present, otherwise return false
bool delete_data(person_node *&tail, char *person_name);

#endif