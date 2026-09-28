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
    char class_station;
};

// Ввод положительного числа
int Get_positive_numb()
{
    int k;

    while (1)
    {
        if (cin >> k && cin.peek() == '\n' && k > 0)
        {
            return k;
        }
        else
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Wrong action" << endl;
        }
    }
}

int Get_number()
{
    int k;

    while (1)
    {
        if (cin >> k && cin.peek() == '\n' && k >= 0)
        {
            return k;
        }
        else
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Wrong action" << endl;
        }
    }
}

Pipe Add_P()
{
    Pipe p;

    cout << "1.Kilometer marker" << endl;
    cin >> p.Name_KM;

    cout << "2.enter length" << endl;
    p.length = Get_positive_numb();

    cout << "3. enter diametr pipe" << endl;
    p.d = Get_positive_numb();

    cout << "4. Status under repair (1 or 0)" << endl;

    int repair;

    while (1)
    {
        repair = Get_number();

        if (repair == 0 || repair == 1)
            break;

        cout << "Wrong action. Enter 0 or 1" << endl;
    }

    p.repair = repair;

    return p;
}

Station Add_S()
{
    Station s;

    cout << "1. Name KS" << endl;
    cin >> s.Name;

    cout << "2. Enter workshops" << endl;
    s.count_workshops_all = Get_positive_numb();

    cout << "3. Enter workshops work" << endl;

    while (1)
    {
        s.count_in_work = Get_number();

        if (s.count_in_work >= 0 &&
            s.count_in_work <= s.count_workshops_all)
        {
            break;
        }

        cout << "Wrong action. Enter value from 0 to "
            << s.count_workshops_all << endl;
    }

    cout << "4. Enter station indicator (a,b,c)" << endl;

    while (1)
    {
        cin >> s.class_station;

        if (cin.peek() == '\n' &&
            (s.class_station == 'a' ||
                s.class_station == 'b' ||
                s.class_station == 'c'))
        {
            break;
        }

        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Wrong action. Enter a, b or c" << endl;
    }

    return s;
}

void Edit_P(Pipe& p)
{
    int repair;

    cout << "Status under repair (1 or 0)" << endl;

    while (1)
    {
        repair = Get_number();

        if (repair == 0 || repair == 1)
            break;

        cout << "Wrong action. Enter 0 or 1" << endl;
    }

    p.repair = repair;
}

void Edit_S(Station& s)
{
    int select;

    cout << "1. Start workshop" << endl;
    cout << "2. Stop workshop" << endl;

    while (1)
    {
        select = Get_positive_numb();

        if (select == 1 || select == 2)
            break;

        cout << "Wrong action. Enter 1 or 2" << endl;
    }

    if (select == 1)
    {
        if (s.count_in_work < s.count_workshops_all)
        {
            s.count_in_work++;
            cout << "Workshop started" << endl;
        }
        else
        {
            cout << "All workshops are already working" << endl;
        }
    }
    else
    {
        if (s.count_in_work > 0)
        {
            s.count_in_work--;
            cout << "Workshop stopped" << endl;
        }
        else
        {
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


void Save(const Pipe& p, const Station& s,
    bool pipe_exists, bool station_exists)
{
    ofstream file("data.txt");

    if (!file.is_open())
    {
        cout << "File opening error" << endl;
        return;
    }

    if (pipe_exists)
    {
        file << "PIPE" << endl;
        file << p.Name_KM << endl;
        file << p.length << endl;
        file << p.d << endl;
        file << p.repair << endl;
    }

    if (station_exists)
    {
        file << "STATION" << endl;
        file << s.Name << endl;
        file << s.count_workshops_all << endl;
        file << s.count_in_work << endl;
        file << s.class_station << endl;
    }

    file.close();

    cout << "Data saved" << endl;
}


void Download(Pipe& p, Station& s,
    bool& pipe_exists, bool& station_exists)
{
    ifstream file("data.txt");

    if (!file.is_open())
    {
        cout << "Data file not found" << endl;
        return;
    }

    string type;

    while (file >> type)
    {
        if (type == "PIPE")
        {
            Pipe p1;

            if (!(file >> p1.Name_KM))
            {
                cout << "Incorrect pipe Name" << endl;
                break;
            }

            if (!(file >> p1.length))
            {
                cout << "Incorrect pipe length" << endl;
                break;
            }

            if (!(file >> p1.d))
            {
                cout << "Incorrect pipe diametr" << endl;
                break;
            }

            if (!(file >> p1.repair))
            {
                cout << "Incorrect pipe repair" << endl;
                break;
            }

            if (p1.length <= 0 || p1.d <= 0)
            {
                cout << "Incorrect pipe length or diametr" << endl;
                break;
            }

            p = p1;
            pipe_exists = true;
        }

        else if (type == "STATION")
        {
            Station s1;

            if (!(file >> s1.Name))
            {
                cout << "Incorrect station Name" << endl;
                break;
            }

            if (!(file >> s1.count_workshops_all))
            {
                cout << "Incorrect station workshops" << endl;
                break;
            }

            if (!(file >> s1.count_in_work))
            {
                cout << "Incorrect station workshops in work" << endl;
                break;
            }

            if (!(file >> s1.class_station))
            {
                cout << "Incorrect class station" << endl;
                break;
            }

            if (s1.count_workshops_all <= 0 ||
                s1.count_in_work < 0 ||
                s1.count_in_work > s1.count_workshops_all)
            {
                cout << "Incorrect station workshops" << endl;
                break;
            }

            if (s1.class_station != 'a' &&
                s1.class_station != 'b' &&
                s1.class_station != 'c')
            {
                cout << "Incorrect class station" << endl;
                break;
            }

            s = s1;
            station_exists = true;
        }
    }

    file.close();

    if (pipe_exists)
        cout << "Pipe downloaded" << endl;

    if (station_exists)
        cout << "Station downloaded" << endl;
}


void Menu()
{
    cout << "1.Add pipe" << endl;
    cout << "2.Add Station" << endl;
    cout << "3.View all objects" << endl;
    cout << "4.Edit pipe" << endl;
    cout << "5.Edit Station" << endl;
    cout << "6.Save" << endl;
    cout << "7.Download" << endl;
    cout << "0.Exit" << endl;
}


int main()
{
    Pipe p1;
    Station s1;

    bool pipe_exists = false;
    bool station_exists = false;

    while (1)
    {
        Menu();

        switch (Get_positive_numb())
        {
        case 1:
        {
            p1 = Add_P();
            pipe_exists = true;
            break;
        }

        case 2:
        {
            s1 = Add_S();
            station_exists = true;
            break;
        }

        case 3:
        {
            cout << "View objects" << endl;
            cout << endl;

            if (pipe_exists)
            {
                cout << "1. Pipe" << endl;
                Print_P(p1);
            }
            else
            {
                cout << "Pipe does not exist" << endl;
            }

            cout << endl;

            if (station_exists)
            {
                cout << "2. Station" << endl;
                Print_S(s1);
            }
            else
            {
                cout << "Station does not exist" << endl;
            }

            break;
        }

        case 4:
        {
            if (pipe_exists)
                Edit_P(p1);
            else
                cout << "Pipe does not exist" << endl;

            break;
        }

        case 5:
        {
            if (station_exists)
                Edit_S(s1);
            else
                cout << "Station does not exist" << endl;

            break;
        }

        case 6:
        {
            Save(p1, s1, pipe_exists, station_exists);
            break;
        }

        case 7:
        {
            Download(p1, s1, pipe_exists, station_exists);
            break;
        }

        case 0:
        {
            return 0;
        }

        default:
        {
            cout << "Wrong action" << endl;
        }
        }
    }

    return 0;
}