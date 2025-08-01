#include <crow.h>
#include "include/login.h"

int main(){
    crow::SimpleApp app;

    CROW_ROUTE(app,"/")([](){
        auto load_page=crow::mustache::load("index.html");
        return load_page.render();
    });

    CROW_ROUTE(app,"/login")([](){
        auto load_page=crow::mustache::load("login.html");
        return load_page.render();
    });

    CROW_ROUTE(app,"/register")([](){
        auto load_page=crow::mustache::load("register.html");
        return load_page.render();
    });

    CROW_ROUTE(app,"/register_data").methods(crow::HTTPMethod::POST)([](crow::request& req,crow::response& res){
        auto parameters=req.get_body_params();
        auto username=parameters.get("username");
        auto password=parameters.get("password");
        bool status=authentication(username,password);
        if(status){
                    auto load_page=crow::mustache::load("confirmation.html");
                    crow::mustache::context ctx;
                    ctx={{"status","Registered!"}};
                    std::string page_html = load_page.render(ctx).dump();
                    res.set_header("Content-Type", "text/html");
                    res.write(page_html);
                    res.end();
        }
        else{
                    res.code=404;
                    res.body="Wrong Password";
                    res.end();
        }

    });

    CROW_ROUTE(app,"/upload")([](){
        auto load_page=crow::mustache::load("upload.html");
        return load_page.render();
    });

    CROW_ROUTE(app,"/download")([](){
        auto load_page=crow::mustache::load("download.html");
        return load_page.render();
    });

    CROW_ROUTE(app,"/files")([](){
        auto load_page=crow::mustache::load("index.html");
        return load_page.render();
    });

    app.port(8080).multithreaded().run();
}