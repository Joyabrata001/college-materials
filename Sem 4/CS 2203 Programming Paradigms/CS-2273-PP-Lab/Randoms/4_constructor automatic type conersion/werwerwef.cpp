#include <iostream>
using namespace std;

class one
{
public:
    one();
};

one::one()
{
    cout << "one made" << endl;
}

class two
{
public:
    two(const one &);
};

two::two(const one &o)
{
    cout << "two made" << endl;
}

void function(two t)
{
    cout<<"Got a two"<<endl;
}

int main()
{
    one o;

    function(o);

    return 0;
}
