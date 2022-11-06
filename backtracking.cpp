//
// Created by Juan Pablo Rodriguez on 5/11/22.
//

#include <QConstOverload>
#include "backtracking.h"
#include "checkersgame.h"

bool atRisk(const std::map<std::pair<char, char>, char> & gameBoard,
            const std::pair<char, char> & from){
    if(((from.first+1 && from.second-1) || (from.first-1 && from.second-1)) == pieces[Empty]){
        return true;
    }
}

std::pair<int, std::pair<char, char>> mejorAdyacente(const std::pair<char, char> & from, const std::map<std::pair<char, char>, char> & gameBoard){

    std::vector<std::pair<char, char>> posibilidades {};
    int puntaje =0;

    char pieza = gameBoard.find(from)->second;
    auto it = gameBoard.find(std::make_pair(from.first, from.second));

    if (pieza == pieces[WhiteKing]) {
        //superior derecha
        it = gameBoard.find(std::make_pair(from.first + 1, from.second + 1));
        if(it != gameBoard.end()){
            if(it->second == pieces[Empty]){
                posibilidades.push_back(it->first);
                if(atRisk(gameBoard,from)){
                    puntaje += 1;
                }else if(atRisk(gameBoard, ){
                    puntaje -=1;
                }

            }
        }

        //superior izquierda
        it = gameBoard.find(std::make_pair(from.first - 1, from.second + 1));
        if(it != gameBoard.end()){
            if(it->second == pieces[Empty]){
                posibilidades.push_back(it->first);
            }
        }
    }

    if (pieza == pieces[White]) {
        it = gameBoard.find(std::make_pair(from.first - 1, from.second - 1));
        //casilla inferior izquierda
        if(it != gameBoard.end()){
            if(it->second == pieces[Empty]){
                posibilidades.push_back(it->first);
            }
        }
        //casilla inferior derecha
        it = gameBoard.find(std::make_pair(from.first + 1, from.second - 1));
        if(it != gameBoard.end()){
            if(it->second == pieces[Empty]){
                posibilidades.push_back(it->first);
            }
        }
    }

    while(posibilidades.size()!= 0) {
        int siz = posibilidades.size();
        if (atRisk(gameBoard, posibilidades.at(siz - 1))) {
            posibilidades.pop_back();
        }else{
            break;
        }
    }

    if(posibilidades.size() == 0){
        return {'z', 'z'};
    }else if(posibilidades.size() == 1){
        return posibilidades.at(0);
    }else{
        int randIdx = qrand() % posibilidades.size();
        return posibilidades.at(randIdx);
    }
}

std::pair<char, char> mejorSalto(const std::map<std::pair<char, char>, char> & gameBoard,
                                                 const std::pair<char, char> & from){
    std::vector<std::pair<char, char>> posibilidades {};

    char playerPiece = gameBoard.find(from)->second;
    auto it = gameBoard.find(std::make_pair(from.first + 1, from.second + 1));//empieza iterador
    auto it2 = gameBoard.find(std::make_pair(from.first + 1, from.second + 1));

    if (playerPiece == pieces[WhiteKing]) {
        //superior derecha
        it = gameBoard.find(std::make_pair(from.first + 2, from.second + 2));
        if(it != gameBoard.end()){
            if(it->second == pieces[Empty] && it2->second != pieces[Empty]){
                posibilidades.push_back(it->first);
            }
        }

        //superior izquierda
        it = gameBoard.find(std::make_pair(from.first - 2, from.second + 2));
        if(it != gameBoard.end()){
            if(it->second == pieces[Empty] && it2->second != pieces[Empty]){ //if the square is empty
                posibilidades.push_back(it->first);
            }
        }
    }

    if (playerPiece == pieces[White]) {
        it = gameBoard.find(std::make_pair(from.first - 2, from.second - 2));
        //casilla inferior izquierda
        if(it != gameBoard.end()){
            if(it->second == pieces[Empty] && it2->second != pieces[Empty]){
                posibilidades.push_back(it->first);
            }
        }
        //casilla inferior derecha
        it = gameBoard.find(std::make_pair(from.first + 2, from.second - 2));
        if(it != gameBoard.end()){
            if(it->second == pieces[Empty] && it2->second != pieces[Empty]){
                posibilidades.push_back(it->first);
            }
        }
    }

    if(posibilidades.size() == 0){
        return {'z', 'z'};
    }else if(posibilidades.size() == 2){
        int randIdx = qrand() % posibilidades.size();
        return posibilidades.at(randIdx);
    }else{
        return posibilidades.at(0);
    }

}

std::pair<std::pair<char, char>, std::pair<char, char>> mejorMovimiento(std::map<std::pair<char, char>, char> & gameBoard,
                                                                        int & playerTurn) {
    //Crea vector con pares ordenados de cada pieza del jugador
    std::vector<std::pair<char, char>> piezas;
    for (auto it = gameBoard.begin(); it != gameBoard.end(); ++it) {
        if (it->second == pieces[playerTurn] || it->second == pieces[playerTurn + 1]) {
            piezas.push_back(it->first);

        }
    }


    std::pair<std::pair<char, char>, std::pair<char, char>> bestMove = std::make_pair(std::make_pair('z', 'z'), std::make_pair('z', 'z'));
    int val = 0;//puntaje del movimiento

    std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> posibilidades;//crea lista de posibles movimientos

    //iteracion sobre piezas del jugador
    for(auto it = piezas.begin(); it != piezas.end(); ++it){
        auto temp = mejorSalto(gameBoard, *it);
        if(temp.first > val){
            std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> newPossibleMoves;
            posibilidades.push_back(std::make_pair(*it, temp.second));
            val = temp.first;
            posibilidades = newPossibleMoves;
        }else if (temp.first == val){
            posibilidades.push_back(std::make_pair(*it, temp.second));
        }
    }

    if(val>0){
        /*for (auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
            std::cout << char(it->first.first)<<char(it->first.second) << "->" <<char(it->second.first)<<char(it->second.second) << std::endl;
        */
        int randomIndex = qrand() % posibilidades.size();
        bestMove = posibilidades.at(randomIndex);
    }

    else { //Don't bother looking for a single square if a jump square was found
        std::vector<std::pair<std::pair<char, char>, std::pair<char, char>>> possibleSingleMoves {};
        for(auto it = pieceVec.begin(); it != pieceVec.end(); ++it){
            std::pair<char, char> temp = findSingleSquareMoveAI(gameBoard, *it);
            if (temp != std::make_pair('z', 'z')){
                possibleSingleMoves.push_back(std::make_pair(*it, temp));
            }
        }

        int randomIndex = qrand() % possibleSingleMoves.size();
        bestMove = possibleSingleMoves.at(randomIndex);

    }
    if (bestMove.second == std::make_pair('z', 'z')){ // Ensure a move has been found
        std::cout<<"Programmer error: AI has no valid moves."<<std::endl;
        throw "Programmer error: AI has no valid moves.";
    }

    return bestMove;
}