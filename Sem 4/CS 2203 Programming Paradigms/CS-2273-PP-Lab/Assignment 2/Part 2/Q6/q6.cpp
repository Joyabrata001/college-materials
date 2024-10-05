#include <cstdlib>
#include <ctime>

#include <iostream>
using namespace std;

const int DEFAULT_SIZE = 10;
const int INCREMENT_SIZE = 10;
const int MAX_SIZE = 20;

template <typename T>
struct rsa
{
    int loc;
    int arr_size;
    int max_size;
    T *arr;
};

template <typename T>
bool initializeRSA(rsa<T> &r)
{
    r.loc = -1;
    r.arr_size = DEFAULT_SIZE - 1; //cause 0 indexed array
    r.arr = new T[DEFAULT_SIZE];
    r.max_size = MAX_SIZE - 1;

    if (r.arr == nullptr)
        return false;

    return true;
}

template <typename T>
bool inflate(rsa<T> &r, int extra_space)
{
    T *temp = new T[r.arr_size + extra_space];
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

template <typename T>
bool addElement(rsa<T> &r, T data)
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
template <typename T>
inline T fetchElement(rsa<T> r, int loc)
{
    return r.arr[loc];
}

//location should be based on a zero indexed array
template <typename T>
bool resetElements(rsa<T> &r, int given_index, int n)
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

template <typename T>
inline int getMaxSize(rsa<T> r)
{
    return r.max_size;
}

template <typename T>
inline int getCount(rsa<T> r)
{
    return r.loc;
}

template <typename T>
bool printAll(rsa<T> r)
{
    for (int i = 0; i < r.arr_size + 1; i++)
        cout << fetchElement(r, i) << " ";
    cout << endl;

    return true;
}

struct number
{
    int num;
};

int main()
{
    srand(time(0));

    rsa<float> r;

    cout << "Initializing \"float\" RSA with initial size " << DEFAULT_SIZE << " and max size " << MAX_SIZE << endl;
    cout << endl;
    if (!initializeRSA(r))
    {
        cout << "Error: Memory Allotment Error, Exiting" << endl;
        exit(1);
    }

    cout << "Adding 10 elements (no inflating takes place)" << endl;
    for (int i = 0; i < 10; i++)
        if (!addElement(r, (float)(rand() % 50) + (float)(rand() % 10) / 10))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    printAll(r);
    cout << endl;

    cout << "Adding 10 more elements (inflation will take place)" << endl;
    for (int i = 0; i < 10; i++)
        if (!addElement(r, (float)(rand() % 50) + (float)(rand() % 10) / 10))
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

    cout << "Max Size: " << getMaxSize(r) + 1 << endl;
    cout << "No. of elements: " << getCount(r) + 1 << endl;
    cout << endl
         << endl;

    number n;
    n.num = 0;

    rsa<number> b;

    cout << "Initializing \"struct number\" RSA with initial size " << DEFAULT_SIZE << " and max size " << MAX_SIZE << endl;
    cout << endl;
    if (!initializeRSA(b))
    {
        cout << "Error: Memory Allotment Error, Exiting" << endl;
        exit(1);
    }

    cout << "Adding 10 elements (no inflating takes place)" << endl;
    for (int i = 0; i < 10; i++)
    {
        n.num = rand() % 50;
        if (!addElement(b, n))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    }

    for (int i = 0; i < b.arr_size + 1; i++)
        cout << fetchElement(b, i).num << " ";
    cout << endl;
    cout << "Did Minor Change to display function."<<endl;


    char string[] = "abc";

    rsa<char *> c;

    cout << "Initializing \"char *\" RSA with initial size " << DEFAULT_SIZE << " and max size " << MAX_SIZE << endl;
    cout << endl;
    if (!initializeRSA(c))
    {
        cout << "Error: Memory Allotment Error, Exiting" << endl;
        exit(1);
    }

    cout << "Adding 10 elements (no inflating takes place)" << endl;
    for (int i = 0; i < 10; i++)
    {
        string[0] = (char)(rand() % (95 - 65) + 65);
        if (!addElement(c, string))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    }
    printAll(c);

    cout<<"All Same Values of char is expected as address of \'string\' is saved in rsa.arr"<<endl;

    cout << endl;

    return 0;
}