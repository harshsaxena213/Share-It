#include <crow.h>
#include <sqlite3.h>
#include <random>
#include <string>
#include <iostream>
#include <openssl/sha.h>

void filename_to_db(std::string username,std::string filename){
    sqlite3* db;
    int exit=sqlite3_open("file.sqlite",&db);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error WHile Opening The DataBase";
    }
    const char* query="INSERT INTO files(username,filename) VALUES(?,?);";
    sqlite3_stmt* final_query=nullptr;
    exit=sqlite3_prepare_v2(db,query,-1,&final_query,nullptr);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error WHile Preapering The Statement";
    }
    sqlite3_bind_text(final_query, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(final_query, 2, filename.c_str(), -1, SQLITE_TRANSIENT);
    int execute=sqlite3_step(final_query);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error WHile RUnning  The Query";
            sqlite3_finalize(final_query);
            sqlite3_close(db);
    }
    sqlite3_finalize(final_query);
    sqlite3_close(db);
}