#ifndef STORAGE_H
#define STORAGE_H

//#include "Resources.h"

#include "Device.h"
#include "Tool.h"
#include <vector>
#include <conio.h>
#include <fstream>

/*
  Class Storage contains tools and devices for all kind of employees.
  Functions allow to: add, lease, take resources which are stored in 
  file: 'storage_data.txt'
    
*/


class Storage
{
    std::vector<Resources*> devices_in_storage;
    std::vector<Resources*> tools_in_storage;
    std::string data_file_name = "storage_data.txt";
 
public:
    Storage() {}
    ~Storage();

    unsigned show_devices();
    unsigned show_tools();
    void show_menu();
    void save_all_resources();
    void read_all_resources();
    bool take_resource(Resources* tmp);
    Resources* lease_device(unsigned nr);
    Resources* lease_tool(unsigned nr);

    void add_new_device(); 
    void add_new_tool(); 
    
};

#endif // STORAGE_H
