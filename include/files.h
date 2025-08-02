#include <crow.h>
#include <sqlite3.h>
#include <random>
#include <string>
#include <iostream>
#include <openssl/sha.h>

std::vector<crow::mustache::context> ListFiles(std::string username)
{
    sqlite3 *db;
    crow::mustache::context ctx;
    crow::json::wvalue result;
    int exit = sqlite3_open("file.sqlite", &db);
    if (exit != SQLITE_OK)
    {
        CROW_LOG_INFO << "Error WHile Opening The DataBase";
    }
    const char *query = "SELECT filename FROM files WHERE username=?";
    sqlite3_stmt *final_query = nullptr;
    exit = sqlite3_prepare_v2(db, query, -1, &final_query, nullptr);
    if (exit != SQLITE_OK)
    {
        CROW_LOG_INFO << "Error WHile Preapering The Statement";
    }
    
    exit = sqlite3_bind_text(final_query, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    std::vector<crow::mustache::context> files_vector;

    while (sqlite3_step(final_query)==SQLITE_ROW) {
        crow::mustache::context file_ctx;
        int id = sqlite3_column_int(final_query, 0);
        const unsigned char* fname = sqlite3_column_text(final_query, 1);

        file_ctx["id"] = std::to_string(id);
        file_ctx["filename"] = fname ? reinterpret_cast<const char*>(fname) : "";

        files_vector.push_back(file_ctx);
    }

    sqlite3_finalize(final_query);
    sqlite3_close(db);

    result["files"] = std::move(files_vector);  
    return files_vector;
}




int main() {
    std::vector<crow::mustache::context> numbers = ListFiles("test");
    print_vector(numbers);
    return 0;
}