#ifndef BLUE_COLLAR
#define BLUE_COLLAR

#include "Employee.h"

/*

   Blue_collar is an abstract class for all handworkers, because
   it will be inherited by more classes like Production_worker, Technician etc
*/


class Blue_collar : public Employee 
{
protected:
    Blue_collar() : Employee() { nof_employee_tools = 0; } // for creating new employee by user
    explicit Blue_collar(string p) : Employee(p) {} // for reading from file
    ~Blue_collar() override {
        /*for (auto a: employee_resources) delete a;*/  // BUG!!! 
        std::cout << "destructor Blue_collar\n";
    }
};

/*
  Class Production_worker is final class.
*/

class Production_worker final: public Blue_collar
{
protected:
    string brigade;
public:
    Production_worker() : Blue_collar() { position = "production worker"; } // for creating new employee by user
    explicit Production_worker(string p) : Blue_collar(p) {} // for reading from file
    ~Production_worker() override { std::cout << "destructor Prod worker\n"; }

    Emp_type recType() const override { return Emp_type::Production_worker; }

    void save_employee(std::ofstream& f_out) override;
    void read_employee(std::ifstream& f_in) override;
    string get_additional_options() override;
    void set_additional_options() override;

    Emp_type Employee_type() const override { return Emp_type::Production_worker; }
};
#endif