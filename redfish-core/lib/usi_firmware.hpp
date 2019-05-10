/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usi_firmware.hpp
 * Author: 075061
 *
 * Created on 2019年4月26日, 上午8:59
 */

#ifndef USI_FIRMWARE_HPP
#define USI_FIRMWARE_HPP


#include "node.hpp"

#include <dbus_utility.hpp>
#include <error_messages.hpp>
#include <openbmc_dbus_rest.hpp>
#include <utils/json_utils.hpp>
#include <variant>

namespace redfish {
    
    class FirmwareService : public Node {
    public:
        
        FirmwareService(CrowApp& app) : Node(app, "/redfish/v1/Switch/FirmwareService/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService"},
                {"@odata.id", "/redfish/v1/Switch/FirmwareService"},
                {"@odata.type", "#FirmwareService.v1_1_0.FirmwareService"},
                {"Id", "Firmware"},
                {"Name", "FirmwareService Information"},
                {"Description", "FirmwareService Information"},   
                {"Firmware",
                    {
                        {"@odata.id", "/redfish/v1/Switch/FirmwareService/Activate"}
                    },{
                        {"@odata.id", "/redfish/v1/Switch/FirmwareService/Functional"}
                    },{
                        {"@odata.id", "/redfish/v1/Switch/FirmwareService/Ready"}
                    },{
                        {"@odata.id", "/redfish/v1/Switch/FirmwareService/Update"}
                    }
                }
            };
        }
            
    };
    
    class Functionl : public Node {
    public:
        
        Functionl(CrowApp& app) : Node(app, "/redfish/v1/Switch/FirmwareService/Functionl/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.Functionl"},
                {"@odata.id", "/redfish/v1/Switch/FirmwareService/Functionl"},
                {"@odata.type", "#Functionl.v1_1_0.Functionl"},
                {"Name", "Functionl Information"},
                {"Description", "Functionl Information"}
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<
                    std::string, std::vector<std::string>>>& propertiesList) {
                    if (ec) {
                        messages::internalError(asyncResp->res);
                        return;
                    }
                    BMCWEB_LOG_DEBUG << "Got " << propertiesList.size()
                            << "properties for FirmwareService Functionl";

                    for(const std::pair<std::string, std::vector<std::string>>& 
                            property : propertiesList) {
                        if(property.first == "Version") {
                            const std::vector<std::string> value(property.second);
                            if(!value.empty()){
                                asyncResp->res.jsonValue["ConfigurationFileVersion"] = value[0];
                                asyncResp->res.jsonValue["FirmwareVersion"] = value[1];
//                                asyncResp->res.jsonValue["Status"] = *value;
                            }
                        }
                    }
                },
            "xyz.openbmc_project.Ssdarray.Firmware", 
            "/xyz/openbmc_project/ssdarray/firmware/functional",
            "org.freedesktop.DBus.Properties", "GetAll",
            "xyz.openbmc_project.Ssdarray.Functional");
        }
        
    };
    
    class Ready : public Node {
    public:
        
        Ready(CrowApp& app) : Node(app, "/redfish/v1/Switch/FirmwareService/Ready/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.Ready"},
                {"@odata.id", "/redfish/v1/Switch/FirmwareService/Ready"},
                {"@odata.type", "#Ready.v1_1_0.Ready"},
                {"Name", "Ready Information"},
                {"Description", "Ready Information"}
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<std::string, std::string>>&
                    propertiesList) {
                    if (ec) {
                        messages::internalError(asyncResp->res);
                        return;
                    }
                    BMCWEB_LOG_DEBUG << "Got " << propertiesList.size()
                            << "properties for FirmwareService Ready";

                    for(const std::pair<std::string, std::string>& 
                            property : propertiesList) {
                        if(property.first == "Type") {
                            const std::string* value = (&property.second);
                                    //std::get_if<std::string>(&property.second);
                            if(value != nullptr){
                                asyncResp->res.jsonValue["Type"] = *value;
                            }
                        }
                        if(property.first == "Version") {
                            const std::string* value = (&property.second);
                                    //std::get_if<std::string>(&property.second);
                            if(value != nullptr) {
                                asyncResp->res.jsonValue["Version"] = *value;
                            }
                        }
                    }
                },
            "xyz.openbmc_project.Ssdarray.Firmware", 
            "/xyz/openbmc_project/ssdarray/firmware/ready",
            "org.freedesktop.DBus.Properties", "GetAll",
            "xyz.openbmc_project.Ssdarray.Ready");
        }
    
    };
    
    class Update : public Node {
    public:
        
        Update(CrowApp& app) : Node(app, "/redfish/v1/Switch/FirmwareService/Update/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.Update"},
                {"@odata.id", "/redfish/v1/Switch/FirmwareService/Update"},
                {"@odata.type", "#Update.v1_1_0.Update"},
                {"Name", "Update Information"},
                {"Description", "Get Update Status"}
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<std::string,std::string>& 
                    propertiesList) {
                    if (ec) {
                        messages::internalError(asyncResp->res);
                        return;
                    }
                    BMCWEB_LOG_DEBUG << "Got " << propertiesList.size()
                            << "properties for FirmwareService Update";

                    for(const std::pair<std::string, std::string>& 
                            property : propertiesList) {
                        if(property.first == "Status") {
                            const std::string* value = (&property.second);
                                   //std::get_if<std::string>(&property.second);
                            if(value != nullptr){
                                asyncResp->res.jsonValue["Status"] = *value;
                            }
                        }
                        if(property.first == "Imageid") {
                            const std::string* value = (&property.second);
                                    //std::get_if<uint32_t>(&property.second);
                            if(value != nullptr){
                                asyncResp->res.jsonValue["Imageid"] = *value;
                            }
                        }
                    }
                },
            "xyz.openbmc_project.Ssdarray.Firmware", 
            "/xyz/openbmc_project/ssdarray/firmware/update",
            "org.freedesktop.DBus.Properties", "GetAll",
            "xyz.openbmc_project.Ssdarray.Update");
        }
        
        void doPatch(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {
            auto asyncResp = std::make_shared<AsyncResp>(res);            
            res.jsonValue = {
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.Update"},
                {"@odata.id", "/redfish/v1/Switch/FirmwareService/Update"},
                {"@odata.type", "#Update.v1_1_0.Update"},
                {"Name", "Update Information"},
                {"Description", "Put ImageId to Update"}
            };
//            if (params.size() != 1) {
//                messages::internalError(asyncResp->res);
//                return;
//            }           
//            const uint32_t& imageId = params[0];
            uint32_t imageId = 0;
            if (!json_util::readJson(req, res, "Value", imageId)) {
                return;
            }
            crow::connections::systemBus->async_method_call(
                    [this, asyncResp, imageId](
                    const boost::system::error_code ec, 
                    const std::vector<std::pair<std::string, uint32_t>>&
                    propertiesList) {
                if (ec) {
                    BMCWEB_LOG_ERROR << "D-Bus responses error: " << ec;
                    messages::internalError(asyncResp->res);
                    return;
                }
                for(const std::pair<std::string, uint32_t>&  
                        property : propertiesList) {
                    if(property.first == "Value") {
                        const uint32_t* value = (&property.second);
                                //std::get_if<std::string>(&property.second);
                        if(value != nullptr){
                            asyncResp->res.jsonValue["Value"] = *value;
                        }
                    }
                }
            },
            "xyz.openbmc_project.Ssdarray.Firmware", 
            "/xyz/openbmc_project/ssdarray/firmware/update",
            "org.freedesktop.DBus.Properties", "Set",
            "xyz.openbmc_project.Switch.Firmware.Update", 
            "Value", imageId);   ///std::variant<uint32_t>(*imageId)        
        }
        
    };
    
    
    class Activate : public Node {
    public:
        
        Activate(CrowApp& app) : Node(app, "/redfish/v1/Switch/FirmwareService/Activate/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.Activate"},
                {"@odata.id", "/redfish/v1/Switch/FirmwareService/Activate"},
                {"@odata.type", "#Activate.v1_1_0.Activate"},
                {"Name", "Activate Information"},
                {"Description", "Get Activate Information"}
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<std::string, std::string>>&
                    propertiesList) {
                    if (ec) {
                        messages::internalError(asyncResp->res);
                        return;
                    }
                    BMCWEB_LOG_DEBUG << "Got " << propertiesList.size()
                            << "properties for FirmwareService Activate";

                    for(const std::pair<std::string, std::string>& 
                            property : propertiesList) {
                        if(property.first == "Status") {
                            const std::string* value = (&property.second);
                                    //std::get_if<std::string>(&property.second);
                            if(value != nullptr){
                                asyncResp->res.jsonValue["Status"] = *value;
                            }
                        }
                    }
                },
            "xyz.openbmc_project.Ssdarray.Firmware", 
            "/xyz/openbmc_project/ssdarray/firmware/activate",
            "org.freedesktop.DBus.Properties", "GetAll",
            "xyz.openbmc_project.Ssdarray.Activate");
        }
        
        void doPatch(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {
            auto asyncResp = std::make_shared<AsyncResp>(res);            
            res.jsonValue = {
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.Activate"},
                {"@odata.id", "/redfish/v1/Switch/FirmwareService/Activate"},
                {"@odata.type", "#Activate.v1_1_0.Activate"},
                {"Name", "Activate Information"},
                {"Description", "Activate Information"}
            };
//            if (params.size() != 1) {
//                messages::internalError(asyncResp->res);
//                return;
//            }           
//            const uint32_t& imageId = params[0];
            uint32_t imageId = 0;
            if (!json_util::readJson(req, res, "Value", imageId)) {
                return;
            }
            crow::connections::systemBus->async_method_call(
                    [this, asyncResp, imageId](
                    const boost::system::error_code ec, 
                    const std::vector<std::pair<std::string, uint32_t>>&
                    propertiesList) {
                if (ec) {
                    BMCWEB_LOG_ERROR << "D-Bus responses error: " << ec;
                    messages::internalError(asyncResp->res);
                    return;
                }
                /*set value and function will return value*/
                for(const std::pair<std::string, uint32_t>& 
                        property : propertiesList) {
                    if(property.first == "Value") {
                        const uint32_t* value = (&property.second);
                                //std::get_if<uint32_t>(&property.second);
                        if(value != nullptr){
                            asyncResp->res.jsonValue["Value"] = *value;
                        }
                    }
                }
            },
            "xyz.openbmc_project.Ssdarray.Firmware", 
            "/xyz/openbmc_project/ssdarray/firmware/activate",
            "org.freedesktop.DBus.Properties", "Set",
            "xyz.openbmc_project.Ssdarray.Firmware.Activate", 
            "Value", imageId);           
        }
         
    };
    
}



#endif /* USI_FIRMWARE_HPP */

