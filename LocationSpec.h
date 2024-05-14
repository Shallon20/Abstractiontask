#pragma once
// model- position type- area
#include "ItemSpec.h"
#include <cstddef> // for std::size_t
#include <iostream>

class LocationSpec : public ItemSpec
{
public:
enum class Area { ANY, URBAN, RURAL };
static constexpr std::string_view Area_str[]{ "Any", "Urban", "Rural" };

LocationSpec() = default;
LocationSpec(const std::string & position, Area area)
: ItemSpec(), _position(position), _area(area) { }

std::string get_position() const { return _position; }
Area get_area() const { return _area; }

void send_to(std::ostream & os) const override;
void recv_from(std::istream & is) override;
bool matches(const ItemSpec & itemSpec) const override;
private:
std::string _position;
Area _area;
};

std::ostream & operator<<(std::ostream & os, LocationSpec::Area area);
std::istream & operator>>(std::istream & is, LocationSpec::Area & area);

