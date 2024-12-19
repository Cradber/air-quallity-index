#ifndef JSONSERIALIZERNLOHMANN_H
#define JSONSERIALIZERNLOHMANN_H

#include "models/models.h"
#include "nlohmann/json.hpp"
#include "serialization/json_serialization.h"

using json = nlohmann::json;


#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER

namespace nlohmann {

template<typename T>
struct adl_serializer<std::shared_ptr<T>> {
    static void to_json(json& j, const std::shared_ptr<T>& opt) {
        if (!opt) j = nullptr;
        else j = *opt;
    }

    static std::shared_ptr<T> from_json(const json& j) {
        if (j.is_null())
            return std::make_shared<T>();
        else
            return std::make_shared<T>(j.get<T>());
    }
};

template<typename T>
struct adl_serializer<std::optional<T>> {
    static void to_json(json& j, const std::optional<T>& opt) {
        if (!opt)
            j = nullptr;
        else
            j = *opt;
    }

    static std::optional<T> from_json(const json& j) {
        if (j.is_null())
            return std::nullopt;
        else
            return j.get<T>();
    }
};

/*
template <typename T>
struct adl_serializer<T> {
    static void from_json(const json& j, T& param) {
        from_json(j, param);
    }

    static void to_json(json& j, const T& param) {
        to_json(j, param);
    }
};
*/
}

#endif  // NLOHMANN_OPT_HELPER



#ifndef NLOHMANN_UNTYPED_aqi_HELPER
#define NLOHMANN_UNTYPED_aqi_HELPER

inline json get_untyped(const json& j, const char* property) {
    if (j.find(property) != j.end())
        return j.at(property).get<json>();
    return json();
}

inline json get_untyped(const json& j, std::string property) {
    return get_untyped(j, property.data());
}

#endif  // NLOHMANN_UNTYPED_aqi_HELPER


#ifndef NLOHMANN_OPTIONAL_aqi_HELPER
#define NLOHMANN_OPTIONAL_aqi_HELPER

template <typename T>
inline std::shared_ptr<T> get_heap_optional(const json& j, const char* property) {
    auto it = j.find(property);
    if (it != j.end() && !it->is_null())
        return j.at(property).get<T>();

    return std::shared_ptr<T>();
}

template <typename T>
inline std::shared_ptr<T> get_heap_optional(const json& j, std::string property) {
    return get_heap_optional<T>(j, property.data());
}

template <typename T>
inline std::optional<T> get_stack_optional(const json& j, const char* property) {
    auto it = j.find(property);
    if (it != j.end() && !it->is_null())
        return j.at(property).get<T>();

    return std::nullopt;
}

template <typename T>
inline std::optional<T> get_stack_optional(const json& j, std::string property) {
    return get_stack_optional<T>(j, property.data());
}

#endif // NLOHMANN_OPTIONAL_aqi_HELPER


namespace nlohmann {
template <>
struct adl_serializer<Metrics> {
    static void from_json(const json& j, Metrics& metric) {
        metric.set_avg(j.at("avg").get<double>());
        metric.set_day(j.at("day").get<std::string>());
        metric.set_min(j.at("min").get<double>());
        metric.set_max(j.at("max").get<double>());
    }

    static void to_json(json& j, const Metrics& metric) {
        j = json::object();
        j["avg"] = metric.get_avg();
        j["day"] = metric.get_day();
        j["min"] = metric.get_min();
        j["max"] = metric.get_max();
    }
};
}



template <typename T>
class JsonSerializerNlohmann : public JsonSerializer<json, T> {
public:
    JsonSerializerNlohmann() = default;
    virtual ~JsonSerializerNlohmann() = default;
};

#endif // JSONSERIALIZERNLOHMANN_H
