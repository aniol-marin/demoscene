#include "definitions.h"

#include <exception>
#include <string>
#include <string_view>

namespace mole
{
    const char* panic::what()
    {
        return m_message.c_str();
    }

    void raise_dev(std::string_view message)
    {
        // TO DO #ifdef (dev)
        throw panic(message);
    }

    void raise_fatal(std::string_view message)
    {
        throw panic(message);
    }
}
