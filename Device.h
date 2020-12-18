#ifndef DEVICE_H
#define DEVICE_H

#include "Resources.h"


class Device : public Resources
{
    string device_brand;
public:
    Device() : Resources() {}
    explicit Device(string name, string br) : Resources(name)  { device_brand = br; }
    explicit Device(int n) : Resources(n) {}
    ~Device() override { std::cout << "Destruktor Device: " << this << "\n"; }
    //---


    Res_type recognize_type() const override
    {
        return Res_type::Tool;
    }



    void save_resource(std::ofstream& f_out) override;
    void read_from_file(std::ifstream& f_in) override;
    void show_info() override;

};



#endif // DEVICE_H