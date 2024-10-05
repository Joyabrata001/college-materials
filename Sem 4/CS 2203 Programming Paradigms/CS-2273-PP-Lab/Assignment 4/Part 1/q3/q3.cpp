#include <iostream>
using namespace std;

#include <ctime>
#include <cstdlib>

class Shape
{
public:
    virtual void read() = 0;
    virtual double calc_area() = 0;
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
};

void Circle::read()
{
    cout << "Enter Radius: ";
    cin >> radius;
}

int main()
{
    srand(time(0));

    float sum_area = 0;
    int counter = 0;
    int num_rand;

    Shape *shape_ptr[10];

    num_rand = rand() % 2 + 1;

    for (int i = counter; i < counter + num_rand; i++)
    {
        shape_ptr[i] = new Triangle(rand() % 10 + 1, rand() % 10 + 1);
        sum_area += shape_ptr[i]->calc_area();
    }

    counter += num_rand;

    num_rand = rand() % 2 + 1;

    for (int i = counter; i < counter + num_rand; i++)
    {
        shape_ptr[i] = new Rectangle(rand() % 10 + 1, rand() % 10 + 1);
        sum_area += shape_ptr[i]->calc_area();
    }

    counter += num_rand;

    for (int i = counter; i < 10; i++)
    {
        shape_ptr[i] = new Circle(rand() % 10 + 1);
        sum_area += shape_ptr[i]->calc_area();
    }

    cout << "Sum of Areas: " << sum_area << endl;
    return 0;
}
