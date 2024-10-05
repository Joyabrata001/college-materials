#include <iostream>
using namespace std;

#include "circular_linked_list_game.h"
#include <cstdlib>


int main()
{
    srand(time(0));

    cout << "Enter N: ";
    int n;
    cin >> n;
    cin.ignore();

    circularLL_game c;
    c.input_data(n);

    c.play_game(n);

    return 0;
}