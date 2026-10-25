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



#endif
