#include <iostream>
using namespace std;

#include "circular_linked_list.h"

#include <cstdlib>
#include <ctime>

#include <cmath>

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

int fn1(int list_size)
{
    int x = rand() % 10; //10 for saving maths time

    int poly = pow(x, 3) - 2 * pow(x, 2) + 4 * x - 1;

    int return_val = 2 * (poly % list_size) - list_size;

    if (return_val == 0) //avoiding passing of zero
        return 1;
    else
        return return_val;
}

int fn2(int list_size)
{
    int x = rand() % 10; //10 for saving maths time

    int poly = pow(x, 2) - 3 * x + 6;

    int return_val = 2 * (poly % list_size) - list_size;

    if (return_val == 0) //avoiding passing of zero
        return 1;
    else
        return return_val;
}

int fn3(int list_size)
{
    int x = rand() % 10; //10 for saving maths time

    int poly = 3 * pow(x, 4) + pow(x, 3) + pow(x, 2) - 3 * x + 6;

    int return_val = 2 * (poly % list_size) - list_size;

    if (return_val == 0) //avoiding passing of zero
        return 1;
    else
        return return_val;
}

int random_value_giver(int list_size)
{
    int choice = rand() % 3 + 1;

    if (choice == 1)
        return fn1(list_size);
    else if (choice == 2)
        return fn2(list_size);
    else
        return fn3(list_size);
}

void go_forward(person_node *&tail, person_node *&temp, int list_size, int skip_size)
{
    for (int i = 0; i < skip_size; i++)
    {
        temp = temp->next;
        if (temp == tail)
            temp = temp->next;
    }
}

void go_backward(person_node *&tail, person_node *&temp, int list_size, int skip_size)
{
    for (int i = 0; i < list_size - skip_size; i++) //go back i steps == go back (list_size-i) steps
    {
        temp = temp->next;
        if (temp == tail)
            temp = temp->next;
    }
}

void play_game(person_node *tail, int list_size)
{
    int start_pos = rand() % list_size;
    int no_of_step = start_pos + 1;

    int skip_size = random_value_giver(list_size);
    bool forward = false;
    if (skip_size > 0)
        forward = true;
    else
        skip_size = -skip_size; //=ve of -ve is +ve

    person_node *temp = tail;

    while (no_of_step > 0)
    {
        temp = temp->next;
        no_of_step--;
    }

    cout << endl;
    cout << "Starting from '" << temp->name << "' with skip_size = " << skip_size << (forward ? "(Forward)" : "(Backword)")<<endl;
    cout << "List: " << endl;
    display(tail);
    cout << endl;

    while (temp->next->next != temp)
    {
        if (forward)
            go_forward(tail, temp, list_size, skip_size);
        else
            go_backward(tail, temp, list_size, skip_size);

        list_size--;

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