#include "Log.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

/*void Log::add_item(
    const std::string& cardNumber, 
	const std::string& currency, 
	const int& amountCents, 
	const Payment::date_time& dateTime,
    spcPaymentSpec spec
) */
void Log::add_item(std::shared_ptr<Item> new_item){
    if (_count < Log::MAX_SIZE)
    {
        //Payment new_item(cardNumber, currency, amountCents, dateTime, spec);
        if (new_item->get_id() != find_item(*new_item->get_spec()).get_id())
        {
            _items[_count] = new_item;
            _count++;
        }
    }
}

const Item& Log::find_item(const ItemSpec& query_spec) const
{
     for (size_t i{ 0U }; i < _count; i++)
        if (_items[i]->get_spec()->matches(query_spec))
            return *_items[i]; // Return the first object with a matching specification
     static const Item def{};
     return def;
}

/*
void Log::save(const std::string & csv_file_name) const
{
     std::ofstream os{ csv_file_name};

    for (size_t i{ 0U }; os.good() && i < this->_count; i++)
        os << this->_items[i] << "\n"; // or: { this->_items[i].send_to(os); os << "\n"; 
}

void Log::load(const std::string & csv_file_name)
{
   std::ifstream is{ csv_file_name };

    this->_count = 0;

    while (this->_count < Log::MAX_SIZE && !is.eof())
    {
        is >> this->_items[_count]; // or: this->_items[_count].recv_from(is);
        if (is) _count++;
    }
};
Payment Log::find_item(const Payment& query) const
{ 
    auto query_spec_p{ query.get_spec()};

    for (size_t i = 0; i < _count; i++)
    {

        if (query.get_cardNumber() != ""
        && query.get_cardNumber() !=_items[i].get_cardNumber())
        continue;
        if (query.get_currency() != ""
        && query.get_currency() !=_items[i].get_currency())
        continue;
        if (query.get_amountCents() != 0
        && query.get_amountCents() !=_items[i].get_amountCents())
        continue;
        auto item_spec_p{ _items[i].get_spec() };
        if(query_spec_p && item_spec_p && item_spec_p->matches(*query_spec_p))
        {
            return _items[i];
        }
    }

    return Payment{}; // returns the 'default' object value

}*/



