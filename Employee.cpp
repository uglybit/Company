#include "Employee.h"

int Employee::employee_counter = 0; // static
int Employee::max_id_amount = 0; // static


Employee::Employee()
{
    employee_id = ++max_id_amount; // ID will always increase, and never duplicate
    ++employee_counter; // increasing number of employess - is not equal to employee_id
}

Employee::~Employee() 
{
    std::cout << "destructor Employee\n"; 
    employee_counter--; 
    for (auto a : employee_resources) {
        if (a != nullptr)
            delete a; 
    }
}


// for reading from file only
Employee::Employee(std::string pos) : position{ pos }
{
    std::cout << "New employee from file: " << this << '\n';
    ++employee_counter;
} 


int Employee::show_employee_resources() 
{   
    std::cout << "\nEmployee's resources: \n";
    if (nof_employee_tools == 0) 
    {
        std::cout << "\t<empty>\n"; // employee has no resources
    }

    for (unsigned i = 0; i < nof_employee_tools; i++)
    {
        std::cout << "\t" << i + 1 << ". ";
        employee_resources[i]->show_info(); // virtual
    }
    std::cout << std::string(100, '-') << '\n';

    return nof_employee_tools;
}


// return employee resource to storage
void Employee::return_resource(Storage* storage)
{
    int quantity = show_employee_resources(); // virtual
    if (quantity <= 0) {
        return;
    }
    std::cout << "Choose number: ";

    int resource_number;
    do 
    {
        std::cin >> resource_number; // number validation
        resource_number -= 1;
        if (resource_number >= 0 && resource_number <= quantity)
            break;
    } while (true);

    bool resource_returned = storage->take_resource(employee_resources[resource_number]); // transfer resource to storage
    if (resource_returned) {
        auto it = employee_resources.begin() + resource_number; // iterator for vector
        employee_resources[resource_number] = nullptr;
        employee_resources.erase(it);
        nof_employee_tools--;
        storage->save_all_resources();
    }
}


// transfer resource from storage to employee
bool Employee::get_resource(Storage* storage)
{
    int resource_number{};
    unsigned resources_on_storage{};

    // Trader gets device, Production worker gets tool
    switch (this->recType())
    {
    case Emp_type::Employee:
        std::cout << "Uncorrect Employee type!";
        return false;
    case Emp_type::Trader:
        resources_on_storage = storage->show_devices(); break;
    case Emp_type::Production_worker:
        resources_on_storage = storage->show_tools(); break;
    }

    if (resources_on_storage == 0) { // if storage is empty
        return false;
    }
    std::cout << "Choose number";

    do {
        std::cin >> resource_number; // add validation 
        resource_number -= 1;
        if ((resource_number >= 0) && (resource_number <= resources_on_storage)) break;
    } while (true);

    Resources* resource = nullptr;

    switch (this->recType()) // checking type of employee
    {
    case Emp_type::Employee:
        std::cout << "Error - wrong type of Employee";
        return false;
    case Emp_type::Trader:
        resource = storage->lease_device(resource_number); break;
    case Emp_type::Production_worker:
        resource = storage->lease_tool(resource_number); break;
    }

    if (resource != nullptr) {
        employee_resources.push_back(resource);
        nof_employee_tools++;
        return true;
    }
    else {
        return false;
    }
}


void Employee::edit_personal_info()
{
    bool quit = false;
    do
    {
        //system("cls");
        show_personal_info();

        std::string edition[7] =
         { "Name","Surname", "Birthday", "Join date", "Addres", "Phone", "Salary" };

        std::cout << "Edit:";
        for (int i = 0; i < 7; i++){ // shows records that can be changed
            std::cout << "\n\t" << i + 1 << ". " << edition[i];
        }
        std::cout << "\n\t0. Return" << "\nChoice: ";

        int position_to_edit; // validation !!
        std::cin >> position_to_edit;

        int array_index = position_to_edit -1;
        if ( array_index > 6 || array_index < 0 )  
            break; 

        std::cout << edition[array_index] << " edition: "; //
        std::cin >> std::ws;
        getline(std::cin, edition[array_index], '\n'); // writing change record temporary in table

        std::cout << "\nSave changes?\n";
        if ( !confirmation())
            return;

        switch(position_to_edit) // if changes was confirmed, original data will  be replaced
        {
            case 1: name =      edition[array_index]; break;
            case 2: surname =   edition[array_index]; break;
            case 3: birthday =  edition[array_index]; break;
            case 4: join_date = edition[array_index]; break;
            case 5: address =   edition[array_index]; break;
            case 6: phone =     edition[array_index]; break;
            case 7: salary =    stod(edition[array_index]); break; 
            case 0: quit = true;
            default : break;
        }
    }while(!quit);
}


void Employee::fill_employee_data()
{
    std::cout << "Name: ";        
    std::cin >> std::ws; 
    getline(std::cin, name, '\n');
    std::cout << "Surname: ";     getline(std::cin, surname,   '\n');
    std::cout << "birthday: ";    getline(std::cin, birthday,  '\n');
    std::cout << "join_date: ";   getline(std::cin, join_date, '\n');
    std::cout << "address: ";     getline(std::cin, address,   '\n');
    std::cout << "phone: ";       getline(std::cin, phone,     '\n');
    std::cout << "salary: ";

    do {                
        std::cin >> salary;
        if (data_validation("Wrong data! Try again: "))
            continue;
        else
            break;
    }while(true);

    set_additional_options(); //virtual
}


void Employee::show_personal_info()
{
    std::cout << std::string(100, '-') << '\n'
         << "ID: "            << employee_id
         << ". "              << name
         << " "               << surname
         << " position: "     << position
         << ", since: "       << join_date << std::fixed << std::cout.precision(2)
         << " salary: "       << salary
         << "\n\tBorn: "      << birthday
         << " phone: "        << phone
         << " address: "      << address;
    std::cout << get_additional_options() << '\n';
}


// only for moving employee blue collar <-> white collar
void Employee::copy_basic_info(Employee* employee) 
{
     name = employee->name;
     surname = employee->surname;
     birthday = employee->birthday;
     join_date = employee->join_date;
     address = employee->address;
     phone = employee->phone;
     salary = employee->salary;
     employee_id = employee->employee_id;
     nof_employee_tools = 0;
}


void Employee::read_basic_info(std::ifstream& f_in) 
{
    f_in >> employee_id;
    f_in >> std::ws;
    getline(f_in, name,      '#');
    getline(f_in, surname,   '#');
    getline(f_in, birthday,  '#');
    getline(f_in, join_date, '#');
    getline(f_in, address,   '#');
    getline(f_in, phone,     '#');
    f_in >> salary;
}


void Employee::save_basic_info(std::ofstream& f_out) 
{
    f_out << position << '#'; // # <-- for getline
    f_out << employee_id << " " << name << '#' << surname << '#' << birthday << '#'
          << join_date << '#' << address << '#' << phone << '#' << salary << " ";
}


void Employee::show_employee_info()
{
    show_personal_info();
    show_employee_resources(); 
}

