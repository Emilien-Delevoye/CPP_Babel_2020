/*!
 * @file Database.hpp
 * @brief Database class
 * @author Cyprien.R
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

    /*!
     * \brief addRow method
     * \param user
     *
     * Add user in db.
    */
    template<typename V>
    V addRow(const T *user) {
        return storage.insert(*user);
    }

    /*!
     * \brief addRow method
     * \param id
     *
     * remove row with id "id".
    */
    void removeRow(const int id) {
        storage.remove<T>(id);
    }

    /*!
     * \brief getVarFromId method
     * \param varType
     * \param id
     * \param idType
     * \param errorValue
     *
     * get var for a specific of specific id
    */
    template<typename P, typename U, typename N, typename J>
    P getVarFromId(const U varType, const N id, const J idType, const P errorValue) {
        auto v = storage.select(varType, where(c(idType) == id));
        return v.begin() == v.end() ? errorValue : *(v.begin());
    }

    /*!
     * \brief getDataFromId method
     * \param id
     * \param idType
     *
     * get row from id
    */
    template<typename U, typename V>
    T getDataFromId(const V id, const U idType) {
        return storage.get_all<T>(where(c(idType) == id));
    }
    /*!
     * \brief getColumn method
     * \param varType
     *
     * get whole column "type"
    */
    template<typename B, typename V>
    std::vector<B> getColumn(const V varType) {
        return storage.select(varType);
    }

private:
    decltype(make_storage_query()) storage;

};

#endif //BABEL_DATABASE_HPP
