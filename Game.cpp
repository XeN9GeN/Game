#include "Game.h"
#include <iostream>
#include "Card.h"
#include <memory>
#include <string>
#include "Colors.h"

Game::Game(Character& p, Enemy& e) : player(p), enemy(e) {}


void Game::logPlay(const std::string& entry) {
    play_log.push_back(entry);
}

void Game::printPlayLog() const {
    if (play_log.empty()) return;
    std::cout << Color::CYAN << "[LOG] Played this turn:" << Color::RESET << "\n";
    for (const auto& e : play_log) {
        std::cout << Color::DARK_GRAY << " - " << Color::RESET << e << "\n";
    }
}


void Game::PlayerTurn() {
    std::cout << Color::CYAN << "\n--- Player turn..." << Color::RESET << "\n";
    

    auto& hand = player.getHand();
    auto& Deck = player.getDeck();
    int currentMana = player.getMana();

    if (hand.empty()) {
        std::cout << Color::YELLOW << "Hand is empty" << Color::RESET;
    }

    while (true) {
        std::cout << "\n\n";
        std::cout << Color::BLUE << "Mana: " << Color::RESET << currentMana << "\n";
        std::cout << Color::WHITE << "Hand:" << Color::RESET << "\n";

        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i]) {
                std::cout << Color::CYAN << " [" << i << "] " << Color::RESET;
                hand[i]->printCard(); // вывод инфо о карте (метод базового Card)
            }
            else {
                std::cout << Color::DARK_GRAY << " [" << i << "] <empty>\n" << Color::RESET;
            }
        }

        std::cout << Color::CYAN << "\nChoose action:" << Color::RESET << "\n";
        std::cout << Color::GREEN << " p <index>" << Color::RESET << "  - Play card with index\n";
        std::cout << Color::BLUE << " r" << Color::RESET << "           - Draw card\n";
        std::cout << Color::RED << " a" << Color::RESET << "          - Basic attack\n";
        std::cout << Color::DARK_GRAY << " e" << Color::RESET << "          - End turn\n";
        std::cout << Color::WHITE << "> " << Color::RESET;

        std::string cmd;
        std::cin >> cmd;

        // Проверка 0: Корректность команды
        if (cmd != "p" && cmd != "r" && cmd != "a" && cmd != "e") {
            std::cout << "Invalid syntax" << "\n";
            continue;
        }

        if (cmd == "p") {
            int indx;
            std::cin >> indx;
            auto card = hand[indx];

            // Проверка 1: Корректность индекса
            if (indx < 0 || indx >= hand.size()) {
                std::cout << Color::RED << "Invalid card index!" << Color::RESET << "\n";
                continue;
            }

            // Проверка 2: Карта существует
            if (!card) {
                std::cout << Color::RED << "No card at this position!" << Color::RESET << "\n";
                continue;
            }

            int cost = player.getEffectiveCardCost(*card);

            // Проверка 3: Хватает ли маны
            if (cost > currentMana) {
                std::cout << Color::RED << "Not Enough Mana!!!" << Color::RESET;
                continue;
            }


            std::cout << Color::GREEN << "Player use card: " << card->getName() << Color::RESET << "\n";
            logPlay(card->getName());
            card->apply(player, enemy);// переработать для BUFF
            currentMana -= player.getEffectiveCardCost(*card);;
            player.setMana(currentMana);
            hand.erase(hand.begin() + indx);

            std::cout << Color::DARK_GRAY << "-------------------------" << Color::RESET << "\n";
            printPlayLog();

        }
        //Проверка на пустоту колоды
        else if (cmd == "r") {
            if (Deck.empty()) {
                std::cout << Color::RED << "Deck is empty!" << Color::RESET << "\n";
            }
            else {
                player.drawCard();
                std::cout << Color::BLUE << "Player draws a card." << Color::RESET << "\n";
            }
        }

        else if (cmd == "a") {
            int dmg = 2;
            enemy.getAttacked(dmg);
            std::cout << Color::RED << "Base attack deals: " << Color::RESET << dmg << Color::RED << " damage\n" << Color::RESET;
            logPlay(std::string("Basic attack: ") + std::to_string(dmg) + " dmg");

            std::cout << Color::DARK_GRAY << "-------------------------" << Color::RESET << "\n";
            printPlayLog();

            break;
        }

        else if (cmd == "e") {
            break;
        }
        else {
            std::cout << Color::RED << "Wrong command." << Color::RESET << "\n";
        }
        std::cout << "\n";
    }
}

void Game::autoPlayerTurn() {
    std::cout << Color::CYAN << "[AUTO] Player turn..." << Color::RESET << "\n";

    int currentMana = player.getMana();
    auto& hand = player.getHand();

    int bestIndex = -1;
    int bestCost = -1;

    // ищем самую дорогую карту в руке, которую можем разыграть
    for (int i = 0; i < hand.size(); ++i) {
        auto& c = hand[i];

        //Проверка на не ту карту
        if (!c) {
            std::cout << Color::YELLOW << "[AUTO] Warning: Null card in hand at index " << i << Color::RESET << "\n";
            continue;
        };

        int cost = player.getEffectiveCardCost(*c);;

        //Проверка на -кост
        if (cost < 0) {
            std::cout << Color::YELLOW << "[AUTO] Warning: Card \"" << c->getName()
                << "\" has negative cost (" << cost << "), treating as 0" << Color::RESET << "\n";
            cost = 0;
        }

        if (cost <= currentMana && cost > bestCost) {
            bestCost = cost;
            bestIndex = i;
        }
    }
    play_log.clear();


    if (bestIndex != -1) {
        auto card = hand[bestIndex];

        //Проверка существование карты
        if (!card) {
            std::cout << Color::RED << "[AUTO] ERROR: Selected card is null!" << Color::RESET << "\n";
        }
        else {
            std::cout << Color::GREEN << "[AUTO] Player uses card: " << card->getName() << Color::RESET << "\n";
        }


        logPlay(card->getName());
        card->apply(player, enemy);

        player.setMana(currentMana - player.getEffectiveCardCost(*card));

        //Проверка на выход за границы индексов
        if (bestIndex >= 0 && bestIndex < hand.size()) {
            hand.erase(hand.begin() + bestIndex);
        }
        else {
            std::cout << Color::RED << "[AUTO] ERROR: Invalid card index for removal: "
                << bestIndex << Color::RESET << "\n";
        }

        std::cout << Color::DARK_GRAY << "-------------------------" << Color::RESET << "\n";
        printPlayLog();
        return;
    }


    int dmg = 2;
    switch (rand() % 2 + 1) {
    case 1: {
        enemy.getAttacked(dmg);

        std::cout << Color::RED << "[AUTO] Player attacks for " << Color::RESET << dmg << Color::RED << " damage\n" << Color::RESET;

        logPlay(std::string("Basic attack: ") + std::to_string(dmg) + " dmg");
        break;
    }
    case 2: {
        player.drawCard();

        logPlay(std::string("PLayer drow card"));
        std::cout << Color::BLUE << "[AUTO] Player draws a card\n" << Color::RESET;
        break;
    }
          std::cout << Color::DARK_GRAY << "-------------------------" << Color::RESET << "\n";
          printPlayLog();
          std::cout << "\n\n\n";

    }
}