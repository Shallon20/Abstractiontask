#include "Location.h"

void Location::send_to(std::ostream& os) const
{
    Item::send_to(os);

    os << csv_delimiter << _amountCents;
}


void Location::recv_from(std::istream & is)
{
    Item::recv_from(is);

    if (is)
       (is >> _amountCents).ignore();
}