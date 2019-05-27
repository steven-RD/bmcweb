
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
    using InfoTypeP = std::pair<std::string, 
			     std::variant<std::string, 
			     std::vector<std::pair<std::string, std::string> >, 
			     std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string> > > > 
			     >
			     >;
    using InfoType = std::vector<std::pair<std::string, 
			     std::variant<std::string, 
			     std::vector<std::pair<std::string, std::string> >, 
			     std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string> > > > 
			     >
			     >>;
    
    using USIInforType = std::map<std::string, std::variant<std::string, 
                                std::map<std::string, std::string>, 
                                std::map<std::string, std::map<std::string, std::string>> > >;
    
    using USIInforTypeP = std::pair<std::string, std::variant<std::string, 
                                std::map<std::string, std::string>, 
                                std::map<std::string, std::map<std::string, std::string>> > >; 
    
   /* class Information : public Node {
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
    };*/
    
    class BindInfo : public Node {
    public:
        
        BindInfo(CrowApp& app) : Node(app, "/redfish/v1/Switch/BindInfo/") {
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
                {"@odata.context", "/redfish/v1/$metadata#Switch.BindInfo"},
                {"@odata.id", "/redfish/v1/Switch/BindInfo"},
                {"@odata.type", "#Information.v1_1_0.BindInfo"},
                {"Id", "BindInfo"},
                {"Name", "USI Info Information"},
                {"Description", "BindInfo Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<InfoType>& propertiesList){
                
                if (ec) {
                    messages::internalError(asyncResp->res);
                    return;
                }
                BMCWEB_LOG_DEBUG << "Got property for USI Bindinfo";
                const InfoType *value = 
                            std::get_if<InfoType>(&propertiesList);
                if(value != nullptr) {
                    for(const InfoTypeP& property : *value) {
                        if(property.first == "Bindinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///Bindinfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const std::map<std::string, std::string>* infos =
                                    std::get_if<std::map<std::string, std::string>>(&property.second);
                            if (infos != nullptr) {
                                for(const std::pair<std::string, std::string>& info : *infos) {
                                    asyncResp->res.jsonValue["Info"][property.first][info.first] = info.second;
                                } 
                            } 
                        }
                    }
                }
            
            },
            "com.usi.Ssdarray.Info",
            "/xyz/openbmc_project/ssdarray/info",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Info", "Info");
        }
        /**
         void doGet(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {
            
            auto asyncResp = std::make_shared<AsyncResp>(res);
            res.jsonValue = {
                {"@odata.context", "/redfish/v1/$metadata#Switch.BindInfo"},
                {"@odata.id", "/redfish/v1/Switch/BindInfo"},
                {"@odata.type", "#Information.v1_1_0.BindInfo"},
                {"Id", "BindInfo"},
                {"Name", "USI Info Information"},
                {"Description", "BindInfo Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<USIInforType>& propertiesList){
                
                if (ec) {
                    messages::internalError(asyncResp->res);
                    return;
                }
                BMCWEB_LOG_DEBUG << "Got property for USI Bindinfo";
                const USIInforType *value = 
                            std::get_if<USIInforType>(&propertiesList);
                if(value != nullptr) {
                    for(const USIInforTypeP& property : *value) {
                        if(property.first == "Bindinfo") {
                            const std::map<std::string, std::string>* infos =
                                    std::get_if<std::map<std::string, std::string>>(&property.second);
                            for(const std::pair<std::string, std::string>& info : *infos) {
                                asyncResp->res.jsonValue["Info"][property.first][info.first] = info.second;
                            }  
                        }
                    }
                }
            
            },
            "com.usi.Ssdarray.Info",
            "/xyz/openbmc_project/ssdarray/info",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Info", "Info");
        }
         */
    };
    
    class BindInfoTest : public Node {
    public:
        
        BindInfoTest(CrowApp& app) : Node(app, "/redfish/v1/Switch/BindInfoTest/") {
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
                {"@odata.context", "/redfish/v1/$metadata#Switch.BindInfo"},
                {"@odata.id", "/redfish/v1/Switch/BindInfo"},
                {"@odata.type", "#Information.v1_1_0.BindInfo"},
                {"Id", "BindInfo"},
                {"Name", "USI Info Information"},
                {"Description", "BindInfo Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<USIInforType>& propertiesList){
                
                if (ec) {
                    messages::internalError(asyncResp->res);
                    return;
                }
                BMCWEB_LOG_DEBUG << "Got property for USI Bindinfo";
                const USIInforType *value = 
                            std::get_if<USIInforType>(&propertiesList);
                if(value != nullptr) {
                    for(const USIInforTypeP& property : *value) {
                        if(property.first == "Bindinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///Bindinfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const std::map<std::string, std::string>* infos =
                                    std::get_if<std::map<std::string, std::string>>(&property.second);
                            if (infos != nullptr) {     
                                for(const std::pair<std::string, std::string>& info : *infos) {
                                    asyncResp->res.jsonValue["Info"][property.first][info.first] = info.second;
                                } 
                            } 
                        }
                    }
                }
            
            },
            "com.usi.Ssdarray.Info",
            "/xyz/openbmc_project/ssdarray/info",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Info", "Info");
        }
    
}

#endif /* USI_INFORMATION_HPP */




