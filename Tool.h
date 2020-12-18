#ifndef TOOL_H
#define TOOL_H

#include "Resources.h"
#include <ctime>

/*
  Class Tool represents tools that can possess only Blue_collar worker.
  Functions allow to: show info, read/save tool to file.
*/

class Tool : public Resources
{
    double tool_price;
    string next_inspection_date;
public:
    Tool() : Resources() {}
    explicit Tool(string name, double pr);
    explicit Tool(int n) : Resources(n)  {}
    ~Tool() override { std::cout << "Destruktor Tool " << this << "\n"; }

    Res_type recognize_type() const override {  return Res_type::Tool; }
    void save_resource(std::ofstream& f_out) override;
    void read_from_file(std::ifstream& f_in) override;
    void show_info() override;
    string next_test_date();
};


#endif // TOOL_H
