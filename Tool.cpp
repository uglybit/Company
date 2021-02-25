#include "Tool.h"

Tool::Tool(std::string name, double price) : Resources(name)
{
    tool_price = price;
    next_inspection_date = next_test_date(); // sets date: one year from "now"
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
    std::time_t now = std::time(nullptr);
    std::string time_now = std::asctime(std::localtime(&now));

    auto _year = std::localtime(&now)->tm_year + 1900;
    auto _month = std::localtime(&now)->tm_mon;
    auto _day = std::localtime(&now)->tm_mday;

    std::string date =
        std::to_string(_year) + "-" +
        std::to_string(_month) + "-" +
        std::to_string(_day);
    return date;
}