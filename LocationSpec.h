#pragma once

#include "ItemSpec.h"
#include <cstddef> // for std::size_t
#include <iostream>

class LocationSpec : public ItemSpec
{
public:
    enum class CardType { ANY, VIRTUAL, PLASTIC };
    static constexpr std::string_view CardType_str[]{ "Any", "Virtual", "Plastic" };

    LocationSpec() = default;
    LocationSpec(const std::string & currency, CardType cardType)
        : ItemSpec(), _currency(currency), _cardType(cardType) { }

    std::string get_currency() const { return _currency; }
    CardType get_cardType() const { return _cardType; }

    void send_to(std::ostream & os) const override;
	void recv_from(std::istream & is) override;
    bool matches(const ItemSpec & itemSpec) const override;
private:
    std::string _currency;
    CardType _cardType;
};

std::ostream & operator<<(std::ostream & os, LocationSpec::CardType cardType);
std::istream & operator>>(std::istream & is, LocationSpec::CardType & cardType);