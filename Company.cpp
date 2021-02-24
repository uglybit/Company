#include "Company.h"
#include "windows.h"

Company::Company()
{
    storage = new Storage;
    current_employee = 0;
}


Company::~Company()
{
    if (storage != nullptr) 
        delete storage;
        
    for (auto a : all_workers )
        if (a != nullptr) 
            delete a;
}

void Company::read_from_file()
{
    std::string employee_type;
    std::ifstream file_in(file_employee);
    if (!file_in)
    {
        std::cout << "Can not open file " << file_employee << '\n';
        return;
    }

    unsigned all_workers_size;
    file_in >> all_workers_size; // number of employees

    int n;
    file_in >> n; // value of the highest ID
    Employee::set_max_id_amount(n); // setting max id

    for (unsigned i = 0; i < all_workers_size; i++)
    {
        Employee* new_employee = nullptr;
        file_in >> std::ws;
        getline(file_in, employee_type, '#');

        if (employee_type == "production worker")
            new_employee = new Production_worker(employee_type);
        if (employee_type == "trader")
            new_employee = new Trader(employee_type);
        if (!new_employee) // didnt find so new_employee is still nullptr, end of program
        {
            std::cout << "Error while reading employee database\n"
                << "didn't recognize occupation\n";
            return;
        }

        all_workers.push_back(new_employee); // new_employee has proper value
        all_workers[i]->read_employee(file_in); // reading employee data
    }

    if (file_in)
        std::cout << "Employee datebase has been read properly\n";
    else {
        std::cout << "Unknown error while reading employee database\n"
            << "file read state: " << file_in.rdstate() << '\n';
    }
    file_in.close(); // closing file
    storage->read_all_resources(); // storage reading own data
    //require_key();
}


void Company::add_new_employee()
{                           
    Employee* new_employee = occupation_choosing(); 
                            // ^ function returns nullptr or pointer - allocates memory  
    std::cout << "Adres Company::new employee: " << new_employee << '\n';

    if (new_employee != nullptr) { 
         new_employee->fill_employee_data();
         all_workers.push_back(new_employee);
         save_to_file(); // automatically saving
         current_employee = all_workers.size();
    }
    else {
        return;
    }
}


Employee* Company::occupation_choosing()
{
    bool quit = false;
    char occupation;

    std::cout << "\nChoose occupation:\n"
         << " p - production worker \n"
         << " t - trader \n\n"
         << " m - Main menu\n";

    Employee* employee = nullptr;

    std::cin >> occupation; // add validation
    do {
        switch (occupation)
        {
        case 'p': employee = new Production_worker(); break;
        case 't': employee = new Trader(); break;
        case 'm': quit = true;
        default: std::cout << "Wrong command, try again\n";
        }
    } while (!employee && !quit); 
    return employee;
}


//returns iterator for current employee
Company::iterator Company::it_curr_emp()
{
    return all_workers.begin() + current_employee;
}


void Company::show_all_employees() // shows only personal info from abstract class
{
    if (all_workers.size() == 0) {
        std::cout << "No employee in database\n";
    } else {
        system("cls");
        std::cout << "\nNumber of employees: " << Employee::get_number_of_employee() << '\n';
        for (auto a : all_workers)
            a->show_personal_info();
    }

    std::cout << std::string(100 , '-') << '\n';
    require_key();
}


void Company::find_employee()
{
    bool found = false;
    bool quit  = false;
    char choice;

    do
    {
        //system("cls");
        std::cout << "\n--> FIND EMPLOYEE\n\n"
             << " 1 -  Search by surname\n"
             << " 2 -  Search by employee id\n\n"
             << " m -  Main menu\n\n";

        std::cin >> choice;
        switch(choice)
        {
            case '1': found = search_by_surname(); break;
            case '2': found = search_by_id(); break;
            case 27 : quit = true;
        }
    }while(!found && !quit);

    if (found)
        employee_menu(); // if found then shows menu
    else
        return;

}


bool Company::search_by_surname()
{
    std::string surname;
    unsigned counter = 0; // counter for persons with the same name
    std::cout << "\nEnter surname: ";
    std::cin >> std::ws; // clearing white spaces
    getline(std::cin, surname, '\n');

    for (unsigned i = 0; i < all_workers.size(); i++)
    {
        if (surname == all_workers[i]->get_surname() ) // if there is matching name
        {
            all_workers[i]->show_personal_info(); // shows personal info with items
            ++counter; // increasnig matching name counter
            current_employee = i; // sets current employee
        }
    }
    
    if (counter == 1) // only one person found, end of function
        return true;

    if ( counter == 0 )  { // no matching name
        std::cout << "No match for: " << surname << '\n' << '\n';
        require_key();
        return false;
    }

    if ( counter > 1 ) // more then one surname match --> searching by id
    {
        std::cout << "Matching surname: \"" << surname << "\":  " << counter << '\n';

        if (search_by_id()) // sets variable: current_employee and shows info if found
            return true;
        else
            return false;
    }
}


bool Company::search_by_id() // function is invoking when find by surname found more than one person
{
    unsigned id_number;
    std::cout << "\nChoose employee id: " << '\n';
    do
    {
        std::cin >> id_number;
        if ( data_validation("\nEmployee ID must be integer number!\n")) // wrong data
            continue; 
        else if (id_number < 1 || id_number > Employee::get_max_id_amount()) // if the chosen id is bigger than number of employee
            std::cout << "Wrong id! Try again: ";
        else break; // evertyhing is ok - breaking loop
    }while(true);

    for (unsigned i = 0; i < all_workers.size(); i++)
    {
        if (id_number  == all_workers[i]->get_employee_id() ) // if found employee id
        {
            current_employee = i; 
            //system("cls");
            all_workers[current_employee]->show_personal_info();
            return true;
        }
    }

    std::cout << "Did not find id: " << id_number << ". Check id and try again\n";
    return false;
}


// add resource from storage to employee
void Company::give_resource(Employee* empl, Storage* stor)
{
    if (empl->get_resource(stor)) {
        storage->save_all_resources();
    }
}


void Company::employee_menu() // shows when serching function returned true
{
    bool quit = false;
    char menu_option;
    do
    {
       // system("cls");
        std::cout << "\n--> EMPLOYEE MANAGEMENT\n\n";
        all_workers[current_employee]->show_employee_info();

        std::cout << "\na - Add item"
             << "\nr - Return item"
             << "\ne - Edit personal info"
             << "\nv - Move employee"
             << "\nd - Delete employee\n"
             << "\nm - Main menu\n";

        std::cin >> menu_option;
         switch(menu_option)
         {
             case 'a': give_resource(all_workers[current_employee], storage); break; // gives a tool or device from storage
             case 'r': all_workers[current_employee]->return_resource(storage); break; // returns resource to storage
             case 'e': all_workers[current_employee]->edit_personal_info(); break;
             case 'v': move_employee(); break;  // moves employee in another position
             case 'd': remove_employee(); 
             case 'm': quit = true;  // Esc
             default: std::cout << "Wrong command, try again\n";
         }

     }while(!quit);

//     std::cout << "\nDo you want to save the changes?\n";
//     if ( !confirmation()) return;

     //system("cls");
     save_to_file(); // automaticaly saving after changes OR NOT!! - NOT GOOD
     require_key();
}


void Company::remove_employee() // option delete employee from Company::menu_employee 
{
    system("cls");
    std::cout << "Do you want to delete this employee?\n";
    all_workers[current_employee]->show_personal_info();

    if ( !confirmation()) // user doesn't want to delete, return
        return;

    // before deleting employee must return all tools/devices
    while(all_workers[current_employee]->get_number_of_itmes() > 0)
    {
        std::cout << "Return all items to storage\n";
        all_workers[current_employee]->return_resource(storage);
    }

    delete all_workers.at(current_employee); // only frees memory - deleting address
    iterator i = it_curr_emp(); // sets iterator for current employee in container
    all_workers.erase(i); // deletes element from vector, decreasing size of vector
}


void Company::move_employee()
{
    Employee* employee = occupation_choosing(); // returns new object or nullptr

    if (!employee) // if there something gone wrong
    {
         std::cout << "Cannot move the employee\n";
         Sleep(3000);
         return;
    }

    //system("cls");
    std::cout << "Do you want to move this employee?\n";
    all_workers[current_employee]->show_personal_info();

    if ( !confirmation()) return; //user doesn't want to move employee

    while(all_workers[current_employee]->get_number_of_itmes() > 0) // returning tools/devices
    {
        std::cout << "\nReturn all items to storage\n";
        all_workers[current_employee]->return_resource(storage);
    }
    employee->copy_basic_info(all_workers[current_employee]); // copy info then
    delete all_workers.at(current_employee); // deleting employee

    iterator it = it_curr_emp();  // setting iterator   
    all_workers.erase(it); // erase from vector
    all_workers.push_back(employee); // adding moving employee

    current_employee = all_workers.size() -1; // setting current employee
}


void Company::save_to_file()
{
    std::ofstream file_out(file_employee);

    if ( !file_out )
    {
        std::cout << "Can not open file " << file_employee << '\n';
        return;
    }

    file_out << Employee::get_number_of_employee() << '\n'; // how many employees
    file_out << Employee::get_max_id_amount() << '\n'; // for adding ID properly, save the biggest ID
    for (auto a : all_workers ) a->save_employee(file_out); // saving to file

    if (file_out) std::cout << "Employee database has been saved properly.\n";
    file_out.close(); 
/**    storage->save_all_resources(); // saving resources in another file */
    //Sleep(2000);
}


