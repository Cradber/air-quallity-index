#ifndef CITYSERIALIZATION_H
#define CITYSERIALIZATION_H


#include "nlohmann/json.hpp"
#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"


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


#endif // CITYSERIALIZATION_H
