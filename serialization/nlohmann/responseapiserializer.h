#ifndef RESPONSEAPISERIALIZER_H
#define RESPONSEAPISERIALIZER_H


#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"


class ResponseAPISerializer : public JsonSerializerNlohmann<ResponseAPI> {
public:
    ResponseAPI from_json(const json& j) {
        ResponseAPI resp;

        resp.set_data(j.at("data").get<Data>());
        resp.set_status(j.at("status").get<StatusResponseAPI>());

        return resp;
    }

    json to_json(const ResponseAPI& resp) {
        auto j = json::object();

        j["status"] = resp.get_status();
        j["data"] = resp.get_data();

        return j;
    }

};

#endif // RESPONSEAPISERIALIZER_H
