#include "Item.h"

void Item::send_to(std::ostream & os) const
{
    os << _id;
    if (_spec){
        _spec ->send_to(os);
    }
}

std::ostream & operator<<(std::ostream & os, const Item & item)
{
    item.send_to(os);
    return os;
}

std::istream & operator >>(std::istream &is, Item & item)
{
    item.recv_from(is);
    return is;
}

void Item::recv_from(std::istream & is)
{
    if (is){
        is >> _id;
        _spec.reset();
        // Unfinished as it requires additional information on the serialized object:
       // auto temp_spec{ std::make_shared<PaymentSpec>() };
       // is >> *temp_spec; // alternative: temp_spec->recv_from(is);
       // set_spec(temp_spec); // replaces specification

    }
}

double Item::get_payments() const {
    return _payments;
}