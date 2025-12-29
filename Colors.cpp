#include "Colors.h"

// ANSI escape codes
const std::string Color::RESET = "\033[0m";

// ќсновные цвета
const std::string Color::RED = "\033[31m";
const std::string Color::GREEN = "\033[32m";
const std::string Color::YELLOW = "\033[33m";
const std::string Color::BLUE = "\033[34m";
const std::string Color::PURPLE = "\033[35m";
const std::string Color::CYAN = "\033[36m";
const std::string Color::WHITE = "\033[37m";
const std::string Color::DARK_GRAY = "\033[90m";

// яркие цвета
const std::string Color::BRIGHT_RED = "\033[91m";
const std::string Color::BRIGHT_YELLOW = "\033[93m";
const std::string Color::BRIGHT_MAGENTA = "\033[95m";
const std::string Color::BRIGHT_CYAN = "\033[96m";

// ÷вета дл€ типов карт
const std::string Color::CARD_ATTACK = Color::BRIGHT_RED;
const std::string Color::CARD_DEFENSE = Color::BRIGHT_YELLOW;
const std::string Color::CARD_DEBUFF = Color::BRIGHT_MAGENTA;
const std::string Color::CARD_BUFF = Color::BRIGHT_CYAN;