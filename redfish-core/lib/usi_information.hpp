
/* 
 * File:   usi_switch.hpp
 * Author: Steven
 *
 * Created 20190520
 */

#ifndef USI_INFORMATION_HPP
#define USI_INFORMATION_HPP

#include "node.hpp"

#include <dbus_utility.hpp>
#include <error_messages.hpp>
#include <openbmc_dbus_rest.hpp>
#include <utils/json_utils.hpp>
#include <variant>

namespace redfish {
    
    using DicStrType = std::vector<std::pair<std::string, std::string> >;	
    using DicStrDicType = std::vector<std::pair<std::string, 
                std::vector<std::pair<std::string, std::string> > > >;
    using InfoVariant = std::variant<std::string, DicStrType, DicStrDicType>;
    
    using InfoType = std::vector<std::pair<std::string, 
			     std::variant<std::string, 
			     std::vector<std::pair<std::string, std::string> >, 
			     std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string> > > > 
			     >
			     >>;
    
    class Information : public Node {
    public:
        
        Information(CrowApp& app) : Node(app, "/redfish/v1/Switch/Information/") {
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
                {"@odata.context", "/redfish/v1/$metadata#Switch.Information"},
                {"@odata.id", "/redfish/v1/Switch/Information"},
                {"@odata.type", "#Information.v1_1_0.Information"},
                {"Id", "Information"},
                {"Name", "USI Info Information"},
                {"Description", "Info Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<
                    std::string, std::variant<uint32_t, uint16_t, uint8_t>>>&
                    propertiesList){
                
            
            },
            "com.usi.Ssdarray.Info",
            "/xyz/openbmc_project/ssdarray/info",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Info", "Info");
        }
    };
    
    
}

#endif /* USI_INFORMATION_HPP */




