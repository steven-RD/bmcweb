
/* 
 * File:   usi_control.hpp
 * Author: Steven
 *
 * Created on 20190520
 */

#ifndef USI_CONTROL_HPP
#define USI_CONTROL_HPP

#include "node.hpp"

#include <dbus_utility.hpp>
#include <error_messages.hpp>
#include <openbmc_dbus_rest.hpp>
#include <utils/json_utils.hpp>
#include <variant>


namespace redfish {

    class Control : public Node {
    public:

        Control(CrowApp& app) : Node(app, "/redfish/v1/Switch/Control/") {
            entityPrivileges = {
                {boost::beast::http::verb::get,{
                        {"ConfigureUsers"},
                        {"ConfigureManager"}}},
                {boost::beast::http::verb::head,{
                        {"Login"}}},
                {boost::beast::http::verb::patch,{
                        {"ConfigureUsers"}}},
                {boost::beast::http::verb::put,{
                        {"ConfigureUsers"}}},
                {boost::beast::http::verb::delete_,{
                        {"ConfigureUsers"}}},
                {boost::beast::http::verb::post,{
                        {"ConfigureUsers"}}}
            };
        }
        
    private:
        
        void doGet(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {
            
            auto asyncResp = std::make_shared<AsyncResp>(res);
            res.jsonValue = {
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch..Control"},
                {"@odata.id", "/redfish/v1/Switch//Control"},
                {"@odata.type", "#Control.v1_1_0.Control"},
                {"Name", "Control Information"},
                {"Description", "Get Control Information"}
            };
            
            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<std::string,
                    std::variant < std::string>>>& propertiesList) {
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got " << propertiesList.size()
                                << "properties for Firmware Control";

                        for (const std::pair<std::string, std::variant < std::string>>&
                                property : propertiesList) {
                            if (property.first == "Command") {
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Command"] = *value;
                                }
                            }
                            if (property.first == "Status") {
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Status"] = *value;
                                }
                            }
                        }
                    },
            "com.usi.Ssdarray.Control",
            "/xyz/openbmc_project/ssdarray/control",
            "org.freedesktop.DBus.Properties", "GetAll",
            "com.usi.Ssdarray.Control");
         }
        
        void doPatch(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {            
            auto asyncResp = std::make_shared<AsyncResp>(res);

            std::optional<std::string> command;
            if (!json_util::readJson(req, res, "Command", command)) {
                return;
            }
            if (command) {
                crow::connections::systemBus->async_method_call(
                    [this, asyncResp, command](
                    const boost::system::error_code ec) {
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        messages::success(asyncResp->res);
                    },
                "com.usi.Ssdarray.Control",
                "/xyz/openbmc_project/ssdarray/control",
                "org.freedesktop.DBus.Properties", "Set",
                "com.usi.Ssdarray.Control", "Command", std::variant<std::string>(*command)); 
            }
        }
        
    };

}



#endif /* USI_CONTROL_HPP */

