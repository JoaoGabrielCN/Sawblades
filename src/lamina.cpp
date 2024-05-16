/*
 * lamina.cpp
 *
 *  Created on: 23 de abr. de 2024
 *      Author: Aldo
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include "lamina.hpp"
#include <ctime>
#include <cstdlib>

Lamina::Lamina(float velX, float velY, float direcao){ // @suppress("Class members should be properly initialized")
    if (direcao == 1) {
        direcao = 1;
    } else {
        direcao = -1;
    }

    this->direcao = direcao;
    this->velX = velX * direcao;
    this->velY = velY;

}

void Lamina::colisaoTela(sf::Window& janela){
    if (x > janela.getSize().x - sprite.getGlobalBounds().width || x < 0) {
        velX = -velX;
    }
    if (y + sprite.getGlobalBounds().height > janela.getSize().y) {
        velY = -velY;
    }
}

void Lamina::atualiza(sf::Window& janela){

	 textura.loadFromFile("assets/saw.png");
	 sprite.setTexture(textura);

	 Lamina::colisaoTela(janela);

	 x += velX;
	 y += velY;

	 sprite.setPosition(x, y);
}

