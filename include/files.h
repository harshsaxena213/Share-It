std::vector<crow::mustache::context> ListFiles(std::string username)
{
    sqlite3 *db;
    int exit = sqlite3_open("file.sqlite", &db);
    if (exit != SQLITE_OK)
    {
        CROW_LOG_INFO << "Error While Opening The Database";
        return {};
    }
    
    
    const char *query = "SELECT id, filename FROM files WHERE username=?";
    sqlite3_stmt *final_query = nullptr;
    exit = sqlite3_prepare_v2(db, query, -1, &final_query, nullptr);
    if (exit != SQLITE_OK)
    {
        CROW_LOG_INFO << "Error While Preparing The Statement";
        sqlite3_finalize(final_query);
        sqlite3_close(db);
        return {};
    }
    
    exit = sqlite3_bind_text(final_query, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    if (exit != SQLITE_OK)
    {
        CROW_LOG_INFO << "Error While Binding Parameter";
        sqlite3_finalize(final_query);
        sqlite3_close(db);
        return {};
    }

    std::vector<crow::mustache::context> files_vector;

    while (sqlite3_step(final_query) == SQLITE_ROW) {
        crow::mustache::context file_ctx;
       
        int id = sqlite3_column_int(final_query, 0);
        const unsigned char* fname = sqlite3_column_text(final_query, 1);

        file_ctx["id"] = std::to_string(id);
        file_ctx["filename"] = fname ? reinterpret_cast<const char*>(fname) : "";

        files_vector.push_back(file_ctx);
    }

    sqlite3_finalize(final_query);
    sqlite3_close(db);

    return files_vector;
}