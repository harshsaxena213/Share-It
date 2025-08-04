#include<crow.h>
#include <sqlite3.h>


std::string delete_file(int fileid){
    sqlite3* db;
    int exit=sqlite3_open("file.sqlite",&db);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error While Opening!";
    }
    const char* query="SELECT filename FROM files WHERE id=?;";
    sqlite3_stmt* final_query=nullptr;
    exit = sqlite3_prepare_v2(db, query, -1, &final_query, nullptr);
    if (exit != SQLITE_OK)
    {
        CROW_LOG_INFO << "Error While Preparing The Statement";
        sqlite3_finalize(final_query);
        sqlite3_close(db);
        return {};
    }
    exit = sqlite3_bind_int(final_query, 1, fileid);
    // CROW_LOG_INFO<<fileid;
    if (exit != SQLITE_OK)
    {
        CROW_LOG_INFO << "Error While Binding Parameter";
        sqlite3_finalize(final_query);
        sqlite3_close(db);
        return {};
    }
    std::string filename;
    if (sqlite3_step(final_query) == SQLITE_ROW){
        const unsigned char* text = sqlite3_column_text(final_query, 0);
        if (text)
            filename = std::string(reinterpret_cast<const char*>(text));
    }
    sqlite3_finalize(final_query);
    
    
    const char* delete_query = "DELETE FROM files WHERE id = ?;";
    sqlite3_stmt* delete_stmt = nullptr;
    exit = sqlite3_prepare_v2(db, delete_query, -1, &delete_stmt, nullptr);
    if (exit != SQLITE_OK){
        CROW_LOG_INFO << "Error Preparing Delete Statement";
        sqlite3_close(db);
    }
    exit = sqlite3_bind_int(delete_stmt, 1, fileid);
    if(exit != SQLITE_OK){
        CROW_LOG_INFO << "Error Binding Delete Parameter";
        sqlite3_finalize(delete_stmt);
        sqlite3_close(db);
    }
    exit = sqlite3_step(delete_stmt);
    if (exit != SQLITE_DONE){
        CROW_LOG_INFO << "Error Executing Delete Statement";
        sqlite3_finalize(delete_stmt);
        sqlite3_close(db);
    }
    sqlite3_finalize(delete_stmt);
    sqlite3_close(db);


    return filename;
}