/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"

int main(int argc, char **argv)
{
    Call call("127.0.0.1", std::stoi(argv[1]), std::stoi(argv[2]));
    return 0;
}