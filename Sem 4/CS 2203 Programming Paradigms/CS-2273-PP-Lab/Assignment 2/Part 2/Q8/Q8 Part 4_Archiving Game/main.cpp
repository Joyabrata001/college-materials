#include <iostream>
using namespace std;

#include "circular_linked_list.h"
#include "play.h"
#include <cstdlib>


int main()
{
    srand(time(0));

    cout << "Enter N: ";
    int n;
    cin >> n;
    cin.ignore();

    person_node *tail = initialise_circular_list();
    input_data(tail, n);

    play_game(tail, n);

    return 0;
}