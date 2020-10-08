/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#include "Users.hpp"

#include <utility>
using namespace std;

// TODO abstract

DataBase::DataBase() : storage(QUERY)
{
    storage.sync_schema();
    storage.remove_all<User>();

    User paul{-1, "Paul", "pass", "California", 4242};
    User allen{-1, "Allen", "pass", "Texas",    4242};
    User teddy{-1, "Teddy", "pass", "Norway",   4242};
    User mark{-1, "Mark", "pass", "Rich-Mond",  4242};
    User david{-1, "David", "pass", "Texas",    4242};
    User kim{-1, "Kim", "pass", "South-Hall",   4242};
    User james{-1, "James", "pass", "Houston",  4242};

    paul.id = storage.insert(paul);
    allen.id = storage.insert(allen);
    teddy.id = storage.insert(teddy);
    mark.id = storage.insert(mark);
    david.id = storage.insert(david);
    kim.id = storage.insert(kim);
    james.id = storage.insert(james);

    auto rows = storage.get_all<User>(group_by(&User::id), having(is_equal(&User::id, 2)));
    for(auto &employee: rows)
        std::cout << storage.dump(employee) << std::endl;
    auto test = storage.get<User>(2);
    //std::cout << test << std::endl;
    storage.remove<User>(2);
    auto rows2 = storage.get_all<User>(group_by(&User::id), having(is_equal(&User::id, 3)));
    for (auto &employee: rows2)
        std::cout << storage.dump(employee) << std::endl;

    vector<tuple<int, std::string, std::string, short>> all_users = storage.select(columns(&User::id, &User::login, &User::ip, &User::port));

    //  decltype(idsNamesSalarys) = vector<tuple<int, string, unique_ptr<double>>>
    for (auto &tpl: all_users) {
        std::cout << "id = " << std::get<0>(tpl) << ", name = " << std::get<1>(tpl) << ", ip = " << std::get<2>(tpl);
        cout << endl;
    }
}

int DataBase::addRow(std::string name, std::string password, std::string ip, short port)
{
    return storage.insert(User{-1, std::move(name), std::move(password), std::move(ip), port});
}

void DataBase::removeRow(int id)
{
    storage.remove<User>(id);
}

std::string DataBase::getPasswordFromLogin(std::string login)
{
    vector<tuple<int, std::string>> all_users = storage.select(columns(&User::id, &User::login));

    for (auto &tpl: all_users) {
        if (std::get<1>(tpl) == login)
            return getPassword(std::get<0>(tpl));
    }
    return ("");
}

void DataBase::removeRowFromLogin(std::string login)
{
    vector<tuple<int, std::string>> all_users = storage.select(columns(&User::id, &User::login));

    for (auto &tpl: all_users) {
        if (std::get<1>(tpl) == login)
            removeRow(std::get<0>(tpl));
    }
}