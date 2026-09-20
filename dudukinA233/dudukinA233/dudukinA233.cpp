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
Station Add_S()
{
    Station s;
    cout << "1. Name KS" << endl;
    cin >> s.Name;
    do {
        cout << "2. Enter workshops" << endl;
        cin >> s.count_workshops_all;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (cin.fail() || s.count_workshops_all <= 0);

    do {
        cout << "3. Enter workshops work" << endl;
        cin >> s.count_in_work;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (cin.fail() || s.count_in_work < 0 || s.count_in_work > s.count_workshops_all);

    do {
        cout << "4. Enter station indicator (a,b,c)" << endl;
        cin >> s.class_station;

    } while (s.class_station != 'a' && s.class_station != 'b' && s.class_station != 'c');
    return s;
}
void Edit_P(Pipe& p)
{
    int repair;                            // для функции сохранения сделать .  
    do {
        cout << "Status under repair (1 or 0)" << endl;
        cin >> repair;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }

    } while (cin.fail() || (repair != 0 && repair != 1));
    p.repair = repair;
}

void Edit_S(Station& s)
{
    int select;
    do {
        cout << "1. Start workshop" << endl;
        cout << "2. Stop workshop" << endl;
        cin >> select;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (cin.fail() || (select != 1 && select != 2));
    if (select == 1) {
        if (s.count_in_work < s.count_workshops_all) {
            s.count_in_work++;
            cout << "Workshop started" << endl;
        }
        else {
            cout << "All workshops are already working" << endl;
        }
    }
    else {
        if (s.count_in_work > 0) {
            s.count_in_work--;
            cout << "Workshop stopped" << endl;
        }
        else {
            cout << "There are no working workshops" << endl;
        }
    }
}
void Print_P(const Pipe& p)
{
    cout << "Kilometer marker: " << p.Name_KM << endl;
    cout << "Length: " << p.length << endl;
    cout << "Diameter: " << p.d << endl;
    cout << "Repair: " << p.repair << endl;
}

void Print_S(const Station& s)
{
    cout << "Name: " << s.Name << endl;
    cout << "Workshops: " << s.count_workshops_all << endl;
    cout << "Workshops work: " << s.count_in_work << endl;
    cout << "Station indicator: " << s.class_station << endl;
}
