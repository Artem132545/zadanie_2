#pragma once
#include "Pipe.h"
#include "Station.h"
#include <string>
#include <vector>
#include <unordered_map>

class Network
{
private:

    int nextPipeID = 1;
    int nextStationID = 1;

    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, Station> stations;

    std::vector<int> FindPipes();
    std::vector<int> FindStations();

    void BatchOperation(const std::vector<int>& ids);

    bool Save(const std::string& filename) const;
    bool Load(const std::string& filename);

public:
    Network();

    void AddPipe();
    void AddStation();

    void ViewAll() const;

    void EditPipe();
    void EditStation();

    void DeletePipe();
    void DeleteStation();

    void SearchPipes();
    void SearchStations();

    void BatchEditPipes();

    void SaveInteractive() const;
    void LoadInteractive();
};
