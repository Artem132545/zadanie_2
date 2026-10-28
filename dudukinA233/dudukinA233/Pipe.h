#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <string>
#include <unordered_map>

class Pipe
{
private:
    int id;
    std::string Name_KM;
    int d;
    int length;
    bool repair;

public:
    static int Next_id_P;

    Pipe();

    int Get_id() const;
    const std::string& Get_name() const;
    bool Is_repair() const;
    void Set_repair(bool value);
    void Edit_P();

    void SaveToFile(std::ostream& out) const;
    bool LoadFromFile(std::istream& file);

    static void CalcMaxId(const std::unordered_map<int, Pipe>& pipes);

    friend std::istream& operator>>(std::istream& in, Pipe& p);
    friend std::ostream& operator<<(std::ostream& out, const Pipe& p);
};


#endif