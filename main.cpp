#include <SFML/Graphics.hpp>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "personagem.hpp"
#include "update.hpp"
#include "lamina.hpp"


int main() {
	std::srand(time(NULL));
	bool pausado = false;

    sf::RenderWindow window(sf::VideoMode(400, 600), "Sawblades", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(200);
    window.setVerticalSyncEnabled(true);


    std::vector <Lamina> saws;
    sf::Clock relogio;
    sf::Time tempoPassado;

    int intervalo = 1;

    sf::Font fonte;
    fonte.loadFromFile("assets/fonte.TTF");

    sf::Text textoPontos;
    textoPontos.setFont(fonte);
    textoPontos.setCharacterSize(100);
    textoPontos.setFillColor(sf::Color::White);
    textoPontos.setPosition(window.getSize().x * 0.5 - 50 , window.getSize().y * 0.5 - 100);

    sf::Text textoFim;
    textoFim.setFont(fonte);
    textoFim.setCharacterSize(35);
    textoFim.setFillColor(sf::Color::White);
    textoFim.setPosition(30 , window.getSize().y * 0.5 - 100);
    textoFim.setString("Voce perdeu!");

    Personagem mario(window);



    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
                pausado = true;
            }
        }


if(!pausado){

    mario.sprite.setOrigin(mario.sprite.getLocalBounds().width * 0.5, 0);

    tempoPassado = relogio.getElapsedTime();

    if (tempoPassado.asMilliseconds() >= intervalo * 1000) {

            Lamina novaLamina(2.f, 4.f, 1 + rand() % 2);
            novaLamina.x =  std::rand() % (window.getSize().x - 50);
            novaLamina.y = 0 - novaLamina.sprite.getGlobalBounds().height;
            saws.push_back(novaLamina);
            intervalo = 0 + rand() % 4;
            relogio.restart();
     }

        for (unsigned int i = 0; i < saws.size(); ++i) {
			saws[i].colisaoTela(window);
			saws[i].x += saws[i].velX;
			saws[i].y += saws[i].velY;
			saws[i].sprite.setPosition(saws[i].x, saws[i].y);
			colisao(mario, saws[i], pausado);
			ganhaPontos(mario, saws[i], window);


		}

        mario.colisaoTela(window);
        atualizaPlayer(mario, window);

        window.clear(sf::Color::Blue);

        for(unsigned int i = 0; i < saws.size(); ++i) {

        	saws[i].textura.loadFromFile("assets/saw.png");
        	saws[i].sprite.setTexture(saws[i].textura);
        	if(saws[i].ativa){
        	window.draw(saws[i].sprite);

        	}else{
        		saws.erase(saws.begin() + i);
        	}
        }

        window.draw(mario.sprite);
        textoPontos.setString(std::to_string(mario.pontos));
        window.draw(textoPontos);
        window.display();

    }else{

    	window.clear();
    	window.draw(textoFim);
    	window.display();
    }

  }
    return 0;
}
