/*
 * personagem.hpp
 *
 *  Created on: 15 de abr. de 2024
 *      Author: Aldo
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Personagem {
public:

    sf::Texture textura;
    sf::Sprite sprite;

    int pontos = 0;

    bool noChao = false;

    float x, y, velX, velY, alturaPulo = -20.f;
    float gravidade = 0.8;

    Personagem(sf::Window& janela);

    void colisaoTela(sf::Window& janela);

    void andar();

    void pular(sf::Window& janela);
};
