#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <array>


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



#endif // MODELS_H
