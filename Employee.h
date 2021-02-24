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

/*
    class Employee is abstract class for specific types of Employee
*/

class Employee 
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
    explicit Employee(std::string pos);  // for reading from file only
    virtual ~Employee();
    
    virtual Emp_type recType() const { return Emp_type::Employee; }
    static int get_number_of_employee() { return employee_counter; }
    static unsigned get_max_id_amount() {return max_id_amount; } 
    static void set_max_id_amount(int n) { max_id_amount = n; } 
    int get_employee_id() { return employee_id; }
    int get_number_of_itmes() { return nof_employee_tools; }
    std::string get_surname() { return surname; }
    int show_employee_resources();
    bool get_resource(Storage* s);
    void return_resource(Storage* s);

    // manage employee
    void fill_employee_data();
    void edit_personal_info();
    void show_personal_info();
    void show_employee_info(); 
    void copy_basic_info(Employee*);

    void read_basic_info(std::ifstream& f_in);
    void save_basic_info(std::ofstream& f_out);
    virtual void save_employee(std::ofstream& f_out) = 0;
    virtual void read_employee(std::ifstream& f_in) = 0;

    /** defined as  Trader! */
    virtual std::string get_additional_options() { return " "; };
    virtual void set_additional_options() {};
    /** */
};

#endif // EMPLOYEE_H
