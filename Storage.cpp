#include "Storage.h"

using namespace std;

Storage::~Storage() // frees memory
{
    for (auto a : devices_in_storage)
        if (a != nullptr)
            delete a;

    for (auto a : tools_in_storage)
        if (a != nullptr)
            delete a;
}


// storage menu
void Storage::show_menu()
{
    bool quit = false;
    char choice;
    do
    {
        //system("cls");
        cout << "\n--> STORAGE\n\n"
             << " d - Show devices\n"
             << " t - Show tools\n"
             << " v - Add device\n"
             << " o - Add tool\n"
             << " m.   Main menu\n";

        cin >> choice;
         switch(choice)
         {
            case 'd': show_devices();
                      require_key(); break;
            case 't': show_tools();
                      require_key(); break;
            case 'v': add_new_device(); break;
            case 'o': add_new_tool(); break;
            case 'm': /*system("cls");*/ quit = true; break; // to main Menu
            default: cout << "Wrong commmand, try again" << endl;
         }
    }while(!quit);
}


// show devices (only for white collar)
unsigned Storage::show_devices()
{
    unsigned quantity = devices_in_storage.size();
    cout << endl << string(60 , '-') << endl;

    for (unsigned i = 0; i < quantity; i++)
    {
        cout << i + 1 << ". ";
        devices_in_storage[i]->show_info();
        cout << string(60 , '-') << endl;
    }

    return quantity;
}


// show tools (only for blue collar)
unsigned Storage::show_tools()
{
    unsigned quantity = tools_in_storage.size();
    cout << endl << string(80 , '-') << endl;

    for (unsigned i = 0; i < quantity; i++)
    {
        cout << i + 1 << ". ";
        tools_in_storage[i]->show_info();
        cout << string(80 , '-') << endl;
    }

    return quantity;
    //
}


// saving to file all resources: tools and devices
void Storage::save_all_resources()
{
    std::ofstream f_out(data_file_name);
    if(!f_out)
    {
        cout << "Can not open file " << data_file_name << endl;
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

    if (f_out) cout << "Storage database has been saved properly\n";
    f_out.close();
}


// reading all resources from file: tools and devices
void Storage::read_all_resources()
{
    unsigned size_devices;
    unsigned size_tools;

    std::ifstream f_in(data_file_name);

    if(!f_in)
    {
        cout << "Can not open file " << data_file_name << endl;
        return;
    }

    // reading devices
    f_in >> size_devices;
    //cout << "Size devices: " << size_devices << endl; // TEST

    for (unsigned i = 0; i < size_devices; i++) 
    {
        devices_in_storage.push_back(new Device);
       // std::cout << "Address Storage::new Device: " << devices_in_storage.back() << std::endl; // TEST
        devices_in_storage.back()->read_from_file(f_in);
    }
    //cout << "Size of devices vector: " << devices_in_storage.size() << endl; // TEST

    //reading tools
    f_in >> size_tools;
    cout << "Size tools: " << size_tools << endl;

    for (unsigned i = 0; i < size_tools; i++) 
    {
        tools_in_storage.push_back(new Tool);
        //std::cout << "Address Storage::new Tool: " << tools_in_storage.back() << std::endl; // TEST
        tools_in_storage.back()->read_from_file(f_in);
    }

    //cout << "Size of tools vector: " << tools_in_storage.size() << endl; // TEST

    if (f_in)
        cout << "Storage database has been read properly\n";
    else
        cout << "Error while reading storage database.\n";
    f_in.close();
}


// transfer device from storage to White collar worker
Resources* Storage::lease_device(unsigned nr) 
{
    //cout << "Devices in storage size:" << devices_in_storage.size() << endl;
    if ((nr < 0) || (nr >= devices_in_storage.size() ) ) {
        //cout <<"First nullptr w lease device\m";
        return nullptr;
    }

    cout << "Save changes?";
    if (confirmation() )
        save_all_resources();
    else
        return nullptr;

    Resources *tmp = devices_in_storage[nr];

    auto it = devices_in_storage.begin() + nr;
    //devices_in_storage[nr] = nullptr;
    devices_in_storage.erase(it);
    return tmp;
}

 
// transfer device from storage to Blue collar worker
Resources* Storage::lease_tool(unsigned nr) 
{
    if ( (nr < 0) || (nr >= tools_in_storage.size()) )
        return nullptr;

    cout << "Save changes?";
    if (confirmation() )
        save_all_resources();
    else
        return nullptr;
    Resources *tmp = tools_in_storage[nr];

    auto it = tools_in_storage.begin() + nr;
    //delete   tools_in_storage[nr];
    //tools_in_storage[nr] = nullptr;
    tools_in_storage.erase(it);
    return tmp;
}


// transfer resource from Blue/White collar worker
bool Storage::take_resource(Resources* tmp)
{
    if (tmp == nullptr) return false;

    switch (tmp->recognize_type())
    {
    case Res_type::Resources: return false;
    case Res_type::Device:
        devices_in_storage.push_back(tmp); break;
    case Res_type::Tool:
        tools_in_storage.push_back(tmp); break;
    }
    return true;
}


// add new device to storage
void Storage::add_new_device()
{
    // system("cls");
    cout << "\n--> ADD DEVICE TO STORAGE\n";
    string name;
    string brand;
    unsigned quantity;
    cout << "Device name: ";
    cin >> name;
    cout << "Brand: ";
    cin >> brand;
    cout << "Quantity: ";
    cin >> quantity;

    for (unsigned i = 0; i < quantity; i++)
    {
        devices_in_storage.push_back(new Device(name, brand));
        std::cout << "Adres Storage::Add new Device: " << devices_in_storage.back() << std::endl;
    }

    cout << "Do you want to save changes? \n";
    if (confirmation())
        save_all_resources();
}


// add new tool to storage
void Storage::add_new_tool() 
{
   // system("cls");
    cout << "\n--> ADD TOOL TO STORAGE\n";
    string name;
    double price;
    unsigned quantity;
    cout << "Tool name: ";
    cin >> name;
    cout << "Price: ";
    cin >> price;
    cout << "Quantity: ";
    cin >> quantity;

    for (unsigned i = 0; i < quantity; i++)
    {
        tools_in_storage.push_back(new Tool(name, price));
        std::cout << "Adres Storage::new tool: " << tools_in_storage.back() << std::endl;
    }

    cout << "Do you want to save changes? \n";
    if ( confirmation() )
        save_all_resources();
}


