
/* 
 * File:   usi_power_supply.hpp
 * Author: Steven
 *
 * Created on 20190520
 */

#ifndef USI_POWER_SUPPLY_HPP
#define USI_POWER_SUPPLY_HPP

#include "node.hpp"

#include <dbus_utility.hpp>
#include <error_messages.hpp>
#include <openbmc_dbus_rest.hpp>
#include <utils/json_utils.hpp>
#include <variant>

namespace redfish {

    class PowerSupply : public Node {
    public:
        
        PowerSupply(CrowApp& app) : Node (app, "/redfish/v1/Swtich/PowerSupply/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.PowerSupply"},
                {"@odata.id", "/redfish/v1/Switch/PowerSupply"},
                {"@odata.type", "#Control.v1_1_0.PowerSupply"},
                {"Name", "PowerSupply Information"},
                {"Description", "Get PowerSupply Information"}
            };
            
            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<std::vector<std::string>>& property){
                    
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got property for Switch PowerSupply";

                        const std::vector<std::string> *value =
                                std::get_if<std::vector<std::string>>(&property);

                        if(value != nullptr){
                            asyncResp->res.jsonValue["Status"]["PSA"] = (*value)[0];
                            asyncResp->res.jsonValue["Status"]["PSB"] = (*value)[1];
                         }
                    },
            "com.usi.Ssdarray.powersupply", 
            "/xyz/openbmc_project/ssdarray/powersupply",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Powersupply", "Status");
        }
        
    };
    
}


#endif /* USI_POWER_SUPPLY_HPP */

