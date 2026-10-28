
#ifndef NETWORK_H
#define NETWORK_H

#include "Pipe.h"
#include "Station.h"
#include <string>
#include <unordered_map>
#include <vector>

class Network
{
private:
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, Station> stations;

    std::unordered_map<int, Pipe> FindPipes();
    std::unordered_map<int, Station> FindStations();

    bool Save(const std::string& filename);
    bool Load(const std::string& filename);

    std::vector<int> SelectPipeIDs(
        const std::unordered_map<int, Pipe>& found);

    void ApplyBatchOperation(const std::vector<int>& chosen);

public:

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
