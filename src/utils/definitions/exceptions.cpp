#include "definitions.h"

#include <exception>
#include <string>

namespace mole
{
    const char* panic::what()
    {
        return m_message.c_str();
    }

    void raise_dev(const char* message)
    {
        // TO DO #ifdef (dev)
        throw panic(message);
    }

    void raise_fatal(const char* message)
    {
        throw panic(message);
    }
}
