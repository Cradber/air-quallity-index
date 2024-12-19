#ifndef FORECASTSERIALIZER
#define FORECASTSERIALIZER

#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"

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

#endif // FORECASTSERIALIZER
