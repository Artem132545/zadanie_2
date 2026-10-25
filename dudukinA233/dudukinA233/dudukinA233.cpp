#include "Util.h"
#include <iostream>

using namespace std;

void Menu()
{
    cout << "\n======= MENU =======\n"
        << "1. Add pipe\n"
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
    Network network;

    while (true)
    {
        Menu();
        int action = Get_number();
        network.LogMenu(action);

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
        {
            cout << "Save before exit? (0 - no, 1 - yes): ";
            bool save = (Get_int_range(0, 1) == 1);
            network.LogExitDecision(save);
            if (save)
                network.SaveInteractive();
            cout << "Goodbye!\n";
            return 0;
        }
        default:
            cout << "Wrong action\n";
            break;
        }
    }
}
