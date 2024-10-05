#include <iostream>
using namespace std;
#include <cstring>

const int DEFAULT_STRING_SIZE = 20;
const int DEFAULT_ARR_SIZE = 3;

class Cricketer
{
protected:
    char name[DEFAULT_STRING_SIZE];
    char country[DEFAULT_ARR_SIZE][DEFAULT_STRING_SIZE];

public:
    Cricketer();
};

Cricketer::Cricketer() : name("\n")
{
    cout << "Enter Name: ";
    cin >> name;
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++)
        strcpy(country[i], "\n");
}

class Batsman : public virtual Cricketer
{
protected:
    unsigned int run[DEFAULT_ARR_SIZE];
    bool out[DEFAULT_ARR_SIZE];

public:
    Batsman();
};

Batsman::Batsman()
{
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++)
    {
        run[i] = 0;
        out[i] = false;
    }
}

class Bowler : virtual public Cricketer
{
protected:
    unsigned int wickets[DEFAULT_ARR_SIZE];

public:
    Bowler();
};

Bowler::Bowler()
{
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++)
        wickets[i] = 0;
}

class All_Rounder : public Batsman, public Bowler
{
public:
    void insert_match_wise_record();
    void display_batting_average();
    void display_total_wickets();
    void display_highest_wicket_country();
    void display_highest_run_country();
};

void All_Rounder::insert_match_wise_record()
{
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++)
    {
        cout << "Enter Enemy Country: ";
        cin >> country[i];

        cout << "Enter Runs Scored: ";
        cin >> run[i];

        cout << "Out or Not Out (0 or 1): ";
        cin >> out[i];

        cout << "Wickets taken: ";
        cin >> wickets[i];

        cout << endl;
    }
}

void All_Rounder::display_batting_average()
{
    float sum_runs = 0;
    float count = 0;
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++)
    {
        sum_runs += run[i];

        if (out[i] != true)
            count++;
    }

    if (count != 0)
        cout << "Batting Average: " << sum_runs / count << endl;
    else
        cout << "Player was not out in all match: division by zero" << endl;
}

void All_Rounder::display_total_wickets()
{
    int sum_wicket = 0;

    for (int i = 0; i < DEFAULT_ARR_SIZE; i++)
        sum_wicket += wickets[i];

    cout << "Total Wickets Taken: " << sum_wicket << endl;
}

void All_Rounder::display_highest_wicket_country()
{
    int index = 0;

    for (int i = 0; i < DEFAULT_ARR_SIZE; i++)
    {
        if (wickets[index] < wickets[i])
            index = i;
    }

    cout << "Highest Wickets " << wickets[index] << " against " << country[index] << endl;
}

void All_Rounder::display_highest_run_country()
{
    int index = 0;

    for (int i = 0; i < DEFAULT_ARR_SIZE; i++)
    {
        if (run[index] < run[i])
            index = i;
    }

    cout << "Highest Runs " << run[index] << " against " << country[index] << endl;
}


int main()
{
    All_Rounder a;
    a.insert_match_wise_record();
    a.display_batting_average();
    a.display_total_wickets();
    a.display_highest_wicket_country();
    a.display_highest_run_country();
    return 0;
}