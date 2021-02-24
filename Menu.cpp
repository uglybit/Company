#include "Menu.h"



void Menu::show_menu()
{
    system("cls");
    std::cout << "\n*** MY COMPANY ***\n" << '\n';
    std::cout << " a - Add employee\n"
         << " f - Find employee\n"
         << " l - Show all\n"
         << " s - Go to storage\n\n"
         << " e - End program\n"
         << '\n';
}


char Menu::menu_choice()
{
    char choice;
    std::cin >> choice;
    switch(choice)
    {
        case 'a': company->add_new_employee(); break;
        case 'f': company->find_employee(); break;
        case 'l': company->show_all_employees(); break;
        case 's': company->get_storage()->show_menu(); break;
        case 'e': return 'e'; //  ends program
        default: std::cout << "Wrong command, try again" << '\n';
    }
    return 'x';
}
