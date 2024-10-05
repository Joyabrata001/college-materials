#include <iostream>
#include <cstring>
using namespace std;

#include "circular_linked_list.h"

int main()
{
    circularLL c;
    char name1[NAME_SIZE] = "1";
    c.add_data(name1);

    char name2[NAME_SIZE] = "2";
    c.add_data(name2);

    char name3[NAME_SIZE] = "3";
    c.add_data(name3);

    char name4[NAME_SIZE] = "4";
    c.add_data(name4);
    c.display();

    c.delete_data(name3);
    c.display();

    return 0;
}