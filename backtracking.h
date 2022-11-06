//
// Created by Juan Pablo Rodriguez on 5/11/22.
//

#ifndef PROYECTO2_BACKTRACKING_H
#define PROYECTO2_BACKTRACKING_H
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <map>
#include <stack>


bool atRisk(const std::map<std::pair<char, char>, char> & gameBoard,
            const std::pair<char, char> & from);

std::pair<int, std::pair<char, char>> mejorAdyacente(const std::pair<char, char> & from,
                                             const std::map<std::pair<char, char>, char> & gameBoard);

std::pair<int, std::pair<char, char>> mejorSalto(const std::map<std::pair<char, char>, char> & gameBoard,
                                                 const std::pair<char, char> & from);

std::pair<std::pair<char, char>, std::pair<char, char>> mejorMovimiento(std::map<std::pair<char, char>, char> & gameBoard,
                                                                  int & playerTurn);


#endif //PROYECTO2_BACKTRACKING_H
