/*
 * personagem.cpp
 *
 *  Created on: 23 de abr. de 2024
 *      Author: Aldo
 */

#include "personagem.hpp"
#include<iostream>

Personagem::Personagem(sf::Window& janela) { // @suppress("Class members should be properly initialized")
    textura.loadFromFile("assets/mario.png");
    sprite.setTexture(textura);
    x = janela.getSize().x/2;
    y = janela.getSize().y - sprite.getGlobalBounds().height;
}

void Personagem::colisaoTela(sf::Window& janela) {
    if (x  > janela.getSize().x - sprite.getGlobalBounds().width + sprite.getGlobalBounds().width * 0.5) {
        x = janela.getSize().x - sprite.getGlobalBounds().width + sprite.getGlobalBounds().width * 0.5;
    }
    if (x  <= 0 +  sprite.getGlobalBounds().width * 0.5) {
        x = 0 + sprite.getGlobalBounds().width * 0.5 ;
    }
}

void Personagem::andar() {
    velX = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velX = 5;
        sprite.setScale(1, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velX = -5;
        sprite.setScale(-1, 1);
    }
    x += velX;
}

void Personagem::pular(sf::Window& janela) {
    noChao = y >= janela.getSize().y - sprite.getGlobalBounds().height;

    bool pressionado = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (pressionado && noChao) {
        noChao = false;
        velY = alturaPulo;
        pressionado = false;

    }

    if (!noChao) {
        velY += gravidade;

    } else {
        velY = 0;
        y = janela.getSize().y - sprite.getGlobalBounds().height;
        noChao = true;
    }

    pressionado = false;
    y += velY;
}

void Personagem::atualiza(sf::Window& janela){

	Personagem::colisaoTela(janela);
	Personagem::pular(janela);
	Personagem::andar();

	sprite.setPosition(x, y);
}
