#ifndef DEVICE_H
#define DEVICE_H

#include "Resources.h"

/*
  Device class represents tools thats only White_collar workers can posses.
  Functions allow to: show info, read/save tool to file.
*/

class Device : public Resources
{
    std::string device_brand;
public:
    Device() : Resources() {}
    explicit Device(std::string name, std::string br) : Resources(name)  { device_brand = br; }
    explicit Device(int n) : Resources(n) {}
    ~Device() override { std::cout << "Destruktor Device: " << this << "\n"; }

    Res_type recognize_type() const override { return Res_type::Device; }
    void save_resource(std::ofstream& f_out) override;
    void read_from_file(std::ifstream& f_in) override;
    void show_info() override;
};

#endif // DEVICE_H