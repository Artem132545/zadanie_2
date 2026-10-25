#include "Util.h"
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <set>
#include <vector>

using namespace std;

int Get_int_range(int min_value, int max_value)
{
    cout << "Enter number from " << min_value << " to " << max_value << ": ";
    while (true)
    {
        int value = Get_number();
        if (value >= min_value && value <= max_value) return value;
        cout << "Wrong action. Enter from " << min_value << " to " << max_value << ": ";
    }
}

string Get_line()
{
    string value;
    getline(cin, value);
    return value;
}

int Get_positive_numb()
{
    int k;

    while (1)
    {
        if (cin >> k && cin.peek() == '\n' && k > 0)
        {
            cin.ignore(10000, '\n');
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
            cin.ignore(10000, '\n');
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

string Get_name()
{
    string name;

    getline(cin, name);

    while (name.empty())
    {
        cout << "Wrong action. Enter name" << endl;
        getline(cin, name);
    }

    return name;
}


char Get_class_station()
{
    char c;

    while (1)
    {
        if (cin >> c && cin.peek() == '\n' &&
            (c == 'a' || c == 'b' || c == 'c'))
        {
            cin.ignore(10000, '\n');
            return c;
        }
        else
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Wrong action. Enter a, b or c" << endl;
        }
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
    return name_ok && percent >= f.min_percent &&
        percent <= f.max_percent;
}

namespace
{
    template <typename T>
    set<int> SortedIDs(const unordered_map<int, T>& objects)
    {
        set<int> ids;
        for (const auto& item : objects)
            ids.insert(item.first);
        return ids;
    }

    template <typename T>
    void PrintObjects(const unordered_map<int, T>& objects)
    {
        for (int id : SortedIDs(objects))
            cout << objects.at(id) << '\n';
    }

    template <typename T>
    void PrintIDs(const unordered_map<int, T>& objects, char prefix)
    {
        cout << "Available IDs: ";
        for (int id : SortedIDs(objects))
            cout << prefix << '-' << id << "  ";
        cout << '\n';
    }
}

Network::Network() : log_file("actions.log", ios::app)
{
    if (!log_file)
        cerr << "WARNING: Cannot open actions.log\n";
    Log("Program started");
}

Network::~Network()
{
    Log("Program finished");
}

void Network::Log(const string& message)
{
    if (!log_file.is_open())
        return;

    time_t now = time(0);
    tm local_time;

    localtime_s(&local_time, &now);

    log_file << put_time(&local_time, "[%Y-%m-%d %H:%M:%S] ")
        << message << endl;
}

void Network::LogMenu(int action)
{
    Log("Menu choice: " + to_string(action));
}

void Network::LogExitDecision(bool save)
{
    Log(save ? "Exit: user chose to save" : "Exit: user chose not to save");
}

void Network::AddPipe()
{
    if (Pipe::Next_id_P > MAX_OBJECT_ID)
    {
        cout << "No more pipe IDs available\n";
        Log("Add pipe failed: ID limit reached");
        return;
    }
    Pipe p = Add_P();
    int id = p.Get_id();
    pipes.emplace(id, p);
    cout << "Pipe added: P-" << id << '\n';
    Log("Added pipe P-" + to_string(id) + ", name=" + p.Get_name());
}

void Network::AddStation()
{
    if (Station::Next_id_S > MAX_OBJECT_ID)
    {
        cout << "No more station IDs available\n";
        Log("Add station failed: ID limit reached");
        return;
    }
    Station s = Add_S();
    int id = s.Get_id();
    stations.emplace(id, s);
    cout << "Station added: S-" << id << '\n';
    Log("Added station S-" + to_string(id) + ", name=" + s.Get_name());
}

void Network::ViewAll()
{
    cout << "\nPIPES:\n";
    if (pipes.empty()) cout << "No pipes\n";
    else PrintObjects(pipes);
    cout << "STATIONS:\n";
    if (stations.empty()) cout << "No stations\n";
    else PrintObjects(stations);
    Log("Viewed all objects");
}

void Network::EditPipe()
{
    if (pipes.empty()) { cout << "No pipes\n"; Log("Edit pipe: empty"); return; }
    PrintIDs(pipes, 'P');
    cout << "Enter pipe ID: ";
    int id = Get_positive_numb();
    auto it = pipes.find(id);
    if (it == pipes.end())
    {
        cout << "Pipe not found\n";
        Log("Edit pipe: P-" + to_string(id) + " not found");
        return;
    }
    it->second.Edit_P();
    Log("Edited pipe P-" + to_string(id));
    cout << "Pipe edited\n";
}

void Network::EditStation()
{
    if (stations.empty()) { cout << "No stations\n"; Log("Edit station: empty"); return; }
    PrintIDs(stations, 'S');
    cout << "Enter station ID: ";
    int id = Get_positive_numb();
    auto it = stations.find(id);
    if (it == stations.end())
    {
        cout << "Station not found\n";
        Log("Edit station: S-" + to_string(id) + " not found");
        return;
    }
    it->second.Edit_S();
    Log("Edited station S-" + to_string(id));
    cout << "Station edited\n";
}

void Network::DeletePipe()
{
    if (pipes.empty()) { cout << "No pipes\n"; Log("Delete pipe: empty"); return; }
    PrintIDs(pipes, 'P');
    cout << "Enter pipe ID to delete: ";
    int id = Get_positive_numb();
    if (pipes.erase(id))
    {
        cout << "Pipe deleted\n";
        Log("Deleted pipe P-" + to_string(id));
    }
    else
    {
        cout << "Pipe not found\n";
        Log("Delete pipe: P-" + to_string(id) + " not found");
    }
}

void Network::DeleteStation()
{
    if (stations.empty()) { cout << "No stations\n"; Log("Delete station: empty"); return; }
    PrintIDs(stations, 'S');
    cout << "Enter station ID to delete: ";
    int id = Get_positive_numb();
    if (stations.erase(id))
    {
        cout << "Station deleted\n";
        Log("Deleted station S-" + to_string(id));
    }
    else
    {
        cout << "Station not found\n";
        Log("Delete station: S-" + to_string(id) + " not found");
    }
}

unordered_map<int, Pipe> Network::FindPipes()
{
    if (pipes.empty())
    {
        cout << "No pipes\n";
        Log("Search pipes: empty collection");
        return unordered_map<int, Pipe>();
    }

    PipeFilter f;
    cout << "Part of pipe name (Enter = any): ";
    f.name = Get_line();
    cout << "Under repair (0 - no, 1 - yes, 2 - any): ";
    f.repair = Get_int_range(0, 2);

    auto subset = search(pipes, f, FilterPipe);
    cout << "Found pipes: " << subset.size() << '\n';
    PrintObjects(subset);
    Log("Search pipes: name='" + f.name + "', repair=" +
        to_string(f.repair) + ", found=" + to_string(subset.size()));
    return subset;
}

unordered_map<int, Station> Network::FindStations()
{
    if (stations.empty())
    {
        cout << "No stations\n";
        Log("Search stations: empty collection");
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
    PrintObjects(subset);
    for (int id : SortedIDs(subset))
        cout << "S-" << id << ": unused "
        << subset.at(id).Get_unused_percent() << "%\n";

    Log("Search stations: name='" + f.name + "', percent=" +
        to_string(f.min_percent) + ".." + to_string(f.max_percent) +
        ", found=" + to_string(subset.size()));
    return subset;
}

void Network::SearchPipes() { FindPipes(); }
void Network::SearchStations() { FindStations(); }

vector<int> Network::SelectPipeIDs(const unordered_map<int, Pipe>& found)
{
    vector<int> chosen;
    cout << "1. All found pipes\n"
        << "2. Select pipe IDs\n"
        << "0. Cancel\nChoose: ";
    int choice = Get_int_range(0, 2);

    if (choice == 1)
    {
        Log("Batch selection: all found pipes");
        set<int> ids = SortedIDs(found);
        return vector<int>(ids.begin(), ids.end());
    }
    if (choice == 0)
    {
        Log("Batch selection cancelled");
        return chosen;
    }

    Log("Batch selection: IDs chosen by user");
    PrintIDs(found, 'P');
    cout << "Enter IDs one by one, 0 to finish:\n";
    set<int> used;
    while (true)
    {
        cout << "ID: ";
        int id = Get_number();
        if (id == 0) break;
        if (found.find(id) == found.end())
        {
            cout << "ID is not among found pipes\n";
            Log("Batch selection rejected P-" + to_string(id));
        }
        else if (!used.insert(id).second)
        {
            cout << "ID already selected\n";
        }
        else
        {
            chosen.push_back(id);
            Log("Batch selection added P-" + to_string(id));
        }
    }
    return chosen;
}

void Network::ApplyBatchOperation(const vector<int>& chosen)
{
    cout << "1. Set same repair status for selected\n"
        << "2. Edit each selected pipe (all fields)\n"
        << "3. Delete selected pipes\n"
        << "0. Cancel\nChoose: ";
    int operation = Get_int_range(0, 3);
    Log("Batch operation menu choice: " + to_string(operation));
    if (operation == 0) { Log("Batch edit: cancelled"); return; }

    if (operation == 1)
    {
        cout << "New repair status (0 - no, 1 - yes): ";
        bool value = (Get_int_range(0, 1) == 1);
        for (int id : chosen)
        {
            pipes.at(id).Set_repair(value);
            Log("Batch repair set P-" + to_string(id) + " to " +
                to_string(value ? 1 : 0));
        }
    }
    else if (operation == 2)
    {
        for (int id : chosen)
        {
            cout << "\nEditing P-" << id << '\n';
            pipes.at(id).Edit_P();
            Log("Batch full edit P-" + to_string(id));
        }
    }
    else
    {
        cout << "Confirm deletion of " << chosen.size()
            << " pipes? (0 - no, 1 - yes): ";
        if (Get_int_range(0, 1) == 0)
        {
            Log("Batch delete: confirmation refused");
            return;
        }
        for (int id : chosen)
        {
            pipes.erase(id);
            Log("Batch deleted P-" + to_string(id));
        }
    }
    cout << "Batch operation completed for " << chosen.size() << " pipes\n";
}

void Network::BatchEditPipes()
{
    auto found = FindPipes();
    if (found.empty()) { Log("Batch pipes: no matches"); return; }

    vector<int> chosen = SelectPipeIDs(found);
    if (chosen.empty())
    {
        cout << "Nothing selected\n";
        Log("Batch: nothing selected");
        return;
    }
    ApplyBatchOperation(chosen);
}

bool Network::Save(const string& filename)
{
    // Не допускаем перезаписи файла журнала данными объектов.
    if (filename == "actions.log")
    {
        Log("Save refused: filename actions.log is reserved");
        return false;
    }

    ofstream file(filename.c_str());
    if (!file)
    {
        Log("Save failed: cannot open '" + filename + "'");
        return false;
    }
    for (int id : SortedIDs(pipes)) pipes.at(id).SaveToFile(file);
    for (int id : SortedIDs(stations)) stations.at(id).SaveToFile(file);
    file.close();
    bool ok = !file.fail();
    Log(string(ok ? "Saved" : "Save failed") + " file '" + filename +
        "', pipes=" + to_string(pipes.size()) +
        ", stations=" + to_string(stations.size()));
    return ok;
}

bool Network::Load(const string& filename)
{
    ifstream file(filename.c_str());
    if (!file)
    {
        Log("Load failed: cannot open '" + filename + "'");
        return false;
    }

    int old_pipe_next = Pipe::Next_id_P;
    int old_station_next = Station::Next_id_S;
    auto fail = [&]() -> bool
        {
            Pipe::Next_id_P = old_pipe_next;
            Station::Next_id_S = old_station_next;
            Log("Load failed: invalid file '" + filename + "'; current data kept");
            return false;
        };

    unordered_map<int, Pipe> new_pipes;
    unordered_map<int, Station> new_stations;
    int max_pipe_id = 0;
    int max_station_id = 0;
    string type;

    while (getline(file, type))
    {
        if (type == "PIPE")
        {
            Pipe p;
            int id = 0;
            if (!Pipe::LoadFromFile(file, p, id)) return fail();
            if (!new_pipes.emplace(id, p).second) return fail();
            if (id > max_pipe_id) max_pipe_id = id;
        }
        else if (type == "STATION")
        {
            Station s;
            int id = 0;
            if (!Station::LoadFromFile(file, s, id)) return fail();
            if (!new_stations.emplace(id, s).second) return fail();
            if (id > max_station_id) max_station_id = id;
        }
        else return fail();
    }
    if (file.bad()) return fail();

    pipes.swap(new_pipes);
    stations.swap(new_stations);
    Pipe::Next_id_P = max_pipe_id + 1;
    Station::Next_id_S = max_station_id + 1;
    Log("Loaded file '" + filename + "', pipes=" + to_string(pipes.size()) +
        ", stations=" + to_string(stations.size()));
    return true;
}

void Network::SaveInteractive()
{
    cout << "Filename to save (example: data.txt): ";
    string filename = Get_name();
    if (Save(filename)) cout << "Data saved\n";
    else cout << "File saving error\n";
}

void Network::LoadInteractive()
{
    cout << "Filename to load: ";
    string filename = Get_name();
    if (Load(filename)) cout << "Data loaded\n";
    else cout << "Loading error. Data was not replaced\n";
}
