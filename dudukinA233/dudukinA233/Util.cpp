
#include "Util.h"
#include <cstdlib>
#include <cstdio>

using namespace std;


string ReadInput()
{
    string value;

    getline(cin, value);

    if (cin)
        cerr << value << '\n';

    return value;
}


int Get_number()
{
    int k;

    while (true)
    {
        if (cin >> k && cin.peek() == '\n' && k >= 0)
        {
            cerr << k << '\n';
            cin.ignore(10000, '\n');
            return k;
        }

        if (cin.eof())
            exit(1);

        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Wrong action" << endl;
    }
}

int Get_positive_numb()
{
    int k;

    while (true)
    {
        if (cin >> k && cin.peek() == '\n' && k > 0)
        {
            cerr << k << '\n';
            cin.ignore(10000, '\n');
            return k;
        }

        if (cin.eof())
            exit(1);

        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Wrong action" << endl;
    }
}

int Get_int_range(int min_value, int max_value)
{
    while (true)
    {
        int value = Get_number();

        if (value >= min_value && value <= max_value)
            return value;

        cout << "Wrong action. Enter from "
            << min_value << " to " << max_value << ": ";
    }
}

string Get_line()
{
    return ReadInput();
}

string Get_name()
{
    string name;

    while (true)
    {
        name = ReadInput();

        if (!name.empty())
            return name;

        cout << "Wrong action. Enter name" << endl;
    }
}

char Get_class_station()
{
    while (true)
    {
        string value = ReadInput();

        if (value.size() == 1 &&
            (value[0] == 'a' ||
                value[0] == 'b' ||
                value[0] == 'c'))
            return value[0];

        if (cin.eof())
            exit(1);

        cout << "Wrong action. Enter a, b or c" << endl;
    }
}

bool FilterPipe(const Pipe& p, const PipeFilter& f)
{
    bool name_ok = f.name.empty() ||
        p.Get_name().find(f.name) != string::npos;

    bool repair_ok = f.repair == 2 ||
        p.Is_repair() == (f.repair == 1);

    return name_ok && repair_ok;
}

bool FilterStation(const Station& s, const StationFilter& f)
{
    bool name_ok = f.name.empty() ||
        s.Get_name().find(f.name) != string::npos;

    double percent = s.Get_unused_percent();

    return name_ok &&
        percent >= f.min_percent &&
        percent <= f.max_percent;
}
