// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
        *this = src;
    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
        aloc_slots = 0;
        used_slots = 0;     //need these to be zero for reserve to work properly
        reserve(rhs.aloc_slots);
        for(int i = 0; i < rhs.used_slots; i++){
            company_array[i] = rhs.company_array[i];    //uses company.cpp "=" operator to copy each company
            used_slots++;                               //from rhs into this database's company array
        }
    }
    
    
    database::~database() {
        delete []company_array;     //deletes company array
        aloc_slots = 0;
        used_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);
        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        company* newarr = new company[new_capacity];
        for (int i = 0; i < used_slots; ++i) { // copy company into my new array (newarr)
            newarr[i] = company_array[i]; //looping + copying etc.
        }
        delete [] company_array; // delete old company array
        company_array = newarr; // swap!
        aloc_slots = new_capacity; // super important but only for insert company i think (i worked from here down so i could be so wrong)
    }

    bool database::insert_company(const std::string &entry) {
        Debug("Insert company..." << std::endl);
        assert(entry.length() > 0);
        size_type pos = search_company(entry);
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND)
            return false;
        if (aloc_slots == used_slots)   // check to make sure u have space in database!!
            reserve(aloc_slots + 1);    // if not, add space for 1 more!
        company company_entry(entry); // create new company object to add !
        company_array[used_slots] = company_entry; // garunteed to be space cuz of the reserve!
        used_slots++;
        return true;
    }

    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);
        assert(company.length() > 0 && product_name.length() > 0);
        //find the index of it!! ->
        size_type company_index = search_company(company);
        if (company_index == COMPANY_NOT_FOUND) // check!!!!
            return false;
        company_array[company_index].insert(product_name, price);
        return true;
    }

    bool database::erase_company(const std::string &company) {
        size_type company_index = search_company(company);
        if (company_index == COMPANY_NOT_FOUND) //negative 1
            return false;
        company_array[company_index] = company_array[used_slots-1];
        //swaps the last company into the place of the one that we want to delete!!
        --used_slots;
        return true;
    }

    bool database::erase_item(const std::string& cName, const std::string& pName) {
        assert(cName.length() > 0 && pName.length() > 0);
        // set index to location of input name
        size_type target_index = search_company(cName);
        if(target_index = -1)
            return false;
        return company_array[target_index].erase(pName); // erases it from list (wohoo!!)
    }

    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
        for (int i = 0; i < used_slots; ++i) { // ++i so u dont have to do the i+1 and then i wont get a seg fault (im so smart ik)
            if (company_array[i].get_name() == company)
                return i; // index of the found name
        }
        return COMPANY_NOT_FOUND; //return -1
    }

    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);
        size_type c_index = search_company(cName);
        if (c_index == COMPANY_NOT_FOUND)
            return false;
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        return true;
    }

    void database::print_companies() {
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}
#endif