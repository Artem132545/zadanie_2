#include "Network.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <format>

using namespace std;

void Menu()
{
    cout << "1. Add pipe\n"
        << "2. Add station\n"
        << "3. View all objects\n"
        << "4. Edit pipe\n"
        << "5. Edit station\n"
        << "6. Save to file\n"
        << "7. Load from file\n"
        << "8. Delete pipe\n"
        << "9. Delete station\n"
        << "10. Search pipes\n"
        << "11. Search stations\n"
        << "12. Batch edit/delete pipes\n"
        << "0. Exit\n"
        << "Choose action: ";
}


int main()
{
    string time = std::format("{:%d_%m_%Y %H_%M_%OS}",
        std::chrono::system_clock::now());

    ofstream logfile("log_" + time + ".txt");

    redirect_output_wrapper cerr_out(cerr);

    if (logfile)
        cerr_out.redirect(logfile);

    Network network;

    while (true)
    {
        Menu();

        int action = Get_number();

        switch (action)
        {
        case 1: network.AddPipe(); break;
        case 2: network.AddStation(); break;
        case 3: network.ViewAll(); break;
        case 4: network.EditPipe(); break;
        case 5: network.EditStation(); break;
        case 6: network.SaveInteractive(); break;
        case 7: network.LoadInteractive(); break;
        case 8: network.DeletePipe(); break;
        case 9: network.DeleteStation(); break;
        case 10: network.SearchPipes(); break;
        case 11: network.SearchStations(); break;
        case 12: network.BatchEditPipes(); break;

        case 0:
            return 0;

        default:
            cout << "Wrong action" << endl;
            break;
        }
    }
}
