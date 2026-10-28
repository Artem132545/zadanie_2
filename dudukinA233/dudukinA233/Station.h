#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>
#include <unordered_map>

class Station
{
private:
    int id;
    std::string Name;
    int count_workshops_all;
    int count_in_work;
    char class_station;

public:
    static int Next_id_S;

    Station();

    int Get_id() const;
    const std::string& Get_name() const;
    double Get_unused_percent() const;
    void Edit_S();

    void SaveToFile(std::ostream& out) const;
    bool LoadFromFile(std::istream& file);

    static void CalcMaxId(const std::unordered_map<int, Station>& css);

    friend std::istream& operator>>(std::istream& in, Station& s);
    friend std::ostream& operator<<(std::ostream& out, const Station& s);

    
};

#endif