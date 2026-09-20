#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Pipe
{
    string Name_KM;
    float length;
    float d;
    bool repair;
};

struct Station
{
    string Name;
    int count_workshops_all;
    int count_in_work;
    char class_station;             // (a,b,c)
};

