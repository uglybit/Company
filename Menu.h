#ifndef MENU_H
#define MENU_H

#include "Company.h"

/* 
   When program starts the constuctor gets parameter of type Company*
   and automaticaly reads employees and resources data from file
   then shows main menu 
 */

class Menu
{
    Company* company;
public:
    Menu(Company* c) : company{c}
    {
        company->read_from_file(); // reading from file automaticaly
    }
    
    void show_menu();
    char menu_choice();
};


#endif // MENU_H
