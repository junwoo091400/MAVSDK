// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/param_server/param_server.proto)

#include "param_server/param_server.grpc.pb.h"
#include "plugins/param_server/param_server.h"

#include "mavsdk.h"

#include "lazy_plugin.h"

#include "log.h"
#include <atomic>
#include <cmath>
#include <future>
#include <limits>
#include <memory>
#include <sstream>
#include <vector>

namespace mavsdk {
namespace mavsdk_server {

template<typename ParamServer = ParamServer, typename LazyPlugin = LazyPlugin<ParamServer>>

class ParamServerServiceImpl final : public rpc::param_server::ParamServerService::Service {
public:
    ParamServerServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}

    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::ParamServer::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_param_server_result = new rpc::param_server::ParamServerResult();
        rpc_param_server_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_param_server_result->set_result_str(ss.str());

        response->set_allocated_param_server_result(rpc_param_server_result);
    }

    static std::unique_ptr<rpc::param_server::IntParam>
    translateToRpcIntParam(const mavsdk::ParamServer::IntParam& int_param)
    {
        auto rpc_obj = std::make_unique<rpc::param_server::IntParam>();

        rpc_obj->set_name(int_param.name);

        rpc_obj->set_value(int_param.value);

        return rpc_obj;
    }

    static mavsdk::ParamServer::IntParam
    translateFromRpcIntParam(const rpc::param_server::IntParam& int_param)
    {
        mavsdk::ParamServer::IntParam obj;

        obj.name = int_param.name();

        obj.value = int_param.value();

        return obj;
    }

    static std::unique_ptr<rpc::param_server::FloatParam>
    translateToRpcFloatParam(const mavsdk::ParamServer::FloatParam& float_param)
    {
        auto rpc_obj = std::make_unique<rpc::param_server::FloatParam>();

        rpc_obj->set_name(float_param.name);

        rpc_obj->set_value(float_param.value);

        return rpc_obj;
    }

    static mavsdk::ParamServer::FloatParam
    translateFromRpcFloatParam(const rpc::param_server::FloatParam& float_param)
    {
        mavsdk::ParamServer::FloatParam obj;

        obj.name = float_param.name();

        obj.value = float_param.value();

        return obj;
    }

    static std::unique_ptr<rpc::param_server::CustomParam>
    translateToRpcCustomParam(const mavsdk::ParamServer::CustomParam& custom_param)
    {
        auto rpc_obj = std::make_unique<rpc::param_server::CustomParam>();

        rpc_obj->set_name(custom_param.name);

        rpc_obj->set_value(custom_param.value);

        return rpc_obj;
    }

    static mavsdk::ParamServer::CustomParam
    translateFromRpcCustomParam(const rpc::param_server::CustomParam& custom_param)
    {
        mavsdk::ParamServer::CustomParam obj;

        obj.name = custom_param.name();

        obj.value = custom_param.value();

        return obj;
    }

    static std::unique_ptr<rpc::param_server::AllParams>
    translateToRpcAllParams(const mavsdk::ParamServer::AllParams& all_params)
    {
        auto rpc_obj = std::make_unique<rpc::param_server::AllParams>();

        for (const auto& elem : all_params.int_params) {
            auto* ptr = rpc_obj->add_int_params();
            ptr->CopyFrom(*translateToRpcIntParam(elem).release());
        }

        for (const auto& elem : all_params.float_params) {
            auto* ptr = rpc_obj->add_float_params();
            ptr->CopyFrom(*translateToRpcFloatParam(elem).release());
        }

        for (const auto& elem : all_params.custom_params) {
            auto* ptr = rpc_obj->add_custom_params();
            ptr->CopyFrom(*translateToRpcCustomParam(elem).release());
        }

        return rpc_obj;
    }

    static mavsdk::ParamServer::AllParams
    translateFromRpcAllParams(const rpc::param_server::AllParams& all_params)
    {
        mavsdk::ParamServer::AllParams obj;

        for (const auto& elem : all_params.int_params()) {
            obj.int_params.push_back(
                translateFromRpcIntParam(static_cast<mavsdk::rpc::param_server::IntParam>(elem)));
        }

        for (const auto& elem : all_params.float_params()) {
            obj.float_params.push_back(translateFromRpcFloatParam(
                static_cast<mavsdk::rpc::param_server::FloatParam>(elem)));
        }

        for (const auto& elem : all_params.custom_params()) {
            obj.custom_params.push_back(translateFromRpcCustomParam(
                static_cast<mavsdk::rpc::param_server::CustomParam>(elem)));
        }

        return obj;
    }

    static rpc::param_server::ParamServerResult::Result
    translateToRpcResult(const mavsdk::ParamServer::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::ParamServer::Result::Unknown:
                return rpc::param_server::ParamServerResult_Result_RESULT_UNKNOWN;
            case mavsdk::ParamServer::Result::Success:
                return rpc::param_server::ParamServerResult_Result_RESULT_SUCCESS;
            case mavsdk::ParamServer::Result::NotFound:
                return rpc::param_server::ParamServerResult_Result_RESULT_NOT_FOUND;
            case mavsdk::ParamServer::Result::WrongType:
                return rpc::param_server::ParamServerResult_Result_RESULT_WRONG_TYPE;
            case mavsdk::ParamServer::Result::ParamNameTooLong:
                return rpc::param_server::ParamServerResult_Result_RESULT_PARAM_NAME_TOO_LONG;
            case mavsdk::ParamServer::Result::NoSystem:
                return rpc::param_server::ParamServerResult_Result_RESULT_NO_SYSTEM;
            case mavsdk::ParamServer::Result::ParamValueTooLong:
                return rpc::param_server::ParamServerResult_Result_RESULT_PARAM_VALUE_TOO_LONG;
        }
    }

    static mavsdk::ParamServer::Result
    translateFromRpcResult(const rpc::param_server::ParamServerResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::param_server::ParamServerResult_Result_RESULT_UNKNOWN:
                return mavsdk::ParamServer::Result::Unknown;
            case rpc::param_server::ParamServerResult_Result_RESULT_SUCCESS:
                return mavsdk::ParamServer::Result::Success;
            case rpc::param_server::ParamServerResult_Result_RESULT_NOT_FOUND:
                return mavsdk::ParamServer::Result::NotFound;
            case rpc::param_server::ParamServerResult_Result_RESULT_WRONG_TYPE:
                return mavsdk::ParamServer::Result::WrongType;
            case rpc::param_server::ParamServerResult_Result_RESULT_PARAM_NAME_TOO_LONG:
                return mavsdk::ParamServer::Result::ParamNameTooLong;
            case rpc::param_server::ParamServerResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::ParamServer::Result::NoSystem;
            case rpc::param_server::ParamServerResult_Result_RESULT_PARAM_VALUE_TOO_LONG:
                return mavsdk::ParamServer::Result::ParamValueTooLong;
        }
    }

    grpc::Status RetrieveParamInt(
        grpc::ServerContext* /* context */,
        const rpc::param_server::RetrieveParamIntRequest* request,
        rpc::param_server::RetrieveParamIntResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::ParamServer::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "RetrieveParamInt sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->retrieve_param_int(request->name());

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_value(result.second);
        }

        return grpc::Status::OK;
    }

    grpc::Status ProvideParamInt(
        grpc::ServerContext* /* context */,
        const rpc::param_server::ProvideParamIntRequest* request,
        rpc::param_server::ProvideParamIntResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::ParamServer::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "ProvideParamInt sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result =
            _lazy_plugin.maybe_plugin()->provide_param_int(request->name(), request->value());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status RetrieveParamFloat(
        grpc::ServerContext* /* context */,
        const rpc::param_server::RetrieveParamFloatRequest* request,
        rpc::param_server::RetrieveParamFloatResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::ParamServer::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "RetrieveParamFloat sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->retrieve_param_float(request->name());

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_value(result.second);
        }

        return grpc::Status::OK;
    }

    grpc::Status ProvideParamFloat(
        grpc::ServerContext* /* context */,
        const rpc::param_server::ProvideParamFloatRequest* request,
        rpc::param_server::ProvideParamFloatResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::ParamServer::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "ProvideParamFloat sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result =
            _lazy_plugin.maybe_plugin()->provide_param_float(request->name(), request->value());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status RetrieveParamCustom(
        grpc::ServerContext* /* context */,
        const rpc::param_server::RetrieveParamCustomRequest* request,
        rpc::param_server::RetrieveParamCustomResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::ParamServer::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "RetrieveParamCustom sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->retrieve_param_custom(request->name());

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_value(result.second);
        }

        return grpc::Status::OK;
    }

    grpc::Status ProvideParamCustom(
        grpc::ServerContext* /* context */,
        const rpc::param_server::ProvideParamCustomRequest* request,
        rpc::param_server::ProvideParamCustomResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::ParamServer::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "ProvideParamCustom sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result =
            _lazy_plugin.maybe_plugin()->provide_param_custom(request->name(), request->value());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status RetrieveAllParams(
        grpc::ServerContext* /* context */,
        const rpc::param_server::RetrieveAllParamsRequest* /* request */,
        rpc::param_server::RetrieveAllParamsResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->retrieve_all_params();

        if (response != nullptr) {
            response->set_allocated_params(translateToRpcAllParams(result).release());
        }

        return grpc::Status::OK;
    }

    void stop()
    {
        _stopped.store(true);
        for (auto& prom : _stream_stop_promises) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        }
    }

private:
    void register_stream_stop_promise(std::weak_ptr<std::promise<void>> prom)
    {
        // If we have already stopped, set promise immediately and don't add it to list.
        if (_stopped.load()) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        } else {
            _stream_stop_promises.push_back(prom);
        }
    }

    void unregister_stream_stop_promise(std::shared_ptr<std::promise<void>> prom)
    {
        for (auto it = _stream_stop_promises.begin(); it != _stream_stop_promises.end();
             /* ++it */) {
            if (it->lock() == prom) {
                it = _stream_stop_promises.erase(it);
            } else {
                ++it;
            }
        }
    }

    LazyPlugin& _lazy_plugin;

    std::atomic<bool> _stopped{false};
    std::vector<std::weak_ptr<std::promise<void>>> _stream_stop_promises{};
};

} // namespace mavsdk_server
} // namespace mavsdk