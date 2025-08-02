#include <crow.h>
#include <sqlite3.h>
#include <random>
#include <string>
#include <iostream>
#include <openssl/sha.h>

std::string fileid_to_filename(int fileid){
    sqlite3* db;
    int exit=sqlite3_open("file.sqlite",&db);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error WHile Opening The DataBase";
    }
    const char* query="SELECT filename FROM files WHERE id=?;";
    sqlite3_stmt* final_query=nullptr;
    exit=sqlite3_prepare_v2(db,query,-1,&final_query,nullptr);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error WHile Preapering The Statement";
    }
    sqlite3_bind_int(final_query, 1, fileid);
    int execute=sqlite3_step(final_query);
    if(execute==SQLITE_ROW){
        const unsigned char* filename = sqlite3_column_text(final_query, 0);
        if(filename){
            std::string filename_str = std::string(reinterpret_cast<const char*>(filename));
            sqlite3_finalize(final_query);
            sqlite3_close(db);
            return filename_str; 
        }
        else{
            return "";
        }

}
}