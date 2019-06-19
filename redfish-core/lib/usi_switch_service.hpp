
/* 
 * File:   usi_switch.hpp
 * Author: Steven
 *
 * Created 20190613
 */

#ifndef USI_SWITCH_SERVICE_HPP
#define USI_SWITCH_SERVICE_HPP

#include "node.hpp"

#include <systemd/sd-id128.h>

namespace redfish
{

class SwitchService : public Node {
  public:
    SwitchService(CrowApp& app) : Node(app, "/redfish/v1/Switch/")
    {
        entityPrivileges = {
            {boost::beast::http::verb::get, {{"Login"}}},
            {boost::beast::http::verb::head, {{"Login"}}},
            {boost::beast::http::verb::patch, {{"ConfigureManager"}}},
            {boost::beast::http::verb::put, {{"ConfigureManager"}}},
            {boost::beast::http::verb::delete_, {{"ConfigureManager"}}},
            {boost::beast::http::verb::post, {{"ConfigureManager"}}}};
    }

  private:
    void doGet(crow::Response& res, const crow::Request& req,
                const std::vector<std::string>& params) override {
            auto asyncResp = std::make_shared<AsyncResp>(res);
            res.jsonValue = {
                {"@odata.context", "/redfish/v1/"
                    "$metadata#Switch.Switch"},
                {"@odata.id", "/redfish/v1/Switch"},
                {"@odata.type", "#Switch.v1_1_0.Switch"},
                {"Id", "Switch"},
                {"Name", "Switch Service"},
                {"Description", "Switch Service"},
                {"ServiceEnabled", true},
                {"AllInformations",
                    {
                        {"@odata.id", "/redfish/v1/Switch/AllInformations"}
                    }},
                {"BindInfo",
                    {
                        {"@odata.id", "/redfish/v1/Switch/BindInfo"}
                    }},
                {"DspInfo",
                    {
                        {"@odata.id", "/redfish/v1/Switch/DspInfo"}
                    }},    
                {"SwitchInfo",
                    {
                        {"@odata.id", "/redfish/v1/Switch/SwitchInfo"}
                    }}, 
                {"CableInfo",
                    {
                        {"@odata.id", "/redfish/v1/Switch/CableInfo"}
                    }},
                {"SsdInfo",
                    {
                        {"@odata.id", "/redfish/v1/Switch/SsdInfo"}
                    }},
                {"PatopoInfo",
                    {
                        {"@odata.id", "/redfish/v1/Switch/PatopoInfo"}
                    }},
                
                {"PowerSupply",
                    {
                        {"@odata.id", "/redfish/v1/Switch/PowerSupply"}
                    }},    
                {"PowerSwitch",
                    {
                        {"@odata.id", "/redfish/v1/Switch/PowerSwitch"}
                    }},
                    
                {"Control",
                    {
                        {"@odata.id", "/redfish/v1/Switch/Control"}
                    }},
                {"Functional",
                    {
                        {"@odata.id", "/redfish/v1/Switch/Functional"}
                    }},
                {"Ready",
                    {
                        {"@odata.id", "/redfish/v1/Switch/Ready"}
                    }},
                {"Update",
                    {
                        {"@odata.id", "/redfish/v1/Switch/Update"}
                    }},
                {"Activate",
                    {
                        {"@odata.id", "/redfish/v1/Switch/Activate"}
                    }},
                  
                {"FirmwareService",
                    {
                        {"@odata.id", "/redfish/v1/Switch/FirmwareService"}
                    }}
            };
    }
    
};

} // namespace redfish

#endif /* USI_SWITCH_SERVICE_HPP */

