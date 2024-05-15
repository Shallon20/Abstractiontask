#pragma once

#include "Item.h"
#include "LocationSpec.h"
#include <string>

class Location : public Item {
public:
Location() = default;
Location(
    int id, 
    int amountCents, 
    std::string name,
    std::shared_ptr<const LocationSpec> spec)
                 
    :   Item(id, spec), 
        _amountCents{ amountCents },
        _name{ name }
        { }
    int get_amountCents() const { return _amountCents; }
    std::string get_name() const { return _name; }
    void send_to(std::ostream & os) const override;
    void recv_from(std::istream & is)override;
private:
    int _amountCents;
    std::string _name;
    
};