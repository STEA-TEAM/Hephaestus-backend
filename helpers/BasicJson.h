//
// Created by ParticleG on 2022/2/9.
//

#pragma once

#include <drogon/drogon.h>

namespace hephaestus::helpers {
    class BasicJson {
    public:
        BasicJson();

        explicit BasicJson(Json::Value json);

        explicit BasicJson(const std::string &raw);

        [[nodiscard]] std::string stringify(const std::string &indentation = "") const;

        Json::Value &ref();

        [[nodiscard]] Json::Value copy() const;

        void operator()(Json::Value &&another);

        const Json::Value &operator[](Json::ArrayIndex index) const;

        const Json::Value &operator[](int index) const;

        const Json::Value &operator[](const char *key) const;

        const Json::Value &operator[](const Json::String &key) const;

        virtual ~BasicJson() = default;

    protected:
        Json::Value _value;
    };
}



