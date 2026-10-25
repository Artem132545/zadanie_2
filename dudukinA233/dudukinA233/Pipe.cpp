#include "Pipe.h"
#include "Util.h"

#include <iostream>
#include <string>

using namespace std;

int Pipe::Next_id_P = 1;

Pipe::Pipe() : id(Next_id_P++), Name_KM(""), d(0), length(0), repair(false)
{
}

int Pipe::Get_id() const { return id; }
const string& Pipe::Get_name() const { return Name_KM; }
bool Pipe::Is_repair() const { return repair; }
void Pipe::Set_repair(bool value) { repair = value; }

istream& operator>>(istream& in, Pipe& p)
{
    cout << "Enter pipe name: ";
    p.Name_KM = Get_name();
    cout << "Enter pipe length: ";
    p.length = Get_positive_numb();
    cout << "Enter pipe diameter: ";
    p.d = Get_positive_numb();
    cout << "Under repair (0 - no, 1 - yes): ";
    p.repair = (Get_int_range(0, 1) == 1);
    return in;
}

ostream& operator<<(ostream& out, const Pipe& p)
{
    out << "Pipe P-" << p.id << '\n'
        << "Name: " << p.Name_KM << '\n'
        << "Length: " << p.length << '\n'
        << "Diameter: " << p.d << '\n'
        << "Under repair: " << (p.repair ? "yes" : "no") << '\n';
    return out;
}

Pipe Add_P()
{
    Pipe p;
    cin >> p;
    return p;
}

void Pipe::Edit_P()
{
    cout << "New pipe name: ";
    Name_KM = Get_name();
    cout << "New length: ";
    length = Get_positive_numb();
    cout << "New diameter: ";
    d = Get_positive_numb();
    cout << "Under repair (0 - no, 1 - yes): ";
    repair = (Get_int_range(0, 1) == 1);
}

void Pipe::SaveToFile(ostream& out) const
{
    out << "PIPE\n" << id << '\n' << Name_KM << '\n'
        << length << '\n' << d << '\n' << (repair ? 1 : 0) << '\n';
}

bool Pipe::LoadFromFile(istream& in, Pipe& p, int& loaded_id)
{
    string name;
    int new_length, new_d, new_repair;

    if (!(in >> loaded_id)) return false;
    in.ignore(10000, '\n');
    if (!getline(in, name)) return false;
    if (!(in >> new_length >> new_d >> new_repair)) return false;
    in.ignore(10000, '\n');

    if (loaded_id <= 0 || loaded_id > MAX_OBJECT_ID || name.empty() ||
        new_length <= 0 || new_d <= 0 ||
        (new_repair != 0 && new_repair != 1))
        return false;

    p.id = loaded_id;
    p.Name_KM = name;
    p.length = new_length;
    p.d = new_d;
    p.repair = (new_repair == 1);
    return true;
}
