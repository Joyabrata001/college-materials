#include <iostream>
using namespace std;

#include "circular_linked_list.h"

#include <cstdlib>
#include <ctime>

void input_data(person_node *tail, int n)
{
    char name[NAME_SIZE];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter name for Person " << i + 1 << ": ";
        cin.getline(name, NAME_SIZE);
        add_data(tail, name);
    }
}

void play_game(person_node *tail, int start_pos, int skip_size = 2)
{
    int no_of_step = start_pos + 1;

    person_node *temp = tail;

    while (no_of_step > 0)
    {
        temp = temp->next;
        no_of_step--;
    }

    cout << endl;
    cout << "Starting from '" << temp->name << "' with skip_size = " << skip_size << endl;
    cout << "List: " << endl;
    display(tail);
    cout << endl;
    while (temp->next->next != temp)
    {
        for (int i = 0; i < skip_size; i++)
        {
            temp = temp->next;
            if (temp == tail)
                temp = temp->next;
        }

        person_node *del = temp;
        temp = temp->next;
        if (temp == tail)
            temp = temp->next;
        cout << "Evicting '" << del->name << "'" << endl;
        delete_data(tail, del->name);
        cout << "List: " << endl;
        display(tail);
        cout << endl;
    }

    cout << "'" << tail->next->name << "' Won The Game !!" << endl;
}

int main()
{
    cout << "Enter N: ";
    int n;
    cin >> n;
    cin.ignore();

    person_node *tail = initialise_circular_list();
    input_data(tail, n);

    srand(time(0));
    int start_pos = rand() % n;

    play_game(tail, start_pos);

    return 0;
}