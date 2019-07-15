
/* 
 * File:   usi_switch_upload.hpp
 * Author: Steven
 *
 * Created 20190708
 */


#ifndef USI_SWITCH_UPLOAD_HPP
#define USI_SWITCH_UPLOAD_HPP


#include <crow/app.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cstdio>
#include <dbus_singleton.hpp>
#include <fstream>
#include <memory>
#include <unistd.h>

namespace crow {
    namespace usi_switch_upload {


        inline void uploadImageHandler(const crow::Request& req, crow::Response& res,
                const std::string& filename) {
            
            static boost::asio::deadline_timer timeout(*req.ioService,
                    boost::posix_time::seconds(5));

            timeout.expires_from_now(boost::posix_time::seconds(15));

            auto timeoutHandler = [&res](const boost::system::error_code & ec) {
                if (ec == asio::error::operation_aborted) {
                    // expected, we were canceled before the timer completed.
                    return;
                }
                BMCWEB_LOG_ERROR << "Timed out waiting for Version interface";

                if (ec) {
                    BMCWEB_LOG_ERROR << "Async_wait failed " << ec;
                    return;
                }

                res.result(boost::beast::http::status::bad_request);
                res.jsonValue = {
                    {"data",
                        {
                            {"description",
                                "Version already exists or failed to be extracted"}
                        }},
                    {"message", "400 Bad Request"},
                    {"status", "error"}
                };
                res.end();
            };

            std::string filepath( "/var/lib/obmc/usi_cfg_01_13_1p_s0_x16_m_u2.pmc");           
            if(access(filepath.c_str(), F_OK) != 0) {
                BMCWEB_LOG_DEBUG << "Writing file to " << filepath;
                std::ofstream out(filepath, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
                out << req.body;
                out.close();
                timeout.async_wait(timeoutHandler);
                if(access(filepath.c_str(), F_OK) == 0) {
                    res.jsonValue = {
                        {"data", nullptr},
                        {"message", "200 OK"},
                        {"status", "ok"}
                    };
                    BMCWEB_LOG_DEBUG << "ending response";
                    res.end();
                } else {
                    res.jsonValue = {
                        {"data", nullptr},
                        {"message", "Write image error!"},
                        {"status", "error"}
                    };
                    res.end();
                }
            } else {
                res.jsonValue = {
                    {"data", nullptr},
                    {"message", "image already exists!"},
                    {"status", "error"}
                };
                res.end();
            }
        }

        template <typename... Middlewares> void requestRoutes(Crow<Middlewares...>& app) {
            BMCWEB_ROUTE(app, "/upload/switchImage/<str>")
                    .methods("POST"_method,"PUT"_method)(
                    [](const crow::Request& req, crow::Response& res,
                    const std::string & filename) {
                        uploadImageHandler(req, res, filename);
                    });

            BMCWEB_ROUTE(app, "/upload/switchImage")
                    .methods("POST"_method, "PUT"_method)(
                    [](const crow::Request& req, crow::Response & res) {
                        uploadImageHandler(req, res, "");
                    });
        }
    } // namespace usi_switch_upload
} // namespace crow

#endif /* USI_SWITCH_UPLOAD_HPP */

