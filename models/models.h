#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "nlohmann/detail/macro_scope.hpp"


class Attributions {
private:
    std::string url;
    std::string name;
    std::optional<std::string> logo;

public:
    Attributions() = default;
    Attributions(std::string url, std::string name, std::optional<std::string> logo);
    virtual ~Attributions() = default;

    std::string get_url() const;
    void set_url(std::string url);

    std::string get_name() const;
    void set_name(std::string name);

    std::optional<std::string> get_logo();
    void set_logo(std::optional<std::string> logo);
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
    Daily(std::vector<Metrics> o3,
          std::vector<Metrics> pm10,
          std::vector<Metrics> pm25,
          std::vector<Metrics> uvi)
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
    inline const Co & get_co() const { return co; }
    inline void set_co(const Co & value) { this->co = value; }

    inline const H & get_h() const { return h; }
    inline void set_h(const H & value) { this->h = value; }

    inline const No2 & get_no2() const { return no2; }
    inline void set_no2(const No2 & value) { this->no2 = value; }

    inline const O3 & get_o3() const { return o3; }
    inline void set_o3(const O3 & value) { this->o3 = value; }

    inline const P & get_p() const { return p; }
    inline void set_p(const P & value) { this->p = value; }

    inline const Pm10 & get_pm10() const { return pm10; }
    inline void set_pm10(const Pm10 & value) { this->pm10 = value; }

    inline const Pm25 & get_pm25() const { return pm25; }
    inline void set_pm25(const Pm25 & value) { this->pm25 = value; }

    inline const So2 & get_so2() const { return so2; }
    inline void set_so2(const So2 & value) { this->so2 = value; }

    inline const T & get_t() const { return t; }
    inline void set_t(const T & value) { this->t = value; }
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

    inline std::string get_s() const { return s; }
    inline void set_s(std::string s) { this->s = s; }

    inline std::string get_tz() const { return tz; }
    inline void set_tz(std::string tz) { this->tz= tz; }

    inline std::string get_iso() const { return iso; }
    inline void set_iso(std::string iso) { this->iso= iso; }

    inline double get_v() const { return v; }
    inline void set_v(double v) { this->v = v; }
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

    inline const long & get_aqi() const { return aqi; }
    inline void set_aqi(const long & value) { this->aqi = value; }

    inline const long & get_idx() const { return idx; }
    inline void set_idx(const long & value) { this->idx = value; }

    inline const std::vector<Attributions> & get_attributions() const { return attributions; }
    inline void set_attributions(const std::vector<Attributions> & value) { this->attributions = value; }

    inline const City & get_city() const { return city; }
    inline void set_city(const City & value) { this->city = value; }

    inline const std::string & get_dominentpol() const { return dominentpol; }
    inline void set_dominentpol(const std::string & value) { this->dominentpol = value; }

    inline const Iaqi & get_iaqi() const { return iaqi; }
    inline void set_iaqi(const Iaqi & value) { this->iaqi = value; }

    inline const Time & get_time() const { return time; }
    inline void set_time(const Time & value) { this->time = value; }

    inline const Forecast & get_forecast() const { return forecast; }
    inline void set_forecast(const Forecast & value) { this->forecast = value; }

    inline const Debug & get_debug() const { return debug; }
    inline void set_debug(const Debug & value) { this->debug = value; }
};


enum class StatusResponseAPI {
    OK = 200,
    ERROR = 400
};
NLOHMANN_JSON_SERIALIZE_ENUM(StatusResponseAPI,{
    {StatusResponseAPI::OK, "ok"},
    {StatusResponseAPI::ERROR, "error"}
});
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

    inline StatusResponseAPI get_status() const { return status; }
    inline void set_status(StatusResponseAPI status) { this->status = status; }

    inline const Data get_data() const { return data; }
    inline void set_data(const Data& data) { this->data = data; }
};



#endif // MODELS_H
