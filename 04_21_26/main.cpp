#include "map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// M06 A lab
//  write a new main to test the map. use any key value pair you like (insert change and delete items)

int main()
{
    map<int, std::string> hobbits;
    std::ifstream name("names.txt");
    for (int i = 0; !name.eof(); i++)
    {
        std::string in;
        std::getline(name >> std::ws, in);
        hobbits.insert(i, in);
    }
    for (auto it = hobbits.begin(); it != hobbits.end(); ++it)
    {
        pair<int, std::string> p = *it;
        std::cout << p.getValue() << std::endl;
    }
    std::cout << std::endl
              << std::endl;
    std::cout << hobbits[6] << std::endl;
    std::cout << std::setw(40) << std::setfill('-') << "-" << std::endl;
    hobbits[0] = "Tasha Oakbottom";
    std::cout << hobbits[0] << std::endl;
    hobbits[15] = std::string("Brianna Button");
    std::cout
        << std::setw(40) << std::setfill('-') << "-" << std::endl;
    for (auto it = hobbits.begin(); it != hobbits.end(); ++it)
    {
        pair<int, std::string> p = *it;
        std::cout << p.getValue() << std::endl;
    }

    std::cout << std::endl
              << std::endl;

    std::cout << "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\nBegin Delete test:\n\n";

    std::cout << "Notes about the delete debugger:\nType -1 to exit\nType -2 to print map\n";

    while (true)
    {

        std::cout << "\n  *** \n";

        int ind;

        std::cout << "Enter index of node to be deleted: ";

        std::cin >> ind;

        if (ind == -1)
        {

            break;
        }

        if (ind == -2)
        {
            // std::cout << hobbits.preorder() << std::endl;
            for (auto it = hobbits.begin(); it != hobbits.end(); ++it)

            {

                pair<int, std::string> p = *it;

                std::cout << p.getValue() << std::endl;
            }
        }

        else
        {

            try

            {

                std::cout << "Deleting " << hobbits.at(ind) << "\n";

                std::cout << hobbits.deleteItem(ind)
                          << std::endl;
            }

            catch (const std::out_of_range &e)

            {

                std::cout << e.what() << '\n';
            }
        }
    }

    return 0;
}