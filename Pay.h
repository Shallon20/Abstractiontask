#pragma once
class Pay : public Item {
public:
    Pay(int id, const std::string & unique_property_2
                 , shared_ptr<const PaySpec> spec)
        : Item(id, spec), _unique_property_2{ unique_property_2 } { }
    
private:
    std::string _unique_property_2;
    
};