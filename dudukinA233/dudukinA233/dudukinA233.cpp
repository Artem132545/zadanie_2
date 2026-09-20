#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Pipe
{
    string Name_KM;
    float length;
    float d;
    bool repair;
};

struct Station
{
    string Name;
    int count_workshops_all;
    int count_in_work;
    char class_station;             // (a,b,c)
};
Pipe Add_P()
{
    Pipe p;
    cout << "1.Kilometer marker" << endl;
    cin >> p.Name_KM;
    do {
        cout << "2.enter length" << endl;
        cin >> p.length;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (cin.fail() || p.length <= 0);

    do {
        cout << "3. enter diametr pipe" << endl;
        cin >> p.d;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (cin.fail() || p.d <= 0);
    int repair;
    do
    {
        cout << "4. Status under repair (1 or 0)" << endl;
        cin >> repair;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }

    } while (cin.fail() || (repair != 0 && repair != 1));

    p.repair = repair;


    return p;
}