#pragma once

#include "Payment.h"

class Log
{
public:
    // Initializes the log
    Log() { _count = 0; }

    // Returns the current number of abstraction objects
    size_t get_count() const { return _count; }

    // Returns stored abstraction object by its index or default object if index is invalid
    Payment get_item(size_t i) const { return (i < _count) ? _items[i] : Payment{}; }

    // From passed property values, creates and adds new abstraction object in an array _items
    // (replace parameters to match your property types and identifiers)
    void add_item(
        const std::string& cardNumber, 
        const std::string& currency, 
        const int& amountCents, 
        const Payment::CardType cardType,
        const Payment::date_time& dateTime
    );

    // Looks for a matching abstraction object and returns the first found or default object
    Payment find_item(const Payment& query) const;

    Payment find_largest_payment() const;
private:
    // The maximum number of abstraction objects that can be stored
    static const size_t MAX_SIZE{ 10 };

    // An array container for storing abstraction objects
    Payment _items[Log::MAX_SIZE];

    // The number of currently stored abstraction objects in the array _items
    size_t _count;
};

