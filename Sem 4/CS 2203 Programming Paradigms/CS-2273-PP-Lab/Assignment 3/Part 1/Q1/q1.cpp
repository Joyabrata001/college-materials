#include <iostream>
using namespace std;

#include <fstream>
#include <cstring>

const int NAME_SIZE = 20;
const int DEPT_NAME_SIZE = 5;

class student
{
    char name[NAME_SIZE];
    int age;
    char department[DEPT_NAME_SIZE];
    int year_grad;

public:
    void readStudentData(ifstream &fin);
    void readStudentData();
    void printStudentData() const;
};

void student::readStudentData(ifstream &fin)
{
    fin.getline(name, NAME_SIZE);
    fin >> age >> department >> year_grad;
    fin.ignore(); //ignore newline
}

void student::readStudentData()
{
    cout << "Enter Student's Name: ";
    cin.getline(name, NAME_SIZE);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Department (Abbv.): ";
    cin >> department;
    cout << "Enter Year of Graduation: ";
    cin >> year_grad;
    cin.ignore(); //ignore newline
}

void student::printStudentData() const
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Department: " << department << endl;
    cout << "Year of Graduation: " << year_grad << endl;
}

int main()
{
    cout << "Enter Number of Record to be added: ";
    int n;
    cin >> n;
    cin.ignore(); //ignore newline
    cout << endl;

    student s[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter Detail of Student " << i + 1 << ":" << endl;
        s[i].readStudentData();
        cout << endl;
    }

    cout << "Output: " << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Data of Student " << i + 1 << ":" << endl;
        s[i].printStudentData();
        cout << endl;
    }

    char filename[] = "./data.txt";

    ifstream fin;
    fin.open(filename, ios::in);

    cout << "Input through " << filename << endl;
    student a[2];
    int i = 0;

    while(!fin.eof())
    {
        a[i].readStudentData(fin);
        i++;
    }

    cout << "Data of Student"
         << ":" << endl;

    for (int i = 0; i < 2; i++)
    {
        a[i].printStudentData();
    }

    cout << endl;

    fin.close();
    return 0;
}