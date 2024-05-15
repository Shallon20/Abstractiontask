#include "LocationSpec.h"

#include <string> // for std::getline()

#ifdef _MSC_VER // Visual C++ ?
#define strcasecmp _stricmp // then use the function _stricmp() 
#else
#include <strings.h> // for strcasecmp() function in POSIX C++
#endif

bool LocationSpec::matches(const ItemSpec& itemSpec) const
{
if (this == &itemSpec)
return true; // if comparing to self

bool result{ true };

// try to downcast to the required derived specification type
auto temp{ dynamic_cast<const LocationSpec*>(&itemSpec) };
if (nullptr == temp)
return false; // if itemSpec doesn't refer to GuitarSpec (or derived) class instance

// cast to reference type for actual comparison of properties
const LocationSpec& otherSpec{ *temp };

if (otherSpec.get_currency() != ""
&& otherSpec.get_currency() != this->_currency)
result = false;

if (otherSpec.get_area() != LocationSpec::Area::ANY
&& otherSpec.get_area() != this->_area)
result = false;

return result;
}

void LocationSpec::send_to(std::ostream& os) const
{
os << _currency << csv_delimiter
<< Area_str[static_cast<size_t>(_area)];
}

void LocationSpec::recv_from(std::istream & is)
{
if (is)
getline(is >> std::ws, _currency, csv_delimiter); // also skips the delimiter
if (is)
is >> _area;
}

std::ostream & operator<<(std::ostream & os, LocationSpec::Area area)
{
os << LocationSpec::Area_str[static_cast<std::size_t>(area)];
return os;
}

std::istream & operator>>(std::istream & is, LocationSpec::Area & area)
{
if (is)
{
std::string tmp;
getline(is, tmp, csv_delimiter);

if (is)
{
bool found{ false };

for (size_t i{ 0 }; i < sizeof(LocationSpec::Area_str)/sizeof(LocationSpec::Area_str[0]); i++)
{
if (tmp.length() == LocationSpec::Area_str[i].length()
&& 0 == strcasecmp(tmp.c_str(), std::string(LocationSpec::Area_str[i]).c_str())) // case insensitive comparison
{
area = static_cast<LocationSpec::Area>(i);
found = true;
break;
}
}

if (!found)
area = LocationSpec::Area::ANY;
}
}
return is;
}
