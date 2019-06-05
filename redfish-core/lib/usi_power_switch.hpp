
/* 
 * File:   usi_control.hpp
 * Author: Steven
 *
 * Created on 20190527
 */

#ifndef USI_POWER_SWITCH_HPP
#define USI_POWER_SWITCH_HPP


#include "node.hpp"

#include <dbus_utility.hpp>
#include <error_messages.hpp>
#include <openbmc_dbus_rest.hpp>
#include <utils/json_utils.hpp>
#include <variant>

namespace redfish {
     class PowerSwitch : public Node {
    public:

        PowerSwitch(CrowApp& app) : Node(app, "/redfish/v1/Managers/Switch/PowerSwitch/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Managers.Switch.PowerSwitch"},
                {"@odata.id", "/redfish/v1/Managers/Switch/PowerSwitch"},
                {"@odata.type", "#PowerSwitch.v1_1_0.PowerSwitch"},
                {"Name", "PowerSwitch Information"},
                {"Description", "Get PowerSwitch Information"}
            };
            
            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<std::string>& property) {
                    
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got  property for Switch Power Switch";

                        const std::string* value =
                                std::get_if<std::string>(&property);
                        if(value != nullptr) {
                            asyncResp->res.jsonValue["Status"] = *value;
                        }                        
                    },
            "com.usi.Ssdarray.Powerswitch",
            "/xyz/openbmc_project/ssdarray/powerswitch",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Powerswitch", "Status");
         }
         
     };
}



#endif /* USI_POWER_SWITCH_HPP */

