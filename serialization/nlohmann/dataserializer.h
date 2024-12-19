#ifndef DATASERIALIZER_H
#define DATASERIALIZER_H

#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"

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


#endif // DATASERIALIZER_H
