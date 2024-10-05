#ifndef CIRCULAR_LINKED_LIST
#define CIRCULAR_LINKED_LIST

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

#endif