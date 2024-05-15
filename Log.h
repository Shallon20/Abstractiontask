#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <optional>
#include <stdexcept>
#include <exception>
#include "Payment.h"
//#include "PaymentSpec.h"
#include "Item.h"
#include "ItemSpec.h"

class Log
{
public:
    // Initializes the log
    Log() :_count{ 0 } { }
    size_t get_count() const { return _count; }
    const Item & operator[](size_t i) const 
    {
        return get_item(i); }

    const Item & get_item(size_t i) const
    {
        if (i < _count) 
            return *_items[i];
        throw std::out_of_range("Invalid index value");
    }

    /*Log(const std::string & csv_file_name)
    :Log(){ this->load(csv_file_name); }
*/
    void save(const std::string & csv_file_name) const;
    void load(const std::string & csv_file_name);
    // Returns the current number of abstraction objects
    

    // From passed property values, creates and adds new abstraction object in an array _items
    // (replace parameters to match your property types and identifiers)
    void add_item(std::shared_ptr<Item> newItem);
    const Item & find_item(const ItemSpec & spec_query) const;

    // Looks for a matching abstraction object and returns the first found or default object
    
    const Payment & find_largest_payment() const;

    double find_average_amount() const;
private:
    // The maximum number of abstraction objects that can be stored
    static const size_t MAX_SIZE{ 10 };

    // An array container for storing abstraction objects
    std::shared_ptr<Item> _items[Log::MAX_SIZE];

    // The number of currently stored abstraction objects in the array _items
    size_t _count;
    
};
