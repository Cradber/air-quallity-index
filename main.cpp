#include <iostream>

#include "cpr/api.h"
#include "serialization/nlohmann/serializers/responseapiserializer.h"
#include "factories/json_serializer_nlohmann_aqi_factory.h"

using json = nlohmann::json;



class API {
private:
    std::string token;
    std::string city;
    std::string base_url = "https://api.waqi.info/feed/";

public:
    explicit API(std::string token) : token(token) {}

    auto get_data(std::string city) {
        auto url = base_url + city + "/?token=" + token;
        auto r = cpr::Get(cpr::Url(url));
        auto j = json::parse(r.text);

        auto resp = JsonSerializerNlohmannAQIFactory::create<ResponseAPISerializer>();
        return resp->from_json(j);
    }
};


int main()
{
    std::string url("https://api.waqi.info/feed/barcelona/?token=f6f6f6af50e320629df1c50a4b9b7750a5526a22");
    cpr::Response r = cpr::Get(cpr::Url(url));
    json j = json::parse(r.text);

    // ResponseAPI resp;

    // from_json(j, resp);

    std::string token("f6f6f6af50e320629df1c50a4b9b7750a5526a22");
    API api(token);
    auto response = api.get_data("barcelona");

    std::cout << "Response status: " << response.get_status() << std::endl;
    std::cout << "Last data received: " << response.get_data().get_time().get_s() << std::endl;
    // std::cout <<
}
