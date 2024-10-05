#include <iostream>
using namespace std;

#include <cstdlib>
#include <ctime>

const int DATASET_SIZE = 5;

struct value
{
    int data;
};

inline int val_cmp(value a, value b)
{
    return a.data - b.data;
}

template <typename A>
void generic_swap(A &a, A &b)
{
    A c = a;
    a = b;
    b = c;
}

template <typename T>
void generic_sort(T &a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
                generic_swap(a[j], a[j + 1]);
        }
    }
}

template <typename R>
void generic_sort(R &a, int n, int (*cmp_fn)(value, value))
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (cmp_fn(a[j], a[j + 1]))
                generic_swap(a[j], a[j + 1]);
        }
    }
}

int main()
{
    srand(time(0));

    cout << "Testing int: " << endl;
    int a[DATASET_SIZE];
    for (int i = 0; i < DATASET_SIZE; i++)
        a[i] = rand() % 50;
    cout << "Original Values: ";
    for (int i = 0; i < DATASET_SIZE; i++)
        cout << a[i] << " ";
    cout << endl;
    generic_sort(a, DATASET_SIZE);
    cout << "Sorted Values  : ";
    for (int i = 0; i < 5; i++)
        cout << a[i] << " ";
    cout << endl
         << endl;

    cout << "Testing short: " << endl;
    short b[DATASET_SIZE];
    for (int i = 0; i < DATASET_SIZE; i++)
        b[i] = rand() % 50;
    cout << "Original Values: ";
    for (int i = 0; i < DATASET_SIZE; i++)
        cout << b[i] << " ";
    cout << endl;
    generic_sort(b, DATASET_SIZE);
    cout << "Sorted Values  : ";
    for (int i = 0; i < 5; i++)
        cout << b[i] << " ";
    cout << endl
         << endl;

    cout << "Testing float: " << endl;
    float c[DATASET_SIZE];
    for (int i = 0; i < DATASET_SIZE; i++)
        c[i] = rand() % 50;
    cout << "Original Values: ";
    for (int i = 0; i < DATASET_SIZE; i++)
        cout << c[i] << " ";
    cout << endl;
    generic_sort(c, DATASET_SIZE);
    cout << "Sorted Values  : ";
    for (int i = 0; i < 5; i++)
        cout << c[i] << " ";
    cout << endl
         << endl;

    cout << "Testing double: " << endl;
    double d[DATASET_SIZE];
    for (int i = 0; i < DATASET_SIZE; i++)
        d[i] = rand() % 50;
    cout << "Original Values: ";
    for (int i = 0; i < DATASET_SIZE; i++)
        cout << d[i] << " ";
    cout << endl;
    generic_sort(d, DATASET_SIZE);
    cout << "Sorted Values  : ";
    for (int i = 0; i < 5; i++)
        cout << d[i] << " ";
    cout << endl
         << endl;

    cout << "Testing struct value: " << endl;
    value e[DATASET_SIZE];
    for (int i = 0; i < DATASET_SIZE; i++)
        e[i].data = rand() % 50;
    cout << "Original Values: ";
    for (int i = 0; i < DATASET_SIZE; i++)
        cout << e[i].data << " ";
    cout << endl;
    cout << "Here usual comparision in sorting will give error, so overloading sort with a compare_function()" << endl;
    generic_sort(e, DATASET_SIZE, val_cmp);
    cout << "Sorted Values  : ";
    for (int i = 0; i < 5; i++)
        cout << e[i].data << " ";
    cout << endl
         << endl;
    return 0;
}