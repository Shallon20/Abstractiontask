#include "Log.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

void Log::add_item(
    const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
	const Payment::date_time& dateTime,
    const std::shared_ptr<const PaymentSpec>& spec
) {
    if (_count < Log::MAX_SIZE)
    {
        Payment new_item(cardNumber, currency, amountCents, dateTime, spec);
        _items[_count] = new_item;
        _count++;
    }
}

Payment Log::find_item(const Payment& query) const
{ 
    auto query_spec_p = query.get_spec();

    for (size_t i = 0; i < _count; i++)
    {
        auto item_spec_p = _items[i].get_spec();

        if (query_spec_p && item_spec_p && item_spec_p->matches(*query_spec_p))
        {
            return _items[i];
        }
    }

    return Payment{}; // returns the 'default' object value

}

Payment Log::find_item(const PaymentSpec& query_spec) const
{
     for (size_t i = 0; i < _count; i++)
    {
        auto item_spec_p = _items[i].get_spec();

        if (item_spec_p && item_spec_p->matches(query_spec))
        {
            return _items[i]; // Return the first object with a matching specification
        }
    }

    return Payment{}; // returns the 'default' object value

}

 Payment Log::find_largest_payment() const
 {
    std::vector<Payment> payments(std::begin(_items), std::begin(_items)+_count);
    std::sort(payments.begin(), payments.end());
    return payments.back();
 }

 double Log::find_average_amount() const
 {
    double sum = 0.0;
    for (size_t i = 0 ; i < _count ; i++){
        sum += _items[i].get_amountCents();
    }
    return sum/(double)_count/100;
 }

 void Log::save(const std::string & csv_file_name) const
{
    std::ofstream outfile(csv_file_name);
    if (!outfile.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    for (size_t i = 0; i < _count; i++) {
        outfile << _items[i].get_cardNumber() << ";"
                << _items[i].get_currency() << ";"
                << _items[i].get_amountCents() << ";"
                << _items[i].get_dateTime().time_since_epoch().count() << ";";

        if (_items[i].get_spec()) {
            outfile << *_items[i].get_spec();
        }

        outfile << std::endl;
    }

    outfile.close();
}

void Log::load(const std::string & csv_file_name)
{
   std::ifstream is{ "payments.csv" };

    this->_count = 0;

    while (this->_count < Log::MAX_SIZE && !is.eof())
    {
        is >> this->_items[_count]; // or: this->_items[_count].recv_from(is);
        if (is) _count++;
    }
};