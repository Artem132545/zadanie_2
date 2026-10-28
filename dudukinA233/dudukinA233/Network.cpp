#include "Network.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<set>

using namespace std;


void Network::AddPipe()
{
    Pipe p;
    cin >> p;
    int id = p.Get_id();

    pipes.emplace(id, p);

    cout << "Pipe added. ID: " << id << '\n';
}

void Network::AddStation()
{
    Station s;
    cin >> s;
    int id = s.Get_id();

    stations.emplace(id, s);

    cout << "Station added. ID: " << id << '\n';
}

void Network::ViewAll()
{
    cout << "\nPIPES:\n";

    if (pipes.empty())
        cout << "No pipes\n";
    else
        for (const auto& item : pipes)
            cout << item.second << '\n';

    cout << "STATIONS:\n";

    if (stations.empty())
        cout << "No stations\n";
    else
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

    cout << "Enter pipe ID: ";
    int id = Get_positive_numb();

    auto it = pipes.find(id);

    if (it == pipes.end())
    {
        cout << "Pipe not found\n";
        return;
    }

    it->second.Edit_P();

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

    cout << "Enter station ID: ";
    int id = Get_positive_numb();

    auto it = stations.find(id);

    if (it == stations.end())
    {
        cout << "Station not found\n";
        return;
    }

    it->second.Edit_S();

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

    cout << "Enter pipe ID to delete: ";
    int id = Get_positive_numb();

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

    cout << "Enter station ID to delete: ";
    int id = Get_positive_numb();

    if (stations.erase(id))
        cout << "Station deleted\n";
    else
        cout << "Station not found\n";
}

unordered_map<int, Pipe> Network::FindPipes()
{
    if (pipes.empty())
    {
        cout << "No pipes\n";
        return unordered_map<int, Pipe>();
    }

    PipeFilter f;

    cout << "Part of pipe name (Enter = any): ";
    f.name = Get_line();

    cout << "Under repair (0 - no, 1 - yes, 2 - any): ";
    f.repair = Get_int_range(0, 2);

    auto subset = search(pipes, f, FilterPipe);

    cout << "Found pipes: " << subset.size() << '\n';

    for (const auto& item : subset)
        cout << item.second << '\n';

    return subset;
}

unordered_map<int, Station> Network::FindStations()
{
    if (stations.empty())
    {
        cout << "No stations\n";
        return unordered_map<int, Station>();
    }

    StationFilter f;

    cout << "Part of station name (Enter = any): ";
    f.name = Get_line();

    cout << "Minimum percent of unused workshops (0-100): ";
    f.min_percent = Get_int_range(0, 100);

    cout << "Maximum percent (" << f.min_percent << "-100): ";
    f.max_percent = Get_int_range(f.min_percent, 100);

    auto subset = search(stations, f, FilterStation);

    cout << "Found stations: " << subset.size() << '\n';

    for (const auto& item : subset)
        cout << item.second << '\n';

    for (const auto& item : subset)
    {
        cout << "ID: " << item.first << ", unused "
            << item.second.Get_unused_percent()
            << "%\n";
    }

    return subset;
}

void Network::SearchPipes()
{
    FindPipes();
}

void Network::SearchStations()
{
    FindStations();
}

vector<int> Network::SelectPipeIDs(const unordered_map<int, Pipe>& found)
{
    vector<int> chosen;

    cout << "1. All found pipes\n"
        << "2. Select pipe IDs\n"
        << "0. Cancel\n"
        << "Choose: ";

    int choice = Get_int_range(0, 2);

    if (choice == 1)
    {
        for (const auto& item : found)
            chosen.push_back(item.first);

        return chosen;
    }

    if (choice == 0)
        return chosen;

    PrintID(found);

    cout << "Enter IDs one by one, 0 to finish:\n";

    set<int> used;

    while (true)
    {
        cout << "ID: ";
        int id = Get_number();

        if (id == 0)
            break;

        if (found.find(id) == found.end())
        {
            cout << "ID is not among found pipes\n";
        }
        else if (!used.insert(id).second)
        {
            cout << "ID already selected\n";
        }
        else
        {
            chosen.push_back(id);
            cout << "ID selected\n";
        }
    }

    return chosen;
}

void Network::ApplyBatchOperation(const vector<int>& chosen)
{
    cout << "1. Set same repair status for selected\n"
        << "2. Edit each selected pipe (all fields)\n"
        << "3. Delete selected pipes\n"
        << "0. Cancel\n"
        << "Choose: ";

    int operation = Get_int_range(0, 3);

    if (operation == 0)
        return;

    if (operation == 1)
    {
        cout << "New repair status (0 - no, 1 - yes): ";

        bool value = (Get_int_range(0, 1) == 1);

        for (int id : chosen)
            pipes.at(id).Set_repair(value);
    }
    else if (operation == 2)
    {   
        for (int id : chosen)
        {   
            cout << "\nEditing ID: " << id << '\n';

            pipes.at(id).Edit_P();
        }
    }
    else
    {
        cout << "Confirm deletion of " << chosen.size()
            << " pipes? (0 - no, 1 - yes): ";

        if (Get_int_range(0, 1) == 0)
            return;

        for (int id : chosen)
            pipes.erase(id);
    }

    cout << "Batch operation completed for "
        << chosen.size() << " pipes\n";
}

void Network::BatchEditPipes()
{
    auto found = FindPipes();

    if (found.empty())
        return;

    vector<int> chosen = SelectPipeIDs(found);

    if (chosen.empty())
    {
        cout << "Nothing selected\n";
        return;
    }

    ApplyBatchOperation(chosen);
}

bool Network::Save(const string& filename)
{
    if (filename == "log.txt" || filename == "actions.log")
        return false;

    ofstream file(filename);

    if (!file)
        return false;

    for (const auto& item : pipes)
        item.second.SaveToFile(file);

    for (const auto& item : stations)
        item.second.SaveToFile(file);

    file.close();

    return file.good();
}

bool Network::Load(const string& filename)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "File opening error" << endl;
        return false;
    }

    pipes.clear();
    stations.clear();

    string type;

    while (getline(file, type))
    {
        if (type == "PIPE")
        {
            Pipe p;

            if (!p.LoadFromFile(file))
                break;

            pipes.emplace(p.Get_id(), p);
        }
        else if (type == "STATION")
        {
            Station s;

            if (!s.LoadFromFile(file))
                break;

            stations.emplace(s.Get_id(), s);
        }
        else
        {
            break;
        }
    }

    if (!file.eof())
    {
        cout << "File reading error" << endl;

        pipes.clear();
        stations.clear();

        Pipe::CalcMaxId(pipes);
        Station::CalcMaxId(stations);

        return false;
    }

    Pipe::CalcMaxId(pipes);
    Station::CalcMaxId(stations);

    return true;
}

void Network::SaveInteractive()
{
    cout << "Filename to save (example: data.txt): ";

    string filename = Get_name();

    if (Save(filename))
        cout << "Data saved\n";
    else
        cout << "File saving error\n";
}

void Network::LoadInteractive()
{
    cout << "Filename to load: ";

    string filename = Get_name();

    if (Load(filename))
        cout << "Data loaded\n";
    else
        cout << "Loading error. Data was not replaced\n";
}
