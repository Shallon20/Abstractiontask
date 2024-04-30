#include "Item.h"

std::ostream & operator<<(std::ostream & os, const Item & item)
{
    item.send_to(os);
    return os;
}