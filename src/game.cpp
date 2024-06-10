/*
 * game.cpp
 *
 *  Criado em: 7 de mai. de 2024
 *      Autor: Aldo
 */

#include "game.hpp"
#include "update.hpp"

Game::Game() : window(sf::VideoMode(400, 600), "Sawblades", sf::Style::Close | sf::Style::Titlebar), player(window) {
    window.setFramerateLimit(200);
    window.setVerticalSyncEnabled(true);

    fonte.loadFromFile("assets/fonte.TTF");

    textoPontos.setFont(fonte);
    textoPontos.setCharacterSize(100);
    textoPontos.setFillColor(sf::Color::White);
    textoPontos.setPosition(window.getSize().x * 0.5 - 50, window.getSize().y * 0.5 - 100);

    textoFim.setFont(fonte);
    textoFim.setCharacterSize(35);
    textoFim.setFillColor(sf::Color::Red);
    textoFim.setPosition(60, window.getSize().y * 0.5 - 100);
    textoFim.setString("Game over!");

    botaoReset.setFont(fonte);
    botaoReset.setCharacterSize(35);
    botaoReset.setFillColor(sf::Color::White);
    botaoReset.setPosition(100, window.getSize().y * 0.5 + 30);
    botaoReset.setString("Restart");

    intervalo = 1;
    pausado = false;
}

void Game::criaSaw() {
    tempoPassado = relogio.getElapsedTime();

    if (tempoPassado.asSeconds() >= intervalo) {
        Lamina novaLamina(2.f, 4.f, 1 + rand() % 2);
        novaLamina.x = std::rand() % (window.getSize().x - 50);
        novaLamina.y = -novaLamina.sprite.getGlobalBounds().height;
        saws.push_back(novaLamina);
        intervalo = rand() % 4;
        relogio.restart();
    }
}

void Game::run() {
    while (window.isOpen()) {
        loopEventos();
        atualiza();
        desenha();
    }
}

void Game::loopEventos() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            pausado = true;
        }

        if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
            sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);
            if (botaoReset.getGlobalBounds().contains(static_cast<float>(posicaoMouse.x), static_cast<float>(posicaoMouse.y))) {
                resetGame();
            }
        }
    }
}

void Game::resetGame() {
    intervalo = 1;
    pausado = false;
    player.reset(window);
    saws.clear();
    relogio.restart();
    intervalo = 1;
}

void Game::atualiza() {
    if (!pausado) {
        player.sprite.setOrigin(player.sprite.getLocalBounds().width * 0.5, 0);

        criaSaw();

        for (auto& saw: saws) {
            saw.colisaoTela(window);
            saw.x += saw.velX;
            saw.y += saw.velY;

            saw.sprite.setPosition(saw.x, saw.y);
            saw.textura.loadFromFile("assets/saw.png");
            saw.sprite.setTexture(saw.textura);

            colisao(player, saw, pausado, window);
            ganhaPontos(player, saw, window);
        }

        player.colisaoTela(window);
        atualizaPlayer(player, window);
    }
}

void Game::desenha() {
    if (!pausado) {
        window.clear();

        for (unsigned int i = 0; i < saws.size(); ++i) {
            if (saws[i].ativa) {
                window.draw(saws[i].sprite);
            } else {
                saws.erase(saws.begin() + i);
            }
        }

        window.draw(player.sprite);
        textoPontos.setString(std::to_string(player.pontos));
        window.draw(textoPontos);
        window.display();
    } else {
        window.clear();
        window.draw(textoFim);
        window.draw(botaoReset);
        window.display();
    }
}
