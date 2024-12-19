#ifndef JSON_SERIALIZATION_H
#define JSON_SERIALIZATION_H


template <typename JsonType, typename T>
class JsonSerializer {
public:
    virtual ~JsonSerializer() = default;

    virtual T from_json(const JsonType& json) = 0;
    virtual JsonType to_json(const T& obj) = 0;
};


#endif // JSON_SERIALIZATION_H
