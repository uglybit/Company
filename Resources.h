#ifndef RESOURCES_H
#define RESOURCES_H

#include <fstream>
#include <iostream>
#include <string>

// global functions - definitions: main.cpp
bool data_validation(std::string info);
void require_key(char key = 'b');
bool confirmation();


// for recognizing type of Resource in derived class
enum class Res_type
{
    Resources,
    Tool,
    Device
};


class Resources
{
protected:
    static int resources_counter;
    int resource_id;
    std::string resource_name;

public:
    Resources() { resource_id = ++resources_counter; }
    explicit Resources(int n)  { resources_counter += n; }
    explicit Resources(std::string name);
    virtual ~Resources() { std::cout << "Destr Resources\n"; resources_counter--; }

    //This function allows to recognize type of Resource*  in derived class
    virtual Res_type recognize_type() const{ return Res_type::Resources; }
    virtual void save_resource(std::ofstream& f_out) = 0;
    virtual void read_from_file(std::ifstream& f_in) = 0;
    virtual void show_info() { std::cout << "pure resources show_info\n"; }
};

#endif // RESOURCES_H
