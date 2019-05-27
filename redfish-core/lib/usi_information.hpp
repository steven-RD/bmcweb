
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
    
    class InformationService : public Node {
    public:

        InformationService(CrowApp& app) : Node(app, "/redfish/v1/Switch/InformationService/") {
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
            
            asyncResp->res.jsonValue["@odata.context"] = "/redfish/v1/$metadata#USI.Switch.InformationService";
            asyncResp->res.jsonValue["@odata.id"] = "/redfish/v1/Switch/InformationService";
            asyncResp->res.jsonValue["@odata.type"] = "#InformationService.v1_1_0.InformationService";
            asyncResp->res.jsonValue["Id"] = "InformationService";
            asyncResp->res.jsonValue["Name"] = "InformationService Information";
            asyncResp->res.jsonValue["Description"] = "InformationService Information";
            asyncResp->res.jsonValue["Firmware"]["@odata.id1"] = "/redfish/v1/Switch/AllInformations";
            asyncResp->res.jsonValue["Firmware"]["@odata.id2"] = "/redfish/v1/Switch/BindInfo";
            asyncResp->res.jsonValue["Firmware"]["@odata.id3"] = "/redfish/v1/Switch/DspInfo";
            asyncResp->res.jsonValue["Firmware"]["@odata.id4"] = "/redfish/v1/Switch/SwitchInfo";
            asyncResp->res.jsonValue["Firmware"]["@odata.id5"] = "/redfish/v1/Switch/CableInfo";
            asyncResp->res.jsonValue["Firmware"]["@odata.id6"] = "/redfish/v1/Switch/SsdInfo";
            asyncResp->res.jsonValue["Firmware"]["@odata.id7"] = "/redfish/v1/Switch/PatopoInfo";
        }
    };
    
    class AllInformations : public Node {
    public:
        
        AllInformations(CrowApp& app) : Node(app, "/redfish/v1/Switch/AllInformations/") {
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
                            const DicStrType* infos =
                                    std::get_if<DicStrType>(&property.second);
                            if (infos != nullptr) {
                                for(const std::pair<std::string, std::string>& info : *infos) {
                                    asyncResp->res.jsonValue["Info"][property.first][info.first] = info.second;
                                } 
                            } 
                        }
                        if(property.first == "Dspinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///DspInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrType* infos =
                                    std::get_if<DicStrType>(&property.second);
                            if (infos != nullptr) {
                                for(const std::pair<std::string, std::string>& info : *infos) {
                                    asyncResp->res.jsonValue["Info"][property.first][info.first] = info.second;
                                } 
                            } 
                        }
                        if(property.first == "Swinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///SwInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrType* infos =
                                    std::get_if<DicStrType>(&property.second);
                            if (infos != nullptr) {
                                for(const std::pair<std::string, std::string>& info : *infos) {
                                    asyncResp->res.jsonValue["Info"][property.first][info.first] = info.second;
                                } 
                            } 
                        }
                        if(property.first == "Cableinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///CableInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrDicType* cables =
                                    std::get_if<DicStrDicType>(&property.second);
                            if (cables != nullptr) {
                                for(const std::pair<std::string, DicStrType>& cable : *cables) {
                                    //asyncResp->res.jsonValue["Info"][property.first][cable.first] = cable.second;
                                    for(const std::pair<std::string, std::string>& info : cable.second) {
                                        asyncResp->res.jsonValue["Info"][property.first][cable.first][info.first] = info.second;
                                    } 
                                }
                            } 
                        }
                        if(property.first == "Ssdinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///SsdInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrDicType* ssds =
                                    std::get_if<DicStrDicType>(&property.second);
                            if (ssds != nullptr) {
                                for(const std::pair<std::string, DicStrType>& ssd : *ssds) {
                                    for(const std::pair<std::string, std::string>& info : ssd.second) {
                                        asyncResp->res.jsonValue["Info"][property.first][ssd.first][info.first] = info.second;
                                    } 
                                }
                            } 
                        }
                        if(property.first == "Patopoinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///PatopoInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrDicType* patops =
                                    std::get_if<DicStrDicType>(&property.second);
                            if (patops != nullptr) {
                                for(const std::pair<std::string, DicStrType>& patop : *patops) {
                                    for(const std::pair<std::string, std::string>& info : patop.second) {
                                        asyncResp->res.jsonValue["Info"][property.first][patop.first][info.first] = info.second;
                                    } 
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
    };
    
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
                            const DicStrType* infos =
                                    std::get_if<DicStrType>(&property.second);
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
    };
    
    class DspInfo : public Node {
    public:
        
        DspInfo(CrowApp& app) : Node(app, "/redfish/v1/Switch/DspInfo/") {
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
                {"@odata.context", "/redfish/v1/$metadata#Switch.DspInfo"},
                {"@odata.id", "/redfish/v1/Switch/DspInfo"},
                {"@odata.type", "#Information.v1_1_0.DspInfo"},
                {"Id", "DspInfo"},
                {"Name", "USI Info Information"},
                {"Description", "DspInfo Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<InfoType>& propertiesList){
                
                if (ec) {
                    messages::internalError(asyncResp->res);
                    return;
                }
                BMCWEB_LOG_DEBUG << "Got property for USI DspInfo";
                const InfoType *value = 
                            std::get_if<InfoType>(&propertiesList);
                if(value != nullptr) {
                    for(const InfoTypeP& property : *value) {
                        if(property.first == "Dspinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///DspInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrType* infos =
                                    std::get_if<DicStrType>(&property.second);
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
    };
    
    class SwitchInfo : public Node {
    public:
        
        SwitchInfo(CrowApp& app) : Node(app, "/redfish/v1/Switch/SwitchInfo/") {
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
                {"@odata.context", "/redfish/v1/$metadata#Switch.SwitchInfo"},
                {"@odata.id", "/redfish/v1/Switch/SwitchInfo"},
                {"@odata.type", "#Information.v1_1_0.SwitchInfo"},
                {"Id", "SwitchInfo"},
                {"Name", "USI Info Information"},
                {"Description", "SwitchInfo Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<InfoType>& propertiesList){
                
                if (ec) {
                    messages::internalError(asyncResp->res);
                    return;
                }
                BMCWEB_LOG_DEBUG << "Got property for USI DspInfo";
                const InfoType *value = 
                            std::get_if<InfoType>(&propertiesList);
                if(value != nullptr) {
                    for(const InfoTypeP& property : *value) {
                        if(property.first == "Swinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///SwInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrType* infos =
                                    std::get_if<DicStrType>(&property.second);
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
    };
    
    class CableInfo : public Node {
    public:
        
        CableInfo(CrowApp& app) : Node(app, "/redfish/v1/Switch/CableInfo/") {
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
                {"@odata.context", "/redfish/v1/$metadata#Switch.CableInfo"},
                {"@odata.id", "/redfish/v1/Switch/CableInfo"},
                {"@odata.type", "#Information.v1_1_0.CableInfo"},
                {"Id", "CableInfo"},
                {"Name", "USI Info Information"},
                {"Description", "CableInfo Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<InfoType>& propertiesList){
                
                if (ec) {
                    messages::internalError(asyncResp->res);
                    return;
                }
                BMCWEB_LOG_DEBUG << "Got property for USI CableInfo";
                const InfoType *value = 
                            std::get_if<InfoType>(&propertiesList);
                if(value != nullptr) {
                    for(const InfoTypeP& property : *value) {
                        if(property.first == "Cableinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///CableInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrDicType* cables =
                                    std::get_if<DicStrDicType>(&property.second);
                            if (cables != nullptr) {
                                for(const std::pair<std::string, DicStrType>& cable : *cables) {
                                    //asyncResp->res.jsonValue["Info"][property.first][cable.first] = cable.second;
                                    for(const std::pair<std::string, std::string>& info : cable.second) {
                                        asyncResp->res.jsonValue["Info"][property.first][cable.first][info.first] = info.second;
                                    } 
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
    };
    
    class SsdInfo : public Node {
    public:
        
        SsdInfo(CrowApp& app) : Node(app, "/redfish/v1/Switch/SsdInfo/") {
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
                {"@odata.context", "/redfish/v1/$metadata#Switch.SsdInfo"},
                {"@odata.id", "/redfish/v1/Switch/SsdInfo"},
                {"@odata.type", "#Information.v1_1_0.SsdInfo"},
                {"Id", "SsdInfo"},
                {"Name", "USI Info Information"},
                {"Description", "SsdInfo Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<InfoType>& propertiesList){
                
                if (ec) {
                    messages::internalError(asyncResp->res);
                    return;
                }
                BMCWEB_LOG_DEBUG << "Got property for USI SsdInfo";
                const InfoType *value = 
                            std::get_if<InfoType>(&propertiesList);
                if(value != nullptr) {
                    for(const InfoTypeP& property : *value) {
                        if(property.first == "Ssdinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///SsdInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrDicType* ssds =
                                    std::get_if<DicStrDicType>(&property.second);
                            if (ssds != nullptr) {
                                for(const std::pair<std::string, DicStrType>& ssd : *ssds) {
                                    for(const std::pair<std::string, std::string>& info : ssd.second) {
                                        asyncResp->res.jsonValue["Info"][property.first][ssd.first][info.first] = info.second;
                                    } 
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
    };
    
    class PatopoInfo : public Node {
    public:
        
        PatopoInfo(CrowApp& app) : Node(app, "/redfish/v1/Switch/PatopoInfo/") {
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
                {"@odata.context", "/redfish/v1/$metadata#Switch.PatopoInfo"},
                {"@odata.id", "/redfish/v1/Switch/PatopoInfo"},
                {"@odata.type", "#Information.v1_1_0.PatopoInfo"},
                {"Id", "PatopoInfo"},
                {"Name", "USI Info Information"},
                {"Description", "PatopoInfo Information"},               
            };
            
            crow::connections::systemBus->async_method_call(
            [asyncResp](
                    const boost::system::error_code ec,
                    const std::variant<InfoType>& propertiesList){
                
                if (ec) {
                    messages::internalError(asyncResp->res);
                    return;
                }
                BMCWEB_LOG_DEBUG << "Got property for USI SsdInfo";
                const InfoType *value = 
                            std::get_if<InfoType>(&propertiesList);
                if(value != nullptr) {
                    for(const InfoTypeP& property : *value) {
                        if(property.first == "Patopoinfo") {
                            const std::string* none =
                                    std::get_if<std::string>(&property.second); ///PatopoInfo : None
                            if (none != nullptr) {
                                asyncResp->res.jsonValue["Info"][property.first] = *none;
                            }
                            const DicStrDicType* patops =
                                    std::get_if<DicStrDicType>(&property.second);
                            if (patops != nullptr) {
                                for(const std::pair<std::string, DicStrType>& patop : *patops) {
                                    for(const std::pair<std::string, std::string>& info : patop.second) {
                                        asyncResp->res.jsonValue["Info"][property.first][patop.first][info.first] = info.second;
                                    } 
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
    };
    
}

#endif /* USI_INFORMATION_HPP */




