#include <crow.h>
#include "include/register.h"
#include "include/login.h"
#include <crow/middlewares/session.h>
#include "include/download.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "include/upload.h"
#include "include/files.h"
#include "include/delete.h"

using Session = crow::SessionMiddleware<crow::InMemoryStore>;

int main()
{
    crow::App<crow::CookieParser, Session> app;

    CROW_ROUTE(app, "/")([]()
                         {
        auto load_page=crow::mustache::load("index.html");
        return load_page.render(); });

    CROW_ROUTE(app, "/login")([]()
                              {
        auto load_page=crow::mustache::load("login.html");
        return load_page.render(); });

    CROW_ROUTE(app, "/login_data").methods(crow::HTTPMethod::POST)([&app](crow::request &req, crow::response &res)
                                                                   {
        auto parameters=req.get_body_params();
        std::string username=parameters.get("username");
        std::string password=parameters.get("password");
        auto& session = app.get_context<Session>(req);
        bool isLoged=login(username,password);
        if(isLoged){
            session.set("logged_in", true);
            session.set("username", username);
            res.code = 302;
            res.set_header("Location", "/upload");
            res.end();
        
        } });

    CROW_ROUTE(app, "/register")([]()
                                 {
        auto load_page=crow::mustache::load("register.html");
        return load_page.render(); });

    CROW_ROUTE(app, "/register_data").methods(crow::HTTPMethod::POST)([](crow::request &req, crow::response &res)
                                                                      {
                                                                          auto parameters = req.get_body_params();
                                                                          auto load_page = crow::mustache::load("confirmation.html");
                                                                          auto username = parameters.get("username");
                                                                          auto password = parameters.get("password");
                                                                          bool isRegister = Register(username, password);
                                                                          if (isRegister)
                                                                          {
                                            
                                                                                
                                                                                res.code = 302;
                                                                                res.set_header("Location", "/login");
                                                                                res.end();
                                                                          }
                                                                          else
                                                                          {
                                                                              res.code = 404;
                                                                              res.body = "Wrong Password";
                                                                              res.end();
                                                                          } });

    CROW_ROUTE(app, "/upload")([&app](crow::request &req, crow::response &res)
                               {
        auto& session = app.get_context<Session>(req);
        bool logged_in = session.get("logged_in", false);
        if(logged_in){
                auto load_page=crow::mustache::load("upload.html");
                std::string page_html = load_page.render().dump();
                res.write(page_html);
                res.end();
        }
        else{
        res.code = 302;
        res.set_header("Location", "/login");
        res.end();
        } });

    CROW_ROUTE(app, "/download")([&app](crow::request &req, crow::response &res)
                                 {
    auto& session = app.get_context<Session>(req);
    bool logged_in = session.get("logged_in", false);
    if(!logged_in){
            res.code = 302;
            res.set_header("Location", "/login");
            res.end();  
    }          
     
    auto load_page=crow::mustache::load("download.html");
    std::string page_html = load_page.render().dump();
    res.write(page_html);
    res.end();
 });

    CROW_ROUTE(app, "/files")([&app](crow::request &req, crow::response &res)
                              {
    auto& session = app.get_context<Session>(req);
    bool logged_in = session.get("logged_in", false);
    std::string username = session.get("username", "guest");
    
    if (!logged_in || username == "guest") {
            res.code = 302;
            res.set_header("Location", "/login");
            res.end();
    }
    else {
        
        auto files_vector = ListFiles(username);
        
        
        crow::mustache::context ctx;
        ctx["files"] = std::move(files_vector);
        
        auto html = crow::mustache::load("files.html").render(ctx).dump();
        res.set_header("Content-Type", "text/html");
        res.write(html);
        res.end();
        return;
    } });

    CROW_ROUTE(app, "/upload_data").methods(crow::HTTPMethod::POST)([&app](crow::request &req, crow::response &res)
                                                                    {
   
    auto& session = app.get_context<Session>(req);
    bool logged_in = session.get("logged_in", false);
    
    if (!logged_in) {
        crow::mustache::context ctx;
        ctx["status"] = "Login Please!";
        auto load_page = crow::mustache::load("confirmation.html");
        std::string page_html = load_page.render(ctx).dump();

        res.set_header("Content-Type", "text/html");
        res.write(page_html);
        res.end();
        return;
    }
    
    
    std::string filename = req.get_header_value("X-Filename");
    std::string username = session.get("username","guest");
    if(username=="guest"){
        res.code=400;
        res.write("Invalid Username Please Login Again With Your Details");
        res.end();
        return;
    }
    filename_to_db(username,filename);
    if (filename.empty()) {
        res.code = 400;
        res.write("Missing X-Filename header!");
        res.end();
        return;
    }

    std::ofstream outfile("uploads/" + filename, std::ios::binary);
    if (!outfile.is_open()) {
        res.code = 500;
        res.write("Failed to open file for writing");
        res.end();
        return;
    }

    outfile.write(req.body.c_str(), req.body.size());
    outfile.close();

    std::cout << "File saved successfully to uploads/" << filename << std::endl;

    res.code = 200;
    res.write("File uploaded successfully");
    res.end(); });

    CROW_ROUTE(app, "/download_data").methods(crow::HTTPMethod::POST)([&app](crow::request &req, crow::response &res)
                                                                      {
                                                                          auto parameters = req.get_body_params();
                                                                          std::string fileid_str = parameters.get("fileid");
                                                                          int fileid = 0;
                                                                          try
                                                                          {
                                                                              fileid = std::stoi(fileid_str);
                                                                          }
                                                                          catch (...)
                                                                          {
                                                                              res.code = 400;
                                                                              res.write("Invalid file ID");
                                                                              res.end();
                                                                              return;
                                                                          }
                                                                          std::string filename = fileid_to_filename(fileid);
                                                                          if (filename.empty())
                                                                          {
                                                                              res.code = 404;
                                                                              res.write("File not found");
                                                                              res.end();
                                                                              return;
                                                                          }
                                                                          std::string filepath = "uploads/" + filename;
                                                                          if (!std::filesystem::exists(filepath))
                                                                          {
                                                                              res.code = 404;
                                                                              res.write("File Not Found");
                                                                              res.end();
                                                                              return;
                                                                          }
                                                                          std::ifstream file_stream(filepath, std::ios::binary);
                                                                          if (!file_stream)
                                                                          {
                                                                              res.code = 500;
                                                                              res.write("Failed to open file");
                                                                              res.end();
                                                                              return;
                                                                          }
                                                                          std::ostringstream oss;
                                                                          oss << file_stream.rdbuf();
                                                                          std::string file_content = oss.str();
                                                                          res.set_header("Content-Disposition", "attachment; filename=\"" + filename + "\"");
                                                                          res.set_header("Content-Type", "application/octet-stream");
                                                                          res.set_header("Content-Length", std::to_string(file_content.size()));

                                                                          res.write(file_content);
                                                                          res.end(); });

    CROW_ROUTE(app,"/delete")([&app](crow::request& req,crow::response& res){
        auto& session = app.get_context<Session>(req);
        bool logged_in = session.get("logged_in", false);
        if(logged_in){
                auto load_page=crow::mustache::load("delete.html");
                std::string page_html = load_page.render().dump();
                res.write(page_html);
                res.end();
        }
        else{
            res.code=302;
            res.set_header("Location", "/login");
            res.end();
        }
    });              

    CROW_ROUTE(app,"/delete_data").methods(crow::HTTPMethod::POST)([](crow::request& req,crow::response& res){
            auto parameters=req.get_body_params();
            std::string fileid_str_delete=parameters.get("fileid");
            int fileid = 0;                                                           
            int fileid_delete = std::stoi(fileid_str_delete);                                                              
            std::string file_name=delete_file(fileid_delete);
            if(!file_name.empty()){
                    std::string filepath = "./uploads/" + file_name;
                    if (std::remove(filepath.c_str()) != 0) {
                        if (std::remove(filepath.c_str()) != 0) {
                                CROW_LOG_INFO << "Failed to delete the file from filesystem: " << filepath 
                                << ", reason: " << std::strerror(errno);
}
                    CROW_LOG_INFO << "Failed to delete the file from filesystem: " << filepath;
    }
                res.code=200;
                res.write("File Deleted successfully");
                res.end(); 
            }
            else{
                res.code=404;
                res.write("No File For That File Id!");
                res.end();
            }

        
    });  
    app.port(8080).multithreaded().run();
}                                                                              
