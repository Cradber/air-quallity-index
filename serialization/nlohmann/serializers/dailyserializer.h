#ifndef DAILYSERIALIZER_H
#define DAILYSERIALIZER_H

#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"

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


#endif // DAILYSERIALIZER_H
