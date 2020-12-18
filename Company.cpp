#include "Company.h"
#include "windows.h"

using namespace std;

Company::Company()
{
    storage = new Storage;
    current_employee = 0;
}


Company::~Company() // frees memory
{
    if (storage != nullptr) 
        delete storage;
    for (auto a : all_workers )
        if (a != nullptr) 
            delete a;
}

void Company::read_from_file()
{
    string p;
    ifstream file_in(file_employee);
    if (!file_in)
    {
        cout << "Can not open file " << file_employee << endl;
        return;
    }

    unsigned all_workers_size;
    file_in >> all_workers_size; // number of employees

    int n;
    file_in >> n; // value of the highest ID
    Employee::set_max_id_amount(n); // setting max id

    for (unsigned i = 0; i < all_workers_size; i++)
    {
        Employee* tmp = nullptr;
        file_in >> ws;
        getline(file_in, p, '#');

        if (p == "production worker")
            tmp = new Production_worker(p);
        if (p == "trader")
            tmp = new Trader(p);
        if (!tmp) // didnt find so tmp is still nullptr, end of program
        {
            cout << "Error while reading employee database\n"
                << "didn't recognize occupation" << endl;
            return;
        }

        all_workers.push_back(tmp); // tmp has proper value
        all_workers[i]->read_employee(file_in); // reading employee data
    }

    if (file_in)
        cout << "Employee datebase has been read properly\n";
    else {
        cout << "Unknown error while reading employee database\n"
            << "file read state: " << file_in.rdstate() << endl;
    }
    file_in.close(); // closing file
    storage->read_all_resources(); // storage reading own data
    //require_key();
}


void Company::add_new_employee()
{
    Employee* e = occupation_choosing(); // function returns nullptr or pointer
    std::cout << "Adres Company::new employee: " << e << std::endl;

    if (e) {    // if there is not nullptr
         e->fill_employee_data();
         all_workers.push_back(e);
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
    char choice;

    cout << "\nChoose occupation:\n";
    cout << " p - production worker \n"
         << " t - trader \n\n"
         << " m - Main menu" << endl;

    Employee* emp = nullptr;

    cin >> choice;
    do {
        switch (choice)
        {
        case 'p': emp = new Production_worker(); break;
        case 't': emp = new Trader(); break;
        case 'm': quit = true;
        default: cout << "Wrong command, try again" << endl;
        }
    } while (!emp && !quit); 
    return emp;
}


//returns iterator for current employee
Company::iterator Company::it_curr_emp()
{
    return all_workers.begin() + current_employee;
}


void Company::show_all_employees() // shows only personal info from abstract class
{
    if (all_workers.size() == 0) {
        cout << "No employee in database\n";
    } else {
        system("cls");
        cout << "\nNumber of employees: " << Employee::get_number_of_employee() << endl;
        for (auto a : all_workers)
            a->show_personal_info();
    }

    cout << string(100 , '-') << endl;
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
        cout << "\n--> FIND EMPLOYEE\n\n"
             << " 1 -  Search by surname\n"
             << " 2 -  Search by employee id\n\n"
             << " m -  Main menu\n\n" << flush;

        cin >> choice;
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
    string s;
    unsigned counter = 0; // counter for persons with the same name
    cout << "\nEnter surname: ";
    cin >> ws; // clearing white spaces
    getline(cin, s, '\n');

    for (unsigned i = 0; i < all_workers.size(); i++)
    {
        if (s == all_workers[i]->get_surname() ) // if there is matching name
        {
            all_workers[i]->show_personal_info(); // shows personal info with items
            ++counter; // increasnig matching name counter
            current_employee = i; // sets current employee
        }
    }
    if (counter == 1) // only one person found, end of function
        return true;

    if ( counter == 0 )  { // no matching name
        cout << "No match for: " << s << endl << endl;
        require_key();
        return false;
    }

    if ( counter > 1 ) // more then one surname match --> searching by id
    {
        cout << "Matching surname: \"" << s << "\":  " << counter << endl;

        if (search_by_id()) // sets variable: current_employee and shows info if found
            return true;
        else
            return false;
    }
}


bool Company::search_by_id() // function is invoking when find by surname found more than one person
{
    unsigned n;
    cout << "\nChoose employee id: " << endl;
    do
    {
        cin >> n;
        if ( data_validation("\nEmployee ID must be integer number!\n")) // wrong data
            continue; //
        else if (n < 1 || n > Employee::get_max_id_amount()) // if the chosen id is bigger than number of employee
            cout << "Wrong id! Try again: ";
        else break; // evertyhing is ok - breaking loop
    }while(true);

    for (unsigned i = 0; i < all_workers.size(); i++)
    {
        if ( n == all_workers[i]->get_employee_id() ) // if found employee id
        {
            current_employee = i; 
            //system("cls");
            all_workers[current_employee]->show_personal_info();
            return true;
        }
    }

    cout << "Did not find id: " << n << ". Check id and try again" << endl;
    return false;
}


// add resource from storage to employee
void Company::give_resource(Employee* emp, Storage* s)
{
    if (emp->get_resource(s)) {
        storage->save_all_resources();
    }
}


void Company::employee_menu() // shows when serching function returned true
{
    bool quit = false;
    char choice;
    do
    {
       // system("cls");
        cout << "\n--> EMPLOYEE MANAGEMENT\n\n";
        all_workers[current_employee]->show_employee_info();

        cout << "\na - Add item"
             << "\nr - Return item"
             << "\ne - Edit personal info"
             << "\nv - Move employee"
             << "\nd - Delete employee\n"
             << "\nm - Main menu\n" << flush;

        cin >> choice;
         switch(choice)
         {
             case 'a': give_resource(all_workers[current_employee], storage); break; // gives a tool or device from storage
             case 'r': all_workers[current_employee]->return_resource(storage); break; // returns resource to storage
             case 'e': all_workers[current_employee]->edit_personal_info(); break;
             case 'v': move_employee(); break;  // moves employee in another position
             case 'd': remove_employee(); 
             case 'm': quit = true;  // Esc
             default: cout << "Wrong command, try again" << endl;
         }

     }while(!quit);

//     cout << "\nDo you want to save the changes?\n";
//     if ( !confirmation()) return;

     //system("cls");
     save_to_file(); // automaticaly saving after changes OR NOT!! - NOT GOOD
     require_key();
}


void Company::remove_employee() // option delete employee from Company::menu_employee 
{
    system("cls");
    cout << "Do you want to delete this employee?\n";
    all_workers[current_employee]->show_personal_info();

    if ( !confirmation()) // user doesn't want to delete, return
        return;

    // before deleting employee must return all tools/devices
    while(all_workers[current_employee]->get_number_of_itmes() > 0)
    {
        cout << "Return all items to storage\n";
        all_workers[current_employee]->return_resource(storage);
    }

    delete all_workers.at(current_employee); // only frees memory - deleting address
    iterator i = it_curr_emp(); // sets iterator for current employee in container
    all_workers.erase(i); // deletes element from vector, decreasing size of vector
}


void Company::move_employee()
{
    Employee* e = occupation_choosing(); // returns new object or nullptr

    if (!e) // if there something gone wrong
    {
         cout << "Cannot move the employee\n";
         Sleep(3000);
         return;
    }

    //system("cls");
    cout << "Do you want to move this employee?\n";
    all_workers[current_employee]->show_personal_info();

    if ( !confirmation()) return; //user doesn't want to move employee

    while(all_workers[current_employee]->get_number_of_itmes() > 0) // returning tools/devices
    {
        cout << "\nReturn all items to storage\n";
        all_workers[current_employee]->return_resource(storage);
    }
    e->copy_basic_info(all_workers[current_employee]); // copy info then
    delete all_workers.at(current_employee); // deleting employee

    iterator it = it_curr_emp();  // setting iterator
    
    
    all_workers.erase(it); // erase from vector
    all_workers.push_back(e); // adding moving employee
    

    current_employee = all_workers.size() -1; // setting current employee
}


void Company::save_to_file()
{
    ofstream file_out(file_employee);

    if ( !file_out )
    {
        cout << "Can not open file " << file_employee << endl;
        return;
    }

    file_out << Employee::get_number_of_employee() << '\n'; // how many employees
    file_out << Employee::get_max_id_amount() << '\n'; // for adding ID properly, save the biggest ID
    for (auto a : all_workers ) a->save_employee(file_out); // saving to file

    if (file_out) cout << "Employee database has been saved properly.\n";
    file_out.close(); // closing file
/**    storage->save_all_resources(); // saving resources in another file */
    //Sleep(2000);
}


