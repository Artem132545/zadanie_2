#include "Station.h"
#include "Util.h"

#include <iostream>
#include <string>

using namespace std;

int Station::Next_id_S = 1;

Station::Station() : id(Next_id_S++), Name(""),
count_workshops_all(0), count_in_work(0), class_station('a')
{
}

int Station::Get_id() const
{
    return id;
}

const string& Station::Get_name() const
{
    return Name;
}

double Station::Get_unused_percent() const
{
    if (count_workshops_all == 0)
        return 0.0;

    return 100.0 * (count_workshops_all - count_in_work)
        / count_workshops_all;
}

istream& operator>>(istream& in, Station& s)
{
    cout << "Enter station name: ";
    s.Name = Get_name();

    cout << "Total workshops: ";
    s.count_workshops_all = Get_positive_numb();

    cout << "Working workshops: ";
    s.count_in_work = Get_int_range(0, s.count_workshops_all);

    cout << "Station class (a, b, c): ";
    s.class_station = Get_class_station();

    return in;
}

ostream& operator<<(ostream& out, const Station& s)
{
    out << "Station ID: " << s.id << '\n'
        << "Name: " << s.Name << '\n'
        << "Total workshops: " << s.count_workshops_all << '\n'
        << "Working workshops: " << s.count_in_work << '\n'
        << "Class: " << s.class_station << '\n';

    return out;
}

void Station::Edit_S()
{
    cout << "New station name: ";
    Name = ::Get_name();

    cout << "Total workshops: ";
    count_workshops_all = Get_positive_numb();

    cout << "Working workshops: ";
    count_in_work = Get_int_range(0, count_workshops_all);

    cout << "Station class (a, b, c): ";
    class_station = Get_class_station();
}

void Station::SaveToFile(ostream& out) const
{
    out << "STATION\n"
        << id << '\n'
        << Name << '\n'
        << count_workshops_all << '\n'
        << count_in_work << '\n'
        << class_station << '\n';
}

bool Station::LoadFromFile(istream& file)
{
    file >> id;

    file.ignore(10000, '\n');

    getline(file, Name);

    file >> count_workshops_all >> count_in_work >> class_station;

    file.ignore(10000, '\n');

    return bool(file);
}

void Station::CalcMaxId(const unordered_map<int, Station>& css)
{
    Next_id_S = 1;

    for (const auto& [id, s] : css)
    {
        if (id >= Next_id_S)
            Next_id_S = id + 1;
    }
}
