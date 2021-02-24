#include "Device.h"


void Device::save_resource(std::ofstream& f_out)
{
    f_out << '\t' << resource_id << " " << resource_name << " " << device_brand << '\n';
}


void Device::read_from_file(std::ifstream& f_in)
{
    f_in >> resource_id >> resource_name >> device_brand;
}


void Device::show_info()
{
    std::cout << resource_name << ", brand: " << device_brand  << ", ID: " << resource_id << '\n';
}

