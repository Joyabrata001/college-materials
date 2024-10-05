#include <iostream>
#include <cstring>
using namespace std;

#include "circular_linked_list.h"

int main()
{
    person_node *t = initialise_circular_list();
    char name[NAME_SIZE] = "1";
    add_data(t, name);

    char name1[NAME_SIZE] = "2";
    add_data(t, name1);

    char name2[NAME_SIZE] = "3";
    add_data(t, name2);

    char name3[NAME_SIZE] = "4";
    add_data(t, name3);
    display(t);

    delete_data(t,name3);
    display(t);

    return 0;
}