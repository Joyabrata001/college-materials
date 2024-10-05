#include <iostream>
#include <cstring>
using namespace std;
#include <cmath>
#include <cstdlib>

const int NAME_SIZE = 10;

class circularLL_game
{
    struct node
    {
        char *name;
        node *next;
    };

    node *tail;

public:
    circularLL_game();
    void add_data(char *);
    void display();
    bool delete_data(char *);
    void go_forward(node *&, node *&, int, int);
    void go_backward(node *&, node *&, int, int);
    void play_game(int);
    void input_data(int n);
};

//initialises circular linked list
circularLL_game::circularLL_game()
{
    tail = new node;
    tail->next = tail;
}

//adds name to the circular linked list
void circularLL_game::add_data(char *person_name)
{
    node *temp = new node;
    temp->name = new char[NAME_SIZE];
    strcpy(temp->name, person_name);
    temp->next = tail->next;
    tail->next = temp;
}

//displays the circular linked list
void circularLL_game::display()
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
bool circularLL_game::delete_data(char *person_name)
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

void circularLL_game::go_forward(node *&tail, node *&temp, int list_size, int skip_size)
{
    for (int i = 0; i < skip_size; i++)
    {
        temp = temp->next;
        if (temp == tail)
            temp = temp->next;
    }
}

void circularLL_game::go_backward(node *&tail, node *&temp, int list_size, int skip_size)
{
    for (int i = 0; i < list_size - skip_size; i++) //go back i steps == go back (list_size-i) steps
    {
        temp = temp->next;
        if (temp == tail)
            temp = temp->next;
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

void circularLL_game::play_game(int list_size)
{
    int start_pos = rand() % list_size;
    int no_of_step = start_pos + 1;

    int skip_size = random_value_giver(list_size);
    bool forward = false;
    if (skip_size > 0)
        forward = true;
    else
        skip_size = -skip_size; //=ve of -ve is +ve

    node *temp = tail;

    while (no_of_step > 0)
    {
        temp = temp->next;
        no_of_step--;
    }

    cout << endl;
    cout << "Starting from '" << temp->name << "' with skip_size = " << skip_size << (forward ? "(Forward)" : "(Backword)") << endl;
    cout << "List: " << endl;
    display();
    cout << endl;

    while (temp->next->next != temp)
    {
        if (forward)
            go_forward(tail, temp, list_size, skip_size);
        else
            go_backward(tail, temp, list_size, skip_size);

        list_size--;

        node *del = temp;
        temp = temp->next;
        if (temp == tail)
            temp = temp->next;
        cout << "Evicting '" << del->name << "'" << endl;
        delete_data(del->name);
        cout << "List: " << endl;
        display();
        cout << endl;
    }

    cout << "'" << tail->next->name << "' Won The Game !!" << endl;
}

void circularLL_game::input_data(int n)
{
    char name[NAME_SIZE];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter name for Person " << i + 1 << ": ";
        cin.getline(name, NAME_SIZE);
        add_data(name);
    }
}






