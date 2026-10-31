
#include "Pipe.h"
#include "Util.h"

using namespace std;

int Pipe::NextId = 1;

Pipe::Pipe()
{
    id = NextId++;
}

int Pipe::getID() const
{
    return id;
}

string Pipe::getName() const
{
    return name;
}

bool Pipe::getUnderRepair() const
{
    return underRepair;
}

void Pipe::editUnderRepair()
{
    underRepair = !underRepair;
}

istream& operator>>(istream& in, Pipe& p)
{
    readValidName(p.name, "Enter pipe name: ");

    readValidNumber(p.length, "Enter pipe length: ", 1.0);

    readValidNumber(p.diameter, "Enter pipe diameter: ", 1);

    readValidNumber(p.underRepair, "Under repair (0 - no, 1 - yes): ", false, true);

    return in;
}

ifstream& operator>>(ifstream& inF, Pipe& p)
{
    int savedID;

    inF >> savedID;
    inF.ignore(10000, '\n');

    getline(inF, p.name);

    inF >> p.length >> p.diameter >> p.underRepair;

    return inF;
}

ostream& operator<<(ostream& out, const Pipe& p)
{
    out << "Pipe ID: " << p.id << '\n'
        << "Name: " << p.name << '\n'
        << "Length: " << p.length << '\n'
        << "Diameter: " << p.diameter << '\n'
        << "Under repair: "
        << (p.underRepair ? "yes" : "no") << '\n';

    return out;
}

ofstream& operator<<(ofstream& outF, const Pipe& p)
{
    outF << p.id << '\n'
        << p.name << '\n'
        << p.length << '\n'
        << p.diameter << '\n'
        << p.underRepair << '\n';

    return outF;
}
