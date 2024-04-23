/*
 * lamina.hpp
 *
 *  Created on: 23 de abr. de 2024
 *      Author: Aldo
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Lamina {
public:
    sf::Texture textura;
    sf::Sprite sprite;

    bool marcada = false;
    bool ativa = true;

    float x, y, velX, velY, direcao;

    Lamina(float velX, float velY, float direcao); // @suppress("Class members should be properly initialized")

    void colisaoTela(sf::Window& janela);

};

