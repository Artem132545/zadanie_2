#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>


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
    static bool LoadFromFile(std::istream& in, Station& s, int& loaded_id);

    friend std::istream& operator>>(std::istream& in, Station& s);
    friend std::ostream& operator<<(std::ostream& out, const Station& s);
};

Station Add_S();

#endif
