#include <iostream>
using namespace std;

#include <cstring>

const int DEFAULT_SIZE = 10;
const int INCREMENT_SIZE = 10;
const int MAX_SIZE = 20;

typedef unsigned char byte;

typedef struct RuntimeSizeArray
{
    int loc;
    int arr_size;
    int max_size;
    byte **arr;

    //Additions for going generic
    int dsize;
    void (*printFn)(byte *a);

} rsa;

bool initializeRSA(rsa &r, int dsize, void (*printFn)(byte *a))
{
    r.printFn = printFn;
    r.dsize = dsize;
    r.loc = -1;
    r.arr_size = DEFAULT_SIZE - 1; //cause 0 indexed array
    r.arr = new byte *[DEFAULT_SIZE];

    r.max_size = MAX_SIZE - 1;

    if (r.arr == nullptr)
        return false;

    return true;
}

bool inflate(rsa &r, int extra_space)
{
    byte **temp = new byte *[r.arr_size + extra_space];

    if (temp == nullptr)
        return false;

    for (int i = 0; i <= r.arr_size; i++)
    {
        temp[i] = r.arr[i];
    }

    r.arr_size += extra_space;

    delete r.arr;
    r.arr = temp;
    return true;
}

bool addElement(rsa &r, byte *data)
{
    if (r.loc == r.arr_size)
    {
        if (r.arr_size == r.max_size)
        {
            return false;
        }
        else
        {
            if (r.arr_size + INCREMENT_SIZE <= r.max_size)
            {
                if (!inflate(r, INCREMENT_SIZE))
                {
                    cout << "Error: Fail to inflate, exiting";
                    exit(-1);
                }
            }
            else
            {
                if (!inflate(r, r.max_size - r.arr_size))
                {
                    cout << "Error: Fail to inflate, exiting";
                    exit(-1);
                }
            }
        }
    }

    r.loc++;

    r.arr[r.loc] = (byte *)malloc(r.dsize);

    memcpy(r.arr[r.loc], data, r.dsize);

    return true;
}

//location should be based on a zero indexed array
inline byte *fetchElement(rsa r, int loc)
{
    return r.arr[loc];
}

//location should be based on a zero indexed array
bool resetElements(rsa &r, int given_index, int n)
{
    if (r.arr_size < given_index + n)
        return false;

    int initial = given_index - 1;
    int final = given_index + n - 1;

    while (final <= r.arr_size)
    {
        swap(r.arr[initial], r.arr[final]);
        initial++;
        final++;
    }

    r.loc = initial - 1;

    for (; initial < final; initial++)
        delete r.arr[initial];

    return true;
}

inline int getMaxSize(rsa r)
{
    return r.max_size;
}

inline int getCount(rsa r)
{
    return r.loc;
}

inline void print_int(byte *data)
{
    cout << *((int *)data);
}

inline void print_char(byte *data)
{
    cout << *((char *)data);
}

inline void print_char_star(byte *data)
{
    cout << (char *)data;
}

inline void print_double(byte *data)
{
    cout << *((double *)data);
}

bool printAll(rsa r)
{
    for (int i = 0; i < r.loc + 1; i++)
    {
        r.printFn(r.arr[i]);
        cout << " ";
    }
    cout << endl;

    return true;
}

int main()
{
    rsa a;

    cout << "Making <int> RSA(a)" << endl;
    if (!initializeRSA(a, sizeof(int), print_int))
    {
        cout << "Error: Memory Allotment Error, Exiting" << endl;
        exit(1);
    }

    for (int i = 0; i < 20; i++)
        if (!addElement(a, (byte *)&i))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    printAll(a);
    cout << endl;

    cout << "Resetting Elements(make their value 0) with given pos 5, and n as 5" << endl;
    if (!resetElements(a, 5, 5))
    {
        cout << "Error: provided out of bound parameters" << endl;
    }
    printAll(a);
    cout << endl;

    cout << "Max Size: " << getMaxSize(a) << endl;
    cout << "No. of elements: " << getCount(a) + 1 << endl;
    cout << endl
         << endl;

    cout << "Making <char> RSA(b) :" << endl;
    rsa b;
    initializeRSA(b, sizeof(char), print_char);
    for (int i = 0; i < 10; i++)
    {
        char temp = i + 65;
        if (!addElement(b, (byte *)&temp))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    }
    printAll(b);
    cout << endl;

    // cout << "Removing it's first 5 elements:" << endl;
    // if (!resetElements(b, 1, 5))
    // {
    //     cout << "Error: provided out of bound parameters" << endl;
    // }
    // printAll(b);
    cout << endl
         << endl;

    cout << "Making <double> RSA(c) :" << endl;
    rsa c;
    initializeRSA(c, sizeof(double), print_double);
    for (int i = 0; i < 10; i++)
    {
        double temp = (double)i + ((double)i) / 10;
        if (!addElement(c, (byte *)&temp))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    }
    printAll(c);
    cout << endl;

    // cout << "Removing it's first 5 elements:" << endl;
    // if (!resetElements(c, 1, 5))
    // {
    //     cout << "Error: provided out of bound parameters" << endl;
    // }
    // printAll(c);
    cout << endl
         << endl;

    cout << "Making <char*> RSA(d) :" << endl;
    char *string = new char[5];
    strcpy(string, "abc");
    rsa d;

    if (!initializeRSA(d, sizeof(char *), print_char_star))
    {
        cout << "Error: Memory Allotment Error, Exiting" << endl;
        exit(1);
    }

    for (int i = 0; i < 10; i++)
    {
        string[0] = (char)(rand() % (95 - 65) + 65);
        if (!addElement(d, (byte *)string))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    }
    printAll(d);
    cout << endl;

    // cout << "Removing it's first 5 elements:" << endl;
    // if (!resetElements(d, 1, 5))
    // {
    //     cout << "Error: provided out of bound parameters" << endl;
    // }
    // printAll(d);
    // cout << endl;

    return 0;
}