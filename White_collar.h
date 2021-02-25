#ifndef WHITE_COLLAR
#define WHITE_COLLAR

#include "Employee.h"

/*
    class White_collar is abstract class for all white collar workers
*/

class White_collar : public Employee
{
protected:
    explicit White_collar() : Employee() { nof_employee_tools = 0; }
    explicit White_collar(std::string p) : Employee(p) {} // for reading from file
    ~White_collar() override { std::cout << "Destr White collar\n"; }
};


class Trader final : public White_collar
{
public:
    explicit Trader() : White_collar() { position = "trader"; } // for creating new employee by user
    explicit Trader(std::string p) : White_collar(p) {} // for reading from file
    ~Trader() override { std::cout << "destructor Trader\n"; }

    Emp_type recType() const override { return Emp_type::Trader; }
    void save_employee(std::ofstream& f_out) override;
    void read_employee(std::ifstream& f_in) override;
};

#endif