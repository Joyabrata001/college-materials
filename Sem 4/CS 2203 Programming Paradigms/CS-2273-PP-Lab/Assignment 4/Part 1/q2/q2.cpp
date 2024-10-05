#include <iostream>
using namespace std;
#include <string.h>

const int DEFAULT_STRING_SIZE = 10;

class Person
{
    char name[DEFAULT_STRING_SIZE];
    unsigned int age;
    char gender;

public:
    Person() : name("\n"), age(0), gender('-') {}
    Person(const char *given_name, unsigned int given_age, char given_gender) : age(given_age), gender(given_gender)
    {
        strcpy(name, given_name);
    }
    void read_data();
    void display_data();
};

void Person::read_data()
{
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Gender (single char only): ";
    cin >> gender;
}

void Person::display_data()
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
}

class Academic : virtual public Person
{
    char department[DEFAULT_STRING_SIZE];

public:
    Academic() : department("\n") {}
    Academic(const char *given_name, unsigned int given_age, char given_gender, const char *given_dept) : Person(given_name, given_age, given_gender)
    {
        strcpy(department, given_dept);
    }
    void read_data();
    void display_data();
    const char *return_department()
    {
        return department;
    }
    void read_department()
    {
        cout << "Enter Department: ";
        cin >> department;
    }
};

void Academic::read_data()
{
    Person::read_data();
    read_department();
}

void Academic::display_data()
{
    Person::display_data();
    cout << "Department: " << department << endl;
}

class Professional : virtual public Person
{
    double salary;

public:
    Professional() : salary(0) {}
    Professional(const char *given_name, unsigned int given_age, char given_gender, const double given_salary) : Person(given_name, given_age, given_gender), salary(given_salary) {}
    void read_data();
    void display_data();
    double return_salary()
    {
        return salary;
    }
    void read_salary()
    {
        cout << "Enter Salary: ";
        cin >> salary;
    }
};

void Professional::read_data()
{
    Person::read_data();
    read_salary();
}

void Professional::display_data()
{
    Person::display_data();
    cout << "Salary: " << salary << endl;
}

class Student : public Academic
{
    unsigned int year;

public:
    Student() : year(0) {}
    Student(const char *given_name, unsigned int given_age, char given_gender, const char *given_dept, const unsigned int given_year) : Academic(given_name, given_age, given_gender, given_dept), year(given_year), Person(given_name, given_age, given_gender) {}
    void read_data();
    void display_data();
};

void Student::read_data()
{
    Academic::read_data();
    cout << "Enter Year: ";
    cin >> year;
}

void Student::display_data()
{
    Academic::display_data();
    cout << "Year: " << year << endl;
}

class Clerk : public Professional
{
    char workLoad[DEFAULT_STRING_SIZE];

public:
    Clerk() : workLoad("\n") {}
    Clerk(const char *given_name, unsigned int given_age, char given_gender, const double given_salary, const char *given_work) : Professional(given_name, given_age, given_gender, given_salary), Person(given_name, given_age, given_gender)
    {
        strcpy(workLoad, given_work);
    }
    void read_data();
    void display_data();
};

void Clerk::read_data()
{
    Professional::read_data();
    cout << "Enter Work-Load: ";
    cin >> workLoad;
}

void Clerk::display_data()
{
    Professional::display_data();
    cout << "Work-Load: " << workLoad << endl;
}

class Professor : public Professional, public Academic
{
    char courseLoad[DEFAULT_STRING_SIZE];

public:
    Professor() : courseLoad("\n") {}
    Professor(const char *name, unsigned int age, char gender, const char *department, const char *given_courseLoad, double salary) : Professional(name, age, gender, salary), Academic(name, age, gender, department), Person(name, age, gender)
    {
        strcpy(courseLoad, given_courseLoad);
    }
    void display_data();
    void read_data();
};

void Professor::display_data()
{
    Person::display_data();
    cout << "Department: " << Academic::return_department() << endl;
    cout << "Course-Load: " << courseLoad << endl;
    cout << "Salary: " << Professional::return_salary() << endl;
}

void Professor::read_data()
{
    Person::read_data();
    Academic::read_department();
    Professional::read_salary();
    cout<<"Enter Course-Load: ";
    cin>>courseLoad;
}

int main()
{
    Student s("Abhiroop",18,'M',"CST",2023);
    s.display_data();
    cout<<endl;

    Clerk c("Seele",23,'F',200000,"Paperwork");
    c.display_data();
    cout<<endl;

    Professor p;
    p.read_data();
    p.display_data();
}
