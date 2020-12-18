#include <iostream>
#include <windows.h>
#include "Menu.h"
#include "Tool.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>


using namespace std;

int main()
{
    {
        Company my_company;
        Menu menu(&my_company);
        do
        {
            menu.show_menu();

        } while (menu.menu_choice() != 'e');

       getchar();
    }

    _CrtDumpMemoryLeaks();
    return 0;
}


// to making possible for user to see result of operations
void require_key(char key)
{
    cout << "\n " << key << " - go back... \n";
    char ch;
    do {
        cin >> ch;
    } while (ch != 'b');
}


// confirmation when overwriting important data 
bool confirmation()
{
    cout << "y - yes\n" 
         << "n - no\n";
    char c;
    do
    {
        c = getchar();
    } while (!(c == 'y' || c == 'n'));

    if (c == 'y') return true;
    else return false;
}


// any number validation 
bool data_validation(string info)
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << info;
        require_key();
        return true;
    }
    else
        return false;
}
