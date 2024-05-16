#pragma once

#include "ItemSpec.h"
#include <cstddef> // for std::size_t
#include <iostream>

class GuitarSpec : public ItemSpec
{
public:
    enum class Type { ANY, ACOUSTIC, ELECTRIC };
    static constexpr std::string_view Type_str[]{ "Any", "Acoustic", "Electric" };

    GuitarSpec() = default;
    GuitarSpec(const std::string & model, Type type)
        : ItemSpec(), _model(model), _type(type) { }

    std::string get_model() const { return _model; }
    Type get_type() const { return _type; }

    void send_to(std::ostream & os) const override;
	void recv_from(std::istream & is) override;
    bool matches(const ItemSpec & itemSpec) const override;
private:
    std::string _model;
    Type _type;
};

std::ostream & operator<<(std::ostream & os, GuitarSpec::Type type);
std::istream & operator>>(std::istream & is, GuitarSpec::Type & type);