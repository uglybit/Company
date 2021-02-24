#include "White_collar.h"

void Trader::save_employee(std::ofstream& f_out)
{
    save_basic_info(f_out);
    f_out << '\n' << '\t' << nof_employee_tools << '\n';
    for (auto a : employee_resources) a->save_resource(f_out);
}


void Trader::read_employee(std::ifstream& f_in) // override
{
    read_basic_info(f_in);
    f_in >> nof_employee_tools;

    for (int i = 0; i < nof_employee_tools; i++)
    {
        employee_resources.push_back(new Device);
        std::cout << "New Deivce z read employee: " << employee_resources.back() << '\n';
        employee_resources[i]->read_from_file(f_in);
    }
}
