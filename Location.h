#pragma once

#include "Item.h"
#include "LocationSpec.h"
#include <string>

class Location : public Item {
public:
Location() = default;
Location(
    int id, 
    double distance, 
    std::string name,
    std::shared_ptr<const LocationSpec> spec)
                 
    :   Item(id, spec), 
        _distance{ distance } 
        _name { name }
        { }
    double get_distance() const { return _distance; }
    void send_to(std::ostream & os)const override;
    void recv_from(std::istream & is)override;
private:
    double _distance;
    std::string _name;
    
};