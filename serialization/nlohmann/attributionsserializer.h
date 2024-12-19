#ifndef ATTRIBUTIONSSERIALIZER_H
#define ATTRIBUTIONSSERIALIZER_H

#include <string>

#include "nlohmann/json.hpp"
#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"

class AttributionsSerializer : public JsonSerializerNlohmann<Attributions> {
public:
    using json = nlohmann::json;

    virtual ~AttributionsSerializer() = default;

    Attributions from_json(const json& json) {
        Attributions attribution;

        attribution.set_url(json.at("url").get<std::string>());
        attribution.set_name(json.at("name").get<std::string>());
        attribution.set_logo(get_stack_optional<std::string>(json, "logo"));

        return attribution;
    }

    json to_json(const Attributions& attributions) {
        auto j = json::object();

        j["url"] = attributions.get_url();
        j["name"] = attributions.get_name();
        j["logo"] = attributions.get_logo();

        return j;
    }
};

#endif // ATTRIBUTIONSSERIALIZER_H
