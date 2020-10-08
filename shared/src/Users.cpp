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
    storage.remove_all<User>(); // FIXME

    std::cout << "DUMP DB" << std::endl;
    vector<tuple<int, std::string, std::string, short>> all_users = storage.select(columns(&User::id, &User::login, &User::ip, &User::port));
    for (auto &tpl: all_users) {
        std::cout << "id = " << std::get<0>(tpl) << ", name = " << std::get<1>(tpl) << ", ip = " << std::get<2>(tpl);
        cout << endl;
    }
    std::cout << "=======" << std::endl;
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