/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_ADATABASE_HPP
#define BABEL_ADATABASE_HPP


template<typename T>
class ADatabase {
public:
    ADatabase() = default;
    int addRow(T) = 0;
    void removeRow(int) = 0;


};


#endif //BABEL_ADATABASE_HPP
