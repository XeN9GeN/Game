// Colors.h - кросс-платформенная версия

#pragma once
#include <string>

class Color {
public:
    // ANSI escape codes для цветов
    static const std::string RESET;

    // Основные цвета интерфейса
    static const std::string RED;        // Для здоровья врага и урона
    static const std::string GREEN;      // Для здоровья игрока
    static const std::string YELLOW;     // Для брони
    static const std::string BLUE;       // Для маны и магических эффектов
    static const std::string PURPLE;     // Для статусных эффектов
    static const std::string CYAN;       // Для информации о ходе
    static const std::string WHITE;      // Для нейтрального текста
    static const std::string DARK_GRAY;  // Для разделителей

    // Яркие цвета для карт
    static const std::string BRIGHT_RED;
    static const std::string BRIGHT_YELLOW;
    static const std::string BRIGHT_MAGENTA;
    static const std::string BRIGHT_CYAN;

    // Цвета для типов карт
    static const std::string CARD_ATTACK;    // Карты атаки
    static const std::string CARD_DEFENSE;   // Карты защиты
    static const std::string CARD_DEBUFF;    // Карты ослаблений
    static const std::string CARD_BUFF;      // Карты усилений
};