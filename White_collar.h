#ifndef WHITE_COLLAR
#define WHITE_COLLAR

#include "Employee.h"

/*
   White_collar is an abstract class, because
   it will be inherited by more classes like Trader, Engineer etc
 */

// abstract class
class White_collar : public Employee
{
protected:

    explicit White_collar() : Employee() { nof_employee_tools = 0; }
    explicit White_collar(string p) : Employee(p) {} // for reading from file
    ~White_collar() override {};
};

/*
  Class Trader is final class.
*/


class Trader : public White_collar
{
public:

    explicit Trader() : White_collar() { position = "trader"; } // for creating new employee by user
    explicit Trader(string p) : White_collar(p) {} // for reading from file
    ~Trader() override { std::cout << "destructor Trader\n"; }

    Emp_type recType() const override { return Emp_type::Trader; }

    void save_employee(std::ofstream& f_out) override;
    void read_employee(std::ifstream& f_in) override;

    Emp_type Employee_type() const override { return Emp_type::Trader; }
};


#endif
