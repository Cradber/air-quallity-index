#ifndef TIMESERIALIZER_H
#define TIMESERIALIZER_H

#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"

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


#endif // TIMESERIALIZER_H
