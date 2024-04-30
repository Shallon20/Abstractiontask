#include "ItemSpec.h"

std::ostream & operator<<(std::ostream & os, const ItemSpec & spec)
{
    spec.send_to(os);
    return os;
}