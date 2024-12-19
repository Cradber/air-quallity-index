#ifndef METRICSSERIALIZATION_H
#define METRICSSERIALIZATION_H


#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"


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

#endif // METRCISSERIALIZATION_H
