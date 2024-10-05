#include <iostream>
using namespace std;

#include <ctime>
#include <cstdlib>

class Shape
{
public:
    virtual void read() = 0;
    virtual double calc_area() = 0;
    virtual void display() = 0;
};

class Triangle : public Shape
{
    double base;
    double height;

public:
    Triangle() : base(0), height(0) {}
    Triangle(const double given_base, const double given_height) : base(given_base), height(given_height) {}
    double calc_area()
    {
        return 0.5 * base * height;
    }
    void read();
    void display()
    {
        cout << "Triangle: Base " << base << " Height: " << height << endl;
    }
};

void Triangle::read()
{
    cout << "Enter Base: ";
    cin >> base;
    cout << "Enter Height: ";
    cin >> height;
}

class Rectangle : public Shape
{
    double length;
    double breadth;

public:
    Rectangle() : length(0), breadth(0) {}
    Rectangle(const double given_length, const double given_breadth) : length(given_length), breadth(given_breadth) {}
    double calc_area()
    {
        return length * breadth;
    }
    void read();
    void display()
    {
        cout << "Rectangle: Length: " << length << " Breadth: " << breadth << endl;
    }
};
void Rectangle::read()
{
    cout << "Enter Length: ";
    cin >> length;
    cout << "Enter Breadth: ";
    cin >> breadth;
}

const double pi = 3.14159;

class Circle : public Shape
{
    double radius;

public:
    Circle() : radius(0) {}
    Circle(const double given_radius) : radius(given_radius) {}
    double calc_area()
    {
        return pi * radius * radius;
    }
    void read();
    void display()
    {
        cout << "Circle: Radius: " << radius << endl;
    }
};

void Circle::read()
{
    cout << "Enter Radius: ";
    cin >> radius;
}

const int DEFAULT_STACK_SIZE = 10;

class ShapeStack
{
    Shape *stack[DEFAULT_STACK_SIZE] = {NULL};
    double total_area;
    int pos;

public:
    ShapeStack() : total_area(0), pos(0) {}
    void push();
    void pop();
    //pos will be 0 indexed
    void display(const int pos);
    void displayAll();
    double TotalAreaCovered()
    {
        return total_area;
    }
};

void ShapeStack::push()
{
    if (pos == DEFAULT_STACK_SIZE - 1)
    {
        cout << "Error: Stack is Full" << endl;
        return;
    }

    cout << "Enter Shape:" << endl
         << "1) Triangle" << endl
         << "2) Rectangle" << endl
         << "3) Circle" << endl
         << "Input: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        stack[pos] = new Triangle;
        stack[pos]->read();
        total_area += stack[pos]->calc_area();
        break;
    case 2:
        stack[pos] = new Rectangle;
        stack[pos]->read();
        total_area += stack[pos]->calc_area();
        break;
    case 3:
        stack[pos] = new Circle;
        stack[pos]->read();
        total_area += stack[pos]->calc_area();
        break;

    default:
        cout << "Error Wrong Option!!" << endl;
        return;
        break;
    }
    pos++;
}

void ShapeStack::display(const int pos)
{
    if (pos >= DEFAULT_STACK_SIZE || pos < 0)
        cout << "Error: Given Position Out of bounds" << endl;
    else if (stack[pos] == NULL)
        cout << "Error: Position's data is NULL" << endl;
    else
        stack[pos]->display();
}

void ShapeStack::displayAll()
{
    int temp = 0;
    while (stack[temp] != NULL)
    {
        stack[temp]->display();
        temp++;
    }
}

void ShapeStack::pop()
{
    cout << "Following Shape will be deleted: " << endl;
    stack[pos - 1]->display();
    cout << "Are You Sure you want to pop?(y,n): ";
    char choice;
    cin >> choice;

    switch (choice)
    {
    case 'y':
        delete stack[pos - 1];
        stack[pos - 1] = NULL;
        pos--;
        break;
    default:
        cout << "Not Deleted!!" << endl;
        break;
    }
}

int main()
{
    ShapeStack s;
    s.push();
    s.push();
    s.push();
    s.displayAll();
    s.pop();
    s.displayAll();
    cout << "Area: " << s.TotalAreaCovered();

    return 0;
}
