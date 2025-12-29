#include "DeckLoader.h"
#include <iostream>
#include "Colors.h"

std::shared_ptr<Card> DeckLoader::createCardFromString(const std::string& line) {
    std::istringstream iss(line);
    std::string type, name, description, statusTypeStr;
    int cost = 0, value = 0, duration = 1;


    // Очищаем пробелы в начале и конце
    std::string cleanLine = line;

    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(cleanLine);

    while (std::getline(ss, token, '|')) {
        // Убираем лишние пробелы
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        tokens.push_back(token);
    }

    if (tokens.size() < 4) {
        return nullptr;
    }

    type = tokens[0];
    name = tokens[1];
    description = tokens[2];

    try {
        cost = std::stoi(tokens[3]);
    }
    catch (...) {
        return nullptr;
    }

    // Для разных типов карт разное количество параметров
    if (type == "Attack" || type == "Defense" || type == "Heal") {
        if (tokens.size() < 5) 
            return nullptr;

        try {
            value = std::stoi(tokens[4]);
        }
        catch (...) { return nullptr; }
    }

    else if (type == "Debuff") {
        if (tokens.size() < 7) 
            return nullptr; // Type|Name|Desc|Cost|StatusType|Value|Duration
        statusTypeStr = tokens[4];

        try {
            value = std::stoi(tokens[5]);
            duration = std::stoi(tokens[6]);
        }
        catch (...) { return nullptr; }
    }

    else if (type == "Buff") { }

    else { return nullptr; }// Неизвестный тип карты
   

    // Создаем карту в зависимости от типа
    if (type == "Attack") {
        return std::make_shared<Attack_card>(name, description, cost, value);
    }
    else if (type == "Defense") {
        return std::make_shared<Defense_card>(name, description, cost, value);
    }
    else if (type == "Heal") {
        return std::make_shared<Heal_card>(name, description, cost, value);
    }
    else if (type == "Buff") {
        StatusType statusType = StatusType::Dexterity;
        if (statusTypeStr == "Strength") statusType = StatusType::Strength;
        else if (statusTypeStr == "Dexterity") statusType = StatusType::Dexterity;
        else if (statusTypeStr == "Regeneration") statusType = StatusType::Regeneration;
        else if (statusTypeStr == "Haste") statusType = StatusType::Haste;
        else{
            std::cout << Color::YELLOW << "Warning: Unknown status type: " << statusTypeStr << Color::RESET << "\n";
            return nullptr;
        }
    }

    else if (type == "Debuff") {

        // Преобразуем строку в StatusType
        StatusType statusType = StatusType::Poison;
        if (statusTypeStr == "Poison") statusType = StatusType::Poison;
        else if (statusTypeStr == "Bleed") statusType = StatusType::Bleed;
        else if (statusTypeStr == "Weak") statusType = StatusType::Weak;
        else if (statusTypeStr == "Vulnerable") statusType = StatusType::Vulnerable;
        else if (statusTypeStr == "Fragile") statusType = StatusType::Fragile;

        else {
            std::cout << Color::YELLOW << "Warning: Unknown status type: " << statusTypeStr << Color::RESET << "\n";
            return nullptr;
        }
        
        //Пришлось так сделать, ибо все яды блиды и тд попали не в switch в Card.h/cpp, а уже в отдельные классы наследники Debuff
        //поэтому сам Debuff превратился в абстрактный класс, а здесь надо напрямую создавать определённый дочерний
        std::shared_ptr<Debuff_card> card;
        switch (statusType) {
        case StatusType::Poison:
            card = std::make_shared<Poison_card>(name, description, cost, value, duration);
            break;
        case StatusType::Bleed:
            card = std::make_shared<Bleed_card>(name, description, cost, value, duration);
            break;
        case StatusType::Weak:
            card = std::make_shared<Weak_card>(name, description, cost, value, duration);
            break;
        case StatusType::Vulnerable:
            card = std::make_shared<Vulnerable_card>(name, description, cost, value, duration);
            break;
        case StatusType::Fragile:
            card = std::make_shared<Fragile_card>(name, description, cost, value, duration);
            break;
        default:
            return nullptr;
        }

        return card;
    }

    std::cout << Color::YELLOW << "Warning: Unknown card type: " << type << Color::RESET << "\n";
    return nullptr;
}



bool DeckLoader::loadPlayerDeck(Character& player, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << Color::RED << "Error: Cannot open file " << filename << Color::RESET << "\n";
        return false;
    }

    std::string line;
    int cardCount = 0;
    int lineNum = 0;

    std::cout << Color::CYAN << "Loading deck from " << filename << "..." << Color::RESET << "\n";

    while (std::getline(file, line)) {
        lineNum++;

        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '#' || line[0] == '[') 
            continue;

        std::cout << Color::WHITE << "Line " << lineNum << ": " << line << Color::RESET << "\n";

        auto card = createCardFromString(line);
        if (card) {
            player.addCardToDeck(card);
            cardCount++;
            std::cout << Color::GREEN << "   Card created: " << card->getName() << Color::RESET << "\n";
        }
        else {
            std::cout << Color::YELLOW << "   Could not parse card: " << line << Color::RESET << "\n";
        }
    }

    file.close();

    if (cardCount == 0) {
        std::cout << Color::YELLOW << "Warning: No cards loaded from " << filename << Color::RESET << "\n";
        return false;
    }

    std::cout << Color::GREEN << "Successfully loaded " << cardCount << " cards to player deck" << Color::RESET << "\n\n\n";
    return true;
}