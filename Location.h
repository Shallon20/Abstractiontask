#pragma once
#include "Item.h"
#include "LocationSpec.h"
#include <string>

class Location : public Item
{
public:
    location() = default;
    Location(int id, int amountCents, std::shared_ptr<const LocationSpec> spec)
        : Item(id, spec), _amountCents(amountCents) { }

    int get_amountCents() const { return _amountCents; }

    void send_to(std::ostream& os) const override;
    void recv_from(std::istream & is) override;
private:
    int _amountCents;
};
