#include "Resources.h"

int Resources::resources_counter = 0; // static

Resources::Resources(std::string name) : resource_name{name}
{
    resource_id = ++resources_counter;
}

