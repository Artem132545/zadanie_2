#include <iostream>
#include <string>
using namespace std;

struct Pipe
{
    string KM;
    float lenght;
    float d;
    bool remont;
};
struct Station
{
    string Name;
    int count_ALL;
    int count_work;
    char class_station; // (a,b,c)
    bool rabota;
};


void out() {

    cout << "Add pipe"; //all param
    cout << "Add Station"; // all param

}

int main()
{
    Pipe p;
    Station s;
    return 0;
}
