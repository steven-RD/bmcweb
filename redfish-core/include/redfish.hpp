/*
// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
 */
#pragma once

#include "../lib/account_service.hpp"
#include "../lib/chassis.hpp"
#include "../lib/cpudimm.hpp"
#include "../lib/ethernet.hpp"
#include "../lib/log_services.hpp"
#include "../lib/managers.hpp"
#include "../lib/network_protocol.hpp"
#include "../lib/power.hpp"
#include "../lib/redfish_sessions.hpp"
#include "../lib/roles.hpp"
#include "../lib/service_root.hpp"
#include "../lib/systems.hpp"
#include "../lib/thermal.hpp"
#include "../lib/update_service.hpp"
#include "../lib/usi_firmware.hpp"
#include "../lib/usi_control.hpp"
#include "../lib/usi_power_supply.hpp"
#include "../lib/usi_power_switch.hpp"
#include "../lib/usi_information.hpp"
#include "../lib/usi_switch_service.hpp"
#include "webserver_common.hpp"

namespace redfish {

    /*
     * @brief Top level class installing and providing Redfish services
     */
    class RedfishService {
    public:

        /*
         * @brief Redfish service constructor
         *
         * Loads Redfish configuration and installs schema resources
         *
         * @param[in] app   Crow app on which Redfish will initialize
         */
        RedfishService(CrowApp& app) {
            
            /*
             * Add USI redfish class modules 
             * author: USI Steven 
             * date: 20190527
             */
            nodes.emplace_back(std::make_unique<SwitchService>(app));
            nodes.emplace_back(std::make_unique<FirmwareService>(app));
            nodes.emplace_back(std::make_unique<Functional>(app));
            nodes.emplace_back(std::make_unique<Ready>(app));
            nodes.emplace_back(std::make_unique<Update>(app));         
            nodes.emplace_back(std::make_unique<Activate>(app));
            nodes.emplace_back(std::make_unique<Delete>(app));
            nodes.emplace_back(std::make_unique<ImageFile>(app));
            nodes.emplace_back(std::make_unique<Control>(app));
            nodes.emplace_back(std::make_unique<PowerSupply>(app));
            nodes.emplace_back(std::make_unique<PowerSwitch>(app));
            nodes.emplace_back(std::make_unique<InformationService>(app));   
            nodes.emplace_back(std::make_unique<BindInfo>(app));  
            nodes.emplace_back(std::make_unique<BindInfoTest>(app)); 
            nodes.emplace_back(std::make_unique<DspInfo>(app));  
            nodes.emplace_back(std::make_unique<SwitchInfo>(app)); 
            nodes.emplace_back(std::make_unique<CableInfo>(app));  
            nodes.emplace_back(std::make_unique<SsdInfo>(app)); 
            nodes.emplace_back(std::make_unique<PatopoInfo>(app)); 
            nodes.emplace_back(std::make_unique<AllInformations>(app));
            
            
            nodes.emplace_back(std::make_unique<AccountService>(app));
            nodes.emplace_back(std::make_unique<AccountsCollection>(app));
            nodes.emplace_back(std::make_unique<ManagerAccount>(app));
            nodes.emplace_back(std::make_unique<SessionCollection>(app));
            nodes.emplace_back(std::make_unique<Roles>(app));
            nodes.emplace_back(std::make_unique<RoleCollection>(app));
            nodes.emplace_back(std::make_unique<ServiceRoot>(app));
            nodes.emplace_back(std::make_unique<NetworkProtocol>(app));
            nodes.emplace_back(std::make_unique<SessionService>(app));
            nodes.emplace_back(std::make_unique<EthernetCollection>(app));
            nodes.emplace_back(std::make_unique<EthernetInterface>(app));
            nodes.emplace_back(std::make_unique<Thermal>(app));
            nodes.emplace_back(std::make_unique<ManagerCollection>(app));
            nodes.emplace_back(std::make_unique<Manager>(app));
            nodes.emplace_back(std::make_unique<ManagerActionsReset>(app));
            nodes.emplace_back(std::make_unique<Power>(app));
            nodes.emplace_back(std::make_unique<ChassisCollection>(app));
            nodes.emplace_back(std::make_unique<Chassis>(app));
            nodes.emplace_back(std::make_unique<UpdateService>(app));
            nodes.emplace_back(std::make_unique<SoftwareInventoryCollection>(app));
            nodes.emplace_back(std::make_unique<SoftwareInventory>(app));
            nodes.emplace_back(
                    std::make_unique<VlanNetworkInterfaceCollection>(app));
            nodes.emplace_back(std::make_unique<VlanNetworkInterface>(app));

            nodes.emplace_back(std::make_unique<SystemLogServiceCollection>(app));
            nodes.emplace_back(std::make_unique<EventLogService>(app));
            nodes.emplace_back(std::make_unique<EventLogEntryCollection>(app));
            nodes.emplace_back(std::make_unique<EventLogEntry>(app));

            nodes.emplace_back(std::make_unique<BMCLogServiceCollection>(app));
#ifdef BMCWEB_ENABLE_REDFISH_BMC_JOURNAL
            nodes.emplace_back(std::make_unique<BMCJournalLogService>(app));
            nodes.emplace_back(std::make_unique<BMCJournalLogEntryCollection>(app));
            nodes.emplace_back(std::make_unique<BMCJournalLogEntry>(app));
#endif

#ifdef BMCWEB_ENABLE_REDFISH_CPU_LOG
            nodes.emplace_back(std::make_unique<CPULogService>(app));
            nodes.emplace_back(std::make_unique<CPULogEntryCollection>(app));
            nodes.emplace_back(std::make_unique<CPULogEntry>(app));
            nodes.emplace_back(std::make_unique<OnDemandCPULog>(app));
#ifdef BMCWEB_ENABLE_REDFISH_RAW_PECI
            nodes.emplace_back(std::make_unique<SendRawPECI>(app));
#endif // BMCWEB_ENABLE_REDFISH_RAW_PECI
#endif // BMCWEB_ENABLE_REDFISH_CPU_LOG

            nodes.emplace_back(std::make_unique<ProcessorCollection>(app));
            nodes.emplace_back(std::make_unique<Processor>(app));
            nodes.emplace_back(std::make_unique<MemoryCollection>(app));
            nodes.emplace_back(std::make_unique<Memory>(app));

            nodes.emplace_back(std::make_unique<SystemsCollection>(app));
            nodes.emplace_back(std::make_unique<Systems>(app));
            nodes.emplace_back(std::make_unique<SystemActionsReset>(app));
#ifndef BMCWEB_ENABLE_REDFISH_DBUS_LOG_ENTRIES ///modify by USI Steven 20190716 ifdef->ifndef
            nodes.emplace_back(std::make_unique<DBusLogServiceActionsClear>(app));
#endif

            for (const auto& node : nodes) {
                node->initPrivileges();
            }
        }

    private:
        std::vector<std::unique_ptr<Node>> nodes;
    };

} // namespace redfish
