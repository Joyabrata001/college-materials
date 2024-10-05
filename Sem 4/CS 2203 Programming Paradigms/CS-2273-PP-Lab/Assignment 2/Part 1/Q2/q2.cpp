#include <iostream>
using namespace std;

const int DEFAULT_SIZE = 10;
const int INCREMENT_SIZE = 10;
const int MAX_SIZE = 20;

typedef struct RuntimeSizeArray
{
    int loc;
    int arr_size;
    int max_size;
    int *arr;
} rsa;

bool initializeRSA(rsa &r)
{
    r.loc = -1;
    r.arr_size = DEFAULT_SIZE - 1; //cause 0 indexed array
    r.arr = new int[DEFAULT_SIZE];
    r.max_size = MAX_SIZE - 1;

    if (r.arr == nullptr)
        return false;

    return true;
}

bool inflate(rsa &r, int extra_space)
{
    int *temp = new int[r.arr_size + extra_space];
    r.arr_size += extra_space;
    if (temp == nullptr)
        return false;

    for (int i = 0; i <= r.arr_size; i++)
    {
        temp[i] = r.arr[i];
    }

    delete r.arr;
    r.arr = temp;
    return true;
}

bool addElement(rsa &r, int data)
{
    if (r.loc == r.arr_size)
    {
        if (r.arr_size == r.max_size)
        {
            return false;
        }
        else if (r.arr_size + INCREMENT_SIZE <= r.max_size)
            if (!inflate(r, INCREMENT_SIZE))
            {
                cout << "Error: Fail to inflate, exiting";
                exit(-1);
            }
            else if (!inflate(r, r.max_size - r.arr_size))
            {
                cout << "Error: Fail to inflate, exiting";
                exit(-1);
            }
    }

    r.loc++;
    r.arr[r.loc] = data;

    return true;
}

//location should be based on a zero indexed array
inline int fetchElement(rsa r, int loc)
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
        r.arr[initial] = r.arr[final];
        initial++;
        final++;
    }

    r.loc = initial - 1;

    while (initial <= r.arr_size)
    {
        r.arr[initial] = 0;
        initial++;
    }

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

bool printAll(rsa r)
{
    for (int i = 0; i < r.arr_size + 1; i++)
        cout << fetchElement(r, i) << " ";
    cout << endl;

    return true;
}

int main()
{
    rsa r;

    cout << "Initializing RSA with initial size " << DEFAULT_SIZE << " and  max size " << MAX_SIZE << endl;
    cout << endl;
    if (!initializeRSA(r))
    {
        cout << "Error: Memory Allotment Error, Exiting" << endl;
        exit(11);
    }

    cout << "Adding 10 elements (no inflating takes place)" << endl;
    for (int i = 0; i < 10; i++)
        if (!addElement(r, i))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    printAll(r);
    cout << endl;

    cout << "Adding 10 more elements (inflation will take place)" << endl;
    for (int i = 0; i < 10; i++)
        if (!addElement(r, i + 10))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    printAll(r);
    cout << endl;

    cout << "Resetting Elements(make their value 0) with given pos 5, and n as 5" << endl;
    if (!resetElements(r, 5, 5))
    {
        cout << "Error: provided out of bound parameters" << endl;
    }
    printAll(r);
    cout << endl;

    cout << "Max Size: " << getMaxSize(r) << endl;
    cout << "No. of elements: " << getCount(r) + 1 << endl;
    cout << endl;

    cout << "Making another RSA(b) having value 20-39:" << endl;
    rsa b;
    initializeRSA(b);
    for (int i = 0; i < 20; i++)
        if (!addElement(b, i + 20))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    printAll(b);
    cout << endl;

    cout << "Removing it's first 10 elements:" << endl;
    if (!resetElements(b, 0, 10))
    {
        cout << "Error: provided out of bound parameters" << endl;
    }
    printAll(b);
    cout << endl;

    cout<<"First RSA(r):"<<endl;
    printAll(r);
    cout << endl;

    cout<<"First RSA(b):"<<endl;
    printAll(b);
    cout << endl;
    return 0;
}