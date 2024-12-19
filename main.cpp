#include <iostream>
#include <optional>

#include "cpr/api.h"
#include "nlohmann/json.hpp"

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


class Attributions {
private:
    std::string url;
    std::string name;
    std::optional<std::string> logo;

public:
    Attributions() = default;
    Attributions(std::string url, std::string name, std::optional<std::string> logo)
        : url(url), name(name), logo(logo ? logo : std::nullopt) {}
    virtual ~Attributions() = default;

    std::string get_url() const { return url; }
    void set_url(std::string url) { this->url = url; }

    std::string get_name() const { return name; }
    void set_name(std::string name) { this->name = name; }

    std::optional<std::string> get_logo() const { return logo; }
    void set_logo(std::optional<std::string> logo) { this->logo = logo ? logo : std::nullopt; }
};

class City {
private:
    std::string name;
    std::string url;
    std::string location;
    std::array<double, 2> geo;

public:
    City() = default;
    City(std::string name, std::string url, std::string location, std::array<double, 2> geo)
        : name(name), url(url), location(location), geo(geo) {}
    virtual ~City() = default;

    std::string get_url() const { return url; }
    void set_url(std::string url) { this->url = url; }

    std::string get_name() const { return name; }
    void set_name(std::string name) { this->name = name; }

    std::string get_location() const { return location; }
    void set_location(std::string location) { this->location = location; }

    std::array<double, 2> get_geo() const { return geo; }
    void set_geo(std::array<double, 2>  value) { this->geo = value; }

    double get_geo_latitude() const { return geo[0]; }
    void set_geo_latitute(double lat) { geo[0] = lat; }

    double get_geo_longitude() const { return geo[1]; }
    void set_geo_longitude(double lon) { geo[1] = lon; }
};

class Metrics {
private:
    double avg;
    double max;
    double min;
    std::string day;

public:
    Metrics() = default;
    Metrics(double avg, double min, double max, std::string day)
        : avg(avg), min(min), max(max), day(day) {}
    virtual ~Metrics() = default;

    double get_avg() const { return avg; }
    void set_avg(double avg) { this->avg = avg; }

    double get_min() const { return min; }
    void set_min(double min) { this->min= min; }

    double get_max() const { return max; }
    void set_max(double max) { this->max= max; }

    std::string get_day() const { return day; }
    void set_day(std::string day) { this->day= day; }
};

class Daily {
private:
    std::vector<Metrics> o3;
    std::vector<Metrics> pm10;
    std::vector<Metrics> pm25;
    std::vector<Metrics> uvi;

public:
    Daily() = default;
    Daily(std::vector<Metrics> o3, std::vector<Metrics> pm10, std::vector<Metrics> pm25, std::vector<Metrics> uvi)
        : o3(o3), pm10(pm10), pm25(pm25), uvi(uvi) {}
    virtual ~Daily() = default;

    std::vector<Metrics> get_o3() const { return o3; }
    void set_o3(std::vector<Metrics> o3) { this->o3 = o3; }

    std::vector<Metrics> get_pm10() const { return pm10; }
    void set_pm10(std::vector<Metrics> pm10) { this->pm10= pm10; }

    std::vector<Metrics> get_pm25() const { return pm25; }
    void set_pm25(std::vector<Metrics> pm25) { this->pm25 = pm25; }

    std::vector<Metrics> get_uvi() const { return uvi; }
    void set_uvi(std::vector<Metrics> uvi) { this->uvi = uvi; }
};

template <typename T>
class ParamAdapter {
private:
    T data;

protected:
    ParamAdapter() = default;
    explicit ParamAdapter(const T& data) : data(data) {}
    virtual ~ParamAdapter() = default;

public:
    const T& get() const { return data; }
    void set(const T& data) { this->data = data; }
};

class Forecast : public ParamAdapter<Daily> {};

using Sync = std::string;
class Debug: public ParamAdapter<Sync> {};

using V = double;
class Co   : public ParamAdapter<V> {};
class H    : public ParamAdapter<V> {};
class No2  : public ParamAdapter<V> {};
class O3   : public ParamAdapter<V> {};
class P    : public ParamAdapter<V> {};
class Pm10 : public ParamAdapter<V> {};
class Pm25 : public ParamAdapter<V> {};
class So2  : public ParamAdapter<V> {};
class T    : public ParamAdapter<V> {};

class Iaqi {
private:
    Co   co;
    H    h;
    No2  no2;
    O3   o3;
    P    p;
    Pm10 pm10;
    Pm25 pm25;
    So2  so2;
    T    t;

public:
    const Co & get_co() const { return co; }
    void set_co(const Co & value) { this->co = value; }

    const H & get_h() const { return h; }
    void set_h(const H & value) { this->h = value; }

    const No2 & get_no2() const { return no2; }
    void set_no2(const No2 & value) { this->no2 = value; }

    const O3 & get_o3() const { return o3; }
    void set_o3(const O3 & value) { this->o3 = value; }

    const P & get_p() const { return p; }
    void set_p(const P & value) { this->p = value; }

    const Pm10 & get_pm10() const { return pm10; }
    void set_pm10(const Pm10 & value) { this->pm10 = value; }

    const Pm25 & get_pm25() const { return pm25; }
    void set_pm25(const Pm25 & value) { this->pm25 = value; }

    const So2 & get_so2() const { return so2; }
    void set_so2(const So2 & value) { this->so2 = value; }

    const T & get_t() const { return t; }
    void set_t(const T & value) { this->t = value; }
};

class Time {
private:
    std::string s;
    std::string tz;
    std::string iso;
    double      v;

public:
    Time() = default;
    Time(std::string s, std::string tz, std::string iso, double v)
        : s(s), tz(tz), iso(iso), v(v) {}
    virtual ~Time() = default;

    std::string get_s() const { return s; }
    void set_s(std::string s) { this->s = s; }

    std::string get_tz() const { return tz; }
    void set_tz(std::string tz) { this->tz= tz; }

    std::string get_iso() const { return iso; }
    void set_iso(std::string iso) { this->iso= iso; }

    double get_v() const { return v; }
    void set_v(double v) { this->v = v; }
};

class Data {
private:
    long aqi;
    long idx;
    std::vector<Attributions> attributions;
    City city;
    std::string dominentpol;
    Iaqi iaqi;
    Time time;
    Forecast forecast;
    Debug debug;

public:
    Data() = default;
    virtual ~Data() = default;

    const long & get_aqi() const { return aqi; }
    void set_aqi(const long & value) { this->aqi = value; }

    const long & get_idx() const { return idx; }
    void set_idx(const long & value) { this->idx = value; }

    const std::vector<Attributions> & get_attributions() const { return attributions; }
    void set_attributions(const std::vector<Attributions> & value) { this->attributions = value; }

    const City & get_city() const { return city; }
    void set_city(const City & value) { this->city = value; }

    const std::string & get_dominentpol() const { return dominentpol; }
    void set_dominentpol(const std::string & value) { this->dominentpol = value; }

    const Iaqi & get_iaqi() const { return iaqi; }
    void set_iaqi(const Iaqi & value) { this->iaqi = value; }

    const Time & get_time() const { return time; }
    void set_time(const Time & value) { this->time = value; }

    const Forecast & get_forecast() const { return forecast; }
    void set_forecast(const Forecast & value) { this->forecast = value; }

    const Debug & get_debug() const { return debug; }
    void set_debug(const Debug & value) { this->debug = value; }
};

enum class StatusResponseAPI {
    OK = 200,
    ERROR = 400
};
NLOHMANN_JSON_SERIALIZE_ENUM(StatusResponseAPI,{
    {StatusResponseAPI::OK, "ok"},
    {StatusResponseAPI::ERROR, "error"}
})
std::ostream& operator<<(std::ostream& out, const StatusResponseAPI& status) {
    switch (status) {
    case StatusResponseAPI::OK:
        out << "ok (2xx)" << std::endl;
        break;
    case StatusResponseAPI::ERROR:
        out << "error (4xx)" << std::endl;
        break;
    }
    return out;
}

class ResponseAPI {
private:
    StatusResponseAPI status;
    Data data;

public:
    ResponseAPI() = default;
    virtual ~ResponseAPI() = default;

    StatusResponseAPI get_status() const { return status; }
    void set_status(StatusResponseAPI status) { this->status = status; }

    const Data get_data() const { return data; }
    void set_data(const Data& data) { this->data = data; }
};




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
}




inline void from_json(const json& j, Attributions& attribution) {
    try {
        attribution.set_url(j.at("url").get<std::string>());
        attribution.set_name(j.at("name").get<std::string>());
        attribution.set_logo(get_stack_optional<std::string>(j, "logo"));
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Attributions` parsin" << std::endl;
    }
}

inline void to_json(json& j, Attributions& attribution) {
    j = json::object();
    j["url"] = attribution.get_url();
    j["name"] = attribution.get_name();
    j["logo"] = attribution.get_logo();
}

inline void from_json(const json& j, City& city) {
    try {
        city.set_geo(j.at("geo").get<std::array<double,2>>());
        city.set_name(j.at("name").get<std::string>());
        city.set_url(j.at("url").get<std::string>());
        city.set_location(j.at("location").get<std::string>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `City` parsin" << std::endl;
    }
}

inline void to_json(json& j, City& city) {
    j = json::object();
    j["geo"] = city.get_geo();
    j["name"] = city.get_name();
    j["url"] = city.get_url();
    j["location"] = city.get_location();
}

inline void from_json(const json& j, Debug& debug) {
    try {
        debug.set(j.at("sync").get<std::string>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Debug` parsin" << std::endl;
    }
}

inline void to_json(json& j, const Debug& debug) {
    j = json::object();
    j["sync"] = debug.get();
}

inline void from_json(const json& j, Metrics& metrics) {
    try {
        metrics.set_avg(j.at("avg").get<double>());
        metrics.set_day(j.at("day").get<std::string>());
        metrics.set_min(j.at("min").get<double>());
        metrics.set_max(j.at("max").get<double>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Metrics` parsin" << std::endl;
    }
}

inline void to_json(json& j, const Metrics& metrics) {
    j = json::object();
    j["avg"] = metrics.get_avg();
    j["day"] = metrics.get_day();
    j["min"] = metrics.get_min();
    j["max"] = metrics.get_max();
}

inline void form_json(const json& j, Daily& daily) {
    try {
        daily.set_o3(j.at("o3").get<std::vector<Metrics>>());
        daily.set_pm10(j.at("pm10").get<std::vector<Metrics>>());
        daily.set_pm25(j.at("pm25").get<std::vector<Metrics>>());
        daily.set_uvi(j.at("uvi").get<std::vector<Metrics>>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Daily` parsin" << std::endl;
    }
}

inline void to_json(json& j, const Daily& daily) {
    j = json::object();
    j["o3"] = daily.get_o3();
    j["pm10"] = daily.get_pm10();
    j["pm25"] = daily.get_pm25();
    j["uvi"] = daily.get_uvi();
}

inline void from_json(const json& j, Forecast& forecast) {
    try {
        forecast.set(j.at("daily").get<Daily>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Forecast` parsin" << std::endl;
    }
}

inline void to_json(json& j, const Forecast& forecast) {
    j = json::object();
    j["forecast"] = forecast.get();
}

inline void from_json(const json& j, ParamAdapter<double>& param) {
    try {
        param.set(j.at("v").get<double>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `ParamAdapter<double>` parsin" << std::endl;
    }
}

inline void to_json(json& j, const ParamAdapter<double>& param) {
    j = json::object();
    j["v"] = param.get();
}

inline void from_json(const json& j, Iaqi& iaqi) {
    try {
        iaqi.set_co(j.at("co").get<Co>());
        iaqi.set_h(j.at("h").get<H>());
        iaqi.set_no2(j.at("no2").get<No2>());
        iaqi.set_o3(j.at("o3").get<O3>());
        iaqi.set_p(j.at("p").get<P>());
        iaqi.set_pm10(j.at("pm10").get<Pm10>());
        iaqi.set_pm25(j.at("pm25").get<Pm25>());
        iaqi.set_so2(j.at("so2").get<So2>());
        iaqi.set_t(j.at("t").get<T>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Iaqi` parsin" << std::endl;
    }
}

inline void to_json(json& j, const Iaqi& iaqi) {
    j = json::object();

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

inline void from_json(const json& j, Time& time) {
    try {
        time.set_s(j.at("s").get<std::string>());
        time.set_tz(j.at("tz").get<std::string>());
        time.set_v(j.at("v").get<double>());
        time.set_iso(j.at("iso").get<std::string>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Time` parsin" << std::endl;
    }
}

inline void to_json(json& j, const Time& time) {
    j = json::object();

    j["s"]   = time.get_s();
    j["tz"]  = time.get_tz();
    j["v"]   = time.get_v();
    j["iso"] = time.get_iso();
}

inline void from_json(const json& j, Data& resp) {
    try {
        resp.set_aqi(j.at("aqi").get<long>());
        resp.set_idx(j.at("idx").get<long>());
        resp.set_attributions(j.at("attributions").get<std::vector<Attributions>>());
        resp.set_city(j.at("city").get<City>());
        resp.set_dominentpol(j.at("dominentpol").get<std::string>());
        resp.set_iaqi(j.at("iaqi").get<Iaqi>());
        resp.set_time(j.at("time").get<Time>());
        resp.set_forecast(j.at("forecast").get<Forecast>());
        resp.set_debug(j.at("debug").get<Debug>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Data` parsin" << std::endl;
    }
}

inline void to_json(json& j, const Data& resp) {
    j = json::object();

    j["aqi"] = resp.get_aqi();
    j["idx"] = resp.get_idx();
    j["attributions"] = resp.get_attributions();
    j["city"] = resp.get_city();
    j["dominentpol"] = resp.get_dominentpol();
    j["iaqi"] = resp.get_iaqi();
    j["time"] = resp.get_time();
    j["forecast"] = resp.get_forecast();
    j["debug"] = resp.get_debug();
}

inline void from_json(const json& j, ResponseAPI& resp) {
    try {
        resp.set_data(j.at("data").get<Data>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `Status` parsin" << std::endl;
    }

    try {
        resp.set_status(j.at("status").get<StatusResponseAPI>());
    } catch (const json::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "At `ResponseAPI` parsin" << std::endl;
    }
}

inline void to_json(json& j, const ResponseAPI& resp) {
    j = json::object();

    j["status"] = resp.get_status();
    j["data"] = resp.get_data();
}


/* Class */

template <typename JsonType, typename T>
class JsonSerializer {
public:
    virtual ~JsonSerializer() = default;

    virtual T from_json(const JsonType& json) = 0;
    virtual JsonType to_json(const T& obj) = 0;
};


template <typename T>
class JsonSerializerNlohmann : public JsonSerializer<nlohmann::json, T> {};

class AttributionsSerializer : public JsonSerializerNlohmann<Attributions> {
public:
    using json = nlohmann::json;

    Attributions from_json(const json& json) {
        Attributions attribution;

        attribution.set_url(json.at("url").get<std::string>());
        attribution.set_name(json.at("name").get<std::string>());
        attribution.set_logo(get_stack_optional<std::string>(json, "logo"));

        return attribution;
    }

    json to_json(const Attributions& attributions) {
        auto j = json::object();

        j["url"] = attributions.get_url();
        j["name"] = attributions.get_name();
        j["logo"] = attributions.get_logo();

        return j;
    }
};

class CitySerializer : public JsonSerializerNlohmann<City> {
public:
    City from_json(const json& j) {
        City city;

        city.set_geo(j.at("geo").get<std::array<double,2>>());
        city.set_name(j.at("name").get<std::string>());
        city.set_url(j.at("url").get<std::string>());
        city.set_location(j.at("location").get<std::string>());

        return city;
    }

    json to_json(City& city) {
        auto j = json::object();

        j["geo"] = city.get_geo();
        j["name"] = city.get_name();
        j["url"] = city.get_url();
        j["location"] = city.get_location();

        return j;
    }

};

class DebugSerializer : public JsonSerializerNlohmann<Debug> {
public:
    Debug from_json(const json& j) {
        Debug debug;

        debug.set(j.at("sync").get<std::string>());

        return debug;
    }

    json to_json(const Debug& debug) {
        auto j = json::object();

        j["sync"] = debug.get();

        return j;
    }

};

class MetricsSerializer : public JsonSerializerNlohmann<Metrics> {
public:

    Metrics from_json(const json& j) {
        Metrics metrics;

        metrics.set_avg(j.at("avg").get<double>());
        metrics.set_day(j.at("day").get<std::string>());
        metrics.set_min(j.at("min").get<double>());
        metrics.set_max(j.at("max").get<double>());

        return metrics;
    }

     json to_json(const Metrics& metrics) {
        auto j = json::object();

        j["avg"] = metrics.get_avg();
        j["day"] = metrics.get_day();
        j["min"] = metrics.get_min();
        j["max"] = metrics.get_max();

        return j;
    }
};

class DailySerializer : public JsonSerializerNlohmann<Daily> {
public:
    Daily form_json(const json& j) {
        Daily daily;

        daily.set_o3(j.at("o3").get<std::vector<Metrics>>());
        daily.set_pm10(j.at("pm10").get<std::vector<Metrics>>());
        daily.set_pm25(j.at("pm25").get<std::vector<Metrics>>());
        daily.set_uvi(j.at("uvi").get<std::vector<Metrics>>());

        return daily;
    }

    void to_json(json& j, const Daily& daily) {
        j = json::object();
        j["o3"] = daily.get_o3();
        j["pm10"] = daily.get_pm10();
        j["pm25"] = daily.get_pm25();
        j["uvi"] = daily.get_uvi();
    }
};

class ForecastSerializer : public JsonSerializerNlohmann<Forecast> {
public:
    Forecast from_json(const json& j) {
        Forecast forecast;

        forecast.set(j.at("daily").get<Daily>());

        return forecast;
    }

    json to_json(const Forecast& forecast) {
        auto j = json::object();

        j["forecast"] = forecast.get();

        return j;
    }

};

class ParamAdapterDSerializer : public JsonSerializerNlohmann<ParamAdapter<double>> {
public:
    ParamAdapter<double> from_json(const json& j) {
        class PA : public ParamAdapter<double> {};
        PA param;

        param.set(j.at("v").get<double>());

        return param;
    }

    json to_json(const ParamAdapter<double>& param) {
        auto j = json::object();

        j["v"] = param.get();

        return j;
    }
};

class IaqiSerializer : public JsonSerializerNlohmann<Iaqi> {
public:
    Iaqi from_json(const json& j) {
        Iaqi iaqi;

        iaqi.set_co(j.at("co").get<Co>());
        iaqi.set_h(j.at("h").get<H>());
        iaqi.set_no2(j.at("no2").get<No2>());
        iaqi.set_o3(j.at("o3").get<O3>());
        iaqi.set_p(j.at("p").get<P>());
        iaqi.set_pm10(j.at("pm10").get<Pm10>());
        iaqi.set_pm25(j.at("pm25").get<Pm25>());
        iaqi.set_so2(j.at("so2").get<So2>());
        iaqi.set_t(j.at("t").get<T>());

        return iaqi;
    }

    json to_json(const Iaqi& iaqi) {
        auto j = json::object();

        j["co"]   = iaqi.get_co();
        j["h"]    = iaqi.get_h();
        j["no2"]  = iaqi.get_no2();
        j["o3"]   = iaqi.get_o3();
        j["p"]    = iaqi.get_p();
        j["pm10"] = iaqi.get_pm10();
        j["pm25"] = iaqi.get_pm25();
        j["so2"]  = iaqi.get_so2();
        j["t"]    = iaqi.get_t();

        return j;
    }

};

class TimeSerializer : public JsonSerializerNlohmann<Time> {
public:
    Time from_json(const json& j) {
        Time time;

        time.set_s(j.at("s").get<std::string>());
        time.set_tz(j.at("tz").get<std::string>());
        time.set_v(j.at("v").get<double>());
        time.set_iso(j.at("iso").get<std::string>());

        return time;
    }

    json to_json(const Time& time) {
        auto j = json::object();

        j["s"]   = time.get_s();
        j["tz"]  = time.get_tz();
        j["v"]   = time.get_v();
        j["iso"] = time.get_iso();

        return j;
    }

};

class DataSerializer : public JsonSerializerNlohmann<Data> {
public:
    Data from_json(const json& j) {
        Data resp;

        resp.set_aqi(j.at("aqi").get<long>());
        resp.set_idx(j.at("idx").get<long>());
        resp.set_attributions(j.at("attributions").get<std::vector<Attributions>>());
        resp.set_city(j.at("city").get<City>());
        resp.set_dominentpol(j.at("dominentpol").get<std::string>());
        resp.set_iaqi(j.at("iaqi").get<Iaqi>());
        resp.set_time(j.at("time").get<Time>());
        resp.set_forecast(j.at("forecast").get<Forecast>());
        resp.set_debug(j.at("debug").get<Debug>());

        return resp;
    }

    json to_json(const Data& resp) {
        auto j = json::object();

        j["aqi"] = resp.get_aqi();
        j["idx"] = resp.get_idx();
        j["attributions"] = resp.get_attributions();
        j["city"] = resp.get_city();
        j["dominentpol"] = resp.get_dominentpol();
        j["iaqi"] = resp.get_iaqi();
        j["time"] = resp.get_time();
        j["forecast"] = resp.get_forecast();
        j["debug"] = resp.get_debug();

        return j;
    }

};

class ResponseAPISerializer : public JsonSerializerNlohmann<ResponseAPI> {
public:
    ResponseAPI from_json(const json& j) {
        ResponseAPI resp;

        resp.set_data(j.at("data").get<Data>());
        resp.set_status(j.at("status").get<StatusResponseAPI>());

        return resp;
    }

    json to_json(const ResponseAPI& resp) {
        auto j = json::object();

        j["status"] = resp.get_status();
        j["data"] = resp.get_data();

        return j;
    }

};



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




class API {
private:
    std::string token;
    std::string city;
    std::string base_url = "https://api.waqi.info/feed/";

public:
    explicit API(std::string token) : token(token) {}

    auto get_data(std::string city) {
        auto url = base_url + city + "/?token=" + token;
        auto r = cpr::Get(cpr::Url(url));
        auto j = json::parse(r.text);

        auto resp = JsonSerializerNlohmannAQIFactory::create<ResponseAPISerializer>();
        return resp->from_json(j);
    }
};


int main()
{
    std::string url("https://api.waqi.info/feed/barcelona/?token=f6f6f6af50e320629df1c50a4b9b7750a5526a22");
    cpr::Response r = cpr::Get(cpr::Url(url));
    json j = json::parse(r.text);

    ResponseAPI resp;

    from_json(j, resp);

    std::string token("f6f6f6af50e320629df1c50a4b9b7750a5526a22");
    API api(token);
    auto response = api.get_data("barcelona");

    std::cout << "Response status: " << response.get_status() << std::endl;
    std::cout << "Last data received: " << response.get_data().get_time().get_s() << std::endl;
    // std::cout <<
}
