/*
 * main.cpp
 *
 *  Created on: 15 de abr. de 2024
 *      Author: Aldo
 */

#include "src/game.hpp"
#include<SFML/Graphics.hpp>

int main() {
    Game *game = new Game;
    game->run();

    delete game;
    game = nullptr;
    return 0;
}
