#ifndef RESOURCES_H
#define RESOURCES_H

#include <fstream>
#include <iostream>
#include <string>


using std::string;

// global functions - definitions: main.cpp
bool data_validation(string info);
void require_key(char key = 'b');
bool confirmation();


// for recognizing type of Resource in derived class
enum class Res_type
{
    Resources,
    Tool,
    Device
};

/*
  Resource is an abstract class for all kind tools, devices etc. that company owns
  Functions allow to: show information, read/save to file. 
*/

class Resources
{
protected:
    static int resources_counter;
    int resource_id;
    std::string resource_name;

public:
    Resources() { resource_id = ++resources_counter; }
    explicit Resources(int n)  { resources_counter += n; }
    explicit Resources(string name);
    virtual ~Resources() { std::cout << "Destr Resources\n"; resources_counter--; }

    //This function allows to recognize type of Resource*  in derived class
    virtual Res_type recognize_type() const{ return Res_type::Resources; }
    virtual void save_resource(std::ofstream& f_out) = 0;
    virtual void read_from_file(std::ifstream& f_in) = 0;
    virtual void show_info() { std::cout << "pure resources show_info\n"; }
};

#endif // RESOURCES_H
