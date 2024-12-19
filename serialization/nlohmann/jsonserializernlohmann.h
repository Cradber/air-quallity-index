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

template<>
struct adl_serializer<Daily> {
    static void from_json(const json& j, Daily& daily) {
        daily.set_o3(j.at("o3").get<std::vector<Metrics>>());
        daily.set_pm10(j.at("pm10").get<std::vector<Metrics>>());
        daily.set_pm25(j.at("pm25").get<std::vector<Metrics>>());
        daily.set_uvi(j.at("uvi").get<std::vector<Metrics>>());
    }

    static void to_json(json& j, const Daily& daily) {
        j = json::object();
        j["o3"] = daily.get_o3();
        j["pm10"] = daily.get_pm10();
        j["pm25"] = daily.get_pm25();
        j["uvi"] = daily.get_uvi();
    }
};

template <>
struct adl_serializer<ParamAdapter<double>> {
    static void from_json(const json& j, ParamAdapter<double>& co) {
        co.set(j.at("v").get<double>());
    }

    static void to_json(json& j, const ParamAdapter<double>& co) {
        j = json::object();
        j["v"] = co.get();
    }
};

template <> struct adl_serializer<Co>   : adl_serializer<ParamAdapter<double>> {};
template <> struct adl_serializer<H>    : adl_serializer<ParamAdapter<double>> {};
template <> struct adl_serializer<No2>  : adl_serializer<ParamAdapter<double>> {};
template <> struct adl_serializer<O3>   : adl_serializer<ParamAdapter<double>> {};
template <> struct adl_serializer<P>    : adl_serializer<ParamAdapter<double>> {};
template <> struct adl_serializer<Pm10> : adl_serializer<ParamAdapter<double>> {};
template <> struct adl_serializer<Pm25> : adl_serializer<ParamAdapter<double>> {};
template <> struct adl_serializer<So2>  : adl_serializer<ParamAdapter<double>> {};
template <> struct adl_serializer<T>    : adl_serializer<ParamAdapter<double>> {};

template <>
struct adl_serializer<City> {
    static void from_json(const json& j, City& city) {
        city.set_geo(j.at("geo").get<std::array<double,2>>());
        city.set_name(j.at("name").get<std::string>());
        city.set_url(j.at("url").get<std::string>());
        city.set_location(j.at("location").get<std::string>());
    }

    static void to_json(json& j, const City& city) {
        j = json::object();
        j["geo"] = city.get_geo();
        j["name"] = city.get_name();
        j["url"] = city.get_url();
        j["location"] = city.get_location();
    }
};

template <>
struct adl_serializer<Attributions> {
    static void from_json(const json& j, Attributions& attribution) {
        attribution.set_url(j.at("url").get<std::string>());
        attribution.set_name(j.at("name").get<std::string>());
        attribution.set_logo(get_stack_optional<std::string>(j, "logo"));
    }

    static void to_json(json& j, const Attributions& attribution) {
        j = json::object();
        j["url"] = attribution.get_url();
        j["name"] = attribution.get_name();
        j["logo"] = attribution.get_logo();
    }
};

template <>
struct adl_serializer<Time> {
    static void from_json(const json& j, Time& time) {
        time.set_s(j.at("s").get<std::string>());
        time.set_tz(j.at("tz").get<std::string>());
        time.set_v(j.at("v").get<double>());
        time.set_iso(j.at("iso").get<std::string>());
    }
    static void to_json(json& j, const Time& time) {
        j["s"]   = time.get_s();
        j["tz"]  = time.get_tz();
        j["v"]   = time.get_v();
        j["iso"] = time.get_iso();
    }
};

template <>
struct adl_serializer<Debug> {
    static void from_json(const json& j, Debug& debug) {
        debug.set(j.at("sync").get<std::string>());
    }
    static void to_json(json& j, const Debug& debug) {
        j["sync"] = debug.get();
    }
};

template <>
struct adl_serializer<Forecast> {
    static void from_json(const json& j, Forecast& forecast) {
        forecast.set(j.at("daily").get<Daily>());
    }
    static void to_json(json& j, const Forecast& forecast) {
        j["forecast"] = forecast.get();
    }
};

template <>
struct adl_serializer<Iaqi> {
    static void from_json(const json& j, Iaqi& iaqi) {
        iaqi.set_co(j.at("co").get<Co>());
        iaqi.set_h(j.at("h").get<H>());
        iaqi.set_no2(j.at("no2").get<No2>());
        iaqi.set_o3(j.at("o3").get<O3>());
        iaqi.set_p(j.at("p").get<P>());
        iaqi.set_pm10(j.at("pm10").get<Pm10>());
        iaqi.set_pm25(j.at("pm25").get<Pm25>());
        iaqi.set_so2(j.at("so2").get<So2>());
        iaqi.set_t(j.at("t").get<T>());
    }
    static void to_json(json& j, const Iaqi& iaqi) {
        j["co"]   = iaqi.get_co();
        j["h"]    = iaqi.get_h();
        j["no2"]  = iaqi.get_no2();
        j["o3"]   = iaqi.get_o3();
        j["p"]    = iaqi.get_p();
        j["pm10"] = iaqi.get_pm10();
        j["pm25"] = iaqi.get_pm25();
        j["so2"]  = iaqi.get_so2();
        j["t"]    = iaqi.get_t();
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
