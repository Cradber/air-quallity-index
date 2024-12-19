#ifndef JSON_SERIALIZER_NLOHMANN_AQI_FACTORY_H
#define JSON_SERIALIZER_NLOHMANN_AQI_FACTORY_H


#include <type_traits>
#include "serialization/nlohmann/jsonserializernlohmann.h"


template <typename T, typename... Types>
struct is_derived_from_any : std::false_type {};

template <typename T, typename First, typename... Rest>
struct is_derived_from_any<T, First, Rest...>
    : std::conditional_t<std::is_base_of_v<JsonSerializerNlohmann<First>, T>,
                         std::true_type,
                         is_derived_from_any<T, Rest...>> {};

template <typename T, typename... Types>
struct is_derived_from_any<T, std::tuple<Types...>>
    : std::disjunction<std::is_base_of<JsonSerializerNlohmann<Types>, T>...> {};

template <typename T, typename First>
struct is_derived_from_any<T, First>
    : std::is_base_of<JsonSerializerNlohmann<First>, T> {};


class JsonSerializerNlohmannAQIFactory {
private:
    using aqi_types = std::tuple<
        Attributions,
        City,
        Debug,
        Metrics,
        Daily,
        Forecast,
        ParamAdapter<double>,
        Iaqi,
        Time,
        Data,
        ResponseAPI
        >;

public:
    template <typename Serializer,
             typename = std::enable_if_t<
                 is_derived_from_any<Serializer, aqi_types>::value
                 >>
    static std::unique_ptr<Serializer> create() {
        return std::make_unique<Serializer>();
    }
};


#endif // JSON_SERIALIZER_NLOHMANN_AQI_FACTORY_H
