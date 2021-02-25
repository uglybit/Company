#include <iostream>
#include <windows.h>
#include "Menu.h"
#include "Tool.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    Company my_company;
    Menu menu(&my_company);
    do
    {
        menu.show_menu();

    } while (menu.menu_choice() != 'e');

    std::cin.get();
    return 0;
}


// to making possible for user to see result of operations
void require_key(char key)
{
    std::cout << "\n " << key << " - go back... \n";
    char ch;
    do {
        std::cin >> ch;
    } while (ch != 'b');
}


// confirmation when overwriting important data 
bool confirmation()
{
    std::cout << "y - yes\n" 
         << "n - no\n";
    char c;
    do
    {
        c = getchar();
    } while (!(c == 'y' || c == 'n'));

    // return (c == 'y');
    if (c == 'y') return true;
    else return false;
}


// any number validation 
bool data_validation(std::string info)
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10, '\n');
        std::cout << info;
        require_key();
        return true;
    }
    else
        return false;
}
