#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <array>
#include <vector>


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
    City(std::string name, std::string url, std::string location, std::array<double, 2> geo);
    virtual ~City() = default;

    std::string get_url() const;
    void set_url(std::string url);

    std::string get_name() const;
    void set_name(std::string name);

    std::string get_location() const;
    void set_location(std::string location);

    std::array<double, 2> get_geo() const;
    void set_geo(std::array<double, 2>  value);

    double get_geo_latitude() const;
    void set_geo_latitute(double lat);

    double get_geo_longitude() const;
    void set_geo_longitude(double lon);
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
          std::vector<Metrics> uvi);
    virtual ~Daily() = default;

    std::vector<Metrics> get_o3() const;
    void set_o3(std::vector<Metrics> o3);

    std::vector<Metrics> get_pm10() const;
    void set_pm10(std::vector<Metrics> pm10);

    std::vector<Metrics> get_pm25() const;
    void set_pm25(std::vector<Metrics> pm25);

    std::vector<Metrics> get_uvi() const;
    void set_uvi(std::vector<Metrics> uvi);
};


template <typename T>
class ParamAdapter {
private:
    T data;

protected:
    ParamAdapter() = default;
    explicit ParamAdapter(const T& data);
    virtual ~ParamAdapter() = default;

public:
    const T& get() const;
    void set(const T& data);
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



#endif // MODELS_H
