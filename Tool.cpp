#include "Tool.h"


Tool::Tool(std::string name, double price) : Resources(name)
{
    tool_price = price;
    next_inspection_date = next_test_date(); // sets date: one year form "now"
}


void Tool::save_resource(std::ofstream& f_out)
{
    f_out << '\t' << resource_id << " " << resource_name << " "
         << tool_price << " " << next_inspection_date << '\n';
}


void Tool::read_from_file(std::ifstream& f_in)
{
    f_in >> resource_id >> resource_name >> tool_price >> next_inspection_date;
}


void Tool::show_info()
{
    std::cout  << resource_name << ", next inspection date: " << next_inspection_date
          << ", price: " << tool_price << " euro , ID: " << resource_id << '\n';
}


std::string Tool::next_test_date() 
{
    std::string date;
    struct tm new_time;
    time_t now = time(0);
    localtime_s(&new_time, &now);
    int year = 1901 + new_time.tm_year;
    int month = 1 + new_time.tm_mon;
    int day = new_time.tm_mday;
    date = std::to_string(year) + '-' + 
           std::to_string(month) + '-' + 
           std::to_string(day);
    return date;
}
