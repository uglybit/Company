#include "Blue_collar.h"


void Production_worker::save_employee(std::ofstream& f_out)
{
    save_basic_info(f_out);
    f_out << get_additional_options() << " "; // virtual
    f_out << '\n' << '\t' << nof_employee_tools << '\n';

    for (auto a : employee_resources) a->save_resource(f_out); // virtual
}


void Production_worker::read_employee(std::ifstream& f_in) // virtual
{
    //std::cout << "\nProduction_worker read_employee\n";
    read_basic_info(f_in);
    f_in >> brigade;
    f_in >> nof_employee_tools;

    for (int i = 0; i < nof_employee_tools; i++)
    {
        employee_resources.push_back(new Tool);
        std::cout << "New Tool z read employee: " << employee_resources.back() << '\n';
        employee_resources[i]->read_from_file(f_in); // virtual
    }
}


std::string Production_worker::get_additional_options() // virtual
{
    std::cout << " brigade: ";
    return brigade;
}


void Production_worker::set_additional_options() // virtual
{
    std::cout << "Brigade number: ";
    std::cin >> brigade; // validation!!
}

