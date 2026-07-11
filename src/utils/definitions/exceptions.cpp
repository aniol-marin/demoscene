export module definitions:exceptions;

import std;

export namespace mole
{
    struct panic : public std::exception
    {
        panic() = delete ("panicking without a reason is not allowed");
        panic(std::string_view message) : m_message{ message } {}

        const char* what() { return m_message.c_str(); }

    private:
        const std::string m_message;
    };

    auto raise_dev(std::string_view message = { "undefined development error" })
    {
        // TO DO if constexpr (dev)
        throw panic(message);
    }

    auto raise_fatal(std::string_view message = { "undefined fatal error" })
    {
        throw panic(message);
    }
}
