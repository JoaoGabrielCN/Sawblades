/*
 * update.hpp
 *
 *  Created on: 19 de abr. de 2024
 *      Author: Aldo
 */

#pragma once

#include<SFML/Graphics.hpp>
#include "personagem.hpp"
#include "lamina.hpp"

void atualizaPlayer(Personagem &player, sf::Window& janela){
	player.pular(janela);
	player.andar();
	player.sprite.setPosition(player.x, player.y);
}

void colisao(Personagem& player, Lamina& saw, bool& pause){
	if(player.sprite.getGlobalBounds().intersects(saw.sprite.getGlobalBounds()))
	pause = true;

}

void ganhaPontos(Personagem& player, Lamina& saw, sf::Window& janela){

	float distancia = (player.x - saw.x) > 0 ? player.x - saw.x : (player.x - saw.x) * -1;
	player.noChao = player.y >= janela.getSize().y - player.sprite.getGlobalBounds().height;

	if(player.y - player.sprite.getGlobalBounds().height < saw.y - saw.sprite.getGlobalBounds().height && distancia < 10 && !saw.marcada){
		saw.marcada = true;
		saw.sprite.setColor(sf::Color::Green);
		player.pontos++;

}

	if(player.noChao && saw.marcada){
		saw.ativa = false;

	}
}



