#include <iostream>
#include <fstream>
using namespace std;

const int NAME_SIZE = 20;
const int DEPT_SIZE = 5;

struct student
{
    char name[NAME_SIZE];
    int age;
    char department[DEPT_SIZE];
    int year_grad;
};

void readStudentData(student &s, char *filename)
{
    ifstream fin;

    fin.open(filename, ios::in);

    fin.getline(s.name, NAME_SIZE);

    fin >> s.age >> s.department >> s.year_grad;

    fin.close();
}

void readStudentData(student &s)
{
    cout << "Enter Student's Name: ";
    cin.getline(s.name, NAME_SIZE);
    cout << "Enter Age: ";
    cin >> s.age;
    cout << "Enter Department (Abbv.): ";
    cin >> s.department;
    cout << "Enter Year of Graduation: ";
    cin >> s.year_grad;
    cin.ignore(); //ignore newline
}

void printStudentData(student s)
{
    cout << "Name: " << s.name << endl;
    cout << "Age: " << s.age << endl;
    cout << "Department: " << s.department << endl;
    cout << "Year of Graduation: " << s.year_grad << endl;
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
        readStudentData(s[i]);
        cout << endl;
    }

    cout << "Output: " << endl
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Data of Student " << i + 1 << ":" << endl;
        printStudentData(s[i]);
        cout << endl;
    }

    char filename[] = "./Q1/data.txt";
    cout << "Input through " << filename << endl;
    student a[n];

    for (int i = 0; i < n; i++)
        readStudentData(a[i], filename);

    for (int i = 0; i < n; i++)
    {
        cout << "Data of Student " << i + 1 << ":" << endl;
        printStudentData(a[i]);
        cout << endl;
    }

    return 0;
}