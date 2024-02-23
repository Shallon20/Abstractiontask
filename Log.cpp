#include "Log.h"
#include <cmath>

void Log::add_item(int id, string type, double price)
{
    if (_count < Log::MAX_SIZE)
    {
        Bicycle new_item;
        new_item.init(id, type, price);
        _items[_count] = new_item;
        _count++;
    }
}

Bicycle Log::find_item(Bicycle query)
{
    for (size_t i = 0; i < _count; i++)
    {
        // for integer or boolean type property
        if (query.get_id() != 0
            && query.get_id() != _items[i].get_id())
            continue;

        // for string type property
        if (query.get_type() != ""
            && query.get_type() != _items[i].get_type())
            continue;

        // for double type
        constexpr double epsil{ 0.005 };
        if (query.get_price() != 0.0
            && epsil < std::abs(query.get_price() - _items[i].get_price()))
            continue;

        return _items[i];
    }

    return Bicycle{}; // returns the 'default' object value
}