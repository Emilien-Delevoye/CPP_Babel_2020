/*!
 * @file Database.hpp
 * @brief Database class
 * @author Cyprien R
 * @version 1.0
 * @date 10/10/2020
 *
 * This class permit to interact with the sqlite database.
*/

#ifndef BABEL_DATABASE_HPP
#define BABEL_DATABASE_HPP

#include <string>
#include <sqlite3.h>
#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
#include <utility>
#include "ADatabase.hpp"
#include <type_traits>

using namespace sqlite_orm;

struct User {
    int id;
    std::string login;
    std::string password;
    std::string ip;
    int port;
};

#define QUERY make_storage("select.sqlite", \
    make_table("Users", \
    make_column("ID", &User::id, primary_key()), \
    make_column("LOGIN", &User::login), \
    make_column("PASSWORD", &User::password), \
    make_column("IP", &User::ip), \
    make_column("PORT", &User::port)))

template <typename... Args>
auto make_storage_query() {
    return QUERY;
}

template<class T>
class DataBase : ADatabase<T> {
public:
    DataBase();

    template<typename V>
    V addRow(T *user) {
        return storage.insert(*user);
    }
    void removeRow(int id) {
        storage.remove<T>(id);
    }
    template<typename P, typename U, typename N, typename J>
    P getVarFromId(U varType, N id, J idType, P errorValue) {
        auto v = storage.select(varType, where(c(idType) == id));
        return v.begin() == v.end() ? errorValue : *(v.begin());
    }
    template<typename U, typename V>
    T getDataFromId(V id, U idType) {
        return storage.get_all<T>(where(c(idType) == id));
    }
    template<typename B, typename V>
    std::vector<B> getColumn(V varType) {
        return storage.select(varType);
    }

private:
    decltype(make_storage_query()) storage;

};

#endif //BABEL_DATABASE_HPP
