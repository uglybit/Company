#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Storage.h"
#include <vector>

// recgognize Employee type
enum class Emp_type
{
    Employee,
    Trader,
    Production_worker
};

class Employee // abstract class
{
protected:
    std::string position;
    std::string name;
    std::string surname;
    std::string birthday;
    std::string join_date;
    std::string address;
    std::string phone;
    double salary;
    int employee_id;

    int nof_employee_tools{};
    static int max_id_amount; // the highest employee ID
    static int employee_counter;
    std::vector<Resources*> employee_resources;

public:
    Employee();
    Employee(const Employee &) = delete;
    Employee* operator=(const Employee &) = delete;
    explicit Employee(std::string p);  // for reading from file only
    virtual ~Employee();

    virtual Emp_type recType() const { return Emp_type::Employee; }

    // get, set
    static int get_number_of_employee() { return employee_counter; }
    int get_employee_id() { return employee_id; }
    int get_number_of_itmes() { return nof_employee_tools; }
    static unsigned get_max_id_amount() {return max_id_amount; } 
    std::string get_surname() { return surname; } // for searching for employee
    static void set_max_id_amount(int n) { max_id_amount = n; } 

    bool get_resource(Storage* s);
    void return_resource(Storage* s);

    // functions
    void fill_employee_data();
    void edit_personal_info();
    void show_personal_info();
    void show_employee_info(); // show all employee data
    void read_basic_info(std::ifstream& f_in);
    void save_basic_info(std::ofstream& f_out);
    void copy_basic_info(Employee*);

    int show_employee_resources();
    virtual void save_employee(std::ofstream& f_out) = 0;
    virtual void read_employee(std::ifstream& f_in) = 0;

    /** defined as  Trader! */
    virtual std::string get_additional_options() { return " "; };
    virtual void set_additional_options() {};
    /** */

    virtual Emp_type Employee_type() const
    {
        return Emp_type::Employee;
    }
};

#endif // EMPLOYEE_H
