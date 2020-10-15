/*!
 * @file ADatabase.hpp
 * @brief ADatabase abstract
 * @author Cyprien.R
 * @version 1.0
 * @date 10/10/2020
 *
 * This class is an abstraction of the usage of the database.
*/

#ifndef BABEL_ADATABASE_HPP
#define BABEL_ADATABASE_HPP

#include <boost/any.hpp>
#include <sqlite_orm/sqlite_orm.h>
#include <boost/config.hpp>

#include "ADatabase.hpp"

template<typename T>
class ADatabase {
public:
    ADatabase() = default;
private:
    template<typename V>
    V addRow(T *user) {};
    void removeRow(int id) {};
    template<typename P, typename U, typename N, typename J>
    P getVarFromId(U varType, N id, J idType, P errorValue) {};
    template<typename U, typename V>
    T getDataFromId(V id, U idType) {};
    template<typename B, typename V>
    std::vector<B> getColumn(V varType) {};
};


#endif //BABEL_ADATABASE_HPP
