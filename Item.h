#pragma once
#include <memory>
#include <ostream>
#include "ItemSpec.h"

class Item
{
public:
    Item() = default;
    virtual ~Item() = default;
    
    Item(
        int id, 
        std::shared_ptr<const ItemSpec> spec
        )

        : _id{ id }
    {
        set_spec(spec);
    }

    int get_id() const
    {
        return _id;
    }

    std::shared_ptr<const ItemSpec> get_spec() const
    {
        return _spec;
    }

    virtual void send_to(std::ostream & os) const;
    virtual void recv_from(std::istream & os);

protected:
    // for changing the specification only in this and in derived classes:
    void set_spec(std::shared_ptr<const ItemSpec> spec)
    {
        _spec = spec;
    }

private:
    int _id;
    std::shared_ptr<const ItemSpec> _spec;
};

std::ostream & operator<<(std::ostream & os, const Item & item);
std::istream & operator>>(std::istream & os, Item & item);