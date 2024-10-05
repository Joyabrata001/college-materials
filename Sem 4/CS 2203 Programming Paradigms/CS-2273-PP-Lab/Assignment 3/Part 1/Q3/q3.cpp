#include <iostream>
using namespace std;

const int DEFAULT_SIZE = 10;
const int INCREMENT_SIZE = 10;
const int MAX_SIZE = 20;

template <typename T>
void print_generic(T a)
{
    cout << a;
}

template <typename T>
class rsa
{
    int loc;
    unsigned int arr_size;
    unsigned int max_size;
    T *arr;
    void (*printFn)(T a);

public:
    rsa(void (*printFunction)(T a) = print_generic, int arr_s = DEFAULT_SIZE, int max_s = MAX_SIZE);
    rsa(const rsa &rhs);
    rsa &operator=(const rsa &rhs);
    bool addElement(T data);
    bool inflate(int extra_space);
    bool resetElements(int given_index, int n);
    bool printAll() const;
    ~rsa();

    //location should be based on a zero indexed array
    T fetchElement(int loc) const
    {
        return arr[loc];
    }

    int getMaxSize() const
    {
        return max_size;
    }

    int getCount() const
    {
        return loc;
    }
};

template <typename T>
rsa<T>::rsa(void (*printFunction)(T a), int arr_s, int max_s )
{
    loc = -1;
    arr_size = arr_s - 1; //cause 0 indexed array
    arr = new T[arr_s];
    max_size = max_s - 1;
    printFn = printFunction;

    if (arr == NULL)
    {
        cout << "Error: Memory Allotment Error, Exiting" << endl;
        exit(1);
    }
}

template <typename T>
rsa<T>::rsa(const rsa<T> &rhs)
{
    loc = rhs.loc;
    arr_size = rhs.arr_size;
    max_size = rhs.max_size;
    printFn = rhs.printFn;
    arr = new T[arr_size];

    for (int i = 0; i <= arr_size; i++)
        arr[i] = rhs.arr[i];
}

template <typename T>
rsa<T> &rsa<T>::operator=(const rsa<T> &rhs)
{
    if (this == &rhs)
        return *this;

    delete arr;

    loc = rhs.loc;
    arr_size = rhs.arr_size;
    max_size = rhs.max_size;
    printFn = rhs.printFn;
    arr = new T[arr_size];

    for (int i = 0; i <= arr_size; i++)
        arr[i] = rhs.arr[i];

    return *this;
}

template <typename T>
rsa<T>::~rsa()
{
    cout << "Deleting following RSA..." << endl;
    printAll();
    cout << endl;

    delete arr;
}

template <typename T>
bool rsa<T>::inflate(int extra_space)
{
    T *temp = new T[arr_size + extra_space];
    arr_size += extra_space;
    if (temp == nullptr)
        return false;

    for (int i = 0; i <= arr_size; i++)
    {
        temp[i] = arr[i];
    }

    delete arr;
    arr = temp;
    return true;
}

template <typename T>
bool rsa<T>::addElement(T data)
{
    if (loc == arr_size)
    {
        if (arr_size == max_size)
        {
            return false;
        }
        else if (arr_size + INCREMENT_SIZE <= max_size)
            if (!inflate(INCREMENT_SIZE))
            {
                cout << "Error: Fail to inflate, exiting";
                exit(-1);
            }
            else if (!inflate(max_size - arr_size))
            {
                cout << "Error: Fail to inflate, exiting";
                exit(-1);
            }
    }

    loc++;
    arr[loc] = data;

    return true;
}

template <typename T>
bool rsa<T>::resetElements(int given_index, int n)
{
    if (arr_size < given_index + n)
        return false;

    int initial = given_index - 1;
    int final = given_index + n - 1;

    while (final <= arr_size)
    {
        arr[initial] = arr[final];
        initial++;
        final++;
    }

    loc = initial - 1;

    while (initial <= arr_size)
    {
        arr[initial] = 0;
        initial++;
    }

    return true;
}

template <typename T>
bool rsa<T>::printAll() const
{
    for (int i = 0; i < arr_size + 1; i++)
    { // cout << fetchElement(i) << " ";
        printFn(fetchElement(i));
        cout << " ";
    }
    cout << endl;

    return true;
}

struct num
{
    int a;
};

void print_num(num a)
{
    cout<<a.a;
}

int main()
{
    cout << "Initializing RSA with initial size " << DEFAULT_SIZE << " and  max size " << MAX_SIZE << endl;
    rsa<int> a;
    cout << endl;

    cout << "Adding 10 elements (no inflating takes place)" << endl;
    for (int i = 0; i < 10; i++)
        if (!a.addElement(i))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    a.printAll();
    cout << endl;

    cout << "Adding 10 more elements (inflation will take place)" << endl;
    for (int i = 0; i < 10; i++)
        if (!a.addElement(i + 10))
        {
            cout << "Error: Overflowing Max Size" << endl;
            exit(1);
        }
    a.printAll();
    cout << endl;

    cout << "Max Size: " << a.getMaxSize() + 1 << endl;
    cout << "No. of elements: " << a.getCount() + 1 << endl;
    cout << endl;

    {
        cout << "Making another RSA(b) having <char>" << endl;
        rsa<char> b;
        for (int i = 0; i < 20; i++)
            if (!b.addElement((char)(i + 65)))
            {
                cout << "Error: Overflowing Max Size" << endl;
                exit(1);
            }
        b.printAll();
        cout << endl;
    }

    {
        cout << "Making another RSA(b) of <float>" << endl;
        rsa<float> b;
        for (int i = 0; i < 20; i++)
        {
            float temp = (float)i * 0.1 + i;
            if (!b.addElement(temp))
            {
                cout << "Error: Overflowing Max Size" << endl;
                exit(1);
            }
        }
        b.printAll();
        cout << endl;
    }

    {
        cout << "Making another RSA(b) of <struct>" << endl;
        rsa<num> b(print_num);
        num temp;

        for (int i = 0; i < 20; i++)
        {
            temp.a = i+5;
            if (!b.addElement(temp))
            {
                cout << "Error: Overflowing Max Size" << endl;
                exit(1);
            }
        }
        b.printAll();
        cout << endl;
    }

    cout << "Making another RSA(c) using copy constructor of a..." << endl;

    rsa<int> c(a);
    c.printAll();
    cout << endl;

    cout << "Resetting Elements(c)(make their value 0) with given pos 5, and n as 5" << endl;
    if (!c.resetElements(5, 5))
    {
        cout << "Error: provided out of bound parameters" << endl;
    }
    c.printAll();
    cout << endl;

    cout << "Making another RSA(d) using \'=\' operator of a..." << endl;

    rsa<int> d = a;
    d.printAll();
    cout << endl;

    cout << "Resetting Elements(d)(make their value 0) with given pos 1, and n as 5" << endl;
    if (!d.resetElements(1, 5))
    {
        cout << "Error: provided out of bound parameters" << endl;
    }
    d.printAll();
    cout << endl;

    cout << endl
         << endl
         << endl;

    cout << "a..." << endl;
    a.printAll();
    cout << endl;

    cout << "c..." << endl;
    c.printAll();
    cout << endl;

    cout << "d..." << endl;
    d.printAll();
    cout << endl;

    return 0;
}