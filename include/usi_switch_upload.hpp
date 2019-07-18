
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
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

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
                            {"description", "Upload image time out!"}
                        }},
                    {"message", "400 Bad Request"},
                    {"status", "error"}
                };
                res.end();
            };

            std::string filePath("/var/lib/obmc/usiSwitchImage.tar");
            std::string tmpDirPath("/var/lib/obmc/");
            struct stat statbuff;
            int status = 0;            
            struct dirent *dir;
            
            DIR *pdir = opendir(tmpDirPath.c_str());
            if(pdir == NULL) {
                BMCWEB_LOG_ERROR << "Opendir error!";
            }
            while((dir = readdir(pdir)) != NULL) {
                if(std::string(dir->d_name).find(".pmc") != std::string::npos) { /// *.pmc file exist
                    closedir(pdir);
                    res.jsonValue = {
                        {"data", nullptr},
                        {"message", "image already exist!"},
                        {"status", "error"}
                    };
                    res.end();
                    return;
                }                
            }
            
            ///file not exist, write file
            BMCWEB_LOG_DEBUG << "Writing file to " << filePath;
            std::ofstream out(filePath, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
            out << req.body;
            out.close();
            timeout.async_wait(timeoutHandler);
           
            /// judge file write sucess: file exist and size equal req.body, then untar to get *.pmc and remove *.tar 
            if((access(filePath.c_str(), F_OK) == 0) && (stat(filePath.c_str(), &statbuff) == 0) && 
               (statbuff.st_size == req.body.size())) {
                boost::system::error_code ec;
                timeout.cancel(ec);
                if (ec) {
                    BMCWEB_LOG_ERROR << "error canceling timer " << ec;
                }
                pid_t pid = fork();
                if(pid == 0) {       /// child process                        
                    execl("/bin/tar", "tar", "-xf", filePath.c_str(), "-C", tmpDirPath.c_str(), (char*)0);
                } else if(pid > 0) { /// parent process
                    waitpid(pid, &status, 0); /// wait until child process end
                    res.jsonValue = {
                        {"data", nullptr},
                        {"message", "200 OK"},
                        {"status", "ok"}
                    };
                    BMCWEB_LOG_DEBUG << "ending response";
                } else {      /// fork error
                    res.jsonValue = {
                        {"data", nullptr},
                        {"message", "untar image fail, please upload again!"},
                        {"status", "fail"}
                    };
                }

            } else {
                res.jsonValue = {
                    {"data", nullptr},
                    {"message", "Write image error!"},
                    {"status", "error"}
                };
            }

            FILE* fp = popen(("rm -rf " + filePath).c_str(), "r");
            pclose(fp);
            res.end();                 
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

