//
// Created by ParticleG on 2022/2/9.
//

#include <helpers/ResponseJson.h>
#include <magic_enum.hpp>
#include <structures/Exceptions.h>

using namespace drogon;
using namespace magic_enum;
using namespace std;
using namespace hephaestus::helpers;
using namespace hephaestus::structures;
using namespace hephaestus::types;

ResponseJson::ResponseJson() : BasicJson() { setResultCode(types::ResultCode::completed); }

ResponseJson::ResponseJson(Json::Value json) : BasicJson(std::move(json)) {}

ResponseJson::ResponseJson(const string &raw) : BasicJson(raw) {}

ResponseJson::ResponseJson(const HttpResponsePtr &res) {
    auto object = res->getJsonObject();
    if (!object) {
        throw json_exception::InvalidFormat(res->getJsonError());
    }
    _value = std::move(*object);
}

void ResponseJson::setResultCode(const ResultCode &code) { setResultCode(enum_integer(code)); }

void ResponseJson::setResultCode(const uint32_t &code) { _value["code"] = code; }

void ResponseJson::setStatusCode(drogon::HttpStatusCode code) { _statusCode = code; }

void ResponseJson::setMessage(const string &message) { _value["message"] = message; }

void ResponseJson::setData(Json::Value data) { _value["data"] = move(data); }

void ResponseJson::setReason(const exception &e) { setReason(e.what()); }

[[maybe_unused]] void ResponseJson::setReason(const drogon::orm::DrogonDbException &e) { setReason(e.base().what()); }

void ResponseJson::setReason(const string &reason) { _value["reason"] = reason; }

void ResponseJson::httpCallback(const function<void(const drogon::HttpResponsePtr &)> &callback) {
    auto httpJsonResponse = HttpResponse::newHttpJsonResponse(_value);
    httpJsonResponse->setStatusCode(_statusCode);
    callback(httpJsonResponse);
}

void ResponseJson::httpCallback(const ResponseJson::HttpCallback &callback, const string &cors) {
    auto httpJsonResponse = HttpResponse::newHttpJsonResponse(_value);
    httpJsonResponse->setStatusCode(_statusCode);
    httpJsonResponse->addHeader("Access-Control-Allow-Origin", cors);
    httpJsonResponse->addHeader("Access-Control-Allow-Headers", cors);
    callback(httpJsonResponse);
}
