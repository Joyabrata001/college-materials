#ifndef CIRCULAR_LINKED_LIST
#define CIRCULAR_LINKED_LIST

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

#endif