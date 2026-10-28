#ifndef UTIL_H
#define UTIL_H

#include "Pipe.h"
#include "Station.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>


class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;

public:
    redirect_output_wrapper(std::ostream& src)
        : old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper()
    {
        stream.rdbuf(old_buf);
    }

    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};


int Get_int_range(int min_value, int max_value);
int Get_positive_numb();
int Get_number();
std::string Get_name();
std::string Get_line();
char Get_class_station();

template <typename T, typename Tx, typename Filter>
std::unordered_map<int, T> search(
    const std::unordered_map<int, T>& objects,
    const Tx& criterion,
    Filter f)
{
    std::unordered_map<int, T> subset;

    for (const auto& item : objects)
    {
        const T& p = item.second;

        if (f(p, criterion))
        {
            subset.emplace(item.first, p);
        }
    }

    return subset;
}

template<typename T>
void PrintID(const std::unordered_map<int, T>& objects)
{
    std::cout << "All ID: ";
    for (const auto& it : objects)
    {
        std::cout << it.second.Get_id() << " ";
    }
    std::cout << '\n';
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

#endif
