#include <iostream>
#include <cstdlib> 
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
#include <string>
#include <algorithm>

#include "Character.h"
#include "Enemy.h"
#include "Card.h"
#include "Game.h"
#include "Face.cpp"
#include "Display.h"
#include <windows.h>
#include "DeckLoader.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
}


using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);
    wcscpy_s(fontInfo.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);
    std::locale::global(std::locale("en_US.UTF-8"));




    Character player(30, 5, 10); // HP, Armor, Mana
    Enemy enemy("Bread", 15, 10, 10);
    
    Game game(player, enemy);
    
    //Колоду можни 
    //Какие ptr'ы бывают
    //Валидация ошибок
    //Интерфейс
    DeckLoader::loadPlayerDeck(player, "player_deck.txt");
    DeckLoader::loadPlayerDeck(enemy, "enemy_deck.txt");

    player.drawCard();
    player.drawCard();
    player.drawCard();
    player.drawCard();

    enemy.drawCard();
    enemy.drawCard();
    enemy.drawCard();
    enemy.drawCard();

    bool auto_mode = false;
    cout << "Choose mode:\n";
    cout << "1 - Auto battle\n";
    cout << "2 - Manual battle (you play your turn)\n";
    cout << "> ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        auto_mode = true;
        cout << "\n[MODE] Auto battle enabled.\n";
    }
    else {
        auto_mode = false;
        cout << "\n[MODE] Manual mode enabled.\n";
    }

    std::cout << "Battle Start!" << endl;

    int turn = 1;
    while (player.getHealth() > 0 && enemy.getHealth() > 0) {
        clearScreen();
        std::cout << "\n\n\n\n";
        Display::printSimpleBattle(player, enemy, turn);
        

        if(player.getStatuses().getRegeneration() > 0) {
            int heal_amount = player.getStatuses().getRegeneration();
            player.setHp(player.getHealth() + heal_amount);
            std::cout << Color::GREEN << "Player regenerates " << heal_amount << " health due to Regeneration status." << Color::RESET << "\n";
		}//Хил в начале хода от регенерации

        player.getStatuses().updateStatuses();
        enemy.getStatuses().updateStatuses();
        
        player.setMana(turn);
        enemy.setMana(turn);
       
            
        if (auto_mode) {
            game.autoPlayerTurn();      // игрок ходит автоматически
        }
        else {
            game.PlayerTurn();          // игрок вводит команды сам
        }
        enemy.autoEnemyTurn(player);    // враг ВСЕГДА ходит автоматически
        enemy.drawCard();
        enemy.drawCard();

        // Пауза между ходами
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore();
        std::cin.get();
        turn++;
    }
}


