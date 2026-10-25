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



#endif
