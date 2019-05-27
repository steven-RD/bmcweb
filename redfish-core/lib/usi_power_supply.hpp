
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
    
    using PowerSupplyTypeP = std::pair<std::string, 
            std::variant<std::string, 
            std::vector<std::pair<std::string, std::string> > > >;
    using PowerSupplyType = std::vector<std::pair<std::string, 
            std::variant<std::string, 
                std::vector<std::pair<std::string, std::string> > > >>;

    class PowerSupply : public Node {
    public:
        
        PowerSupply(CrowApp& app) : Node (app, "/redfish/v1/Switch/PowerSupply/") {
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
                {"@odata.type", "#PowerSupply.v1_1_0.PowerSupply"},
                {"Name", "PowerSupply Information"},
                {"Description", "Get PowerSupply Information"}
            };
            
            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    /*const std::map<std::string, std::variant<std::string, std::map<std::string, std::string> > >& propertiesList) {
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        
                        BMCWEB_LOG_DEBUG << "Got property for Switch PowerSupply";
                        
                        for (const std::pair<std::string,  std::variant<std::string, std::map<std::string, std::string> > >&
                                property : propertiesList) {
                            if(property.first == "PSA"){
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Status"]["PSA"] = *value;
                                }
                                const std::map<std::string, std::string>* error = 
                                        std::get_if<std::map<std::string, std::string>>(&property.second);
                                if(error != nullptr){
                                    for(const std::pair<std::string, std::string>& it : *error) {
                                        asyncResp->res.jsonValue["Status"]["PSA"][it.first] =  it.second;    
                                    }
                                }
                            }
                            
                        }*/
                    const std::variant<PowerSupplyType>& propertiesList) {
                        
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got property for Switch PowerSupply";
                        const PowerSupplyType *value= std::get_if<PowerSupplyType>(&propertiesList);   
                        for(const PowerSupplyTypeP& property : *value) {
                            const std::string* val =
                                    std::get_if<std::string>(&property.second);
                            if (val != nullptr) {
                                asyncResp->res.jsonValue["Status"][property.first] = *val;
                            }
                            const std::vector<std::pair<std::string, std::string> >* error = 
                                        std::get_if<std::vector<std::pair<std::string, std::string> >>(&property.second);
                            if(error != nullptr){
                                for(const std::pair<std::string, std::string>& it : *error) {
                                    asyncResp->res.jsonValue["Status"][property.first][it.first] =  it.second;    
                                }
                            }
                        }
                                     
                    },
            "com.usi.Ssdarray.Powersupply", 
            "/xyz/openbmc_project/ssdarray/powersupply",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Powersupply", "Status");
        }
        
    };
    
}


#endif /* USI_POWER_SUPPLY_HPP */

