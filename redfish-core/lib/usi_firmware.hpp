
/* 
 * File:   usi_firmware.hpp
 * Author: Steven
 *
 * Date: 20190516
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
            
            asyncResp->res.jsonValue["@odata.context"] = "/redfish/v1/$metadata#USI.Switch.FirmwareService";
            asyncResp->res.jsonValue["@odata.id"] = "/redfish/v1/Switch/FirmwareService";
            asyncResp->res.jsonValue["@odata.type"] = "#FirmwareService.v1_1_0.FirmwareService";
            asyncResp->res.jsonValue["Id"] = "Firmware";
            asyncResp->res.jsonValue["Name"] = "FirmwareService Information";
            asyncResp->res.jsonValue["Description"] = "FirmwareService Information";
            asyncResp->res.jsonValue["Firmware"]["@odata.id1"] = "/redfish/v1/Switch/Functional";
            asyncResp->res.jsonValue["Firmware"]["@odata.id2"] = "/redfish/v1/Switch/Ready";
            asyncResp->res.jsonValue["Firmware"]["@odata.id3"] = "/redfish/v1/Switch/Update";
            asyncResp->res.jsonValue["Firmware"]["@odata.id4"] = "/redfish/v1/Switch/Activate";
            asyncResp->res.jsonValue["Firmware"]["@odata.id5"] = "/redfish/v1/Switch/ImageFile";
            asyncResp->res.jsonValue["Firmware"]["@odata.id6"] = "/redfish/v1/Switch/Delete";
        }

    };

    class Functional : public Node {
    public:

        Functional(CrowApp& app) : Node(app, "/redfish/v1/Switch/Functional/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.Functional"},
                {"@odata.id", "/redfish/v1/Switch/Functional"},
                {"@odata.type", "#Functional.v1_1_0.Functional"},
                {"Name", "Functional Information"},
                {"Description", "Get Functional Information"}
            };

            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<std::vector<std::pair<std::string, 
                            std::string>>>& property){
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got " 
                                << "properties for FirmwareService Functional";
                        
                        const std::vector<std::pair<std::string, std::string>> *value =
                                std::get_if<std::vector<std::pair<std::string, std::string>>>(&property);
                        
                        if(value != nullptr){
                            for(std::pair<std::string, std::string> p : *value) {
                                asyncResp->res.jsonValue["Version"][p.first] = p.second;
                            }
                            //asyncResp->res.jsonValue["Version"][(*value)[0].first] = (*value)[0].second;
                            //asyncResp->res.jsonValue["Version"][(*value)[1].first] = (*value)[1].second;
                        }
                    },
            "com.usi.Ssdarray.Firmware",
            "/xyz/openbmc_project/ssdarray/firmware/functional",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Functional", "Version");
        }

    };

    class Ready : public Node {
    public:

        Ready(CrowApp& app) : Node(app, "/redfish/v1/Switch/Ready/") {
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
                {"@odata.id", "/redfish/v1/Switch/Ready"},
                {"@odata.type", "#Ready.v1_1_0.Ready"},
                {"Name", "Ready Information"},
                {"Description", "Get Ready Information"}
            };

            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<std::string,
                    std::variant<std::string>>>& propertiesList) {
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got " << propertiesList.size()
                                << "properties for FirmwareService Ready";

                        for (const std::pair<std::string, std::variant < std::string>>&
                                property : propertiesList) {
                            if (property.first == "Type") {
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Type"] = *value;
                                }
                            }
                            if (property.first == "Version") {
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Version"] = *value;
                                }
                            }
                        }
                    },
            "com.usi.Ssdarray.Firmware",
            "/xyz/openbmc_project/ssdarray/firmware/ready",
            "org.freedesktop.DBus.Properties", "GetAll",
            "com.usi.Ssdarray.Ready");
        }

    };

    class Update : public Node {
    public:

        Update(CrowApp& app) : Node(app, "/redfish/v1/Switch/Update/") {
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
                {"@odata.id", "/redfish/v1/Managers/Switch/Update"},
                {"@odata.type", "#Update.v1_1_0.Update"},
                {"Name", "Update Information"},
                {"Description", "Get Update Information"}
            };

            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<std::string, 
                            std::variant<std::string, uint32_t>>>& propertiesList) {
                        
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got properties for Firmware Update";
                        
                        for (const std::pair<std::string, std::variant<std::string, uint32_t>>&
                                property : propertiesList) {
                            if (property.first == "Status") {
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Status"] = *value;
                                }
                            }
                            /*if (property.first == "Imageid") {
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Imageid"] = *value;
                                }
                            }*/
                            if (property.first == "Value") {
                                const uint32_t* value =
                                        std::get_if<uint32_t>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Value"] = *value;
                                }
                            }
                        }
                    },
            "com.usi.Ssdarray.Firmware",
            "/xyz/openbmc_project/ssdarray/firmware/update",
            "org.freedesktop.DBus.Properties", "GetAll",
            "com.usi.Ssdarray.Update");
        }
        
        void doPatch(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {            
            auto asyncResp = std::make_shared<AsyncResp>(res);
            
            std::optional<uint32_t> value;
            if (!json_util::readJson(req, res, "Value", value)) {
                return;
            }
            if (value) {
                crow::connections::systemBus->async_method_call(
                    [this, asyncResp, value](
                    const boost::system::error_code ec) {
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        messages::success(asyncResp->res);
                    },
                "com.usi.Ssdarray.Firmware",
                "/xyz/openbmc_project/ssdarray/firmware/update",
                "org.freedesktop.DBus.Properties", "Set",
                "com.usi.Ssdarray.Update", "Value", std::variant<uint32_t>(*value)); 
            }
            /*if(imageId) {
                crow::connections::systemBus->async_method_call(
                    [this, asyncResp, imageId](
                    const boost::system::error_code ec) {
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        messages::success(asyncResp->res);
                    },
                "com.usi.Ssdarray.Firmware",
                "/xyz/openbmc_project/ssdarray/firmware/update",
                "org.freedesktop.DBus.Properties", "Set",
                "com.usi.Ssdarray.Update", "Imageid", 
                std::variant<std::string>(*imageId)); 
            }*/
        }

    };
    
    
    class Activate : public Node {
    public:

        Activate(CrowApp& app) : Node(app, "/redfish/v1/Switch/Activate/") {
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
                {"@odata.id", "/redfish/v1/Switch/Activate"},
                {"@odata.type", "#Activate.v1_1_0.Activate"},
                {"Name", "Activate Information"},
                {"Description", "Get Activate Information"}
            };
            
            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<std::string,
                    std::variant < std::string, uint32_t>>>& propertiesList) {
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got " << propertiesList.size()
                                << "properties for Firmware Activate";

                        for (const std::pair<std::string, std::variant<std::string, uint32_t>>&
                                property : propertiesList) {
                            if (property.first == "Status") {
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Status"] = *value;
                                }
                            }
                            if (property.first == "Value") {
                                const uint32_t* value =
                                        std::get_if<uint32_t>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Value"] = *value;
                                }
                            }
                        }
                    },
            "com.usi.Ssdarray.Firmware",
            "/xyz/openbmc_project/ssdarray/firmware/activate",
            "org.freedesktop.DBus.Properties", "GetAll",
            "com.usi.Ssdarray.Activate");
        }
        
        void doPatch(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {           
            auto asyncResp = std::make_shared<AsyncResp>(res);
            
            std::optional<uint32_t> value;
            if (!json_util::readJson(req, res, "Value", value)) {
                return;
            }
            if(value) {
                crow::connections::systemBus->async_method_call(
                        [this, asyncResp, value](
                        const boost::system::error_code ec) {
                            if (ec) {
                                messages::internalError(asyncResp->res);
                                return;
                            }
                            messages::success(asyncResp->res);
                        },
                "com.usi.Ssdarray.Firmware",
                "/xyz/openbmc_project/ssdarray/firmware/activate",
                "org.freedesktop.DBus.Properties", "Set",
                "com.usi.Ssdarray.Activate", "Value", std::variant<uint32_t>(*value));
            }
        }

    };
    
    
    class Delete : public Node {
    public:

        Delete(CrowApp& app) : Node(app, "/redfish/v1/Switch/Delete/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.Delete"},
                {"@odata.id", "/redfish/v1/Switch/Delete"},
                {"@odata.type", "#Delete.v1_1_0.Delete"},
                {"Name", "Delete Information"},
                {"Description", "Get Delete Information"}
            };
            
            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::vector<std::pair<std::string,
                    std::variant<std::string, uint32_t>>>& propertiesList) {
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got " << propertiesList.size()
                                << "properties for FirmwareService Delete";

                        for (const std::pair<std::string, std::variant<std::string, uint32_t>>&
                                property : propertiesList) {
                            if (property.first == "Status") {
                                const std::string* value =
                                        std::get_if<std::string>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Status"] = *value;
                                }
                            }
                            if (property.first == "Value") {
                                const uint32_t* value =
                                        std::get_if<uint32_t>(&property.second);
                                if (value != nullptr) {
                                    asyncResp->res.jsonValue["Value"] = *value;
                                }
                            }
                        }
                    },
            "com.usi.Ssdarray.Firmware",
            "/xyz/openbmc_project/ssdarray/firmware/delete",
            "org.freedesktop.DBus.Properties", "GetAll",
            "com.usi.Ssdarray.Delete");
        }
        
        void doPatch(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {           
            auto asyncResp = std::make_shared<AsyncResp>(res);
            
            std::optional<uint32_t> value;
            if (!json_util::readJson(req, res, "Value", value)) {
                return;
            }
            if(value) {
                crow::connections::systemBus->async_method_call(
                        [this, asyncResp, value](
                        const boost::system::error_code ec) {
                            if (ec) {
                                messages::internalError(asyncResp->res);
                                return;
                            }
                            messages::success(asyncResp->res);
                        },
                "com.usi.Ssdarray.Firmware",
                "/xyz/openbmc_project/ssdarray/firmware/delete",
                "org.freedesktop.DBus.Properties", "Set",
                "com.usi.Ssdarray.Delete", "Value", std::variant<uint32_t>(*value));
            }
        }

    };
    
    class ImageFile : public Node {        
    public:
        
        ImageFile(CrowApp& app) : Node(app, "/redfish/v1/Switch/ImageFile/") {
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
                {"@odata.context", "/redfish/v1/$metadata#USI.Switch.FirmwareService.ImageFile"},
                {"@odata.id", "/redfish/v1/Switch/ImageFile"},
                {"@odata.type", "#ImageFile.v1_1_0.ImageFile"},
                {"Name", "ImageFile Information"},
                {"Description", "Get ImageFile Information"}
            };
            
            crow::connections::systemBus->async_method_call(
                    [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<std::vector<std::pair<std::string, std::string>>>& property){
                        if (ec) {
                            messages::internalError(asyncResp->res);
                            return;
                        }
                        BMCWEB_LOG_DEBUG << "Got " 
                                << "properties for FirmwareService ImageFile";
                        
                        const std::vector<std::pair<std::string, std::string>> *value =
                                std::get_if<std::vector<std::pair<std::string, std::string>>>(&property);
                        
                        if(value != nullptr){
                            for(std::pair<std::string, std::string> p : *value) {
                                asyncResp->res.jsonValue["Status"][p.first] = p.second;
                            }
                        }
                    },
            "com.usi.Ssdarray.Firmware",
            "/xyz/openbmc_project/ssdarray/firmware/imagefile",
            "org.freedesktop.DBus.Properties", "Get",
            "com.usi.Ssdarray.Imagefile", "Status");
        }
        
    };
    
}



#endif /* USI_FIRMWARE_HPP */

