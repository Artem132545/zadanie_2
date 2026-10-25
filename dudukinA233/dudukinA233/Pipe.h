#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <string>

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
    static bool LoadFromFile(std::istream& in, Pipe& p, int& loaded_id);

    friend std::istream& operator>>(std::istream& in, Pipe& p);
    friend std::ostream& operator<<(std::ostream& out, const Pipe& p);
};

Pipe Add_P();

#endif
