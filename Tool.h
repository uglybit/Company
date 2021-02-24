#ifndef TOOL_H
#define TOOL_H

#include "Resources.h"
#include <ctime>

/*
  Tool class represents tools that only Blue_collar workers  can possess.
  Functions allow to: show info, read/save tool to file.
*/

class Tool : public Resources
{
private:
    double tool_price;
    std::string next_inspection_date;
    std::string next_test_date();
public:
    Tool() : Resources() {}
    explicit Tool(std::string name, double price);
    explicit Tool(int n) : Resources(n)  {}
    ~Tool() override { std::cout << "Destruktor Tool " << this << "\n"; }

    Res_type recognize_type() const override {  return Res_type::Tool; }
    void save_resource(std::ofstream& f_out) override;
    void read_from_file(std::ifstream& f_in) override;
    void show_info() override;
};

#endif // TOOL_H
