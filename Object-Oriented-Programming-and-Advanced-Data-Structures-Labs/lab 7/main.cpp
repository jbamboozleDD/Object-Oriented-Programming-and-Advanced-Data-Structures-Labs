#include "node.h"
#include "company.h"
#include "database.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using namespace coen79_lab7;

int main(){
    cout << "Testing constructor...!" << endl;
    cout << endl;
    database myDB1;

    cout << "Inserting company names...!" << endl;
    cout << endl;
    myDB1.insert_company("Intel");
    myDB1.insert_company("NVIDIA");
    myDB1.insert_company("Cypress");

    cout << "Printing myDB1..." << endl;
    myDB1.print_companies();
    cout << endl;

    cout << "Inserting company names to invoke reserve...!" << endl;
    myDB1.insert_item("Intel", "Core i7", 300.0);
    myDB1.insert_item("Intel", "Core i5", 200.0);
    cout << endl;

    cout << "Printing myDB1..." << endl;
    myDB1.print_items_by_company("Intel");
    cout << endl;

    cout << "Inserting company names to invoke reserve...!" << endl;
    myDB1.insert_company("Qualcomm");
    myDB1.insert_company("Apple");
    cout << endl;

    cout << "Inserting product names...!" << endl;
    myDB1.insert_item("Apple", "iPhone 6", 400.0);
    myDB1.insert_item("Apple", "iPhone X", 900.0);
    cout << endl;

    cout << "Printing products of Apple and Intel..." << endl;
    myDB1.print_items_by_company("Apple");
    myDB1.print_items_by_company("Intel");
    cout << endl;

    cout << "Creating myDB2 on heap..." << endl;
    database *myDB2 = new database();
    myDB2->insert_company("Google");
    myDB2->insert_item("Google", "glass", 1000);
    myDB2->insert_item("Google", "phone", 1000);
    myDB2->insert_item("Google", "Android", 0);
    myDB2->insert_item("Google", "Tensorflow", 0);
    myDB2->erase_item("Google", "phone");
    cout << endl;

    cout << "Printing myDB2..." << endl;
    myDB2->print_items_by_company("Google");
    cout << endl;

    cout << "Creating myDB3 on heap..." << endl;
    database *myDB3 = new database();
    cout << endl;

    cout << "Assigning myDB2 to myDB3..." << endl;
    *myDB3 = *myDB2;
    cout << "copying elements of database..." << endl;
    cout << "Printing myDB3..." << endl;
    myDB3->print_items_by_company("Google");
    myDB2->erase_company("Google");
    cout << endl;

    cout << "Printing myDB2..." << endl;
    myDB2->print_items_by_company("Google");

    cout << "Printing myDB3..." << endl;
    myDB3->print_items_by_company("Google");
    cout << endl;

    cout << "Deleting myDB2 and myDB3..." << endl;
    delete myDB2;
    delete myDB3;
    return 0;
}