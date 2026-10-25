#ifndef UTIL_H
#define UTIL_H
#include "Pipe.h"
#include "Station.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int Get_int_range(int min_value, int max_value);
int Get_positive_numb();
int Get_number();
std::string Get_name();
std::string Get_line();
char Get_class_station();

const int MAX_OBJECT_ID = 1000000000;

template <typename T, typename Tx, typename Filter>
std::unordered_map<int, T> search(const std::unordered_map<int, T>& objects, const Tx& criterion, Filter f)
{
    std::unordered_map<int, T> subset;

    for (const auto& item : objects)
    {
        const T& p = item.second;
        if (f(p, criterion))
            subset.emplace(item.first, p);
    }
    return subset;
}

struct PipeFilter
{
    std::string name;
    int repair;
};

struct StationFilter
{
    std::string name;
    int min_percent;
    int max_percent;
};

bool FilterPipe(const Pipe& p, const PipeFilter& f);
bool FilterStation(const Station& s, const StationFilter& f);

class Network
{
private:
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, Station> stations;
    std::ofstream log_file;

    void Log(const std::string& action);
    std::unordered_map<int, Pipe> FindPipes();
    std::unordered_map<int, Station> FindStations();
    bool Save(const std::string& filename);
    bool Load(const std::string& filename);
    std::vector<int> SelectPipeIDs(const std::unordered_map<int, Pipe>& found);
    void ApplyBatchOperation(const std::vector<int>& chosen);

public:
    Network();
    ~Network();

    void LogMenu(int action);
    void LogExitDecision(bool save);
    void AddPipe();
    void AddStation();
    void ViewAll();
    void EditPipe();
    void EditStation();
    void DeletePipe();
    void DeleteStation();
    void SearchPipes();
    void SearchStations();
    void BatchEditPipes();
    void SaveInteractive();
    void LoadInteractive();
};

#endif
