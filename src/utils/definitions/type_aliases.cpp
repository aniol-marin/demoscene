export module definitions:type_aliases;

import std;

export namespace mole_def
{
    /* TO DO
    class id_t
    {
        std::uint_fast8_t value;

    public:
        id_t() = delete ("a valid initialization is required for the invariant");
        template<typename V>
            requires std::no_narrowing_conversion<V, std::uint_fast8_t>, requires std::same_as<V, std::uint_fast8_t>
        explicit constexpr id_t(V value) : value{ value }
        {
        }
        template<typename V>
            requires std::no_narrowing_conversion<V, std::uint_fast8_t>, requires std::same_as<V, std::uint_fast8_t>
                                                                     constexpr id_t& operator=(id_t) = default;
        constexpr auto v() const { return value; }
    };
     */
    using Id = std::uint_fast8_t;
    using bunch = std::uint_fast8_t;
    using seconds = std::uint_fast16_t;
    using milliseconds = std::uint_fast16_t;
    using permille = std::int_fast16_t;
    using speed = std::uint_fast16_t;
    using index_t = std::uint_fast32_t;
    using point1D = std::uint_fast16_t;
    using offset1D = std::int_fast64_t;
    using rgbaColor = std::uint32_t;
    using hslaColor = std::uint32_t;
    using tempChannel = std::uint_fast16_t;
    using channel = std::uint_fast8_t;
    using hue = std::uint_fast8_t;
    using saturation = std::uint_fast8_t;
    using lightness = std::uint_fast8_t;
}
