#include <iostream>
using namespace std;

#include <string.h>

class person
{
    char *name;
    int age;

public:
    person();
    person(char *, int);
    person &operator=(const person &);
    ~person();
    void write() const;
};

person::person() : name(NULL), age(-1)
{
    ;
}

person::person(char *n, int a) : age(a)
{
    name = new char[strlen(n) + 1];
    strcpy(name, n);
}

person &person::operator=(const person &rhs)
{
    name = new char[strlen(rhs.name) + 1];
    strcpy(name, rhs.name);
    age = rhs.age;
    return *this;
}

person::~person()
{
    delete name;
}

void person::write() const
{
    cout << name << " " << age << endl;
}

int main()
{
    char a[] = "abhiroop";
    person p(a, 53);

    // person q=p;
    // invokes copy contructor

    //invokes overloaded operator
    person q;
    q = p;

    q.write();
}
