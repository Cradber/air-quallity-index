#ifndef DEBUGSERIALIZER_H
#define DEBUGSERIALIZER_H

#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"


class DebugSerializer : public JsonSerializerNlohmann<Debug> {
public:
    Debug from_json(const json& j) {
        Debug debug;

        debug.set(j.at("sync").get<std::string>());

        return debug;
    }

    json to_json(const Debug& debug) {
        auto j = json::object();

        j["sync"] = debug.get();

        return j;
    }

};


#endif // DEBUGSERIALIZER_H
