/*
 * game.hpp
 *
 *  Created on: 7 de mai. de 2024
 *      Author: Aldo
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "personagem.hpp"
#include "lamina.hpp"

class Game {
public:
    Game();
    void run();

private:
    void loopEventos();
    void atualiza();
    void desenha();
    void criaSaw();
    void resetGame();
    void atualizaPontos(Personagem& player, Lamina& saw, sf::Window& janela);
    void colisao(Personagem& player, Lamina& saw, bool& pause, sf::Window& janela);


    sf::RenderWindow window;
    sf::Font fonte;
    sf::Text textoPontos;
    sf::Text textoFim;
    sf::Text botaoReset;
    Personagem player;
    std::vector<Lamina> saws;
    sf::Clock relogio;
    sf::Time tempoPassado;

    float intervalo;
    bool pausado;
};

#endif // GAME_HPP

