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
        return true;  // if comparing to self

    bool result{ true };

    // try to downcast to the required derived specification type
    auto temp{ dynamic_cast<const GuitarSpec*>(&itemSpec) };
    if (nullptr == temp)
        return false; // if itemSpec doesn't refer to GuitarSpec (or derived) class instance

    // cast to reference type for actual comparison of properties
    const GuitarSpec& otherSpec{ *temp };

    if (otherSpec.get_model() != ""
        && otherSpec.get_model() != this->_model)
        result = false;

    if (otherSpec.get_type() != GuitarSpec::Type::ANY
        && otherSpec.get_type() != this->_type)
        result = false;

    return result;
}


void GuitarSpec::send_to(std::ostream& os) const
{
    os << _model << csv_delimiter
       << Type_str[static_cast<size_t>(_type)];
}


void GuitarSpec::recv_from(std::istream & is)
{
    if (is)
        getline(is >> std::ws, _model, csv_delimiter); // also skips the delimiter
		
    if (is)
        is >> _type;
}


std::ostream & operator<<(std::ostream & os, GuitarSpec::Type t)
{
    os << GuitarSpec::Type_str[static_cast<std::size_t>(t)];
    return os;
}


std::istream & operator>>(std::istream & is, GuitarSpec::Type & type)
{
    if (is)
    {
        std::string tmp;
        getline(is, tmp, csv_delimiter);

        if (is)
        {
            bool found{ false };

            for (size_t i{ 0 }; i < sizeof(GuitarSpec::Type_str)/sizeof(GuitarSpec::Type_str[0]); i++)
            {
                if (tmp.length() == GuitarSpec::Type_str[i].length()
					&& 0 == strcasecmp(tmp.c_str(), std::string(GuitarSpec::Type_str[i]).c_str())) // case insensitive comparison
                {
                    type = static_cast<GuitarSpec::Type>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                type = GuitarSpec::Type::ANY;
        }
    }
    return is;
}