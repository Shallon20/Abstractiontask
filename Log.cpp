#include "Log.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

void Log::add_item(std::shared_ptr<Item> newItem) {
    if (_count < Log::MAX_SIZE)
    {
        if (newItem->get_id() != find_item(*newItem->get_spec()).get_id())
        {
            _items[_count] = newItem;
            _count++;
        }
    }
}

/*Payment Log::find_item(const Payment& query) const
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

const Item & Log::find_item(const ItemSpec& otherSpec) const
{
     for (size_t i{ 0U }; i < _count; i++)
        if (_items[i]->get_spec()->matches(otherSpec))
            return *_items[i]; // return the first object with matching specification

    static const Item def{};
    return def; // return the 'default' value object
}

/* double Log::find_largest_payment() const
 {
    std::vector<Item> payments(std::begin(_items), std::begin(_items)+_count);
    std::sort(payments.begin(), payments.end());
    return payments.back();
 }

 double Log::find_average_amount() const
 {
    double sum = 0.0;
    for (size_t i = 0 ; i < _count ; i++){
        sum += _items[i].();
    }
    return sum/(double)_count/100;
 }
*/
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
      //  is >> this->_items[_count]; // or: this->_items[_count].recv_from(is);
        if (is) _count++;
    }
};