#include "Employee.h"

using namespace std;

int Employee::employee_counter = 0; // static
int Employee::max_id_amount = 0; // static


Employee::Employee()
{
    employee_id = ++max_id_amount; // ID will always increase, and never duplicate
    ++employee_counter; // increasing number of employess - is not equal to employee_id
}


Employee::Employee(string p) : position{ p }
{
    cout << "New employee from file: " << this << endl;
    ++employee_counter;
} // for reading from file only


Employee::~Employee() 
{
    cout << "destructor Employee\n"; employee_counter--; 
    for (auto a : employee_resources) {
        if (a != nullptr)
            delete a; // frees memory
    }
}


int Employee::show_employee_resources() 
{   
    cout << "\nEmployee's resources: \n";
    unsigned n = employee_resources.size();

    if (n == 0) cout << "\t<empty>\n"; // employee has no resources

    for (unsigned i = 0; i < n; i++)
    {
        cout << "\t" << i + 1 << ". ";
        employee_resources[i]->show_info(); // virtual
    }
    cout << string(100, '-') << endl;

    return employee_resources.size();
}


// return employee resource to storage
void Employee::return_resource(Storage* s)
{
    int quantity = show_employee_resources(); // virtual
    if (quantity <= 0) {
        return;
    }
    cout << "Choose number: ";

    int number;
    do // number validation
    {
        cin >> number;
        number -= 1;
        if (number >= 0 && number <= quantity)
            break;
    } while (true);

    bool b = s->take_resource(employee_resources[number]); // transfer resource to storage
    if (b == true) {
        auto it = employee_resources.begin() + number; // iterator for vector
        employee_resources[number] = nullptr;
        employee_resources.erase(it);
        nof_employee_tools--;
        s->save_all_resources();
    }
}


// transfer resource from storage to employee
bool Employee::get_resource(Storage* s)
{
    int number{};
    int quantity{};

    // recognize type of employee: 
    // Trader gets device, Production worker gets tool
    switch (this->recType())
    {
    case Emp_type::Employee:
        cout << "Uncorrect Employee type!";
        return false;
    case Emp_type::Trader:
        quantity = s->show_devices(); break;
    case Emp_type::Production_worker:
        quantity = s->show_tools(); break;
    }

    if (quantity <= 0) { // if storage is empty
        return false;
    }
    cout << "Choose number";

    do {
        cin >> number; // validation!!
        number -= 1;
        if (number >= 0 && number <= quantity) break;
    } while (true);

    Resources* tmp = nullptr;

    switch (this->recType()) // checking type of employee
    {
    case Emp_type::Employee:
        cout << "Error - wrong type of Employee";
        return false;
    case Emp_type::Trader:
        tmp = s->lease_device(number); break;
    case Emp_type::Production_worker:
        tmp = s->lease_tool(number); break;
    }

    if (tmp != nullptr) {
        employee_resources.push_back(tmp);
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
        string edition[7] = {
             "Name","Surname", "Birthday", "Join date", "Addres", "Phone", "Salary" };

        cout << "Edit:";
        for (int i = 0; i < 7; i++){ // shows records that can be changed
            cout << "\n\t" << i + 1 << ". " << edition[i];
        }
        cout << "\n\t0. Return" << "\nChoice: ";

        int choice; // validation !!
        cin >> choice;
        int n = choice -1;
        if ( n > 6 || n < 0 )  break; // the number must be 0<= n >=6
        cout << edition[n] << " edition: "; //
        cin >> ws;
        getline(cin, edition[n], '\n'); // writing change record temporary in table

        cout << "\nSave changes?\n";
        if ( !confirmation())
            return;

        switch(choice) // if changes was confirmed, original data will  be replaced
        {
            case 1: name =      edition[n]; break;
            case 2: surname =   edition[n]; break;
            case 3: birthday =  edition[n]; break;
            case 4: join_date = edition[n]; break;
            case 5: address =   edition[n]; break;
            case 6: phone =     edition[n]; break;
            case 7: salary =    stod(edition[n]); break; // conversion string to double
            case 0: quit = true;
            default : break;
        }
    }while(!quit);
}


void Employee::fill_employee_data()
{
    cout << "Name: ";        cin >> ws;
                             getline(cin, name,      '\n');
    cout << "Surname: ";     getline(cin, surname,   '\n');
    cout << "birthday: ";    getline(cin, birthday,  '\n');
    cout << "join_date: ";   getline(cin, join_date, '\n');
    cout << "address: ";     getline(cin, address,   '\n');
    cout << "phone: ";       getline(cin, phone,     '\n');
    cout << "salary: ";
    do {                // data validaion - salary is an integer
        cin >> salary;
        if (data_validation("Wrong data! Try again: "))
            continue;
        else
            break;
    }while(true);

    set_additional_options(); //virtual
}


void Employee::show_personal_info()
{
    cout << string(100, '-') << endl;
    cout << "ID: "            << employee_id
         << ". "              << name
         << " "               << surname
         << " position: "     << position
         << ", since: "       << join_date << fixed << cout.precision(2)
         << " salary: "       << salary
         << "\n\tBorn: "      << birthday
         << " phone: "        << phone
         << " address: "      << address;
    cout << get_additional_options();
    cout << endl;

}


// only for moving employee blue collar <-> white collar
void Employee::copy_basic_info(Employee* o) 
{
     name = o->name;
     surname = o->surname;
     birthday = o->birthday;
     join_date = o->join_date;
     address = o->address;
     phone = o->phone;
     salary = o->salary;
     employee_id = o->employee_id;
     nof_employee_tools = 0;
}


// company invokes this function
void Employee::read_basic_info(std::ifstream& f_in) 
{
    f_in >> employee_id;
    f_in >> ws;
    getline(f_in, name,      '#');
    getline(f_in, surname,   '#');
    getline(f_in, birthday,  '#');
    getline(f_in, join_date, '#');
    getline(f_in, address,   '#');
    getline(f_in, phone,     '#');
    f_in >> salary;
}


// company invokes this function
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