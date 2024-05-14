#include "ItemSpec.h"

std::ostream & operator<<(std::ostream & os, const ItemSpec & spec)
{
    spec.send_to(os);
    return os;
}
std::istream & operator>>(std:istream & is, ItemSpec & item)
{
    item.recv_from(is);
    return is;
}