#include <iostream>
using namespace std;

class abc{
    int a;
    char name[10];
    float f;
    double d;
    struct assad
    {
        char dept[10];
    };
    
};

int main()
{
    // //difference is exactly 4 as its array
    // int *ptr;
    // ptr = new int[10];

    // cout << "sizeof(int) = " << sizeof(int) << endl;

    // for (int i = 0; i < 10; i++)
    // {
    //     cout << &ptr[i] << endl;
    // }


    //32 bytes difference
    for (int i = 0; i < 10; i++)
    {
        
        int *ptr = new int;
        cout << ptr << endl;
    }


    // //48 bytes difference
    // cout << "sizeof(abc) = " << sizeof(abc) << endl;
    // for (int i = 0; i < 10; i++)
    // {
        
    //     abc *ptr = new abc;
    //     cout << ptr << endl;
    // }
}