#include "Device.h"



// saving to file
void Device::save_resource(std::ofstream& f_out)
{
    f_out << '\t' << resource_id << " " << resource_name << " " << device_brand << '\n';
}

// reading from file
void Device::read_from_file(std::ifstream& f_in)
{
    f_in >> resource_id >> resource_name >> device_brand;
}

// show information about device
void Device::show_info()
{
    std::cout << resource_name << ", brand: " << device_brand  << ", ID: " << resource_id << '\n';
}

