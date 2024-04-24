#include "Log.h"
#include <cmath>
#include <vector>
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
    double sum = 0.00;
    for (size_t i = 0 ; i < _count ; i++){
        sum += _items[i].get_amountCents();
    }
    return sum/(double)_count/100;
 }

 