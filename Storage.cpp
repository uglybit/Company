#include "Storage.h"


Storage::~Storage() 
{
    for (auto a : devices_in_storage)
        if (a != nullptr)
            delete a;

    for (auto a : tools_in_storage)
        if (a != nullptr)
            delete a;
}


void Storage::show_menu()
{
    bool quit = false;
    char menu_option;
    do
    {
        //system("cls");
        std::cout << "\n--> STORAGE\n\n"
             << " d - Show devices\n"
             << " t - Show tools\n"
             << " v - Add device\n"
             << " o - Add tool\n"
             << " m - Main menu\n";

        std::cin >> menu_option;
        switch(menu_option)
        {
            case 'd': show_devices();
                        require_key(); break;
            case 't': show_tools();
                        require_key(); break;
            case 'v': add_new_device(); break;
            case 'o': add_new_tool(); break;
            case 'm': /*system("cls");*/ quit = true; break; // to main Menu
            default: std::cout << "Wrong commmand, try again" << '\n';
        }
    }while(!quit);
}

void Storage::separate_records() 
{
    std::cout << '\n' << std::string(80 , '-') << '\n';
}


// show devices (only for white collar)
unsigned Storage::show_devices()
{
    unsigned quantity = devices_in_storage.size();
    separate_records();
    if (quantity == 0) std::cout << "\n<empty>\n";

    for (unsigned i = 0; i < quantity; i++)
    {
        std::cout << i + 1 << ". ";
        devices_in_storage[i]->show_info();
        separate_records();
    }

    return quantity;
}


// show tools (only for blue collar)
unsigned Storage::show_tools()
{
    unsigned quantity = tools_in_storage.size();
    separate_records();
    if (quantity == 0) std::cout << "\n<empty>\n";

    for (unsigned i = 0; i < quantity; i++)
    {
        std::cout << i + 1 << ". ";
        tools_in_storage[i]->show_info();
        separate_records();
    }

    return quantity;
}


// saving to file all resources: tools and devices
void Storage::save_all_resources()
{
    std::ofstream f_out(data_file_name);

    if(!f_out)
    {
        std::cout << "Can not open file " << data_file_name << '\n';
        return;
    }

    f_out << devices_in_storage.size() << '\n';

    for ( unsigned i = 0; i < devices_in_storage.size(); i++)
    {
            devices_in_storage[i]->save_resource(f_out);
    }

    f_out << tools_in_storage.size() << '\n';

    for ( unsigned i = 0; i < tools_in_storage.size(); i++)
    {
            tools_in_storage[i]->save_resource(f_out);
    }

    if (f_out) std::cout << "Storage database has been saved properly\n";

    f_out.close();
}


// reading all resources from file: tools and devices
void Storage::read_all_resources() 
{
    std::ifstream f_in(data_file_name);

    if(!f_in)
    {
        std::cout << "Can not open file " << data_file_name << '\n';
        return;
    }

    read_all_devices(f_in);
    read_all_tools(f_in);
    if (f_in)
        std::cout << "Storage database has been read properly\n";
    else
        std::cout << "Error while reading storage database.\n";
    f_in.close();
}


void Storage::read_all_devices(std::ifstream& f_in) 
{
    unsigned size_devices;
    f_in >> size_devices;

    for (unsigned i = 0; i < size_devices; i++) 
    {
        devices_in_storage.push_back(new Device);
        devices_in_storage.back()->read_from_file(f_in);
    }
}


void Storage::read_all_tools(std::ifstream& f_in) 
{
    unsigned size_tools;
    f_in >> size_tools;
    std::cout << "Size tools: " << size_tools << '\n';

    for (unsigned i = 0; i < size_tools; i++) 
    {
        tools_in_storage.push_back(new Tool);
        tools_in_storage.back()->read_from_file(f_in);
    }
}


// transfer device from storage to White collar worker
Resources* Storage::lease_device(unsigned device_number) 
{
    //std::cout << "Devices in storage size:" << devices_in_storage.size() << '\n';
    if ((device_number < 0) || (device_number >= devices_in_storage.size() ) ) {
        //std::cout <<"First nullptr w lease device\m";
        return nullptr;
    }

    std::cout << "Save changes?\n";
    if (confirmation() )
        save_all_resources();
    else
        return nullptr;

    Resources *device = devices_in_storage[device_number];

    auto it = devices_in_storage.begin() + device_number;
    //devices_in_storage[device_number] = nullptr;
    devices_in_storage.erase(it);
    return device;
}

 
// transfer device from storage to Blue collar worker
Resources* Storage::lease_tool(unsigned tool_number) 
{
    if ((tool_number < 0) || (tool_number >= tools_in_storage.size()) )
        return nullptr;

    std::cout << "Save changes?\n";
    if (confirmation() )
        save_all_resources();
    else
        return nullptr;
    Resources *tmp = tools_in_storage[tool_number];

    auto it = tools_in_storage.begin() + tool_number;
    //delete   tools_in_storage[tool_number];
    //tools_in_storage[tool_number] = nullptr;
    tools_in_storage.erase(it);
    return tmp;
}


// transfer resource from Blue/White collar worker
bool Storage::take_resource(Resources* resource)
{
    if (resource == nullptr) return false;

    switch (resource->recognize_type())
    {
    case Res_type::Resources: return false;
    case Res_type::Device:
        devices_in_storage.push_back(resource); break;
    case Res_type::Tool:
        tools_in_storage.push_back(resource); break;
    }
    return true;
}


// add new device to storage
void Storage::add_new_device()
{
    // system("cls");
    std::string name;
    std::string brand;
    unsigned int quantity;

    std::cout << "\n--> ADD DEVICE TO STORAGE\n";
    std::cout << "Device name: ";
    std::cin >> name;
    std::cout << "Brand: ";
    std::cin >> brand;
    std::cout << "Quantity: ";
    std::cin >> quantity;

    std::cout << "przed petla\n";
    for (unsigned i = 0; i < quantity; i++)
    {
        std::cout << "W petli\n";
        devices_in_storage.push_back(new Device(name, brand));
        std::cout << "Adres Storage::Add new Device: " << devices_in_storage.back() << '\n';
    }

    std::cout << "Do you want to save changes? \n";
    if (confirmation())
        save_all_resources();
}


void Storage::add_new_tool() 
{
    // system("cls");
    std::string name;
    double price;
    int quantity;
   
    std::cout << "\n--> ADD TOOL TO STORAGE\n";
    std::cout << "Tool name: ";
    std::cin >> name;
    std::cout << "Price: ";
    std::cin >> price;
    std::cout << "Quantity: ";
    std::cin >> quantity;
    std::cout << "Wczytalo\n";

    for (int i = 0; i < quantity; i++)
    {
        tools_in_storage.push_back(new Tool(name, price));
        std::cout << "Adres Storage::new tool: " << tools_in_storage.back() << '\n';
    }

    std::cout << "Do you want to save changes? \n";
    if ( confirmation() )
        save_all_resources();
}