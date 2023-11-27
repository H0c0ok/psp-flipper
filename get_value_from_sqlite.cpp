#include <sqlite3.h>
#include <iostream>

void searchValueByHash(const char* dbName, const char* hash) 
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // открываем базу данных
    rc = sqlite3_open(dbName,    db);
    if (rc) 
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    

    // выполнение запроса
    const char* sql = "SELECT value FROM map WHERE hash = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1,    stmt, 0);
    if (rc != SQLITE_OK) 
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    

    // привязываем значение к параметру в запросе
    rc = sqlite3_bind_text(stmt, 1, hash, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) 
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
        return;
    

    // выполняем запрос и выводим результат
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) 
        std::cout << "Value found: " << sqlite3_column_text(stmt, 0) << std::endl;
     else 
        std::cerr << "Value not found" << std::endl;
    

    // освобождаем ресурсы
    sqlite3_finalize(stmt);
    sqlite3_close(db);


int main() 
    const char* dbName = "database.db";
    const char* hash = "example_hash_value";
    searchValueByHash(dbName, hash);

    return 0;