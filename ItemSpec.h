#pragma once
#include <ostream>

class ItemSpec
{
    public:
    ItemSpec() = default;
    virtual ~ItemSpec() = default;
    virtual void send_to(std::ostream & os) const = 0;
    virtual bool matches(const ItemSpec & itemSpec)
    const = 0;
};

std::ostream & operator<<(std::ostream & os, const ItemSpec & spec);