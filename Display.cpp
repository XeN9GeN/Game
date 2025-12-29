// Display.cpp
#include "Display.h"
#include "Face.cpp"  // для вывода лиц
#include "Colors.h"
namespace Display {

    void printAsciiArt(const std::string& art, bool isLeft) {
        std::vector<std::string> lines;
        std::stringstream ss(art);
        std::string line;

        while (std::getline(ss, line)) {
            lines.push_back(line);
        }

        for (const auto& l : lines) {
            if (isLeft) {
                std::cout << Color::GREEN << std::setw(SIDE_WIDTH) << std::left << l << Color::RESET;
            }
            else {
                std::cout << Color::RED << std::setw(SIDE_WIDTH) << std::right << l << Color::RESET;
            }
        }
    }


    void printCharacterStatusDisplay(const Character& character, const std::string& name, bool isLeft) {
        if (isLeft) {
            std::cout << Color::GREEN << std::setw(SIDE_WIDTH) << std::left
                << (name + " - HP: " + std::to_string(character.getHealth()) +
                    ", Armor: " + std::to_string(character.getArmor()) +
                    ", Mana: " + std::to_string(character.getMana())) << Color::RESET;
        }
        else {
            std::cout << Color::RED << std::setw(SIDE_WIDTH) << std::right
                << (name + " - HP: " + std::to_string(character.getHealth()) +
                    ", Armor: " + std::to_string(character.getArmor()) +
                    ", Mana: " + std::to_string(character.getMana())) << Color::RESET;
        }
    }


    void printSimpleBattle(const Character& player, const Character& enemy, int turn) {

        std::cout << Color::DARK_GRAY << "\n" << std::string(TOTAL_WIDTH, '=') << Color::RESET << "\n";
        std::cout << Color::CYAN << std::setw(TOTAL_WIDTH / 2 + 4) << std::right << "TURN " << turn << Color::RESET << "\n";
        std::cout << Color::DARK_GRAY << std::string(TOTAL_WIDTH, '=') << Color::RESET << "\n\n";


        // =========== ВЕРХНЯЯ ЧАСТЬ: СТАТИСТИКИ ===========
        std::cout << std::setw(1) << std::left << Color::GREEN << "[ PLAYER ]" << Color::RESET
            << std::setw(135) << std::right << Color::RED << "[ ENEMY ]" << Color::RESET << "\n";


        // Статистика игрока (левая часть)
        std::string playerStats = Color::GREEN + "HP: " + std::to_string(player.getHealth()) + Color::RESET +
            "  " + Color::YELLOW + "Armor: " + std::to_string(player.getArmor()) + Color::RESET +
            "  " + Color::BLUE + "Mana: " + std::to_string(player.getMana()) + Color::RESET;

        // Статистика врага (правая часть)
        std::string enemyStats = Color::RED + "HP: " + std::to_string(enemy.getHealth()) + Color::RESET +
            "  " + Color::YELLOW + "Armor: " + std::to_string(enemy.getArmor()) + Color::RESET +
            "  " + Color::BLUE + "Mana: " + std::to_string(enemy.getMana()) + Color::RESET;

        std::cout << std::setw(40) << std::left << playerStats
            << std::setw(150) << std::right << enemyStats << "\n\n";


        // =========== СРЕДНЯЯ ЧАСТЬ: ЛИЦА ПЕРСОНАЖЕЙ ===========
        std::vector<std::wstring> playerFace = getPlayerFaceLines(player.getHealth());
        std::vector<std::wstring> enemyFace = getEnemyFaceLines(enemy.getHealth());

        // Находим максимальную высоту для выравнивания
        size_t maxLines = std::max(playerFace.size(), enemyFace.size());

        // Выводим лица параллельно
        for (size_t i = 0; i < maxLines; i++) {
            std::wstring playerLine = (i < playerFace.size()) ? playerFace[i] : L"";
            std::wstring enemyLine = (i < enemyFace.size()) ? enemyFace[i] : L"";

            std::wcout << std::setw(COLUMN_WIDTH) << std::left << playerLine
                << std::setw(COLUMN_WIDTH + 80) << std::right << enemyLine
                << "\n";
        }

        // =========== НИЖНЯЯ ЧАСТЬ: СТАТУСЫ ===========
        std::cout << Color::GREEN << "PLAYER'S Statuses: " << Color::RESET;
        player.getStatuses().showStatuses();

        std::cout << Color::RED << "\nENEMY'S Statuses: " << Color::RESET;
        enemy.getStatuses().showStatuses();

        std::cout << Color::DARK_GRAY << "\n" << std::string(TOTAL_WIDTH, '=') << Color::RESET << "\n";
    }
}