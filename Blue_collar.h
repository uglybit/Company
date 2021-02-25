#ifndef BLUE_COLLAR
#define BLUE_COLLAR

#include "Employee.h"

/*
    class Blue_collar is abstract class for all blue collar workers
*/


class Blue_collar : public Employee 
{
protected:
    Blue_collar() : Employee() { nof_employee_tools = 0; } // for creating new employee by user
    explicit Blue_collar(std::string p) : Employee(p) {} // for reading from file
    ~Blue_collar() override { std::cout << "destructor Blue_collar\n"; }
};


class Production_worker final: public Blue_collar
{
private:
    std::string brigade;
public:
    Production_worker() : Blue_collar() { position = "production worker"; } // for creating new employee by user
    explicit Production_worker(std::string p) : Blue_collar(p) {} // for reading from file
    ~Production_worker() override { std::cout << "destructor Prod worker\n"; }

    Emp_type recType() const override { return Emp_type::Production_worker; }

    void save_employee(std::ofstream& f_out) override;
    void read_employee(std::ifstream& f_in) override;
    std::string get_additional_options() override;
    void set_additional_options() override;
};

#endif