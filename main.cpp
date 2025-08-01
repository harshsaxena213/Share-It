#include <crow.h>

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