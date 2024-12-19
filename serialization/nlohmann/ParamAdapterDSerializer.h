#ifndef PARAMADAPTERDSERIALIZATION
#define PARAMADAPTERDSERIALIZATION

#include "models/models.h"
#include "serialization/nlohmann/jsonserializernlohmann.h"


class ParamAdapterDSerializer : public JsonSerializerNlohmann<ParamAdapter<double>> {
public:
    ParamAdapter<double> from_json(const json& j) {
        class PA : public ParamAdapter<double> {};
        PA param;

        param.set(j.at("v").get<double>());

        return param;
    }

    json to_json(const ParamAdapter<double>& param) {
        auto j = json::object();

        j["v"] = param.get();

        return j;
    }
};

#endif // PARAMADAPTERDSERIALIZATION
