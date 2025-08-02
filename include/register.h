#include <crow.h>
#include <sqlite3.h>
#include <random>
#include <string>
#include <iostream>
#include <openssl/sha.h>

bool Register(std::string username,std::string password){
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
    int id = std::rand() % 100 + 1;
    sqlite3* db;
    int exit=sqlite3_open("db.sqlite",&db);
    if (exit!=SQLITE_OK)
    {
        CROW_LOG_INFO<<"Error While Opening The Database";
    }
    const char* query="INSERT INTO users(id,username,password_hash) VALUES(?,?,?);";
    sqlite3_stmt* final_query=nullptr;
    exit=sqlite3_prepare_v2(db,query,-1, &final_query ,nullptr);
    if(exit!=SQLITE_OK){
        CROW_LOG_INFO<<"Error While Preparing The Query";
    }

    std::string salted=password+username;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)salted.data(),salted.size(), hash);
    std::stringstream ss;
    for (unsigned char c : hash)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    std::string password_hash = ss.str();
    CROW_LOG_INFO<<password_hash;

        sqlite3_bind_int(final_query,1,id);
        sqlite3_bind_text(final_query,2,username.c_str(),-1,SQLITE_TRANSIENT);
        sqlite3_bind_text(final_query,3,password_hash.c_str(),-1,SQLITE_TRANSIENT);

        exit=sqlite3_step(final_query);
        if(exit!=SQLITE_DONE){
            CROW_LOG_INFO<<"Error While Executing The Query!";
            sqlite3_finalize(final_query);
            sqlite3_close(db);
            
        }

    sqlite3_finalize(final_query);
    sqlite3_close(db);
    return true;
    
}