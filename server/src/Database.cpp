/*!
 * @file Users.cpp
 * @brief Database containing Users implementation
 * @author Cyprien.R
 * @version 1.0
 * @date 05/10/2020
 *
 * This class permit to interact with the sqlite database.
*/

#include "Database.hpp"

using namespace std;

template class DataBase<User>;

/*!
 * \brief DataBase constructor
 *
 * Construct the class.
 * Dump the database
*/

template<class T>
DataBase<T>::DataBase() : ADatabase<T>(), storage(QUERY)
{
    storage.sync_schema();

    std::cout << "===== [DUMP DB] =====" << std::endl;
    vector<tuple<int, std::string, std::string, int>> all_users = storage.select(columns(&User::id, &User::login, &User::ip, &User::port));
    for (auto &tpl: all_users)
        std::cout << "id = " << std::get<0>(tpl) << ", name = " << std::get<1>(tpl) << ", ip = " << std::get<2>(tpl) << endl;
    std::cout << "=====================" << std::endl;
}