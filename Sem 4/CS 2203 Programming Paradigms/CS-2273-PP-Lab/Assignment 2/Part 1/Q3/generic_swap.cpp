#include <iostream>
using namespace std;

template <typename T>
void generic_swap(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}

struct numbers
{
    float decimal;
    int number;
};

void print_data(numbers n)
{
    cout << "Decimal:  " << n.decimal << endl;
    cout << "Integer: " << n.number << endl;
}

int main()
{

    cout << "Testing int" << endl;
    int a = 1;
    int b = 2;
    cout << "Original Values: " << a << " " << b << endl;
    cout << "Swapping ..." << endl;
    generic_swap(a, b);
    cout << "Swapped Values: " << a << " " << b << endl
         << endl;

    cout << "Testing short" << endl;
    short c = 3;
    short d = 4;
    cout << "Original Values: " << c << " " << d << endl;
    cout << "Swapping ..." << endl;
    generic_swap(c, d);
    cout << "Swapped Values: " << c << " " << d << endl
         << endl;

    cout << "Testing float" << endl;
    float e = 5;
    float f = 6;
    cout << "Original Values: " << e << " " << f << endl;
    cout << "Swapping ..." << endl;
    generic_swap(e, f);
    cout << "Swapped Values: " << e << " " << f << endl
         << endl;

    cout << "Testing double" << endl;
    double g = 7;
    double h = 8;
    cout << "Original Values: " << g << " " << h << endl;
    cout << "Swapping ..." << endl;
    generic_swap(g, h);
    cout << "Swapped Values: " << g << " " << h << endl
         << endl;

    cout << "Testing struct" << endl;
    numbers n1;
    n1.decimal = 5;
    n1.number = 10;
    
    numbers n2;
    n2.decimal = 6;
    n2.number = 11;
   
    cout << "Original Values: " << endl;
    print_data(n1);
    cout << endl;
    print_data(n2);
    cout<<endl;

    cout << "Swapping ..." << endl;
    generic_swap(n1, n2);

    cout << "Swapped Values: " << endl;
    print_data(n1);
    cout << endl;
    print_data(n2);

    return 0;
}