#pragma once

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <stdexcept>
#include <exception>

//#include "Payment.h"
#include "Item.h"
#include "ItemSpec.h"
//#include "PaymentSpec.h"

class Log
{
public:
    // Initializes the log
    Log() :_count{ 0 } { }
    // Returns the current number of abstraction objects
    size_t get_count() const { return _count; }

    const Item & operator[](size_t i) const {return get_item(i); }

    const Item & get_item(size_t i) const
    {
        if (i < _count) 
            return *_items[i];
        
        throw std::out_of_range("Invalid index value");
    }

    // From passed property values, creates and adds new abstraction object in an array _items
  /*  void add_item(
        unsigned id,
        const std::string& cardNumber, 
        const std::string& currency, 
        const int& amountCents, 
        const Payment::date_time& dateTime,
        shared::shared_ptr<const ItemSpec> spec
    );*/
    void add_item(std::shared_ptr<Item> new_item);

    const Item& find_item(const ItemSpec& spec_query) const;

    void save(const std::string & csv_file_name) const;
    void load(const std::string & csv_file_name);
    
    // Looks for a matching abstraction object and returns the first found or default object
    //Payment find_item(const Payment& query) const;
    //Payment find_item(const PaymentSpec& query_spec) const;

    //double find_largest_payment() const;

    //double find_average_amount() const;
    //Payment find_largest_payment() const;

    //double find_average_amount() const;
private:
    // The maximum number of abstraction objects that can be stored
    static const size_t MAX_SIZE{ 10 };

    // An array container for storing abstraction objects
    std::shared_ptr<Item> _items[Log::MAX_SIZE];
    // The number of currently stored abstraction objects in the array _items
    size_t _count;
    
};