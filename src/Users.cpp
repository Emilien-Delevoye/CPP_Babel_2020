/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#include "Users.hpp"

#include <utility>


DataBase::DataBase() : storage(QUERY)
{


    storage.sync_schema();
    storage.remove_all<User>();

    User paul{-1, "Paul", "California", 4242};
    User allen{-1, "Allen", "Texas",    4242};
    User teddy{-1, "Teddy", "Norway",   4242};
    User mark{-1, "Mark", "Rich-Mond",  4242};
    User david{-1, "David", "Texas",    4242};
    User kim{-1, "Kim", "South-Hall",   4242};
    User james{-1, "James", "Houston",  4242};

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
    for(auto &employee: rows2)
        std::cout << storage.dump(employee) << std::endl;
}

int DataBase::addRow(std::string name, std::string ip, short port)
{
    return storage.insert(User{-1, std::move(name), std::move(ip), port});
}

void DataBase::removeRow(int id)
{
    storage.remove<User>(id);
}
