#include "Tool.h"

using namespace std;


Tool::Tool(string name, double pr) : Resources(name)
{
    tool_price = pr;
    next_inspection_date = next_test_date(); // sets date: one year form "now"
}


// saving resource to file
void Tool::save_resource(ofstream& f_out)
{
    f_out << '\t' << resource_id << " " << resource_name << " "
         << tool_price << " " << next_inspection_date << '\n';
}


// reading resource from file
void Tool::read_from_file(ifstream& f_in)
{
    f_in >> resource_id >> resource_name >> tool_price >> next_inspection_date;
}


// show informotion about tool
void Tool::show_info()
{
    cout  << resource_name << ", next inspection date: " << next_inspection_date
          << ", price: " << tool_price << " euro , ID: " << resource_id << endl;
}


// new tool - next examination date (one year)
string Tool::next_test_date() 
{
    string date;
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    int year = 1901 + newtime.tm_year;
    int month = 1 + newtime.tm_mon;
    int day = newtime.tm_mday;
    date = to_string(year) + '-' + 
           to_string(month) + '-' + 
           to_string(day);

    return date;
}