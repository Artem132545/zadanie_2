#include "Network.h"
#include <iostream>
#include <fstream>
#include "Util.h"

using namespace std;

Network::Network()
{
    nextPipeID = 1;
    nextStationID = 1;
}

bool checkByRepair(const Pipe& p, bool underRepair)
{
    return p.getUnderRepair() == underRepair;
}

bool checkLessWorkshops(const Station& s, double percent)
{
    return s.getUnusedWorkshops() < percent;
}

bool checkMoreWorkshops(const Station& s, double percent)
{
    return s.getUnusedWorkshops() > percent;
}


void Network::AddPipe()
{
    Pipe p(nextPipeID++);

    cin >> p;

    int id = p.getID();

    pipes.emplace(id, p);

    cout << "Pipe added. ID: " << id << '\n';
}



void Network::AddStation()
{
    Station s(nextStationID++);

    cin >> s;

    int id = s.getID();

    stations.emplace(id, s);

    cout << "Station added. ID: " << id << '\n';
}


void Network::ViewAll() const
{
    cout << "\nPIPES:\n";

    if (pipes.empty())
        cout << "No pipes\n";

    for (const auto& item : pipes)
        cout << item.second << '\n';

    cout << "STATIONS:\n";

    if (stations.empty())
        cout << "No stations\n";

    for (const auto& item : stations)
        cout << item.second << '\n';
}

void Network::EditPipe()
{
    if (pipes.empty())
    {
        cout << "No pipes\n";
        return;
    }

    PrintID(pipes);

    int id;
    readNumber(id, "Enter pipe ID: ", 1);

    auto it = pipes.find(id);

    if (it == pipes.end())
    {
        cout << "Pipe not found\n";
        return;
    }

    cin >> it->second;

    cout << "Pipe edited\n";
}

void Network::EditStation()
{
    if (stations.empty())
    {
        cout << "No stations\n";
        return;
    }

    PrintID(stations);

    int id;
    readNumber(id, "Enter station ID: ", 1);

    auto it = stations.find(id);

    if (it == stations.end())
    {
        cout << "Station not found\n";
        return;
    }

    cin >> it->second;

    cout << "Station edited\n";
}

void Network::DeletePipe()
{
    if (pipes.empty())
    {
        cout << "No pipes\n";
        return;
    }

    PrintID(pipes);

    int id;
    readNumber(id, "Enter pipe ID: ", 1);

    if (pipes.erase(id))
        cout << "Pipe deleted\n";
    else
        cout << "Pipe not found\n";
}

void Network::DeleteStation()
{
    if (stations.empty())
    {
        cout << "No stations\n";
        return;
    }

    PrintID(stations);

    int id;
    readNumber(id, "Enter station ID: ", 1);

    if (stations.erase(id))
        cout << "Station deleted\n";
    else
        cout << "Station not found\n";
}

vector<int> Network::FindPipes()
{
    vector<int> found;

    if (pipes.empty())
    {
        cout << "No pipes\n";
        return found;
    }

    int choice;

    readNumber(choice,"Find pipes by 1 - name, 2 - repair: ", 1, 2);

    if (choice == 1)
    {
        string name;
        readName(name, "Part of pipe name: ");

        found = findAndOutputObjectsByFilter(pipes, checkByName<Pipe>, name);
    }
    else
    {
        bool repair;

        readNumber(repair,"Under repair (0 - no, 1 - yes): ", false, true);

        found = findAndOutputObjectsByFilter(pipes, checkByRepair, repair);
    }

    cout << "Found pipes: " << found.size() << '\n';

    return found;
}


vector<int> Network::FindStations()
{
    vector<int> found;

    if (stations.empty())
    {
        cout << "No stations\n";
        return found;
    }

    int choice;

    readNumber(choice,"Find stations by 1 - name, 2 - unused percent: ", 1, 2);

    if (choice == 1)
    {
        string name;

        readName(name, "Part of station name: ");

        found = findAndOutputObjectsByFilter(stations, checkByName<Station>, name);
    }
    else
    {
        double percent;

        readNumber(percent,"Enter unused workshops percent (0-100): ", 0.0, 100.0);

        int comparison;

        readNumber(comparison,"1 - less than entered percent, 2 - more than entered percent: ",1, 2);

        if (comparison == 1)
        {
            found = findAndOutputObjectsByFilter(
                stations, checkLessWorkshops, percent);
        }
        else
        {
            found = findAndOutputObjectsByFilter(
                stations, checkMoreWorkshops, percent);
        }
    }

    cout << "Found stations: " << found.size() << '\n';

    return found;
}


void Network::SearchPipes()
{
    FindPipes();
}

void Network::SearchStations()
{
    FindStations();
}

void Network::BatchOperation(const vector<int>& ids)
{
    int action;

    readNumber(action,"1 - delete, 2 - toggle repair: ", 1, 2);

    if (action == 1)
    {
        deleteObjectsByFilter(pipes, ids);

        cout << "Pipes deleted\n";
    }
    else
    {
        for (int id : ids)
            pipes.at(id).editUnderRepair();

        cout << "Pipes edited\n";
    }
}

void Network::BatchEditPipes()
{
    vector<int> found = FindPipes();

    if (found.empty())
        return;

    int choice;

    readNumber(choice, "1 - all found, 2 - specific IDs, 0 - cancel: ", 0, 2);

    if (choice == 0)
        return;

    vector<int> chosen;

    if (choice == 1)
        chosen = found;
    else
        chosen = inputSpecificIDs(found);

    if (chosen.empty())
        return;

    BatchOperation(chosen);
}



bool Network::Save(const string& filename) const
{
    ofstream file(filename);

    if (!file)
        return false;

    for (const auto& item : pipes)
    {
        file << "PIPE\n";
        file << item.second;
    }

    for (const auto& item : stations)
    {
        file << "STATION\n";
        file << item.second;
    }

    file << "NEXT_PIPE_ID\n";
    file << nextPipeID << '\n';

    file << "NEXT_STATION_ID\n";
    file << nextStationID << '\n';

    file.close();

    return file.good();
}



bool Network::Load(const string& filename)
{
    ifstream file(filename);

    if (!file)
        return false;

    pipes.clear();
    stations.clear();

    string type;

    while (getline(file, type))
    {
        if (type == "PIPE")
        {
            int savedID;

            file >> savedID;
            file.ignore(10000, '\n');

            Pipe p(savedID);
            file >> p;
            file.ignore(10000, '\n');

            pipes.emplace(p.getID(), p);

            if (savedID >= nextPipeID)
                nextPipeID = savedID + 1;
        }
        else if (type == "STATION")
        {
            int savedID;

            file >> savedID;
            file.ignore(10000, '\n');

            Station s(savedID);
            file >> s;
            file.ignore(10000, '\n');

            stations.emplace(s.getID(), s);

            if (savedID >= nextStationID)
                nextStationID = savedID + 1;
        }
        else if (type == "NEXT_PIPE_ID")
        {
            int savedNextID;

            file >> savedNextID;
            file.ignore(10000, '\n');

            if (savedNextID > nextPipeID)
                nextPipeID = savedNextID;
        }
        else if (type == "NEXT_STATION_ID")
        {
            int savedNextID;

            file >> savedNextID;
            file.ignore(10000, '\n');

            if (savedNextID > nextStationID)
                nextStationID = savedNextID;
        }
    }

    return true;
}


void Network::SaveInteractive() const
{
    string filename;

    readName(filename, "Filename to save: ");

    if (Save(filename))
        cout << "Data saved\n";
    else
        cout << "File saving error\n";
}

void Network::LoadInteractive()
{
    string filename;

    readName(filename, "Filename to load: ");

    if (Load(filename))
        cout << "Data loaded\n";
    else
        cout << "File loading error\n";
}
