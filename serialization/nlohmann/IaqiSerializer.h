#ifndef IAQISERIALIZATION_H
#define IAQISERIALIZATION_H

#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"


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

#endif // IAQISERIALIZATION_H
