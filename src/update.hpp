/*
 * update.hpp
 *
 *  Created on: 19 de abr. de 2024
 *      Author: Aldo
 */


#include<SFML/Graphics.hpp>
#include "personagem.hpp"
#include "lamina.hpp"

void atualizaPlayer(Personagem &player, sf::Window& janela){
	player.pular(janela);
	player.andar();
	player.sprite.setPosition(player.x, player.y);
}

void colisao(Personagem& player, Lamina& saw, bool& pause, sf::Window& janela){

	player.noChao = player.y >= janela.getSize().y - player.sprite.getGlobalBounds().height;

	if(player.sprite.getGlobalBounds().intersects(saw.sprite.getGlobalBounds())&& player.vivo){
	player.velY = -14.f;
	player.vivo = false;
	player.sprite.setColor(sf::Color::Red);
	}

	if(player.noChao && !player.vivo){
		pause = true;
	}
}

void ganhaPontos(Personagem& player, Lamina& saw, sf::Window& janela){

	float distancia = std::abs(static_cast<int>(player.x - saw.x));

	player.noChao = player.y >= janela.getSize().y - player.sprite.getGlobalBounds().height;

	if(player.y - player.sprite.getGlobalBounds().height < saw.y - saw.sprite.getGlobalBounds().height && distancia < 5 && !saw.marcada && player.vivo){
		saw.marcada = true;
		saw.sprite.setColor(sf::Color::Green);
		player.pontos++;
}

	if(player.noChao && saw.marcada){
		saw.ativa = false;
	}

}






