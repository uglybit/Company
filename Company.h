#ifndef COMPANY_H
#define COMPANY_H

#include "Employee.h"
#include "Blue_collar.h"
#include "White_collar.h"
#include "Storage.h"

/*
  Class Company is main class that contains all employees and Storage.
  Functions allow to: show, add, remove, move, search for employees 
  and give them resources from storage.
  All data is stored to file employee_date.txt
*/


class Company
{
    Storage* storage = nullptr;
    string file_employee = "employee_data.txt"; // constant file name
    std::vector<Employee*> all_workers; // container for employees
    int current_employee; // the number of employee, currently are working on
    using  iterator = std::vector<Employee*>::iterator; 

    iterator it_curr_emp(); // returns iterator for current employee
public:
    Company();
    ~Company();

    Storage* get_storage() { return storage; }
    Employee* occupation_choosing();

    void give_resource(Employee* emp, Storage* s);
    void employee_menu();
    void add_new_employee();
    void show_all_employees();
    void find_employee();
    bool search_by_surname();
    bool search_by_id();
    void move_employee();
    void save_to_file();
    void read_from_file();
    void remove_employee();
};

#endif // COMPANY_H
